#include "overview_edit.h"



Overview_edit::Overview_edit(QWidget *parent) :
    QWidget(parent)
{
    margin = 20;
    this->setFixedHeight(100);
    intervals = 100;
    value_edge = 5;
    values = {0,500,999};
    selected_line = 0;
    split_lines = {};
    selected_line = 0;
    mouse3 = false;
    mouse2 = false;
    key_control = false;
    move_index = 0;
    last_move_index = 0;
    setFocusPolicy(Qt::StrongFocus);
}

void Overview_edit::paintEvent(QPaintEvent *event)
{

    if (values.count() < 1){return;}
    this->setFixedWidth((values.count()-1)*intervals + value_edge*2+margin*2) ;
    QPainter painter(this);
    painter.setRenderHint(QPainter::RenderHint::Antialiasing);
    painter.setPen(QColor(47, 54, 60));
    painter.setBrush(QColor(47, 54, 60));
    QPointF topLeft(0,0);
    QRectF rectangle(topLeft, QSizeF(this->width(), this->height()));
    painter.drawRect(rectangle);
    painter.setPen(QColor(47, 54, 60));
    painter.setBrush(QColor(58, 65, 82));
    if (split_lines.isEmpty()){
        QPointF topLeft(margin+value_edge,margin);
        QRectF rectangle(topLeft, QSizeF(this->width()-margin*2, this->height()-margin*2));
        painter.drawRect(rectangle);
    }
    else {
        if (selected_part == split_lines[split_lines.count()-1]){
            QPointF topLeft(value_edge + intervals*selected_part + margin,margin);
            QRectF rectangle(topLeft, QSizeF(this->width()-2*margin-value_edge -intervals*selected_part, this->height()-2*margin));
            painter.drawRect(rectangle);
        }
        else if (selected_part == 0){
            QPointF topLeft(margin+value_edge,margin);
            QRectF rectangle(topLeft, QSizeF(intervals*split_lines[0], this->height()-2*margin));
            painter.drawRect(rectangle);
        }
        else{
            QPointF topLeft(value_edge + intervals*selected_part + margin,margin);
            QRectF rectangle(topLeft, QSizeF(intervals*(split_lines[split_lines.indexOf(selected_part)+1]-selected_part), this->height()-2*margin));
            painter.drawRect(rectangle);
        }        
    }


    for (int i = 0; i < values.count(); ++i){
        int index = i;
        int value = values[i];
        int x = value_edge + intervals*i + margin;
        int y = static_cast<double>(this->height() - value_edge*2 - margin*2)/(-999)*value + this->height() - value_edge - margin;
        if (i){
            if (value == -1){continue;}
            for (index = i;values[index-1] == -1;index = index -1){}
            int last_x = value_edge + intervals*(index-1) + margin;
            int last_y = static_cast<double>(this->height() - value_edge*2 - margin*2)/(-999)*values[index-1]+ this->height() - value_edge - margin;
            QColor color(255, 110, 144);
            painter.setPen(QPen(color, 1));
            painter.drawLine(last_x,last_y,x,y);
            //if (selected_values.indexOf(i) != -1 && selected_values.indexOf(index -1) != -1){
                //painter.setPen(QPen(QColor(136, 0, 255), 4));
                //painter.drawLine(last_x,last_y,x,y);
            //}
        }
    }
    QColor color;
    color.setRgba(qRgba(255, 255, 255, 150));
    painter.setPen(QPen(color, 1));
    painter.drawLine(value_edge+margin,value_edge + margin,this->width() - margin - value_edge,value_edge + margin);
    painter.drawLine(value_edge+margin,this->height()-value_edge - margin,this->width() - margin - value_edge,this->height()-value_edge - margin);
    painter.drawLine(value_edge+margin,this->height()/2,this->width()- margin - value_edge,this->height()/2);
    for (int i = 0; i < values.count(); ++i){
        int value = values[i];
        int x = value_edge + intervals*i + margin;
        QColor color1;
        color1.setRgba(qRgba(255, 255, 255, 150));
        painter.setPen(QPen(color1, 1));
        painter.drawLine(x,value_edge+margin,x,this->height() - margin- value_edge);
        if (split_lines.count()){
            if (split_lines.indexOf(i)!=-1){
                QColor color2;
                color2.setRgba(qRgba(220, 220, 200, 255));
                painter.setPen(QPen(color2, 3));
                painter.drawLine(x,0,x,this->height());
            }
        }

        if ((i == 0 || i == values.count() - 1 || i % 5 == 0) && intervals >= 30){
            painter.setFont(QFont("Microsoft YaHei", 8));
            qint64 totalMilliseconds = i * 100;
            int minutes = (totalMilliseconds % 3600000) / 60000;
            int seconds = (totalMilliseconds % 60000) / 1000;
            int milliseconds = totalMilliseconds % 1000;
            QString text = QString::asprintf("%02d:%02d.%02d", minutes, seconds, milliseconds / 10);
            QRect text_rect = painter.boundingRect(QRect(), Qt::AlignmentFlag::AlignCenter, text);
            text_rect.moveCenter(QPoint(x,this->height()-margin/2));
            painter.setPen(QColor(255, 255, 255));
            painter.drawText(text_rect, Qt::AlignmentFlag::AlignCenter, text);
        }
        if (value == -1){continue;}
    }
    painter.setPen(QPen(QColor(255, 19, 121), 2));
    painter.setBrush(QColor(255, 19, 121));
    int x = value_edge + intervals*selected_line + margin;
    painter.drawLine(x,margin +value_edge-5,x,this->height() - margin- value_edge+5);
    QPolygon triangle1;
    QPolygon triangle2;
    triangle1 << QPoint(x, margin +value_edge-5) << QPoint(x+5, margin +value_edge-10) << QPoint(x-5, margin +value_edge-10);
    triangle2 << QPoint(x, this->height() - margin- value_edge+5) << QPoint(x-5, this->height()  - margin- value_edge+10) << QPoint(x+5, this->height() - margin- value_edge+10);
    painter.drawPolygon(triangle1);
    painter.drawPolygon(triangle2);
}

void Overview_edit::mousePressEvent(QMouseEvent *event)
{
    if (values.isEmpty()){return;}
    if (event->button() == Qt::MouseButton::LeftButton){
        if (split_lines.isEmpty()){
            selected_part = 0;
            emit select_part(0);
            this->update();
            return;
        }
        else if (margin+split_lines[split_lines.count()-1]*intervals<event->position().x()&&event->position().x()< this->width()-margin ){
            selected_part = split_lines[split_lines.count()-1];
            emit select_part(split_lines.indexOf(selected_part)+1);
            this->update();
            return;
        }
        for (int i = 0; i < split_lines.count(); ++i){
            if ( i == 0 && margin < event->position().x() && event->position().x() < margin+split_lines[i]*intervals){
                selected_part = 0;
                emit select_part(0);
                this->update();
                return;
            }
            else if(margin+split_lines[i]*intervals < event->position().x() && event->position().x() < margin+split_lines[i+1]*intervals){
                selected_part = split_lines[i];
                emit select_part(split_lines.indexOf(selected_part)+1);
                this->update();
                return;
            }
        }
    }


    else if(event->button() == Qt::MouseButton::MiddleButton){
        mouse3 = true;
        for (int i = 0; i < values.count(); ++i){
            int x = value_edge + intervals*i + margin;
            if (x - value_edge < event->position().x() && event->position().x() < x + value_edge){
                selected_line = i;
                emit current_line(i);
                this->update();
                return;
            }
        }
        this->update();
    }
    else if(event->button() == Qt::MouseButton::RightButton && !mouse2){
        mouse2 = true;
        for (int i = 0; i < values.count(); ++i){
            int x = value_edge + intervals*i + margin;
            if (x - value_edge < event->position().x() && event->position().x() < x + value_edge){
                if (i == 0 || i == values.count()-1){return;}
                if (split_lines.indexOf(i)== -1){
                    split_lines.append(i);
                    std::sort(split_lines.begin(), split_lines.end());
                    selected_part = i;
                    emit add_part(split_lines.indexOf(i)+1);
                    //emit select_part(split_lines.indexOf(selected_part)+1);
                }
                else{// i 在split_lines内是分割线
                    if (i == selected_part){
                        if (split_lines.indexOf(i) == 0){
                            selected_part = 0;
                            emit del_part(0);
                            emit select_part(0);
                        }
                        else{
                            selected_part = split_lines[split_lines.indexOf(i)-1];
                            emit del_part(split_lines.indexOf(i));
                            emit select_part(split_lines.indexOf(selected_part)+1);
                        }
                    }
                    else{
                        emit del_part(split_lines.indexOf(i));
                    }
                }
                this->update();
                return;
            }
        }
        this->update();
    }
}

void Overview_edit::mouseMoveEvent(QMouseEvent *event)
{
    if (mouse3){
        for (int i = 0; i < values.count(); ++i){
            int x = value_edge + intervals*i + margin;
            if (x - value_edge < event->position().x() && event->position().x() < x + value_edge){
                selected_line = i;
                emit current_line(i);
                this->update();
                return;
            }
        }
    }
}





void Overview_edit::mouseReleaseEvent(QMouseEvent *event)
{
    mouse3 = false;
    mouse2 = false;
    this->update();
}

void Overview_edit::keyPressEvent(QKeyEvent *event)
{

    if (event->keyCombination() == (Qt::KeyboardModifier::ControlModifier|Qt::Key::Key_Left)){
        if (intervals-5 > 5) {
            intervals = intervals - 5;
        }
        else if(intervals-1 > 1){
            intervals = intervals - 1;
        }
        if (intervals <= 100){
            value_edge = static_cast<double>(5-3)/(100-2) * intervals + 3- static_cast<double>(5-3)/(100-2)*2;
        }
        this->update();
    }
    else if (event->keyCombination() == (Qt::KeyboardModifier::ControlModifier|Qt::Key::Key_Right)){
        if (intervals+5 > 200){return;}
        intervals = intervals + 5;
        if (intervals <= 100){
            value_edge = static_cast<double>(5-3)/(100-2) * intervals + 3- static_cast<double>(5-3)/(100-2)*2;
        }
        this->update();
    }
    else if (event->key() == Qt::Key::Key_Control){
        key_control = true;
    }
    else if (event->key() == Qt::Key::Key_Space){
        emit set_play();
    }
    event->accept();
}

void Overview_edit::keyReleaseEvent(QKeyEvent *event)
{
    key_control = false;
}


void Overview_edit::wheelEvent(QWheelEvent *event)
{
    if (!key_control){return;}
    QPoint angleDelta = event->angleDelta();
    if (!angleDelta.isNull()) {
        if (angleDelta.y() > 0) {
            if (intervals+5 > 200){return;}
            intervals = intervals + 5;
        } else {
            if (intervals-5 > 5) {
                intervals = intervals - 5;
            }
            else if(intervals-1 > 1){
                intervals = intervals - 1;
            }
        }
    }
    if (intervals <= 100){
        value_edge = static_cast<double>(5-3)/(100-2) * intervals + 3- static_cast<double>(5-3)/(100-2)*2;
    }
    this->update();
    event->accept();
}




