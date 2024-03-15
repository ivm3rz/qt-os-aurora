import QtQuick 2.0
import Sailfish.Silica 1.0


Page {
    id: accountPage

    Column {
        id: column
        width: parent.width
        spacing: Theme.paddingLarge

        PageHeader {
            title: qsTr("Сведения о пользователе")
        }

        TextField {
            id: name
            width: parent.width
            maximumLength: 16
            label: qsTr("Имя")
            inputMethodHints: Qt.ImhNoAutoUppercase
            EnterKey.enabled: !errorHighlight
            EnterKey.iconSource: "image://theme/icon-m-enter-next"
            EnterKey.onClicked: console.log("Enter name " + text)
        }

        TextField {
            id: surname
            width: parent.width
            maximumLength: 24
            label: qsTr("Фамилия")
            inputMethodHints: Qt.ImhNoAutoUppercase
            EnterKey.enabled: !errorHighlight
            EnterKey.iconSource: "image://theme/icon-m-enter-next"
            EnterKey.onClicked: console.log("Enter name " + text)
        }

        TextField {
            id: email
            label: qsTr("Электронная почта")
            placeholderText: qsTr("Введите адрес электронной почты")
            width: parent.width
            validator: RegExpValidator {
                regExp: /^[\w-\.]+@([\w-]+\.)+[\w-]{2,4}$/
            }
            inputMethodHints: Qt.ImhEmailCharactersOnly
            EnterKey.enabled: !errorHighlight
            EnterKey.iconSource: "image://theme/icon-m-enter-next"
            EnterKey.onClicked: console.log("Enter login " + text)
            readonly property bool valid: text.length && !errorHighlight
        }

        ComboBox {
            label: qsTr("Предпочитаемый язык программирования")
            currentIndex: -1
            menu: ContextMenu {
                MenuItem { text: "С++" }
                MenuItem { text: "Python" }
                MenuItem { text: "Kotlin" }
                MenuItem { text: "Swift" }
                MenuItem { text: "Rust" }
            }
        }

        TextSwitch {
            id: agreement
            text: qsTr("Я даю согласие на обработку персональных данных")
            enabled: email.valid
        }
    }
}





