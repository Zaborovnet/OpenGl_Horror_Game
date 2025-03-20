#ifndef GAME_H
#define GAME_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QKeyEvent>
#include <QMouseEvent>
#include "rendering/Shader.h"
#include <QtCore/qmath.h>
#include <QTimer>

#include "core/Environment.h"
#include "audio/SoundEngine.h"
#include "PlayerState.h"


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
  void renderQuadVertical(float x, float y, float z, float width, float height);
  void renderQuadHorizontal(float x, float y, float z, float width, float height);

  void initEnvironmentalSystems();
  void updateAmbience();

  Environment m_environment;
  SoundEngine m_soundEngine;
  QTimer m_ambienceTimer;
  std::vector<float> m_audioBuffer;
  PlayerState m_playerState; // Объект для управления состоянием игрока

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
  unsigned int shelfTextureID; // Текстура для полок
  unsigned int counterTextureID; // Текстура для касс

  float cameraYaw;   // Угол поворота по оси Y
  float cameraPitch; // Угол поворота по оси X
  bool mousePressed; // Флаг, указывающий, нажата ли кнопка мыши

  float flickerTimer;
  bool lightsOn;
};

#endif // GAME_H
