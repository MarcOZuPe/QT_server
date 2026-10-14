#ifndef SERVER_H
#define SERVER_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QNetworkInterface>
#include <QRandomGenerator>

QT_BEGIN_NAMESPACE
namespace Ui {
class Server;
}
QT_END_NAMESPACE

class Server : public QWidget
{
    Q_OBJECT

public:
    Server(QWidget *parent = nullptr);
    ~Server();

private:
    Ui::Server *ui;
    //socket servidor
    QTcpServer *serverSocket = nullptr;
    //contenedor de mensajes
    QVector<QString> randomMessages;

    //Actividades para inicializar el servidor
    void initServer();

private slots:
    //Recibida el signal de solicitud entrante , respondemos con este slot
    void sendRandomMessage();
};
#endif // SERVER_H
