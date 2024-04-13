#include "Port_thread.h"
#include "qdebug.h"


void Port_thread::get_command(){
    QList<QSerialPortInfo> ports_list = QSerialPortInfo::availablePorts();;
    QSerialPort* ser;
    Start = true;
    while (!end) {
        switch (command) {         
        case -1:
            QThread::msleep(1);
            break;
        case 0:
            ser->close();
            ser->deleteLater();
            emit back_value(0);
            command = -1;
            break;
        case 1:
            ser = new QSerialPort;
            ser->setPort(ports_list[port_id]);
            ser->setBaudRate(baudrate);
            ser->setDataBits(databits);
            ser->setParity(parity);
            ser->setStopBits(stopbits);
            ser->setFlowControl(flowcontrol);
            if (!ser->open(QIODevice::ReadWrite)) {
                qDebug() <<  "Failed to open serial port!";
                emit back_value(-1);
                command = -1;
                break;
            }
            qDebug() << "open serial port successfully!.";
            emit back_value(1);
            first = true;
            command = 2;
            break;
        case 2:
            if (first){
                first =false;
                data = ("L0"+QString("%1").arg(L0, 3, 10, QChar('0')) + "I500"+ " "+"L1"+QString("%1").arg(L1, 3, 10, QChar('0')) + "I500" + " "+"L2"+QString("%1").arg(L2, 3, 10, QChar('0')) + "I500" + " "
                        "R0"+QString("%1").arg(R0, 3, 10, QChar('0')) + "I500"+ " "+"R1"+QString("%1").arg(R1, 3, 10, QChar('0')) + "I500" + " "+"R2"+QString("%1").arg(R2, 3, 10, QChar('0')) + "I500" +
                        + "\r\n"
                        ).toLocal8Bit();
                if (!ser->write(data)){
                    ser->close();
                    ser->deleteLater();
                    emit back_value(-1);
                    qDebug() << "serial disconnect!.";
                    command = -1;
                    break;
                }
                ser->waitForBytesWritten(10);

                qDebug() << data;
                QThread::msleep(500-40);
            }
            else{
                if (play){
                    play = false;
                    data = ("L0"+QString("%1").arg(L0, 3, 10, QChar('0')) + "I" + QString::number(sleep_time) + " " + "L1"+QString("%1").arg(L1, 3, 10, QChar('0')) + "I" + QString::number(sleep_time)+ " "+
                            "L2"+QString("%1").arg(L2, 3, 10, QChar('0')) + "I" + QString::number(sleep_time) + " " + "R0"+QString("%1").arg(R0, 3, 10, QChar('0')) + "I" + QString::number(sleep_time)+ " "+
                            "R1"+QString("%1").arg(R1, 3, 10, QChar('0')) + "I" + QString::number(sleep_time) + " " + "R2"+QString("%1").arg(R2, 3, 10, QChar('0')) + "I" + QString::number(sleep_time)+ " "+
                            "A1"+QString("%1").arg(A1, 3, 10, QChar('0')) + "I" + QString::number(sleep_time) + "\r\n"
                            ).toLocal8Bit();
                if (!ser->write(data)){
                        ser->close();
                        ser->deleteLater();
                        emit back_value(-1);
                        qDebug() << "serial disconnect!.";
                        command = -1;
                        break;
                    }
                ser->waitForBytesWritten(10);
                qDebug() << data;
                QThread::msleep(sleep_time-40);
                }                             
            }
            command = 2;
            break;
        }
    }
    Start = false;
}



Port_thread::Port_thread(QObject* parent) : QThread(parent)
{
    //port
    port_id = 0;
    baudrate = 115200;
    databits = QSerialPort::DataBits::Data8;
    parity = QSerialPort::Parity::NoParity;
    stopbits = QSerialPort::StopBits::OneStop;
    flowcontrol = QSerialPort::FlowControl::NoFlowControl;


    //Axis
    L0 = 500;
    L1 = 500;
    L2 = 500;
    R0 = 500;
    R1 = 500;
    R2 = 500;
    A1 = 0;

    //while
    end = false;
    Start = false;
    play = false;
    first = true;
    command = -1;
    sleep_time = 500;

    data = QString("").toLocal8Bit();
}
