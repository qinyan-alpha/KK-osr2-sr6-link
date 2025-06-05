#include "mainwindow.h"
#include "ui_mainwindow.h"








void MainWindow::ui_init(){
    ports_list = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo& portInfo :ports_list) {
        ui->port_id->addItem(portInfo.portName() + ":" + portInfo.description(), portInfo.portName());
    }
    connect(ui->home, &QPushButton::clicked, this, [=] {
        ui->stackedWidget->setCurrentIndex(0);});
    connect(ui->setting, &QPushButton::clicked, this, [=] {
        ui->stackedWidget->setCurrentIndex(1);});
    //connect(ui->scripter, &QPushButton::clicked, this, [=] {
        //ui->stackedWidget->setCurrentIndex(2);});
    connect(ui->scripter_2, &QPushButton::clicked, this, [=] {
        ui->stackedWidget->setCurrentIndex(3);});
    top_windows = false;
    connect(ui->windows_top_btn,&QPushButton::clicked,this,[=]{
        if (top_windows){
            top_windows = false;
            setWindowFlags(windowFlags() & ~Qt::WindowStaysOnTopHint);
            ui->windows_top_btn->setStyleSheet("QPushButton {"
           "border: 2px;"
           "background-position: center;"
           "background-repeat: no-repeat;"
           "background-image: url(:/forms/icons/cil-notes.png);"
           "border-radius: 0px;"
           "}"
           "QPushButton:hover {"
           "background-color: rgb(57, 65, 80);"
           "border: none;"
           "}");
            show();
        }else{
            top_windows = true;
            setWindowFlags(windowFlags() | Qt::WindowType::WindowStaysOnTopHint);
            ui->windows_top_btn->setStyleSheet("QPushButton {"
            "border: 2px;"
            "background-position: center;"
            "background-repeat: no-repeat;"
            "background-image: url(:/forms/icons/cil-notes.png);"
            "border-radius: 0px;"
            "background-color: rgb(57, 65, 80);"
            "}");
            show();
        }
        ;});
    isMenuExpanded = false;
    ui->leftMenuBg->setFixedWidth(75);
    m_animation0 = new QPropertyAnimation(ui->leftMenuBg,"minimumWidth");
    m_animation0->setDuration(300);
    connect(ui->toggle_btn,&QPushButton::clicked,this,[=]{
        ui->toggle_btn->setEnabled(false);
            int startWidth = ui->leftMenuBg->width();
            int endWidth;
            if (isMenuExpanded) {
                endWidth = 75;
            } else {
                endWidth = 200;
            }
            m_animation0->setStartValue(startWidth);
            m_animation0->setEndValue(endWidth);
            connect(m_animation0, &QPropertyAnimation::valueChanged, this, [=](const QVariant &value) {
                int currentWidth = value.toInt();
                if (currentWidth >= 150) {
                    ui->server_label->setStyleSheet("background-color: rgba(220, 147, 249,0);"
                                                    "color: rgb(225, 255, 255);");
                } else {
                    ui->server_label->setStyleSheet("background-color: rgba(220, 147, 249,0);"
                                                    "color: rgba(225, 255, 255,0);");
                }
            });
            connect(m_animation0, &QPropertyAnimation::finished, this, [=]() {
                disconnect(m_animation0, &QPropertyAnimation::valueChanged, nullptr, nullptr);
                ui->toggle_btn->setEnabled(true);
            });
            m_animation0->start();
            isMenuExpanded = !isMenuExpanded;
        ;});
    connect(ui->minimizeAppbtn, &QPushButton::clicked, this, [=] {
        showMinimized();
        ;});
    connect(ui->maximizeRestoreAppbtn, &QPushButton::clicked, this, [=] {
        if(isMaximized()) {showNormal(); } else {showMaximized();}
        });
    connect(ui->closeAppbtn, &QPushButton::clicked, this, [=] {
        close();
        ;});
    connect(ui->game_folder, &QPushButton::clicked, this, [=] {
        QString selectedDirectory = QFileDialog::getExistingDirectory(nullptr, "Select Directory", QDir::homePath());
        ui->game_root->setText(selectedDirectory);
        settings->beginGroup("Game");
        settings->setValue("game root", selectedDirectory);
        settings->endGroup();
        ;});
    btn_init();
    overview_edit = new Overview_edit;
    overview_edit->values.clear();
    scripter3L0 = new Scripter_edit3;
    scripter3L0->values.clear();
    scripter3L1 = new Scripter_edit3;
    scripter3L1->values.clear();
    scripter3L2 = new Scripter_edit3;
    scripter3L2->values.clear();
    scripter3R0 = new Scripter_edit3;
    scripter3R0->values.clear();
    scripter3R1 = new Scripter_edit3;
    scripter3R1->values.clear();
    scripter3R2 = new Scripter_edit3;
    scripter3R2->values.clear();
    silderL0 = new Range_Silder;
    silderL1 = new Range_Silder;
    silderL2 = new Range_Silder;
    silderR0 = new Range_Silder;
    silderR1 = new Range_Silder;
    silderR2 = new Range_Silder;
    ui->L0_silder->layout()->addWidget(silderL0);
    ui->L1_silder->layout()->addWidget(silderL1);
    ui->L2_silder->layout()->addWidget(silderL2);
    ui->R0_silder->layout()->addWidget(silderR0);
    ui->R1_silder->layout()->addWidget(silderR1);
    ui->R2_silder->layout()->addWidget(silderR2);
    ui->Ov_widget->layout()->addWidget(overview_edit);
    ui->L0_widget_2->layout()->addWidget(scripter3L0);
    ui->L1_widget_2->layout()->addWidget(scripter3L1);
    ui->L2_widget_2->layout()->addWidget(scripter3L2);
    ui->R0_widget_2->layout()->addWidget(scripter3R0);
    ui->R1_widget_2->layout()->addWidget(scripter3R1);
    ui->R2_widget_2->layout()->addWidget(scripter3R2);
    connect(overview_edit, &Overview_edit::select_part, this, [=](int part) {
        ui->scrollArea_13->setEnabled(false);
        if (overview_edit->values.count()){
            overview_edit->setEnabled(false);
            ui->scripter_part_list->blockSignals(true);
            ui->scripter_part_list->setCurrentIndex(part);
            ui->lovemaking_mode_list->setCurrentText(sceneParts[ui->scripter_part_list->currentIndex()].lovemaking_mode);
            QStringList charas = sceneParts[ui->scripter_part_list->currentIndex()].charas.split("-");
            ui->girl_list->blockSignals(true);
            ui->boy_list->blockSignals(true);
            ui->girl_list->setCurrentText(charas[0]);
            ui->boy_list->setCurrentText(charas[1]);
            ui->girl_list->blockSignals(false);
            ui->boy_list->blockSignals(false);
            overview_edit->setEnabled(true);
        }
        ui->scrollArea_13->setEnabled(true);
        overview_edit->setFocusPolicy(Qt::StrongFocus);
        overview_edit->setFocus();
    });
    connect(overview_edit, &Overview_edit::add_part, this, [=](int part) {
        ui->scrollArea_13->setEnabled(false);
        if (overview_edit->values.count()){
            overview_edit->setEnabled(false);
            ui->scripter_part_list->insertItem(part,"part" + QString::number(part+1));
            ScenePart scenepart;
            scenepart.part = overview_edit->split_lines[part-1];
            scenepart.lovemaking_mode = "normal";
            scenepart.charas = ui->girl_list->itemText(0) + "-" + ui->boy_list->itemText(0);
            sceneParts.append(scenepart);
            ui->girl_list->blockSignals(true);
            ui->boy_list->blockSignals(true);
            ui->lovemaking_mode_list->blockSignals(true);
            ui->girl_list->setCurrentIndex(0);
            ui->boy_list->setCurrentIndex(0);
            ui->lovemaking_mode_list->setCurrentText("normal");
            ui->girl_list->blockSignals(false);
            ui->boy_list->blockSignals(false);
            ui->lovemaking_mode_list->blockSignals(false);
            std::sort(sceneParts.begin(), sceneParts.end(), [](const ScenePart& a, const ScenePart& b) {
                return a.part < b.part;
            });
            ui->scripter_part_list->setCurrentIndex(part);
            overview_edit->setEnabled(true);
        }
        ui->scrollArea_13->setEnabled(true);
        overview_edit->setFocusPolicy(Qt::StrongFocus);
        overview_edit->setFocus();
    });
    connect(overview_edit, &Overview_edit::del_part, this, [=](int part) {
        ui->scrollArea_13->setEnabled(false);
        if (overview_edit->values.count()){
            overview_edit->setEnabled(false);
            ui->scripter_part_list->blockSignals(true);
            ui->scripter_part_list->removeItem(part+1);
            for (auto it = sceneParts.begin(); it != sceneParts.end(); ) {
                if (it->part == overview_edit->split_lines[part]) {
                    it = sceneParts.erase(it);
                } else {
                    ++it;
                }
            }
            overview_edit->split_lines.removeAt(part);
            for (int i = 0; i < ui->scripter_part_list->count(); i++) {
                if (ui->scripter_part_list->itemText(i).startsWith("part")) {
                    ui->scripter_part_list->setItemText(i, "part" + QString::number(i + 1));
                }
            }
            ui->scripter_part_list->blockSignals(false);
            overview_edit->setEnabled(true);
        }
        ui->scrollArea_13->setEnabled(true);
        overview_edit->setFocusPolicy(Qt::StrongFocus);
        overview_edit->setFocus();
    });
    connect(scripter3L0,&Scripter_edit3::get_copy_values,this,&MainWindow::copy_values);
    connect(scripter3L1,&Scripter_edit3::get_copy_values,this,&MainWindow::copy_values);
    connect(scripter3L2,&Scripter_edit3::get_copy_values,this,&MainWindow::copy_values);
    connect(scripter3R0,&Scripter_edit3::get_copy_values,this,&MainWindow::copy_values);
    connect(scripter3R1,&Scripter_edit3::get_copy_values,this,&MainWindow::copy_values);
    connect(scripter3R2,&Scripter_edit3::get_copy_values,this,&MainWindow::copy_values);
    connect(overview_edit,&Overview_edit::current_line,this,&MainWindow::setplaytime);
    connect(scripter3L0,&Scripter_edit3::current_line,this,&MainWindow::setplaytime);
    connect(scripter3L1,&Scripter_edit3::current_line,this,&MainWindow::setplaytime);
    connect(scripter3L2,&Scripter_edit3::current_line,this,&MainWindow::setplaytime);
    connect(scripter3R0,&Scripter_edit3::current_line,this,&MainWindow::setplaytime);
    connect(scripter3R1,&Scripter_edit3::current_line,this,&MainWindow::setplaytime);
    connect(scripter3R2,&Scripter_edit3::current_line,this,&MainWindow::setplaytime);
    connect(overview_edit,&Overview_edit::set_play,this,&MainWindow::set_play);
    connect(scripter3L0,&Scripter_edit3::set_play,this,&MainWindow::set_play);
    connect(scripter3L1,&Scripter_edit3::set_play,this,&MainWindow::set_play);
    connect(scripter3L2,&Scripter_edit3::set_play,this,&MainWindow::set_play);
    connect(scripter3R0,&Scripter_edit3::set_play,this,&MainWindow::set_play);
    connect(scripter3R1,&Scripter_edit3::set_play,this,&MainWindow::set_play);
    connect(scripter3R2,&Scripter_edit3::set_play,this,&MainWindow::set_play);
    connect(scripter3L0,&Scripter_edit3::rebuildtimes,this,&MainWindow::rebuildtimes3);
    connect(scripter3L1,&Scripter_edit3::rebuildtimes,this,&MainWindow::rebuildtimes3);
    connect(scripter3L2,&Scripter_edit3::rebuildtimes,this,&MainWindow::rebuildtimes3);
    connect(scripter3R0,&Scripter_edit3::rebuildtimes,this,&MainWindow::rebuildtimes3);
    connect(scripter3R1,&Scripter_edit3::rebuildtimes,this,&MainWindow::rebuildtimes3);
    connect(scripter3R2,&Scripter_edit3::rebuildtimes,this,&MainWindow::rebuildtimes3);
    ui->scrollArea_3->verticalScrollBar()->setSingleStep(0);
    ui->scrollArea_13->horizontalScrollBar()->setSingleStep(0);
}


void MainWindow::config_init(){
    QFileInfo fileInfo1("./config.ini");
    if (fileInfo1.exists()) {
        settings = new QSettings("./config.ini",QSettings::IniFormat, this);
        qDebug() << "exist config";
    }
    else {
        qDebug() << "build config";
        settings = new QSettings("./config.ini",QSettings::IniFormat, this);
        settings->beginGroup("SerialPort");
        settings->setValue("baudrate", "115200");
        settings->endGroup();
        settings->beginGroup("Server");
        settings->setValue("Serverip", "127.0.0.1");
        settings->setValue("Serverport", "8000");
        settings->endGroup();
        settings->beginGroup("Game");
        settings->setValue("game root", "");
        settings->endGroup();
        settings->beginGroup("Intiface Central");
        settings->setValue("webserverip", "ws://localhost:12345");
        settings->endGroup();
        settings->beginGroup("Scripter edit");
        settings->setValue("rebuild all axes", "0");
        settings->endGroup();
    }
    //SerialPort
    connect(ui->BaudRate, &QLineEdit::textChanged, this, [=] {
        if (ui->BaudRate->text().toInt() >= 0 ) {
            settings->beginGroup("SerialPort");
            settings->setValue("baudrate", ui->BaudRate->text());
            settings->endGroup();
            baudrate = ui->BaudRate->text().toInt();
        }
        else {
            ui->BaudRate->setText(settings->value("SerialPort/baudrate").toString());
        }
    });
    connect(ui->Serverip, &QLineEdit::textChanged, this, [=] {
        settings->beginGroup("Server");
        settings->setValue("Serverip", ui->Serverip->text());
        settings->endGroup();
        server_ip = ui->Serverip->text();
    });
    connect(ui->Port, &QLineEdit::textChanged, this, [=] {
        if (ui->Port->text().toInt() >= 0 && ui->Port->text().toInt() <= 9999) {
            settings->beginGroup("SerialPort");
            settings->setValue("Serverport", ui->Port->text());
            settings->endGroup();
        }
        else {
            ui->Port->setText(settings->value("SerialPort/Serverport").toString());
        }
        port = ui->Port->text().toInt();
    });
    connect(ui->port_id, &QComboBox::currentIndexChanged, this, [=] {
        port_id = ui->port_id->currentIndex();
    });
    connect(ui->webserver_ip, &QLineEdit::textChanged, this, [=] {
        intiface_central_ip = ui->webserver_ip->text();
    });
    connect(ui->rebuild_all_checkbox, &QCheckBox::isChecked, this, [=] {
        if(ui->rebuild_all_checkbox->isChecked()){
            settings->beginGroup("Scripter edit");
            settings->setValue("rebuild all axes", "1");
            settings->endGroup();
        }
        else{
            settings->beginGroup("Scripter edit");
            settings->setValue("rebuild all axes", "0");
            settings->endGroup();
        }
    });
    ui->BaudRate->setText(settings->value("SerialPort/baudrate").toString());
    ui->Serverip->setText(settings->value("Server/Serverip").toString());
    ui->Port->setText(settings->value("Server/Serverport").toString());
    ui->game_root->setText(settings->value("Game/game root").toString());
    ui->webserver_ip->setText(settings->value("Intiface Central/webserverip").toString());
    if (settings->value("Scripter edit/rebuild all axes").toInt() == 1){
        ui->rebuild_all_checkbox->setChecked(true);
    }
    else{
        ui->rebuild_all_checkbox->setChecked(false);
    }
}


void MainWindow::btn_init(){
    btn_sty1 = "QPushButton {border: none;background-color: rgb(220, 147, 249);background-position: center;background-repeat: no-repeat;border-radius: 25px;"
               "background-image: url(:/forms/icons/cil-media-play.png);}"
               "QPushButton:hover {background-color: rgb(240, 200, 249);}";
    btn_sty2 = "QPushButton {border: none;background-color: rgb(220, 200, 249);background-position: center;background-repeat: no-repeat;border-radius: 25px;"
               "background-image: url(:/forms/icons/cil-media-play.png);}";
    btn_sty3 = "QPushButton {border: none;background-color: rgb(220, 147, 249);background-position: center;background-repeat: no-repeat;border-radius: 25px;"
               "background-image: url(:/forms/icons/cil-media-stop.png);}"
               "QPushButton:hover {background-color: rgb(240, 200, 249);}";
    btn_sty4 = "QPushButton {border: none;background-color: rgb(220, 147, 249);background-position: center;background-repeat: no-repeat;border-radius: 25px;"
               "background-image: url(:/forms/icons/cil-ban.png);}";
    btn_sty5 = "QPushButton {border: none;background-position: center;background-repeat: no-repeat;background-image: url(:/forms/icons/cil-media-play.png);background-color:transparent;}";
    btn_sty6 = "QPushButton {border: none;background-position: center;background-repeat: no-repeat;background-image: url(:/forms/icons/cil-media-stop.png);;background-color:transparent;}";
    btn_sty7 = "QPushButton {border: none;background-position: center;background-repeat: no-repeat;background-image: url(:/forms/icons/cil-ban.png);;background-color:transparent;}";
    tips_window_init();
    build_server = false;
    server = new QTcpServer;
    socket = new QTcpSocket;
    connect(server, &QTcpServer::newConnection, this, &MainWindow::new_connected);
    connect(ui->run_btn, &QPushButton::clicked, this,&MainWindow::run_btn_clicked);
    intiface_central_ip = "";
    webclient = new QWebSocket;
    connect(webclient, &QWebSocket::connected, this, &MainWindow::webclient_onconnected);
    connect(webclient, &QWebSocket::disconnected, this, &MainWindow::webclient_ondisconnected);
    connect(webclient, &QWebSocket::textMessageReceived, this, &MainWindow::onTextMessageReceived);
    timeoutTimer.setInterval(5000);
    timeoutTimer.setSingleShot(true);
    connect(&timeoutTimer,&QTimer::timeout,this,[=]{webclient->abort();tips->setText("intiface central link failed,check intiface central ip address.");tips_window_start();
    ui->link_intiface_central->setStyleSheet(btn_sty7);timeoutrestoreTimer.start();});
    timeoutrestoreTimer.setInterval(3000);
    timeoutrestoreTimer.setSingleShot(true);
    connect(&timeoutrestoreTimer,&QTimer::timeout,this,[=]{ui->link_intiface_central->setEnabled(true);ui->link_intiface_central->setStyleSheet(btn_sty5);});
    connect(ui->link_intiface_central,&QPushButton::clicked,this,[=]{
        if (webclient->state() == QAbstractSocket::UnconnectedState)
        {
            ui->link_intiface_central->setEnabled(false);
            webclient->open(ui->webserver_ip->text());timeoutTimer.start();
        }
        else if (webclient->state() == QAbstractSocket::ConnectedState){
            devices.clear();
            devices_index.clear();
            ui->devices_list_combox->clear();
            ui->feature_list->clear();
            webclient->abort();
            webclient->close();
            ui->link_intiface_central->setStyleSheet(btn_sty5);
        }
        });
    requestdevicelistTimer.setInterval(100);
    requestdevicelistTimer.setSingleShot(true);
    connect(&requestdevicelistTimer,&QTimer::timeout,this,[=]{
        QJsonObject RequestDeviceList;
        RequestDeviceList["Id"] = 1;
        QJsonObject requestdevicelist;
        requestdevicelist["RequestDeviceList"] = RequestDeviceList;
        QJsonArray requestdevicelistArray;
        requestdevicelistArray.append(requestdevicelist);
        webclient->sendTextMessage(QString(QJsonDocument(requestdevicelistArray).toJson(QJsonDocument::Compact)));
    });
    connect(ui->devices_list_combox,&QComboBox::currentIndexChanged,this,[=]{
        ui->feature_list->clear();
        if (devices.count() == 0 ){return;}
        for (int i = 1;i <= devices[ui->devices_list_combox->currentIndex()].feature.count() ; i ++){
            ui->feature_list->addItem(QString::number(i));
        }
    });
    connect(ui->feature_list,&QComboBox::currentIndexChanged,this,[=]{
        if (ui->feature_list->currentIndex() == -1){ui->feature_list->setCurrentIndex(0);return;}
        ui->work_on_axes->setCurrentIndex(devices[ui->devices_list_combox->currentIndex()].feature[ui->feature_list->currentIndex()]);
        if (devices[ui->devices_list_combox->currentIndex()].feature_enable[ui->feature_list->currentIndex()] == 1){
            ui->enable_checkBox->setChecked(true);
        }
        else{
            ui->enable_checkBox->setChecked(false);
        }
    });
    connect(ui->work_on_axes,&QComboBox::currentIndexChanged,this,[=]{
        if (ui->feature_list->currentIndex() == -1){ui->feature_list->setCurrentIndex(0);return;}
        devices[ui->devices_list_combox->currentIndex()].feature[ui->feature_list->currentIndex()] = ui->work_on_axes->currentIndex();
        if (devices[ui->devices_list_combox->currentIndex()].feature_enable[ui->feature_list->currentIndex()] == 1){
            ui->enable_checkBox->setChecked(true);
        }
        else{
            ui->enable_checkBox->setChecked(false);
        }
    });
    connect(ui->enable_checkBox,&QCheckBox::clicked,this,[=]{
        if (ui->devices_list_combox->count()==0){return;}
        if (devices[ui->devices_list_combox->currentIndex()].feature_enable[ui->feature_list->currentIndex()] == 1)
        {devices[ui->devices_list_combox->currentIndex()].feature_enable[ui->feature_list->currentIndex()] = 0;}
        else{devices[ui->devices_list_combox->currentIndex()].feature_enable[ui->feature_list->currentIndex()] = 1;}
    });

    //New 3
    connect(ui->scripter_part_list, &QComboBox::currentIndexChanged, this, [=](int part) {
        if (overview_edit->values.count()){
            if (part == 0){
                overview_edit->selected_part = 0;
            }
            else{
                overview_edit->selected_part = overview_edit->split_lines[part-1];
                overview_edit->update();
            }
            ui->lovemaking_mode_list->setCurrentText(sceneParts[part].lovemaking_mode);
            QStringList charas = sceneParts[part].charas.split("-");
            ui->girl_list->blockSignals(true);
            ui->boy_list->blockSignals(true);
            ui->girl_list->setCurrentText(charas[0]);
            ui->boy_list->setCurrentText(charas[1]);
            ui->girl_list->blockSignals(false);
            ui->boy_list->blockSignals(false);
        }
    });
    connect(ui->girl_list, &QComboBox::currentIndexChanged, this, [=]{
        sceneParts[ui->scripter_part_list->currentIndex()].charas = ui->girl_list->currentText() + "-" + ui->boy_list->currentText();
        if (ui->select_chara_combobox->isChecked()){            
            if (allowriter){
                try {
                    socket->write("2:"+ui->girl_list->currentText().toLocal8Bit());
                    socket->flush();
                } catch (...) {
                }
                allowriter = false;
                writerTimer.start();
            }
        }
    });
    connect(ui->boy_list, &QComboBox::currentIndexChanged, this, [=]{
        sceneParts[ui->scripter_part_list->currentIndex()].charas = ui->girl_list->currentText() + "-" + ui->boy_list->currentText();
        if (ui->select_chara_combobox->isChecked()){            
            if (allowriter){
                try {
                    socket->write("2:"+ui->boy_list->currentText().toLocal8Bit());
                    socket->flush();
                } catch (...) {
                }
                allowriter = false;
                writerTimer.start();
            }
        }
    });
    connect(ui->lovemaking_mode_list, &QComboBox::currentIndexChanged, this, [=]{
        sceneParts[ui->scripter_part_list->currentIndex()].lovemaking_mode = ui->lovemaking_mode_list->currentText();
    });
    connect(ui->creaet_btn, &QPushButton::clicked, this, [=]{
        if (overview_edit->values.count()){
            overview_edit->setEnabled(false);
            scripter3L0->setEnabled(false);
            QList<float> _inserts = {};
            QList<float> _surges = {};
            QList<float> _sways = {};
            QList<float> _twists = {};
            QList<float> _pitchs = {};
            QList<float> _rolls = {};
            int i = ui->scripter_part_list->currentIndex();
            int partbegin = sceneParts[i].part;int partend;
            if (i == sceneParts.count()-1) {partend = inserts.count();}else{partend = sceneParts[i+1].part;}
            for (Lovemaking_data lovemaking_data:lovemaking_datas){
                if (lovemaking_data.charas_name == sceneParts[i].charas){
                    if (sceneParts[i].lovemaking_mode == "normal"){
                        for (int i = partbegin; i < partend; ++i) {
                            inserts[i] = lovemaking_data.inserts[i];
                            surges[i] = lovemaking_data.surges[i];
                            sways[i] = lovemaking_data.sways[i];
                            twists[i] = lovemaking_data.twists[i];
                            pitchs[i] = lovemaking_data.pitchs[i];
                            rolls[i] = lovemaking_data.rolls[i];
                            _inserts.append(inserts[i]);
                            _surges.append(surges[i]);
                            _sways.append(sways[i]);
                            _twists.append(twists[i]);
                            _pitchs.append(pitchs[i]);
                            _rolls.append(rolls[i]);
                        }
                    }
                    else if (sceneParts[i].lovemaking_mode == "blowjob"){
                        for (int i = partbegin; i < partend; ++i) {
                            blowjob_inserts[i] = lovemaking_data.blowjob_inserts[i];
                            blowjob_surges[i] = lovemaking_data.blowjob_surges[i];
                            blowjob_sways[i] = lovemaking_data.blowjob_sways[i];
                            blowjob_twists[i] = lovemaking_data.blowjob_twists[i];
                            blowjob_pitchs[i] = lovemaking_data.blowjob_pitchs[i];
                            blowjob_rolls[i] = lovemaking_data.blowjob_rolls[i];
                            _inserts.append(blowjob_inserts[i]);
                            _surges.append(blowjob_surges[i]);
                            _sways.append(blowjob_sways[i]);
                            _twists.append(blowjob_twists[i]);
                            _pitchs.append(blowjob_pitchs[i]);
                            _rolls.append(blowjob_rolls[i]);
                        }
                    }
                    else if (sceneParts[i].lovemaking_mode == "breastsex"){
                        for (int i = partbegin; i < partend; ++i) {
                            breastsex_inserts[i] = lovemaking_data.breastsex_inserts[i];
                            breastsex_surges[i] = lovemaking_data.breastsex_surges[i];
                            breastsex_sways[i] = lovemaking_data.breastsex_sways[i];
                            breastsex_twists[i] = lovemaking_data.breastsex_twists[i];
                            breastsex_pitchs[i] = lovemaking_data.breastsex_pitchs[i];
                            breastsex_rolls[i] = lovemaking_data.breastsex_rolls[i];
                            _inserts.append(breastsex_inserts[i]);
                            _surges.append(breastsex_surges[i]);
                            _sways.append(breastsex_sways[i]);
                            _twists.append(breastsex_twists[i]);
                            _pitchs.append(breastsex_pitchs[i]);
                            _rolls.append(breastsex_rolls[i]);
                        }
                    }
                    else if (sceneParts[i].lovemaking_mode == "handjob(Detecting girl left hand)"){
                        for (int i = partbegin; i < partend; ++i) {
                            handjobL_inserts[i] = lovemaking_data.handjobL_inserts[i];
                            handjobL_surges[i] = lovemaking_data.handjobL_surges[i];
                            handjobL_sways[i] = lovemaking_data.handjobL_sways[i];
                            handjobL_twists[i] = lovemaking_data.handjobL_twists[i];
                            handjobL_pitchs[i] = lovemaking_data.handjobL_pitchs[i];
                            handjobL_rolls[i] = lovemaking_data.handjobL_rolls[i];
                            _inserts.append(handjobL_inserts[i]);
                            _surges.append(handjobL_surges[i]);
                            _sways.append(handjobL_sways[i]);
                            _twists.append(handjobL_twists[i]);
                            _pitchs.append(handjobL_pitchs[i]);
                            _rolls.append(handjobL_rolls[i]);
                        }
                    }
                    else if (sceneParts[i].lovemaking_mode == "handjob(Detecting girl right hand))"){
                        for (int i = partbegin; i < partend; ++i) {
                            handjobR_inserts[i] = lovemaking_data.handjobR_inserts[i];
                            handjobR_surges[i] = lovemaking_data.handjobR_surges[i];
                            handjobR_sways[i] = lovemaking_data.handjobR_sways[i];
                            handjobR_twists[i] = lovemaking_data.handjobR_twists[i];
                            handjobR_pitchs[i] = lovemaking_data.handjobR_pitchs[i];
                            handjobR_rolls[i] = lovemaking_data.handjobR_rolls[i];
                            _inserts.append(handjobR_inserts[i]);
                            _surges.append(handjobR_surges[i]);
                            _sways.append(handjobR_sways[i]);
                            _twists.append(handjobR_twists[i]);
                            _pitchs.append(handjobR_pitchs[i]);
                            _rolls.append(handjobR_rolls[i]);
                        }
                    }
                    if (_inserts.isEmpty()){return;}
                    float rebuild_insert_max = *std::max_element(_inserts.begin(), _inserts.end());
                    float rebuild_insert_min = *std::min_element(_inserts.begin(), _inserts.end());
                    float surge_sum = std::accumulate(_surges.begin(), _surges.end(), 0.0f);
                    float surge_offset = surge_sum / _surges.count();
                    float sway_sum = std::accumulate(_sways.begin(), _sways.end(), 0.0f);
                    float sway_offset = sway_sum / _sways.count();
                    for (int i = 0; i < _inserts.count(); ++i){
                        int L0 = (999 / (rebuild_insert_min - rebuild_insert_max))*_inserts[i] - (999 / (rebuild_insert_min - rebuild_insert_max))*rebuild_insert_max;
                        if (L0 < 0){L0 = 0;}else if (L0 > 999){L0 = 999;}
                        int L1 = (999-0)/2 - (int)((_surges[i] - surge_offset) * (999-0) / bodywidth / 2);
                        if (L1 < 0){L1 = 0;}else if (L1 > 999){L1 = 999;}
                        int L2 = (999-0)/2 - (int)((_sways[i] - sway_offset) * (999-0) / bodywidth / 2);
                        if (L2 < 0){L2 = 0;}else if (L2 > 999){L2 = 999;}
                        int R0 = (999-0)/2 + (int)(_twists[i] * 11.1);
                        if (R0 < 0){R0 = 0;}else if (R0 > 999){R0 = 999;}
                        int R1 = (999+0)/2 - (int)(_rolls[i] * 11.1 );
                        if (R1 < 0){R1 = 0;}else if (R1 > 999){R1 = 999;}
                        int R2 = (999-0)/2 + (int)(_pitchs[i] * 11.1 / 2);
                        if (R2 < 0){R2 = 0;}else if (R2 > 999){R2 = 999;}
                        L0s[partbegin+i] = L0;
                        L1s[partbegin+i] = L1;
                        L2s[partbegin+i] = L2;
                        R0s[partbegin+i] = R0;
                        R1s[partbegin+i] = R1;
                        R2s[partbegin+i] = R2;
                    }
                    break;
                }
            }
            overview_edit->values = L0s;
            scripter3L0->values = L0s;
            overview_edit->setEnabled(true);
            scripter3L0->setEnabled(true);
        }
    });
    connect(ui->tabWidget_2,&QTabWidget::currentChanged,this,[=]{
        if (overview_edit->values.isEmpty()){return;}
        if (ui->tabWidget_2->currentIndex()){
            ui->girl_list->setEnabled(false);
            ui->boy_list->setEnabled(false);
            ui->scripter_part_list->setEnabled(false);
            ui->lovemaking_mode_list->setEnabled(false);
            ui->creaet_btn->setEnabled(false);
            ui->show_charas->setEnabled(false);
            ui->hide_charas->setEnabled(false);
            ui->select_chara_combobox->setEnabled(false);
            ui->scripter_part_label->setText("current part");
            selected_part = ui->scripter_part_list->currentIndex();
            for (int i=0;i <overview_edit->split_lines.count();i++){
                if (overview_edit->selected_line > overview_edit->split_lines[overview_edit->split_lines.count()-1]){
                    ui->scripter_part_list->setCurrentIndex(ui->scripter_part_list->count()-1);
                    ui->lovemaking_mode_list->setCurrentText(sceneParts[ui->scripter_part_list->count()-1].lovemaking_mode);
                    QStringList charas = sceneParts[ui->scripter_part_list->count()-1].charas.split("-");
                    ui->girl_list->setCurrentText(charas[0]);
                    ui->boy_list->setCurrentText(charas[1]);
                    break;
                }
                if (overview_edit->selected_line <= overview_edit->split_lines[i]){
                    ui->scripter_part_list->setCurrentIndex(i);
                    ui->lovemaking_mode_list->setCurrentText(sceneParts[i].lovemaking_mode);
                    QStringList charas = sceneParts[i].charas.split("-");
                    ui->girl_list->setCurrentText(charas[0]);
                    ui->boy_list->setCurrentText(charas[1]);
                    break;
                }
            }
        }
        else {
            ui->girl_list->setEnabled(true);
            ui->boy_list->setEnabled(true);
            ui->scripter_part_list->setEnabled(true);
            ui->lovemaking_mode_list->setEnabled(true);
            ui->creaet_btn->setEnabled(true);
            ui->show_charas->setEnabled(true);
            ui->hide_charas->setEnabled(true);
            ui->select_chara_combobox->setEnabled(false);
            ui->scripter_part_label->setText("select part");
            ui->scripter_part_list->setCurrentIndex(selected_part);
            ui->lovemaking_mode_list->setCurrentText(sceneParts[selected_part].lovemaking_mode);
            QStringList charas = sceneParts[selected_part].charas.split("-");
            ui->girl_list->setCurrentText(charas[0]);
            ui->boy_list->setCurrentText(charas[1]);
        }
    });
    connect(ui->show_charas, &QPushButton::clicked, this, [=]{
        if (overview_edit->values.count()){
            if (allowriter){
                try {
                    socket->write("3:"+ui->girl_list->currentText().toLocal8Bit() + "-" + ui-> boy_list->currentText().toLocal8Bit());
                    socket->flush();
                } catch (...) {
                }
                allowriter = false;
                writerTimer.start();
            }
        }
    });
    connect(ui->hide_charas, &QPushButton::clicked, this, [=]{
        if (overview_edit->values.count()){
            if (allowriter){
                try {
                    socket->write("4:"+ui->girl_list->currentText().toLocal8Bit() + "-" + ui-> boy_list->currentText().toLocal8Bit());
                    socket->flush();
                } catch (...) {
                }
                allowriter = false;
                writerTimer.start();
            }
        }
    });
    connect(ui->convert_btn, &QPushButton::clicked, this, [=]{
        if (file_path != ""){
            save_scripter();
            QString get_path = file_path;
            get_path = get_path.replace(".txt",".funscript");
            convertsr6sToFunscript(L0s, get_path);
            get_path = get_path.replace(".funscript",".surge.funscript");
            convertsr6sToFunscript(L1s, get_path);
            get_path = get_path.replace(".sway.funscript",".surge.funscript");
            convertsr6sToFunscript(L2s, get_path);
            get_path = get_path.replace(".surge.funscript",".twist.funscript");
            convertsr6sToFunscript(R0s, get_path);
            get_path = get_path.replace(".twist.funscript",".roll.funscript");
            convertsr6sToFunscript(R1s, get_path);
            get_path = get_path.replace(".roll.funscript",".pitch.funscript");
            convertsr6sToFunscript(R2s, get_path);
        }
    });
    //
    reScanningTimer.setInterval(3000);
    reScanningTimer.setSingleShot(true);
    connect(ui->rescann_btn,&QPushButton::clicked,this,[=]{
        ui->rescann_btn->setEnabled(false);
        reScanningTimer.start();
        QJsonObject StartScanning;
        StartScanning["Id"] = 1;
        QJsonObject startScanning;
        startScanning["StartScanning"] = StartScanning;
        QJsonArray startScanningArray;
        startScanningArray.append(startScanning);
        webclient->sendTextMessage(QString(QJsonDocument(startScanningArray).toJson(QJsonDocument::Compact)));
    });
    connect(&reScanningTimer,&QTimer::timeout,this,[=]{
        QJsonObject StopScanning;
        StopScanning["Id"] = 1;
        QJsonObject stopscanning;
        stopscanning["StopScanning"] = StopScanning;
        QJsonArray stopscanningArray;
        stopscanningArray.append(stopscanning);
        webclient->sendTextMessage(QString(QJsonDocument(stopscanningArray).toJson(QJsonDocument::Compact)));
        ui->rescann_btn->setEnabled(true);
    });
    allowriter = true;
    writerTimer.setInterval(200);
    writerTimer.setSingleShot(true);
    connect(&writerTimer, &QTimer::timeout, this, [=]{allowriter = true;});
    connect(&timer1, &QTimer::timeout, this, &MainWindow::delay_change1);
    timer1.setInterval(3000);
    timer2.setInterval(3000);
    timer3.setInterval(3000);
    connect(&timer1, &QTimer::timeout, this, &MainWindow::delay_change1);
    connect(&timer2, &QTimer::timeout, this, &MainWindow::delay_change2);
    connect(&timer3, &QTimer::timeout, this, &MainWindow::tips_window_end);
    m_animation = new QPropertyAnimation(tips_window, "windowOpacity");
    m_animation->setDuration(800);
    m_animation->setStartValue(0.8);
    m_animation->setEndValue(0.0);
    m_animation->setEasingCurve(QEasingCurve::OutQuart);
    connect(m_animation, &QPropertyAnimation::finished, [=](){
        tips_window->hide();
    });
    ser = new QSerialPort;
    SerialPort_link = false;
    databits = QSerialPort::DataBits::Data8;
    parity = QSerialPort::Parity::NoParity;
    stopbits = QSerialPort::StopBits::OneStop;
    flowcontrol = QSerialPort::FlowControl::NoFlowControl;
    connect(ser, &QSerialPort::errorOccurred, this, &MainWindow::handleSerialError);
    connect(ui->link_btn,&QPushButton::clicked, this,&MainWindow::link_btn_clicked);
    connect(ui->reload_btn,&QPushButton::clicked, this,[=]{
        ui->port_id->clear();
        ports_list = QSerialPortInfo::availablePorts();
        for (const QSerialPortInfo& portInfo :ports_list) {
            ui->port_id->addItem(portInfo.portName() + ":" + portInfo.description(), portInfo.portName());
        }
    });
    file_path = "";
    index = -1;
    sleep_time = 0.1;
    list_clear();
    L0 = 500;
    L1 = 500;
    L2 = 500;
    R0 = 500;
    R1 = 500;
    R2 = 500;
    last_L0 = L0;
    last_L1 = L1;
    last_L2 = L2;
    last_R0 = R0;
    last_R1 = L1;
    last_R2 = R2;
    insert_max = 0;
    insert_min = 0;
    connect(ui->save_btn,&QPushButton::clicked,this,[=]{if (!config_L0.isEmpty()){save_scripter();}});
    connect(ui->regenerate_btn,&QPushButton::clicked,this,[=]{regenerate_scripter();});
    connect(ui->folder_btn,&QPushButton::clicked,this,[=]{
        if (file_path != ""){
        QFileInfo fileInfo(file_path);
        QDesktopServices::openUrl(QUrl::fromLocalFile(fileInfo.absolutePath()));
            }
        ;});
}


void MainWindow::convertsr6sToFunscript(const QList<int>& sr6s, const QString& file_path) {
    // 创建基础JSON结构（基于示例模板）
    QJsonObject root;
    QJsonArray actions;
    QJsonObject metadata;

    // 填充基础信息（根据示例模板）
    metadata.insert("bookmarks", QJsonArray());
    metadata.insert("chapters", QJsonArray());
    metadata.insert("creator", "");
    metadata.insert("description", "");
    metadata.insert("license", "");
    metadata.insert("notes", "");
    metadata.insert("performers", QJsonArray());
    metadata.insert("script_url", "");
    metadata.insert("tags", QJsonArray());
    metadata.insert("title", "");
    metadata.insert("type", "basic");
    metadata.insert("video_url", "");

    // 转换actions数组
    for (int i = 0; i < sr6s.size(); ++i) {
        // 时间计算：index * 0.1秒 → 毫秒
        int at_ms = static_cast<int>(i * 100.0); // 0.1秒 = 100ms

        // 数值映射：0-999 → 0%-99%
        if (sr6s[i] == -1){continue;}
        double pos_percent = (sr6s[i] / 999.0) * 100.0;
        int pos = qRound(pos_percent); // 四舍五入

        // 添加动作点
        QJsonObject action;
        action["at"] = at_ms;
        action["pos"] = qBound(0, pos, 100); // 确保范围0-100
        actions.append(action);
    }

    // 计算 duration（向上取整到整数秒）
    double duration_sec_raw = L0s.isEmpty() ? 0.0 : (L0s.size() - 1) * 0.1;
    int duration_sec = static_cast<int>(std::ceil(duration_sec_raw));
    metadata.insert("duration", duration_sec);


    root.insert("actions", actions);
    root.insert("inverted", false);
    root.insert("metadata", metadata);
    root.insert("range", 100);
    root.insert("version", "1.0");

    // 保存文件
    QFile file(file_path);
    if (file.open(QIODevice::WriteOnly)) {
        QJsonDocument doc(root);
        file.write(doc.toJson());
        file.close();
    }
}

void MainWindow::new_connected(){
    socket = server->nextPendingConnection();
    client_address = socket->peerAddress().toString();
    ui->wait_for_client_link->setText("link from :"+  client_address);
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::server_read);
    connect(socket, &QTcpSocket::disconnected, this, &MainWindow::server_disconnected);
}

void MainWindow::server_read(){
    QString data = socket->readAll();
    if (data != ""){        
        QStringList datalist = data.split("|");
        if (file_path != datalist[0]){ //加载了新场景
            new_version = false;
            QString path = datalist[0];
            file_path = datalist[0];
            QString scence_path = path.replace("KK_osr_sr6_link","Studio/scene").replace(".txt",".png");
            QPixmap img = QPixmap((scence_path));
            ui->scene->setPixmap(img);
            list_clear();
            QFile file(file_path);
            QString search_str = "/UserData/KK_osr_sr6_link/";
            int index = file_path.indexOf(search_str);
            if (index != -1) {
                if (ui->game_root->text() != ""){
                    QString extracted_str = file_path.left(index);
                    file_path = file_path.replace(extracted_str,ui->game_root->text());
                }
            } else {
                return;
            }
            qDebug() << file_path;
            if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                return;
            }
            QTextStream in(&file);//读取新场景文件的txt文件
            bool firstline = true;
            while (!in.atEnd()) {
                QString line = in.readLine();
                if (firstline){
                    if (line == "New"){
                        firstline = false;
                        ui->scripter_part_list->blockSignals(true);
                        ui->girl_list->blockSignals(true);
                        ui->boy_list->blockSignals(true);
                        ui->scripter_part_list->clear();
                        ui->girl_list->clear();
                        ui->boy_list->clear();
                        ui->scripter_part_list->blockSignals(false);
                        ui->girl_list->blockSignals(false);
                        ui->boy_list->blockSignals(false);
                        lovemaking_datas.clear();
                        sceneParts.clear();
                        new_version = true;
                        continue;
                    }
                    else{
                        tips->setText("Please use the latest version to re-collect the action data, the script file generated by the old version remains unaffected.");
                        tips_window_start();
                        }
                }
                if (new_version){
                    if (line.contains("chaF_")){
                        QStringList charas = line.split("-");
                        ui->girl_list->blockSignals(true);
                        ui->boy_list->blockSignals(true);
                        if (ui->girl_list->findText(charas[0]) == -1) {
                            ui->girl_list->addItem(charas[0]);
                            ui->girl_list->setCurrentIndex(ui->girl_list->count()-1);
                        }
                        if (ui->boy_list->findText(charas[1]) == -1) {
                            ui->boy_list->addItem(charas[1]);
                            ui->boy_list->setCurrentIndex(ui->boy_list->count()-1);
                        }
                        ui->girl_list->blockSignals(false);
                        ui->boy_list->blockSignals(false);
                        Lovemaking_data lovemaking_data;
                        lovemaking_data.inserts = {};lovemaking_data.surges = {};lovemaking_data.sways = {};lovemaking_data.twists = {};lovemaking_data.pitchs = {};lovemaking_data.rolls = {};
                        lovemaking_data.blowjob_inserts = {};lovemaking_data.blowjob_surges = {};lovemaking_data.blowjob_sways = {};lovemaking_data.blowjob_twists = {};lovemaking_data.blowjob_pitchs = {};lovemaking_data.blowjob_rolls = {};
                        lovemaking_data.breastsex_inserts = {};lovemaking_data.breastsex_surges = {};lovemaking_data.breastsex_sways = {};lovemaking_data.breastsex_twists = {};lovemaking_data.breastsex_pitchs = {};lovemaking_data.breastsex_rolls = {};
                        lovemaking_data.handjobL_inserts = {};lovemaking_data.handjobL_surges = {};lovemaking_data.handjobL_sways = {};lovemaking_data.handjobL_twists = {};lovemaking_data.pitchs = {};lovemaking_data.rolls = {};
                        lovemaking_data.charas_name = line;
                        lovemaking_datas.append(lovemaking_data);
                        continue;
                    }
                    Lovemaking_data& lovemaking_data = lovemaking_datas[lovemaking_datas.count()-1];
                    QStringList lines = line.split("/");
                    lovemaking_data.inserts.append(lines[0].toFloat());
                    lovemaking_data.surges.append(lines[1].toFloat());
                    lovemaking_data.sways.append(lines[2].toFloat());
                    lovemaking_data.twists.append(lines[3].toFloat());
                    lovemaking_data.rolls.append(lines[4].toFloat());
                    lovemaking_data.pitchs.append(lines[5].toFloat());
                    lovemaking_data.bodywidth = lines[8].toFloat();
                    lovemaking_data.blowjob_inserts.append(lines[9].toFloat());
                    lovemaking_data.blowjob_sways.append(lines[10].toFloat());
                    lovemaking_data.blowjob_surges.append(lines[11].toFloat());
                    lovemaking_data.blowjob_twists.append(lines[12].toFloat());
                    lovemaking_data.blowjob_rolls.append(lines[13].toFloat());
                    lovemaking_data.blowjob_pitchs.append(lines[14].toFloat());
                    lovemaking_data.breastsex_inserts.append(lines[15].toFloat());
                    lovemaking_data.breastsex_surges.append(lines[16].toFloat());
                    lovemaking_data.breastsex_sways.append(lines[17].toFloat());
                    lovemaking_data.breastsex_twists.append(lines[18].toFloat());
                    lovemaking_data.breastsex_rolls.append(lines[19].toFloat());
                    lovemaking_data.breastsex_pitchs.append(lines[20].toFloat());
                    lovemaking_data.handjobL_inserts.append(lines[21].toFloat());
                    lovemaking_data.handjobL_surges.append(lines[22].toFloat());
                    lovemaking_data.handjobL_sways.append(lines[23].toFloat());
                    lovemaking_data.handjobL_twists.append(lines[24].toFloat());
                    lovemaking_data.handjobL_rolls.append(lines[25].toFloat());
                    lovemaking_data.handjobL_pitchs.append(lines[26].toFloat());
                    lovemaking_data.handjobR_inserts.append(lines[27].toFloat());
                    lovemaking_data.handjobR_surges.append(lines[28].toFloat());
                    lovemaking_data.handjobR_sways.append(lines[29].toFloat());
                    lovemaking_data.handjobR_twists.append(lines[30].toFloat());
                    lovemaking_data.handjobR_rolls.append(lines[31].toFloat());
                    lovemaking_data.handjobR_pitchs.append(lines[32].toFloat());
                }
            }
            if (new_version){
                inserts = lovemaking_datas[0].inserts;
                surges = lovemaking_datas[0].surges;
                sways = lovemaking_datas[0].sways;
                twists = lovemaking_datas[0].twists;
                rolls = lovemaking_datas[0].rolls;
                pitchs = lovemaking_datas[0].pitchs;
                if (inserts.isEmpty()){return;}
                insert_max = *std::max_element(inserts.begin(), inserts.end());
                insert_min = *std::min_element(inserts.begin(), inserts.end());
                float surge_sum = std::accumulate(surges.begin(), surges.end(), 0.0f);
                float sway_sum = std::accumulate(sways.begin(), sways.end(), 0.0f);
                surge_offset = surge_sum / surges.count();
                sway_offset = sway_sum / sways.count();
                for (int i = 0; i < inserts.count(); ++i){
                    L0 = (999 / (insert_min - insert_max))*inserts[i] - (999 / (insert_min - insert_max))*insert_max;
                    if (L0 < 0){L0 = 0;}else if (L0 > 999){L0 = 999;}
                    L0s.append(L0);
                    L1 = (999-0)/2 - (int)((surges[i] - surge_offset) * (999-0) / bodywidth / 2);
                    if (L1 < 0){L1 = 0;}else if (L1 > 999){L1 = 999;}
                    L1s.append(L1);
                    L2 = (999-0)/2 - (int)((sways[i] - sway_offset) * (999-0) / bodywidth / 2);
                    if (L2 < 0){L2 = 0;}else if (L2 > 999){L2 = 999;}
                    L2s.append(L2);
                    if (R0 < 0){R0 = 0;}else if (R0 > 999){R0 = 999;}
                    R0s.append(R0);
                    R0 = (999-0)/2 + (int)(twists[i] * 11.1);
                    R1 = (999+0)/2 - (int)(rolls[i] * 11.1);
                    if (R1 < 0){R1 = 0;}else if (R1 > 999){R1 = 999;}
                    R1s.append(R1);
                    R2 = (999-0)/2 + (int)(pitchs[i] * 11.1 / 2);
                    if (R2 < 0){R2 = 0;}else if (R2 > 999){R2 = 999;}
                    R2s.append(R2);
                }
            }
            QString get_path = file_path;
            get_path = get_path.replace(".txt",".sr6script");
            QFileInfo fileInfo(get_path);
            if (fileInfo.exists()) {
                L0s.clear();
                L1s.clear();
                L2s.clear();
                R0s.clear();
                R1s.clear();
                R2s.clear();
                scripter_L0 = new QFile(get_path);
                scripter_L0->open(QIODevice::ReadWrite);
                QJsonDocument loadDocL0(QJsonDocument::fromJson(scripter_L0->readAll()));
                if (!loadDocL0.isObject()) {
                    qWarning() << "not availability sr6script:" << scripter_L0;
                    return;
                }
                config_L0 = loadDocL0.object();
                if (config_L0.contains("actions") && config_L0["actions"].isArray()) {
                    QJsonArray actions = config_L0["actions"].toArray();
                    for (int i = 0; i < actions.size(); ++i) {
                        int value = actions[i].toInt();
                        L0s.append(value);

                    }
                    silderL0->maxvalue = config_L0["maxvalue"].toInt();
                    silderL0->minvalue = config_L0["minvalue"].toInt();
                }
                scripter_L0->close();
                get_path = get_path.replace(".sr6script",".surge.sr6script");
                scripter_L1 = new QFile(get_path);
                scripter_L1->open(QIODevice::ReadWrite);
                QJsonDocument loadDocL1(QJsonDocument::fromJson(scripter_L1->readAll()));
                if (!loadDocL1.isObject()) {
                    qWarning() << "not availability sr6script:" << scripter_L1;
                    return;
                }
                config_L1 = loadDocL1.object();
                if (config_L1.contains("actions") && config_L1["actions"].isArray()) {
                    QJsonArray actions = config_L1["actions"].toArray();
                    for (int i = 0; i < actions.size(); ++i) {
                        int value = actions[i].toInt();
                        L1s.append(value);
                    }
                    silderL1->maxvalue = config_L1["maxvalue"].toInt();
                    silderL1->minvalue = config_L1["minvalue"].toInt();
                }
                scripter_L1->close();
                get_path = get_path.replace(".surge.sr6script",".sway.sr6script");
                scripter_L2 = new QFile(get_path);
                scripter_L2->open(QIODevice::ReadWrite);
                QJsonDocument loadDocL2(QJsonDocument::fromJson(scripter_L2->readAll()));
                if (!loadDocL2.isObject()) {
                    qWarning() << "not availability sr6script:" << scripter_L2;
                    return;
                }
                config_L2 = loadDocL2.object();
                if (config_L2.contains("actions") && config_L2["actions"].isArray()) {
                    QJsonArray actions = config_L2["actions"].toArray();
                    for (int i = 0; i < actions.size(); ++i) {
                        int value = actions[i].toInt();
                        L2s.append(value);
                    }
                    silderL2->maxvalue = config_L2["maxvalue"].toInt();
                    silderL2->minvalue = config_L2["minvalue"].toInt();
                }
                scripter_L2->close();
                get_path = get_path.replace(".sway.sr6script",".twist.sr6script");
                scripter_R0 = new QFile(get_path);
                scripter_R0->open(QIODevice::ReadWrite);
                QJsonDocument loadDocR0(QJsonDocument::fromJson(scripter_R0->readAll()));
                config_R0 = loadDocR0.object();
                if (config_R0.contains("actions") && config_R0["actions"].isArray()) {
                    QJsonArray actions = config_R0["actions"].toArray();
                    for (int i = 0; i < actions.size(); ++i) {
                        int value = actions[i].toInt();
                        R0s.append(value);
                    }
                    silderR0->maxvalue = config_R0["maxvalue"].toInt();
                    silderR0->minvalue = config_R0["minvalue"].toInt();
                }
                scripter_R0->close();
                get_path = get_path.replace(".twist.sr6script",".roll.sr6script");
                scripter_R1 = new QFile(get_path);
                scripter_R1->open(QIODevice::ReadWrite);
                QJsonDocument loadDocR1(QJsonDocument::fromJson(scripter_R1->readAll()));
                config_R1 = loadDocR1.object();
                if (config_R1.contains("actions") && config_R1["actions"].isArray()) {
                    QJsonArray actions = config_R1["actions"].toArray();
                    for (int i = 0; i < actions.size(); ++i) {
                        int value = actions[i].toInt();
                        R1s.append(value);
                    }
                    silderR1->maxvalue = config_R1["maxvalue"].toInt();
                    silderR1->minvalue = config_R1["minvalue"].toInt();
                }
                scripter_R1->close();
                get_path = get_path.replace(".roll.sr6script",".pitch.sr6script");
                scripter_R2 = new QFile(get_path);
                scripter_R2->open(QIODevice::ReadWrite);
                QJsonDocument loadDocR2(QJsonDocument::fromJson(scripter_R2->readAll()));
                config_R2 = loadDocR2.object();
                if (config_R2.contains("actions") && config_R2["actions"].isArray()) {
                    QJsonArray actions = config_R1["actions"].toArray();
                    for (int i = 0; i < actions.size(); ++i) {
                        int value = actions[i].toInt();
                        R2s.append(value);
                    }
                    silderR2->maxvalue = config_R2["maxvalue"].toInt();
                    silderR2->minvalue = config_R2["minvalue"].toInt();
                }
                scripter_R2->close();
                get_path = get_path.replace(".pitch.sr6script",".sr6cfg");
                scence = new QFile(get_path);
                scence->open(QIODevice::ReadWrite);
                QJsonDocument loadDoc = QJsonDocument::fromJson(scence->readAll());
                QJsonArray sceneArray = loadDoc.array();
                if (!loadDoc.isArray()) {
                    qWarning() << "File content is not a JSON array!";
                    return;
                }
                else{
                    sceneParts.clear();
                    for (const QJsonValue& value : sceneArray) {
                        if (value.isObject()) {
                            QJsonObject obj = value.toObject();
                            ScenePart part;
                            part.part = obj["part"].toInt();
                            part.lovemaking_mode = obj["lovemaking mode"].toString();
                            part.charas = obj["charas"].toString();
                            sceneParts.append(part);
                        }
                    }
                }
            }
            else{
                scripter3L0->values = L0s;
                scripter3L1->values = L1s;
                scripter3L2->values = L2s;
                scripter3R0->values = R0s;
                scripter3R1->values = R1s;
                scripter3R2->values = R2s;
                overview_edit->values = L0s;
                ScenePart scenpart;
                scenpart.part = 0;
                scenpart.charas = ui->girl_list->itemText(0) + "-" + ui->boy_list->itemText(0);
                scenpart.lovemaking_mode = "normal";
                sceneParts.append(scenpart);
                save_scripter();
            }
            scripter3L0->values = L0s;
            scripter3L1->values = L1s;
            scripter3L2->values = L2s;
            scripter3R0->values = R0s;
            scripter3R1->values = R1s;
            scripter3R2->values = R2s;
            overview_edit->values = L0s;
            int i = 1;
            for (ScenePart part:sceneParts){
                if (i != 1){
                    overview_edit->split_lines.append(part.part);
                }
                ui->scripter_part_list->addItem("part"+QString::number(i));
                QStringList charas = part.charas.split("-");
                if (ui->girl_list->findText(charas[0]) == -1) {
                    ui->girl_list->addItem(charas[0]);
                    ui->girl_list->setCurrentIndex(ui->girl_list->count()-1);
                }
                if (ui->boy_list->findText(charas[1]) == -1) {
                    ui->boy_list->addItem(charas[1]);
                    ui->boy_list->setCurrentIndex(ui->boy_list->count()-1);
                }
                ui->lovemaking_mode_list->setCurrentText(part.lovemaking_mode);
                i++;
            }
            overview_edit->selected_part = 0;
            file.close();
        }
        index = datalist[1].toInt();
        sleep_time = datalist[2].toDouble();
        if (index+1 >= inserts.count()){return;}
        if (file_path != ""){
            L0 = scripter3L0->values[index];
            L1 = scripter3L1->values[index];
            L2 = scripter3L2->values[index];
            R0 = scripter3R0->values[index];
            R1 = scripter3R1->values[index];
            R2 = scripter3R2->values[index];
            L0s = scripter3L0->values;
            L1s = scripter3L1->values;
            L2s = scripter3L2->values;
            R0s = scripter3R0->values;
            R1s = scripter3R1->values;
            R2s = scripter3R2->values;
            overview_edit->selected_line = index;
            scripter3L0->selected_line = index;
            scripter3L1->selected_line = index;
            scripter3L2->selected_line = index;
            scripter3R0->selected_line = index;
            scripter3R1->selected_line = index;
            scripter3R2->selected_line = index;
            //
            if(ui->tabWidget_2->currentIndex()){
                for (int i=0;i <overview_edit->split_lines.count();i++){
                    if (index > overview_edit->split_lines[overview_edit->split_lines.count()-1]){
                        ui->scripter_part_list->setCurrentIndex(ui->scripter_part_list->count()-1);
                        ui->lovemaking_mode_list->setCurrentText(sceneParts[ui->scripter_part_list->count()-1].lovemaking_mode);
                        QStringList charas = sceneParts[ui->scripter_part_list->count()-1].charas.split("-");
                        ui->girl_list->setCurrentText(charas[0]);
                        ui->boy_list->setCurrentText(charas[1]);
                        break;
                    }
                    if (index <= overview_edit->split_lines[i]){
                        ui->scripter_part_list->setCurrentIndex(i);
                        ui->lovemaking_mode_list->setCurrentText(sceneParts[i].lovemaking_mode);
                        QStringList charas = sceneParts[i].charas.split("-");
                        ui->girl_list->setCurrentText(charas[0]);
                        ui->boy_list->setCurrentText(charas[1]);
                        break;
                    }
                }
            }
            //
            overview_edit->update();
            scripter3L0->update();
            scripter3L1->update();
            scripter3L2->update();
            scripter3R0->update();
            scripter3R1->update();
            scripter3R2->update();
            silderL0->update();
            silderL1->update();
            silderL2->update();
            silderR0->update();
            silderR1->update();
            silderR2->update();

            int sleep_time;
            int i;
            int intervaltime = 100;
            if (index>L0s.count()){return;}
            for (i = index+1;i < L0s.count() && i>=0 ;i++){
                if (L0s[i] != -1){
                    sleep_time = intervaltime*(i-index);
                    L0 = static_cast<double>(silderL0->maxvalue-silderL0->minvalue)/(999-0)*L0s[i] + silderL0->minvalue;
                    silderL0->value = L0;
                    break;
                }
            }
            if (L0!=-1 && last_L0 != L0 && ui->L0->isChecked()){
                last_L0 = L0;
                //qDebug() << "L0"+QString("%1").arg(L0, 3, 10, QChar('0')) +"I"+ QString::number(sleep_time) +"\r\n";
                if (SerialPort_link){
                    try{
                        ser->write(("L0"+QString("%1").arg(L0, 3, 10, QChar('0')) +"I"+ QString::number(sleep_time) +"\r\n").toLocal8Bit());
                    } catch (...) {
                        ser->close();
                        ui->link_btn->setStyleSheet(btn_sty5);
                        tips->setText("Serial close");
                        tips_window_start();
                        SerialPort_link = false;
                        return;
                    }
                }
                for (Device device:devices) {
                    for (int i = 0; i <= device.feature.count()-1;i++){
                        if (device.feature[i] == 0 && device.feature_enable[i] == 1){
                            if (device.work_way == "linearCmd" || device.work_way =="LinearCmd"){
                                sent_LinearCmd(i,device,sleep_time,L0);
                            }
                        }
                    }
                }
            }
            for (i = index+1;i < L1s.count() && i>=0 ;i++){
                if (L1s[i] != -1){
                    sleep_time = intervaltime*(i-index);
                    L1 = static_cast<double>(silderL1->maxvalue-silderL1->minvalue)/(999-0)*L1s[i] + silderL1->minvalue;
                    silderL1->value = L1;
                    break;
                }
            }
            if (L1!=-1 && last_L1 != L1 && ui->L1->isChecked()){
                last_L1 = L1;
                if (SerialPort_link){
                    try{
                        ser->write(("L1"+QString("%1").arg(L1, 3, 10, QChar('0')) +"I"+ QString::number(sleep_time) +"\r\n").toLocal8Bit());
                    } catch (...) {
                        ser->close();
                        ui->link_btn->setStyleSheet(btn_sty5);
                        tips->setText("Serial close");
                        tips_window_start();
                        SerialPort_link = false;
                        return;
                    }
                }
                for (Device device:devices) {
                    for (int i = 0; i <= device.feature.count()-1;i++){
                        if (device.feature[i] == 1 && device.feature_enable[i] == 1){
                            if (device.work_way == "linearCmd" || device.work_way =="LinearCmd"){
                                sent_LinearCmd(i,device,sleep_time,L1);
                            }
                        }
                    }
                }

            }
            for (i = index+1;i < L2s.count() && i>=0 ;i++){
                if (L2s[i] != -1){
                    sleep_time = intervaltime*(i-index);
                    L2 = static_cast<double>(silderL2->maxvalue-silderL2->minvalue)/(999-0)*L2s[i] + silderL2->minvalue;
                    silderL2->value = L2;
                    break;
                }
            }
            if (L2!=-1 && last_L1 != L2 && ui->L2->isChecked()){
                last_L2 = L2;
                if (SerialPort_link){
                    try{
                        ser->write(("L2"+QString("%1").arg(L2, 3, 10, QChar('0')) +"I"+ QString::number(sleep_time) +"\r\n").toLocal8Bit());
                    } catch (...) {
                        ser->close();
                        ui->link_btn->setStyleSheet(btn_sty5);
                        tips->setText("Serial close");
                        tips_window_start();
                        SerialPort_link = false;
                        return;
                    }
                }
                for (Device device:devices) {
                    for (int i = 0; i <= device.feature.count()-1;i++){
                        if (device.feature[i] == 2 && device.feature_enable[i] == 1){
                            if (device.work_way == "linearCmd" || device.work_way =="LinearCmd"){
                                sent_LinearCmd(i,device,sleep_time,L2);
                            }
                        }
                    }
                }

            }
            for (i = index+1;i < R0s.count() && i>=0 ;i++){
                if (R0s[i] != -1){
                    sleep_time = intervaltime*(i-index);
                    R0 = static_cast<double>(silderR0->maxvalue-silderR0->minvalue)/(999-0)*R0s[i] + silderR0->minvalue;
                    silderR0->value = R0;
                    break;
                }
            }
            if (R0!=-1 && last_R0 != R0 && ui->R0->isChecked()){
                last_R0 = R0;
                if (SerialPort_link){
                    try{
                        ser->write(("R0"+QString("%1").arg(R0, 3, 10, QChar('0')) +"I"+ QString::number(sleep_time) +"\r\n").toLocal8Bit());
                    } catch (...) {
                        ser->close();
                        ui->link_btn->setStyleSheet(btn_sty5);
                        tips->setText("Serial close");
                        tips_window_start();
                        SerialPort_link = false;
                        return;
                    }
                }
                for (Device device:devices) {
                    for (int i = 0; i <= device.feature.count()-1;i++){
                        if (device.feature[i] == 3 && device.feature_enable[i] == 1){
                            if (device.work_way == "linearCmd" || device.work_way =="LinearCmd"){
                                sent_LinearCmd(i,device,sleep_time,R0);
                            }
                        }
                    }
                }

            }
            for (i = index+1;i < R1s.count() && i>=0 ;i++){
                if (R1s[i] != -1){
                    sleep_time = intervaltime*(i-index);
                    R1 = static_cast<double>(silderR1->maxvalue-silderR1->minvalue)/(999-0)*R1s[i] + silderR1->minvalue;
                    silderR1->value = R1;
                    break;
                }
            }
            if (R1!=-1 && last_R1 != R1 && ui->R1->isChecked()){
                last_R1 = R1;
                if (SerialPort_link){
                    try{
                        ser->write(("R1"+QString("%1").arg(R1, 3, 10, QChar('0')) +"I"+ QString::number(sleep_time) +"\r\n").toLocal8Bit());
                    } catch (...) {
                        ser->close();
                        ui->link_btn->setStyleSheet(btn_sty5);
                        tips->setText("Serial close");
                        tips_window_start();
                        SerialPort_link = false;
                        return;
                    }
                }
                for (Device device:devices) {
                    for (int i = 0; i <= device.feature.count()-1;i++){
                        if (device.feature[i] == 4 && device.feature_enable[i] == 1){
                            if (device.work_way == "linearCmd" || device.work_way =="LinearCmd"){
                                sent_LinearCmd(i,device,sleep_time,R1);
                            }
                        }
                    }
                }

            }
            for (i = index+1;i < R2s.count() && i>=0 ;i++){
                if (R2s[i] != -1){
                    sleep_time = intervaltime*(i-index);
                    R2 = static_cast<double>(silderR2->maxvalue-silderR2->minvalue)/(999-0)*R2s[i] + silderR2->minvalue;
                    silderR2->value = R2;
                    break;
                }
            }
            if (R2!=-1 && last_R2 != R2 && ui->R2->isChecked()){
                last_R2 = R2;
                if (SerialPort_link){
                    try{
                        ser->write(("R2"+QString("%1").arg(R2, 3, 10, QChar('0')) +"I"+ QString::number(sleep_time) +"\r\n").toLocal8Bit());
                    } catch (...) {
                        ser->close();
                        ui->link_btn->setStyleSheet(btn_sty5);
                        tips->setText("Serial close");
                        tips_window_start();
                        SerialPort_link = false;
                        return;
                    }
                }
                for (Device device:devices) {
                    for (int i = 0; i <= device.feature.count()-1;i++){
                        if (device.feature[i] == 5 && device.feature_enable[i] == 1){
                            if (device.work_way == "linearCmd" || device.work_way =="LinearCmd"){
                                sent_LinearCmd(i,device,sleep_time,R2);
                            }
                        }
                    }
                }

            }
        //qDebug() << "L0:"+QString::number(L0) << "L1:"+QString::number(L1) << "L2:"+QString::number(L2) << "L2:"+QString::number(L2) << "R0:"+QString::number(R0) << "R1:"+QString::number(R1) << "R2:"+QString::number(R2);
        return;

        }
    }
}



void MainWindow::server_disconnected(){
    ui->wait_for_client_link->setText("wait server start");
    socket->abort();
}


void MainWindow::run_btn_clicked(){
    if(!build_server){
        try {
            qDebug() << "wait for client link";
            qDebug() << server_ip;
            qDebug() << port;
            server->listen(QHostAddress(server_ip),quint16(port));
            build_server = true;
            ui->run_btn->setStyleSheet(btn_sty3);
            ui->wait_for_client_link->setText("wait for client link");
        } catch (...) {
            socket->abort();
            server->close();
            ui->run_btn->setStyleSheet(btn_sty4);
            ui->run_btn->setEnabled(false);
            tips->setText("build server fail,check other available port");
            tips_window_start();
        }
    }
    else{
        build_server = false;
        ui->run_btn->setStyleSheet(btn_sty1);
        socket->abort();
        server->close();
        ui->wait_for_client_link->setText("wait server start");
    }

}

void MainWindow::delay_change1(){
    ui->run_btn->setEnabled(true);
    ui->run_btn->setStyleSheet(btn_sty1);
    timer1.stop();
}

void MainWindow::delay_change2(){
    ui->link_btn->setEnabled(true);
    ui->link_btn->setStyleSheet(btn_sty5);
    timer2.stop();
}

void MainWindow::tips_window_init(){
    tips_window = new QWidget(this);
    tips_layout = new QHBoxLayout;
    tips = new QLabel;
    QPalette pe;
    pe.setColor(QPalette::WindowText,Qt::black);
    tips->setAlignment(Qt :: AlignCenter);
    tips->setPalette(pe);
    tips_layout->setContentsMargins(0,0,0,0);
    tips_layout->setSpacing(0);
    tips_window->setLayout(tips_layout);
    tips_window->layout()->addWidget(tips);
    tips_window->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);
    tips_window->setWindowModality(Qt::NonModal);
    tips_window->setWindowOpacity(0.8);
    tips_window->setAttribute(Qt::WA_TranslucentBackground);
    tips_window->hide();
}


void MainWindow::tips_window_start(){
    int width = this->width() / 1.5;
    int height = this->height() / 35;
    tips_window->setWindowOpacity(0.8);
    tips_window->setFixedSize(width,height);
    QPoint mainWindowPos = this->mapToGlobal(QPoint(0, 0));
    int tips_windowX = mainWindowPos.x() + (this->width() - width) / 2;
    int tips_windowY = mainWindowPos.y() + this->height()-ui->bottomBar->height()-height;
    tips_window->move(tips_windowX, tips_windowY);
    QString radius = QString::number(height/2);
    tips_window->setStyleSheet("background-color: rgb(255, 255, 255);border: none;border-radius:"+radius+"px;"
                             "QLabel{background-color: rgba(255, 255, 255,0.5);border: none;border-radius:"+radius+"px;}");
    tips_window->show();
    timer3.start();
}


void MainWindow::tips_window_end(){
    timer3.stop();
    m_animation->start();
}

void MainWindow::link_btn_clicked(){
    if (!SerialPort_link){
        ser->setPort(ports_list[port_id]);
        ser->setBaudRate(baudrate);
        ser->setDataBits(databits);
        ser->setParity(parity);
        ser->setStopBits(stopbits);
        ser->setFlowControl(flowcontrol);
        if (!ser->open(QIODevice::ReadWrite)) {
            ui->link_btn->setStyleSheet(btn_sty7);
            tips->setText("Serial link fail");
            ui->link_btn->setEnabled(false);
            tips_window_start();
            timer2.start();
        }
        else{
            ui->link_btn->setStyleSheet(btn_sty6);
            tips->setText("Serial link succeed");
            tips_window_start();
            SerialPort_link = true;
        }
    }
    else{
        ser->close();
        ui->link_btn->setStyleSheet(btn_sty5);
        tips->setText("Serial close");
        tips_window_start();
        SerialPort_link = false;
    }
}

void MainWindow::handleSerialError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::NoError) {
        ser->close();
        ui->link_btn->setStyleSheet(btn_sty5);
        tips->setText("Serial close");
        tips_window_start();
        SerialPort_link = false;
        return;
    }
}

void MainWindow::save_scripter()
{
    L0s = scripter3L0 ->values;
    L1s = scripter3L1 ->values;
    L2s = scripter3L2 ->values;
    R0s = scripter3R0 ->values;
    R1s = scripter3R1 ->values;
    R2s = scripter3R2 ->values;
    QString get_path = file_path;
    get_path = get_path.replace(".txt",".sr6script");
    scripter_L0 = new QFile(get_path);
    config_L0 =  QJsonObject();
    QJsonArray Array_L0;
    for (int value:L0s){
        Array_L0.append(value);
    }
    config_L0["actions"] = Array_L0;
    config_L0["maxvalue"] = 999;
    config_L0["minvalue"] = 0;
    silderL0->maxvalue = config_L0["maxvalue"].toInt();
    silderL0->minvalue = config_L0["minvalue"].toInt();
    QJsonDocument documentL0(config_L0);
    if (scripter_L0->open(QIODevice::WriteOnly)) {
        scripter_L0->write(documentL0.toJson(QJsonDocument::Indented));
        scripter_L0->close();
    }
    get_path = get_path.replace(".sr6script",".surge.sr6script");
    scripter_L1 = new QFile(get_path);
    config_L1 =  QJsonObject();
    QJsonArray Array_L1;
    for (int value:L1s){
        Array_L1.append(value);
    }
    config_L1["actions"] = Array_L1;
    config_L1["maxvalue"] = 999;
    config_L1["minvalue"] = 0;
    silderL1->maxvalue = config_L1["maxvalue"].toInt();
    silderL1->minvalue = config_L1["minvalue"].toInt();
    QJsonDocument documentL1(config_L1);
    if (scripter_L1->open(QIODevice::WriteOnly)) {
        scripter_L1->write(documentL1.toJson(QJsonDocument::Indented));
        scripter_L1->close();
    }
    get_path = get_path.replace(".surge.sr6script",".sway.sr6script");
    scripter_L2 = new QFile(get_path);
    config_L2 =  QJsonObject();
    QJsonArray Array_L2;
    for (int value:L2s){
        Array_L2.append(value);
    }
    config_L2["actions"] = Array_L2;
    config_L2["maxvalue"] = 999;
    config_L2["minvalue"] = 0;
    silderL2->maxvalue = config_L2["maxvalue"].toInt();
    silderL2->minvalue = config_L2["minvalue"].toInt();
    QJsonDocument documentL2(config_L2);
    if (scripter_L2->open(QIODevice::WriteOnly)) {
        scripter_L2->write(documentL2.toJson(QJsonDocument::Indented));
        scripter_L2->close();
    }
    get_path = get_path.replace(".sway.sr6script",".twist.sr6script");
    scripter_R0 = new QFile(get_path);
    config_R0 =  QJsonObject();
    QJsonArray Array_R0;
    for (int value:R0s){
        Array_R0.append(value);
    }
    config_R0["actions"] = Array_R0;
    config_R0["maxvalue"] = 999;
    config_R0["minvalue"] = 0;
    silderR0->maxvalue = config_R0["maxvalue"].toInt();
    silderR0->minvalue = config_R0["minvalue"].toInt();
    QJsonDocument documentR0(config_R0);
    if (scripter_R0->open(QIODevice::WriteOnly)) {
        scripter_R0->write(documentR0.toJson(QJsonDocument::Indented));
        scripter_R0->close();
    }
    get_path = get_path.replace(".twist.sr6script",".roll.sr6script");
    scripter_R1 = new QFile(get_path);
    config_R1 =  QJsonObject();
    QJsonArray Array_R1;
    for (int value:R1s){
        Array_R1.append(value);
    }
    config_R1["actions"] = Array_R1;
    config_R1["maxvalue"] = 999;
    config_R1["minvalue"] = 0;
    silderR1->maxvalue = config_R1["maxvalue"].toInt();
    silderR1->minvalue = config_R1["minvalue"].toInt();
    QJsonDocument documentR1(config_R1);
    if (scripter_R1->open(QIODevice::WriteOnly)) {
        scripter_R1->write(documentR1.toJson(QJsonDocument::Indented));
        scripter_R1->close();
    }
    get_path = get_path.replace(".roll.sr6script",".pitch.sr6script");
    scripter_R2 = new QFile(get_path);
    config_R2 =  QJsonObject();
    QJsonArray Array_R2;
    for (int value:R2s){
        Array_R2.append(value);
    }
    config_R2["actions"] = Array_R2;
    config_R2["maxvalue"] = 999;
    config_R2["minvalue"] = 0;
    silderR2->maxvalue = config_R2["maxvalue"].toInt();
    silderR2->minvalue = config_R2["minvalue"].toInt();
    QJsonDocument documentR2(config_R2);
    if (scripter_R2->open(QIODevice::WriteOnly)) {
        scripter_R2->write(documentR2.toJson(QJsonDocument::Indented));
        scripter_R2->close();
    }
    get_path = get_path.replace(".pitch.sr6script",".sr6cfg");
    scence = new QFile(get_path);
    QJsonArray sceneArray;
    for (const ScenePart& part : sceneParts) {
        QJsonObject obj;
        obj["part"] = part.part;
        obj["lovemaking mode"] = part.lovemaking_mode;
        obj["charas"] = part.charas;
        sceneArray.append(obj);
    }
    QJsonDocument saveDoc(sceneArray);
    if (scence->open(QIODevice::WriteOnly)) {
        scence->write(saveDoc.toJson());
        scence->close();
    }

}


void MainWindow::list_clear(){
    inserts.clear();
    surges.clear();
    sways.clear();
    twists.clear();
    pitchs.clear();
    rolls.clear();
    blowjob_inserts.clear();
    blowjob_surges.clear();
    blowjob_sways.clear();
    blowjob_twists.clear();
    blowjob_pitchs.clear();
    blowjob_rolls.clear();
    breastsex_inserts.clear();
    breastsex_surges.clear();
    breastsex_sways.clear();
    breastsex_twists.clear();
    breastsex_pitchs.clear();
    breastsex_rolls.clear();
    handjobL_inserts.clear();
    handjobL_surges.clear();
    handjobL_sways.clear();
    handjobL_twists.clear();
    handjobL_pitchs.clear();
    handjobL_rolls.clear();
    handjobR_inserts.clear();
    handjobR_surges.clear();
    handjobR_sways.clear();
    handjobR_twists.clear();
    handjobR_pitchs.clear();
    handjobR_rolls.clear();
    L0s.clear();
    L1s.clear();
    L2s.clear();
    R0s.clear();
    R1s.clear();
    R2s.clear();
}

void MainWindow::regenerate_scripter()
{

}

void MainWindow::copy_values(QList<int> values,QList<int> index)
{
    scripter3L0->copy_values = values;
    scripter3L1->copy_values = values;
    scripter3L2->copy_values = values;
    scripter3R0->copy_values = values;
    scripter3R1->copy_values = values;
    scripter3R2->copy_values = values;
    scripter3L0->copy_values_indexs = index;
    scripter3L1->copy_values_indexs = index;
    scripter3L2->copy_values_indexs = index;
    scripter3R0->copy_values_indexs = index;
    scripter3R1->copy_values_indexs = index;
    scripter3R2->copy_values_indexs = index;
}

void MainWindow::setplaytime(int index){
    scripter3L0->selected_line = index;
    scripter3L1->selected_line = index;
    scripter3L2->selected_line = index;;
    scripter3R0->selected_line = index;
    scripter3R1->selected_line = index;
    scripter3R2->selected_line = index;
    if (allowriter){
        try {
            socket->write("1:"+QString::number(index).toLocal8Bit());
            socket->flush();
        } catch (...) {
        }
        allowriter = false;
        writerTimer.start();       
    }
    else{
        return;
    }
    if(ui->tabWidget_2->currentIndex()){
        for (int i=0;i <overview_edit->split_lines.count();i++){
            if (index > overview_edit->split_lines[overview_edit->split_lines.count()-1]){
                ui->scripter_part_list->setCurrentIndex(ui->scripter_part_list->count()-1);
                ui->lovemaking_mode_list->setCurrentText(sceneParts[ui->scripter_part_list->count()-1].lovemaking_mode);
                QStringList charas = sceneParts[ui->scripter_part_list->count()-1].charas.split("-");
                ui->girl_list->setCurrentText(charas[0]);
                ui->boy_list->setCurrentText(charas[1]);
                break;
            }
            if (index <= overview_edit->split_lines[i]){
                ui->scripter_part_list->setCurrentIndex(i);
                ui->lovemaking_mode_list->setCurrentText(sceneParts[i].lovemaking_mode);
                QStringList charas = sceneParts[i].charas.split("-");
                ui->girl_list->setCurrentText(charas[0]);
                ui->boy_list->setCurrentText(charas[1]);
                break;
            }
        }
    }
    this->update();
}


void MainWindow::set_play(){
    if (allowriter){
        try {
            socket->write("0:");
            socket->flush();
        } catch (...) {
        }
        allowriter = false;
        writerTimer.start();
    }
    else{
        return;
    }
    this->update();
}



void MainWindow::rebuildtimes3(QList<int> rebuild_times){
    QObject* sender = QObject::sender();
    update_list(sender,ui->lovemaking_mode_list->currentIndex(),rebuild_times);
}



void MainWindow::update_list(QObject* sender,int way,QList<int> rebuild_times){
    QList<float> _inserts;
    QList<float> _surges;
    QList<float> _sways;
    QList<float> _twists;
    QList<float> _rolls;
    QList<float> _pitchs;
    if (way == 0){
        _inserts = inserts;
        _surges = surges;
        _sways = sways;
        _twists = twists;
        _rolls = rolls;
        _pitchs = pitchs;
    }
    else if (way == 1){
        _inserts = blowjob_inserts;
        _surges = blowjob_surges;
        _sways = blowjob_sways;
        _twists = blowjob_twists;
        _rolls = blowjob_rolls;
        _pitchs = blowjob_pitchs;
    }
    else if (way == 2){
        _inserts = breastsex_inserts;
        _surges = breastsex_surges;
        _sways = breastsex_sways;
        _twists = breastsex_twists;
        _rolls = breastsex_rolls;
        _pitchs = breastsex_pitchs;
    }
    else if (way == 3){
        _inserts = handjobL_inserts;
        _surges = handjobL_surges;
        _sways = handjobL_sways;
        _twists = handjobL_twists;
        _rolls = handjobL_rolls;
        _pitchs = handjobL_pitchs;
    }
    else if (way == 4){
        _inserts = handjobR_inserts;
        _surges = handjobR_surges;
        _sways = handjobR_sways;
        _twists = handjobR_twists;
        _rolls = handjobR_rolls;
        _pitchs = handjobR_pitchs;
    }
    if (_inserts.count() == 0 ){return;}
    if (!ui->rebuild_all_checkbox->isChecked()) {
        if (sender == scripter3L0){
            scripter3L0->record_values.append(scripter3L0->values);
        }
        else if (sender == scripter3L1){
            scripter3L1->record_values.append(scripter3L1->values);
        }
        else if (sender == scripter3L2){
            scripter3L2->record_values.append(scripter3L2->values);
        }
        else if (sender == scripter3R0){
            scripter3R0->record_values.append(scripter3R0->values);
        }
        else if (sender == scripter3R1){
            scripter3R1->record_values.append(scripter3R1->values);
        }
        else if (sender == scripter3R2){
            scripter3R2->record_values.append(scripter3R2->values);
        }
    } else {
        scripter3L0->record_values.append(scripter3L0->values);
        scripter3L1->record_values.append(scripter3L1->values);
        scripter3L2->record_values.append(scripter3L2->values);
        scripter3R0->record_values.append(scripter3R0->values);
        scripter3R1->record_values.append(scripter3R1->values);
        scripter3R2->record_values.append(scripter3R2->values);
    }
    if (file_path != ""){
        QList<float> rebuild_inserts = {};
        QList<float> rebuild_surges = {};
        QList<float> rebuild_sways = {};
        QList<float> rebuild_twists = {};
        QList<float> rebuild_pitchs = {};
        QList<float> rebuild_rolls = {};
        for (int index:rebuild_times){
            rebuild_inserts.append(_inserts[index]);
            rebuild_surges.append(_surges[index]);
            rebuild_sways.append(_sways[index]);
            rebuild_twists.append(_twists[index]);
            rebuild_rolls.append(_rolls[index]);
            rebuild_pitchs.append(_pitchs[index]);
        }
        float rebuild_insert_max = *std::max_element(rebuild_inserts.begin(), rebuild_inserts.end());
        float rebuild_insert_min = *std::min_element(rebuild_inserts.begin(), rebuild_inserts.end());
        float surge_sum = *std::max_element(rebuild_surges.begin(), rebuild_surges.end());
        float surge_offset = surge_sum / rebuild_surges.count();
        float sway_sum = *std::max_element(rebuild_sways.begin(), rebuild_sways.end());
        float sway_offset = sway_sum / rebuild_sways.count();

        for (int i = 0; i < rebuild_inserts.count(); ++i){
            int L0 = (999 / (rebuild_insert_min - rebuild_insert_max))*rebuild_inserts[i] - (999 / (rebuild_insert_min - rebuild_insert_max))*rebuild_insert_max;
            if (L0 < 0){L0 = 0;}else if (L0 > 999){L0 = 999;}

            int L1 = (999-0)/2 - (int)((rebuild_surges[i] - surge_offset) * (999-0) / bodywidth / 2);
            if (L1 < 0){L1 = 0;}else if (L1 > 999){L1 = 999;}

            int L2 = (999-0)/2 - (int)((rebuild_sways[i] - sway_offset) * (999-0) / bodywidth / 2);
            if (L2 < 0){L2 = 0;}else if (L2 > 999){L2 = 999;}

            int R0 = (999-0)/2 + (int)(rebuild_twists[i] * 11.1);
            if (R0 < 0){R0 = 0;}else if (R0 > 999){R0 = 999;}

            int R1 = (999+0)/2 - (int)(rebuild_rolls[i] * 11.1 );
            if (R1 < 0){R1 = 0;}else if (R1 > 999){R1 = 999;}

            int R2 = (999-0)/2 + (int)(rebuild_pitchs[i] * 11.1 / 2);
            if (R2 < 0){R2 = 0;}else if (R2 > 999){R2 = 999;}
            if (!ui->rebuild_all_checkbox->isChecked()){
                if (sender == scripter3L0){
                    scripter3L0->values[rebuild_times[i]] = L0;
                }
                else if (sender == scripter3L1){
                    scripter3L1->values[rebuild_times[i]] = L1;
                }
                else if (sender == scripter3L2){
                    scripter3L2->values[rebuild_times[i]] = L2;
                }
                else if (sender == scripter3R0){
                    scripter3R0->values[rebuild_times[i]] = R0;
                }
                else if (sender == scripter3R1){
                    scripter3R1->values[rebuild_times[i]] = R1;
                }
                else if (sender == scripter3R2){
                    scripter3R2->values[rebuild_times[i]] = R2;
                }
            }
            else{
                scripter3L0->values[rebuild_times[i]] = L0;
                scripter3L1->values[rebuild_times[i]] = L1;
                scripter3L2->values[rebuild_times[i]] = L2;
                scripter3R0->values[rebuild_times[i]] = R0;
                scripter3R1->values[rebuild_times[i]] = R1;
                scripter3R2->values[rebuild_times[i]] = R2;
            }
        }
        this->update();
    }
}



void MainWindow::webclient_onconnected(){
    ui->link_intiface_central->setEnabled(true);
    timeoutTimer.stop();
    //handshake_msg
    QJsonObject requestServerInfo;
    requestServerInfo["Id"] = 1;
    requestServerInfo["ClientName"] = "Link_osr2_sr6_to_kk_studio";
    requestServerInfo["MessageVersion"] = 1;

    QJsonObject handshakeMsg;
    handshakeMsg["RequestServerInfo"] = requestServerInfo;

    QJsonArray handshakemessageArray;
    handshakemessageArray.append(handshakeMsg);
    //messageArray.append(requestdevicelist);


    webclient->sendTextMessage(QString(QJsonDocument(handshakemessageArray).toJson(QJsonDocument::Compact)));

    requestdevicelistTimer.start();

    ui->link_intiface_central->setStyleSheet(btn_sty6);
    tips->setText("intiface central link succeed");
    tips_window_start();
}

void MainWindow::webclient_ondisconnected(){
    devices.clear();
    devices_index.clear();
    ui->devices_list_combox->clear();
    ui->feature_list->clear();
    ui->link_intiface_central->setStyleSheet(btn_sty5);
    tips->setText("intiface central dislink");
    tips_window_start();
}

void MainWindow::onTextMessageReceived(const QString &message)
{
    //qDebug() << "Message received:" << message;

    QJsonDocument jsonDoc = QJsonDocument::fromJson(message.toUtf8());
    if (!jsonDoc.isArray()) {
        qDebug() << "Invalid JSON format";
        return;
    }
    QJsonArray jsonArray = jsonDoc.array();
    for (const QJsonValue &value : jsonArray) {
        if (!value.isObject()) continue;
        QJsonObject obj = value.toObject();
        if (obj.contains("ServerInfo")) {
        qDebug() << "Server Info:";
        qDebug() << "  Major Version:" << obj["ServerInfo"].toObject()["MajorVersion"].toInt();
        qDebug() << "  Minor Version:" << obj["ServerInfo"].toObject()["ServerInfo"].toInt();
        qDebug() << "  Server Name:" << obj["ServerInfo"].toObject()["ServerName"].toString();
        } else if (obj.contains("DeviceList")) {
            handleDeviceList(obj["DeviceList"].toObject());
        } else if (obj.contains("DeviceAdded")) {
            handleDeviceAdded(obj["DeviceAdded"].toObject());
        }
    }
}


void MainWindow::handleDeviceList(const QJsonObject &deviceList)
{
    qDebug() << "Handling Device List";
    QJsonArray get_devices = deviceList["Devices"].toArray();
    ui->devices_list_combox->clear();
    devices.clear();
    devices_index.clear();
    for (const QJsonValue &deviceValue : get_devices) {
        QJsonObject deviceObject = deviceValue.toObject();
        handleDeviceAdded(deviceObject);
    }
    qDebug() << "Total devices added:" << devices.size();
    ui->devices_list_combox->setCurrentIndex(0);
}


void MainWindow::handleDeviceAdded(const QJsonObject &deviceInfo){
    Device device;
    device.index = deviceInfo["DeviceIndex"].toInt();
    device.name = deviceInfo["DeviceName"].toString();
    QJsonObject deviceMessages = deviceInfo["DeviceMessages"].toObject();
    if (deviceMessages.contains("VibrateCmd")) {
        device.work_way = "VibrateCmd";
        QJsonObject vibrateCmd = deviceMessages["VibrateCmd"].toObject();
        int featureCount = vibrateCmd["FeatureCount"].toInt();
        for (int i=1;i<=featureCount;i++){
            device.feature.append(0);
            device.feature_enable.append(0);
        }
    } else if (deviceMessages.contains("LinearCmd")) {
        device.work_way = "linearCmd";
        QJsonObject linearCmd = deviceMessages["LinearCmd"].toObject();
        int featureCount = linearCmd["FeatureCount"].toInt();
        for (int i=1;i<=featureCount;i++){
            device.feature.append(0);
            device.feature_enable.append(0);
        }
    }
    else if (deviceMessages.contains("ScalarCmd")){
        device.work_way = "ScalarCmd";
        QJsonObject scalarCmd = deviceMessages["ScalarCmd"].toObject();
        int featureCount = scalarCmd["FeatureCount"].toInt();
        for (int i=1;i<=featureCount;i++){
            device.feature.append(0);
            device.feature_enable.append(0);
        }
    }
    else if (deviceMessages.contains("RotateCmd")){
        device.work_way = "RotateCmd";
        QJsonObject scalarCmd = deviceMessages["RotateCmd"].toObject();
        int featureCount = scalarCmd["RotateCmd"].toInt();
        for (int i=1;i<=featureCount;i++){
            device.feature.append(0);
            device.feature_enable.append(0);
        }
    }
    else {
        device.work_way = "unknown";
    }
    if (devices_index.indexOf(device.index) == -1){
        devices_index.append(device.index);
        devices.append(device);
        if (device.work_way == "linearCmd" || device.work_way =="LinearCmd"){
            ui->devices_list_combox->addItem(device.name+"("+QString::number(device.index)+")");
        }
        else {
            ui->devices_list_combox->addItem(device.name+"("+QString::number(device.index)+")"+"Unsupported devices, currently only LinearCmd devices are supported.");
        }
    }
}


void MainWindow::sent_LinearCmd(int& i,Device& device,int& sleeptime,int& move){
    QJsonObject vectorObj;
    vectorObj["Index"] = i;
    vectorObj["Duration"] = sleeptime;
    float position = static_cast<float>(move) / 1000.0f;
    qDebug() << position;
    vectorObj["Position"] = QString::number(position, 'f', 3).toDouble();
    QJsonArray vectorsArray;
    vectorsArray.append(vectorObj);
    QJsonObject LinearCmd;
    LinearCmd["Id"] = 1;
    LinearCmd["DeviceIndex"] = device.index;
    LinearCmd["Vectors"] = vectorsArray;
    QJsonObject linearCmd;
    linearCmd["LinearCmd"] = LinearCmd;
    QJsonArray linearCmdArray;
    linearCmdArray.append(linearCmd);
    //messageArray.append(requestdevicelist);
    webclient->sendTextMessage(QString(QJsonDocument(linearCmdArray).toJson(QJsonDocument::Compact)));
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::MouseButton::LeftButton){
        mouse1 = true;
        press_point = event->globalPosition();
        if (event->position().x() < 5 && event->position().y() < 5){
            orientation = 1;
        }
        else if (event->position().x() > this->width()- 5 && event->position().y() > this->height() -5){
            orientation = 2;
        }
        else if (event->position().x() < 5 && event->position().y() > this->height() -5){
            orientation = 3;
        }
        else if (event->position().x() > this->width()- 5 && event->position().y() < 5){
            orientation = 4;
        }
        else if (event->position().x() < 5){
            orientation = 5;
        }
        else if (event->position().x() > this->width()- 5){
            orientation = 6;
        }
        else if (event->position().y() < 5){
            orientation = 7;
        }
        else if (event->position().y() > this->height() -5){
            orientation = 8;
        }
        else{
            orientation = 0;
        }
        m_drag = true;
        m_dragPosition = event->globalPosition().toPoint() - this->pos();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (mouse1 && orientation){
        move_point = event->globalPosition() - press_point;
        press_point = event->globalPosition();
        QRect geometry = this->geometry();
        qreal dpr = windowHandle()->devicePixelRatio();
        move_point /= dpr;
        switch(orientation) {
        case 1:
            geometry.setTopLeft(geometry.topLeft() + move_point.toPoint());
            break;
        case 2:
            geometry.setBottomRight(geometry.bottomRight() + move_point.toPoint());
            break;
        case 3:
            geometry.setBottomLeft(geometry.bottomLeft() + QPoint(move_point.x(), move_point.y()));
            break;
        case 4:
            geometry.setTopRight(geometry.topRight() + QPoint(move_point.x(), move_point.y()));
            break;
        case 5:
            geometry.setLeft(geometry.left() + move_point.x());
            break;
        case 6:
            geometry.setRight(geometry.right() + move_point.x());
            break;
        case 7:
            geometry.setTop(geometry.top() + move_point.y());
            break;
        case 8:
            geometry.setBottom(geometry.bottom() + move_point.y());
            break;
        }
        this->setGeometry(geometry);
        this->update();
    }
    else if (mouse1 && m_drag && !orientation){
        move(event->globalPosition().toPoint() - m_dragPosition);
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    mouse1 = false;
    orientation = 0;
    m_drag = false;
    if (scripterL0_current_hover_x){
        QPoint viewportPos = event->pos();
        QPoint widgetPos = ui->scrollArea_4->viewport()->mapToParent(viewportPos);
        QPoint scrollAreaPos = ui->scrollArea_4->mapFromParent(widgetPos);
        qDebug() << "相对移动位置为：" << scripterL0_current_hover_x - scrollAreaPos.x();
        scripterL0_current_hover_x = 0;
    }
}


bool MainWindow::event(QEvent *event)
{
    if (event->type() == QEvent::HoverMove) {
        QHoverEvent *hoverEvent = static_cast<QHoverEvent *>(event);
        if (hoverEvent->position().x() < 5 && hoverEvent->position().y() < 5){
            setCursor(Qt::CursorShape::SizeFDiagCursor);
        }
        else if (hoverEvent->position().x() > this->width()- 5 && hoverEvent->position().y() > this->height() -5){
            setCursor(Qt::CursorShape::SizeFDiagCursor);
        }
        else if (hoverEvent->position().x() < 5 && hoverEvent->position().y() > this->height() -5){
            setCursor(Qt::CursorShape::SizeBDiagCursor);
        }
        else if (hoverEvent->position().x() > this->width()- 5 && hoverEvent->position().y() < 5){
            setCursor(Qt::CursorShape::SizeBDiagCursor);
        }
        else if (hoverEvent->position().x() < 5){
            setCursor(Qt::CursorShape::SizeHorCursor);
        }
        else if (hoverEvent->position().x() > this->width()- 5){
            setCursor(Qt::CursorShape::SizeHorCursor);
        }
        else if (hoverEvent->position().y() < 5){
            setCursor(Qt::CursorShape::SizeVerCursor);
        }
        else if (hoverEvent->position().y() > this->height() -5){
            setCursor(Qt::CursorShape::SizeVerCursor);
        }
        else{
            setCursor(Qt::CursorShape::ArrowCursor);
        }
    }
     return QWidget::event(event);
}



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    press_point = QPointF(0,0);
    move_point = QPointF(0,0);
    mouse1 = false;
    orientation = 0;
    m_drag = false;
    m_dragPosition = this->pos();
    setWindowFlags(Qt::FramelessWindowHint);
    ui->setupUi(this);
    config_init();
    ui_init();
    lovemaking_datas = {};
    sceneParts = {};
    new_version = false;
    selected_part = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}
