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
    //Enviar un mensaje aleatorio
    connect(serverSocket,&QTcpServer::newConnection,this,&Server::sendRandomMessage);
}

Server::~Server()
{
    delete ui;
}

void Server::initServer()
{
    //crear los mensajes aleatorios
    for (int i = 0 ;i < 100 ; i++){
        randomMessages<<"Mensaje aleatorio" + QString :: number(i+1);
    }
    //arrancar el socket
    if (!serverSocket->listen()){
        qDebug() << "Error en el servidor:"+ serverSocket ->errorString();
        return;
    }
    //obtener los datos del servidor
    int puerto = serverSocket->serverPort();
    QString port = QString :: number(puerto);
    qDebug()<<"port : "<< port ;
    QString ip ;
    //listar las IPs
    QList<QHostAddress> ipList = QNetworkInterface ::allAddresses();
    for (int i = 0 ; i < ipList.size();++i){
        if (ipList.at(i) != QHostAddress::LocalHost && ipList.at(i).toIPv4Address()){
            ip = ipList.at(i).toString();
            break;
        }
    }
    qDebug()<<ip;
}

void Server::sendRandomMessage()
{

}
