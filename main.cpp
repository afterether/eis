/*
    Copyright 2018 The AfterEther Team
    This file is part of the AfterEther Wallet

    AfterEther Wallet is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    AfterEther Wallet is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with EthBot. If not, see <http://www.gnu.org/licenses/>.
*/
#include <QDebug>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QQmlContext>
#include <QQuickStyle>
#include <QSettings>
#include <QMetaType>
#include <QFontDatabase>

#include "eis.h"
#include "identicon.h"
#include "ethkey.h"
#include "hqx.h"
#include "hqx4.h"

uint32_t   hqx::RGBtoYUV[16777216];

int main(int argc, char *argv[])
{
    hqx::hqxInit();
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<EIS>("org.afterether.eis",1,0,"EIS");
    qmlRegisterType<Identicon>("org.afterether.eis.identicon",1,0,"Identicon");
    qmlRegisterType<EthKey>("org.afterether.eis.ethkey",1,0,"EthKey");


    QQmlApplicationEngine engine;
    QQuickStyle::setStyle("Material");

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

