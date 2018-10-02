#include "desktopwallpapermanager.h"
#include "Shobjidl.h"
#include <string>
#include <QFileDialog>
#include <QDebug>
#include <iostream>
#include <QDesktopServices>
#include <QProcess>
#include <QTextCodec>
#include <QStringList>


//#if _MSC_VER >= 1600
//#pragma execution_character_set("utf-8")
//#endif

DesktopWallpaperManager::DesktopWallpaperManager()
{
    HRESULT hr = CoInitialize(NULL);
    hr = CoCreateInstance(__uuidof(DesktopWallpaper), NULL, CLSCTX_ALL, IID_PPV_ARGS(&pDesktopWallpaper));
}

DesktopWallpaperManager::~DesktopWallpaperManager()
{

}

bool DesktopWallpaperManager::init()
{
    HRESULT hr = CoInitialize(NULL);
    hr = CoCreateInstance(__uuidof(DesktopWallpaper), NULL, CLSCTX_ALL, IID_PPV_ARGS(&pDesktopWallpaper));

    if(FAILED(hr))
    {
        return false;
    }
    else
    {
        return true;
    }
}

unsigned int DesktopWallpaperManager::getMonitorNum()
{
    HRESULT hr = pDesktopWallpaper->GetMonitorDevicePathCount(&monNum);
    if(hr==S_OK)
    {
        return monNum;
    }
    else
    {
        return 0;
    }
}

unsigned int DesktopWallpaperManager::getRealMonitorNum()
{
    return realMonNum;
}

QStringList DesktopWallpaperManager::getAllWallpaperUrl()
{
    QStringList urlList;
    realMonNum = 0;
    if(getMonitorNum())
    {
        for(unsigned int i=0;i<monNum;i++)
        {
            LPWSTR  wallpaper,monId;
            RECT displayRECT;
            HRESULT hr;

            hr = pDesktopWallpaper->GetMonitorDevicePathAt(i,&monId);
            if(hr==S_OK)
            {
                hr = pDesktopWallpaper->GetMonitorRECT(monId,&displayRECT);
                if(hr==S_OK)
                {
                    realMonNum = realMonNum + 1;
                    hr = pDesktopWallpaper->GetWallpaper(monId,&wallpaper);
                    if(hr==S_OK)
                    {
                        //qDebug() << "QString::fromWCharArray(wallpaper) : " << QString::fromWCharArray(wallpaper);
                        urlList << QString::fromWCharArray(wallpaper).replace("\\", "/");
                    }
                    else
                    {
                        //GetWallpaper Exception
                        //urlList.clear();
                        //return urlList;
                    }
                }
                else
                {
                    //GetMonitorRECT Exception
                    //urlList.clear();
                    //return urlList;
                }

            }
            else
            {
                //GetMonitorDevicePathAt Exception
                //urlList.clear();
                //return urlList;
            }
        }
    }
    else
    {
        return urlList;
    }
    return urlList;
}


void DesktopWallpaperManager::test()
{
    HRESULT thr;
    UINT mNum;
    IShellItemArray *images;
    LPWSTR monId;
    pDesktopWallpaper->GetSlideshow(&images);
    pDesktopWallpaper->GetMonitorDevicePathCount(&mNum);
    qDebug() <<"mNum:" << mNum;
    for(unsigned int i=0;i<mNum;i++)
    {
        LPWSTR  wallpaper;
        RECT displayRECT;
        //qDebug() << i;
        thr = pDesktopWallpaper->GetMonitorDevicePathAt(i,&monId);
        qDebug() << "GetMonitorDevicePathAt result:" << thr << " monId:" <<  QString::fromWCharArray(monId);
        thr = pDesktopWallpaper->GetMonitorRECT(monId,&displayRECT);
        if(thr==S_OK)
        {
            thr = pDesktopWallpaper->GetWallpaper(monId,&wallpaper);
            qDebug() << "GetWallpaper result:" << thr << " wallpaper:" <<  QString::fromWCharArray(wallpaper) ;

            QString path = QString::fromWCharArray(wallpaper);
            path.replace("\\", "/");
            QDesktopServices::openUrl(QUrl::fromLocalFile(path));
            //QProcess::startDetached("explorer "+path);//打开上面获取的目录
        }
        break;
    }


}

