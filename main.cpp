#include <alsa/asoundlib.h>
#include <iostream>
#include <fstream>
 
// Function to read a WAV file and return its data
short* readWavFile(const char* filename, int& samples, int& rate) {
    std::ifstream file(filename, std::ios::binary);
 
    if (!file.is_open()) {
        std::cerr << "Error opening the WAV file." << std::endl;
        return nullptr;
    }
 
    char header[44];
    file.read(header, sizeof(header));
 
    rate = *reinterpret_cast<int*>(header + 24);
    samples = *reinterpret_cast<int*>(header + 40);
 
    short* buffer = new short[samples];
    file.read(reinterpret_cast<char*>(buffer), samples * sizeof(short));
    file.close();
 
    return buffer;
}
 
int main() {
    const char* filename = "/home/basil/Audio2/test.wav"; // Replace with your WAV file path
 
    int samples, rate;
    short* buffer = readWavFile(filename, samples, rate);
 
    if (!buffer) {
        return 1; // Exit if there's an error reading the WAV file
    }
 
    // Initialize ALSA
    snd_pcm_t* pcm_handle;
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
