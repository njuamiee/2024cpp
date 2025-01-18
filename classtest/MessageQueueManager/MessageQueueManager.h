#ifndef MESSAGE_QUEUE_MANAGER_H
#define MESSAGE_QUEUE_MANAGER_H

#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>

// Message 类的声明
class Message {
public:
    char* data;
    int priority;

    Message(const char* d, int p);
    Message(const Message& other) = delete;
    Message& operator=(const Message& other) = delete;
    Message(Message&& other) noexcept;
    Message& operator=(Message&& other) noexcept;
    ~Message();
};

// MessageQueueManager 类的声明
class MessageQueueManager {
public:
    std::vector<Message> messages;

    // 添加消息并按优先级顺序插入
    void addMessage(Message m);
    MessageQueueManager();
    MessageQueueManager(MessageQueueManager& other) = delete;
    MessageQueueManager& operator=(MessageQueueManager& other) = delete;
    MessageQueueManager(MessageQueueManager&& other) noexcept;
    MessageQueueManager& operator=(MessageQueueManager&& other) noexcept;

    // 打印消息队列
    void printMessages() const;

    ~MessageQueueManager();
};

#endif // MESSAGE_QUEUE_MANAGER_H