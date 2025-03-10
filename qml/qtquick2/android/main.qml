/*
 *  Copyright 2011 Ruediger Gad
 *
 *  This file is part of MeePasswords.
 *
 *  MeePasswords is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  MeePasswords is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with MeePasswords.  If not, see <http://www.gnu.org/licenses/>.
 */

import QtQuick 2.0
import meepasswords 1.0
//import SyncToImap 1.0

Rectangle {
    id: main

    property int primaryFontSize: settingsAdapter.fontSize > 0 ? settingsAdapter.fontSize : 30
    property int primaryBorderSize: 35

    property string primaryFontColor: "black"
    property string secondaryFontColor: "gray"

    property string primaryBackgroundColor: "lightgray"
    property double primaryBackgroundOpacity: 0.9
    property string secondaryBackgroundColor: "lightgray"
    property double secondaryBackgroundOpacity: 0.9

    property string iconNameSuffix: ""

    color: "lightgray"

    onPrimaryFontSizeChanged: settingsAdapter.fontSize = primaryFontSize

    onRotationChanged: {
        console.log("Rotation changed...");
    }

    Component.onCompleted: {
        cleanOldFiles()
        main.forceActiveFocus()
    }

    Keys.onReleased: {
        if (event.key === Qt.Key_Back && mainFlickable.loggedIn) {
            event.accepted = true

            if (mainFlickable.editEntryRectangle.isShown) {
                mainFlickable.editEntryRectangle.hide()
            } else {
                mainFlickable.logOut()
            }
        }
    }

    function cleanOldFiles() {
        console.log("Cleaning left overs from last run.")
//        mainFlickable.fileHelper.rmAll(mainFlickable.entryStorage.getStorageDirPath(), ".encrypted.");
    }

    Item {
        anchors.fill: parent

        Rectangle {
            id: header
            height: primaryFontSize * 2
            color: "#0c61a8"
            anchors{left: parent.left; right: parent.right; top: parent.top}

            Text {
                text: "MeePasswords"
                color: "white"
                font.pointSize: primaryFontSize * 0.75
                anchors.left: parent.left
                anchors.leftMargin: primaryFontSize * 0.6
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        MainFlickable {
            id: mainFlickable

            anchors{top: header.bottom; left: parent.left; right: parent.right; bottom: parent.bottom}
        }
    }

    Menu {
        id: mainMenu

        anchors.fill: parent
        parent: main

        menuBottomOffset: mainFlickable.toolBar.height
        onClosed: mainFlickable.meePasswordsToolBar.enabled = true
        onOpened: mainFlickable.meePasswordsToolBar.enabled = false
    }

    SettingsAdapter {
        id: settingsAdapter
    }
}
