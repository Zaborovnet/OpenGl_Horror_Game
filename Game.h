#ifndef GAME_H
#define GAME_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QKeyEvent>
#include <QMouseEvent>
#include "Shader.h"
#include <QtCore/qmath.h>
#include <QTimer>

#include "Environment.h"
#include "SoundEngine.h"


#include<GL/glu.h>


class Game : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT

  public:
  Game(QWidget *parent = nullptr);
  ~Game();

  protected:
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int w, int h) override;
  virtual void keyPressEvent(QKeyEvent *event) override;
  virtual void mouseReleaseEvent(QMouseEvent *event) override;
  virtual void mouseMoveEvent(QMouseEvent *event) override;
  virtual void mousePressEvent(QMouseEvent *event) override;


  private:
  void setupScene();
  void renderGame();
  void updatePlayerPosition();

  void initEnvironmentalSystems();
  void updateAmbience();

  Environment m_environment;
  SoundEngine m_soundEngine;
  QTimer m_ambienceTimer;
  std::vector<float> m_audioBuffer;

  Shader *shader;
  float playerX;
  float playerZ;
  float moveSpeed;
  float sensitivity; // Коэффициент чувствительности

  float playerY; // Высота игрока
  float verticalSpeed; // Скорость по вертикали
  bool isOnGround; // Проверка, на земле ли игрок

  unsigned int floorTextureID;
  unsigned int wallTextureID;

  float cameraYaw;   // Угол поворота по оси Y
  float cameraPitch; // Угол поворота по оси X
  bool mousePressed; // Флаг, указывающий, нажата ли кнопка мыши

  float flickerTimer;
  bool lightsOn;
};

#endif // GAME_H
