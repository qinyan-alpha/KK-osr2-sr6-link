#ifndef SCRIPTER_EDIT_H
#define SCRIPTER_EDIT_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QMenu>
#include <QLabel>
#include <QWidgetAction>
#include <QLineEdit>


class Scripter_edit : public QWidget
{
    Q_OBJECT

public:
    explicit Scripter_edit(QWidget *parent = nullptr);

    QList<int> values;
    QList<int> old_values;
    int intervals;
    int value_edge;
    QList<int> selected_values;
    bool mouse1;
    bool mouse3;
    QPointF press_point;
    QPointF move_point;
    bool focus;
    bool key_shift;
    bool key_control;
    QMenu *menubar;
    QAction *action1;
    QAction *action2;
    QAction *action3;
    QAction *action4;
    QAction *action5;
    QAction *action6;
    QAction *action7;
    QAction *action8;
    QAction *action9;
    QAction *action10;
    QAction *action11;
    QAction *action12;
    QAction *action13;
    int margin;
    int selected_line;
    QList<int> selected_times;
    QLabel *show_label;
    QLineEdit *value_lineEdit;
    QList<int> copy_values;
    QList<int> copy_values_indexs;
    QList<QList<int>> record_values;
    bool movefirst;

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void focusInEvent(QFocusEvent *event) override;
    void focusOutEvent(QFocusEvent *event) override;
    void wheelEvent(QWheelEvent* event) override;
signals:
    void updatevalue_lineEdit(const QString &text);
    int current_line(int);
    QList<int> get_copy_values(QList<int>,QList<int>);
};


#endif // SCRIPTER_EDIT_H
