#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  MainWindow mainWindow;
  mainWindow.resize(800, 600);
  mainWindow.setWindowTitle("Night Store Horror");
  mainWindow.show();


  return app.exec();
}
