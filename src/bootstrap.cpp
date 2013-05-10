#include <iostream>
#include "common.hpp"
#include "bootstrap.hpp"
#include "gl.hpp"

/* xtrium stuff */
#include <vector> 

#define NEPLAYER_NOTEOFF 0
#define NEPLAYER_NOTEON  1
#define FRAMES_PER_PULSE (2646000 / (NSD_TEMPO * 96))

using namespace std;

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
Ne::Mixer *mixer;
Ne::Wavetable *wavetbl;
unsigned int NSD_TEMPO;
Ne::AudioDevice *ad;
float cursor;

bootstrap_c::bootstrap_c(float width, float height, bool full) :
    _width(width)
  , _height(height)
  , _pWin(nullptr)
  , _textWriter(nullptr)
  , _mod0(nullptr)
  , _mod1(nullptr)
  , _mod2(nullptr)
  , _mod3(nullptr) {
  GLubyte const *glstr;

  _pWin = new window_c(width, height, full);
  cout << "init window" << endl;

  glstr = glGetString(GL_VERSION);
  cout << "OpenGL Version String: " << glstr << endl;
}

bootstrap_c::~bootstrap_c() {
  delete _mod0;
  delete _mod1;
  delete _mod2;
  delete _mod3;
  delete _textWriter;
  delete _pWin;
#if FMOD_SYNTH
  FMOD_System_Release(_sndsys);
#endif
}

void * track_play_routine(void*) {
  unsigned int nTracks = ((unsigned int*)nsd_data)[0];
  unsigned int loadOffset = 4;

  unsigned int NSD_TEMPO = ((unsigned int*)(&nsd_data[loadOffset]))[0];
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

  ad = Ne::AudioDevice::getInstance();
  ad->setSongLength(165 * 44100);
  ad->open();
  cout << "init softsynth" << endl;

  mixer = new Ne::Mixer;
  wavetbl = new Ne::Wavetable;
  nsd_prepare(mixer, wavetbl);

  bool continuePlaying  = true;
  unsigned int curTick  = 0;
  unsigned int curFrame = 0;
  unsigned short blankTicks = 1024;
  //float step = 0.98571f / 44100.f;
  float step = 1.f / 44100.f;
  cursor = 0.;

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
              mixer->noteOn(trk, ev.data1, ev.data2);
            if(ev.type == NEPLAYER_NOTEOFF)
              mixer->noteOff(trk, ev.data1);

            ++(ms_trackIndices[trk]);
          }
          else
            break;
        }
      }

      mixer->process(cursor, pulseBuffer[frame], pulseBuffer[frame + 1]);
      ++curFrame;
      cursor += step;
    }

    // write buffer to audio device
    ad->write(pulseBuffer, FRAMES_PER_PULSE * 2 * sizeof(float));
    if(curTick == 4)
      ad->start();

    ++curTick;
    if(!continuePlaying)
      --blankTicks;
  }

  ad->close();
  return nullptr; 
}

void bootstrap_c::_launch_track() {
  auto r = pthread_create(&_trackThread, nullptr, &track_play_routine, nullptr);
}

float bootstrap_c::_track_cursor() {
#if FMOD_SYNTH
  unsigned int i;
  FMOD_Channel_GetPosition(_chan, &i, FMOD_TIMEUNIT_MS);
  return i / 1000.f;
#endif
  return cursor;
}

#if FMOD_SYNTH
float bootstrap_c::_track_length() {
  unsigned int i;
  FMOD_Sound_GetLength(_track, &i, FMOD_TIMEUNIT_MS);
  return i / 1000.f;
}
void bootstrap_c::_advance_track(float t) {
  auto c = _track_cursor();
  FMOD_Channel_SetPosition(_chan, (c+t)*1000,FMOD_TIMEUNIT_MS );
}
#endif

void bootstrap_c::init() {
  /* init the lol */
  //_pWin = new window_c(WIDTH, HEIGHT, FULLSCREEN);
  /* init the text writer */
  _textWriter = new text_writer_c;
  /* init the mods */
  _mod0 = new mod0_c(_width, _height, *_textWriter);
  _mod1 = new mod1_c(_width, _height, *_textWriter);
  _mod2 = new mod2_c(_width, _height, *_textWriter, _mod0->cube_program(), _mod0->cube());
  _mod3 = new mod3_c(_width, _height, *_textWriter);
  glEnable(GL_DEPTH_TEST);
  /* init the softsynth */
#if FMOD_SYMTH
  FMOD_System_CreateStream(_sndsys, TRACK_PATH.c_str(), FMOD_HARDWARE | FMOD_LOOP_OFF | FMOD_2D, 0, &_track);
  FMOD_System_PlaySound(_sndsys, FMOD_CHANNEL_FREE, _track, 0, &_chan);
#endif
  //_init_softsynth();
}

void bootstrap_c::run() {
  float time;

  /* launch the track */
  _launch_track();
#if DEBUG
  //_advance_track(54.0f);
#endif
  while ((time = _track_cursor()) <= 150.f && treat_events()) {
#if DEBUG
    cout << "time: " << time << endl;
#endif
    if (time < 27.5f) {
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      _mod0->render(time);
    //} else if (time < 54.8732f) {
    } else if (time < 55.f) {
      _mod1->render(time);
    } else if (time < 137.2f) {
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      _mod2->render(time);
    } else {
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      _mod3->render(time);
    }
    _pWin->swap_buffers();
  }

  /* wait for the end of the track */
  //pthread_join(_trackThread, NULL);
}

bool bootstrap_c::treat_events() {
  XEvent event;
  auto disp = _pWin->display();

  while (XPending(disp)) {
    XNextEvent(disp, &event);
    switch (event.type) {
      case KeyPress :
        if (XKeycodeToKeysym(disp, event.xkey.keycode, 0) == XK_Escape)
          return false;
        break;

      case DestroyNotify :
        return false;
        break;

      default :;
    }
  }

  return true;
}

