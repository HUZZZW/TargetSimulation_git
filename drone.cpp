#include "drone.h"

Drone::Drone()
{

}

QString Drone::getDroneID() const
{
    return DroneID;
}

void Drone::setDroneID(const QString &value)
{
    DroneID = value;
}

QString Drone::getDronetype() const
{
    return DroneType;
}

void Drone::setDronType(const QString &value)
{
    DroneType = value;
}

QString Drone::getDrStrLongitude() const
{
    return DrStrLongitude;
}

void Drone::setDrStrLongitude(const QString &value)
{
    DrStrLongitude = value;
}

QString Drone::getDrStrLatitude() const
{
    return DrStrLatitude;
}

void Drone::setDrStrLatitude(const QString &value)
{
    DrStrLatitude = value;
}


QString Drone::getDrStrAltitude() const
{
    return DrStrAltitude;
}

void Drone::setDrStrAltitude(const QString &value)
{
    DrStrAltitude = value;
}


QString Drone::getDrEndLongitude() const
{
    return DrStrAltitude;
}

void Drone::setDrEndLongitude(const QString &value)
{
    DrStrAltitude = value;
}


QString Drone::getDrEndLatitude() const
{
    return DrStrLatitude;
}

void Drone::setDrEndLatitude(const QString &value)
{
    DrStrLatitude = value;
}


QString Drone::getDrEndAltitude() const
{
    return DrStrAltitude;
}

void Drone::setDrEndAltitude(const QString &value)
{
    DrStrAltitude = value;
}
