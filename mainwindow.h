#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>
#include <list>

using namespace std;

namespace Ui {

class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  
  void tcpConnect(QString);

public slots:

  void mostraLcdMinimo(int value);
  void mostraLcdMaximo(int value);
  void mostraTempo(int value);

  void digitIP();
  void veloc(int);
  void discon();
  void start();
  void Stop();
  void timerEvent(QTimerEvent *e);
private:
  int delay = 0;
  int frequencia;
  int tempor;
  int flag;
  list<QString> dataL;
  Ui::MainWindow *ui;
  QTcpSocket *socket;
};

#endif // MAINWINDOW_H
