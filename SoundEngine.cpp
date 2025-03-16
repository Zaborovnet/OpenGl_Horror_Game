#include "SoundEngine.h"
#include <algorithm>

std::vector<float> SoundEngine::generateRain(int samples) {
  std::vector<float> buffer(samples);
  static float phase = 0.0f;

  for(int i = 0; i < samples; ++i) {
      buffer[i] = 0.3f * std::sin(phase * 5000) *
                  (1.0f - std::fmod(phase, 0.1f)*10);
      phase += 0.0001f;
    }
  return buffer;
}

std::vector<float> SoundEngine::generateCreak(int samples) {
  std::vector<float> buffer(samples);
  for(int i = 0; i < samples; ++i) {
      buffer[i] = (std::rand() % 2000 - 1000) / 10000.0f *
                  (1.0f - (float)i/samples);
    }
  return buffer;
}

float SoundEngine::noise(float phase) {
  return 2.0f * (std::rand() / (float)RAND_MAX) - 1.0f;
}
