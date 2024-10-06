#ifndef _LIBRARY_MESSAGE_SYSTEM_SRC_PRODUCE_H
#define _LIBRARY_MESSAGE_SYSTEM_SRC_PRODUCE_H

#include <SimpleAmqpClient/SimpleAmqpClient.h>
#include <string>

class Produce {
public:
  Produce(const std::string &_username) {
    username = _username;
    channel = AmqpClient::Channel::Create("localhost", 5672, "guest", "guest",
                                          "message-system", 131072);
    channel->DeclareQueue(username, false, true, false, true);
  }

  void send(const std::string &_message) {
    auto message = AmqpClient::BasicMessage::Create(_message);
    message->ContentType("application/json");
    message->Type("XYZRequest");
    message->AppId("a guid");
    AmqpClient::Table headersTable;
    headersTable.insert(
        std::pair<std::string, std::string>("Key-1", "value-1"));
    headersTable.insert(
        std::pair<std::string, std::string>("Key-2", "value-2"));
    message->HeaderTable(headersTable);
    channel->BasicPublish("", username, message);
  }

private:
  AmqpClient::Channel::ptr_t channel;
  std::string username;
};

#endif