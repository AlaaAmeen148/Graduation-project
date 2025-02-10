#include "zones.h"
#include <sstream>
#include <algorithm>
Zones::Zones()
    : localBroker("tcp://192.168.1.2:1884", "Zone 1"),
    hiveMq("ssl://821f7642c0484b89aef14234c7d41de3.s1.eu.hivemq.cloud:8883",
             "Zone 1", "mahdy", "121212Am"),refValues{"Null" , false, false, false, false, false}{

}

void Zones::SaveValue(ZoneInformation values){

}

bool Zones::startConnection(){
    bool status = localBroker.Initialize();
    status &= hiveMq.Initialize();
    return status;
}

ZoneInformation Zones::getMessage(){
    std::string hivemqMessage = hiveMq.getMessage(); //get message from hive mq broker if available
    std::string localBrokerMessage = localBroker.getMessage(); //get message from local broker if available
    //////////////////////////////////////////////
    /// this logic give higer piriority for hivemq
    /// if it empty then we will check on local broker received message
    /// if not message will be formatted and returned to main code to take action
    //////////////////////////////////////////////
    if(hivemqMessage.empty()){
        if(localBrokerMessage.empty()){

        }
        else{
           return returnFormat(localBrokerMessage);
        }
    }
    return returnFormat(hivemqMessage);
}
ZoneInformation Zones::returnFormat(std::string message)
{
    ZoneInformation &temp = refValues;
    std::array<std::string,2> extractedInfo;
    std::stringstream ss(message);
    std::string item;
    uint8_t cnt = 0;
    uint8_t deviceNum = 0;
    bool status = false;
    ///////////////////////////////////////////////
    /// Check whether message has content or not
    /// if not return null map
    /// else continue func execution
    //////////////////////////////////////////////
    if(message.empty()){
        return {"Null" , false, false, false, false, false};
    }
    //////////////////////////////////////////////
    /// parse string to 2 main strings saved in extractedInfo array
    //////////////////////////////////////////////
    while (std::getline(ss, item, ',') && cnt < 2) {
        // (&& cnt < 2 )  2 here is the maximum number of elements in extractedInfo array
        extractedInfo[cnt++] = item;
    }
    deviceNum = std::stoi(extractedInfo[1]); // get Zone Number from String
    temp.ZoneNum = extractedInfo[0];
    // transform parsed device command into lower case to avoid type missmatch from another developer
    std::transform(extractedInfo[1].begin(), extractedInfo[1].end(), extractedInfo[1].begin(), ::tolower);
    //////////////////////////////////////////////
    /// check if Device command have on
    /// if yes set status to true to turn on that device in ui
    /// else leave status with false
    //////////////////////////////////////////////
    if(extractedInfo[1].find("on") != std::string::npos){
        status = true;
    }
    ////////////////////////////////////////////////////////////////////////////////////////////
    /// switch on Device Number sented in broker Message
    /// to detect which device should be set to (T||F)
    /// and if device not listed return Null
    ///////////////////////////////////////////////////////////////////////////////////////////
    switch(deviceNum)
    {
    case 1:     temp.Dev1_status = status; break;
    case 2:     temp.Dev2_status = status; break;
    case 3:     temp.Dev3_status = status; break;
    case 4:     temp.Dev4_status = status; break;
    case 5:     temp.Dev5_status = status; break;
    default:    temp.ZoneNum = "Null";     break;
    }

    //////////////////////////////////////////////
    /// return formatted Zoneinfo Temp object to check it in the main code
    //////////////////////////////////////////////
    return temp;
}
