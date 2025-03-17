#include "Game.h"
#include "rendering/TextureGenerator.h"
#include "qevent.h"
#include <cmath>
#include "core/Environment.h"
#include "audio/SoundEngine.h"

Game::Game(QWidget *parent)
  : QOpenGLWidget(parent), shader(new Shader()), playerX(0.0f), playerZ(0.0f), moveSpeed(0.1f),
  sensitivity(0.1f), playerY(0.0f), verticalSpeed(0.0f),
  isOnGround(true), cameraYaw(0.0f), cameraPitch(0.0f), mousePressed(false) {
  setMouseTracking(true); // Включите отслеживание мыши
  initEnvironmentalSystems();
}

Game::~Game() {
  delete shader; // Освобождаем память
}

void Game::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D); // Включаем использование текстур
  shader->loadShaders();
  setupScene(); // Настройка сцены
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Темный фон

}

void Game::setupScene() {
  TextureGenerator::generateFloorTexture(floorTextureID, 1024, 1024);
  TextureGenerator::generateWallTexture(wallTextureID, 256, 256);
}

void Game::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0f, (float)w / (float)h, 0.1f, 100.0f);
  glMatrixMode(GL_MODELVIEW);
}

void Game::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Применяем параметры окружения к шейдеру
  QVector3D ambient = m_environment.getAmbientLight();
  shader->getProgram()->setUniformValue("ambientColor", ambient);

  // Мерцание освещения
  flickerTimer += 0.02f;
  if(flickerTimer > 1.0f) {
    lightsOn = !lightsOn;
    flickerTimer = 0;
   }

  float lightIntensity = lightsOn ? 0.8f : 0.2f;
  glClearColor(0.1f * lightIntensity, 0.1f * lightIntensity, 0.1f * lightIntensity, 1.0f);


  // Установите матрицу вида
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // Поворачиваем камеру
  glRotatef(cameraPitch, 1.0f, 0.0f, 0.0f); // Поворот по оси X
  glRotatef(cameraYaw, 0.0f, 1.0f, 0.0f);   // Поворот по оси Y

  // Перемещение камеры
  glTranslatef(-playerX, -playerY - 0.2f, -playerZ - 5.0f); // Перемещение камеры

  shader->getProgram()->bind(); // Привязываем шейдер

  renderGame(); // Рендеринг объектов

  shader->getProgram()->release(); // Отвязываем шейдер

  updatePlayerPosition(); // Обновляем позицию игрока
}

void Game::renderGame() {
    // Рендеринг пола
    shader->getProgram()->setUniformValue("texture", 0);
    glBindTexture(GL_TEXTURE_2D, floorTextureID);

    GLfloat floorVertices[] = {
        -5.0f, 0.0f, -5.0f,  0.0f, 0.0f,
        5.0f, 0.0f, -5.0f,  1.0f, 0.0f,
        5.0f, 0.0f,  5.0f,  1.0f, 1.0f,
        -5.0f, 0.0f,  5.0f,  0.0f, 1.0f
    };

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), floorVertices);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), floorVertices+3);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glDrawArrays(GL_QUADS, 0, 4);

    // Рендеринг стен
    shader->getProgram()->setUniformValue("texture", 0);
    glBindTexture(GL_TEXTURE_2D, wallTextureID);

    GLfloat wallVertices[] = {
        -1.0f, 0.0f, -1.0f,  0.0f, 0.0f,
        1.0f, 0.0f, -1.0f,  1.0f, 0.0f,
        1.0f, 2.0f, -1.0f,  1.0f, 1.0f,
        -1.0f, 2.0f, -1.0f,  0.0f, 1.0f
    };

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), wallVertices);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), wallVertices+3);
    glDrawArrays(GL_QUADS, 0, 4);
}
void Game::keyPressEvent(QKeyEvent *event) {
  float radYaw = qDegreesToRadians(cameraYaw); // Преобразуем угол в радианы

  switch (event->key()) {
  case Qt::Key_D: // Вперед
    playerX += moveSpeed * cos(radYaw); // Двигаем вперед по оси X
    playerZ += moveSpeed * sin(radYaw); // Двигаем вперед по оси Z
    break;
  case Qt::Key_A: // Назад
    playerX -= moveSpeed * cos(radYaw); // Двигаем назад по оси X
    playerZ -= moveSpeed * sin(radYaw); // Двигаем назад по оси Z
    break;
  case Qt::Key_S: // Влево
    playerX -= moveSpeed * sin(radYaw); // Двигаем влево по оси X
    playerZ += moveSpeed * cos(radYaw); // Двигаем влево по оси Z
    break;
  case Qt::Key_W: // Вправо
    playerX += moveSpeed * sin(radYaw); // Двигаем вправо по оси X
    playerZ -= moveSpeed * cos(radYaw); // Двигаем вправо по оси Z
    break;
  case Qt::Key_Q: // Поворот влево
    cameraYaw -= 1.0f; // Уменьшаем угол поворота по оси Y
    break;
  case Qt::Key_E: // Поворот вправо
    cameraYaw += 1.0f; // Увеличиваем угол поворота по оси Y
    break;
  case Qt::Key_Space: // Прыжок
    if (isOnGround) {
      verticalSpeed = 0.5f; // Начальная скорость прыжка
      isOnGround = false; // Игрок не на земле
    }
    break;
  }

  update(); // Перерисовываем сцену
}

void Game::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    mousePressed = true;
    setCursor(Qt::BlankCursor);
    QCursor::setPos(mapToGlobal(QPoint(width() / 2, height() / 2))); // Позиция курсора в центр
  }
}

void Game::mouseReleaseEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    mousePressed = false;
    unsetCursor();
  }
}

void Game::mouseMoveEvent(QMouseEvent *event) {
  if (mousePressed) {
    // Получите смещение мыши
    float deltaX = event->pos().x() - width() / 2;
    float deltaY = event->pos().y() - height() / 2;

    // Обновите углы поворота камеры
    cameraYaw += deltaX * sensitivity;   // sensitivity - коэффициент чувствительности
    cameraPitch += deltaY * sensitivity; // Инвертируем Y, чтобы движение было интуитивным

    // Ограничьте угол наклона
    if (cameraPitch > 89.0f) cameraPitch = 89.0f;
    if (cameraPitch < -89.0f) cameraPitch = -89.0f;

    // Переместите курсор в центр окна
    QCursor::setPos(mapToGlobal(QPoint(width() / 2, height() / 2)));

    update();
  }
}

void Game::updatePlayerPosition() {
  // Обновляем вертикальное положение
  if (!isOnGround) {
    playerY += verticalSpeed; // Обновляем высоту игрока
    verticalSpeed -= 0.01f; // Применяем гравитацию

    // Проверка на землю
    if (playerY <= 0.0f) {
      playerY = 0.1f; // Устанавливаем на уровень земли
      isOnGround = true; // Игрок на земле
      verticalSpeed = 0.0f; // Сбрасываем вертикальную скорость
    }
  }


  // Проверка коллизий с стенами
  // if (playerX < -4.0f || playerX > 4.0f || playerZ < -4.0f || playerZ > 4.0f) {
  //   // Возврат игрока на предыдущую позицию
  //   playerX = std::max(-4.0f, std::min(playerX, 4.0f));
  //   playerZ = std::max(-4.0f, std::min(playerZ, 4.0f));
  // }

  update();
}

void Game::initEnvironmentalSystems() {
  // Таймер для атмосферных эффектов (каждые 3 сек)
  connect(&m_ambienceTimer, &QTimer::timeout, this, &Game::updateAmbience);
  m_ambienceTimer.start(3000);

  // Инициализация звукового буфера дождя
  m_audioBuffer = m_soundEngine.generateRain(44100);
}

void Game::updateAmbience() {
  // Обновление параметров окружения
  m_environment.update(3.0f); // Дельта-тайм 3 секунды

  // Случайные звуковые эффекты
  if(rand() % 100 < 15) { // 15% шанс каждые 3 сек
      auto creakSound = m_soundEngine.generateCreak(2205);
      // Ваш метод воспроизведения звука
    }
}


