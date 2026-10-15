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
    QString info = "IP:" + ip + ", port :" + port ;
    qDebug()<<info;
    ui->lbl_ip_port->setText(info);
}

void Server::sendRandomMessage()
{
    //seleccionamos un mensaje alaetorio
    QString rndMessage = randomMessages [QRandomGenerator::global()->bounded(randomMessages.size())];
    ui->lbl_message->setText(rndMessage);
    //Preparar el mensaje para enviarse a traves de la red
    QByteArray qByteArray ;
    //canal
    QDataStream qDataStream (&qByteArray,QIODevice::WriteOnly);
    //insertar el mensaje en el stream
    qDataStream<< rndMessage ;
    //socket client
    QTcpSocket *clientConnection = serverSocket->nextPendingConnection();
    //cuando el cliente termina la transaccion se elimina
    connect(clientConnection,&QAbstractSocket::disconnected,clientConnection,&QObject::deleteLater);
    //enviar mensaje
    clientConnection->write(qByteArray);
    //termina el envio
    clientConnection->disconnectFromHost();
}
