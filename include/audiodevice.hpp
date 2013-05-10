#ifndef NE__AUDIODEVICE_HPP
#define NE__AUDIODEVICE_HPP

#include <cstdio>

#ifdef __WIN32__
# include <windows.h>
# include <mmsystem.h>

#define WAVE_FORMAT_IEEE_FLOAT 0x0003
#endif /* __WIN32__ */

#ifdef __linux__
# include <alsa/asoundlib.h>
#endif /* __linux__ */

#ifdef __APPLE__
# include <AudioToolbox/AudioQueue.h>
#endif /* __APPLE__ */

#define SAMPLE_RATE  44100
#define N_CHANNELS   2
#define MAX_DURATION 600

namespace Ne
{
    class AudioDevice
    {
    public:
        static AudioDevice* getInstance();
        ~AudioDevice();
        
        static void setWav(bool wav);
        
        void open();
        void close();
        bool isOpen() const;
        
        void setSongLength(unsigned int songLength);
        
        void write(float* buffer, unsigned int bufferLength);
        void start();
        
    private:
        static AudioDevice* _instance;
        AudioDevice();
        
        static unsigned int _songLength;
        
#ifdef __WIN32__
        static float*       _songBuffer;
        static HWAVEOUT     _hWaveOut;
        static WAVEFORMATEX _waveFMT;
        static WAVEHDR      _waveHDR;

        static unsigned int _bufferLength;
        static unsigned int _writtenSamples;
#endif /* __WIN32__ */

#ifdef __linux__
        static snd_pcm_t* _wavHandle;
#endif /* __linux__ */

#ifdef __APPLE__
// TODO : Mac OS X sound output using the Audio Queue API
#endif /* __APPLE__ */

        static bool _wav;
        static FILE* _outFile;

        bool _prepared;
    };
}

#endif /* NE__AUDIODEVICE_HPP */
