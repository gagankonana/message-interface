#ifndef _LIBRARY_MESSAGE_SYSTEM_MESSAGE_H
#define _LIBRARY_MESSAGE_SYSTEM_MESSAGE_H

/*
Requirements:
Messaging systems
user to user message
user to group message
delete after certain period

message - time, sender, 
fetch messages, filter by sender, reciepient


nouns and verbs
Message  : content, time
User
Groups

send message
filter messages by sender, by reciepient



*/

#include <ctime>
#include <future>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>



class User {
public:
    User(const std::string& _username) : username{_username} {}
    [[nodiscard]] const std::string get_username() { return username; }

private:
    std::string username;
};

class Message {
public:
    Message(const std::string& _message, const std::time_t& _time, const std::shared_ptr<User>& _author) 
        : content(_message), time{_time}, author{_author} {}
    [[nodiscard]] const std::string get_content() { return content; }
    [[nodisacrd]] const std::string get_author() {return author->get_username(); }
    [[nodiscard]] const std::time_t get_time() { return time; }
private:
    std::string content;
    std::time_t time;
    std::shared_ptr<User> author;
};

class Group {
public:
    Group(const std::string& _groupname, const std::vector<std::shared_ptr<User>> _users) 
        : groupname{_groupname}, users{_users} {}
    void add_to_group(const std::shared_ptr<User> user) { users.push_back(user); }
    [[nodiscard]] const std::string get_groupname() { return groupname; }
private:
    std::string groupname;
    std::vector<std::shared_ptr<User>> users;
};

class Chat {
public:
    Chat() {}
    void add_to_chat(std::shared_ptr<Message> message) { messages.push_back(message); }
    const std::vector<std::shared_ptr<Message>> get_chat() { return messages; }
private:
    std::vector<std::shared_ptr<Message>> messages;
};

class System {
public:
    System() {}
    [[nodiscard]] bool create_user(const std::string& username) { 
        if (users.find(username) != users.end()) return false;
        std::shared_ptr<User> user = std::make_shared<User>(username);
        chats[username] = {};
        users[username] = user;
        return true;
    }

    [[nodiscard]] bool create_group(const std::string& groupname, const std::vector<std::shared_ptr<User>> _users) { 
        if (groups.find(groupname) != groups.end()) return false;
        std::shared_ptr<Group> group = std::make_shared<Group>(groupname, _users);
        return true;
    }

    [[nodiscard]] bool add_to_group(const std::string& _username, const std::string& _groupname) {
        if (groups.find(_groupname) == groups.end()) return false;
        groups[_groupname]->add_to_group(users[_username]);
        return true;
    }

    [[nodiscard]] bool send_text(const std::string& from, const std::string& to, const std::string& msg) {
        if (users.find(from) == users.end() || users.find(to) == users.end()) return false;
        if (chats[to].find(from) == chats[to].end()) {
            std::shared_ptr<Chat> chat = std::make_shared<Chat>();
            chats[to][from] = chat;
            chats[from][to] = chat;
        }
        std::chrono::time_point now = std::chrono::system_clock::now();
        time_t now_t = std::chrono::system_clock::to_time_t(now);
        std::shared_ptr<Message> message = std::make_shared<Message>(msg, now_t, users[from]);
        chats[to][from]->add_to_chat(message);
        return true;
    }

    [[nodiscard]] const std::vector<std::string> get_chat(const std::string& user1, const std::string& user2) {
        std::vector<std::string> out;
        for (auto message: chats[user1][user2]->get_chat()) {
            std::string s = message->get_author() + " : " + message->get_content() + "\n";
            out.push_back(std::move(s));
        }
        return out;
    }

private:
    std::unordered_map<std::string, std::unordered_map<std::string, std::shared_ptr<Chat>>> chats;
    std::unordered_map<std::string, std::shared_ptr<User>> users;
    std::unordered_map<std::string, std::shared_ptr<Group>> groups;
};

#endif