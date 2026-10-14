#include "server.h"
#include "ui_server.h"

Server::Server(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Server)
{
    ui->setupUi(this);
    //inicializar el socket server
    serverSocket = new QTcpServer(this);
    //inicializar al servidor
    initServer();
    //conexiones
    connect(ui->btn_close,&QAbstractButton::clicked,this,&QWidget::close);
}

Server::~Server()
{
    delete ui;
}

void Server::initServer()
{

}

void Server::sendRandomMessage()
{

}
