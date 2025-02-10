#include "Mqtt.hpp"
#include <MQTTClient.h>
Mqtt::Mqtt(std::string SERVER_ADDRESS, std::string TOPIC, std::string USERNAME, std::string PASSWORD)
    : SERVER_ADDRESS{SERVER_ADDRESS},
    CLIENT_ID{"RaspiClient"}, TOPIC{TOPIC}, USERNAME{USERNAME},
    PASSWORD{PASSWORD}, brokerStatus(false),
    client(SERVER_ADDRESS, CLIENT_ID)
   {
    client.set_callback(cb);
    ssl_opt.set_enable_server_cert_auth(0);
    ssl_opt.set_verify(1);
    connOpts.set_ssl(ssl_opt);
    connOpts.set_clean_session(true);
    connOpts.set_user_name(USERNAME);
    connOpts.set_password(PASSWORD);
};
Mqtt::Mqtt(std::string SERVER_ADDRESS, std::string TOPIC)
   : SERVER_ADDRESS{SERVER_ADDRESS},
   CLIENT_ID{"RaspiClient"}, TOPIC{TOPIC}, brokerStatus(false), client(SERVER_ADDRESS, CLIENT_ID)
{
   client.set_callback(cb);
   connOpts.set_clean_session(true);
};
bool Mqtt::Initialize(){
    brokerStatus = client.is_connected();
    if(!brokerStatus)
    {
        try {
            // Connect to the broker
            std::cout << "Connecting to the broker..." << SERVER_ADDRESS << std::endl;
            client.connect(connOpts)->wait_for(TIMEOUT);
            // Subscribe to a topic
            std::cout << "Subscribing to topic: " << TOPIC << std::endl;
            client.subscribe(TOPIC, QOS)->wait_for(TIMEOUT);
            PushMessage("Hello", "ahmed/Test");
            brokerStatus = true;
        } catch (const mqtt::exception &exc) {
            std::cerr << "Error: " << exc.what() << std::endl;
            brokerStatus = false;
        }
    }
    return brokerStatus;
}
void Mqtt::PushMessage(std::string foo, std::string Topic){
    mqtt::message_ptr pubmsg = mqtt::make_message(Topic, foo);
    pubmsg->set_qos(QOS);
    client.publish(pubmsg)->wait_for(TIMEOUT);
}
std::string Mqtt::getMessage() {
    return cb.getMessage();
}
void Mqtt::Reconnect(){
    try {
        client.reconnect()->wait();
    } catch (const mqtt::exception &exc) {
        std::cerr << "Error during reconnecting: " << exc.what() << std::endl;
    }
}
void Mqtt::Disconnect()
{
    try {
        client.unsubscribe(TOPIC)->wait_for(100);
        client.disconnect()->wait_for(100);
        std::cout << "Disconnected successfully." << std::endl;
        brokerStatus = false;
    } catch (const mqtt::exception &exc) {
        std::cerr << "Error during disconnect: " << exc.what() << std::endl;
    }
}
bool Mqtt::isConnected()
{
    return client.is_connected();
}
Mqtt::~Mqtt() {
    Disconnect();
}
