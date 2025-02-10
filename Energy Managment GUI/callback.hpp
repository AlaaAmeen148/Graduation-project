#pragma once
#include <mqtt/async_client.h>
#include <string>

class Callback : public virtual mqtt::callback {
public:

    void message_arrived(mqtt::const_message_ptr msg) override;
    void connected(const std::string &cause) override;
    void connection_lost(const std::string &cause) override;
  void delivery_complete(mqtt::delivery_token_ptr token) override;
  std::string getMessage() ;
private:
    std::string Message;
};
