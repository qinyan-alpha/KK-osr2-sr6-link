#include "scripter_edit.h"




Scripter_edit::Scripter_edit(QWidget *parent) :
    QWidget(parent)
{
    margin = 20;
    this->setFixedHeight(120);
    intervals = 100;
    value_edge = 5;
    values = {0,500,999};
    old_values = values;
    selected_values = {};
    old_selected_values = {};
    copy_values = {};
    copy_values_indexs ={};
    selected_line = 0;
    selected_times = {};
    record_values = {};
    mouse1 = false;
    mouse3 = false;
    mouse2 = false;
    press_point = QPointF(0,0);
    move_point = QPointF(0,0);
    focus = false;
    key_shift =false;
    key_control = false;
    key_alt = false;
    move_index = 0;
    last_move_index = 0;
    movefirst = true;
    rebuild = false;
    rebuild_times = {};
    rebuild_start = QPointF(0,0);
    rebuild_end = QPointF(0,0);
    menubar = new QMenu;
    show_label = new QLabel("no point selected");
    QPalette palette = show_label->palette();
    palette.setColor(QPalette::WindowText, QColor(225, 225, 225));
    show_label->setPalette(palette);
    QFont font("微软雅黑", 10);
    show_label->setFont(font);
    show_label->setAlignment(Qt::AlignCenter);
    palette.setColor(QPalette::Window, Qt::transparent);
    show_label->setPalette(palette);
    show_label->setContentsMargins(0, 5, 0, 5);
    QWidgetAction *labelAction = new QWidgetAction(menubar);
    labelAction->setDefaultWidget(show_label);
    menubar->addAction(labelAction);
    menubar->addSeparator();
    QLineEdit *value_lineEdit = new QLineEdit;
    connect(this, &Scripter_edit::updatevalue_lineEdit, value_lineEdit, &QLineEdit::setText);
    value_lineEdit->setPlaceholderText("set new point value");
    value_lineEdit->setStyleSheet("QLineEdit {\n"
                             "	background-color: rgb(60,67,76);\n"
                             "	padding-left: 25px;\n"
                             "	selection-color: rgb(255, 255, 255);\n"
                             "	selection-background-color: rgb(255, 121, 198);\n"
                             "  font: 10pt \"微软雅黑\";"
                             "  color: rgb(225, 225, 225);"
                             "}\n"
                             "QLineEdit:hover {\n"
                             "	border: 2px solid rgb(60,67,76);\n"
                             "}\n"
                             "QLineEdit:focus {\n"
                             "	border: 2px solid rgb(60,67,76);\n"
                             "}\n");
    QWidgetAction *lineEditAction = new QWidgetAction(menubar);
    lineEditAction->setDefaultWidget(value_lineEdit);
    menubar->addAction(lineEditAction);
    menubar->addSeparator();
    action1 = new QAction("clean all selected");
    action1->setShortcut(QKeySequence("Ctrl+D"));
    action2 = new QAction("delete selected point");
    action2->setShortcut(QKeySequence("Ctrl+Delete"));
    action3 = new QAction("add selected lines point");
    action3->setShortcut(QKeySequence("Ctrl+E"));
    action4 = new QAction("selecte all point");
    action4->setShortcut(QKeySequence("Ctrl+A"));
    action5 = new QAction("selecte selected top points");
    action5->setShortcut(QKeySequence("Ctrl+W"));
    action6 = new QAction("selecte selected down points");
    action6->setShortcut(QKeySequence("Ctrl+S"));
    action7 = new QAction("change selected point values");
    action8 = new QAction("copy selected point values");
    action8->setShortcut(QKeySequence("Ctrl+C"));
    action9 = new QAction("cut selected point values");
    action9->setShortcut(QKeySequence("Ctrl+X"));
    action10 = new QAction("paste selected point values");
    action10->setShortcut(QKeySequence("Ctrl+V"));
    action11 = new QAction("Rebuild the selected times,Click the alt key to start selecting the time period for the rebuild.");
    action12 = new QAction("select intervals points");
    action13 = new QAction("withdraw changes of points");
    action13->setShortcut(QKeySequence("Ctrl+Z"));
    action14 = new QAction("enlarge selected point values");
    action14->setShortcut(QKeySequence("Ctrl+Pgup"));
    action15 = new QAction("decrease selected point values");
    action15->setShortcut(QKeySequence("Ctrl+Pgdown"));
    action16 = new QAction("reverse selected point values");
    action17 = new QAction("select selected midpoints");
    menubar->setStyleSheet("QMenu{"
                        "background:rgb(60,67,76);"
                        "}"
                        "QMenu::item{"
                        "background:rgb(60,67,76);"
                        "font: 10pt \"微软雅黑\";"
                        "padding:3px 30px;"
                        "color: rgb(225, 225, 225);"
                        "text-align: center;"
                        "}"
                        "QMenu::item:hover{"
                        "background:rgb(255, 121, 198);"
                        "color: rgb(225, 255, 255);"
                        "}"
                        "QMenu::item:selected{"
                        "background:rgb(255, 121, 198);"
                        "color: rgb(225, 255, 255);"
                        "}" );
    connect(action1,&QAction::triggered,this,[=]{
        selected_values.clear();
        this->update();
    });
    connect(action2,&QAction::triggered,this,[=]{
        old_values = values;
        for (int value:selected_values){
            if (value == 0 || value == values.count() - 1){continue;}
            values[value] = -1;
        }
        if (old_values != values){record_values.append(old_values);}
        selected_values.clear();
        this->update();
    });
    connect(action3,&QAction::triggered,this,[=]{
        old_values = values;
        for (int value:selected_times){      
            if (values[value] == -1){
                values[value] = 500;
            }
        }
        if (old_values != values){record_values.append(old_values);}
        this->update();
    });
    connect(action4,&QAction::triggered,this,[=]{
        selected_values.clear();
        selected_times.clear();
        for (int i = 0; i < values.count(); ++i){
            if (values[i] != -1){selected_values.append(i);}
            selected_times.append(i);
        }
        this->update();
    });
    connect(action5,&QAction::triggered,this,[=]{
        if (selected_values.count() < 1){return;}
        std::sort(selected_values.begin(), selected_values.end());
        for (int i = 0; i < values.count(); ++i){
            if (values[i] == -1 && selected_values.indexOf(i) != -1){
                selected_values.removeAt(selected_values.indexOf(i));
            }
        }
        QList<int> old_selected_values = selected_values;
        selected_values.clear();
        for (int index = 0; index < old_selected_values.count(); index++) {
            if (index == 0) {
                if (old_selected_values.count() > 1 &&
                    values[old_selected_values[0]] > values[old_selected_values[1]]) {
                    selected_values.append(old_selected_values[0]);
                }
            } else if (index == old_selected_values.count() - 1) {
                if (values[old_selected_values[index]] > values[old_selected_values[index - 1]]) {
                    selected_values.append(old_selected_values[index]);
                }
            } else {
                if (values[old_selected_values[index]] >= values[old_selected_values[index - 1]] &&
                    values[old_selected_values[index]] > values[old_selected_values[index + 1]]) {
                    selected_values.append(old_selected_values[index]);
                }
                else if (values[old_selected_values[index]] > values[old_selected_values[index - 1]] &&
                    values[old_selected_values[index]] >= values[old_selected_values[index + 1]]){
                    selected_values.append(old_selected_values[index]);
                }
            }
        }
        this->update();
    });
    connect(action6,&QAction::triggered,this,[=]{
        if (selected_values.count() < 1){return;}
        std::sort(selected_values.begin(), selected_values.end());
        for (int i = 0; i < values.count(); ++i){
            if (values[i] == -1 && selected_values.indexOf(i) != -1){
                selected_values.removeAt(selected_values.indexOf(i));
            }
        }
        QList<int> old_selected_values = selected_values;
        selected_values.clear();
        for (int index = 0; index < old_selected_values.count(); index++) {
            if (index == 0) {
                if (old_selected_values.count() > 1 &&
                    values[old_selected_values[0]] < values[old_selected_values[1]]) {
                    selected_values.append(old_selected_values[0]);
                }
            } else if (index == old_selected_values.count() - 1) {
                if (values[old_selected_values[index]] < values[old_selected_values[index - 1]]) {
                    selected_values.append(old_selected_values[index]);
                }
            } else {
                if (values[old_selected_values[index]] <= values[old_selected_values[index - 1]] &&
                    values[old_selected_values[index]] < values[old_selected_values[index + 1]]) {
                    selected_values.append(old_selected_values[index]);
                }
                else if (values[old_selected_values[index]] < values[old_selected_values[index - 1]] &&
                               values[old_selected_values[index]] <= values[old_selected_values[index + 1]]){
                    selected_values.append(old_selected_values[index]);
                }
            }
        }
        this->update();
    });
    connect(action7,&QAction::triggered,this,[=]{
        old_values = values;
        if (value_lineEdit->text() == ""){return;}
        int value = value_lineEdit->text().toInt();
        if (value < 0 || value > 999){return;}
        for (int index : selected_values){values[index] = value;}
        if (old_values != values){record_values.append(old_values);}
        this->update();
    });
    connect(action8,&QAction::triggered,this,[=]{
        if (selected_values.count() < 1){return;}
        for (int i = 0; i < values.count(); ++i){
            if (values[i] == -1 && selected_values.indexOf(i) != -1){
                selected_values.removeAt(selected_values.indexOf(i));
            }
        }
        std::sort(selected_values.begin(), selected_values.end());
        copy_values.clear();
        copy_values_indexs.clear();
        for (int index : selected_values){
            copy_values_indexs.append(index);
        }
        for (int i = copy_values_indexs[0]; i <= copy_values_indexs[copy_values_indexs.count()-1]; ++i){
            if (copy_values_indexs.indexOf(i) == -1){
                copy_values_indexs.append(i);
                std::sort(copy_values_indexs.begin(), copy_values_indexs.end());
            }
            copy_values.append(values[i]);
        }
        emit get_copy_values(copy_values,copy_values_indexs);
    });
    connect(action9,&QAction::triggered,this,[=]{
        if (selected_values.count() < 1){return;}
        for (int i = 0; i < values.count(); ++i){
            if (values[i] == -1 && selected_values.indexOf(i) != -1){
                selected_values.removeAt(selected_values.indexOf(i));
            }
        }
        std::sort(selected_values.begin(), selected_values.end());
        copy_values.clear();
        copy_values_indexs.clear();
        for (int index : selected_values){
            copy_values_indexs.append(index);
        }
        for (int i = copy_values_indexs[0]; i <= copy_values_indexs[copy_values_indexs.count()-1]; ++i){
            if (copy_values_indexs.indexOf(i) == -1){
                copy_values_indexs.append(i);
                std::sort(copy_values_indexs.begin(), copy_values_indexs.end());
            }
            copy_values.append(values[i]);
        }
        emit get_copy_values(copy_values,copy_values_indexs);
        for (int value:selected_values){
            if (value == 0 || value == values.count()-1){continue;}
            values[value] = -1;
        }
        record_values.append(old_values);
        this->update();
    });
    connect(action10,&QAction::triggered,this,[=]{
        old_values = values;
        int index = selected_line;
        for (int i = 0; i < copy_values.count(); ++i){
            if (index+copy_values_indexs[0] - copy_values_indexs[0] < values.count()-1 && index+copy_values_indexs[i] - copy_values_indexs[0] >= 0){
                values[index+copy_values_indexs[i] - copy_values_indexs[0]] = copy_values[i];
            }
            this->update();
        }
        if (old_values != values){record_values.append(old_values);}
    });
    connect(action11,&QAction::triggered,this,[=]{
        emit rebuildtimes(rebuild_times);
        rebuild = false;
        rebuild_times.clear();
        emit current_rebuildtimes(rebuild_times);
    });
    connect(action12,&QAction::triggered,this,[=]{
        if (selected_values.count() < 1){return;}
        std::sort(selected_values.begin(), selected_values.end());
        for (int i = 0; i < values.count(); ++i){
            if (values[i] == -1 && selected_values.indexOf(i) != -1){
                selected_values.removeAt(selected_values.indexOf(i));
            }
        }
        QList<int> new_selected_values;
        new_selected_values.append(selected_values.first());
        for (int i = 0; i < selected_values.count() - 1; i += 2) {
            if (i == 0 || i == selected_values.count()-1){continue;}
            new_selected_values.append(selected_values[i]);
        }
        selected_values = new_selected_values;
        this->update();
    });
    connect(action13,&QAction::triggered,this,[=]{
        if (record_values.count() < 1){return;}
        values = record_values[record_values.count()-1];
        record_values.removeAt(record_values.count()-1);
        this->update();
    });
    connect(action14,&QAction::triggered,this,[=]{
        if (selected_values.count() < 1){return;}
        for (int i = 0; i < values.count(); ++i){
            if (values[i] == -1 && selected_values.indexOf(i) != -1){
                selected_values.removeAt(selected_values.indexOf(i));
            }
        }
        std::sort(selected_values.begin(), selected_values.end());
        old_values = values;
        QList<int> now_values = {};
        for (int index : selected_values){
            now_values.append(values[index]);
        }
        int min = 999;
        int max = 0;
        for (float value : now_values) {
            if (value > max) {
                max = value;
            }
        }
        for (float value : now_values) {
            if (value < min) {
                min = value;
            }
        }
        int average = (max+min)/2;
        for (int i = 0; i < now_values.count(); ++i){
            int difference = now_values[i] - average;
            int amplifiedDifference = difference * 1.1;
            int newValue = average + amplifiedDifference;
            now_values[i] = newValue;
            if (now_values[i] > 999){now_values[i] = 999;}
            else if (now_values[i] < 0){now_values[i] = 0;}
        }
        for (int i = 0; i < selected_values.count(); ++i){
            values[selected_values[i]] = now_values[i];
        }
        this->update();
        if (old_values != values){record_values.append(old_values);}
    });
    connect(action15,&QAction::triggered,this,[=]{
        if (selected_values.count() < 1){return;}
        for (int i = 0; i < values.count(); ++i){
            if (values[i] == -1 && selected_values.indexOf(i) != -1){
                selected_values.removeAt(selected_values.indexOf(i));
            }
        }
        std::sort(selected_values.begin(), selected_values.end());
        old_values = values;
        QList<int> now_values = {};
        for (int index : selected_values){
            now_values.append(values[index]);
        }
        int min = 999;
        int max = 0;
        for (float value : now_values) {
            if (value > max) {
                max = value;
            }
        }
        for (float value : now_values) {
            if (value < min) {
                min = value;
            }
        }
        int average = (max+min)/2;
        for (int i = 0; i < now_values.count(); ++i){
            int difference = now_values[i] - average;
            int amplifiedDifference = difference * 0.9;
            int newValue = average + amplifiedDifference;
            now_values[i] = newValue;
            if (now_values[i] > 999){now_values[i] = 999;}
            else if (now_values[i] < 0){now_values[i] = 0;}
        }
        for (int i = 0; i < selected_values.count(); ++i){
            values[selected_values[i]] = now_values[i];
        }
        this->update();
        if (old_values != values){record_values.append(old_values);}
    });
    connect(action16,&QAction::triggered,this,[=]{
        if (selected_values.count() < 1){return;}
        for (int i = 0; i < values.count(); ++i){
            if (values[i] == -1 && selected_values.indexOf(i) != -1){
                selected_values.removeAt(selected_values.indexOf(i));
            }
        }
        std::sort(selected_values.begin(), selected_values.end());
        old_values = values;
        QList<int> now_values = {};
        for (int index : selected_values){
            now_values.append(values[index]);
        }
        for (int i = 0; i < now_values.count(); ++i){
            int difference = 500 - now_values[i];
            int newValue = 500 + difference;
            now_values[i] = newValue;
            if (now_values[i] > 999){now_values[i] = 999;}
            else if (now_values[i] < 0){now_values[i] = 0;}
        }
        for (int i = 0; i < selected_values.count(); ++i){
            values[selected_values[i]] = now_values[i];
        }
        this->update();
        if (old_values != values){record_values.append(old_values);}
    });
    connect(action17,&QAction::triggered,this,[=]{
        if (selected_values.count() < 1){return;}
        std::sort(selected_values.begin(), selected_values.end());
        for (int i = 0; i < values.count(); ++i){
            if (values[i] == -1 && selected_values.indexOf(i) != -1){
                selected_values.removeAt(selected_values.indexOf(i));
            }
        }
        QList<int> old_selected_values = selected_values;
        QList<int> not_mid_values = {};
        selected_values.clear();
        for (int index = 0; index < old_selected_values.count(); index++) {
            if (index == 0) {
                    not_mid_values.append(old_selected_values[0]);
            } else if (index == old_selected_values.count() - 1) {
                    not_mid_values.append(old_selected_values[index]);
            } else {
                if (values[old_selected_values[index]] >= values[old_selected_values[index - 1]] &&
                    values[old_selected_values[index]] > values[old_selected_values[index + 1]]) {
                    not_mid_values.append(old_selected_values[index]);
                }
                else if (values[old_selected_values[index]] > values[old_selected_values[index - 1]] &&
                         values[old_selected_values[index]] >= values[old_selected_values[index + 1]]){
                    not_mid_values.append(old_selected_values[index]);
                }
                else if (values[old_selected_values[index]] <= values[old_selected_values[index - 1]] &&
                    values[old_selected_values[index]] < values[old_selected_values[index + 1]]) {
                    not_mid_values.append(old_selected_values[index]);
                }
                else if (values[old_selected_values[index]] < values[old_selected_values[index - 1]] &&
                         values[old_selected_values[index]] <= values[old_selected_values[index + 1]]){
                    not_mid_values.append(old_selected_values[index]);
                }
            }
        }
        QList<int> result;
        for (int value : old_selected_values) {
            if (!not_mid_values.contains(value)) {
                result.append(value);
            }
        }
        selected_values = result;
        this->update();
    });
    menubar->addAction(action1);
    menubar->addAction(action2);
    menubar->addAction(action3);
    menubar->addAction(action4);
    menubar->addAction(action5);
    menubar->addAction(action6);
    menubar->addAction(action7);
    menubar->addAction(action8);
    menubar->addAction(action9);
    menubar->addAction(action10);
    menubar->addAction(action11);
    menubar->addAction(action12);
    menubar->addAction(action13);
    menubar->addAction(action14);
    menubar->addAction(action15);
    menubar->addAction(action16);
    menubar->addAction(action17);
}

void Scripter_edit::paintEvent(QPaintEvent *event)
{

    if (values.count() < 1){return;}
    this->setFixedWidth((values.count()-1)*intervals + value_edge*2+margin*2) ;
    QPainter painter(this);
    painter.setRenderHint(QPainter::RenderHint::Antialiasing);
    if (focus){
        painter.setPen(QColor(47, 54, 60));
        painter.setBrush(QColor(58, 65, 82));
    }
    else{
        painter.setPen(QColor(47, 54, 60));
        painter.setBrush(QColor(47, 54, 60));
    }
    QPointF topLeft(0,0);
    QRectF rectangle(topLeft, QSizeF(this->width(), this->height()));
    painter.drawRect(rectangle);
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
            if (selected_values.indexOf(i) != -1 && selected_values.indexOf(index -1) != -1){
                painter.setPen(QPen(QColor(136, 0, 255), 4));
                painter.drawLine(last_x,last_y,x,y);
            }
        }
    }
    QColor color;
    color.setRgba(qRgba(255, 255, 255, 150));
    painter.setPen(QPen(color, 1));
    painter.drawLine(value_edge+margin,value_edge + margin,this->width() - margin - value_edge,value_edge + margin);
    painter.drawLine(value_edge+margin,this->height()-value_edge - margin,this->width() - margin - value_edge,this->height()-value_edge - margin);
    painter.drawLine(value_edge+margin,this->height()/2,this->width()- margin - value_edge,this->height()/2);
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
    for (int i = 0; i < values.count(); ++i){
        int value = values[i];    
        int x = value_edge + intervals*i + margin;
        int y = static_cast<double>(this->height() - value_edge*2 - margin*2)/(-999)*value + this->height() - value_edge - margin;
        QColor color1;
        if (selected_times.indexOf(i) != -1){
            color1.setRgb(255, 255, 255);
        }
        else{
            color1.setRgba(qRgba(255, 255, 255, 150));
        }
        if (rebuild_times.indexOf(i) != -1){
            color1.setRgb(105, 105, 105);
        }
        painter.setPen(QPen(color1, 1));
        painter.drawLine(x,value_edge+margin,x,this->height() - margin- value_edge);
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
        if (selected_values.indexOf(i) != -1){
            painter.setPen(QColor(255, 121, 198));
            painter.setBrush(QColor(255, 121, 198));
        }
        else{
            painter.setPen(QColor(189, 147, 249));
            painter.setBrush(QColor(189, 147, 249));
        }
        painter.drawEllipse(x - value_edge, y - value_edge, value_edge*2, value_edge*2);
    }
    if (mouse1 || mouse2){
        QColor color;
        color.setRgba(qRgba(255, 121, 198, 10));
        painter.setPen(QColor(255, 121, 198));
        painter.setBrush(color);
        if (press_point.x() > move_point.x() && press_point.y() > move_point.y()) {
            QPointF topLeft = move_point;
            int width = press_point.x() - move_point.x();
            int height = press_point.y() - move_point.y();
            QRectF rectangle(topLeft, QSizeF(width, height));
            painter.drawRect(rectangle);
        }
        else if (press_point.x() > move_point.x() && press_point.y() < move_point.y()) {
            QPointF topLeft(move_point.x(),press_point.y());
            int width = press_point.x() - move_point.x();
            int height = move_point.y() - press_point.x();
            QRectF rectangle(topLeft, QSizeF(width, height));
            painter.drawRect(rectangle);
        }
        else if (press_point.x() < move_point.x() && press_point.y() < move_point.y()) {
            QPointF topLeft = press_point;
            int width = move_point.x() - press_point.x();
            int height = move_point.y() - press_point.y();
            QRectF rectangle(topLeft, QSizeF(width, height));
            painter.drawRect(rectangle);
        }
        else if (press_point.x() < move_point.x() && press_point.y() > move_point.y()) {
            QPointF topLeft(press_point.x(),move_point.y());
            int width = move_point.x() - press_point.x();
            int height = press_point.y() - move_point.y();
            QRectF rectangle(topLeft, QSizeF(width, height));
            painter.drawRect(rectangle);
        }
    } 
    if (selected_values.count() == 1){show_label->setText("single point selected");}
    else if(selected_values.count() == 0){show_label->setText("no point selected");}
    else if(selected_values.count() > 1){show_label->setText("multiple points");}
}

void Scripter_edit::mousePressEvent(QMouseEvent *event)
{
    emit updatevalue_lineEdit("");
    setFocus();
    if (rebuild and event->button() != Qt::MouseButton::RightButton and event->button()!= Qt::MouseButton::MiddleButton){
        return;}
    if (event->button() == Qt::MouseButton::LeftButton and !key_control and !key_shift &&!key_alt){
        mouse1 = true;
        press_point = move_point = event->position();
        selected_values.clear();
        selected_times.clear();
        for (int i = 0; i < values.count(); ++i){        
            int x = value_edge + intervals*i + margin;
            int value = values[i];
            int y = static_cast<double>(this->height() - value_edge*2 - margin*2)/(-999)*value + this->height() - value_edge - margin;
            if ( x - value_edge < press_point.x() && press_point.x() < x + value_edge && y - value_edge < press_point.y() && press_point.y()< y + value_edge && selected_values.indexOf(i) == -1 && y != -1){
                selected_values.append(i);      
                this->update();
            }
            if (x - value_edge < press_point.x() && press_point.x() < x + value_edge && selected_times.indexOf(i) == -1 ){
                selected_times.append(i);
                this->update();
            }
        }
        old_values = values;
    }
    else if(event->button() == Qt::MouseButton::LeftButton and key_control and !key_shift &&!key_alt){
        mouse1 = true;
        press_point = move_point = event->position();
        for (int i = 0; i < values.count(); ++i){
            int x = value_edge + intervals*i + margin;
            int value = values[i];
            int y = static_cast<double>(this->height() - value_edge*2 - margin*2)/(-999)*value + this->height() - value_edge - margin;
            if ( x - value_edge < press_point.x() && press_point.x() < x + value_edge && y - value_edge < press_point.y() && press_point.y()< y + value_edge && selected_values.indexOf(i) == -1 && y != -1){
                selected_values.append(i);
                this->update();
            }
            else if (x - value_edge < press_point.x() && press_point.x() < x + value_edge && y - value_edge < press_point.y() && press_point.y()< y + value_edge && selected_values.indexOf(i) != -1 && y != -1){
                selected_values.removeAt(selected_values.indexOf(i));
                this->update();
            }
            if (x - value_edge < press_point.x() && press_point.x() < x + value_edge && selected_times.indexOf(i) == -1){
                selected_times.append(i);
                this->update();
            }
            else if (x - value_edge < press_point.x() && press_point.x() < x + value_edge && selected_times.indexOf(i) != -1){
                selected_times.removeAt(selected_times.indexOf(i));
                this->update();
            }
        }
    }
    else if(event->button() == Qt::MouseButton::LeftButton and key_shift and !key_control &&!key_alt){
        mouse1 = true;
        press_point = move_point = event->position();
        old_values = values;
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
    else if(event->button() == Qt::MouseButton::RightButton and !key_control &&!key_alt and !key_shift){
        menubar->popup(event->globalPosition().toPoint());
    }
    else if(event->button() == Qt::MouseButton::RightButton and key_shift and !key_control && !key_alt){
        mouse2 = true;
        press_point = move_point = event->position();
        old_values = values;
        old_selected_values = selected_values;
    }
    else if(event->button() == Qt::MouseButton::RightButton and key_control &&!key_alt and !key_shift){
        mouse2 = true;
        press_point = move_point = event->position();
        for (int i = 0; i < values.count(); ++i){
            int x = value_edge + intervals*i + margin;

            if (x - value_edge < event->position().x() && event->position().x() < x + value_edge){
                if (values[i] == -1){
                    int value = (event->position().y() -this->height() + value_edge + margin)/(static_cast<double>(this->height() - value_edge*2 - margin*2) / (-999));
                    if (value >= 0 && value <= 999){values[i] = value;}
                }
                else{
                    int y = static_cast<double>(this->height() - value_edge*2 - margin*2)/(-999)*values[i] + this->height() - value_edge - margin;
                    if (y - value_edge < event->position().y() && event->position().y() < y + value_edge){
                        values[i] = -1;
                    }
                }
            }
        }
    }
}

void Scripter_edit::mouseMoveEvent(QMouseEvent *event)
{
    if (rebuild){
        rebuild_end = event->position();
        rebuild_times.clear();
        if (rebuild_end.x()>rebuild_start.x() && rebuild_end.y()>rebuild_start.y()){
            for (int i = 0; i < values.count(); ++i){
                int x = value_edge + intervals*i + margin;
                if (rebuild_start.x()< x && x < rebuild_end.x() && rebuild_times.indexOf(i) == -1){
                    rebuild_times.append(i);
                }
            }
        }
        else if (rebuild_end.x()>rebuild_start.x() && rebuild_end.y()<rebuild_start.y()){
            for (int i = 0; i < values.count(); ++i){
                int x = value_edge + intervals*i + margin;
                if (rebuild_start.x()< x && x < rebuild_end.x() && rebuild_times.indexOf(i) == -1){
                    rebuild_times.append(i);
                }
            }
        }
        else if (rebuild_end.x()<rebuild_start.x() && rebuild_end.y()<rebuild_start.y()){
            for (int i = 0; i < values.count(); ++i){
                int x = value_edge + intervals*i + margin;
                if (rebuild_start.x()> x && x > rebuild_end.x() && rebuild_times.indexOf(i) == -1){
                    rebuild_times.append(i);
                }
            }
        }
        else if (rebuild_end.x()<rebuild_start.x() && rebuild_end.y()>rebuild_start.y()){
            for (int i = 0; i < values.count(); ++i){
                int x = value_edge + intervals*i + margin;
                if (rebuild_start.x()> x && x > rebuild_end.x() && rebuild_times.indexOf(i) == -1){
                    rebuild_times.append(i);
                }
            }
        }
        emit current_rebuildtimes(rebuild_times);
        return;
    }
    if (mouse1 && !key_shift && !key_control &&!key_alt){
        move_point = event->position();
        selected_values.clear();
        selected_times.clear();
        if (move_point.x()>press_point.x() && move_point.y()>press_point.y()){
            for (int i = 0; i < values.count(); ++i){
                int x = value_edge + intervals*i + margin;
                int value = values[i];
                int y = static_cast<double>(this->height() - value_edge*2 - margin*2)/(-999)*value + this->height() - value_edge - margin;
                if (press_point.x()< x && x < move_point.x() && press_point.y()< y && y < move_point.y() && selected_values.indexOf(i) == -1 && y != -1){
                    selected_values.append(i);
                }
                if (press_point.x()< x && x < move_point.x() && selected_times.indexOf(i) == -1){
                    selected_times.append(i);
                }
            }
        }
        else if (move_point.x()>press_point.x() && move_point.y()<press_point.y()){
            for (int i = 0; i < values.count(); ++i){
                int x = value_edge + intervals*i + margin;
                int value = values[i];
                int y = static_cast<double>(this->height() - value_edge*2 - margin*2)/(-999)*value + this->height() - value_edge - margin;
                if (press_point.x()< x && x < move_point.x() && press_point.y()> y && y > move_point.y() && selected_values.indexOf(i) == -1 && y != -1){
                    selected_values.append(i);
                }
                if (press_point.x()< x && x < move_point.x() && selected_times.indexOf(i) == -1){
                    selected_times.append(i);
                }
            }
        }
        else if (move_point.x()<press_point.x() && move_point.y()<press_point.y()){
            for (int i = 0; i < values.count(); ++i){
                int x = value_edge + intervals*i + margin;
                int value = values[i];
                int y = static_cast<double>(this->height() - value_edge*2 - margin*2)/(-999)*value + this->height() - value_edge - margin;
                if (press_point.x()> x && x > move_point.x() && press_point.y()> y && y > move_point.y() && selected_values.indexOf(i) == -1 && y != -1){
                    selected_values.append(i);
                }
                if (press_point.x()> x && x > move_point.x() && selected_times.indexOf(i) == -1){
                    selected_times.append(i);
                }
            }
        }
        else if (move_point.x()<press_point.x() && move_point.y()>press_point.y()){
            for (int i = 0; i < values.count(); ++i){
                int x = value_edge + intervals*i + margin;
                int value = values[i];
                int y = static_cast<double>(this->height() - value_edge*2 - margin*2)/(-999)*value + this->height() - value_edge - margin;
                if (press_point.x()> x && x > move_point.x() && press_point.y()< y && y < move_point.y() && selected_values.indexOf(i) == -1 && y != -1){
                    selected_values.append(i);
                }
                if (press_point.x()> x && x > move_point.x() && selected_times.indexOf(i) == -1){
                    selected_times.append(i);
                }
            }
        }
        this->update();
    }
    else if (mouse1 && key_shift && !key_alt && !key_control){
        int movepos = event->position().y()-press_point.y();
        for (int i = 0; i < selected_values.count(); ++i){
            if (values[selected_values[i]] == -1){;continue;}
            int value = old_values[selected_values[i]];
            int addvalue = (movepos)/(static_cast<double>(this->height() - value_edge*2 - margin*2) / (-999));
            if (value + addvalue > 999 || value + addvalue < 0) {continue;}
            values[selected_values[i]] = value + addvalue;
        }
        this->update();
    }
    else if (mouse1 && key_control && !key_shift && !key_alt){
        move_point = event->position();
        if (move_point.x()>press_point.x() && move_point.y()>press_point.y()){
            for (int i = 0; i < values.count(); ++i){
                int x = value_edge + intervals*i + margin;
                int value = values[i];
                int y = static_cast<double>(this->height() - value_edge*2 - margin*2)/(-999)*value + this->height() - value_edge - margin;
                if (press_point.x()< x && x < move_point.x() && press_point.y()< y && y < move_point.y() && selected_values.indexOf(i) == -1 && y != -1){
                    selected_values.append(i);
                }
                if (press_point.x()< x && x < move_point.x() && selected_times.indexOf(i) == -1){
                    selected_times.append(i);
                }
            }
        }
        else if (move_point.x()>press_point.x() && move_point.y()<press_point.y()){
            for (int i = 0; i < values.count(); ++i){
                int x = value_edge + intervals*i + margin;
                int value = values[i];
                int y = static_cast<double>(this->height() - value_edge*2 - margin*2)/(-999)*value + this->height() - value_edge - margin;
                if (press_point.x()< x && x < move_point.x() && press_point.y()> y && y > move_point.y() && selected_values.indexOf(i) == -1 && y != -1){
                    selected_values.append(i);
                }
                if (press_point.x()< x && x < move_point.x() && selected_times.indexOf(i) == -1){
                    selected_times.append(i);
                }
            }
        }
        else if (move_point.x()<press_point.x() && move_point.y()<press_point.y()){
            for (int i = 0; i < values.count(); ++i){
                int x = value_edge + intervals*i + margin;
                int value = values[i];
                int y = static_cast<double>(this->height() - value_edge*2 - margin*2)/(-999)*value + this->height() - value_edge - margin;
                if (press_point.x()> x && x > move_point.x() && press_point.y()> y && y > move_point.y() && selected_values.indexOf(i) == -1 && y != -1){
                    selected_values.append(i);
                }
                if (press_point.x()> x && x > move_point.x() && selected_times.indexOf(i) == -1){
                    selected_times.append(i);
                }
            }
        }
        else if (move_point.x()<press_point.x() && move_point.y()>press_point.y()){
            for (int i = 0; i < values.count(); ++i){
                int x = value_edge + intervals*i + margin;
                int value = values[i];
                int y = static_cast<double>(this->height() - value_edge*2 - margin*2)/(-999)*value + this->height() - value_edge - margin;
                if (press_point.x()> x && x > move_point.x() && press_point.y()< y && y < move_point.y() && selected_values.indexOf(i) == -1 && y != -1){
                    selected_values.append(i);
                }
                if (press_point.x()> x && x > move_point.x() && selected_times.indexOf(i) == -1){
                    selected_times.append(i);
                }
            }
        }
        this->update();   
    }
    else if (mouse2 && !key_control && key_shift && !key_alt){
        for (int i = 0; i < values.count(); ++i){
            int x = value_edge + intervals*i + margin;
            if (x - value_edge < event->position().x() && event->position().x() < x + value_edge){
                move_index = (event->position().x()-press_point.x())/intervals;
                if (move_index == 0 || last_move_index == move_index){return;}
                last_move_index = move_index;
                QList<int> now_selected_values = {};
                for (int i = 0; i < old_selected_values.count(); ++i){
                    int new_index = old_selected_values[i] + move_index;
                    if (new_index <= 0){return;}
                    else if (new_index >= values.count()-1){return;}
                    now_selected_values.append(new_index);
                    values[new_index] = old_values[old_selected_values[i]];
                    values[selected_values[i]] = -1;
                }
                QSet<int> uniqueSet = QSet<int>(now_selected_values.begin(), now_selected_values.end());
                now_selected_values = QList<int>(uniqueSet.begin(), uniqueSet.end());
                selected_values = now_selected_values;
                this->update();
                return;
            }
        }
    }
    else if (mouse2 && key_control && !key_shift && !key_alt){
        move_point = event->position();
        if (move_point.x()>press_point.x() && move_point.y()>press_point.y()){
            for (int i = 0; i < values.count(); ++i){
                int x = value_edge + intervals*i + margin;
                int value = values[i];
                int y = static_cast<double>(this->height() - value_edge*2 - margin*2)/(-999)*value + this->height() - value_edge - margin;
                if (press_point.x()< x && x < move_point.x() && press_point.y()< y && y < move_point.y() && selected_values.indexOf(i) != -1 && y != -1){
                    selected_values.removeAt(selected_values.indexOf(i));
                }
                if (press_point.x()< x && x < move_point.x() && selected_times.indexOf(i) != -1){
                    selected_times.removeAt(selected_times.indexOf(i));
                }
            }
        }
        else if (move_point.x()>press_point.x() && move_point.y()<press_point.y()){
            for (int i = 0; i < values.count(); ++i){
                int x = value_edge + intervals*i + margin;
                int value = values[i];
                int y = static_cast<double>(this->height() - value_edge*2 - margin*2)/(-999)*value + this->height() - value_edge - margin;
                if (press_point.x()< x && x < move_point.x() && press_point.y()> y && y > move_point.y() && selected_values.indexOf(i) != -1 && y != -1){
                    selected_values.removeAt(selected_values.indexOf(i));
                }
                if (press_point.x()< x && x < move_point.x() && selected_times.indexOf(i) == -1){
                    selected_times.removeAt(selected_times.indexOf(i));
                }
            }
        }
        else if (move_point.x()<press_point.x() && move_point.y()<press_point.y()){
            for (int i = 0; i < values.count(); ++i){
                int x = value_edge + intervals*i + margin;
                int value = values[i];
                int y = static_cast<double>(this->height() - value_edge*2 - margin*2)/(-999)*value + this->height() - value_edge - margin;
                if (press_point.x()> x && x > move_point.x() && press_point.y()> y && y > move_point.y() && selected_values.indexOf(i) != -1 && y != -1){
                    selected_values.removeAt(selected_values.indexOf(i));
                }
                if (press_point.x()> x && x > move_point.x() && selected_times.indexOf(i) != -1){
                    selected_times.removeAt(selected_times.indexOf(i));
                }
            }
        }
        else if (move_point.x()<press_point.x() && move_point.y()>press_point.y()){
            for (int i = 0; i < values.count(); ++i){
                int x = value_edge + intervals*i + margin;
                int value = values[i];
                int y = static_cast<double>(this->height() - value_edge*2 - margin*2)/(-999)*value + this->height() - value_edge - margin;
                if (press_point.x()> x && x > move_point.x() && press_point.y()< y && y < move_point.y() && selected_values.indexOf(i) != -1 && y != -1){
                    selected_values.removeAt(selected_values.indexOf(i));
                }
                if (press_point.x()> x && x > move_point.x() && selected_times.indexOf(i) != -1){
                    selected_times.removeAt(selected_times.indexOf(i));
                }
            }
        }
        this->update();
    }
    else if (mouse3){
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





void Scripter_edit::mouseReleaseEvent(QMouseEvent *event)
{
press_point = move_point = event->position();
    if (mouse1 && key_shift && old_values != values){record_values.append(old_values);}
mouse1 = false;
mouse3 = false;
mouse2 = false;
this->update();
}

void Scripter_edit::keyPressEvent(QKeyEvent *event)
{
    if (event->keyCombination() == (Qt::KeyboardModifier::ShiftModifier|Qt::Key::Key_Up)){
        if (movefirst){movefirst = false;old_values = values;}
        for (int i = 0; i < selected_values.count(); ++i){
            if (values[selected_values[i]] + 10 > 999){continue;}
            values[selected_values[i]] = values[selected_values[i]] + 10;
        }
        this->update();
    }
    else if (event->keyCombination() == (Qt::KeyboardModifier::ShiftModifier|Qt::Key::Key_Left)){
        if (movefirst){movefirst = false;old_values = values;}
        move_index = -1;
        last_move_index = move_index;
        QList<int> now_selected_values = {};
        for (int i = 0; i < selected_values.count(); ++i){
            int new_index = selected_values[i] + move_index;
            if (new_index <= 0){return;}
            else if (new_index >= values.count()-1){return;}
            now_selected_values.append(new_index);
            values[new_index] = values[selected_values[i]];
            values[selected_values[i]] = -1;
        }
        old_values = values;
        QSet<int> uniqueSet = QSet<int>(now_selected_values.begin(), now_selected_values.end());
        now_selected_values = QList<int>(uniqueSet.begin(), uniqueSet.end());
        selected_values = now_selected_values;
        this->update();
        return;
    }
    else if (event->keyCombination() == (Qt::KeyboardModifier::ShiftModifier|Qt::Key::Key_Right)){
        if (movefirst){movefirst = false;old_values = values;}
        move_index = 1;
        last_move_index = move_index;
        QList<int> now_selected_values = {};
        for (int i = 0; i < selected_values.count(); ++i){
            int new_index = selected_values[i] + move_index;
            if (new_index <= 0){return;}
            else if (new_index >= values.count()-1){return;}
            now_selected_values.append(new_index);
            values[new_index] = values[selected_values[i]];
            values[selected_values[i]] = -1;
        }
        QSet<int> uniqueSet = QSet<int>(now_selected_values.begin(), now_selected_values.end());
        now_selected_values = QList<int>(uniqueSet.begin(), uniqueSet.end());
        selected_values = now_selected_values;
        this->update();
        return;
    }
    else if (event->keyCombination() == (Qt::KeyboardModifier::ShiftModifier|Qt::Key::Key_Down)){
        if (movefirst){movefirst = false;old_values = values;}
        for (int i = 0; i < selected_values.count(); ++i){
            if (values[selected_values[i]] - 10 < 0){continue;}
            values[selected_values[i]] = values[selected_values[i]] - 10;
        }
        this->update();
    }
    else if (event->keyCombination() == (Qt::KeyboardModifier::ControlModifier|Qt::Key::Key_Left)){
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
    else if (event->keyCombination() == (Qt::KeyboardModifier::ControlModifier|Qt::Key::Key_A)){
        selected_values.clear();
        selected_times.clear();
        for (int i = 0; i < values.count(); ++i){
            if (values[i] != -1){selected_values.append(i);}
            selected_times.append(i);
        }
        this->update();
    }
    else if (event->keyCombination() == (Qt::KeyboardModifier::ControlModifier|Qt::Key::Key_D)){
        selected_values.clear();
        this->update();
    }
    else if (event->keyCombination() == (Qt::KeyboardModifier::ControlModifier|Qt::Key::Key_Delete)){
        old_values = values;
        for (int value:selected_values){
            if (value == 0 || value == values.count() - 1){continue;}
            values[value] = -1;
        }
        if (old_values != values){record_values.append(old_values);}
        this->update();
        selected_values.clear();
    }
    else if (event->keyCombination() == (Qt::KeyboardModifier::ControlModifier|Qt::Key::Key_E)){
        old_values = values;
        for (int value:selected_times){
            if (values[value] == -1){
                values[value] = 500;
            }
        }
        record_values.append(old_values);
        this->update();
    }
    else if (event->keyCombination() == (Qt::KeyboardModifier::ControlModifier|Qt::Key::Key_W)){
        if (selected_values.count() < 1){return;}
        std::sort(selected_values.begin(), selected_values.end());
        for (int i = 0; i < values.count(); ++i){
            if (values[i] == -1 && selected_values.indexOf(i) != -1){
                selected_values.removeAt(selected_values.indexOf(i));
            }
        }
        QList<int> old_selected_values = selected_values;
        selected_values.clear();
        for (int index = 0; index < old_selected_values.count(); index++) {
            if (index == 0) {
                if (old_selected_values.count() > 1 &&
                    values[old_selected_values[0]] > values[old_selected_values[1]]) {
                    selected_values.append(old_selected_values[0]);
                }
            } else if (index == old_selected_values.count() - 1) {
                if (values[old_selected_values[index]] > values[old_selected_values[index - 1]]) {
                    selected_values.append(old_selected_values[index]);
                }
            } else {
                if (values[old_selected_values[index]] >= values[old_selected_values[index - 1]] &&
                    values[old_selected_values[index]] > values[old_selected_values[index + 1]]) {
                    selected_values.append(old_selected_values[index]);
                }
                else if (values[old_selected_values[index]] > values[old_selected_values[index - 1]] &&
                         values[old_selected_values[index]] >= values[old_selected_values[index + 1]]){
                    selected_values.append(old_selected_values[index]);
                }
            }
        }
        this->update();
    }
    else if (event->keyCombination() == (Qt::KeyboardModifier::ControlModifier|Qt::Key::Key_S)){
        if (selected_values.count() < 1){return;}
        std::sort(selected_values.begin(), selected_values.end());
        for (int i = 0; i < values.count(); ++i){
            if (values[i] == -1 && selected_values.indexOf(i) != -1){
                selected_values.removeAt(selected_values.indexOf(i));
            }
        }
        QList<int> old_selected_values = selected_values;
        selected_values.clear();
        for (int index = 0; index < old_selected_values.count(); index++) {
            if (index == 0) {
                if (old_selected_values.count() > 1 &&
                    values[old_selected_values[0]] < values[old_selected_values[1]]) {
                    selected_values.append(old_selected_values[0]);
                }
            } else if (index == old_selected_values.count() - 1) {
                if (values[old_selected_values[index]] < values[old_selected_values[index - 1]]) {
                    selected_values.append(old_selected_values[index]);
                }
            } else {
                if (values[old_selected_values[index]] <= values[old_selected_values[index - 1]] &&
                    values[old_selected_values[index]] < values[old_selected_values[index + 1]]) {
                    selected_values.append(old_selected_values[index]);
                }
                else if (values[old_selected_values[index]] < values[old_selected_values[index - 1]] &&
                         values[old_selected_values[index]] <= values[old_selected_values[index + 1]]){
                    selected_values.append(old_selected_values[index]);
                }
            }
        }
    }
    else if (event->keyCombination() == (Qt::KeyboardModifier::ControlModifier|Qt::Key::Key_C)){
        if (selected_values.count() < 1){return;}
        for (int i = 0; i < values.count(); ++i){
            if (values[i] == -1 && selected_values.indexOf(i) != -1){
                selected_values.removeAt(selected_values.indexOf(i));
            }
        }
        std::sort(selected_values.begin(), selected_values.end());
        copy_values.clear();
        copy_values_indexs.clear();
        for (int index : selected_values){
            copy_values_indexs.append(index);
        }
        for (int i = copy_values_indexs[0]; i <= copy_values_indexs[copy_values_indexs.count()-1]; ++i){
            if (copy_values_indexs.indexOf(i) == -1){
                copy_values_indexs.append(i);
                std::sort(copy_values_indexs.begin(), copy_values_indexs.end());
            }
            copy_values.append(values[i]);
        }
        emit get_copy_values(copy_values,copy_values_indexs);
    }
    else if (event->keyCombination() == (Qt::KeyboardModifier::ControlModifier|Qt::Key::Key_X)){
        if (selected_values.count() < 1){return;}
        for (int i = 0; i < values.count(); ++i){
            if (values[i] == -1 && selected_values.indexOf(i) != -1){
                selected_values.removeAt(selected_values.indexOf(i));
            }
        }
        std::sort(selected_values.begin(), selected_values.end());
        copy_values.clear();
        copy_values_indexs.clear();
        for (int index : selected_values){
            copy_values_indexs.append(index);
        }
        for (int i = copy_values_indexs[0]; i <= copy_values_indexs[copy_values_indexs.count()-1]; ++i){
            if (copy_values_indexs.indexOf(i) == -1){
                copy_values_indexs.append(i);
                std::sort(copy_values_indexs.begin(), copy_values_indexs.end());
            }
            copy_values.append(values[i]);
        }
        emit get_copy_values(copy_values,copy_values_indexs);
        for (int value:selected_values){
            if (value == 0 || value == values.count()-1){continue;}
            values[value] = -1;
        }
        record_values.append(old_values);
        this->update();
    }
    else if (event->keyCombination() == (Qt::KeyboardModifier::ControlModifier|Qt::Key::Key_V)){
        old_values = values;
        int index = selected_line;
        for (int i = 0; i < copy_values.count(); ++i){
            if (index+copy_values_indexs[0] - copy_values_indexs[0] < values.count()-1 && index+copy_values_indexs[i] - copy_values_indexs[0] >= 0){
                values[index+copy_values_indexs[i] - copy_values_indexs[0]] = copy_values[i];
            }
            this->update();
        }
        if (old_values != values){record_values.append(old_values);}
    }
    else if (event->keyCombination() == (Qt::KeyboardModifier::ControlModifier|Qt::Key::Key_Z)){
        if (record_values.count() < 1){return;}
        values = record_values[record_values.count()-1];
        record_values.removeAt(record_values.count()-1);
        this->update();
    }
    else if (event->keyCombination() == (Qt::KeyboardModifier::ControlModifier|Qt::Key::Key_PageUp)){
        if (movefirst){movefirst = false;old_values = values;}
        if (selected_values.count() < 1){return;}
        for (int i = 0; i < values.count(); ++i){
            if (values[i] == -1 && selected_values.indexOf(i) != -1){
                selected_values.removeAt(selected_values.indexOf(i));
            }
        }
        std::sort(selected_values.begin(), selected_values.end());
        QList<int> now_values = {};
        for (int index : selected_values){
            now_values.append(values[index]);
        }
        int min = 999;
        int max = 0;
        for (float value : now_values) {
            if (value > max) {
                max = value;
            }
        }
        for (float value : now_values) {
            if (value < min) {
                min = value;
            }
        }
        int average = (max+min)/2;
        for (int i = 0; i < now_values.count(); ++i){
            int difference = now_values[i] - average;
            int amplifiedDifference = difference * 1.1;
            int newValue = average + amplifiedDifference;
            now_values[i] = newValue;
            if (now_values[i] > 999){now_values[i] = 999;}
            else if (now_values[i] < 0){now_values[i] = 0;}
        }
        for (int i = 0; i < selected_values.count(); ++i){
            values[selected_values[i]] = now_values[i];
        }
        this->update();
    }
    else if (event->keyCombination() == (Qt::KeyboardModifier::ControlModifier|Qt::Key::Key_PageDown)){
        if (movefirst){movefirst = false;old_values = values;}
        if (selected_values.count() < 1){return;}
        for (int i = 0; i < values.count(); ++i){
            if (values[i] == -1 && selected_values.indexOf(i) != -1){
                selected_values.removeAt(selected_values.indexOf(i));
            }
        }
        std::sort(selected_values.begin(), selected_values.end());
        QList<int> now_values = {};
        for (int index : selected_values){
            now_values.append(values[index]);
        }
        int min = 999;
        int max = 0;
        for (float value : now_values) {
            if (value > max) {
                max = value;
            }
        }
        for (float value : now_values) {
            if (value < min) {
                min = value;
            }
        }
        int average = (max+min)/2;
        for (int i = 0; i < now_values.count(); ++i){
            int difference = now_values[i] - average;
            int amplifiedDifference = difference * 0.9;
            int newValue = average + amplifiedDifference;
            now_values[i] = newValue;
            if (now_values[i] > 999){now_values[i] = 999;}
            else if (now_values[i] < 0){now_values[i] = 0;}
        }
        for (int i = 0; i < selected_values.count(); ++i){
            values[selected_values[i]] = now_values[i];
        }
        this->update();
    }
    if (event->key() == Qt::Key::Key_Shift){
        key_shift = true;
    }
    else if (event->key() == Qt::Key::Key_Control){
        key_control = true;
    }
    else if (event->key() == Qt::Key::Key_Space){
        emit set_play();
    }
    else if (event->key() == Qt::Key::Key_Alt){
        mouse1 = false;
        mouse3 = false;
        mouse2 = false;
        key_alt = true;
        key_shift = false;
        key_control = false;
        selected_values.clear();
        selected_times.clear();
        if (!rebuild){
            rebuild = true;
            rebuild_start = this->mapFromGlobal(QCursor::pos());
            setMouseTracking(true);
            rebuild_times.clear();
        }
        else{
            rebuild_times.clear();
            rebuild = false;
            setMouseTracking(false);
            emit current_rebuildtimes(rebuild_times);
        }
        this->update();
    }
}

void Scripter_edit::keyReleaseEvent(QKeyEvent *event)
{
    key_shift = false;
    key_control = false;
    key_alt = false;
    if (event->keyCombination() == (Qt::KeyboardModifier::ShiftModifier|Qt::Key::Key_Up)){
        movefirst = true;
    }
    else if (event->keyCombination() == (Qt::KeyboardModifier::ShiftModifier|Qt::Key::Key_Left)){
        movefirst = true;
    }
    else if (event->keyCombination() == (Qt::KeyboardModifier::ShiftModifier|Qt::Key::Key_Right)){
        movefirst = true;
    }
    else if (event->keyCombination() == (Qt::KeyboardModifier::ShiftModifier|Qt::Key::Key_Down)){
        movefirst = true;
    }
    else if (event->keyCombination() == (Qt::KeyboardModifier::ControlModifier|Qt::Key::Key_PageUp)){
        movefirst = true;
    }
    else if (event->keyCombination() == (Qt::KeyboardModifier::ControlModifier|Qt::Key::Key_PageDown)){
        movefirst = true;
    }
    if (old_values != values){record_values.append(old_values);}
}

void Scripter_edit::focusInEvent(QFocusEvent *event)
{
    focus = true;
}

void Scripter_edit::focusOutEvent(QFocusEvent *event)
{
    focus = false;
}

void Scripter_edit::wheelEvent(QWheelEvent *event)
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




