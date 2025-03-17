#pragma once
#include <cmath>
#include <vector>

class SoundEngine {
public:
  static std::vector<float> generateRain(int samples);
  static std::vector<float> generateCreak(int samples);
  static std::vector<float> generateHeartbeat(int samples);

private:
  static float noise(float phase);
};
