
#ifndef PLEXY_BACK_PLUGIN_H
#define PLEXY_BACK_PLUGIN_H 

#include <plexy.h>
#include <config.h>
#include <baseplugin.h>
#include <QtCore>
#include <QtGui>

namespace PlexyDesk
{
    class BackdropPlugin : public BasePlugin
    {
        Q_OBJECT
        public :
                BackdropPlugin(QObject  * object = 0): BasePlugin(object){}
                virtual ~BackdropPlugin(){}
                virtual void render(QPainter *p,QRectF r) = 0;
        public slots:
                virtual void pushData(QVariant&) = 0;
        signals:
                virtual void data(QVariant&)=0;

     };
}
#endif