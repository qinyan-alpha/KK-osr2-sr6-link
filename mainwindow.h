#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QFileInfo>
#include <QSettings>
#include <QTimer>
#include <QLabel>
#include <QPropertyAnimation>
#include "scripter_edit.h"
#include "range_silder.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QScrollBar>
#include <QDesktopServices>
#include <QWindow>
#include <QFileDialog>
#include <QWebSocket>




QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString server_ip;
    QString client_address;
    int port;
    QTcpServer *server;
    QTcpSocket *socket;
    int port_id;
    int baudrate;
    QSerialPort::DataBits databits;
    QSerialPort::Parity parity;
    QSerialPort::StopBits stopbits;
    QSerialPort::FlowControl flowcontrol;
    QList<QSerialPortInfo> ports_list;
    QSettings *settings;

    QString btn_sty1;
    QString btn_sty2;
    QString btn_sty3;
    QString btn_sty4;

    QString btn_sty5;
    QString btn_sty6;
    QString btn_sty7;
    void ui_init();
    void config_init();
    void btn_init();
    void run_btn_clicked();
    bool build_server;
    QTimer timer1;
    QTimer timer2;
    QTimer timer3;
    void delay_change1();
    QWidget *tips_window;
    QLayout *tips_layout;
    QLabel *tips;
    QPropertyAnimation *m_animation;
    void delay_change2();
    void tips_window_init();
    void tips_window_start();
    void tips_window_end();
    void link_btn_clicked();
    bool SerialPort_link;
    QSerialPort *ser;
    void new_connected();
    void server_read();
    void server_disconnected();
    void handleSerialError(QSerialPort::SerialPortError error);

    QString file_path;
    int index;
    double sleep_time;

    QList<float> inserts;
    QList<float> surges;
    QList<float> sways;
    QList<float> twists;
    QList<float> pitchs;
    QList<float> rolls;
    int L0;
    int L1;
    int L2;
    int R0;
    int R1;
    int R2;
    int last_L0;
    int last_L1;
    int last_L2;
    int last_R0;
    int last_R1;
    int last_R2;
    QList<int> L0s;
    QList<int> L1s;
    QList<int> L2s;
    QList<int> R0s;
    QList<int> R1s;
    QList<int> R2s;

    float bodywidth;
    float surge_offset;
    float sway_offset;
    float insert_max;
    float insert_min;
    bool smoothing;

    Scripter_edit *scripterL0;
    Scripter_edit *scripterL1;
    Scripter_edit *scripterL2;
    Scripter_edit *scripterR0;
    Scripter_edit *scripterR1;
    Scripter_edit *scripterR2;
    Range_Silder *silderL0;
    Range_Silder *silderL1;
    Range_Silder *silderL2;
    Range_Silder *silderR0;
    Range_Silder *silderR1;
    Range_Silder *silderR2;

    QFile* scripter_L0;
    QFile* scripter_L1;
    QFile* scripter_L2;
    QFile* scripter_R0;
    QFile* scripter_R1;
    QFile* scripter_R2;

    QJsonObject config_L0;
    QJsonObject config_L1;
    QJsonObject config_L2;
    QJsonObject config_R0;
    QJsonObject config_R1;
    QJsonObject config_R2;

    void save_scripter();
    void regenerate_scripter();
    void copy_values(QList<int> values,QList<int> index);
    void setplaytime(int index);
    void set_play();
    void rebuildtimes(QList<int> rebuild_times);
    void current_rebuildtimes(QList<int> rebuild_times);

    bool top_windows;
    bool isMenuExpanded;
    QPropertyAnimation *m_animation0;

    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    QPointF press_point;
    QPointF move_point;
    bool mouse1;
    int orientation;
    bool m_drag;
    QPoint m_dragPosition;
    bool event(QEvent *event) override;
    int scripterL0_current_hover_x;

    QString intiface_central_ip;
    QWebSocket *webclient;
    QTimer timeoutTimer;
    QTimer timeoutrestoreTimer;
    QTimer requestdevicelistTimer;
    void webclient_onconnected();
    void webclient_ondisconnected();
    void onTextMessageReceived(const QString &message);
    struct Device
    {
        QString name;
        int index;
        QList<int> feature;
        QString work_way;
        QList<int> feature_enable;
    };
    QList<Device> devices;
    QList<int> devices_index;
    void handleDeviceAdded(const QJsonObject &deviceInfo);
    void handleDeviceList(const QJsonObject &deviceList);
    void sent_LinearCmd(int& i,Device& device,int& sleeptime,int& move);
    QTimer reScanningTimer;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
