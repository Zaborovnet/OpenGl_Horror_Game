#include "Environment.h"
#include <cmath>
#include <ctime>

Environment::Environment() :
                              weatherIntensity(0.85f),
                              lightFlickerTimer(0.0f),
                              fogDensity(0.02f),
                              ambientLight(0.4f, 0.4f, 0.5f)
{
  std::srand(std::time(nullptr));
}

void Environment::update(float deltaTime) {
  // Динамическая погода
  weatherIntensity = 0.7f + 0.1f * std::sin(lightFlickerTimer * 0.5f);

  // Мерцание света
  lightFlickerTimer += deltaTime;
  if(lightFlickerTimer > 1.0f) {
      ambientLight.setX(0.3f + 0.1f * (std::rand()%100)/100.0f);
      lightFlickerTimer = 0;
    }

  // Эффект тумана
  fogDensity = 0.02f + 0.01f * weatherIntensity;
}

QVector3D Environment::getAmbientLight() const {
  return ambientLight;
}

float Environment::getFogDensity() const {
  return fogDensity;
}

void Environment::applyEnvironmentEffects(QOpenGLShaderProgram* shader) {
  shader->setUniformValue("fogDensity", fogDensity);
  shader->setUniformValue("ambientColor", ambientLight);
}
