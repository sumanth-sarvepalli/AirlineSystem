/**
 * @file AirlineSystemController.cpp
 * @author sumanth (sumanth.sarvepalli@gmail.com)
 * @brief Controller file for Airline System
 * @version 0.1
 * @date 2024-08-11
 * 
 * @copyright Copyright (c) 2024 sumanth sarvepalli
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the 'Software'), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 */

#include "AirlineSystemController.h"
#include "Flight.h"
#include <QDebug>

AirlineSystemController::AirlineSystemController(QObject *parent)
    : QObject(parent), m_flightModel(new FlightModel(this)) {
    initializeDatabase();
    loadFlights();
}

AirlineSystemController::~AirlineSystemController() {
    if (m_database.isOpen()) {
        m_database.close();
    }
}

void AirlineSystemController::initializeDatabase() {
    m_database = QSqlDatabase::addDatabase("QSQLITE");
    m_database.setDatabaseName("../database/flights.db"); //set db path

    if (!m_database.open()) {
        qWarning() << "Error: Could not open database.";

        QSqlQuery query;
        query.exec("CREATE TABLE IF NOT EXISTS flights ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "flightNumber TEXT, "
                   "departure TEXT, "
                   "arrival TEXT, "
                   "time TEXT)");

        // Example data insertion (can be removed after initial setup)
        query.exec("INSERT INTO flights (flightNumber, departure, arrival, time) VALUES "
                   "('AI101', 'New York', 'London', '08:00 AM'), "
                   "('BA202', 'London', 'Paris', '10:00 AM'), "
                   "('AF303', 'Paris', 'Berlin', '01:00 PM'), "
                   "('LH404', 'Berlin', 'Rome', '03:00 PM')");

        return;
    }
}

void AirlineSystemController::loadFlights() {
    QSqlQuery query("SELECT flightNumber, departure, arrival, time FROM flights");

    while (query.next()) {
        QString flightNumber = query.value(0).toString();
        QString departure = query.value(1).toString();
        QString arrival = query.value(2).toString();
        QString time = query.value(3).toString();

        QSharedPointer<Flight> flight = QSharedPointer<Flight>::create(flightNumber, departure, arrival, time);
        m_flightModel->addFlight(flight);
    }
}

FlightModel *AirlineSystemController::flightModel() const {
    return m_flightModel;
}
