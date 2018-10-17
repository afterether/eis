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
import org.afterether.eis 1.0
import org.afterether.eis.identicon 1.0

ApplicationWindow {
    id: ethereum_icon_scanner
    title: qsTr("Ethereum Icon Scanner")
    property int avatar_width: 100
    property int avatar_line_height: 120
    property int current_num_lines: 0
    property int num_icons_in_line: 1   
    property bool started: false
    property bool locked: false
    visible: true
    width: 640
    height: 480

    EIS {
        id: eis_obj
    }
    Page {
        id: main_content
        anchors.fill: parent
        header: Flow {
                id: controls

                RowLayout {
                    Label {
                        Layout.alignment: Qt.AlignVCenter
                        text: "Output:"
                    }
                    TextField {
                        id: output_dir_name
                        Layout.alignment: Qt.AlignVCenter
                        placeholderText: "/tmp"
                        text: "/tmp"
                    }
                }
                RowLayout {
                    Label {
                        Layout.alignment: Qt.AlignVCenter
                        text: "Passwd:"
                    }
                    TextField {
                        id: fld_password
                        Layout.alignment: Qt.AlignVCenter
                        text: "123"
                        width: 100
                    }
                }
                RowLayout {
                    Button {
                        id: btn_process_control
                        Layout.alignment: Qt.AlignVCenter|Qt.AlignHCenter
                        text: "Next"
                        onClicked:  {
                            generate_accounts()
                        }
                    }
                }
        }

        Column {
            id: rows_of_the_avatars
            anchors.fill: parent
        }
    }

    Component.onCompleted: {        
        onWidthChanged.connect(width_changed)
        onHeightChanged.connect(height_changed)
        height_changed(ethereum_icon_scanner.height)
    }   

    function generate_new_key() {
        var tmp_key=eis_obj.generate_ethereum_key();
    }  
    function generate_avatar_line(line_obj,line_size) {
        var i;        
        for (i=0; i<line_size;i++) {
            var component = Qt.createComponent("EthAvatar.qml");
            if (component.status === Component.Ready) {
                var obj;
                obj=component.createObject(line_obj, {"output_dir":output_dir_name.text,"password": fld_password.text});
                if (obj===null) {
                    console.log("ERROR: obj=null")
                    continue;
                } else {
                    obj.genkey()
                }
            }
        }
    }
    function delete_line(line_obj) {
        for(var i = line_obj.children.length; i > 0 ; i--) {            
            line_obj.children[i-1].destroy()
        }
        line_obj.destroy();
    }
    function width_changed(val) {
        if (locked) return
        locked=true

        var required_width=avatar_width*num_icons_in_line
        var diff=required_width-val

        if (diff>avatar_width) { // rightmost item must be deleted, it isn't seen anyway            
            for (var i=0;i<rows_of_the_avatars.children.length;i++) {
                var row=rows_of_the_avatars.children[i]                
                var last_child=row.children[row.children.length-1]                
                last_child.destroy()               
            }
            num_icons_in_line--
        }
        diff=val-required_width
        if (diff>avatar_width) { // add new column
            for (i=0;i<rows_of_the_avatars.children.length;i++) {
                row=rows_of_the_avatars.children[i]
                var component = Qt.createComponent("EthAvatar.qml");
                if (component.status === Component.Ready) {
                    var obj;
                    obj=component.createObject(row, {"output_dir":output_dir_name.text,"password": fld_password.text});
                    if (obj===null) {
                        continue;
                    } else {
                        obj.genkey()
                    }
                }
            }
            num_icons_in_line++
        }       
        locked=false
    }
    function height_changed(height) {
        if (locked) return;
        locked=true
        var used_height=main_content.contentHeight
        var remaining_space=rows_of_the_avatars.height-used_height       
        var icons_per_line=Math.floor(ethereum_icon_scanner.width/avatar_width)        
        while (remaining_space>avatar_line_height) {
            var component = Qt.createComponent("AvatarLine.qml");
            if (component.status === Component.Ready) {
                var obj;
                obj=component.createObject(rows_of_the_avatars, {});
                if (obj===null) {
                    // nothing
                } else {
                    generate_avatar_line(obj,icons_per_line)
                    current_num_lines++
                    remaining_space=remaining_space-avatar_line_height
                    num_icons_in_line=icons_per_line
                }
            }
        }
        locked=false
    }
    function generate_accounts() {
        if (locked) return;
        locked=true       
        for (var i=0;i<rows_of_the_avatars.children.length;i++) {
            var row=rows_of_the_avatars.children[i]            
            for(var j = 0; j<  row.children.length; j++) {
                var child=row.children[j]                
                child.genkey()
            }
        }
        locked=false
    }
}
