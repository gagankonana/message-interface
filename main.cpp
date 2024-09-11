#include "message.h"
#include <iostream>


int main() {
    System system{};
    system.create_user("user1");
    system.create_user("user2");

    system.send_text("user1", "user2", "Hellowww");
    system.send_text("user2", "user1", "How are you?");
    system.send_text("user1", "user2", "I am good! How are you?");

    for (auto& msg : system.get_chat("user1", "user2")) {
       std::cout << msg;
    }
    return 1;
}