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
#include "blockies.h"
#include <QDebug>
#include <QColor>
#include <QImage>
#include <QPainter>

Blockies::Blockies(QObject *parent) : QObject(parent)
{

}
QColor Blockies::create_color(long *rand_seed) {

    //saturation is the whole color spectrum
    int h=(int) floor(Blockies::rand(rand_seed)*360);

    double sdouble= (Blockies::rand(rand_seed)*60+40);
    sdouble= sdouble*255/100; // convert from percentage to the actual value according to the model
    int s=(int) sdouble;
    double aux= Blockies::rand(rand_seed) +
                Blockies::rand(rand_seed) +
                Blockies::rand(rand_seed) +
                Blockies::rand(rand_seed);
    //aux=aux*25;
    aux=aux*25;
    double ldouble=aux*255/100;

    int l=(int) ldouble;
    QColor color;
    color.setHsl(h,s,l,255);
    return color;
}
void Blockies::init_rand_seed(long *rand_seed,const char *data,int data_len) {

    for (int i=0;i<data_len;i++) {
        int rotated32=rand_seed[i%4];
        rotated32=rotated32 << 5;
        int charcode=data[i];
        long substraction=rotated32-rand_seed[i%4];
        long addition=substraction+charcode;
        rand_seed[i%4]=addition;
    }

}
double Blockies::rand(long *rand_seed) {

    int v1,v2;

    v1=rand_seed[0] << 11;
    int pre_t=rand_seed[0];
    pre_t=pre_t<<11;
    long t=rand_seed[0] ^ pre_t;

    rand_seed[0]=rand_seed[1];
    rand_seed[1]=rand_seed[2];
    rand_seed[2]=rand_seed[3];
    v1=rand_seed[3];
    v1=v1>>19;

    v2=t;
    v2=v2>>8;
    int aux0=rand_seed[3] ^ v1;
    int aux1 = aux0 ^ t ^ v2;
    rand_seed[3]=aux1;

    uint rs=(uint) rand_seed[3];
    float v=(float) rs;
    uint tmp=1<<31;
    float d=(float) tmp;

    double output=v / d;

    return output;
}

void Blockies::create_image_data(QByteArray *data,long *rand_seed,int p_dimensions) {

    if (data==nullptr) return;

    int height=p_dimensions /*Blockies::IMAGE_SIZE*/;
    int data_width=p_dimensions/2; /*Blockies::IMAGE_SIZE/2; */

    QByteArray mirror_row;
    for (int y=0; y< height; y++) {
        mirror_row.clear();
        for (int x=0; x<data_width; x++) {

            double rvar=Blockies::rand(rand_seed);
            double result=floor(rvar*2.3);

            int datum=(int) result;

            data->append(datum);
            mirror_row.append(datum);
        }
        for(int i=mirror_row.size()-1;i>=0; i--) {      // copy data in reverse order to create a mirror
            data->append(mirror_row[i]);
        }
    }

}
void Blockies::render_identicon(QPainter *painter,QString address,int p_dimensions) {
    if (p_dimensions%2) {
        return;         // dimension must be divisible by 2
    }
    if (address.length()!=40) return; // not an Ethereum address (without 0x prepended)
    address=address.toLower();

    long rand_seed[4]  __attribute__ ((aligned (64))) = {0,0,0,0};

    QByteArray data_arr = address.toLatin1();
    const char *addr_data = data_arr.data();
    Blockies::init_rand_seed(rand_seed,addr_data,40);

    QColor color=Blockies::create_color(rand_seed);
    QColor bg_color=Blockies::create_color(rand_seed);
    QColor spotcolor=Blockies::create_color(rand_seed);
    QByteArray data;
    Blockies::create_image_data(&data,rand_seed,p_dimensions);
    int width=p_dimensions;
    int height=p_dimensions;
    QImage account_avatar(width, height, QImage::Format_RGB32);

    painter->setRenderHint(QPainter::Antialiasing);
    QRect image_rect(0,0,p_dimensions*SCALE,p_dimensions*SCALE);
    painter->fillRect(image_rect,bg_color);
    int len=data.size();
    for (int i=0;i<len;i++) {
        int datum=data[i];
        if (datum>0) {
            int row=(int) floor(i/width);
            int col=(int) i % width;
            QRect datumRect(col*SCALE,row*SCALE,SCALE,SCALE);
            if (datum==1) {
                painter->fillRect(datumRect,color);
            } else {
                painter->fillRect(datumRect,spotcolor);
            }
        } else {

        }
    }
}
void Blockies::render_identicon2(QImage *image,QString address,int p_dimensions) {
    if (p_dimensions%2) {
        return;         // dimension must be divisible by 2
    }
    if (address.length()!=40) return; // not an Ethereum address (without 0x prepended)
    address=address.toLower();

    long rand_seed[4]  __attribute__ ((aligned (64))) = {0,0,0,0};

    QByteArray data_arr = address.toLatin1();
    const char *addr_data = data_arr.data();
    Blockies::init_rand_seed(rand_seed,addr_data,40);

    QColor color=Blockies::create_color(rand_seed);
    QColor bg_color=Blockies::create_color(rand_seed);
    QColor spotcolor=Blockies::create_color(rand_seed);
    QByteArray data;
    Blockies::create_image_data(&data,rand_seed,p_dimensions);
    int width=p_dimensions;
    int height=p_dimensions;
    for (int y=0;y<height;y++) {
        for (int x=0;x<width;x++) {
            for(int y_minor=0;y_minor<SCALE;y_minor++) {
                for (int x_minor=0;x_minor<SCALE;x_minor++) {
                    int scaled_y,scaled_x;
                    scaled_y=y*SCALE+y_minor;
                    scaled_x=x*SCALE+x_minor;
                    image->setPixel(scaled_x, scaled_y, bg_color.rgb());
                }
            }
        }
    }
    int len=data.size();
    for (int i=0;i<len;i++) {
        int datum=data[i];
        if (datum>0) {
            int row=(int) floor(i/width);
            int col=(int) i % width;
            if (datum==1) {
                for(int y_minor=0;y_minor<SCALE;y_minor++) {
                    for (int x_minor=0;x_minor<SCALE;x_minor++) {
                        int scaled_y,scaled_x;
                        scaled_y=row*SCALE+y_minor;
                        scaled_x=col*SCALE+x_minor;
                        image->setPixel(scaled_x, scaled_y, color.rgb());
                    }
                }

            } else {
                for(int y_minor=0;y_minor<SCALE;y_minor++) {
                    for (int x_minor=0;x_minor<SCALE;x_minor++) {
                        int scaled_y,scaled_x;
                        scaled_y=row*SCALE+y_minor;
                        scaled_x=col*SCALE+x_minor;
                        image->setPixel(scaled_x, scaled_y, spotcolor.rgb());
                    }
                }
            }
        }
    }
}
