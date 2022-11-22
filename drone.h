#ifndef DRONE_H
#define DRONE_H
#include <QString>

class Drone
{
public:
    Drone();

public:
    QString getDroneID() const;
    void setDroneID(const QString &value);

    QString getDronetype() const;
    void setDronType(const QString &value);

    QString getDrStrLongitude() const;
    void setDrStrLongitude(const QString &value);

    QString getDrStrLatitude() const;
    void setDrStrLatitude(const QString &value);

    QString getDrStrAltitude() const;
    void setDrStrAltitude(const QString &value);

    QString getDrEndLongitude() const;
    void setDrEndLongitude(const QString &value);

    QString getDrEndLatitude() const;
    void setDrEndLatitude(const QString &value);

    QString getDrEndAltitude() const;
    void setDrEndAltitude(const QString &value);



private:
    QString DroneID;
    QString DroneType;
    QString DrStrLongitude;
    QString DrStrLatitude;
    QString DrStrAltitude;
    QString DrEndLongitude;
    QString DrEndLatitude;
    QString DrEndAltitude;
};

#endif // DRONE_H
