import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.LocalStorage 2.9
import QtCharts 2.3

Window{
    id: win_study_report
    title: qsTr("studt report")
    width: Screen.width
    height: Screen.height - 45
    x: 0
    y: 75
    visible: true


    ColumnLayout {
        anchors.centerIn: parent
        // spacing: 5

        // 显示提示语句辛苦了, 请查看报告
        Text{
            id: study_how_much_time

            width: 500
            height: 40
            visible: true
            Layout.alignment: Qt.AlignCenter 
            text: qsTr("已专注学习 ") + Number($actual_study_time).toString() + qsTr(" 秒，休息一下吧~")
            font.pointSize: 26
        }
        
        Rectangle {
            id: chart_box 
            width: 800
            height: 370
            visible: true
            color: "#FFF5F5F5" 
            Layout.alignment: Qt.AlignCenter 

            Text {
                id: chart_text
                width: 600
                height: 300
                visible: true
                text: "研发小哥正在加紧开发中"
                color: "white"
                font.pointSize: 55
                anchors.fill: parent
                anchors.centerIn: parent
            }

            /*
            ChartView {
                id: chart
                // title: "本次学习状态报告"
                anchors.fill: parent
                legend.alignment: Qt.AlignBottom
                antialiasing: true

                HorizontalStackedBarSeries {
                    axisY: BarCategoryAxis { categories: ["无视线", "看其它", "看屏幕", "看手机", "看台灯", "看书" ] }
                    BarSet { label: "无视线"; values: [$look_none_time, 0, 0, 0, 0, 0] }
                    BarSet { label: "看其它"; values: [0, $look_other_time, 0, 0, 0, 0] }
                    BarSet { label: "看屏幕"; values: [0, 0, $look_monitor_time, 0, 0, 0] }
                    BarSet { label: "看手机"; values: [0, 0, 0, $play_phone_time, 0, 0] }
                    BarSet { label: "看台灯"; values: [0, 0, 0, 0, $look_lamp_time, 0] }
                    BarSet { label: "看书"; values: [0, 0, 0, 0, 0, $look_book_time] }

                    barWidth: 0.8
                }
            }
            */
        }

        RowLayout {
            Layout.alignment: Qt.AlignCenter 
            spacing: 60

            RoundButton {
                id: hand_homework
                text: "交作业"
                font.pointSize: 30

                contentItem: Text {
                    text: hand_homework.text
                    font: hand_homework.font
                    color: hand_homework.down ? "#FF262626" : "#FF262626"
                    // opacity: enabled ? 1.0 : 0.3
                    opacity: 0.2
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    elide: Text.ElideRight
                }

                background: Rectangle {
                    radius: 30
                    color: "#FF000000"
                    opacity: 0.3
                    implicitWidth: 270
                    implicitHeight: 70
                    anchors.fill: parent 
                }

                onClicked: {
                    lockTimer.restart()
                }
            }
 
            RoundButton {
                id: return_home
                text: "返回首页"
                font.pointSize: 30

                contentItem: Text {
                    text: return_home.text
                    font: return_home.font
                    // opacity: enabled ? 1.0 : 0.3
                    opacity: 1
                    color: return_home.down ? "#F5F5F5" : "#F5F5F5"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    elide: Text.ElideRight
                }

                background: Rectangle {
                    radius: 30
                    color: "#FF000000"
                    opacity: 0.5
                    // border.color: "black"
                    // border.width: 2
                    implicitWidth: 270
                    implicitHeight: 70
                    anchors.fill: parent 
                }

                onClicked: {
                    lockTimer.restart()
                    close();
                    control.visible = true
                    report_loader.source = "";
                }
            }

       }

        Component.onCompleted: {
            /*
            console.log($play_phone_time)
            console.log($look_lamp_time)
            console.log($look_monitor_time)
            console.log($look_book_time)
            console.log($look_other_time)
            console.log($look_none_time)
            */
        }
    }
}
