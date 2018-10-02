#ifndef DESKTOPWALLPAPERMANAGER_H
#define DESKTOPWALLPAPERMANAGER_H

#include <QObject>
#include <string>
#include "Shobjidl.h"

struct IDesktopWallpaper;
class QStringList;

class DesktopWallpaperManager : public QObject
{
    Q_OBJECT
public:
    DesktopWallpaperManager();
    ~DesktopWallpaperManager();
    bool init();
    unsigned int getMonitorNum();
    void test();
    QStringList getAllWallpaperUrl();

private:
    IDesktopWallpaper *pDesktopWallpaper = nullptr;
    unsigned int monNum = 0;


};

#endif // DESKTOPWALLPAPERMANAGER_H
