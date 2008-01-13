#include "backdrop.h"
#include "backdropitem.h"
#include <desktopwidget.h>
#include "pictureflow.h"

ClassicBackdrop::ClassicBackdrop(QObject * object):QObject(object)
{
    bg = QPixmap("/usr/share/plexy/skins/default/default.png");

    width = QDesktopWidget().availableGeometry().width();
    height = QDesktopWidget().availableGeometry().height();
    
    img = QImage(width,height,QImage::Format_ARGB32_Premultiplied);
    QPainter p;
    p.begin(&img);
    p.drawPixmap(QRect(0,0,width,height),bg);
    p.end();

    paint.setTextureImage(img);
}

ClassicBackdrop::~ClassicBackdrop()
{

}

QGraphicsItem * ClassicBackdrop::backdrop()
{

QPushButton * btn = new QPushButton("hi");
PictureFlow* w = new PictureFlow; 
w->setSlideSize(QSize(50, 50));
w->resize(300,150);
w->setBackgroundColor(Qt::white);


return new PlexyDesk::DesktopWidget(QRect(0,0,200,200),w);

//return new  PlexyDesk::BackdropItem(QRectF(0,0,200,200));//QGraphicsPixmapItem(QPixmap("/home/siraj/downloads-torrents/wallpaper/water.png"));
}

void ClassicBackdrop::render(QPainter *p,QRectF r)
{
   // QRect er = p->matrix().inverted().mapRect(QRect(r.x(),r.y(),r.width(),r.height())).adjusted(-1, -1, 1, 1);
    p->fillRect(r.x(),r.y(),r.width(),r.height(),paint);
//	p->drawImage(r,img);
	//p->drawPixmap(r.x(),r.y(),r.width(),r.height(),bg);
}

Q_EXPORT_PLUGIN2(ClassicBackdrop,ClassicBackdrop)
#include "backdrop.moc"
