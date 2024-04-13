#ifndef SERVER_H
#define SERVER_H

#include <QThread>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>


class Bulid_server : public QThread {
    Q_OBJECT
public:
    explicit Bulid_server(QObject* parent = nullptr);

    bool Start;
    int command;
    bool end;
    QString server_ip;
    QString client_address;
    int port;
    QTcpServer *server;
    QTcpSocket *socket;

    QString data;

    QString file_path;
    int index;
    double sleep_time;

    void get_command();
    bool check_link();
    void run() override{get_command();};

signals:
    int back_value(int);
};




















#endif // SERVER_H
