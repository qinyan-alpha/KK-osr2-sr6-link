#ifndef RANGE_SILDER_H
#define RANGE_SILDER_H

#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include <QMouseEvent>


class Range_Silder : public QWidget
{
    Q_OBJECT

public:
    explicit Range_Silder(QWidget *parent = nullptr);

    int maxvalue;
    int minvalue;
    int value;
    int value_edge;
    int margin;
    int select_value;

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    int get_x(int value);


};
#endif // RANGE_SILDER_H
