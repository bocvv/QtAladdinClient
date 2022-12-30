import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2

Window {
    width: Screen.width
    height: Screen.height - 45
    x: 0
    y: 75
    visible: true
    color: "#1C1C1C"

    property bool hasColon: true

    function currentLockDateTime(){
        return Qt.formatDateTime(new Date(), "hh mm");
    }

    Text {
        id: lock_textDateTime
        text: currentLockDateTime()
        font.pointSize: 230
        font.bold: true
        font.family: qsTr("DIN Alternate")
        color: "white"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 20 
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    Text {
        id: dateTimeColon 
        text: ""
        font.pointSize: 230
        font.bold: true
        font.family: qsTr("DIN Alternate")
        color: "white"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 20 
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    Text {
        id: contentText
        text: "书山有路勤为径"
        font.pointSize: 80
        font.bold: true
        font.family: qsTr("HYQiHei")
        font.letterSpacing: 15
        color: "#FFFFFF"
        opacity: 0.5
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 40 
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    //定时器
    Timer {
        id: sec_timer
        interval: 1000 //间隔(单位毫秒):1000毫秒=1秒
        repeat: true //重复
        onTriggered:{
            lock_textDateTime.text = currentLockDateTime();

            if (hasColon) {
                hasColon = false;
                dateTimeColon.text = ":";
            } else {
                hasColon = true;
                dateTimeColon.text = "";
            }
        }
    }

    Component.onCompleted: {
        sec_timer.start();
    }

    MouseArea {
        anchors.fill: parent

        onClicked: {
            lockTimer.restart()
            lock_screen_loader.source = ""
        }
    }
}
