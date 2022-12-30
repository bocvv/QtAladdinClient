import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.LocalStorage 2.9
import yd.qt.AladdinController 1.0
// import "DataBase.js" as JS

Window{
    id: win
    title: qsTr("子窗口")
    width: Screen.width
    height: Screen.height - 45
    color: "#1C1C1C"
    x: 0
    y: 75
    visible: true

    AladdinController {
        id: aladdinController
    }

    WordResult {
        id: word_rect_1
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 20
        z: 5
    }

    Connections {
        target: $fintip
        onWordDetTriggered: {
            word_rect_1.visible = true
            console.log(strWordRaw)
            console.log(strWordTrans)
        }
    }

    ColumnLayout {
        anchors.centerIn: parent
        spacing: 30

        Text {
            id: timeLabel
            width: 500
            height: 200
            color: "#F5F5F5"
            Layout.alignment: Qt.AlignCenter 
            font.pointSize: 80
        }

        //显示
        Text{
            id: study_status_text
            width: 500
            height: 90
            visible: true
            Layout.alignment: Qt.AlignCenter 
            text: "\n\n"
            font.pointSize: 23
            color: "white"
        }

        //定时器
        Timer{
            id: status_timer
            interval: 2000 //间隔(单位毫秒):1000毫秒=1秒
            repeat: false //重复
            running: false
            triggeredOnStart: false
            /*
            onTriggered: {
                study_status_text.text = " "
            }
            */
        }

        RowLayout {
            Layout.alignment: Qt.AlignCenter 

            RoundButton {
                id: pause
                text: "结束学习"
                font.pointSize: 30

                contentItem: Text {
                    text: pause.text
                    font: pause.font
                    opacity: enabled ? 1.0 : 0.3
                    color: pause.down ? "gray" : "black"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    elide: Text.ElideRight
                }

                background: Rectangle {
                    radius: 30
                    color: "white"
                    border.color: "black"
                    border.width: 5
                    implicitWidth: 270
                    implicitHeight: 70
                    anchors.fill: parent 
                }

                onClicked: {
                    lockTimer.restart()
                    $aladdinMaker.stop()
                    aladdinController.stop()
                    close();

                    status_loader.source = ""
                    // calEveryStatusTime()
                    report_loader.source = "study_report.qml"
                }
            }
        }

        Connections {
            target: $aladdinMaker
            onCurrentTime: {
                timeLabel.text = strTime
                lockTimer.restart()
            }
        }

        Connections {
            target: $aladdinMaker
            onActualTime: {
                // $actual_study_time = intTime + 1
                $actual_study_time = intTime
            }
        }

        /* six study status sgl
        Connections {
            target: aladdinController
            onSglPlayPhoneRate: {
                $play_phone_rate = d_rate
                console.log($play_phone_rate)
            }
        }

        Connections {
            target: aladdinController
            onSglLookLampRate: {
                $look_lamp_rate = d_rate
                console.log($look_lamp_rate)
            }
        }

        Connections {
            target: aladdinController
            onSglLookMonitorRate: {
                $look_monitor_rate = d_rate
                console.log($look_monitor_rate)
            }
        }

        Connections {
            target: aladdinController
            onSglLookBookRate: {
                $look_book_rate = d_rate
                console.log($look_book_rate)
            }
        }

        Connections {
            target: aladdinController
            onSglLookOtherRate: {
                $look_other_rate = d_rate
                console.log($look_other_rate)
            }
        }

        Connections {
            target: aladdinController
            onSglLookNoneRate: {
                $look_none_rate = d_rate
                console.log($look_none_rate)
            }
        }  // end of six study status sgl
        */


        Connections {
            target: $aladdinMaker
            onStopStudyStatus: {
                aladdinController.stop()
                close()

                status_loader.source = ""
                // calEveryStatusTime()
                report_loader.source = "study_report.qml"
            }
        }

        Connections {
            target: aladdinController
            onStudyStatus: {
                study_status_text.text = strStudyStatus;
                study_status_text.visible = true
                status_timer.start()
            }
        }

        Component.onCompleted: {
            $aladdinMaker.color = Qt.rgba(0, 180, 120, 255)
            $aladdinMaker.start()
            aladdinController.start()
            console.log("start all aladdin modules!")
        }
    }

    function setStudyTime(time) {
        $aladdinMaker.setFullTime(time)
    }

    /*
    function calEveryStatusTime() {
        JS.dbReadLastReport()
        $play_phone_time = Math.floor($play_phone_rate * $actual_study_time )
        $look_lamp_time = Math.floor($look_lamp_rate * $actual_study_time)
        $look_monitor_time = Math.floor($look_monitor_rate * $actual_study_time)
        $look_book_time = Math.floor($look_book_rate * $actual_study_time)
        $look_other_time = Math.floor($look_other_rate * $actual_study_time)
        $look_none_time = Math.floor($look_none_rate * $actual_study_time)
    }
    */

}
