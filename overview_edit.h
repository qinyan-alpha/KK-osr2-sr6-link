#ifndef OVERVIEW_EDIT_H
#define OVERVIEW_EDIT_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QMenu>
#include <QLabel>
#include <QWidgetAction>
#include <QLineEdit>
#include <QTimer>

class Overview_edit : public QWidget
{
    Q_OBJECT

public:
    explicit Overview_edit(QWidget *parent = nullptr);

    QList<int> values;

    QTimer timer;
    bool allow_change;
    QList<int> split_lines;
    int selected_part;
    int selected_line;
    int intervals;
    int value_edge;
    bool mouse2;
    bool mouse3;
    bool key_control;
    int move_index;
    int last_move_index;
    int margin;

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void wheelEvent(QWheelEvent* event) override;
signals:
    int current_line(int);
    void set_play();
    int add_part(int);
    int del_part(int);
    int select_part(int);
};


#endif // OVERVIEW_EDIT_H
