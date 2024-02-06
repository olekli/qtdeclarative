// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

import QtQuick
import QtQuick.Shapes

Item {
    width: 1200
    height: 600

    ListModel {
        id: fillRules
        ListElement { fillrule: ShapePath.WindingFill }
        ListElement { fillrule: ShapePath.OddEvenFill }
    }

    ListModel {
        id: renderers
        ListElement { renderer: Shape.GeometryRenderer }
        ListElement { renderer: Shape.CurveRenderer }
    }

    ListModel {
        id: svgstrings
        ListElement { scaleToFit: 1; offsetX: 20; offsetY: 20; pathString: "M 10,30 A 20,20 0,0,1 50,30 A 20,20 0,0,1 90,30 Q 90,60 50,90 Q 10,60 10,30 M 5 40 L 100 40 L 100 60 L 5 60 Z" }
        ListElement { scaleToFit: 5; offsetX: 10; offsetY: 20; pathString: "M 7.10938 0 Q 7.73438 0 8.28125 0.140625 Q 8.82813 0.28125 9.14063 0.546875 L 8.64063 2.10938 Q 8.35938 1.92188 8.02344 1.83594 Q 7.6875 1.75 7.26563 1.75 Q 6.23438 1.75 5.66406 2.24219 Q 5.09375 2.73438 5.09375 3.8125 L 5.09375 5.64063 L 5.09375 6.26563 L 5.09375 17.6406 L 3.17188 17.6406 L 3.17188 3.625 Q 3.17188 2.82813 3.40625 2.15625 Q 3.64063 1.48438 4.13281 1.00781 Q 4.625 0.53125 5.375 0.265625 Q 6.125 1.77636e-15 7.10938 0 M 9.09375 5.64063 L 9.09375 7.29688 L 0.765625 7.29688 L 0.765625 5.64063 L 9.09375 5.64063 M 16.2813 5.40625 Q 17.9844 5.40625 19.2891 6.14844 Q 20.5938 6.89063 21.3438 8.29688 Q 22.0938 9.70313 22.0938 11.6406 Q 22.0938 13.5781 21.3438 14.9844 Q 20.5938 16.3906 19.2891 17.1328 Q 17.9844 17.875 16.2813 17.875 Q 14.5938 17.875 13.2734 17.1328 Q 11.9531 16.3906 11.2109 14.9844 Q 10.4688 13.5781 10.4688 11.6406 Q 10.4688 9.70313 11.2109 8.29688 Q 11.9531 6.89063 13.2734 6.14844 Q 14.5938 5.40625 16.2813 5.40625 M 16.2813 7.0625 Q 15.0469 7.0625 14.1875 7.60938 Q 13.3281 8.15625 12.8594 9.17969 Q 12.3906 10.2031 12.3906 11.6406 Q 12.3906 13.0625 12.8594 14.0938 Q 13.3281 15.125 14.1875 15.6719 Q 15.0469 16.2188 16.2813 16.2188 Q 17.5 16.2188 18.3672 15.6719 Q 19.2344 15.125 19.7031 14.0938 Q 20.1719 13.0625 20.1719 11.6406 Q 20.1719 10.2031 19.7031 9.17969 Q 19.2344 8.15625 18.3672 7.60938 Q 17.5 7.0625 16.2813 7.0625" }
        ListElement { scaleToFit: 5; offsetX: -120; offsetY: 20; pathString: "M 30.6719 5.40625 Q 32.375 5.40625 33.6797 6.14844 Q 34.9844 6.89063 35.7344 8.29688 Q 36.4844 9.70313 36.4844 11.6406 Q 36.4844 13.5781 35.7344 14.9844 Q 34.9844 16.3906 33.6797 17.1328 Q 32.375 17.875 30.6719 17.875 Q 28.9844 17.875 27.6641 17.1328 Q 26.3438 16.3906 25.6016 14.9844 Q 24.8594 13.5781 24.8594 11.6406 Q 24.8594 9.70313 25.6016 8.29688 Q 26.3438 6.89063 27.6641 6.14844 Q 28.9844 5.40625 30.6719 5.40625 M 30.6719 7.0625 Q 29.4375 7.0625 28.5781 7.60938 Q 27.7188 8.15625 27.25 9.17969 Q 26.7813 10.2031 26.7813 11.6406 Q 26.7813 13.0625 27.25 14.0938 Q 27.7188 15.125 28.5781 15.6719 Q 29.4375 16.2188 30.6719 16.2188 Q 31.8906 16.2188 32.7578 15.6719 Q 33.625 15.125 34.0938 14.0938 Q 34.5625 13.0625 34.5625 11.6406 Q 34.5625 10.2031 34.0938 9.17969 Q 33.625 8.15625 32.7578 7.60938 Q 31.8906 7.0625 30.6719 7.0625 M 45.9688 17.875 Q 44.9688 17.875 44.1016 17.5156 Q 43.2344 17.1563 42.6094 16.5078 Q 41.9844 15.8594 41.6719 15.0469 L 41.9375 14.7188 L 41.7656 17.6406 L 40.0938 17.6406 L 40.0938 0.125 L 42.0156 0.125 L 42.0156 8.35938 L 41.7656 7.98438 Q 42.25 6.85938 43.3906 6.13281 Q 44.5313 5.40625 46 5.40625 Q 47.4844 5.40625 48.7344 6.14844 Q 49.9844 6.89063 50.7266 8.28125 Q 51.4688 9.67188 51.4688 11.6406 Q 51.4688 13.5781 50.7109 14.9844 Q 49.9531 16.3906 48.7031 17.1328 Q 47.4531 17.875 45.9688 17.875 M 45.7813 16.2031 Q 47.5625 16.2031 48.5547 14.9531 Q 49.5469 13.7031 49.5469 11.6406 Q 49.5469 9.57813 48.5625 8.32813 Q 47.5781 7.07813 45.7969 7.07813 Q 44.6719 7.07813 43.8203 7.65625 Q 42.9688 8.23438 42.4922 9.26563 Q 42.0156 10.2969 42.0156 11.6875 Q 42.0156 13.0625 42.4844 14.0781 Q 42.9531 15.0938 43.8047 15.6484 Q 44.6563 16.2031 45.7813 16.2031" }
        ListElement { scaleToFit: 5; offsetX: -260; offsetY: 20; pathString: "M 62.1406 9.89063 Q 62.1406 8.54688 61.4219 7.8125 Q 60.7031 7.07813 59.3906 7.07813 Q 58.1406 7.07813 57.2734 7.61719 Q 56.4063 8.15625 56 9.35938 L 54.4375 8.40625 Q 54.9219 7.0625 56.2188 6.23438 Q 57.5156 5.40625 59.4375 5.40625 Q 60.7344 5.40625 61.7891 5.84375 Q 62.8438 6.28125 63.4531 7.1875 Q 64.0625 8.09375 64.0625 9.5 L 64.0625 15.3125 Q 64.0625 16.1719 64.9844 16.1719 Q 65.4375 16.1719 65.875 16.0625 L 65.7656 17.5625 Q 65.2969 17.8125 64.5156 17.8125 Q 63.8281 17.8125 63.2734 17.5469 Q 62.7188 17.2813 62.4063 16.7422 Q 62.0938 16.2031 62.0938 15.3906 L 62.0938 15.1406 L 62.5781 15.2188 Q 62.2969 16.1563 61.6016 16.7422 Q 60.9063 17.3281 60.0391 17.6016 Q 59.1719 17.875 58.3281 17.875 Q 57.2813 17.875 56.3672 17.5156 Q 55.4531 17.1563 54.9141 16.4297 Q 54.375 15.7031 54.375 14.6094 Q 54.375 13.2656 55.2734 12.3906 Q 56.1719 11.5156 57.7813 11.2031 L 62.5313 10.2656 L 62.5313 11.8594 L 58.6719 12.6406 Q 57.4844 12.8906 56.9141 13.3203 Q 56.3438 13.75 56.3438 14.5156 Q 56.3438 15.2656 56.9297 15.7344 Q 57.5156 16.2031 58.5938 16.2031 Q 59.2969 16.2031 59.9297 16.0234 Q 60.5625 15.8438 61.0703 15.4688 Q 61.5781 15.0938 61.8594 14.5313 Q 62.1406 13.9688 62.1406 13.2031 L 62.1406 9.89063 M 68.7188 17.6406 L 68.7188 5.64063 L 70.2813 5.64063 L 70.5469 7.60938 Q 71.0469 6.5 72.0156 5.95313 Q 72.9844 5.40625 74.375 5.40625 Q 74.6875 5.40625 75.0625 5.45313 Q 75.4375 5.5 75.7031 5.64063 L 75.3594 7.39063 Q 75.0938 7.29688 74.7891 7.25 Q 74.4844 7.20313 73.9063 7.20313 Q 73.1563 7.20313 72.3984 7.63281 Q 71.6406 8.0625 71.1406 8.9375 Q 70.6406 9.8125 70.6406 11.1563 L 70.6406 17.6406 L 68.7188 17.6406" }
        ListElement { scaleToFit: 1; offsetX: 20; offsetY: 20; pathString: "M 0 0 L 100 0 L 100 50 L 0 50 Z M 0 50 L 100 50 L 100 100 L 0 100 Z " }
        ListElement { scaleToFit: 1; offsetX: 20; offsetY: 20; pathString: "M 0 0 L 0 50 L 100 50 L 100 0 Z M 0 50 L 0 100 L 100 100 L 100 50 Z " }
        ListElement { scaleToFit: 1; offsetX: 20; offsetY: 20; pathString: "M 0 0 L 0 50 L 100 50 L 100 0 Z M 0 50 L 100 50 L 100 100 L 0 100 Z " }
        ListElement { scaleToFit: 1; offsetX: 20; offsetY: 40; pathString: "M 0 0 L 100 0 L 100 50 L 0 50 Z M 20 0 Q 20 -30 50 -30 Q 80 -30 80 0 L 80 70 Q 50 100 20 70 Z" }
    }
    Column {
        Repeater {
            model: renderers
            Column {
                Repeater {
                    model: fillRules
                    Row {
                        Repeater {
                            model: svgstrings
                            Rectangle {
                                width: 150
                                height: 150
                                border.color: "black"

                                Shape {
                                    preferredRendererType: renderer
                                    ShapePath {
                                        fillColor: renderer == Shape.CurveRenderer ? "#99483d8b" : "#99dc143c"
                                        fillRule: fillrule
                                        strokeWidth: 0
                                        PathSvg { path: pathString }
                                    }

                                    transform: Matrix4x4 {
                                        matrix: Qt.matrix4x4(scaleToFit, 0, 0, offsetX,
                                                             0, scaleToFit, 0, offsetY,
                                                             0, 0, 1, 0,
                                                             0, 0, 0, 1)
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
