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
    connect(ui->scripter, &QPushButton::clicked, this, [=] {
        ui->stackedWidget->setCurrentIndex(2);});
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
    scripterL0 = new Scripter_edit;
    scripterL0->values.clear();
    scripterL1 = new Scripter_edit;
    scripterL1->values.clear();
    scripterL2 = new Scripter_edit;
    scripterL2->values.clear();
    scripterR0 = new Scripter_edit;
    scripterR0->values.clear();
    scripterR1 = new Scripter_edit;
    scripterR1->values.clear();
    scripterR2 = new Scripter_edit;
    scripterR2->values.clear();
    silderL0 = new Range_Silder;
    silderL1 = new Range_Silder;
    silderL2 = new Range_Silder;
    silderR0 = new Range_Silder;
    silderR1 = new Range_Silder;
    silderR2 = new Range_Silder;
    ui->L0_widget->layout()->addWidget(scripterL0);
    ui->L1_widget->layout()->addWidget(scripterL1);
    ui->L2_widget->layout()->addWidget(scripterL2);
    ui->R0_widget->layout()->addWidget(scripterR0);
    ui->R1_widget->layout()->addWidget(scripterR1);
    ui->R2_widget->layout()->addWidget(scripterR2);
    ui->L0_silder->layout()->addWidget(silderL0);
    ui->L1_silder->layout()->addWidget(silderL1);
    ui->L2_silder->layout()->addWidget(silderL2);
    ui->R0_silder->layout()->addWidget(silderR0);
    ui->R1_silder->layout()->addWidget(silderR1);
    ui->R2_silder->layout()->addWidget(silderR2);
    connect(scripterL0,&Scripter_edit::get_copy_values,this,&MainWindow::copy_values);
    connect(scripterL1,&Scripter_edit::get_copy_values,this,&MainWindow::copy_values);
    connect(scripterL2,&Scripter_edit::get_copy_values,this,&MainWindow::copy_values);
    connect(scripterR0,&Scripter_edit::get_copy_values,this,&MainWindow::copy_values);
    connect(scripterR1,&Scripter_edit::get_copy_values,this,&MainWindow::copy_values);
    connect(scripterR2,&Scripter_edit::get_copy_values,this,&MainWindow::copy_values);
    connect(scripterL0,&Scripter_edit::current_line,this,&MainWindow::setplaytime);
    connect(scripterL1,&Scripter_edit::current_line,this,&MainWindow::setplaytime);
    connect(scripterL2,&Scripter_edit::current_line,this,&MainWindow::setplaytime);
    connect(scripterR0,&Scripter_edit::current_line,this,&MainWindow::setplaytime);
    connect(scripterR1,&Scripter_edit::current_line,this,&MainWindow::setplaytime);
    connect(scripterR2,&Scripter_edit::current_line,this,&MainWindow::setplaytime);
    connect(scripterL0,&Scripter_edit::set_play,this,&MainWindow::set_play);
    connect(scripterL1,&Scripter_edit::set_play,this,&MainWindow::set_play);
    connect(scripterL2,&Scripter_edit::set_play,this,&MainWindow::set_play);
    connect(scripterR0,&Scripter_edit::set_play,this,&MainWindow::set_play);
    connect(scripterR1,&Scripter_edit::set_play,this,&MainWindow::set_play);
    connect(scripterR2,&Scripter_edit::set_play,this,&MainWindow::set_play);
    connect(scripterL0,&Scripter_edit::rebuildtimes,this,&MainWindow::rebuildtimes);
    connect(scripterL1,&Scripter_edit::rebuildtimes,this,&MainWindow::rebuildtimes);
    connect(scripterL2,&Scripter_edit::rebuildtimes,this,&MainWindow::rebuildtimes);
    connect(scripterR0,&Scripter_edit::rebuildtimes,this,&MainWindow::rebuildtimes);
    connect(scripterR1,&Scripter_edit::rebuildtimes,this,&MainWindow::rebuildtimes);
    connect(scripterR2,&Scripter_edit::rebuildtimes,this,&MainWindow::rebuildtimes);
    connect(scripterL0,&Scripter_edit::rebuildblowjobtimes,this,&MainWindow::rebuildblowjobtimes);
    connect(scripterL1,&Scripter_edit::rebuildblowjobtimes,this,&MainWindow::rebuildblowjobtimes);
    connect(scripterL2,&Scripter_edit::rebuildblowjobtimes,this,&MainWindow::rebuildblowjobtimes);
    connect(scripterR0,&Scripter_edit::rebuildblowjobtimes,this,&MainWindow::rebuildblowjobtimes);
    connect(scripterR1,&Scripter_edit::rebuildblowjobtimes,this,&MainWindow::rebuildblowjobtimes);
    connect(scripterR2,&Scripter_edit::rebuildblowjobtimes,this,&MainWindow::rebuildblowjobtimes);
    connect(scripterL0,&Scripter_edit::rebuildbreastsextimes,this,&MainWindow::rebuildbreastsextimes);
    connect(scripterL1,&Scripter_edit::rebuildbreastsextimes,this,&MainWindow::rebuildbreastsextimes);
    connect(scripterL2,&Scripter_edit::rebuildbreastsextimes,this,&MainWindow::rebuildbreastsextimes);
    connect(scripterR0,&Scripter_edit::rebuildbreastsextimes,this,&MainWindow::rebuildbreastsextimes);
    connect(scripterR1,&Scripter_edit::rebuildbreastsextimes,this,&MainWindow::rebuildbreastsextimes);
    connect(scripterR2,&Scripter_edit::rebuildbreastsextimes,this,&MainWindow::rebuildbreastsextimes);
    connect(scripterL0,&Scripter_edit::rebuildhandjobLtimes,this,&MainWindow::rebuildhandjobLtimes);
    connect(scripterL1,&Scripter_edit::rebuildhandjobLtimes,this,&MainWindow::rebuildhandjobLtimes);
    connect(scripterL2,&Scripter_edit::rebuildhandjobLtimes,this,&MainWindow::rebuildhandjobLtimes);
    connect(scripterR0,&Scripter_edit::rebuildhandjobLtimes,this,&MainWindow::rebuildhandjobLtimes);
    connect(scripterR1,&Scripter_edit::rebuildhandjobLtimes,this,&MainWindow::rebuildhandjobLtimes);
    connect(scripterR2,&Scripter_edit::rebuildhandjobLtimes,this,&MainWindow::rebuildhandjobLtimes);
    connect(scripterL0,&Scripter_edit::rebuildhandjobRtimes,this,&MainWindow::rebuildhandjobRtimes);
    connect(scripterL1,&Scripter_edit::rebuildhandjobRtimes,this,&MainWindow::rebuildhandjobRtimes);
    connect(scripterL2,&Scripter_edit::rebuildhandjobRtimes,this,&MainWindow::rebuildhandjobRtimes);
    connect(scripterR0,&Scripter_edit::rebuildhandjobRtimes,this,&MainWindow::rebuildhandjobRtimes);
    connect(scripterR1,&Scripter_edit::rebuildhandjobRtimes,this,&MainWindow::rebuildhandjobRtimes);
    connect(scripterR2,&Scripter_edit::rebuildhandjobRtimes,this,&MainWindow::rebuildhandjobRtimes);
    ui->scrollArea_3->verticalScrollBar()->setSingleStep(0);
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
    writerTimer.setInterval(100);
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
        if (file_path != datalist[0]){
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
            QTextStream in(&file);
            while (!in.atEnd()) {
                QString line = in.readLine();
                QStringList lines = line.split("/");
                inserts.append(lines[0].toFloat());
                surges.append(lines[1].toFloat());
                sways.append(lines[2].toFloat());
                twists.append(lines[3].toFloat());
                rolls.append(lines[4].toFloat());
                pitchs.append(lines[5].toFloat());
                bodywidth = lines[8].toFloat();
                if (lines.count() >= 10){blowjob_inserts.append(lines[9].toFloat());}
                if (lines.count() >= 11){blowjob_sways.append(lines[10].toFloat());}
                if (lines.count() >= 12){blowjob_surges.append(lines[11].toFloat());}
                if (lines.count() >= 13){blowjob_twists.append(lines[12].toFloat());}
                if (lines.count() >= 14){blowjob_rolls.append(lines[13].toFloat());}
                if (lines.count() >= 15){blowjob_pitchs.append(lines[14].toFloat());}
                if (lines.count() >= 10){blowjob_inserts.append(lines[9].toFloat());}
                if (lines.count() >= 11){blowjob_sways.append(lines[10].toFloat());}
                if (lines.count() >= 12){blowjob_surges.append(lines[11].toFloat());}
                if (lines.count() >= 13){blowjob_twists.append(lines[12].toFloat());}
                if (lines.count() >= 14){blowjob_rolls.append(lines[13].toFloat());}
                if (lines.count() >= 15){blowjob_pitchs.append(lines[14].toFloat());}
                if (lines.count() >= 16){breastsex_inserts.append(lines[15].toFloat());}
                if (lines.count() >= 17){breastsex_surges.append(lines[16].toFloat());}
                if (lines.count() >= 18){breastsex_sways.append(lines[17].toFloat());}
                if (lines.count() >= 19){breastsex_twists.append(lines[18].toFloat());}
                if (lines.count() >= 20){breastsex_rolls.append(lines[19].toFloat());}
                if (lines.count() >= 21){breastsex_pitchs.append(lines[20].toFloat());}
                if (lines.count() >= 22){handjobL_inserts.append(lines[21].toFloat());}
                if (lines.count() >= 23){handjobL_surges.append(lines[22].toFloat());}
                if (lines.count() >= 24){handjobL_sways.append(lines[23].toFloat());}
                if (lines.count() >= 25){handjobL_twists.append(lines[24].toFloat());}
                if (lines.count() >= 26){handjobL_rolls.append(lines[25].toFloat());}
                if (lines.count() >= 27){handjobL_pitchs.append(lines[26].toFloat());}
                if (lines.count() >= 28){handjobR_inserts.append(lines[27].toFloat());}
                if (lines.count() >= 29){handjobR_surges.append(lines[28].toFloat());}
                if (lines.count() >= 30){handjobR_sways.append(lines[29].toFloat());}
                if (lines.count() >= 31){handjobR_twists.append(lines[30].toFloat());}
                if (lines.count() >= 32){handjobR_rolls.append(lines[31].toFloat());}
                if (lines.count() >= 33){handjobR_pitchs.append(lines[32].toFloat()); }
            }
            float surge_sum = 0;
            for (float value : surges) { surge_sum += value; }
            surge_offset = surge_sum / surges.count();
            float sway_sum = 0;
            for (float value : surges) { surge_sum += value; }
            sway_offset = sway_sum / sways.count();
            for (float value : inserts) {
                if (value > insert_max) {
                    insert_max = value;
                }
            }
            for (float value : inserts) {
                if (value < insert_min) {
                    insert_min = value;
                }
            }
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
                R1 = (999+0)/2 - (int)(rolls[i] * 11.1 / 2 );
                if (R1 < 0){R1 = 0;}else if (R1 > 999){R1 = 999;}
                R1s.append(R1);
                R2 = (999-0)/2 + (int)(pitchs[i] * 11.1 / 2);
                if (R2 < 0){R2 = 0;}else if (R2 > 999){R2 = 999;}
                R2s.append(R2);
                if (R0 < 0){R0 = 0;}else if (R0 > 999){R0 = 999;}
                R0 = (999-0)/2 + (int)(twists[i] * 11.1 /2 );
                R0s.append(R0);
            }
            QString get_path = file_path;
            get_path = get_path.replace(".txt",".sr6script");
            qDebug() << get_path;
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

            }
            else{
                scripterL0->values = L0s;
                scripterL1->values = L1s;
                scripterL2->values = L2s;
                scripterR0->values = R0s;
                scripterR1->values = R1s;
                scripterR2->values = R2s;
                save_scripter();
            }
            scripterL0->values = L0s;
            scripterL1->values = L1s;
            scripterL2->values = L2s;
            scripterR0->values = R0s;
            scripterR1->values = R1s;
            scripterR2->values = R2s;
            file.close();
        }
        index = datalist[1].toInt();
        sleep_time = datalist[2].toDouble();
        if (index+1 >= inserts.count()){return;}
        if (file_path != ""){
            L0 = scripterL0->values[index];
            L1 = scripterL1->values[index];
            L2 = scripterL2->values[index];
            R0 = scripterR0->values[index];
            R1 = scripterR1->values[index];
            R2 = scripterR2->values[index];
            L0s = scripterL0->values;
            L1s = scripterL1->values;
            L2s = scripterL2->values;
            R0s = scripterR0->values;
            R1s = scripterR1->values;
            R2s = scripterR2->values;
            scripterL0->selected_line = index;
            scripterL1->selected_line = index;
            scripterL2->selected_line = index;
            scripterR0->selected_line = index;
            scripterR1->selected_line = index;
            scripterR2->selected_line = index;
            scripterL0->update();
            scripterL1->update();
            scripterL2->update();
            scripterR0->update();
            scripterR1->update();
            scripterR2->update();
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
                qDebug() << "L0"+QString("%1").arg(L0, 3, 10, QChar('0')) +"I"+ QString::number(sleep_time) +"\r\n";
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
    L0s = scripterL0 ->values;
    L1s = scripterL1 ->values;
    L2s = scripterL2 ->values;
    R0s = scripterR0 ->values;
    R1s = scripterR1 ->values;
    R2s = scripterR2 ->values;
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
    scripterL0->copy_values =values;
    scripterL1->copy_values =values;
    scripterL2->copy_values =values;
    scripterR0->copy_values =values;
    scripterR1->copy_values =values;
    scripterR2->copy_values =values;
    scripterL0->copy_values_indexs = index;
    scripterL1->copy_values_indexs = index;
    scripterL2->copy_values_indexs = index;
    scripterR0->copy_values_indexs = index;
    scripterR1->copy_values_indexs = index;
    scripterR2->copy_values_indexs = index;
}

void MainWindow::setplaytime(int index){
    scripterL0->selected_line = index;
    scripterL1->selected_line = index;
    scripterL2->selected_line = index;
    scripterR0->selected_line = index;
    scripterR1->selected_line = index;
    scripterR2->selected_line = index;
    if (allowriter){
        try {
            socket->write("1:"+QString::number(index).toLocal8Bit());
            socket->flush();
        } catch (...) {
        }
        allowriter = false;
        writerTimer.start();
    }
    this->update();
}


void MainWindow::set_play(){
    try {
        socket->write("0:");
        socket->flush();
    } catch (...) {
    }
    this->update();
}

void MainWindow::rebuildtimes(QList<int> rebuild_times){
    QObject* sender = QObject::sender();
    update_list(sender,0,rebuild_times);
}

void MainWindow::rebuildblowjobtimes(QList<int> rebuild_times){
    QObject* sender = QObject::sender();
    update_list(sender,1,rebuild_times);
}

void MainWindow::rebuildbreastsextimes(QList<int> rebuild_times){
    QObject* sender = QObject::sender();
    update_list(sender,2,rebuild_times);
}

void MainWindow::rebuildhandjobLtimes(QList<int> rebuild_times){
    QObject* sender = QObject::sender();
    update_list(sender,2,rebuild_times);
}

void MainWindow::rebuildhandjobRtimes(QList<int> rebuild_times){
    QObject* sender = QObject::sender();
    update_list(sender,2,rebuild_times);
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
        if (sender == scripterL0) {
            scripterL0->record_values.append(scripterL0->values);
        } else if (sender == scripterL1) {
            scripterL1->record_values.append(scripterL1->values);
        } else if (sender == scripterL2) {
            scripterL2->record_values.append(scripterL2->values);
        } else if (sender == scripterR0) {
            scripterR0->record_values.append(scripterR0->values);
        } else if (sender == scripterR1) {
            scripterR1->record_values.append(scripterR1->values);
        } else if (sender == scripterR2) {
            scripterR2->record_values.append(scripterR2->values);
        }
    } else {
        scripterL0->record_values.append(scripterL0->values);
        scripterL1->record_values.append(scripterL1->values);
        scripterL2->record_values.append(scripterL2->values);
        scripterR0->record_values.append(scripterR0->values);
        scripterR1->record_values.append(scripterR1->values);
        scripterR2->record_values.append(scripterR2->values);
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
        float rebuild_insert_max =0 ;
        float rebuild_insert_min =999 ;
        for (float value : rebuild_inserts) {
            if (value > rebuild_insert_max) {
                rebuild_insert_max = value;
            }
        }
        for (float value : rebuild_inserts) {
            if (value < rebuild_insert_min) {
                rebuild_insert_min = value;
            }
        }
        float surge_sum = 0;
        for (float value : rebuild_surges) { surge_sum += value; }
        float surge_offset = surge_sum / rebuild_surges.count();
        float sway_sum = 0;
        for (float value : rebuild_surges) { surge_sum += value; }
        float sway_offset = sway_sum / rebuild_sways.count();
        //float rebuild_insert_min =999 ;

        for (int i = 0; i < rebuild_inserts.count(); ++i){
            int L0 = (999 / (rebuild_insert_min - rebuild_insert_max))*rebuild_inserts[i] - (999 / (rebuild_insert_min - rebuild_insert_max))*rebuild_insert_max;
            if (L0 < 0){L0 = 0;}else if (L0 > 999){L0 = 999;}

            int L1 = (999-0)/2 - (int)((rebuild_surges[i] - surge_offset) * (999-0) / bodywidth / 2);
            if (L1 < 0){L1 = 0;}else if (L1 > 999){L1 = 999;}

            int L2 = (999-0)/2 - (int)((rebuild_sways[i] - sway_offset) * (999-0) / bodywidth / 2);
            if (L2 < 0){L2 = 0;}else if (L2 > 999){L2 = 999;}

            int R0 = (999-0)/2 + (int)(rebuild_twists[i] * 11.1 / 2 );
            if (R0 < 0){R0 = 0;}else if (R0 > 999){R0 = 999;}

            int R1 = (999+0)/2 - (int)(rebuild_rolls[i] * 11.1 / 2 );
            if (R1 < 0){R1 = 0;}else if (R1 > 999){R1 = 999;}

            int R2 = (999-0)/2 + (int)(rebuild_pitchs[i] * 11.1 / 2);
            if (R2 < 0){R2 = 0;}else if (R2 > 999){R2 = 999;}
            if (!ui->rebuild_all_checkbox->isChecked()){
                if (sender == scripterL0) {
                    scripterL0->values[rebuild_times[i]] = L0;
                } else if (sender == scripterL1) {
                    scripterL1->values[rebuild_times[i]] = L1;
                } else if (sender == scripterL2) {
                    scripterL2->values[rebuild_times[i]] = L2;
                } else if (sender == scripterR0) {
                    scripterR0->values[rebuild_times[i]] = R0;
                } else if (sender == scripterR1) {
                    scripterR1->values[rebuild_times[i]] = R1;
                } else if (sender == scripterR2) {
                    scripterR2->values[rebuild_times[i]] = R2;
                }
            }
            else{
                scripterL0->values[rebuild_times[i]] = L0;
                scripterL1->values[rebuild_times[i]] = L1;
                scripterL2->values[rebuild_times[i]] = L2;
                scripterR0->values[rebuild_times[i]] = R0;
                scripterR1->values[rebuild_times[i]] = R1;
                scripterR2->values[rebuild_times[i]] = R2;
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
}

MainWindow::~MainWindow()
{
    delete ui;
}
