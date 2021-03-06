/*******************************************************************************
* This file is part of PlexyDesk.
*  Maintained by : Siraj Razick <siraj@kde.org>
*  Authored By  :
*
*  PlexyDesk is free software: you can redistribute it and/or modify
*  it under the terms of the GNU Lesser General Public License as published by
*  the Free Software Foundation, either version 3 of the License, or
*  (at your option) any later version.
*
*  PlexyDesk is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU Lesser General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with PlexyDesk. If not, see <http://www.gnu.org/licenses/lgpl.html>
*******************************************************************************/

#include <config.h>

#include <QtCore>
#include <QtGui>
#include <QDeclarativeComponent>
#include <QIcon>

#include <plexy.h>
// We do not use this for now. Commented.
//#include "plexyeventhandler.h"
#include "desktopview.h"
#include "plexytray.h"
#include <plexyconfig.h>
#include <baserender.h>
#include <pluginloader.h>
#include <datainterface.h>
#include <debug.h>


#ifdef Q_WS_X11
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include <X11/Xlib.h>
#include <QX11Info>

#include <netwm.h>
#endif


int main( int argc, char * *argv )
{
#ifndef Q_WS_MAC
    QApplication::setGraphicsSystem(QLatin1String("raster"));
#endif

    QByteArray debug_settings = qgetenv("PLEXYDESK_CONSOLE_DEBUG").toLower();

    if (debug_settings != "enable" && debug_settings != "true" && debug_settings != "1" ) {
       qInstallMsgHandler(plexyWindowsLogger);
    }

    QApplication app(argc, argv);

    QString appIconPath = PlexyDesk::Config::getInstance()->plexydeskBasePath() + "/share/plexy/plexydesk.png";
    QIcon appIcon=QIcon(QDir::toNativeSeparators(appIconPath));
    app.setWindowIcon(appIcon);
    app.setApplicationName(QString(PLEXYNAME));

#ifdef Q_WS_WIN
    QString pluginPath = PlexyDesk::Config::getInstance()->plexydeskBasePath() + "/lib/qt4/plugins/imageformats";
    app.addLibraryPath(QDir::toNativeSeparators(pluginPath));
#endif

    QGraphicsScene scene;
    scene.setBackgroundBrush(Qt::NoBrush);
    scene.setItemIndexMethod(QGraphicsScene::NoIndex);

    QSharedPointer<DesktopView> view = QSharedPointer<DesktopView>(new DesktopView(0));

/*
    // This is kept if we ever need a special event handler for the app and view
    PlexyEventHandler *eventHandle = new PlexyEventHandler();
    app.installEventFilter(eventHandle);
    view->installEventFilter(eventHandle);
*/

#ifdef Q_WS_MAC
    PlexyDesk::Config::getInstance()->setOpenGL(true);
#endif

    bool accel = PlexyDesk::Config::getInstance()->isOpenGL();

    // TODO: Multihead screen config handling
    QSize desktopSize = QDesktopWidget().screenGeometry().size();
#ifdef Q_WS_WIN
    // A 1px hack to make the widget fullscreen and not covering the toolbar on Win
    desktopSize.setHeight(desktopSize.height()-1);
#endif

    view->setWindowTitle(QString(PLEXYNAME));
    view->enableOpenGL(accel);

    view->setScene(&scene);

    view->addWallpaperItem();

    QObject::connect(view.data(), SIGNAL(closeApplication()), &app, SLOT(quit()));

    // TODO: Resolution changes handling
    QRect r = QDesktopWidget().screenGeometry();
#ifdef Q_WS_WIN
    // A 1px hack to make the widget fullscreen and not covering the toolbar on Win
    r.setHeight(r.height()-1); //win
#endif
    view->move(r.x(), r.y());
    view->resize(desktopSize);
    scene.setSceneRect(r);
    view->setSceneRect(r);
    view->ensureVisible(r);
    view->setDragMode(QGraphicsView::RubberBandDrag);

#ifdef Q_WS_X11
    NETWinInfo info(QX11Info::display(), view->winId(), QX11Info::appRootWindow(), NET::WMDesktop );
    info.setDesktop(NETWinInfo::OnAllDesktops);
    info.setWindowType(NET::Desktop);
#endif

    PlexyDesk::PluginLoader *loader = PlexyDesk::PluginLoader::getInstance();
    loader->scanDisk();
    view->show();

    view->setThemePack(PlexyDesk::Config::getInstance()->themepackName());
    view->showLayer(QLatin1String("Widgets"));
    view->registerPhotoDialog();

    // Set this to false if you need a "close to tray" functionality when systray exists
    QApplication::setQuitOnLastWindowClosed(true);

    /* Set tray icon */
    PlexyTray *trayIcon = new PlexyTray(view->window(), appIcon);

    return app.exec();
}
