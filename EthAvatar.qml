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
import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.11
import QtQuick.Dialogs 1.2
import org.afterether.eis 1.0
import org.afterether.eis.identicon 1.0
import org.afterether.eis.ethkey 1.0

Pane {
    id: avatar_container
    property string output_dir
    property string password 
    property alias scale_factor: avatar.scale_factor
    property EthKey key: EthKey{}
    height: ethereum_icon_scanner.avatar_height
    width: ethereum_icon_scanner.avatar_width

    background: Rectangle {        
        color: "black"
        anchors.fill: parent
    }

    ColumnLayout {
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        Identicon {
            id: avatar            
            scale_factor: 5
            Layout.alignment: Qt.AlignTop|Qt.AlignHCenter
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    save_dialog.visible=true
                }
            }
        }
    }
    MessageDialog {
        id: save_dialog
        title: "Save Dialog"
        text: "Do you want to save this account?"
        standardButtons: StandardButton.Yes | StandardButton.No
        onYes: {
            save_dialog.visible=false
            do_save_key_to_file();
        }
        onNo: {
            save_dialog.visible=false
        } 
    }
    function do_save_key_to_file() {
        if (eis_obj.save_key_to_file(output_dir,password,key)) {
        } else {
            console.log("save failed")
        }
    }  
    function genkey() {        
        if (eis_obj.generate_ethereum_key(avatar_container.key)) {
            avatar.address=key.address
        } else {

        }
    }
}
