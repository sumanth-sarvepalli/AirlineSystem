/**
 * @file main.qml
 * @author sumanth (sumanth.sarvepalli@gmail.com)
 */

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
// import QtQuick.Templates as T

ApplicationWindow {
    visible: true
    width: 800
    height: 600
    title: "Airline System"

    // Heading Text
    Text {
        id: headingText
        anchors.horizontalCenter: parent.horizontalCenter
        text: qsTr("Airline System")
        font.pointSize: 24
        color: "White"
    }

    // Flight details in list view
    ListView {
        id: flightListView
        anchors {
            top: headingText.bottom
            topMargin: 20
        }
        width: parent.width
        height: 200
        model: flightModel

        ScrollBar.horizontal: ScrollBar{
            id: hScroll
            hoverEnabled: true
            active: hovered || pressed
            orientation: Qt.Horizontal
            policy: ScrollBar.AsNeeded
            size: 5
        }

        ScrollBar.vertical: ScrollBar{
            id: vScroll
            hoverEnabled: true
            active: hovered || pressed
            orientation: Qt.Vertical
            policy: ScrollBar.AsNeeded
            size: 5
        }

        delegate: Item {
            width: 100
            height: 50

            Row {
                spacing: 20

                Text {
                    text: model.flightNumber
                    color: "white"
                    width: 100
                }
                Text {
                    text: model.departure
                    color: "white"
                    width: 100
                }
                Text {
                    text: model.arrival
                    color: "white"
                    width: 100
                }
                Text {
                    text: model.time
                    color: "white"
                    width: 100
                }
            }
        }
    }

    // Flight information Column
    Column {
        id: flightColumn
        anchors{
            bottom: parent.bottom
            bottomMargin: 20
            horizontalCenter: parent.horizontalCenter
        }
        spacing: 20
        padding: 20

        // Trip type
        GridLayout {
            id: btnGrid
            RadioButton {
                text: "One-way"
                checked: true
            }
            RadioButton {
                text: "Round Trip"
            }
            RadioButton {
                text: "Multi-City"
            }
        }

        // City information
        GridLayout{
            id: txtBoxGrid
            columns: 2
            columnSpacing: 10

            Label {
                id: fromLbl
                text: qsTr("From:")
                Layout.alignment: Qt.AlignLeft
            }
            TextField {
                id: departureField
                placeholderText: "Departure City"
            }
            Label {
                id: toLbl
                text: qsTr("To:")
                Layout.alignment: Qt.AlignLeft
            }
            TextField {
                id: arrivalField
                placeholderText: "Arrival City"
            }
        }

        // Calendar for Date selection
        ComboBox {
            id: calendarDropdown
            width: 300
            model: ListModel {
                ListElement { text: "Select Date" }
            }

            onActivated: {
                //if (index === 0) {
                    calendarPopup.open()
                //}
            }
        }

        Popup {
            id: calendarPopup
            width: 300
            height: 300
            modal: true
            closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

            MonthGrid {
                id: monthGrid
                anchors.fill: parent
                month: Calendar.September
                year: 2024

                delegate: Item {
                    width: parent.width / 7
                    height: parent.height / 6

                    Rectangle {
                        anchors.fill: parent
                        color: model.today ? "lightblue" : "white"
                        border.color: "black"

                        Text {
                            anchors.centerIn: parent
                            text: model.day
                        }

                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                calendarDropdown.model.append({ text: model.date.toLocaleDateString() })
                                calendarPopup.close()
                            }
                        }
                    }
                }
            }
        }

        // search button
        Button {
            id: searchBtn
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Search Flights"
            onClicked: {
                flightModel.filterFlights(departureField.text, arrivalField.text);
            }
        }
    }
}
