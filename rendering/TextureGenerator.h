#ifndef TEXTUREGENERATOR_H
#define TEXTUREGENERATOR_H

#include <GL/gl.h>

class TextureGenerator {
  public:
  static void generateCheckerboardTexture(unsigned int &textureID, int width, int height);
  static void generateWallTexture(unsigned int &textureID, int width, int height);
  static void generateFloorTexture(unsigned int &textureID, int width, int height);
  static void generateShelfTexture(unsigned int &textureID, int width, int height); // Новая текстура для полок
  static void generateCounterTexture(unsigned int &textureID, int width, int height); // Новая текстура для касс
};

#endif // TEXTUREGENERATOR_H
