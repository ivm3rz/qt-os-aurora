import QtQuick 2.0
import Sailfish.Silica 1.0


Page {
    id: accountPage

    Column {
        id: column
        width: parent.width
        spacing: Theme.paddingLarge

        PageHeader {
            title: qsTr("User info")
        }

        TextField {
            id: name
            width: parent.width
            maximumLength: 16
            label: qsTr("Name")
            inputMethodHints: Qt.ImhNoAutoUppercase
            EnterKey.enabled: !errorHighlight
            EnterKey.iconSource: "image://theme/icon-m-enter-next"
            EnterKey.onClicked: surname.focus = true
        }

        TextField {
            id: surname
            width: parent.width
            maximumLength: 24
            label: qsTr("Surname")
            inputMethodHints: Qt.ImhNoAutoUppercase
            EnterKey.enabled: !errorHighlight
            EnterKey.iconSource: "image://theme/icon-m-enter-next"
            EnterKey.onClicked: email.focus = true
        }

        TextField {
            id: email
            label: qsTr("Email")
            placeholderText: qsTr("Enter your email")
            width: parent.width
            validator: RegExpValidator {
                regExp: /^[\w-\.]+@([\w-]+\.)+[\w-]{2,4}$/
            }
            inputMethodHints: Qt.ImhEmailCharactersOnly
            EnterKey.enabled: !errorHighlight
            EnterKey.iconSource: "image://theme/icon-m-enter-next"
            EnterKey.onClicked: focus = false
            readonly property bool valid: text.length && !errorHighlight
        }

        ComboBox {
            label: qsTr("Favorite progamming language")
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
            text: qsTr("I consent to the processing of personal data")
            enabled: email.valid
        }
    }
}





