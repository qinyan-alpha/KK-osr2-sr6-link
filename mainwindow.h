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
#include "range_silder.h"
#include "overview_edit.h"
#include "scripter_edit3.h"
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
    QList<float> blowjob_inserts;
    QList<float> blowjob_surges;
    QList<float> blowjob_sways;
    QList<float> blowjob_twists;
    QList<float> blowjob_pitchs;
    QList<float> blowjob_rolls;
    QList<float> breastsex_inserts;
    QList<float> breastsex_surges;
    QList<float> breastsex_sways;
    QList<float> breastsex_twists;
    QList<float> breastsex_pitchs;
    QList<float> breastsex_rolls;
    QList<float> handjobL_inserts;
    QList<float> handjobL_surges;
    QList<float> handjobL_sways;
    QList<float> handjobL_twists;
    QList<float> handjobL_pitchs;
    QList<float> handjobL_rolls;
    QList<float> handjobR_inserts;
    QList<float> handjobR_surges;
    QList<float> handjobR_sways;
    QList<float> handjobR_twists;
    QList<float> handjobR_pitchs;
    QList<float> handjobR_rolls;
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
    void list_clear();

    float bodywidth;
    float surge_offset;
    float sway_offset;
    float insert_max;
    float insert_min;

    Range_Silder *silderL0;
    Range_Silder *silderL1;
    Range_Silder *silderL2;
    Range_Silder *silderR0;
    Range_Silder *silderR1;
    Range_Silder *silderR2;

    Overview_edit *overview_edit;
    Scripter_edit3 *scripter3L0;
    Scripter_edit3 *scripter3L1;
    Scripter_edit3 *scripter3L2;
    Scripter_edit3 *scripter3R0;
    Scripter_edit3 *scripter3R1;
    Scripter_edit3 *scripter3R2;

    QFile* scripter_L0;
    QFile* scripter_L1;
    QFile* scripter_L2;
    QFile* scripter_R0;
    QFile* scripter_R1;
    QFile* scripter_R2;
    QFile* scence;

    QJsonObject config_L0;
    QJsonObject config_L1;
    QJsonObject config_L2;
    QJsonObject config_R0;
    QJsonObject config_R1;
    QJsonObject config_R2;
    QJsonObject scence_cfg;
    bool new_version;

    struct ScenePart {
        int part;
        QString lovemaking_mode;
        QString charas;
    };

    QList<ScenePart> sceneParts;
    int selected_part;
    void convertsr6sToFunscript(const QList<int>& sr6s, const QString& file_path);
    void save_scripter();
    void regenerate_scripter();
    void copy_values(QList<int> values,QList<int> index);
    void setplaytime(int index);
    void set_play();
    void rebuildtimes3(QList<int> rebuild_times);
    void update_list(QObject* sender,int way,QList<int> rebuild_times);

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


    QTimer writerTimer;
    bool allowriter;

    struct Lovemaking_data{
        QList<float> inserts;
        QList<float> surges;
        QList<float> sways;
        QList<float> twists;
        QList<float> pitchs;
        QList<float> rolls;
        QList<float> blowjob_inserts;
        QList<float> blowjob_surges;
        QList<float> blowjob_sways;
        QList<float> blowjob_twists;
        QList<float> blowjob_pitchs;
        QList<float> blowjob_rolls;
        QList<float> breastsex_inserts;
        QList<float> breastsex_surges;
        QList<float> breastsex_sways;
        QList<float> breastsex_twists;
        QList<float> breastsex_pitchs;
        QList<float> breastsex_rolls;
        QList<float> handjobL_inserts;
        QList<float> handjobL_surges;
        QList<float> handjobL_sways;
        QList<float> handjobL_twists;
        QList<float> handjobL_pitchs;
        QList<float> handjobL_rolls;
        QList<float> handjobR_inserts;
        QList<float> handjobR_surges;
        QList<float> handjobR_sways;
        QList<float> handjobR_twists;
        QList<float> handjobR_pitchs;
        QList<float> handjobR_rolls;
        float bodywidth;
        QString charas_name;
    };

    QList<Lovemaking_data> lovemaking_datas;


private:
    Ui::MainWindow *ui;



};
#endif // MAINWINDOW_H
