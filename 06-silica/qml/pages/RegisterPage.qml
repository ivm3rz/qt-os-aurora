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
            title: qsTr("Регистрация пользователя")
        }

        TextField {
            id: phone
            width: parent.width
            maximumLength: 10
            placeholderText: qsTr("Введите номер мобильного телефона")
            inputMethodHints: Qt.ImhDialableCharactersOnly
            validator: RegExpValidator {
                regExp: /^[0-9]{10}$/
            }
            EnterKey.enabled: !errorHighlight
            EnterKey.iconSource: "image://theme/icon-m-enter-next"
            EnterKey.onClicked: console.log("Phone number " + text)
        }

        Button {
            text: qsTr( "Зарегистрироваться" )
            onClicked: pageStack.push("SecondPage.qml")
        }
    }
}


