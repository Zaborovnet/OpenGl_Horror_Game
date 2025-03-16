#include "TextureGenerator.h"
#include <cstdlib>
#include <ctime>
#include <QDebug>

void TextureGenerator::generateWallTexture(unsigned int &textureID, int width, int height) {
  unsigned char *data = new unsigned char[width * height * 3]; // RGB
  for(int y = 0; y < height; y++) {
      for(int x = 0; x < width; x++) {
          // Добавляем полосы с помехами
          int noise = rand() % 50;
          int pattern = (x / 32 + y / 32) % 2;

          data[(y*width+x)*3] = pattern ? 200 + noise : 50 + noise;
          data[(y*width+x)*3+1] = pattern ? 200 + noise : 50 + noise;
          data[(y*width+x)*3+2] = pattern ? 200 + noise : 50 + noise;
      }
  }

  glGenTextures(1, &textureID);
  glBindTexture(GL_TEXTURE_2D, textureID);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  delete[] data;

  qDebug() << "Wall texture generated"; // Отладка
}

void TextureGenerator::generateFloorTexture(unsigned int &textureID, int width, int height) {
  unsigned char *data = new unsigned char[width * height * 3]; // RGB
  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      int idx = (y * width + x) * 3;
      data[idx] = 50; // Темно-коричневый
      data[idx + 1] = 25; // Коричневый
      data[idx + 2] = 0; // Черный
    }
  }

  glGenTextures(1, &textureID);
  glBindTexture(GL_TEXTURE_2D, textureID);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  delete[] data;

  qDebug() << "Floor texture generated"; // Отладка
}
