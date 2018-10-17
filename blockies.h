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
#ifndef BLOCKIES_H
#define BLOCKIES_H

#include <QObject>
#include <QByteArray>
#include <QImage>
#include <QPainter>

// Source: https://github.com/ethereum/blockies/blob/master/blockies.js
class Blockies : public QObject
{
    Q_OBJECT

public:
    static const int SCALE = 1;
    explicit Blockies(QObject *parent = nullptr);
    static QColor create_color(long *rand_seed);
    static void init_rand_seed(long *rand_seed,const char *data,int data_len);
    static double rand(long *rand_seed);
    static void create_image_data(QByteArray *data,long *rand_seed,int p_dimensions);
    static void render_identicon(QPainter *painter,QString address,int p_dimensions);
    static void render_identicon2(QImage *image,QString address,int p_dimensions);
signals:

public slots:
};

#endif // BLOCKIES_H
