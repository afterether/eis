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
#ifndef IDENTICON_H
#define IDENTICON_H

#include <QObject>
#include <QQuickItem>
#include <QQuickPaintedItem>
#include <QImage>

class Identicon : public QQuickPaintedItem
{
    Q_OBJECT
public:    
    static const int ICON_DIMENSIONS = 8;
    explicit Identicon(QQuickItem *parent = nullptr);
    Q_PROPERTY(QString address READ get_address WRITE set_address NOTIFY addressChanged)
    Q_PROPERTY(int scale_factor READ get_scale_factor WRITE set_scale_factor NOTIFY scale_factorChanged)

    void paint(QPainter* painter);
    QString get_address();
    void set_address(QString p_address);
    static int calculate_image_dimensions(int scale_factor);
    void render_image();
    void set_scale_factor(int p_scale_factor);
    int get_scale_factor();

signals:    
    void addressChanged(QString address);
    void scale_factorChanged(int scale_factor);

public slots:

private:
    QString         address;        // Ethereum account address
    int             scale_factor;       // the original image is of 8x8 pixels, this field indicates how much times to scale the original image: 2 scales to 16x16,3 scales to 24x24,4 scales to 32x32,5 scales to 64x64, 6 scales to 128x148
    int             dimensions;         // width or height of the image in pixels (width=height always)
    QImage          icon_image;
};

#endif // IDENTICON_H
