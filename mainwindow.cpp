#include "mainwindow.h"
#include "ui_mainwindow.h"



void MainWindow::page_init(){
    connect(ui->home, &QPushButton::clicked, this, [=] {
        ui->stackedWidget->setCurrentIndex(0);});
    connect(ui->setting, &QPushButton::clicked, this, [=] {
        ui->stackedWidget->setCurrentIndex(1);});
    //connect(ui->chart, &QPushButton::clicked, this, [=] {
        //ui->stackedWidget->setCurrentIndex(2);});
}




void MainWindow::config_init() {
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
        settings->beginGroup("Arithmetic");
        settings->setValue("insert", "1");
        settings->setValue("pitch", "1");
        settings->setValue("surge", "1");
        settings->setValue("sway", "1");
        settings->setValue("twist", "1");
        settings->setValue("roll", "1");
        settings->setValue("suck", "1");
        settings->setValue("speed", "200");
        settings->endGroup();
        settings->beginGroup("Axis value");
        settings->setValue("L0_min", "0");
        settings->setValue("L0_max", "999");
        settings->setValue("L1_min", "0");
        settings->setValue("L1_max", "999");
        settings->setValue("L2_min", "0");
        settings->setValue("L2_max", "999");
        settings->setValue("R0_min", "0");
        settings->setValue("R0_max", "999");
        settings->setValue("R1_min", "0");
        settings->setValue("R1_max", "999");
        settings->setValue("R2_min", "0");
        settings->setValue("R2_max", "999");
        settings->setValue("A1_min", "0");
        settings->setValue("A1_max", "999");
        settings->endGroup();
        settings->beginGroup("language");
        settings->setValue("id", "0");
        settings->endGroup();
    }
    QFileInfo fileInfo2("./language.ini");
    if (fileInfo2.exists()) {
        language_setting = new QSettings("./language.ini", QSettings::IniFormat,this);
        qDebug() << "exist language";
    }
    else{
        qDebug() << "build language";
        language_setting = new QSettings("./language.ini", QSettings::IniFormat,this);

        language_setting->beginGroup("English");
        language_setting->setValue("wait_for_client_link", "wait for client link");
        language_setting->setValue("client_link:", "client link");
        language_setting->setValue("load_scene", "load scene");
        language_setting->setValue("Axis_value", "Axis value");
        language_setting->setValue("Serial_and_server_setting", "Serial and server setting");
        language_setting->setValue("com_label", "Com");
        language_setting->setValue("BaudRate_label", "BaudRate");
        language_setting->setValue("Serverip_label", "Serverip");
        language_setting->setValue("Port_label", "Port");
        language_setting->setValue("arithmetic", "arithmetic");
        language_setting->setValue("language_setting", "language setting");
        language_setting->setValue("language", "language");
        language_setting->setValue("Serial_link_fail", "Serial link fail！");
        language_setting->setValue("Serial_link_succeed", "Serial link succeed");
        language_setting->setValue("Close_com_succeed", "Close com succeed");
        language_setting->endGroup();

        language_setting->beginGroup("简体中文");
        language_setting->setValue("wait_for_client_link", "等待应用连接");
        language_setting->setValue("client_link:", "客服端连接来自");
        language_setting->setValue("load_scene", "加载场景卡展示");
        language_setting->setValue("Axis_value", "当前轴体运动值");
        language_setting->setValue("Serial_and_server_setting", "串口和服务器设置");
        language_setting->setValue("com_label", "串口");
        language_setting->setValue("BaudRate_label", "波特率");
        language_setting->setValue("Serverip_label", "服务器ip地址");
        language_setting->setValue("Port_label", "端口号");
        language_setting->setValue("arithmetic", "运动算法");
        language_setting->setValue("language_setting", "语言设置");
        language_setting->setValue("language", "语言");
        language_setting->setValue("Serial_link_fail", "串口连接失败");
        language_setting->setValue("Close_com_succeed", "关闭串口成功");
        language_setting->endGroup();

        language_setting->beginGroup("繁體中文");
        language_setting->setValue("wait_for_client_link", "等待應用程式連線");
        language_setting->setValue("client_link:", "客戶端連線來自");
        language_setting->setValue("load_scene", "載入場景卡展示");
        language_setting->setValue("Axis_value", "當前軸體運動值");
        language_setting->setValue("Serial_and_server_setting", "串列和伺服器設定");
        language_setting->setValue("com_label", "串列埠");
        language_setting->setValue("BaudRate_label", "傳輸速率");
        language_setting->setValue("Serverip_label", "伺服器IP位址");
        language_setting->setValue("Port_label", "埠號");
        language_setting->setValue("arithmetic", "運動算法");
        language_setting->setValue("language_setting", "語言設定");
        language_setting->setValue("language", "語言");
        language_setting->setValue("Serial_link_fail", "串列埠連線失敗");
        language_setting->setValue("Serial_link_succeed", "串列埠連線成功");
        language_setting->setValue("Close_com_succeed", "關閉串列埠成功");
        language_setting->endGroup();

        language_setting->beginGroup("日本語");
        language_setting->setValue("wait_for_client_link", "クライアントの接続を待っている");
        language_setting->setValue("client_link:", "クライアントの接続元");
        language_setting->setValue("load_scene", "シーンカードの表示をロードする");
        language_setting->setValue("Axis_value", "現在の軸の動作値");
        language_setting->setValue("Serial_and_server_setting", "シリアルとサーバーの設定");
        language_setting->setValue("com_label", "COMポート");
        language_setting->setValue("BaudRate_label", "ボーレート");
        language_setting->setValue("Serverip_label", "サーバーIPアドレス");
        language_setting->setValue("Port_label", "ポート番号");
        language_setting->setValue("arithmetic", "動作アルゴリズム");
        language_setting->setValue("language_setting", "言語設定");
        language_setting->setValue("language", "言語");
        language_setting->setValue("Serial_link_fail", "シリアル接続に失敗しました");
        language_setting->setValue("Serial_link_succeed", "シリアル接続に成功しました");
        language_setting->setValue("Close_com_succeed", "COMポートの閉じに成功しました");
        language_setting->endGroup();

        language_setting->beginGroup("한국어");
        language_setting->setValue("wait_for_client_link", "클라이언트 연결 대기 중");
        language_setting->setValue("client_link:", "클라이언트 연결 출처");
        language_setting->setValue("load_scene", "장면 카드 표시 로드");
        language_setting->setValue("Axis_value", "현재 축 운동 값");
        language_setting->setValue("Serial_and_server_setting", "시리얼 및 서버 설정");
        language_setting->setValue("com_label", "COM 포트");
        language_setting->setValue("BaudRate_label", "전송 속도");
        language_setting->setValue("Serverip_label", "서버 IP 주소");
        language_setting->setValue("Port_label", "포트 번호");
        language_setting->setValue("arithmetic", "운동 알고리즘");
        language_setting->setValue("language_setting", "언어 설정");
        language_setting->setValue("language", "언어");
        language_setting->setValue("Serial_link_fail", "시리얼 연결 실패");
        language_setting->setValue("Serial_link_succeed", "시리얼 연결 성공");
        language_setting->setValue("Close_com_succeed", "COM 포트 닫기 성공");
        language_setting->endGroup();

        language_setting->beginGroup("Русский");
        language_setting->setValue("wait_for_client_link", "Ожидание подключения клиента");
        language_setting->setValue("client_link:", "Клиент подключен из");
        language_setting->setValue("load_scene", "Загрузить отображение сцены");
        language_setting->setValue("Axis_value", "Текущее значение оси");
        language_setting->setValue("Serial_and_server_setting", "Настройки последовательного порта и сервера");
        language_setting->setValue("com_label", "COM-порт");
        language_setting->setValue("BaudRate_label", "Скорость передачи");
        language_setting->setValue("Serverip_label", "IP-адрес сервера");
        language_setting->setValue("Port_label", "Номер порта");
        language_setting->setValue("arithmetic", "Алгоритм движения");
        language_setting->setValue("language_setting", "Настройки языка");
        language_setting->setValue("language", "Язык");
        language_setting->setValue("Serial_link_fail", "Ошибка подключения последовательного порта");
        language_setting->setValue("Serial_link_succeed", "Последовательный порт успешно подключен");
        language_setting->setValue("Close_com_succeed", "COM-порт успешно закрыт");
        language_setting->endGroup();
    }

    //language
    ui->language_combox->addItems(language_setting->childGroups());
    config_change();
    ui->language_combox->setCurrentIndex(settings->value("language/id").toInt());


    //Axis_value
    ui->L0_min->setText(settings->value("Axis value/L0_min").toString());
    ui->L0_max->setText(settings->value("Axis value/L0_max").toString());
    ui->L1_min->setText(settings->value("Axis value/L1_min").toString());
    ui->L1_max->setText(settings->value("Axis value/L1_max").toString());
    ui->L2_min->setText(settings->value("Axis value/L2_min").toString());
    ui->L2_max->setText(settings->value("Axis value/L2_max").toString());
    ui->R0_min->setText(settings->value("Axis value/R0_min").toString());
    ui->R0_max->setText(settings->value("Axis value/R0_max").toString());
    ui->R1_min->setText(settings->value("Axis value/R1_min").toString());
    ui->R1_max->setText(settings->value("Axis value/R1_max").toString());
    ui->R2_min->setText(settings->value("Axis value/R2_min").toString());
    ui->R2_max->setText(settings->value("Axis value/R2_max").toString());
    ui->A1_min->setText(settings->value("Axis value/A1_min").toString());
    ui->A1_max->setText(settings->value("Axis value/A1_max").toString());

    //SerialPort
    ui->BaudRate->setText(settings->value("SerialPort/baudrate").toString());

    //Server
    ui->Serverip->setText(settings->value("Server/Serverip").toString());
    ui->Port->setText(settings->value("Server/Serverport").toString());

    //arithmetic
    ui->insert->setText(settings->value("Arithmetic/insert").toString());
    ui->pitch->setText(settings->value("Arithmetic/pitch").toString());
    ui->surge->setText(settings->value("Arithmetic/surge").toString());
    ui->sway->setText(settings->value("Arithmetic/sway").toString());
    ui->twist->setText(settings->value("Arithmetic/twist").toString());
    ui->roll->setText(settings->value("Arithmetic/roll").toString());
    ui->suck->setText(settings->value("Arithmetic/suck").toString());
    ui->diff->setText(settings->value("Arithmetic/speed").toString());


    for (const QSerialPortInfo& portInfo :ports_list) {
        ui->port_id->addItem(portInfo.portName() + ":" + portInfo.description(), portInfo.portName());
    }

}



void MainWindow::config_change(){
    //Axis_value
    connect(ui->L0_min, &QLineEdit::textChanged, this, [=] {
        if (ui->L0_min->text().toInt() >= 0 && ui->L0_min->text().toInt() < ui->L0_min->text().toInt()) {
            settings->beginGroup("Axis value");
            settings->setValue("L0_min", ui->L0_min->text());
            settings->endGroup();
        }
        else {
            ui->L0_min->setText(settings->value("Axis value/L0_min").toString());
        }
    });
    connect(ui->L0_max, &QLineEdit::textChanged, this, [=] {
        if (ui->L0_max->text().toInt() > ui->L0_min->text().toInt() && ui->L0_max->text().toInt() <= 999 ) {
            settings->beginGroup("Axis value");
            settings->setValue("L0_min", ui->L0_min->text());
            settings->endGroup();
        }
        else {
            ui->L0_max->setText(settings->value("Axis value/L0_max").toString());
        }
    });
    connect(ui->L1_min, &QLineEdit::textChanged, this, [=] {
        if (ui->L1_min->text().toInt() >= 0 && ui->L1_min->text().toInt() < ui->L1_max->text().toInt()) {
            settings->beginGroup("Axis value");
            settings->setValue("L1_min", ui->L1_min->text());
            settings->endGroup();
        }
        else {
            ui->L1_min->setText(settings->value("Axis value/L1_min").toString());
        }
    });
    connect(ui->L1_max, &QLineEdit::textChanged, this, [=] {
        if (ui->L1_max->text().toInt() > ui->L1_min->text().toInt() && ui->L1_max->text().toInt() <= 999 ) {
            settings->beginGroup("Axis value");
            settings->setValue("L1_max", ui->L1_max->text());
            settings->endGroup();
        }
        else {
            ui->L1_max->setText(settings->value("Axis value/L1_max").toString());
        }
    });
    connect(ui->L2_min, &QLineEdit::textChanged, this, [=] {
        if (ui->L2_min->text().toInt() >= 0 && ui->L2_min->text().toInt() < ui->L2_max->text().toInt()) {
            settings->beginGroup("Axis value");
            settings->setValue("L2_min", ui->L2_min->text());
            settings->endGroup();
        }
        else {
            ui->L2_min->setText(settings->value("Axis value/L2_min").toString());
        }
    });
    connect(ui->L2_max, &QLineEdit::textChanged, this, [=] {
        if (ui->L2_max->text().toInt() > ui->L2_min->text().toInt() && ui->L2_max->text().toInt() <= 999 ) {
            settings->beginGroup("Axis value");
            settings->setValue("L2_max", ui->L2_max->text());
            settings->endGroup();
        }
        else {
            ui->L2_max->setText(settings->value("Axis value/L2_max").toString());
        }
    });
    connect(ui->R0_min, &QLineEdit::textChanged, this, [=] {
        if (ui->R0_min->text().toInt() >= 0 && ui->R0_min->text().toInt() < ui->R0_max->text().toInt()) {
            settings->beginGroup("Axis value");
            settings->setValue("R0_min", ui->R0_min->text());
            settings->endGroup();
        }
        else {
            ui->R0_min->setText(settings->value("Axis value/R0_min").toString());
        }
    });
    connect(ui->R0_max, &QLineEdit::textChanged, this, [=] {
        if (ui->R0_max->text().toInt() > ui->R0_min->text().toInt() && ui->R0_max->text().toInt() <= 999) {
            settings->beginGroup("Axis value");
            settings->setValue("R0_max", ui->R0_max->text());
            settings->endGroup();
        }
        else {
            ui->R0_max->setText(settings->value("Axis value/R0_max").toString());
        }
    });
    connect(ui->R1_min, &QLineEdit::textChanged, this, [=] {
        if (ui->R1_min->text().toInt() >= 0 && ui->R1_min->text().toInt() < ui->R1_max->text().toInt()) {
            settings->beginGroup("Axis value");
            settings->setValue("R1_min", ui->R1_min->text());
            settings->endGroup();
        }
        else {
            ui->R1_min->setText(settings->value("Axis value/R1_min").toString());
        }
    });
    connect(ui->R1_max, &QLineEdit::textChanged, this, [=] {
        if (ui->R1_max->text().toInt() > ui->R1_min->text().toInt() && ui->R1_max->text().toInt() <= 999) {
            settings->beginGroup("Axis value");
            settings->setValue("R1_max", ui->R1_max->text());
            settings->endGroup();
        }
        else {
            ui->R1_max->setText(settings->value("Axis value/R1_max").toString());
        }
    });
    connect(ui->R2_min, &QLineEdit::textChanged, this, [=] {
        if (ui->R2_min->text().toInt() >= 0 && ui->R2_min->text().toInt() < ui->R2_max->text().toInt()) {
            settings->beginGroup("Axis value");
            settings->setValue("R2_min", ui->R2_min->text());
            settings->endGroup();
        }
        else {
            ui->R2_min->setText(settings->value("Axis value/R2_min").toString());
        }
    });
    connect(ui->R2_max, &QLineEdit::textChanged, this, [=] {
        if (ui->R2_max->text().toInt() > ui->R2_min->text().toInt() && ui->R2_max->text().toInt() <= 999 ) {
            settings->beginGroup("Axis value");
            settings->setValue("R2_max", ui->R2_max->text());
            settings->endGroup();
        }
        else {
            ui->R2_max->setText(settings->value("Axis value/R2_max").toString());
        }
    });
    connect(ui->A1_min, &QLineEdit::textChanged, this, [=] {
        if (ui->A1_min->text().toInt() >= 0 && ui->A1_min->text().toInt() < ui->A1_max->text().toInt()) {
            settings->beginGroup("Axis value");
            settings->setValue("A1_min", ui->A1_min->text());
            settings->endGroup();
        }
        else {
            ui->A1_min->setText(settings->value("Axis value/A1_min").toString());
        }
    });
    connect(ui->A1_max, &QLineEdit::textChanged, this, [=] {
        if (ui->A1_max->text().toInt() > ui->A1_max->text().toInt() && ui->A1_max->text().toInt() <= 999) {
            settings->beginGroup("Axis value");
            settings->setValue("A1_max", ui->A1_max->text());
            settings->endGroup();
        }
        else {
            ui->A1_max->setText(settings->value("Axis value/A1_max").toString());
        }
    });

    //
    connect(ui->BaudRate, &QLineEdit::textChanged, this, [=] {
        if (ui->BaudRate->text().toInt() >= 0 ) {
            settings->beginGroup("SerialPort");
            settings->setValue("baudrate", ui->BaudRate->text());
            settings->endGroup();
        }
        else {
            ui->BaudRate->setText(settings->value("SerialPort/baudrate").toString());
        }
    });
    connect(ui->Serverip, &QLineEdit::textChanged, this, [=] {
        settings->beginGroup("Server");
        settings->setValue("Serverip", ui->Serverip->text());
        settings->endGroup();
        server->server_ip = ui->Serverip->text();
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
        server->port = ui->Port->text().toInt();
    });

    //
    connect(ui->insert, &QLineEdit::textChanged, this, [=] {
        if (ui->insert->text().toInt() >= 0 ) {
            settings->beginGroup("Arithmetic");
            settings->setValue("insert", ui->insert->text());
            settings->endGroup();
        }
        else {
            ui->insert->setText(settings->value("Arithmetic/insert").toString());
        }
    });
    connect(ui->pitch, &QLineEdit::textChanged, this, [=] {
        if (ui->pitch->text().toInt() >= 0 ) {
            settings->beginGroup("Arithmetic");
            settings->setValue("pitch", ui->pitch->text());
            settings->endGroup();
        }
        else {
            ui->pitch->setText(settings->value("Arithmetic/pitch").toString());
        }
    });
    connect(ui->surge, &QLineEdit::textChanged, this, [=] {
        if (ui->surge->text().toInt() >= 0 ) {
            settings->beginGroup("Arithmetic");
            settings->setValue("surge", ui->surge->text());
            settings->endGroup();
        }
        else {
            ui->surge->setText(settings->value("Arithmetic/surge").toString());
        }
    });
    connect(ui->sway, &QLineEdit::textChanged, this, [=] {
        if (ui->sway->text().toInt() >= 0 ) {
            settings->beginGroup("Arithmetic");
            settings->setValue("sway", ui->sway->text());
            settings->endGroup();
        }
        else {
            ui->sway->setText(settings->value("Arithmetic/sway").toString());
        }
    });
    connect(ui->twist, &QLineEdit::textChanged, this, [=] {
        if (ui->twist->text().toInt() >= 0 ) {
            settings->beginGroup("Arithmetic");
            settings->setValue("twist", ui->twist->text());
            settings->endGroup();
        }
        else {
            ui->twist->setText(settings->value("Arithmetic/twist").toString());
        }
    });
    connect(ui->roll, &QLineEdit::textChanged, this, [=] {
        if (ui->roll->text().toInt() >= 0 ) {
            settings->beginGroup("Arithmetic");
            settings->setValue("roll", ui->roll->text());
            settings->endGroup();
        }
        else {
            ui->roll->setText(settings->value("Arithmetic/roll").toString());
        }
    });
    connect(ui->suck, &QLineEdit::textChanged, this, [=] {
        if (ui->suck->text().toInt() >= 0 ) {
            settings->beginGroup("Arithmetic");
            settings->setValue("suck", ui->suck->text());
            settings->endGroup();
        }
        else {
            ui->suck->setText(settings->value("Arithmetic/suck").toString());
        }
    });
    connect(ui->diff, &QLineEdit::textChanged, this, [=] {
        if (ui->diff->text().toInt() >= 50 &&  ui->diff->text().toInt() <= 999) {
            settings->beginGroup("Arithmetic");
            settings->setValue("speed", ui->diff->text());
            settings->endGroup();
        }
        else {
            ui->diff->setText(settings->value("Arithmetic/speed").toString());
        }
    });

    //
    connect(ui->language_combox, &QComboBox::currentIndexChanged, this, [=] {
        settings->beginGroup("language");
        settings->setValue("id", ui->language_combox->currentIndex());
        settings->endGroup();
        if (client_link){
            ui->wait_for_client_link->setText(language_setting->value(ui->language_combox->currentText()+"/client_link").toString()+ui->Serverip->text()+":"+ui->Port->text());
        }
        else{
            ui->wait_for_client_link->setText(language_setting->value(ui->language_combox->currentText()+"/wait_for_client_link").toString());
        }
        ui->load_scene->setText(language_setting->value(ui->language_combox->currentText()+"/load_scene").toString());
        ui->Axis_value->setText(language_setting->value(ui->language_combox->currentText()+"/Axis_value").toString());
        ui->Serial_and_server_setting->setText(language_setting->value(ui->language_combox->currentText()+"/Serial_and_server_setting").toString());
        ui->com_label->setText(language_setting->value(ui->language_combox->currentText()+"/com_label").toString());
        ui->BaudRate_label->setText(language_setting->value(ui->language_combox->currentText()+"/BaudRate_label").toString());
        ui->Serverip_label->setText(language_setting->value(ui->language_combox->currentText()+"/Serverip_label").toString());
        ui->arithmetic->setText(language_setting->value(ui->language_combox->currentText()+"/arithmetic").toString());
        ui->Port_label->setText(language_setting->value(ui->language_combox->currentText()+"/Port_label").toString());
        ui->language_setting->setText(language_setting->value(ui->language_combox->currentText()+"/language_setting").toString());
        ui->language->setText(language_setting->value(ui->language_combox->currentText()+"/language").toString());
    });
}




void MainWindow::btn_init(){
    connect(ui->run_btn,&QPushButton::clicked,this,[=]{
        if(!build_server){
            build_server = true;
            server->command = 1;
            ui->run_btn->setStyleSheet(btn_sty2);
            ui->run_btn->setEnabled(false);
        }
        else{
            server->command = 0;
            build_server = false;
        }
    });
    connect(ui->link_btn,&QPushButton::clicked,this,[=]{
        if (ui->port_id->count()){
            if(!port_link){
                port->baudrate = ui->BaudRate->text().toInt();
                port->port_id = ui->port_id->currentIndex();
                port->command = 1;
                ui->link_btn->setEnabled(false);
            }
            else{
                port->command = 0;
                ui->link_btn->setEnabled(false);
            }
        }
    });
}




void MainWindow::init(){
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
    client_link = false;
    build_server = false;
    last_file_path = "no";
    play = false;
    playtime = 0;
    ports_list = QSerialPortInfo::availablePorts();
    port_link = false;
    inserts = {};
    surges = {};
    sways = {};
    twists = {};
    pitchs = {};
    rolls = {};
    play_times = {};
    L0 = 500;
    L1 = 500;
    L2 = 500;
    R0 = 500;
    R1 = 500;
    R2 = 500;
    A1 = 0;
    last_L0 = 500;
    last_L1 = 500;
    last_L2 = 500;
    last_R0 = 500;
    last_R1 = 500;
    last_R2 = 500;
    last_A1 = 0;
    diff = 200;

    chartL0 = new QChart;
    chartL1 = new QChart;
    chartL2 = new QChart;
    chartR0 = new QChart;
    chartR1 = new QChart;
    chartR2 = new QChart;
    chartA1 = new QChart;
    seriesL0 = new QLineSeries;
    seriesL1 = new QLineSeries;
    seriesL2 = new QLineSeries;
    seriesR0 = new QLineSeries;
    seriesR1 = new QLineSeries;
    seriesR2 = new QLineSeries;
    seriesA1 = new QLineSeries;
    chartL0->addSeries(seriesL0);
    chartL1->addSeries(seriesL1);
    chartL2->addSeries(seriesL2);
    chartR0->addSeries(seriesR0);
    chartR1->addSeries(seriesR1);
    chartR2->addSeries(seriesR2);
    chartA1->addSeries(seriesA1);
    chartL0->createDefaultAxes();
    chartL1->createDefaultAxes();
    chartL2->createDefaultAxes();
    chartR0->createDefaultAxes();
    chartR1->createDefaultAxes();
    chartR2->createDefaultAxes();
    chartA1->createDefaultAxes();



    chartviewL0 = new QChartView;
    chartviewL1 = new QChartView;
    chartviewL2 = new QChartView;
    chartviewR0 = new QChartView;
    chartviewR1 = new QChartView;
    chartviewR2 = new QChartView;
    chartviewA1 = new QChartView;
    chartviewL0->setChart(chartL0);
    chartviewL1->setChart(chartL1);
    chartviewL2->setChart(chartL2);
    chartviewR0->setChart(chartR0);
    chartviewR1->setChart(chartR1);
    chartviewR2->setChart(chartR2);
    chartviewA1->setChart(chartA1);

    L0_Layout = new QHBoxLayout;
    L0_Layout->addWidget(chartviewL0);
    L1_Layout = new QHBoxLayout;
    L1_Layout->addWidget(chartviewL1);
    L2_Layout = new QHBoxLayout;
    L2_Layout->addWidget(chartviewL2);
    R0_Layout = new QHBoxLayout;
    R0_Layout->addWidget(chartviewR0);
    R1_Layout = new QHBoxLayout;
    R1_Layout->addWidget(chartviewR1);
    R2_Layout = new QHBoxLayout;
    R2_Layout->addWidget(chartviewR2);
    A1_Layout = new QHBoxLayout;
    A1_Layout->addWidget(chartviewA1);
    ui->L0_widget->setLayout(L0_Layout);
    ui->L1_widget->setLayout(L1_Layout);
    ui->L2_widget->setLayout(L2_Layout);
    ui->R0_widget->setLayout(R0_Layout);
    ui->R1_widget->setLayout(R1_Layout);
    ui->R2_widget->setLayout(R2_Layout);
    ui->A1_widget->setLayout(A1_Layout);

    timer1.setInterval(3000);
    timer2.setInterval(3000);
    timer3.setInterval(3000);

    server = new Bulid_server(this);
    port = new Port_thread(this);
    tips_window_init();
    m_animation = new QPropertyAnimation(tips_window, "windowOpacity");
    m_animation->setDuration(800);
    m_animation->setStartValue(0.8);
    m_animation->setEndValue(0.0);
    m_animation->setEasingCurve(QEasingCurve::OutQuart);

    page_init();
    config_init();
    btn_init();
    //
    connect(server,&Bulid_server::back_value,this,&MainWindow::back_value_change1);
    connect(port,&Port_thread::back_value,this,&MainWindow::back_value_change2);
    connect(&timer1, &QTimer::timeout, this, &MainWindow::delay_change1);
    connect(&timer2, &QTimer::timeout, this, &MainWindow::delay_change2);
    connect(&timer3, &QTimer::timeout, this, &MainWindow::tips_window_end);
    connect(m_animation, &QPropertyAnimation::finished, [=](){
        tips_window->hide();
    });
    server->start();
    port->start();
}




void MainWindow::back_value_change1(int num){
    switch(num){
    case -1:
        timer1.start();
        ui->run_btn->setStyleSheet(btn_sty4);
        ui->run_btn->setEnabled(false);
        client_link = false;
        ui->wait_for_client_link->setText(language_setting->value(ui->language_combox->currentText()+"/wait_for_client_link").toString());
        break;
    case 0:
        ui->run_btn->setStyleSheet(btn_sty1);
        ui->run_btn->setEnabled(true);
        client_link = false;
        break;
    case 1:
        ui->run_btn->setStyleSheet(btn_sty3);
        ui->run_btn->setEnabled(true);
        break;
    case 2:
        ui->wait_for_client_link->setText(language_setting->value(ui->language_combox->currentText()+"/client_link").toString()+ui->Serverip->text()+":"+ui->Port->text());
        client_link = true;
        break;
    case 3:
        if (last_file_path != server->file_path){
            qDebug() << "new scene start!";
            last_file_path = server->file_path;
            QString scence_path = last_file_path.replace("KK_osr_sr6_link","Studio/scene").replace(".txt",".png");
            last_file_path = server->file_path;
            QPixmap img = QPixmap((scence_path));
            img.scaled(ui->scene->size(),Qt::KeepAspectRatio);
            ui->scene->setPixmap(img);
            inserts.clear();
            surges.clear();
            sways.clear();
            twists.clear();
            pitchs.clear();
            rolls.clear();
            play_times.clear();
            QFile file(last_file_path);
            if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                break;
            }
            insert_max = 0;
            insert_min = 1;
            QTextStream in(&file);
            while (!in.atEnd()) {
                QString line = in.readLine();
                QStringList lines = line.split("/");
                inserts.append(lines[0].toFloat());
                surges.append(lines[1].toFloat());
                sways.append(lines[2].toFloat());
                twists.append(lines[3].toFloat());
                pitchs.append(lines[4].toFloat());
                rolls.append(lines[5].toFloat());
                play_times.append(lines[6].toFloat());
                duration = lines[7].toFloat();
                bodywidth = lines[8].toFloat();
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
                float surge_sum = 0;
                for (float value : surges) { surge_sum += value; }
                surge_offset = surge_sum / surges.count();
                float sway_sum = 0;
                for (float value : surges) { surge_sum += value; }
                surge_offset = sway_sum / sways.count();
            }
            file.close();


            if (play_times.count()){
                for (int i =0 ; i < play_times.count() ; i ++){
                    L0 = (int)((ui->L0_max->text().toInt()-ui->L0_min->text().toInt()) / (insert_max - insert_min) * inserts[i]) + ui->L0_min->text().toInt() - (ui->L0_max->text().toInt()-ui->L0_min->text().toInt())/(insert_max - insert_min)*insert_min ;
                    diff = qAbs(L0 - last_L0);
                    if (diff > ui->diff->text().toInt()){
                        if (L0 - last_L0 >0){L0 = last_L0 + ui->diff->text().toInt();}
                        else if (L0 - - last_L0 < 0 ){L0 = last_L0 - ui->diff->text().toInt();}
                    }
                    last_L0 = L0;

                    if (i == 0){ A1 = 0; }
                    else{
                        A1 = 10 * diff / 2;
                        diff = qAbs(A1 - last_A1);
                        if (diff > ui->diff->text().toInt()){
                            if (A1 - last_A1 >0){A1 = last_A1 + ui->diff->text().toInt();}
                            else if (A1 - last_A1 < 0 ){ A1 = last_A1 - ui->diff->text().toInt();}
                        }
                    }
                    last_A1 = A1;
                    if (A1 > ui->A1_max->text().toInt()) { A1 = ui->A1_max->text().toInt(); } else if (A1 < ui->A1_min->text().toInt()) { A1 = ui->A1_min->text().toInt(); }

                    L1 = (ui->L1_max->text().toInt()-ui->L1_min->text().toInt())/2 - (int)((surges[i] - surge_offset) * (ui->L1_max->text().toInt()-ui->L1_min->text().toInt()) / bodywidth / 2);
                    diff = qAbs(L1 - last_L1);
                    if (diff > ui->diff->text().toInt()){
                        if (L1 - last_L1 >0){L1 = last_L1 + ui->diff->text().toInt();}
                        else if (L1 - last_L1 < 0 ){L1 = last_L1 - ui->diff->text().toInt();}
                    }
                    last_L1 = L1;
                    if (L1 > ui->L1_max->text().toInt()) { L1 = ui->L1_max->text().toInt(); } else if (L1 < ui->L1_min->text().toInt()) { L1 = ui->L1_min->text().toInt(); }

                    L2 = (ui->L2_max->text().toInt()-ui->L2_min->text().toInt())/2 - (int)((sways[i] - sway_offset) * (ui->L1_max->text().toInt()-ui->L1_min->text().toInt()) / bodywidth / 2);
                    diff = qAbs(L2 - last_L2);
                    if (diff > ui->diff->text().toInt()){
                        if (L2 - last_L2 >0){L1 = last_L2 + ui->diff->text().toInt();}
                        else if (L2 - last_L2 < 0 ){L1 = last_L2 - ui->diff->text().toInt();}
                    }
                    last_L2 = L2;
                    if (L2 > ui->L2_max->text().toInt()) { L2 = ui->L2_max->text().toInt(); } else if (L2 < ui->L2_min->text().toInt()) {L2 = ui->L2_min->text().toInt();}

                    R1 = (ui->R1_max->text().toInt()+ui->R1_min->text().toInt())/2 + (int)((rolls[i]) * 11.1 );
                    diff = qAbs(R1 - last_R1);
                    if (diff > ui->diff->text().toInt()){
                        if (R1 - last_R1 >0){L1 = last_R1 + ui->diff->text().toInt();}
                        else if (R1 - last_R1 < 0 ){R1 = last_R1 - ui->diff->text().toInt();}
                    }
                    last_R1 = R1;
                    if (R1 > ui->R1_max->text().toInt()) { R1 = ui->R1_max->text().toInt(); } else if (R1 < ui->R1_min->text().toInt()) { R1 = ui->R1_min->text().toInt(); }

                    R2 = (ui->R2_max->text().toInt()-ui->R2_min->text().toInt())/2 - (int)((pitchs[i]) * 11.1 / 2);
                    diff = qAbs(R2 - last_R2);
                    if (diff > ui->diff->text().toInt()){
                        if (R2 - last_R2 >0){R1 = last_R2 + ui->diff->text().toInt();}
                        else if (R2 - last_R2 < 0 ){R2 = last_R2 - ui->diff->text().toInt();}
                    }
                    if (R2 > ui->R2_max->text().toInt()) { R2 = ui->R2_max->text().toInt(); } else if (R2 < ui->R2_min->text().toInt()) { R2 = ui->R2_min->text().toInt(); }

                    R0 = (ui->R0_max->text().toInt()-ui->R0_min->text().toInt())/2 + (int)((twists[i]) * 11.1 /2 );
                    diff = qAbs(R0 - last_R0);
                    if (diff > ui->diff->text().toInt()){
                        if (R0 - last_R0 >0){R0 = last_R0 + ui->diff->text().toInt();}
                        else if (R0 - last_R0 < 0 ){R0 = last_R0 - ui->diff->text().toInt();}
                    }
                    last_R0 = R0;
                    if (R0 > ui->R0_max->text().toInt()) { R0 = ui->R0_max->text().toInt(); } else if (R0 < ui->R0_min->text().toInt()) { R0 = ui->R0_min->text().toInt(); }

                    seriesL0->append(i, L0);
                    seriesL1->append(i, L1);
                    seriesL2->append(i, L2);
                    seriesR0->append(i, R0);
                    seriesR1->append(i, R1);
                    seriesR2->append(i, R2);
                    seriesA1->append(i, A1);
                }
                chartL0->removeSeries(seriesL0);
                chartL0->addSeries(seriesL0);
                chartL1->removeSeries(seriesL1);
                chartL1->addSeries(seriesL1);
                chartL2->removeSeries(seriesL2);
                chartL2->addSeries(seriesL2);
                chartR0->removeSeries(seriesR0);
                chartR0->addSeries(seriesR0);
                chartR1->removeSeries(seriesR1);
                chartR1->addSeries(seriesR1);
                chartR2->removeSeries(seriesR2);
                chartR2->addSeries(seriesR2);
                chartA1->removeSeries(seriesA1);
                chartA1->addSeries(seriesA1);
            }

        }
        if (play_times.count()){
            L0 = (int)((ui->L0_max->text().toInt()-ui->L0_min->text().toInt()) / (insert_max - insert_min) * inserts[server->index]) + ui->L0_min->text().toInt() - (ui->L0_max->text().toInt()-ui->L0_min->text().toInt())/(insert_max - insert_min)*insert_min ;
            diff = qAbs(L0 - last_L0);
            if (diff > ui->diff->text().toInt()){
                if (L0 - last_L0 >0){L0 = last_L0 + ui->diff->text().toInt();}
                else if (L0 - - last_L0 < 0 ){L0 = last_L0 - ui->diff->text().toInt();}
            }
            last_L0 = L0;

            A1 = 10 * diff / 2;
            diff = qAbs(A1 - last_A1);
            if (diff > ui->diff->text().toInt()){
                if (A1 - last_A1 >0){A1 = last_A1 + ui->diff->text().toInt();}
                else if (A1 - last_A1 < 0 ){ A1 = last_A1 - ui->diff->text().toInt();}
            }
            last_A1 = A1;
            if (A1 > ui->A1_max->text().toInt()) { A1 = ui->A1_max->text().toInt(); } else if (A1 < ui->A1_min->text().toInt()) { A1 = ui->A1_min->text().toInt(); }

            L1 = (ui->L1_max->text().toInt()-ui->L1_min->text().toInt())/2 - (int)((surges[server->index] - surge_offset) * (ui->L1_max->text().toInt()-ui->L1_min->text().toInt()) / bodywidth / 2);
            diff = qAbs(L1 - last_L1);
            if (diff > ui->diff->text().toInt()){
                if (L1 - last_L1 >0){L1 = last_L1 + ui->diff->text().toInt();}
                else if (L1 - last_L1 < 0 ){L1 = last_L1 - ui->diff->text().toInt();}
            }
            last_L1 = L1;
            if (L1 > ui->L1_max->text().toInt()) { L1 = ui->L1_max->text().toInt(); } else if (L1 < ui->L1_min->text().toInt()) { L1 = ui->L1_min->text().toInt(); }

            L2 = (ui->L2_max->text().toInt()-ui->L2_min->text().toInt())/2 - (int)((sways[server->index] - sway_offset) * (ui->L1_max->text().toInt()-ui->L1_min->text().toInt()) / bodywidth / 2);
            diff = qAbs(L2 - last_L2);
            if (diff > ui->diff->text().toInt()){
                if (L2 - last_L2 >0){L1 = last_L2 + ui->diff->text().toInt();}
                else if (L2 - last_L2 < 0 ){L1 = last_L2 - ui->diff->text().toInt();}
            }
            last_L2 = L2;
            if (L2 > ui->L2_max->text().toInt()) { L2 = ui->L2_max->text().toInt(); } else if (L2 < ui->L2_min->text().toInt()) {L2 = ui->L2_min->text().toInt();}

            R1 = (ui->R1_max->text().toInt()+ui->R1_min->text().toInt())/2 + (int)((rolls[server->index]) * 11.1 );
            diff = qAbs(R1 - last_R1);
            if (diff > ui->diff->text().toInt()){
                if (R1 - last_R1 >0){L1 = last_R1 + ui->diff->text().toInt();}
                else if (R1 - last_R1 < 0 ){R1 = last_R1 - ui->diff->text().toInt();}
            }
            last_R1 = R1;
            if (R1 > ui->R1_max->text().toInt()) { R1 = ui->R1_max->text().toInt(); } else if (R1 < ui->R1_min->text().toInt()) { R1 = ui->R1_min->text().toInt(); }

            R2 = (ui->R2_max->text().toInt()-ui->R2_min->text().toInt())/2 - (int)((pitchs[server->index]) * 11.1 / 2);
            diff = qAbs(R2 - last_R2);
            if (diff > ui->diff->text().toInt()){
                if (R2 - last_R2 >0){R1 = last_R2 + ui->diff->text().toInt();}
                else if (R2 - last_R2 < 0 ){R2 = last_R2 - ui->diff->text().toInt();}
            }
            if (R2 > ui->R2_max->text().toInt()) { R2 = ui->R2_max->text().toInt(); } else if (R2 < ui->R2_min->text().toInt()) { R2 = ui->R2_min->text().toInt(); }

            R0 = (ui->R0_max->text().toInt()-ui->R0_min->text().toInt())/2 + (int)((twists[server->index]) * 11.1 /2 );
            diff = qAbs(R0 - last_R0);
            if (diff > ui->diff->text().toInt()){
                if (R0 - last_R0 >0){R0 = last_R0 + ui->diff->text().toInt();}
                else if (R0 - last_R0 < 0 ){R0 = last_R0 - ui->diff->text().toInt();}
            }
            last_R0 = R0;
            if (R0 > ui->R0_max->text().toInt()) { R0 = ui->R0_max->text().toInt(); } else if (R0 < ui->R0_min->text().toInt()) { R0 = ui->R0_min->text().toInt(); }

            port->L0 = L0;
            port->L1 = L1;
            port->L1 = L2;
            port->R0 = R0;
            port->R1 = R1;
            port->R1 = R2;
            port->A1 = A1;
            ui->L0_slider->setSliderPosition(L0);
            ui->L1_slider->setSliderPosition(L1);
            ui->L2_slider->setSliderPosition(L2);
            ui->R0_slider->setSliderPosition(R0);
            ui->R1_slider->setSliderPosition(R1);
            ui->R2_slider->setSliderPosition(R2);
            ui->A1_slider->setSliderPosition(A1);
            ui->play_slider->setSliderPosition(server->index*100/play_times.count());
            port->sleep_time = server->sleep_time * 1000;
            //qDebug() << "L0:" << _L0 <<  "L1:" << _L1 << "L2:" << _L2 << "R0:" << _R0 << "R1:" << _R1 << "R2:" << _R2 << "A1:" << _A1 << "sleep_time:" << server->sleep_time;
            port->play = true;

            seriesL1->replace(server->index, QPointF(server->index,L1));
            seriesL2->replace(server->index, QPointF(server->index,L2));
            seriesR0->replace(server->index, QPointF(server->index,R0));
            seriesR1->replace(server->index, QPointF(server->index,R1));
            seriesR2->replace(server->index, QPointF(server->index,R2));
            seriesA1->replace(server->index, QPointF(server->index,A1));
            chartL0->series().replace(0,seriesL0);
            chartL1->series().replace(0,seriesL1);
            chartL2->series().replace(0,seriesL2);
            chartR0->series().replace(0,seriesR0);
            chartR1->series().replace(0,seriesR1);
            chartR2->series().replace(0,seriesR2);
            chartA1->series().replace(0,seriesA1);
        }
            break;

    }
}


void MainWindow::back_value_change2(int num){
    switch(num){
    case -1:
        timer2.start();
        ui->link_btn->setStyleSheet(btn_sty7);
        ui->link_btn->setEnabled(false);
        tips->setText(language_setting->value(ui->language_combox->currentText()+"/Serial_link_fail").toString());//language_setting->value(ui->language_combox->currentText()+"/Serial_link_fail").toString()
        tips_window_start();
        port_link = false;
        break;
    case 0:
        ui->link_btn->setStyleSheet(btn_sty5);
        ui->link_btn->setEnabled(true);//Close_com_succeed
        tips->setText(language_setting->value(ui->language_combox->currentText()+"/Close_com_succeed").toString());
        tips_window_start();
        port_link = false;
        break;
    case 1:
        ui->link_btn->setStyleSheet(btn_sty6);
        ui->link_btn->setEnabled(true);
        tips->setText(language_setting->value(ui->language_combox->currentText()+"/Serial_link_succeed").toString());//language_setting->value(ui->language_combox->currentText()+"/Serial_link_succeed").toString()
        tips_window_start();
        port_link = true;
        break;
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



void MainWindow::closeEvent(QCloseEvent* event){
    server->command = 0;
    while (server->command != -1){QThread::msleep(10);}
    server->end = true;
    while (server->Start){QThread::msleep(10);}
    server->quit();
    port->command = 0;
    while (server->command != -1){QThread::msleep(10);}
    port->end = true;
    while (port->Start){QThread::msleep(10);}
    port->quit();
}



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
    last_play_time = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}
