#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <GL/glew.h>
#include <GL/gl.h>

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMainWindow>
#include "core/Game.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

  public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  private:
  Ui::MainWindow *ui;
  Game *game;
};

#endif // MAINWINDOW_H
