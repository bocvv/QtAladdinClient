import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.LocalStorage 2.9
import yd.qt.AladdinMaker 1.0
import yd.qt.FintipController 1.0
// import "DataBase.js" as JS


Window {
    id: win_0
    visible: true
    width: Screen.width
    height: Screen.height
    title: qsTr("aladdin client")
    color: "#1C1C1C"

    // global variant
    property int $totalStudyTime: 25

    property int $actual_study_time: 0
    property real $play_phone_rate: 1.0
    property real $look_lamp_rate: 1.0
    property real $look_monitor_rate: 1.0
    property real $look_book_rate: 1.0
    property real $look_other_rate: 1.0
    property real $look_none_rate: 1.0

    // cost time of every study status
    property int $play_phone_time: 0
    property int $look_lamp_time: 0
    property int $look_monitor_time: 0
    property int $look_book_time: 0 
    property int $look_other_time: 0 
    property int $look_none_time: 0

    // global aladdin maker which is used for home page
    property var $aladdinMaker: AladdinMaker{ }

    // global fingertip word search object
    property var $fintip: FintipController{ }
    property string $word_raw
    property string $word_trans

    //当前日期时间
    function currentDateTime(){
        // return Qt.formatDateTime(new Date(), "MM-dd hh:mm ddd");
        var d = new Date();
        var week;
        switch (d.getDay()) {
            case 1: week = "周一"; break;
            case 2: week = "周二"; break;
            case 3: week = "周三"; break;
            case 4: week = "周四"; break;
            case 5: week = "周五"; break;
            case 6: week = "周六"; break;
            default: week = "周日";
        }
        return week + Qt.formatDateTime(new Date(), " hh:mm");
    }

    Item {
        id: timeItem
        width: 300
        height: 64
        z: 101

        //显示
        Text {
            id: textDateTime
            text: currentDateTime();
            font.pointSize: 24
            color: "white"
            anchors.left: parent.left
            anchors.leftMargin: 100
            anchors.top: parent.top
            anchors.topMargin: 20 
        }

        //定时器
        Timer{
            id: timer
            interval: 1000 //间隔(单位毫秒):1000毫秒=1秒
            repeat: true //重复
            onTriggered:{
                textDateTime.text = currentDateTime();
            }
        }

        Component.onCompleted: {
            timer.start();
        }

    }

    // 全局锁屏loader及其定时器lockTimer
    Loader {
        id: lock_screen_loader

        onLoaded: {
        }
    }

    Item {
        Timer {
            id: lockTimer
            repeat: false
            onTriggered: {
                console.log("触发锁屏！")
                lock_screen_loader.source = "lock_screen.qml"
            }
        }

        function setTimer(val) {
            lockTimer.interval = 1000 * val
        }

        Component.onCompleted: {
            console.log("开始锁屏倒计时！")
            setTimer(300)
            lockTimer.start()
        }
    }

    Image {
        id: wifi_icon
        width: 36
        height: 36
        z: 101
        source: "file:/root/wangbw/work/aladdin_client/resources/wifi.png"
        fillMode: Image.PreserveAspectFit
        anchors.left: parent.left
        anchors.leftMargin: 30
        anchors.top: parent.top
        anchors.topMargin: 20
    }

    Image {
        id: nowifi_icon
        width: 36
        height: 36
        z: 101
        visible: false
        source: "file:/root/wangbw/work/aladdin_client/resources/nowifi.png"
        fillMode: Image.PreserveAspectFit
        anchors.left: parent.left
        anchors.leftMargin: 30
        anchors.top: parent.top
        anchors.topMargin: 20
    }

    Connections {
        target: $aladdinMaker
        onCurrNetStat: {
            if (isOnline) {
                wifi_icon.visible = true
                nowifi_icon.visible = false
                console.log("is online")
            } else {
                wifi_icon.visible = false
                nowifi_icon.visible = true
                console.log("is offline")
            }
        }
    }

    WordResult {
        id: word_rect
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: timeItem.bottom
        anchors.topMargin: 20
        z: 5
    }

    Connections {
        target: $fintip
        onWordDetTriggered: {
            word_rect.visible = true
        }
    }

    //显示
    Rectangle {
        id: unuse_warning_box
        width: 450 
        height: 60
        visible: false
        color: "#487CA7" 
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 50
        radius: 15
        z: 2

        Text {
            id: unuse_warning
            width: 500
            height: 40
            visible: true
            text: "研发小哥正在加紧开发中"
            color: "white"
            font.pointSize: 28
            anchors.fill: parent
            anchors.centerIn: parent
        }

        //定时器
        Timer {
            id: unuse_warning_timer
            interval: 3000 //间隔(单位毫秒):1000毫秒=1秒
            repeat: false //重复
            running: false
            triggeredOnStart: false
            onTriggered: {
                unuse_warning_box.visible = false
            }
        }
    }

    Image {
        id: setup_icon
        width: 45
        height: 45
        z: 101
        source: "file:/root/wangbw/work/aladdin_client/resources/setup.png"
        fillMode: Image.PreserveAspectFit
        anchors.right: parent.right
        anchors.rightMargin: 30
        anchors.top: parent.top
        anchors.topMargin: 15
    }

    SwitchDelegate {
        id: control
        text: qsTr("指点查词")
        anchors.right: setup_icon.right
        anchors.rightMargin: 60
        anchors.top: parent.top
        anchors.topMargin: 5
        z: 101
        checked: false
        visible: true

        contentItem: Text {
            rightPadding: control.indicator.width + control.spacing
            text: control.text
            font.pointSize: 24
            opacity: enabled ? 1.0 : 0.3
            color: control.down ? "#17a81a" : "white"
            elide: Text.ElideRight
            verticalAlignment: Text.AlignVCenter
        }

        indicator: Rectangle {
            implicitWidth: 64
            implicitHeight: 38
            x: control.width - width - control.rightPadding
            y: parent.height / 2 - height / 2
            radius: 13
            color: control.checked ? "#17a81a" : "red"
            border.color: control.checked ? "#17a81a" : "#cccccc"

            Rectangle {
                x: control.checked ? parent.width - width : 0
                width: 36
                height: 36
                radius: 13
                color: control.down ? "#cccccc" : "#ffffff"
                border.color: control.checked ? (control.down ? "#17a81a" : "#21be2b") : "#999999"
            }
        }

        background: Rectangle {
            implicitWidth: 100
            implicitHeight: 40
            visible: control.down || control.highlighted
            color: control.down ? "#bdbebf" : "#eeeeee"
        }

        onClicked : {
            lockTimer.restart()
            if (control.checked)
            {
                // word_rect.visible = true
                $fintip.start()
            }
            else
            {
                $fintip.stop()
                word_rect.visible = false
                word_rect.setContentText("", "")
            }
        }
    }

    /*
    DarkSwitch {
        id: darkSwitch
        anchors.right: parent.right
        anchors.rightMargin: 50
        anchors.top: parent.top
        anchors.topMargin: 5
        z: 101
    }
    Text{
        id: switchText1
        text: "指点查词"
        color: darkSwitch.checked? "#969697" : "#3ea1fd"
        anchors{verticalCenter: darkSwitch.verticalCenter; right: darkSwitch.left; rightMargin: 20}
        font{family: "Arial"; pointSize: 24}
        z: 101
    }
    */

    ColumnLayout {
        id: col_1
        anchors.left: parent.left
        anchors.top: timeItem.bottom
        anchors.topMargin: 20
        anchors.leftMargin: 20
        spacing: 15


        Loader {
            id: log_loader

            onLoaded: {
            }
        }

        RoundButton {
            id: search_log
            text: "单词本"
            width: 240
            height: 150
            font.pointSize: 30

            contentItem: Text {
                text: search_log.text
                font: search_log.font
                color: search_log.down ? "skyblue" : "#F5F5F5"
                // horizontalAlignment: Text.AlignHCenter
                // verticalAlignment: Text.AlignVCenter
                anchors.top: parent.top
                anchors.topMargin: 20
                anchors.left: parent.left
                anchors.leftMargin: 20
                elide: Text.ElideRight

                Image {
                    width: 50
                    height: 50
                    source: "file:/root/wangbw/work/aladdin_client/resources/danciben.png"
                    fillMode: Image.PreserveAspectFit
                    anchors.right: parent.right
                    anchors.rightMargin: 30
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 25
                }
            }

            background: Rectangle {
                radius: 15
                color: "#598FC7"
                implicitWidth: 240
                implicitHeight: 150
                opacity: 0.3
                anchors.fill: parent 
            }

            onClicked: {
                lockTimer.restart()
                log_loader.source = "search_log.qml"
            }
        }

        RoundButton {
            id: speak_practice
            text: "口语练习"
            width: 240
            height: 150
            font.pointSize: 30

            contentItem: Text {
                text: speak_practice.text
                font: speak_practice.font
                color: speak_practice.down ? "skyblue" : "#F5F5F5"
                // horizontalAlignment: Text.AlignHCenter
                // verticalAlignment: Text.AlignVCenter
                anchors.top: parent.top
                anchors.topMargin: 20
                anchors.left: parent.left
                anchors.leftMargin: 20
                elide: Text.ElideRight

                Image {
                    width: 50
                    height: 50
                    source: "file:/root/wangbw/work/aladdin_client/resources/kouyulianxi.png"
                    fillMode: Image.PreserveAspectFit
                    anchors.right: parent.right
                    anchors.rightMargin: 30
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 25
                }
            }

            background: Rectangle {
                radius: 15
                color: "#2C979E"
                opacity: 0.3
                implicitWidth: 240
                implicitHeight: 150
                anchors.fill: parent 
            }

            onClicked: {
                lockTimer.restart()
                unuse_warning_box.visible = true
                unuse_warning_timer.start()
            }
        }

        RoundButton {
            id: cal_correct
            text: "口算批改"
            width: 240
            height: 150
            font.pointSize: 30

            contentItem: Text {
                text: cal_correct.text
                font: cal_correct.font
                color: cal_correct.down ? "skyblue" : "#F5F5F5"
                // horizontalAlignment: Text.AlignHCenter
                // verticalAlignment: Text.AlignVCenter
                anchors.top: parent.top
                anchors.topMargin: 20
                anchors.left: parent.left
                anchors.leftMargin: 20
                elide: Text.ElideRight

                Image {
                    width: 50
                    height: 50
                    source: "file:/root/wangbw/work/aladdin_client/resources/kousuanpigai.png"
                    fillMode: Image.PreserveAspectFit
                    anchors.right: parent.right
                    anchors.rightMargin: 30
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 25
                }
            }

            background: Rectangle {
                radius: 15
                color: "#BFAC7A"
                implicitWidth: 240
                implicitHeight: 150
                opacity: 0.3
                anchors.fill: parent 
            }

            onClicked: {
                lockTimer.restart()
                unuse_warning_box.visible = true
                unuse_warning_timer.start()
            }
        }
    }

    ColumnLayout {
        id: col_mid
        anchors.left: col_1.right
        anchors.top: timeItem.bottom
        anchors.topMargin: 20
        anchors.leftMargin: 15
        spacing: 5

        Rectangle {
            id: rect_mid
            color: "#393C3D"
            width: 470
            height: 480
            radius: 15
            Layout.alignment: Qt.AlignCenter

            Rectangle {
                width: 300
                height: 300
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: -15
                anchors.horizontalCenter: parent.horizontalCenter
                color: "transparent"

                Rectangle {
                    width: {
                        if (parent.width > parent.height) {
                            return parent.height
                        } else {
                            return parent.width
                        }
                    }
                    height: width
                    anchors.centerIn: parent
                    radius: {
                        if (width > height) {
                            return height / 2
                        } else {
                            return width / 2
                        }
                    }
                    color: "transparent"
                    opacity: 0.3
                    border.color: "#F5F5F5"
                    border.width: 3
                    Text {
                        anchors.centerIn: parent
                        text: ""
                    }
                }

            }

            Loader {
                id: status_loader

                onLoaded: {
                    item.setStudyTime(time_wheel.value)
                }
            }

            Loader {
                id: report_loader

                onLoaded: {
                }
            }

            Text{
                id: set_study_time
                text: "请设置学习时间"
                color: "white"
                font{family: "Arial"; pointSize: 24}

                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 15

                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            WheelView {
                id: time_wheel
                width: 100; height: 300
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: 0
                model: {
                    var list = [];
                    for (var i = 5; i < 61; i+=5)
                        list.push({ display: i, value: i });
                    return list;
                }
                value: 25

                pathItemCount: 4
                displayFontSize: 70
            }

            Row {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 10
                spacing: 5

                Image {
                    id: triangle_icon
                    width: 30
                    height: 30
                    anchors.verticalCenter: parent.verticalCenter
                    source: "file:/root/wangbw/work/aladdin_client/resources/triangle.png"
                    fillMode: Image.PreserveAspectFit
                }

                Button {
                    id: start
                    text: "开始学习"
                    font.pointSize: 30

                    contentItem: Text {
                        text: start.text
                        font: start.font
                        opacity: enabled ? 1.0 : 0.3
                        color: start.down ? "skyblue" : "#F1F1F1"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        elide: Text.ElideRight
                    }

                    background: Rectangle {
                        radius: 15
                        color: "transparent"
                        opacity: 1
                        implicitWidth: 150
                        implicitHeight: 85
                        anchors.fill: parent 
                    }

                    onClicked: {
                        lockTimer.restart()
                        if (control.checked) {
                            /*
                            $fintip.stop()
                            control.checked = false
                            */
                        }

                        // control.visible = false
                        status_loader.source = "study_status.qml"
                    }
                }

            }

            Text {
                id: fullTimeText
                text: "分钟"
                color: "white"
                anchors {
                    verticalCenter: parent.verticalCenter
                    // verticalCenterOffset: 40
                    right: parent.right
                    rightMargin: 115
                }
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font{family: "Arial"; pointSize: 24}
            }
        }

    }

    ColumnLayout {
        id: col_2
        anchors.left: col_mid.right
        anchors.top: timeItem.bottom
        anchors.topMargin: 20
        anchors.leftMargin: 15
        spacing: 15

        RoundButton {
            id: homework 
            text: "交作业"
            font.pointSize: 30

            contentItem: Text {
                text: homework.text
                font: homework.font
                color: homework.down ? "skyblue" : "#F5F5F5"
                // horizontalAlignment: Text.AlignHCenter
                // verticalAlignment: Text.AlignVCenter
                anchors.top: parent.top
                anchors.topMargin: 20
                anchors.left: parent.left
                anchors.leftMargin: 20
                elide: Text.ElideRight

                Image {
                    width: 50
                    height: 50
                    source: "file:/root/wangbw/work/aladdin_client/resources/jiaozuoye.png"
                    fillMode: Image.PreserveAspectFit
                    anchors.right: parent.right
                    anchors.rightMargin: 30
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 25
                }
            }

            background: Rectangle {
                radius: 15
                color: "#7ABF89"
                opacity: 0.3
                implicitWidth: 240
                implicitHeight: 150
                anchors.fill: parent 
            }

            onClicked: {
                lockTimer.restart()
                unuse_warning_box.visible = true
                unuse_warning_timer.start()
            }
        }

        RoundButton {
            id: tel
            text: "语音通话"
            font.pointSize: 30

            contentItem: Text {
                text: tel.text
                font: tel.font
                color: tel.down ? "skyblue" : "#F5F5F5"
                // horizontalAlignment: Text.AlignHCenter
                // verticalAlignment: Text.AlignVCenter
                anchors.top: parent.top
                anchors.topMargin: 20
                anchors.left: parent.left
                anchors.leftMargin: 20
                elide: Text.ElideRight

                Image {
                    width: 50
                    height: 50
                    source: "file:/root/wangbw/work/aladdin_client/resources/yuyintonghua.png"
                    fillMode: Image.PreserveAspectFit
                    anchors.right: parent.right
                    anchors.rightMargin: 30
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 25
                }
            }

            background: Rectangle {
                radius: 15
                color: "#C5874E"
                opacity: 0.3
                implicitWidth: 240
                implicitHeight: 150 
                anchors.fill: parent 
            }

            onClicked: {
                unuse_warning_box.visible = true
                unuse_warning_timer.start()
                lockTimer.restart()
            }
        }

        RoundButton {
            id: q_and_a
            text: "错题采集"
            font.pointSize: 30

            contentItem: Text {
                text: q_and_a.text
                font: q_and_a.font
                color: q_and_a.down ? "skyblue" : "#F5F5F5"
                // horizontalAlignment: Text.AlignHCenter
                // verticalAlignment: Text.AlignVCenter
                anchors.top: parent.top
                anchors.topMargin: 20
                anchors.left: parent.left
                anchors.leftMargin: 20
                elide: Text.ElideRight

                Image {
                    width: 50
                    height: 50
                    source: "file:/root/wangbw/work/aladdin_client/resources/cuoticaiji.png"
                    fillMode: Image.PreserveAspectFit
                    anchors.right: parent.right
                    anchors.rightMargin: 30
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 25
                }
            }

            background: Rectangle {
                radius: 15
                color: "#DD8484"
                opacity: 0.3
                implicitWidth: 240
                implicitHeight: 150 
                anchors.fill: parent 
            }

            onClicked: {
                unuse_warning_box.visible = true
                unuse_warning_timer.start()

                lockTimer.restart()
            }
        }
    }

    Component.onCompleted: {
        // JS.dbInit() //JS的文件初始化
    }
}
