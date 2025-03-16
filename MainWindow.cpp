#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  game = new Game(this);
  setCentralWidget(game); // Устанавливаем game как центральный виджет
  game->setFocus();
}

MainWindow::~MainWindow() {
  delete game; // Удаляем game при закрытии окна
}
