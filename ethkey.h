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
#ifndef ETHKEY_H
#define ETHKEY_H

#include <QObject>

class EthKey : public QObject
{
    Q_OBJECT
public:
    explicit EthKey(QObject *parent = nullptr);
    Q_PROPERTY(QString address READ get_address WRITE set_address NOTIFY address_changed)
    Q_PROPERTY(QString private_key READ get_private_key WRITE set_private_key NOTIFY private_key_changed)
    Q_PROPERTY(QString key_json READ get_key_json WRITE set_key_json NOTIFY key_json_changed)

    QString get_address();
    QString get_private_key();
    QString get_key_json();

    void set_address(QString p_address);
    void set_private_key(QString p_private_key);
    void set_key_json(QString p_key_json);

signals:
    void address_changed(QString address);
    void private_key_changed(QString private_key);
    void key_json_changed(QString key_json);

public slots:

private:
    QString         address;
    QString         private_key;
    QString         key_json;
};

#endif // ETHKEY_H
