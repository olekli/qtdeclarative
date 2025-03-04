// Copyright (C) 2024 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick
import QtQuick.Controls

ApplicationWindow {
    id: root
    property bool menuBarVisible: true
    property alias fileMenu: fileMenu
    property alias contents: contents

    width: 400
    height: 400
    visible: true

    menuBar: MenuBar {
        visible: root.menuBarVisible
        Menu {
            id: fileMenu
            title: "&File"
            MenuItem { text: "&Open..." }
            MenuItem { text: "&Save" }
            MenuItem { text: "Save &As..." }
            MenuSeparator { }
            MenuItem { text: "&Quit" }
        }
        Menu {
            title: "&Edit"
            MenuItem { text: "&Cut" }
            MenuItem { text: "&Copy" }
            MenuItem { text: "&Paste" }
        }
        Menu {
            title: "&View"
            Menu {
                title: "&Alignment"
                Menu {
                    title: "&Horizontal"
                    MenuItem { text: "&Left" }
                    MenuItem { text: "&Center" }
                    MenuItem { text: "&Right" }
                }
                Menu {
                    title: "&Vertical"
                    MenuItem { text: "&Top" }
                    MenuItem { text: "&Center" }
                    MenuItem { text: "&Bottom" }
                }
            }
        }

        Menu {
            title: "&Help"
            MenuItem { text: "&About" }
        }
    }

    Rectangle {
        id: contents
        anchors.fill: parent
        color: "green"
    }

    Text {
        // dummy binding to test that fileMenu will be kept alive
        // after a call to menuBar.removeMenu(fileMenu) followed
        // by running the garbage collector.
        text: fileMenu.title
    }

    Component {
        id: menuComp
        Menu {
            objectName: "Extra"
            title: "extra"
        }
    }

    function addTestMenu()
    {
        let menu = menuComp.createObject(null)
        menuBar.addMenu(menu)
    }
}
