/**
 * @file main.qml
 * @author sumanth (sumanth.sarvepalli@gmail.com)
 */

import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    visible: true
    width: 800
    height: 600
    title: "Airline System"

    Column {
        spacing: 20
        padding: 20

        TextField {
            id: departureField
            placeholderText: "Enter Departure City"
        }

        TextField {
            id: arrivalField
            placeholderText: "Enter Arrival City"
        }

        Button {
            text: "Search Flights"
            onClicked: {
                flightModel.filterFlights(departureField.text, arrivalField.text);
            }
        }
    }

    ListView {
        id: flightListView
        width: parent.width
        height: 200
        model: flightModel

        delegate: Item {
            width: parent.width
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
}
