import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Window {
    width: Screen.width
    height: Screen.height - 45
    x: 0
    y: 75
    visible: true

    /*
    Rectangle {
        id: stop_orderRect
        x: 0
        y: 45
        z: 10
        width: parent.width - 350
        height: parent.height - 60
        color: "transparent"
        anchors.top: rect_title.bottom

        MouseArea{
            // activeFocusOnTab: true;
            anchors.fill: parent
            propagateComposedEvents: true

            onClicked: {
                lockTimer.restart()
                mouse.accepted = false;
                if (mouseX < Screen.width-350 && orderRect.x != Screen.width) {
                    menuStopAnim.start() 
                }
            }
        }
    }
    */

    //组合动画
    ParallelAnimation{
        id: menuStartAnim
        //属性动画
        NumberAnimation{
            target: orderRect
            properties: "x"
            from: Screen.width
            to: Screen.width - 350
            //动画持续时间，毫秒
            duration: 500
            //动画渐变曲线
            easing.type: Easing.OutQuad
        }
        /*
        NumberAnimation{
            target: orderRect
            properties: "opacity"
            from: 0.2
            to: 0.8
            duration: 500;
            easing.type: Easing.OutQuad
        }
        */
    }
    ParallelAnimation{
        id: menuStopAnim
        NumberAnimation{
            target: orderRect
            properties: "x"
            from: Screen.width - 350
            to: Screen.width
            duration: 500;
            easing.type: Easing.Linear
        }
        /*
        NumberAnimation{
            target: orderRect
            properties: "opacity"
            from: 0.8
            to: 0.2
            duration: 500;
            easing.type: Easing.Linear
        }
        */
    }

    Rectangle {
        id: orderRect
        x: Screen.width
        y: 45
        z: 10
        width: 350
        height: Screen.height - 45
        color: "gray"
        // radius: 5
        anchors.top: parent.top

        MouseArea{
            activeFocusOnTab: true;
            anchors.fill: parent

            onClicked: {
                lockTimer.restart()
            }
        }

        RoundButton {
            id: time_sort_btn
            text: "时间排序"
            width: 260
            height: 55
            font.pointSize: 25
            anchors.top: parent.top
            anchors.topMargin: 50
            anchors.horizontalCenter: parent.horizontalCenter

            contentItem: Text {
                text: time_sort_btn.text
                font: time_sort_btn.font
                color: time_sort_btn.down ? "green" : "#FFFFFFFF"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
            }

            background: Rectangle {
                radius: 22
                color: "#FFBB4F5C"
                implicitWidth: 260
                implicitHeight: 55
                opacity: 1.0
                anchors.fill: parent 
            }

            onClicked: {
                lockTimer.restart()
                wordModel.sort_by_time()
                order_btn.text = "时间";
            }
        }

        RoundButton {
            id: freq_sort_btn
            text: "频次排序"
            width: 260
            height: 55
            font.pointSize: 25
            anchors.top: time_sort_btn.bottom
            anchors.topMargin: 50
            anchors.horizontalCenter: parent.horizontalCenter

            contentItem: Text {
                text: freq_sort_btn.text
                font: freq_sort_btn.font
                color: freq_sort_btn.down ? "green" : "#FFFFFFFF"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
            }

            background: Rectangle {
                radius: 22
                color: "#FF676767"
                implicitWidth: 260
                implicitHeight: 55
                opacity: 1.0
                anchors.fill: parent 
            }

            onClicked: {
                lockTimer.restart()
                wordModel.sort_by_frequency()
                order_btn.text = "频次";
            }
        }
    }

    ColumnLayout {
        anchors.fill: parent

        Rectangle {
            id: rect_title
            width: Screen.width
            height: 60
            color: "#FFE5E5E5"
            z: 20

            Button {
                text: "返回"
                font.pointSize: 25
                anchors.left: parent.left
                anchors.leftMargin: 34.5
                anchors.verticalCenter: parent.verticalCenter

                background: Rectangle {
                    color: "#FFE5E5E5"
                    implicitWidth: 130
                    implicitHeight: 55
                    anchors.fill: parent 
                }

                onClicked: {
                    lockTimer.restart()
                    console.log("点击一次")
                    log_loader.source = "";
                }
            }

            Text {
                text: "查词历史"
                font.pointSize: 30
                font.bold: true
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
            }

            RoundButton {
                id: lang_btn
                text: "全部"
                width: 130
                height: 55
                font.pointSize: 25
                anchors.right: order_btn.left
                anchors.rightMargin: 20
                anchors.verticalCenter: parent.verticalCenter

                contentItem: Text {
                    text: lang_btn.text
                    font: lang_btn.font
                    opacity: enabled ? 0.4 : 0.4
                    color: lang_btn.down ? "#FF797979" : "#FF797979"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    elide: Text.ElideRight
                }

                background: Rectangle {
                    radius: 22
                    color: "#FFF5F5F5"
                    implicitWidth: 130
                    implicitHeight: 55
                    opacity: 1.0
                    anchors.fill: parent 
                }

                onClicked: {
                    lockTimer.restart()
                }
            }

            RoundButton {
                id: order_btn
                text: "时间"
                width: 130
                height: 55
                font.pointSize: 25
                anchors.right: parent.right
                anchors.rightMargin: 34.5
                anchors.verticalCenter: parent.verticalCenter

                contentItem: Text {
                    text: order_btn.text
                    font: order_btn.font
                    color: order_btn.down ? "green" : "#FF797979"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    elide: Text.ElideRight
                }

                background: Rectangle {
                    radius: 22
                    color: "#FFF5F5F5"
                    implicitWidth: 130
                    implicitHeight: 55
                    opacity: 1.0
                    anchors.fill: parent 
                }

                onClicked: {
                    lockTimer.restart()
                    menuStartAnim.start()
                }
            }
        }

        ListView {
            id: listView
            flickableDirection: Flickable.VerticalFlick
            // boundsBehavior: Flickable.StopAtBounds
            model: wordModel
            clip: true

            delegate: Rectangle {
                id: delegate_list
                height: 70
                width: Screen.width
                anchors.left: parent.left
                anchors.leftMargin: 34.5
                anchors.right: parent.right
                anchors.rightMargin: 34.5
                color: delegate_list.ListView.isCurrentItem ? "lightsteelblue" : "transparent"

                //高亮
                MouseArea{
                    id: mouse_delegate
 
                    enabled: true
                    anchors.fill: parent

                    // propagateComposedEvents: true

                    /*
                    onEntered:{
                        delegate_list.color = "#DCDCDC"
                        console.log("in")
                    }
                    onExited:{
                        delegate_list.color = "white"
                        console.log("out")
                    }
                    */
                    onClicked: {
                        lockTimer.restart()
                        // mouse.accepted = false;
                        delegate_list.ListView.view.currentIndex = index;

                        if (mouseX < Screen.width-350 && orderRect.x != Screen.width) {
                            menuStopAnim.start() 
                        }

                        console.log("item click.");
                    }
                }

                Item {
                    // spacing: 30 
 
                    anchors {
                        top: parent.top
                        left: parent.left
                        leftMargin: 12
                        right: parent.right
                        rightMargin: 12
                    }
                    //用于将该行显示在矩形垂直居中
                    anchors.verticalCenter: parent.verticalCenter
 
                    Text {
                        id: left_list_user
                        width: 500
                        height: 70
 
                        // Layout.alignment: Qt.AlignLeft
                        // Layout.leftMargin: 12

                        anchors {
                            left: parent.left
                            leftMargin: 12
                        }
 
                        text: word
                        color: "#333333"
                        font.pixelSize: 36
                        font.family: qsTr("微软雅黑")
                        font.bold: true

                        verticalAlignment: Text.AlignVCenter
                        elide: Text.ElideRight
                    }
 
                    Text {
                        id: right_list_user
                        width: 500
                        height: 70
 
                        // Layout.alignment: Qt.AlignRight
                        // Layout.rightMargin: 12

                        anchors {
                            right: parent.right
                            rightMargin: 12
                        }
 
                        text: explain
                        color: "#333333"
                        font.pixelSize: 36
                        font.family: qsTr("微软雅黑")

                        // horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        elide: Text.ElideRight
                    }
                }
            }

            Layout.fillWidth: true
            Layout.fillHeight: true

            ScrollBar.vertical: ScrollBar {}
        }
    }
}
