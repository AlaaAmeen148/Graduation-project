#include "callback.hpp"

void Callback::message_arrived(mqtt::const_message_ptr msg) {
  Message = msg->get_topic() + "," + msg->to_string();
}
void Callback::connected(const std::string &cause){
    // try {
    //     client->reconnect()->wait_for(100);
    //     std::cout << "Re-subscribed to topic: " << topic << std::endl;
    // } catch (const mqtt::exception &exc) {
    //     std::cerr << "Error re-subscribing: " << exc.what() << std::endl;
    // }
}
void Callback::connection_lost(const std::string &cause) {
    std::cout << "connectionlost: " << cause << std::endl;
    // try {
    //     client->reconnect()->wait();
    //     client->subscribe(topic, QOS)->wait();
    //     std::cout << "Re-subscribed to topic: " << topic << std::endl;
    // } catch (const mqtt::exception &exc) {
    //     std::cerr << "Error re-subscribing: " << exc.what() << std::endl;
    // }
}
void Callback::delivery_complete(mqtt::delivery_token_ptr token) {}

std::string Callback::getMessage() {
  std::string Temp = Message;
  Message.clear();
  return Temp;
}
