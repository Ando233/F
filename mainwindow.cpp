#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QWebEngineView>
#include <QUrl>
#include <QSplitter>
#include <QWidget>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QFont>
#include <QList>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // ================= 左侧地图 =================
    QWebEngineView *mapView = new QWebEngineView(this);
    mapView->load(QUrl("qrc:/sources/map.html"));

    // ================= 右侧面板 =================
    QWidget *panel = new QWidget(this);
    panel->setMinimumWidth(360);
    panel->setMaximumWidth(430);

    QGridLayout *grid = new QGridLayout(panel);
    grid->setContentsMargins(22, 22, 22, 22);
    grid->setHorizontalSpacing(18);
    grid->setVerticalSpacing(16);

    // ================= 输入框与按钮 =================
    QLineEdit *cityEdit = new QLineEdit("北京", panel);
    QPushButton *cityButton = new QPushButton("SetCity", panel);

    QLineEdit *startEdit = new QLineEdit("北方工业大学", panel);
    QPushButton *startButton = new QPushButton("SetStarting", panel);

    QLineEdit *endEdit = new QLineEdit("天安门", panel);
    QPushButton *endButton = new QPushButton("SetEnding", panel);

    grid->addWidget(cityEdit, 0, 0, 1, 2);
    grid->addWidget(cityButton, 0, 2);

    grid->addWidget(startEdit, 1, 0, 1, 2);
    grid->addWidget(startButton, 1, 2);

    grid->addWidget(endEdit, 2, 0, 1, 2);
    grid->addWidget(endButton, 2, 2);

    // ================= 经纬度 =================
    QLabel *lngTitle = new QLabel("经度", panel);
    QLabel *latTitle = new QLabel("纬度", panel);

    QLineEdit *lngEdit = new QLineEdit("116.206490", panel);
    QLineEdit *latEdit = new QLineEdit("39.929413", panel);

    grid->addWidget(lngTitle, 3, 0);
    grid->addWidget(latTitle, 3, 1);

    grid->addWidget(lngEdit, 4, 0);
    grid->addWidget(latEdit, 4, 1);

    // ================= 信号灯状态 =================
    QLabel *lightText = new QLabel("当前信号灯状态", panel);
    QLabel *lightIcon = new QLabel("●  ○  ○", panel);
    lightIcon->setAlignment(Qt::AlignCenter);
    lightIcon->setStyleSheet("color: green; font-size: 22px; font-weight: bold;");

    grid->addWidget(lightText, 5, 0, 1, 2);
    grid->addWidget(lightIcon, 5, 2);

    // ================= 剩余时间 =================
    QLabel *remainText = new QLabel("剩余时间", panel);
    QLabel *remainValue = new QLabel("10s", panel);

    grid->addWidget(remainText, 6, 0, 1, 2);
    grid->addWidget(remainValue, 6, 2);

    // ================= 当前车速 =================
    QLabel *currentSpeed = new QLabel("当前车速\n35km/h", panel);
    grid->addWidget(currentSpeed, 7, 0, 1, 2);

    // ================= 车辆示意 =================
    QLabel *carLabel = new QLabel("🚗", panel);
    carLabel->setAlignment(Qt::AlignCenter);
    carLabel->setStyleSheet("font-size: 80px;");
    grid->addWidget(carLabel, 7, 2, 2, 1);

    // ================= 建议车速 =================
    QLabel *suggestSpeed = new QLabel("建议车速\n50km/h", panel);
    grid->addWidget(suggestSpeed, 8, 0, 1, 2);

    // ================= 字体设置 =================
    QList<QLabel *> labels = panel->findChildren<QLabel *>();
    for (QLabel *label : labels) {
        QFont font = label->font();
        font.setPointSize(12);
        font.setBold(true);
        label->setFont(font);
    }

    QList<QLineEdit *> edits = panel->findChildren<QLineEdit *>();
    for (QLineEdit *edit : edits) {
        QFont font = edit->font();
        font.setPointSize(11);
        edit->setFont(font);
        edit->setMinimumHeight(30);
    }

    QList<QPushButton *> buttons = panel->findChildren<QPushButton *>();
    for (QPushButton *button : buttons) {
        QFont font = button->font();
        font.setPointSize(11);
        font.setBold(true);
        button->setFont(font);
        button->setMinimumHeight(30);
    }

    // ================= 左右分栏 =================
    QSplitter *splitter = new QSplitter(this);
    splitter->addWidget(mapView);
    splitter->addWidget(panel);

    splitter->setStretchFactor(0, 5);
    splitter->setStretchFactor(1, 2);

    setCentralWidget(splitter);

    resize(1100, 700);
    setWindowTitle("MainWindow");
}

MainWindow::~MainWindow()
{
    delete ui;
}
