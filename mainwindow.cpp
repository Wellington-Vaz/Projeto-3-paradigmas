#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QString>
#include <QTimer>
#include <cstdlib>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
    flag=0;

    //Liga o botão start
    connect(ui->pushButtonStart,
            SIGNAL(clicked(bool)),
            this,
            SLOT(start()));

    //Liga o botão Stop
    connect(ui->pushButtonStop,
            SIGNAL(clicked(bool)),
            this,
            SLOT(Stop()));

    //Liga o connect ao slot digitIP
    connect(ui->pushButtonConnect,
            SIGNAL(clicked(bool)),
            this,
            SLOT(digitIP()));

    //Liga o disconnect ao slot discon
    connect(ui->pushButtonDisconnect,
            SIGNAL(clicked(bool)),
            this,
            SLOT(discon()));

    //Liga o slider do temporizador
    connect(ui->horizontalSliderTiming,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(veloc(int)));
}

//Conecta no nºIP
void MainWindow::tcpConnect(QString str)
{
    socket->connectToHost(str,1234);
    qDebug() << str;
    if(socket->waitForConnected(3000)){
        qDebug() << "Connected";
    }
    else{
        qDebug() << "Disconnected";
    }
}

//Copia o texto para uma qstring
void MainWindow::digitIP()
{
    QString str= ui->lineEditDigIP->text();
    tcpConnect(str);
}

//Mostra no lcd o valor minimo a partir do slider
void MainWindow::mostraLcdMinimo(int value)
{
    ui->lcdNumberMin->display(value);
}

//Mostra no lcd o valor máximo a partir do slider
void MainWindow::mostraLcdMaximo(int value)
{
    ui->lcdNumberMax->display(value);
}

void MainWindow::mostraTempo(int value)
{
    //Transformando o valor do  slider
    int i = value;
    QString s = QString::number(i);
    ui->labelTiming_2->setText(s);
}

//Determina a taxa de envio de dados
void MainWindow::veloc(int freq)
{
    this->frequencia = freq;
}

//Desconecta o cliente
void MainWindow::discon()
{
    socket->disconnectFromHost();
    qDebug() << "Disconnected";
}

//Iniciar a conexão
void MainWindow::start()
{
    if (frequencia>0 && flag==0){
        tempor = startTimer(1000/frequencia);
        flag=flag+1;
    }
}

//Para a conexão
void MainWindow::Stop()
{
    killTimer(tempor);
    flag=flag-1;
}

//Envia dados para o servidor com data e hora
void MainWindow::timerEvent(QTimerEvent *e)
{
    QDateTime datetime;
    QString str;
    datetime = QDateTime::currentDateTime();
    str = "set "+
            datetime.toString(Qt::ISODate)+
            " "+
            QString::number(qrand()%int(ui->lcdNumberMax->value()-ui->lcdNumberMin->value())+ui->lcdNumberMin->value());
    dataL.push_back(str);
    ui->plainTextEditInfos->appendPlainText(str);
    qDebug() << socket->write(str.toStdString().c_str()) << " bytes written";
}

//Destrutor
MainWindow::~MainWindow()
{
    delete socket;
    delete ui;
}
