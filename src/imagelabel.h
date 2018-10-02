#ifndef IMAGELABEL_H
#define IMAGELABEL_H

#include <QLabel>

class ImageLabel : public QLabel
{
    Q_OBJECT
public:
    ImageLabel(QString strUrl,QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    QString getImageUrl();
    void setImageUrl(QString);
    void setImageSize(QSize);

private:
    QString imageUrl;


protected:
    void mousePressEvent(QMouseEvent* event);
    void resizeEvent(QResizeEvent *event);

signals:
    void clicked(QString);

};

#endif // IMAGELABEL_H
