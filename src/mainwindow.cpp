#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "desktopwallpapermanager.h"
#include "imagelabel.h"
#include <QSystemTrayIcon>
#include <QDebug>
#include <QStringList>
#include <QListWidget>
#include <QLabel>
#include <QPixmap>
#include <QList>
#include <QDesktopServices>


#if _MSC_VER >= 1600
//#pragma execution_character_set("utf-8")
#endif

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setImageLabels();

    ui->centralWidget->setLayout(ui->centerLayout);

    //setTrayIcon();
    //trayIcon->show();

    QSize windowSize(838,376);
    this->setFixedSize(windowSize);
    QPalette palette;
    palette.setColor(QPalette::Background,QColor("black"));
    this->setPalette(palette);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    qDebug() << "width:" << this->width() << " height:"<<this->height();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    //this->hide();
    //event->ignore();
    event->accept();
}

void MainWindow::setImageLabels()
{
    wallpaperLabelList.clear();
    dwm = new DesktopWallpaperManager();
    dwm->init();
    QStringList urlList = dwm->getAllWallpaperUrl();
   // qDebug() << "urlList.at(0)" << urlList.at(0);

    unsigned int monNum = dwm->getRealMonitorNum();
    //qDebug() << monNum;
    for(unsigned int i=0;i<monNum;i++)
    {
        int times = 2;
        QSize labelSize(192*times,108*times);
        ImageLabel *imageContainer = new ImageLabel(urlList.at(i),this);
        wallpaperLabelList.append(imageContainer);
        QPixmap pixmap(urlList.at(i));
        pixmap = pixmap.scaled(labelSize,Qt::KeepAspectRatioByExpanding,Qt::SmoothTransformation);
        //pixmap = pixmap.scaledToHeight(300,Qt::SmoothTransformation);
        imageContainer->setImageUrl(urlList.at(i));
        imageContainer->setAlignment(Qt::AlignCenter);
        imageContainer->setPixmap(pixmap);
        imageContainer->setAutoFillBackground(true);
        imageContainer->setMaximumSize(labelSize);
        connect(imageContainer,SIGNAL(clicked(QString)),this,SLOT(openImage(QString)));

        ui->wallpapersLayout->addWidget(imageContainer);
        qDebug() << urlList.at(i);

    }
}

void MainWindow::setTrayIcon()
{
    trayIcon = new QSystemTrayIcon(this);
    tiMeun = new QMenu(this);
    showAction = new QAction(tiMeun);
    exitAction = new QAction(tiMeun);

    showAction->setText("Show");
    exitAction->setText("Exit");

    tiMeun->addAction(showAction);
    tiMeun->addAction(exitAction);

    connect(showAction, &QAction::triggered, this, &MainWindow::showWindow);
    connect(exitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    trayIcon->setContextMenu(tiMeun);
    trayIcon->setToolTip("Windows Wallpaper");
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(tiAction(QSystemTrayIcon::ActivationReason)));
}

void MainWindow::tiAction(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason)
    {
    //case QSystemTrayIcon::Trigger:
    //    qDebug() << "trigger" ;
    //    break;
    //case QSystemTrayIcon::Unknown:
    //    qDebug() << "unknow";
    //    break;
    case QSystemTrayIcon::DoubleClick:
        showWindow();
        //qDebug() << "dobuleClick";
        break;
    //case QSystemTrayIcon::MiddleClick:
    //    qDebug() << "middleclick";
    //    break;
    }
}

void MainWindow::showMenu()
{
    tiMeun->show();
}

void MainWindow::showWindow()
{
    this->show();
}

void MainWindow::showMessage()
{
    trayIcon->showMessage("Information",//消息窗口标题
        "There is a new message!",//消息内容
        QSystemTrayIcon::MessageIcon::Information,//消息窗口图标
        5000);//消息窗口显示时长
}

void MainWindow::openImage(QString imageUrl)
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(imageUrl));
    qDebug() << "open Image " << imageUrl;
}
