#ifndef _LIBRARY_MESSAGE_SYSTEM_SRC_CONSUME_H
#define _LIBRARY_MESSAGE_SYSTEM_SRC_CONSUME_H

#include <SimpleAmqpClient/SimpleAmqpClient.h>
#include <string>

class Consume {
public:
    Consume(const std::string& username) {
        channel = AmqpClient::Channel::Create("localhost", 5672, "guest", "guest", "message-system", 131072);
        channel->DeclareQueue(username, false, true, false, true);
        channel->BasicConsume(username, "consumer-tag", true, false, false);
    }

    [[nodiscard]] std::string const read() {
        AmqpClient::Envelope::ptr_t envelope;
        if (channel->BasicConsumeMessage("consumer-tag", envelope, 0)){
            std::string message_body = envelope->Message()->Body();
            channel->BasicAck(envelope);
            return message_body;
        }
        return "";  
    }

private:
    AmqpClient::Channel::ptr_t channel; 
};

#endif