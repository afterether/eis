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
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonValue>
#include <QQmlEngine>
#include <QByteArray>
#include <QDateTime>
#include <QFile>
#include "eis.h"
#include "/home/ethbot/src/github.com/afterether/eacct/libeacct.h"

EIS::EIS(QObject *parent) : QObject(parent)
{

}
bool EIS::generate_ethereum_key(EthKey *key) {
    char key_json_str[1024];
    char err_str[1024];
    int output_len;

    if (key==nullptr) return false;
    int err_code=Generate_key(key_json_str,&output_len,err_str);
    key_json_str[output_len]=0;

    if (!err_code) {
        if ((output_len<1024) && (output_len>0)) {
            QByteArray key_json_bytes(key_json_str);
            QJsonParseError jerr;
            QJsonDocument d = QJsonDocument::fromJson(key_json_bytes,&jerr);
            QJsonObject json=d.object();
            key->set_address(json.value(QString("address")).toString());
            key->set_private_key(json.value(QString("privatekey")).toString());
            key->set_key_json(QString(key_json_bytes));
            return true;            
        }
    }
    return false;
}
bool EIS::save_key_to_file(QString output_directory,QString password,EthKey *key) {
    if (key==nullptr) return false;
    char encrypted_key_json_str[1024];
    int encrypted_key_json_len=0;
    int unencrypted_key_len=0;

    QByteArray key_bytes = key->get_key_json().toLatin1();
    char *unencrypted_key_ptr=(char*) key_bytes.data();
    unencrypted_key_len=key_bytes.size();

    QByteArray password_bytes=password.toLatin1();
    char *password_ptr=(char*) password_bytes.data();

    int err_code=Encrypt_key(encrypted_key_json_str,&encrypted_key_json_len,unencrypted_key_ptr,unencrypted_key_len,password_ptr);
    if (err_code!=0) {
        return false;
    }
    encrypted_key_json_str[encrypted_key_json_len]=0;
    QByteArray final_json(encrypted_key_json_str);
    QDateTime cdt = QDateTime::currentDateTime();
    QDateTime utc_cdt(cdt.toUTC());

    QString date_str=utc_cdt.toString("yyyy-MM-ddThh-mm-ss.zzz000000Z");
    QString file_name=output_directory+QString("/UTC--")+date_str+QString("--")+key->get_address();
    QFile f(file_name);
    if (!f.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }
    QTextStream out(&f);
    out << final_json;
    f.close();
    return true;
}
