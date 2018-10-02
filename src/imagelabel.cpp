#include "imagelabel.h"
#include <QDebug>

ImageLabel::ImageLabel(QString strUrl,QWidget* parent,Qt::WindowFlags f):QLabel(parent)
{

    setImageUrl(strUrl);
}

void ImageLabel::mousePressEvent(QMouseEvent* event)
{
    emit clicked(imageUrl);
}

void ImageLabel::resizeEvent(QResizeEvent* event)
{
    //qDebug() << "image resize";

}

void ImageLabel::setImageSize(QSize size)
{
}

void ImageLabel::setImageUrl(QString strUrl)
{
    imageUrl = strUrl;
}

QString ImageLabel::getImageUrl()
{
    return imageUrl;
}
