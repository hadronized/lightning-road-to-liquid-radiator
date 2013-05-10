#include <cstdio>

#include "audiodevice.hpp"

#define clamp(x,a,b) (x<a?a:(x>b?b:x))

using namespace Ne;

AudioDevice* AudioDevice::_instance       = NULL;
FILE*        AudioDevice::_outFile        = NULL;
bool         AudioDevice::_wav            = false;
unsigned int AudioDevice::_songLength     = 0;

#ifdef __WIN32__
float*       AudioDevice::_songBuffer     = NULL;
unsigned int AudioDevice::_bufferLength   = MAX_DURATION * SAMPLE_RATE * N_CHANNELS;
unsigned int AudioDevice::_writtenSamples = 0;
WAVEFORMATEX AudioDevice::_waveFMT        = {WAVE_FORMAT_IEEE_FLOAT, N_CHANNELS, SAMPLE_RATE, SAMPLE_RATE*sizeof(float)*N_CHANNELS, sizeof(float)*N_CHANNELS, sizeof(float)*8, 0};
WAVEHDR      AudioDevice::_waveHDR        = {0, 0, 0, 0, 0, 0, 0, 0};
HWAVEOUT     AudioDevice::_hWaveOut;
#endif /* __WIN32__ */

#ifdef __linux__
snd_pcm_t*   AudioDevice::_wavHandle;
#endif /* __linux__ */

#ifdef __APPLE__
// TODO : Mac OS X sound output using the Audio Queue API
#endif /* __APPLE__ */

AudioDevice::AudioDevice()
{
    if(!_wav)
    {
#ifdef __WIN32__
#endif /* __WIN32__ */

#ifdef __linux__
#endif /* __linux__ */

#ifdef __APPLE__
// TODO : Mac OS X sound output using the Audio Queue API
#endif /* __APPLE__ */
    }
    
    _prepared = false;
}

AudioDevice::~AudioDevice()
{
    if(isOpen())
        close();
    _instance = NULL;
}

AudioDevice* AudioDevice::getInstance()
{
    if(!_instance)
        _instance = new AudioDevice();
    return _instance;
}

void AudioDevice::setWav(bool wav)
{
    _wav = wav;
}

void AudioDevice::setSongLength(unsigned int songLength)
{
    _songLength = songLength * 2 * 2; // we use sint16 so 2 bytes, and stereo => 2 channels
}

void AudioDevice::open()
{
    if(!_wav)
    {
#ifdef __WIN32__
		_songBuffer = new float[_bufferLength];
        _waveHDR.lpData = (LPSTR)_songBuffer;
        _waveHDR.dwBufferLength = sizeof(float) * _bufferLength;

        waveOutOpen(&_hWaveOut, WAVE_MAPPER, &_waveFMT, 0, 0, CALLBACK_NULL);
        waveOutPrepareHeader(_hWaveOut, &_waveHDR, sizeof(_waveHDR));
#endif /* __WIN32__ */

#ifdef __linux__
        snd_pcm_open(&_wavHandle, "default", SND_PCM_STREAM_PLAYBACK, 0);
        snd_pcm_set_params(_wavHandle, SND_PCM_FORMAT_FLOAT_LE, SND_PCM_ACCESS_RW_INTERLEAVED, N_CHANNELS, SAMPLE_RATE, 0, 128000);
#endif /* __linux__ */

#ifdef __APPLE__
// TODO : Mac OS X sound output using the Audio Queue API
#endif /* __APPLE__ */
    }
    else
    {
        _outFile = fopen("neon_output.wav", "wb");

        // "RIFF" header
        fprintf(_outFile, "RIFF");
        fprintf(_outFile, "%c", (_songLength + 36) & 0xFF);
        fprintf(_outFile, "%c", ((_songLength + 36) >> 8) & 0xFF);
        fprintf(_outFile, "%c", ((_songLength + 36) >> 16) & 0xFF);
        fprintf(_outFile, "%c", ((_songLength + 36) >> 24) & 0xFF);
        fprintf(_outFile, "WAVE");

        // "fmt " subchunk
        fprintf(_outFile, "fmt ");
        fprintf(_outFile, "%c", 16);    // Subchunk size (4b)
        fprintf(_outFile, "%c", 0);
        fprintf(_outFile, "%c", 0);
        fprintf(_outFile, "%c", 0);
        fprintf(_outFile, "%c", 1);     // Format : PCM (2b)
        fprintf(_outFile, "%c", 0);
        fprintf(_outFile, "%c", 2);     // Channels : 2 (2b)
        fprintf(_outFile, "%c", 0);
        fprintf(_outFile, "%c", 0x44);  // Sample rate : 44100Hz (4b)
        fprintf(_outFile, "%c", 0xAC);
        fprintf(_outFile, "%c", 0);
        fprintf(_outFile, "%c", 0);
        fprintf(_outFile, "%c", 0x10);  // Byte rate : 176400bps (44100 * sint16=2 * stereo=2) (4b)
        fprintf(_outFile, "%c", 0xB1);
        fprintf(_outFile, "%c", 0x02);
        fprintf(_outFile, "%c", 0);
        fprintf(_outFile, "%c", 4);     // Block alignment : 4B (sint16=2 * stereo=2) (4b)
        fprintf(_outFile, "%c", 0);
        fprintf(_outFile, "%c", 16);    // Bits per sample : sint16 = 16 (2b)
        fprintf(_outFile, "%c", 0);

        // "data" subchunk
        fprintf(_outFile, "data");
        fprintf(_outFile, "%c", _songLength & 0xFF);
        fprintf(_outFile, "%c", (_songLength >> 8) & 0xFF);
        fprintf(_outFile, "%c", (_songLength >> 16) & 0xFF);
        fprintf(_outFile, "%c", (_songLength >> 24) & 0xFF);
    }

    _prepared = true;
}

void AudioDevice::close()
{
    if(!_wav)
    {
        if(_prepared)
        {
#ifdef __WIN32__
            waveOutBreakLoop(_hWaveOut);
            waveOutUnprepareHeader(_hWaveOut, &_waveHDR, sizeof(WAVEHDR));
            waveOutReset(_hWaveOut);
            waveOutClose(_hWaveOut);
            _waveHDR.dwBytesRecorded = 0;
            _writtenSamples = 0;

                        delete [] _songBuffer;
                        _songBuffer = NULL;
#endif /* __WIN32__ */

#ifdef __linux__
            snd_pcm_close(_wavHandle);
#endif /* __linux__ */

#ifdef __APPLE__
// TODO : Mac OS X sound output using the Audio Queue API
#endif /* __APPLE__ */
        }
    }
    else
    {
        fclose(_outFile);
    }

    _prepared = false;
}

bool AudioDevice::isOpen() const
{
    return _prepared;
}

void AudioDevice::write(float* buffer, unsigned int bufferLength)
{
    if(_prepared)
    {
        if(_wav)
        {
            for(unsigned int i = 0; i < bufferLength / (sizeof(float)); i++)
            {
                float v = clamp(buffer[i], -1.0f, 1.0f);
                short value = short(v * 32767.0f);
                fprintf(_outFile, "%c", value & 0xFF);
                fprintf(_outFile, "%c", (value >> 8) & 0xFF);
            }
        }
        else
        {
#ifdef __WIN32__
            int bl = bufferLength / sizeof(float);
            int endPos = (_writtenSamples + bl) < _bufferLength ? (_writtenSamples + bl) : _bufferLength;

            for(int i = _writtenSamples; i < endPos; i++)
                _songBuffer[i] = buffer[i-_writtenSamples];

            _writtenSamples += bl;
#endif /* __WIN32__ */

#ifdef __linux__
            snd_pcm_writei(_wavHandle, buffer, bufferLength / (sizeof(float) * N_CHANNELS));
#endif /* __linux__ */

#ifdef __APPLE__
// TODO : Mac OS X sound output using the Audio Queue API
#endif /* __APPLE__ */
        }
    }
}

void AudioDevice::start()
{
    if((!_wav) && _prepared)
    {
#ifdef __WIN32__
        waveOutWrite(_hWaveOut, &_waveHDR, sizeof(_waveHDR));
#endif /* __WIN32__ */

#ifdef __linux__
#endif /* __linux__ */

#ifdef __APPLE__
// TODO : Mac OS X sound output using the Audio Queue API
#endif /* __APPLE__ */
    }
}
