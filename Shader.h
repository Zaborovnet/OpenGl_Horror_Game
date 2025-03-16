#ifndef SHADER_H
#define SHADER_H

#include <QOpenGLShaderProgram>

class Shader {
  public:
  Shader();
  ~Shader();
  void loadShaders();
  QOpenGLShaderProgram* getProgram() const;

  private:
  QOpenGLShaderProgram *program;
};

#endif // SHADER_H
