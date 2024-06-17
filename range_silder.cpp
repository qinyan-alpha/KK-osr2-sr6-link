#include "range_silder.h"


Range_Silder::Range_Silder(QWidget *parent):QWidget(parent)
{
    maxvalue = 999;
    minvalue = 0;
    value = 500;
    value_edge = 5;
    margin = 10;
    this->setFixedHeight(30);
    select_value = -1;
    this->setMinimumWidth(50);
}

void Range_Silder::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::RenderHint::Antialiasing);
    painter.setPen(QColor(34, 37, 46));
    painter.setBrush(QColor(34, 37, 46));
    QRectF rectangle(QPointF(0,0), QSizeF(this->width(), this->height()));
    painter.drawRect(rectangle);
    QPainterPath line_path1;
    line_path1.addRoundedRect(QRect(margin, this->height() / 2 - value_edge, this->width() - margin*2, 10), 5, 5);
    painter.setPen(QPen(QColor(52, 59, 72) , 0));
    painter.fillPath(line_path1, QBrush(QColor(52, 59, 72)));
    painter.setPen(QColor(255, 121, 198));
    painter.setBrush(QColor(255, 121, 198));
    QPainterPath line_path2;
    line_path2.addRoundedRect(QRect(get_x(minvalue), this->height() / 2 - 2, get_x(maxvalue)-get_x(minvalue), 4), 2, 2);
    painter.fillPath(line_path2, QColor(255, 121, 198));
    painter.drawEllipse(get_x(maxvalue) - value_edge, this->height()/2 - value_edge, value_edge*2, value_edge*2);
    painter.drawEllipse(get_x(minvalue) - value_edge, this->height()/2 - value_edge, value_edge*2, value_edge*2);
    QRectF value_rect(QPointF(get_x(value)-3,this->height()/2-9), QSizeF(6, 18));
    painter.setPen(QColor(255, 121, 198));
    painter.setBrush(QColor(255, 121, 198));
    painter.drawRect(value_rect);
}


void Range_Silder::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::MouseButton::LeftButton){
        if (event->position().y() < this->height()/2 + 9 && event->position().y() > this->height()/2 - value_edge){
            if (get_x(value) - value_edge < event->position().x() && event->position().x() < get_x(value) + value_edge){
                select_value = 1;
                return;
            }
        }
        if (event->position().y() < this->height()/2 + value_edge && event->position().y() > this->height()/2 - value_edge){
            if (get_x(minvalue) - value_edge < event->position().x() && event->position().x() < get_x(minvalue) + value_edge){
                select_value = 0;
            }
            else if (get_x(maxvalue) - value_edge < event->position().x() && event->position().x() < get_x(maxvalue) + value_edge){
                select_value = 2;
                this->height();
            }
        }

    }
}

void Range_Silder::mouseMoveEvent(QMouseEvent *event)
{
    if (select_value == 0){
        int get_value = static_cast<double>(event->position().x() - value_edge - margin)*999/(this->width() - value_edge*2 - margin*2);
        if (get_value < maxvalue && get_value >= 0){
            if (get_value > value ){value = get_value;}
            minvalue = get_value;
        }
    }
    else if (select_value == 1){
        int get_value = static_cast<double>(event->position().x() - value_edge - margin)*999/(this->width() - value_edge*2 - margin*2);
        if (get_value < maxvalue && get_value > minvalue){
            value = get_value;
        }
    }
    else if (select_value == 2){
        int get_value = static_cast<double>(event->position().x() - value_edge - margin)*999/(this->width() - value_edge*2 - margin*2);
        if (get_value > minvalue && get_value <= 999){
            if (get_value < value ){value = get_value;}
            maxvalue = get_value;
        }
    }
    this->update();
}

void Range_Silder::mouseReleaseEvent(QMouseEvent *event)
{
    select_value = -1;
}


int Range_Silder::get_x(int value)
{
    value = static_cast<double>(this->width() - value_edge*2 - margin*2)/(999)*value + value_edge + margin;
    return value;
}
