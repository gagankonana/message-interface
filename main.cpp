#include "src/message.h"
#include <iostream>
#include "src/interface.h"


// int main() {
//     // System system{};
//     // system.create_user("user1");
//     // system.create_user("user2");

//     // system.send_text("user1", "user2", "Hellowww");
//     // system.send_text("user2", "user1", "How are you?");
//     // system.send_text("user1", "user2", "I am good! How are you?");

//     // for (auto& msg : system.get_chat("user1", "user2")) {
//     //    std::cout << msg;
//     // }
//     // return 1;
// }

int main() {
    std::string username, friend_username;
    std::cout << "Enter your name : ";
    std::cin >> username;
    std::cout << "Enter the username of the person you want to message : ";
    std::cin >> friend_username;
    User user{username, friend_username};
    user.start_message();
}