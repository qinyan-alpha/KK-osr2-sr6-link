#include "Server.h"



void Bulid_server::get_command(){
    server = new QTcpServer;
    Start = true;
    while(!end){
        switch(command){
        case -1:
            QThread::msleep(10);
            break;
        case 0:
            socket->abort();
            server->close();
            command = -1;
            emit back_value(0);
            break;
        case 1:
            qDebug() << "server_ip: " << server_ip << "port: " << port;
            server->listen(QHostAddress(server_ip),quint16(port));
            emit back_value(1);
            command = 2;
            break;
        case 2:
            if (server->waitForNewConnection()){
                socket = server->nextPendingConnection();
                client_address = socket->peerAddress().toString();
                qDebug() << "New connection from" << client_address;
                emit back_value(2);
                command = 3;
            }
            else{QThread::msleep(10);}
            break;
        case 3:
            if (check_link()){
                socket->waitForReadyRead(3);
                data.append(socket->readAll());
                if (data != ""){
                    //qDebug() << data;
                    QStringList datalist = data.split("|");
                    file_path = datalist[0];
                    index = datalist[1].toInt();
                    sleep_time = datalist[2].toDouble();
                    emit back_value(3);
                    //qDebug () << "file_path:" << file_path << "play:" << play << "play_time:" << play_time;
                }
                data.clear();
            }
            else{QThread::msleep(1);}
            break;
        }
    }
    Start = false;
}


bool Bulid_server::check_link(){
    socket->waitForConnected();
    if (socket->state() == QAbstractSocket::ConnectedState){
        return true;
    }
    else{
        qDebug() << "disconnection from" << client_address;
        emit back_value(-1);
        command = -1;
        socket->abort();
        server->close();
        return false;
    }
}


Bulid_server::Bulid_server(QObject* parent) : QThread(parent)
{
    command = -1;
    end = false;
    Start = true;
    client_address = "no";

    file_path = "no";
    index = 0;
    sleep_time = 0;
}
