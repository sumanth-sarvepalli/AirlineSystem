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
#include <QDir>
#include <QGuiApplication>
#include <QFile>
#include <QStandardPaths>

AirlineSystemController::AirlineSystemController(QObject *parent)
    : QObject(parent), m_flightModel(new FlightModel(this)) {
    initializeDatabase();
}

AirlineSystemController::~AirlineSystemController() {
    if (m_database.isOpen()) {
        m_database.close();
    }
}

void AirlineSystemController::initializeDatabase() {
    QString dbPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/flights.db";
    QDir dir(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));
    if (!dir.exists()) {
        dir.mkpath(".");
    }

    if (!QFile::exists(dbPath)) {
        QFile::copy(":/AirlineSystem/database/flights.db", dbPath);
        QFile::setPermissions(dbPath, QFile::WriteOwner | QFile::ReadOwner);
    }

    m_database = QSqlDatabase::addDatabase("QSQLITE");
    m_database.setDatabaseName(dbPath);

    if (!m_database.open()) {
        qWarning() << "Error: Could not open database.";
        return;
    }

    loadFlights();
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

void AirlineSystemController::addFlight(const QString &flightNumber, const QString &departure, const QString &arrival, const QString &time)
{
    QSqlQuery query;
    query.prepare("INSERT INTO flights (flightNumber, departure, arrival, time) VALUES (?, ?, ?, ?)");
    query.addBindValue(flightNumber);
    query.addBindValue(departure);
    query.addBindValue(arrival);
    query.addBindValue(time);
    if (query.exec()) {
        QSharedPointer<Flight> flight = QSharedPointer<Flight>::create(flightNumber, departure, arrival, time);
        m_flightModel->addFlight(flight);
    } else {
        qWarning() << "Error: Could not add flight to database.";
    }
}

void AirlineSystemController::updateFlight(int index, const QString &flightNumber, const QString &departure, const QString &arrival, const QString &time)
{
    if (index >= 0 && index < m_flightModel->rowCount()) {
        QSharedPointer<Flight> flight = m_flightModel->flight(index);
        QSqlQuery query;
        query.prepare("UPDATE flights SET flightNumber = ?, departure = ?, arrival = ?, time = ? WHERE flightNumber = ?");
        query.addBindValue(flightNumber);
        query.addBindValue(departure);
        query.addBindValue(arrival);
        query.addBindValue(time);
        query.addBindValue(flight->flightNumber());
        if (query.exec()) {
            m_flightModel->updateFlight(index, flightNumber, departure, arrival, time);
        } else {
            qWarning() << "Error: Could not update flight in database.";
        }
    }
}

void AirlineSystemController::deleteFlight(int index)
{
    if (index >= 0 && index < m_flightModel->rowCount()) {
        QSharedPointer<Flight> flight = m_flightModel->flight(index);
        QSqlQuery query;
        query.prepare("DELETE FROM flights WHERE flightNumber = ?");
        query.addBindValue(flight->flightNumber());
        if (query.exec()) {
            m_flightModel->deleteFlight(index);
        } else {
            qWarning() << "Error: Could not delete flight from database.";
        }
    }
}

void AirlineSystemController::filterFlights(const QString &departure, const QString &arrival)
{
    m_flightModel->filterFlights(departure, arrival);
}

FlightModel *AirlineSystemController::flightModel() const
{
    return m_flightModel;
}
