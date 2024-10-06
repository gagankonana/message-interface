#include<iostream>
#include "producer.h"
#include "consume.h"


class User {
public:
    User(const std::string& _username, const std::string& _friend_username): username(_username), friend_username(_friend_username), producer(_username),  consumer(_friend_username){
        messages = "";
    }

    std::string fetch_all_messages() {
        std::string read = consumer.read();
        if (read.empty()) return messages;
        messages += "\n" + friend_username + " : " + read;
        return messages;
    }

    void display_messages() {
        std::cout << fetch_all_messages() << std::endl;
    }

    void send_message() {
        std::string message;
        std::cout << std::endl << "You : ";
        std::cin >> message;
        messages+= "\n You : " + message;
        producer.send(message);
    }

    void start_message() {       
        while(true) {            
            std::cout << "Choose from below: \n1. Read All Messages \n2.Send Message\n";
            int option;
            std::cin >> option;
            switch (option)
            {
            case 1:
                display_messages();
                break;
            case 2:
                send_message();
                break;
            default:
                break;
            } 
        }
    }

private:
    std::string username;
    std::string friend_username;
    std::string messages;
    Produce producer;
    Consume consumer;

};
