#ifndef ZONES_H
#define ZONES_H
#include "Mqtt.hpp"
struct ZoneInformation{
    std::string ZoneNum = 0;
    bool Dev1_status = false;
    bool Dev2_status = false;
    bool Dev3_status = false;
    bool Dev4_status = false;
    bool Dev5_status = false;
};

class Zones
{
public:
    Zones();
    bool startConnection();
    ZoneInformation getMessage();

private:
    Mqtt localBroker;
    Mqtt hiveMq;
    void SaveValue(ZoneInformation);
    ZoneInformation returnFormat(std::string);
    ZoneInformation refValues;
};

#endif // ZONES_H
