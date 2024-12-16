import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.2
import GraphRenderer 1.0

Window {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("График")

    FileDialog {
        id: fileDialog
        title: "Выберите файл"
        nameFilters: ["Touchstone (*.s1p)", "Все файлы (*)"]

        onAccepted: fileParser.loadFile(fileUrl)
    }

    Button {
        id: button
        text: qsTr("Загрузить файл")
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.margins: 20

        onClicked: fileDialog.open()
    }

    Rectangle {
        id: background
        color: "lightgray"
        anchors {
            right: parent.right
            left: parent.left
            top: parent.top
            bottom: button.top
            margins: 20
        }

        GraphRenderer {
            id: graphRenderer
            anchors.fill: parent
            anchors.margins: 20
        }
    }

    MessageDialog {
        id: errorDialog
        title: "Ошибка"
        text: ""
        icon: StandardIcon.Critical
        onAccepted: {
            errorDialog.visible = false
        }
    }

    Connections {
        target: dataProcessor
        onDataReady: {
            graphRenderer.setGraphData(X, Y)
        }
    }

    Connections {
        target: errorHandler
        onErrorOccurred: {
            errorDialog.text = message
            errorDialog.open()
        }
    }
}
