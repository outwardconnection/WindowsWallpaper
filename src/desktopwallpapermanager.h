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
    unsigned int getRealMonitorNum();
    void test();
    QStringList getAllWallpaperUrl();

private:
    IDesktopWallpaper *pDesktopWallpaper = nullptr;
    unsigned int getMonitorNum();
    unsigned int realMonNum = 0;
    unsigned int monNum = 0;


};

#endif // DESKTOPWALLPAPERMANAGER_H
