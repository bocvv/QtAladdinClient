import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2

Window {
    id: win_details_word_result
    width: Screen.width
    height: Screen.height - 45
    x: 0
    y: 75
    visible: true

    Rectangle {
       id: menu_pad
       width: 200
       height: parent.height
       color: "#FFE5E5E5"
       anchors.left: parent.left

       Button {
           id: return_btn
           text: "返 回"
           font.pointSize: 30
           anchors.top: parent.top
           anchors.left: parent.left

           background: Rectangle {
               color: "#FF787878"
               implicitWidth: 200
               implicitHeight: 55
               anchors.fill: parent 
           }

           contentItem: Text {
               text: return_btn.text
               font: return_btn.font
               color: return_btn.down ? "green" : "#FFF5F5F5"
               horizontalAlignment: Text.AlignHCenter
               verticalAlignment: Text.AlignVCenter
               elide: Text.ElideRight
           }

           onClicked: {
               lockTimer.restart()
               details_loader.source = "";
           }
       }

       Button {
           id: basic_btn
           text: "基础释义"
           font.pointSize: 30
           anchors.top: return_btn.bottom
           anchors.topMargin: 20
           anchors.left: parent.left

           background: Rectangle {
               color: "#FFE5E5E5"
               implicitWidth: 200
               implicitHeight: 55
               anchors.fill: parent 
           }

           contentItem: Text {
               text: basic_btn.text
               font: basic_btn.font
               color: basic_btn.down ? "#FFA8071A" : "#FFA8071A"
               horizontalAlignment: Text.AlignHCenter
               verticalAlignment: Text.AlignVCenter
               elide: Text.ElideRight
           }
       }

       Rectangle {
           width: 7
           height: 55
           color: "#FFA8071A"
           anchors.left: parent.left
           anchors.verticalCenter: basic_btn.verticalCenter
       }
    }

    Flickable {
        id: details_flick
        anchors.top: parent.top 
        anchors.left: menu_pad.right
        width: Screen.width - 200
        height: parent.height
        contentWidth: width
        contentHeight: 2000

        Text {
            id: details_word_key
            width: parent.width
            height: 60
            visible: true
            text: ""
            color: "#FF262626"
            font.pointSize: 30
            font.bold: true

            anchors.top: parent.top
            // anchors.topMargin: 20
            anchors.left: parent.left
            anchors.leftMargin: 40

            // horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        Text {
            id: details_word_value
            width: parent.width - 100
            height: 2000
            visible: true
            text: ""
            color: "#FF000000"
            font.pointSize: 25
            anchors.top: details_word_key.bottom
            anchors.topMargin: 20
            anchors.left: parent.left
            anchors.leftMargin: 40
            // horizontalAlignment: Text.AlignHCenter
            // verticalAlignment: Text.AlignVCenter
            // elide: Text.ElideRight
            wrapMode: Text.WrapAnywhere
        }
    }

    Rectangle {
       id: details_scrollbar
       anchors.right: details_flick.right
       anchors.top: parent.top
       y: details_flick.visibleArea.yPosition * details_flick.height
       width: 10
       height: details_flick.visibleArea.heightRatio * details_flick.height
       color: "#FFF5F5F5"
   }

    function setDetailsData(word, explain) {
        details_word_key.text = word
        details_word_value.text = explain
    }
}
