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
#include <QPainter>
#include <QPen>
#include <QQuickItem>
#include "identicon.h"
#include "blockies.h"
#include "hqx4.h"
#include "hqx3.h"
#include "hqx2.h"
Identicon::Identicon(QQuickItem *parent) : QQuickPaintedItem(parent)
{
    setFlag( QQuickItem::ItemHasContents, true );

    // these are the defaults
    this->setWidth(8);
    this->setHeight(8);
    this->scale_factor=1;
    this->address=QString("");
}
QString Identicon::get_address() {
    return this->address;
}
void Identicon::set_address(QString p_address) {
    if (p_address.length()!=40) {
        return;
    }
    if (this->address!=p_address) {
        this->address=p_address;
        this->render_image();
        setFlag( QQuickItem::ItemHasContents, true );
        this->update();
        emit addressChanged(this->address);
    }
}
inline int Identicon::calculate_image_dimensions(int p_scale_factor) {

    if (p_scale_factor==5) return 64;
    if (p_scale_factor==6) return 128;
    int dim=p_scale_factor*ICON_DIMENSIONS;
    return dim;
}
void Identicon::set_scale_factor(int p_scale_factor) {
    if ((p_scale_factor>0) && (p_scale_factor<7)) {
        if (this->scale_factor!=p_scale_factor) {
            this->scale_factor=p_scale_factor;
            int dimensions=calculate_image_dimensions(p_scale_factor);
            this->setWidth(dimensions);
            this->setHeight(dimensions);
            this->render_image();
            setFlag( QQuickItem::ItemHasContents, true );
            this->update();
            emit scale_factorChanged(p_scale_factor);
        }
    }
}
int Identicon::get_scale_factor() {
    return this->scale_factor;
}
void Identicon::render_image() {

    if (this->address.length()!=40) return; // invalid address, nothing to render

    QImage image(ICON_DIMENSIONS,ICON_DIMENSIONS, QImage::Format_RGB32);

    Blockies::render_identicon2(&image,this->address,ICON_DIMENSIONS);
    switch(this->scale_factor) {
        case 1: {
            this->icon_image=image.copy();
            break;
        }
        case 2:
        case 3:
        case 4: {
            int scaled_width=Identicon::calculate_image_dimensions(this->scale_factor);
            int scaled_height=scaled_width;

            uchar *data=image.bits();
            uint32_t *data32_ptr=(uint32_t*) data;
            uint32_t output_size = scaled_width * scaled_height;
            uint32_t *output = (uint32_t*) malloc(output_size*sizeof(uint32_t));
            for (int i=0;i<output_size;i++) {
                output[i]=0xFFFFFFFF;
            }
            if (!output) return;
            switch(this->scale_factor) {
                case 2: {
                    hqx2::hq2x_32(data32_ptr,output,ICON_DIMENSIONS,ICON_DIMENSIONS);
                    break;
                }
                case 3: {
                    hqx3::hq3x_32(data32_ptr,output,ICON_DIMENSIONS,ICON_DIMENSIONS);
                    break;
                }
                case 4: {
                    hqx4::hq4x_32(data32_ptr,output,ICON_DIMENSIONS,ICON_DIMENSIONS);
                    break;
                }
            }
            QImage new_image((uchar*) output,scaled_width,scaled_height,QImage::Format_RGB32);
            this->icon_image=new_image.copy();
            this->dimensions=scaled_width;
            free(output);
            break;
        }
        case 5:
        case 6: {
            int scaled_width=Identicon::calculate_image_dimensions(4);
            int scaled_height=scaled_width;
            uchar *data=image.bits();
            uint32_t *data32_ptr=(uint32_t*) data;
            uint32_t output_size = scaled_width * scaled_height;
            uint32_t *output = (uint32_t*) malloc(output_size*sizeof(uint32_t));
            if (!output) return;
            hqx4::hq4x_32(data32_ptr,output,ICON_DIMENSIONS,ICON_DIMENSIONS);
            QImage new_image((uchar*) output,scaled_width,scaled_height,QImage::Format_RGB32);
            if (this->scale_factor==5) {
                this->dimensions=scaled_width*2;
            }
            if (this->scale_factor==6) {
                this->dimensions=scaled_width*4;
            }
            QImage new_image2;
            new_image2=new_image.scaled(this->dimensions,this->dimensions,Qt::IgnoreAspectRatio,Qt::FastTransformation);
            this->icon_image=new_image2.copy();
            free(output);
            break;
        }
    }
}
void Identicon::paint(QPainter* painter) {

    painter->drawImage(QPoint(0,0),this->icon_image);

}
