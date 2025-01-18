#include "MessageQueueManager.h"

// Message 类的实现

Message::Message(const char *d, int p) : priority(p) {
  size_t len = strlen(d) + 1;
  data = new char[len];
  strcpy(data, d);
}

Message::Message(Message &&other) noexcept : data(other.data), priority(other.priority) {
  other.data = nullptr;
  other.priority = 0;
}

Message &Message::operator=(Message &&other) noexcept {
  if (this != &other) {
      delete[] data;
      data = other.data;
      priority = other.priority;
      other.data = nullptr;
      other.priority = 0;
  }
  return *this;
}

Message::~Message() {
  delete[] data;
}

// MessageQueueManager 类的实现
MessageQueueManager::MessageQueueManager() {}

void MessageQueueManager::addMessage(Message m) {
  auto it = std::lower_bound(messages.begin(), messages.end(), m,
    [](const Message& a, const Message& b) {
      return a.priority < b.priority;
    });
  messages.insert(it, std::move(m));
}

MessageQueueManager::MessageQueueManager(MessageQueueManager &&other) noexcept {
  messages = std::move(other.messages);
}

MessageQueueManager &
MessageQueueManager::operator=(MessageQueueManager &&other) noexcept {
  if (this != &other){
      messages = std::move(other.messages);
  }
  return *this;
}

void MessageQueueManager::printMessages() const {
  for (const auto &msg : messages) {
    std::cout << "Message: " << msg.data << ", Priority: " << msg.priority
              << std::endl;
  }
}

MessageQueueManager::~MessageQueueManager() {
  std::cout << "Destructing MessageQueueManager" << std::endl;
}