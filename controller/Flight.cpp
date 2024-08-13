/**
 * @file Flight.cpp
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

#include "Flight.h"

Flight::Flight(const QString &flightNumber, const QString &departure, const QString &arrival, const QString &time, QObject *parent)
    : QObject(parent), m_flightNumber(flightNumber), m_departure(departure), m_arrival(arrival), m_time(time) {}

QString Flight::flightNumber() const { return m_flightNumber; }
QString Flight::departure() const { return m_departure; }
QString Flight::arrival() const { return m_arrival; }
QString Flight::time() const { return m_time; }

void Flight::setFlightNumber(const QString &flightNumber) {
    if (m_flightNumber != flightNumber) {
        m_flightNumber = flightNumber;
        emit flightNumberChanged();
    }
}

void Flight::setDeparture(const QString &departure) {
    if (m_departure != departure) {
        m_departure = departure;
        emit departureChanged();
    }
}

void Flight::setArrival(const QString &arrival) {
    if (m_arrival != arrival) {
        m_arrival = arrival;
        emit arrivalChanged();
    }
}

void Flight::setTime(const QString &time) {
    if (m_time != time) {
        m_time = time;
        emit timeChanged();
    }
}
