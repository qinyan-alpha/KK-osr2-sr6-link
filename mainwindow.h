#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QFileInfo>
#include <QSettings>
#include <QTimer>
#include <QLabel>
#include <QPropertyAnimation>
#include <QChart>
#include <QLineSeries>
#include <QChartView>
#include "Server.h"
#include "Port_thread.h"

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

    QString btn_sty1;
    QString btn_sty2;
    QString btn_sty3;
    QString btn_sty4;

    QString btn_sty5;
    QString btn_sty6;
    QString btn_sty7;


    QSettings * settings;
    QSettings * language_setting;

    Bulid_server * server;
    Port_thread * port;
    QList<QSerialPortInfo> ports_list;
    QTimer timer1;
    QTimer timer2;
    QTimer timer3;

    bool client_link;
    bool build_server;
    bool port_link;

    QString last_file_path;
    bool play;
    float playtime;

    QList<float> inserts;
    QList<float> surges;
    QList<float> sways;
    QList<float> twists;
    QList<float> pitchs;
    QList<float> rolls;
    QList<float> play_times;
    float duration;
    float bodywidth;
    float insert_max;
    float insert_min;
    float surge_offset;
    float sway_offset;
    float last_play_time;

    int L0;
    int L1;
    int L2;
    int R0;
    int R1;
    int R2;
    int A1;
    int last_L0;
    int last_L1;
    int last_L2;
    int last_R0;
    int last_R1;
    int last_R2;
    int last_A1;
    int diff;

    QChart* chartL0;
    QChart* chartL1;
    QChart* chartL2;
    QChart* chartR0;
    QChart* chartR1;
    QChart* chartR2;
    QChart* chartA1;
    QLineSeries *seriesL0;
    QLineSeries *seriesL1;
    QLineSeries *seriesL2;
    QLineSeries *seriesR0;
    QLineSeries *seriesR1;
    QLineSeries *seriesR2;
    QLineSeries *seriesA1;
    QChartView* chartviewL0;
    QChartView* chartviewL1;
    QChartView* chartviewL2;
    QChartView* chartviewR0;
    QChartView* chartviewR1;
    QChartView* chartviewR2;
    QChartView* chartviewA1;
    QHBoxLayout* L0_Layout;
    QHBoxLayout* L1_Layout;
    QHBoxLayout* L2_Layout;
    QHBoxLayout* R0_Layout;
    QHBoxLayout* R1_Layout;
    QHBoxLayout* R2_Layout;
    QHBoxLayout* A1_Layout;

    QWidget *tips_window;
    QLayout *tips_layout;
    QLabel *tips;
    QPropertyAnimation *m_animation;

    void page_init();
    void btn_init();
    void config_init();
    void config_change();
    void init();
    void back_value_change1(int num);
    void back_value_change2(int num);
    void delay_change1();
    void delay_change2();
    void tips_window_init();
    void tips_window_start();
    void tips_window_end();

    void closeEvent(QCloseEvent* event);




private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
