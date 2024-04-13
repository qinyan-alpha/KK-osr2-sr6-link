#ifndef PORT_THREAD_H
#define PORT_THREAD_H


#include <QThread>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>



class Port_thread : public QThread {
    Q_OBJECT
public:
    explicit Port_thread(QObject* parent = nullptr);


    //port
    int port_id;
    int baudrate;
    QSerialPort::DataBits databits;
    QSerialPort::Parity parity;
    QSerialPort::StopBits stopbits;
    QSerialPort::FlowControl flowcontrol;

    QByteArray data;

    bool play;
    bool first;

    int L0;
    int L1;
    int L2;
    int R0;
    int R1;
    int R2;
    int A1;

    int sleep_time;


    int command;
    bool Start;
    bool end;


    void run() override {
        get_command();
    }

    void get_command();



signals:
    int back_value(int);
};


#endif // PORT_THREAD_H
