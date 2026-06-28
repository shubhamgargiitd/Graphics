#include <QApplication>

#include "main_window.h"
int main(int argc, char *argv[]) {
  QApplication app(argc, argv);  // style the application
  MainWindow window;             // object of mainwindow class
  window.show();
  return app.exec();
}