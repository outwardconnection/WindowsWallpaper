#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QCloseEvent>

namespace Ui {
class MainWindow;
}

class DesktopWallpaperManager;class ImageLabel;
class QLabel;class QListWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event);
    void resizeEvent(QResizeEvent *event);
    void showWindow();//显示窗体
    void showMessage();//消息框
    void showMenu();//显示菜单

private:
    DesktopWallpaperManager *dwm = nullptr;
    Ui::MainWindow *ui;
    QSystemTrayIcon *trayIcon = nullptr;

    QMenu *tiMeun = nullptr;
    QAction *showAction = nullptr;
    QAction *exitAction = nullptr;

    QList<ImageLabel*> wallpaperLabelList;

    void setTrayIcon();
    void setImageLabels();

private slots:
    void tiAction(QSystemTrayIcon::ActivationReason reason);
    void openImage(QString imageUrl);
};

#endif // MAINWINDOW_H
