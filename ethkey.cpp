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
#include "ethkey.h"

EthKey::EthKey(QObject *parent) : QObject(parent)
{
    address="";
    private_key="";
    key_json="";
}
QString EthKey::get_address() {
    return address;
}
QString EthKey::get_private_key(){
    return private_key;
}
QString EthKey::get_key_json() {
    return key_json;
}
void EthKey::set_address(QString p_address) {
    this->address=p_address;
}
void EthKey::set_private_key(QString p_private_key) {
    this->private_key=p_private_key;
}
void EthKey::set_key_json(QString p_key_json) {
    this->key_json=p_key_json;
}
