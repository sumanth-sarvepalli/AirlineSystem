/**
 * @file FlightModel.h
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

#ifndef FLIGHTMODEL_H
#define FLIGHTMODEL_H

#include <QAbstractListModel>
#include <QSharedPointer>
#include "controller/Flight.h"

class FlightModel : public QAbstractListModel {
    Q_OBJECT

public:
    enum FlightRoles {
        FlightNumberRole = Qt::UserRole + 1,
        DepartureRole,
        ArrivalRole,
        TimeRole
    };

    explicit FlightModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    void addFlight(QSharedPointer<Flight> flight);
    void filterFlights(const QString &departure, const QString &arrival);

private:
    QList<QSharedPointer<Flight>> m_flights;
    QList<QSharedPointer<Flight>> m_filteredFlights;
};

#endif // FLIGHTMODEL_H
