/**
 * @file Flight.h
 * @author sumanth (sumanth.sarvepalli@gmail.com)
 * @brief update the details of flight
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

#ifndef FLIGHT_H
#define FLIGHT_H

#include <QObject>

class Flight : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString flightNumber READ flightNumber WRITE setFlightNumber NOTIFY flightNumberChanged)
    Q_PROPERTY(QString departure READ departure WRITE setDeparture NOTIFY departureChanged)
    Q_PROPERTY(QString arrival READ arrival WRITE setArrival NOTIFY arrivalChanged)
    Q_PROPERTY(QString time READ time WRITE setTime NOTIFY timeChanged)

public:
    Flight(const QString &flightNumber, const QString &departure, const QString &arrival, const QString &time, QObject *parent = nullptr);

    QString flightNumber() const;
    QString departure() const;
    QString arrival() const;
    QString time() const;

    void setFlightNumber(const QString &flightNumber);
    void setDeparture(const QString &departure);
    void setArrival(const QString &arrival);
    void setTime(const QString &time);

signals:
    void flightNumberChanged();
    void departureChanged();
    void arrivalChanged();
    void timeChanged();

private:
    QString m_flightNumber;
    QString m_departure;
    QString m_arrival;
    QString m_time;
};

#endif // FLIGHT_H
