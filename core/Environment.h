#pragma once
#include <QVector3D>
#include <QOpenGLShaderProgram>

class Environment {
public:
  Environment();

  void update(float deltaTime);
  QVector3D getAmbientLight() const;
  float getFogDensity() const;
  void applyEnvironmentEffects(QOpenGLShaderProgram* shader);

private:
  float weatherIntensity;    // Интенсивность дождя
  float lightFlickerTimer;   // Таймер мерцания света
  float fogDensity;          // Плотность тумана
  QVector3D ambientLight;    // Цвет окружающего света
};
