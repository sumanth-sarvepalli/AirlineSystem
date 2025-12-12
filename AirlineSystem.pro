QT += quick sql

SOURCES += \
        main.cpp \
        controller/AirlineSystemController.cpp \
        controller/Flight.cpp \
        model/FlightModel.cpp

HEADERS += \
        controller/AirlineSystemController.h \
        controller/Flight.h \
        model/FlightModel.h

resources.files = main.qml \
    database/flights.db
resources.prefix = /AirlineSystem
RESOURCES += resources


# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
