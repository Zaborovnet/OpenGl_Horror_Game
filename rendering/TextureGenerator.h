#ifndef TEXTUREGENERATOR_H
#define TEXTUREGENERATOR_H

#include <GL/gl.h>

class TextureGenerator {
  public:
  static void generateCheckerboardTexture(unsigned int &textureID, int width, int height);
  static void generateWallTexture(unsigned int &textureID, int width, int height);
  static void generateFloorTexture(unsigned int &textureID, int width, int height);
};

#endif // TEXTUREGENERATOR_H
