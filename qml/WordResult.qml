import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtGraphicalEffects 1.12

Item {
    width: Screen.width
    height: 485
    clip: true
    visible: false
    z: 5

    Loader {
        id: details_loader

        onLoaded: {
            item.setDetailsData(word_key.text, word_value.text)
        }
    }

    Rectangle {
        id: word_rect
        width: Screen.width 
        height: 485
        color: "#393C3D"
        opacity: 0.9
        radius: 20
    }

    FastBlur {
        id: blur
        anchors.fill: word_rect
        source: word_rect
        width: source.width;
        height: source.height
        radius: 64
    }

    RoundButton {
        id: x_button
        text: "X"
        width: 50
        height: 50
        font.pointSize: 33
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 10
        z: 10

        contentItem: Text {
            text: x_button.text
            font: x_button.font
            color: "#2C2C2C"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
        }

        onClicked: {
            word_key.text = " "
            word_value.text = " "
            parent.visible = false
        }
    }

    MouseArea {
        anchors.fill: parent
    }

    Rectangle {
        id: flick
        anchors.centerIn: parent 
        width: Screen.width
        height: 485
        color: "transparent"
        // contentWidth: width
        // contentHeight: 500

        Text {
            id: finger_status
            width: 200
            height: 50
            visible: true
            text: ""
            color: "green"
            font.pointSize: 20
            anchors.top: parent.top
            anchors.topMargin: 20
            anchors.left: parent.left
            anchors.leftMargin: 40
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        Text {
            id: word_key
            width: Screen.width - 100
            height: 80
            visible: true
            text: ""
            color: "#FFFFFF"
            font.pointSize: 50
            font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 10
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        Text {
            id: word_value
            width: Screen.width - 100
            height: 300
            visible: true
            text: ""
            color: "#FFFFFF"
            font.pointSize: 28
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: word_key.bottom
            anchors.topMargin: 20
            horizontalAlignment: Text.AlignHCenter
            // verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
            wrapMode: Text.WrapAnywhere
        }

        Row {
            spacing: 40
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10

            RoundButton {
                id: details_btn
                text: "详细释义"
                width: 200
                height: 55
                font.pointSize: 25

                contentItem: Text {
                    text: details_btn.text
                    font: details_btn.font
                    // opacity: enabled ? 0.4 : 0.4
                    color: details_btn.down ? "green" : "#FFFFFF"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    elide: Text.ElideRight
                }

                background: Rectangle {
                    radius: 22
                    color: "#262626"
                    implicitWidth: 130
                    implicitHeight: 55
                    opacity: 1.0
                    anchors.fill: parent

                    CustomBorder {
                        commonBorderWidth: 3
                        borderColor: "#FFFFFF"
                        radius: 22
                    }
                }

                onClicked: {
                    /*
                    flick.contentHeight = 1500;
                    word_value.height = 1000;
                    */
                    details_loader.source = "details_word_result.qml";
                }
            }

            RoundButton {
                id: gendu_btn
                text: "跟 读"
                width: 200
                height: 55
                font.pointSize: 25

                contentItem: Text {
                    text: gendu_btn.text
                    font: gendu_btn.font
                    // opacity: enabled ? 0.4 : 0.4
                    color: gendu_btn.down ? "#FF3C3C3C" : "#FF3C3C3C"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    elide: Text.ElideRight
                }

                background: Rectangle {
                    radius: 22
                    color: "transparent"
                    implicitWidth: 130
                    implicitHeight: 55
                    opacity: 1.0
                    anchors.fill: parent

                    CustomBorder {
                        commonBorderWidth: 3
                        borderColor: "#FFFFFF"
                        radius: 22
                    }
                }

                onClicked: {
                }
            }

            RoundButton {
                id: pindu_btn
                text: "拼 读"
                width: 200
                height: 55
                font.pointSize: 25

                contentItem: Text {
                    text: pindu_btn.text
                    font: pindu_btn.font
                    // opacity: enabled ? 0.4 : 0.4
                    color: pindu_btn.down ? "#FF3C3C3C" : "#FF3C3C3C"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    elide: Text.ElideRight
                }

                background: Rectangle {
                    radius: 22
                    color: "transparent"
                    implicitWidth: 130
                    implicitHeight: 55
                    opacity: 1.0
                    anchors.fill: parent

                    CustomBorder {
                        commonBorderWidth: 3
                        borderColor: "#FFFFFF"
                        radius: 22
                    }
                }

                onClicked: {
                }
            }
        }
    }

    /*
    Rectangle {
       id: scrollbar
       anchors.right: flick.right
       y: flick.visibleArea.yPosition * flick.height
       width: 10
       height: flick.visibleArea.heightRatio * flick.height
       color: "#262626"
   }
   */

    Connections {
        target: $fintip
        onWordDetTriggered: {
            finger_status.text = ""
            parent.visible = true
            console.log(strWordRaw)
            console.log(strWordTrans)
            word_key.text = strWordRaw 
            word_value.text = strWordTrans 
        }
    }

    Connections {
        target: $fintip
        onFingerTriggered: {
            if (isTriggered) {
                finger_status.text = "指尖已触发,查词中..."
                lockTimer.restart()
                lock_screen_loader.source = ""
            } else {
                finger_status.text = ""
            }
        }
    }

    function setContentText(word, explain) {
        word_key.text = word
        word_value.text = explain
    }
}

