#include <alsa/asoundlib.h>
#include <cmath>
#include <iostream>
 
// Function to generate a sine wave
void generateSineWave(short *buffer, int samples, int frequency, int rate) {
    for (int i = 0; i < samples; ++i) {
        double time = static_cast<double>(i) / rate;
        buffer[i] = static_cast<short>(32767.0 * std::sin(2.0 * M_PI * frequency * time));
    }
}
 
int main() {
    // Configuration
    const int rate = 44100;        // Sample rate
    const int duration = 5;        // Duration in seconds
    const int frequency = 440;     // Frequency of the sine wave
    const int samples = rate * duration;
 
    short *buffer = new short[samples];
 
    // Generate sine wave
    generateSineWave(buffer, samples, frequency, rate);
 
    // Initialize ALSA
    snd_pcm_t *pcm_handle;
    snd_pcm_open(&pcm_handle, "default", SND_PCM_STREAM_PLAYBACK, 0);
    snd_pcm_set_params(pcm_handle, SND_PCM_FORMAT_S16_LE, SND_PCM_ACCESS_RW_INTERLEAVED, 1, rate, 1, 500000); // 0.5sec latency
 
    // Play the audio
    snd_pcm_writei(pcm_handle, buffer, samples);
 
    // Close ALSA
    snd_pcm_close(pcm_handle);
 
    // Clean up
    delete[] buffer;
 
    return 0;
}