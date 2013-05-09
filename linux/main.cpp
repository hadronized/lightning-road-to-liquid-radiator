#include "nsd.hpp"
#include "audiodevice.hpp"

#define FRAMES_PER_PULSE (2646000 / (NSD_TEMPO * 96))

#include <cstdio>
#include <cstring>
#include <vector>

#ifdef __WIN32__
# include <Windows.h>
#endif /* __WIN32__ */

#define NEPLAYER_NOTEOFF 0
#define NEPLAYER_NOTEON  1

struct NePlayerEvent
{
	unsigned char  type;
	unsigned int   delta;
	unsigned char  data1;
	unsigned char  data2;
};

std::vector< std::vector<NePlayerEvent> > ms_songData;
unsigned int*                             ms_trackDeltas;
unsigned int*                             ms_trackIndices;

int main(int argc, char** argv)
{
	printf("Neon software synthesizer\n  by xtrium / LNX\n\nNow playing: Skypers intro song\n");

	Ne::Mixer*     m  = new Ne::Mixer();
	Ne::Wavetable* wt = new Ne::Wavetable();

	nsd_prepare(m, wt);

	if(argc > 1)
		if(!strcmp(argv[1], "-wav"))
			Ne::AudioDevice::setWav(true);

	// Le Load Routine
	// ---------------
	unsigned int nTracks = ((unsigned int*)nsd_data)[0];
	unsigned int loadOffset = 4;

	const unsigned int NSD_TEMPO = ((unsigned int*)(&nsd_data[loadOffset]))[0];
	loadOffset += 4;

    ms_trackDeltas  = new unsigned int[nTracks];
    ms_trackIndices = new unsigned int[nTracks];

	for(unsigned int trk = 0; trk < nTracks; ++trk)
	{
		ms_trackDeltas[trk]  = 0;
		ms_trackIndices[trk] = 0;

		std::vector<NePlayerEvent> trkEvents;
		unsigned int nEvents = ((unsigned int*)(&(nsd_data[loadOffset])))[0];

		unsigned int totalDelta = 0;

		loadOffset += 4;
		for(unsigned int evt = 0; evt < nEvents; ++evt)
		{
			NePlayerEvent npe;
			npe.type = nsd_data[loadOffset++];
			unsigned short dt = ((unsigned short*)(&(nsd_data[loadOffset])))[0];
			npe.delta = dt + totalDelta;
			loadOffset += 2;
			npe.data1 = nsd_data[loadOffset++];
			if(npe.type == NEPLAYER_NOTEON)
				npe.data2 = nsd_data[loadOffset++];

			trkEvents.push_back(npe);
			totalDelta += dt;
		}
		ms_songData.push_back(trkEvents);
	}

	Ne::AudioDevice* ad = Ne::AudioDevice::getInstance();
	ad->setSongLength(165 * 44100);
	ad->open();

	// Le Play Routine
	// ---------------
	bool continuePlaying  = true;
	unsigned int curTick  = 0;
	unsigned int curFrame = 0;

	unsigned short blankTicks = 1024;

#ifdef __WIN32__
	int startTime = GetTickCount();
	int playTime  = 165000;
#endif /* __WIN32__ */

	float* pulseBuffer = new float[FRAMES_PER_PULSE * 2];
	while(continuePlaying || blankTicks)
	{
		continuePlaying = false;
		for(unsigned int frame = 0; frame < FRAMES_PER_PULSE * 2; frame += 2)
		{
			pulseBuffer[frame + 0] = 0.0f;
			pulseBuffer[frame + 1] = 0.0f;

			for(unsigned int trk = 0; trk < ms_songData.size(); ++trk)
			{
				std::vector<NePlayerEvent>& track = ms_songData[trk];

				while(true)
				{
					if(ms_trackIndices[trk] >= track.size())
						break;

					continuePlaying = true;

					NePlayerEvent& ev = track[ms_trackIndices[trk]];
					if(ev.delta <= curTick)
					{
						if(ev.type == NEPLAYER_NOTEON)
							m->noteOn(trk, ev.data1, ev.data2);
						if(ev.type == NEPLAYER_NOTEOFF)
							m->noteOff(trk, ev.data1);

						++(ms_trackIndices[trk]);
					}
					else
						break;
				}
			}

			m->process(float(curFrame) / 44100.0f, pulseBuffer[frame], pulseBuffer[frame + 1]);
			++curFrame;
		}

		// write buffer to audio device
		ad->write(pulseBuffer, FRAMES_PER_PULSE * 2 * sizeof(float));
		if(curTick == 4)
			ad->start();

		++curTick;
		if(!continuePlaying)
			--blankTicks;
	}

#ifdef __WIN32__
	printf("> Done rendering, going to sleep.\n");
	int sleepTime = playTime - (GetTickCount() - startTime);
	Sleep(sleepTime);
#endif /* __WIN32__ */

	ad->close();
	return 0;
}

