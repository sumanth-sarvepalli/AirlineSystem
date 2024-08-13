/**
 * @file FlightModel.cpp
 * @author sumanth (sumanth.sarvepalli@gmail.com)
 * @brief Flight model in listview
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

#include "FlightModel.h"

FlightModel::FlightModel(QObject *parent) : QAbstractListModel(parent) {}

int FlightModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent)
    return m_filteredFlights.count();
}

QVariant FlightModel::data(const QModelIndex &index, int role) const {
    if (index.row() < 0 || index.row() >= m_filteredFlights.count())
        return QVariant();

    QSharedPointer<Flight> flight = m_filteredFlights[index.row()];

    switch (role) {
    case FlightNumberRole:
        return flight->flightNumber();
    case DepartureRole:
        return flight->departure();
    case ArrivalRole:
        return flight->arrival();
    case TimeRole:
        return flight->time();
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> FlightModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[FlightNumberRole] = "flightNumber";
    roles[DepartureRole] = "departure";
    roles[ArrivalRole] = "arrival";
    roles[TimeRole] = "time";
    return roles;
}

void FlightModel::addFlight(QSharedPointer<Flight> flight) {
    beginInsertRows(QModelIndex(), m_flights.count(), m_flights.count());
    m_flights.append(flight);
    m_filteredFlights.append(flight); // Initially show all flights
    endInsertRows();
}

void FlightModel::filterFlights(const QString &departure, const QString &arrival) {
    beginResetModel();
    m_filteredFlights.clear();

    for (const auto &flight : qAsConst(m_flights)) {
        if ((departure.isEmpty() || flight->departure() == departure) &&
            (arrival.isEmpty() || flight->arrival() == arrival)) {
            m_filteredFlights.append(flight);
        }
    }

    endResetModel();
}
