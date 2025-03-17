#include "Shader.h"
#include <QOpenGLShader>
#include <QDebug>

Shader::Shader() {
  program = new QOpenGLShaderProgram();
}

Shader::~Shader() {
  delete program;
}

void Shader::loadShaders() {
  QOpenGLShader *vertexShader = new QOpenGLShader(QOpenGLShader::Vertex);
  const char *vertexSource = R"(
        #version 120
        attribute vec3 position;
        attribute vec2 texCoord;
        varying vec2 fragTexCoord;
        void main() {
            fragTexCoord = texCoord;
            gl_Position = gl_ModelViewProjectionMatrix * vec4(position, 1.0);
        }
    )";
  if (!vertexShader->compileSourceCode(vertexSource)) {
    qDebug() << "Vertex Shader Error:" << vertexShader->log();
  }
  program->addShader(vertexShader);

  QOpenGLShader *fragmentShader = new QOpenGLShader(QOpenGLShader::Fragment);
  const char *fragmentSource = R"(
        #version 120
        varying vec2 fragTexCoord;
        uniform sampler2D texture;
        void main() {
            gl_FragColor = texture2D(texture, fragTexCoord);
        }
    )";
  if (!fragmentShader->compileSourceCode(fragmentSource)) {
    qDebug() << "Fragment Shader Error:" << fragmentShader->log();
  }
  program->addShader(fragmentShader);

  program->link();
}

QOpenGLShaderProgram* Shader::getProgram() const {
  return program;
}
