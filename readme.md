# Messaging System

This project implements a basic messaging system that supports user-to-user and user-to-group messaging with features like message filtering and timed deletion.

## Features

- **User-to-User Messaging**: Send messages between individual users.
- **User-to-Group Messaging**: Send messages to groups of users.
- **Message Attributes**: Each message includes content, timestamp, and sender information.
- **Filter Messages**: Messages can be filtered by sender or recipient.

## Classes Overview

- `User`: Represents a user in the system.
- `Message`: Stores message content, time, and author.
- `Group`: Manages groups of users.
- `Chat`: Manages conversations between users.
- `System`: Handles user creation, group creation, and sending messages.

## Example Usage

1. **Create a user**:
    ```cpp
    System system;
    system.create_user("Alice");
    system.create_user("Bob");
    ```

2. **Send a message**:
    ```cpp
    system.send_text("Alice", "Bob", "Hello, Bob!");
    ```

3. **Fetch chat**:
    ```cpp
    auto chat = system.get_chat("Alice", "Bob");
    for (const auto& message : chat) {
        std::cout << message;
    }
    ```