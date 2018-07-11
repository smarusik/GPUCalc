import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.2
import base_window 1.0
import workarea_item 1.0
import titlebar_item 1.0
import statusbar_item 1.0
import vnaapp_window 1.0

VNAAppWindow{
    visible: true
    width: 500
    height: 500

    titleBar:TitleBarItem{
        id:title
        color:"blue"

        leftIndent: height
        rightIndent: height*3

        barContent: Rectangle{
            color: "green"
        }
    }

    statusBar:StatusBarItem{
        id:status
        color: "blue"

        barContent: Label{
            color: "magenta"
            text: "Status: screwed-up."
        }
    }

    BaseWindow{
        visible: true
        width: 100
        height: 100

        titleBar:TitleBarItem{
            color:"lightblue"

            leftIndent: height
            rightIndent: height*3

            barContent: Rectangle{
                color: "lightgreen"
            }
        }

        statusBar:StatusBarItem{
            color: "blue"

            barContent: Label{
                color: "white"
                text: "Status: internal."
            }
        }

    }
}
