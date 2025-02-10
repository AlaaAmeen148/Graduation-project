#pragma once 
#include "callback.hpp"
#include <string>
class Mqtt
{
public:
    Mqtt() = delete;
    Mqtt(std::string SERVER_ADDRESS, std::string TOPIC);
    Mqtt(std::string SERVER_ADDRESS, std::string TOPIC, std::string USERNAME, std::string PASSWORD);
    bool Initialize();
    void PushMessage(std::string, std::string) ;
    void Disconnect();
    void Reconnect();
    std::string getMessage();
    bool isConnected();
    ~Mqtt();
private:
    const std::string SERVER_ADDRESS;
    const std::string CLIENT_ID;
    const std::string TOPIC;
    const std::string USERNAME;
    const std::string PASSWORD;

    const int QOS = 0;
    const int TIMEOUT = 1000;
    bool brokerStatus;
    mqtt::async_client client;   
    mqtt::connect_options connOpts;
    mqtt::ssl_options ssl_opt;
    Callback cb;
};

