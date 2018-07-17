import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.2
import channel_window 1.0
import titlebar_item 1.0
import statusbar_item 1.0
import vnaapp_window 1.0

VNAAppWindow{
    visible: true
    width: 1000
    height: 700

    titleBar:TitleBarItem{
        id:title
        color:"blue"

        leftIndent: height
        rightIndent: height*3

        barContent: Label{
            color: "white"
            text: "App window title"
        }
    }

    statusBar:StatusBarItem{
        id:status
        color: "blue"

        barContent: Label{
            color: "white"
            text: "Status: main"
        }
    }

    ChannelWindow{
        visible: true
        width: 300
        height: 100

        titleBar:TitleBarItem{
            color:"lightblue"

            leftIndent: height
            rightIndent: height*3

            barContent: Label{
                color: "white"
                text:"Channel window title"
            }
        }

        statusBar:StatusBarItem{
            color: "blue"

            barContent: Label{
                color: "white"
                text: "Status: sub"
            }
        }

    }

    ChannelWindow{
        visible: true
        width: 300
        height: 100

        titleBar:TitleBarItem{
            color:"lightblue"

            leftIndent: height
            rightIndent: height*3

            barContent: Label{
                color: "white"
                text:"Channel window title"
            }
        }

        statusBar:StatusBarItem{
            color: "blue"

            barContent: Label{
                color: "white"
                text: "Status: sub"
            }
        }

    }

    ChannelWindow{
        visible: true
        width: 300
        height: 100

        titleBar:TitleBarItem{
            color:"lightblue"

            leftIndent: height
            rightIndent: height*3

            barContent: Label{
                color: "white"
                text:"Channel window title"
            }
        }

        statusBar:StatusBarItem{
            color: "blue"

            barContent: Label{
                color: "white"
                text: "Status: sub"
            }
        }

    }
}
