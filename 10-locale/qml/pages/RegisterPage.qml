import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: registerPage

    // Place our content in a Column.  The PageHeader is always placed at the top
    // of the page, followed by our content.
    Column {
        id: column
        width: parent.width
        spacing: Theme.paddingLarge

        PageHeader {
            title: qsTr("User registration")
        }

        TextField {
            id: phone
            width: parent.width
            maximumLength: 10
            label: qsTr("Phone number")
            placeholderText: qsTr("Enter mobile phone number")
            inputMethodHints: Qt.ImhDialableCharactersOnly
            validator: RegExpValidator {
                regExp: /^[0-9]{10}$/
            }
            EnterKey.enabled: !errorHighlight
            EnterKey.iconSource: "image://theme/icon-m-enter-next"
            EnterKey.onClicked: login.focus = true
            readonly property bool valid: text.length && !errorHighlight
        }

        TextField {
            id: login
            label: qsTr("Login")
            placeholderText: qsTr("Enter your login")
            width: parent.width
            validator: RegExpValidator {
                regExp: /^[a-z][a-z0-9_-]{2,15}$/
            }
            inputMethodHints: Qt.ImhNoAutoUppercase
            EnterKey.enabled: !errorHighlight
            EnterKey.iconSource: "image://theme/icon-m-enter-next"
            EnterKey.onClicked: focus = false
            readonly property bool valid: text.length && !errorHighlight
        }

        Button {
            id: confirm
            text: qsTr("Next")
            preferredWidth: Theme.buttonWidthLarge
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: pageStack.push("AccountPage.qml")
            enabled: phone.valid && login.valid
        }
    }
}


