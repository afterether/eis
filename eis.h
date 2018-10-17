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
#ifndef EIS_H
#define EIS_H

#include <QObject>
#include <QString>
#include "ethkey.h"

class EIS : public QObject
{
    Q_OBJECT
public:
    explicit EIS(QObject *parent = nullptr);
    Q_INVOKABLE bool generate_ethereum_key(EthKey *key);
    Q_INVOKABLE bool save_key_to_file(QString output_directory,QString password,EthKey *key);

signals:
    void key_generated(QString private_key,QString address,QString key_json);

public slots:
};

#endif // EIS_H
