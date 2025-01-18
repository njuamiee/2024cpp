#pragma once

#include <optional>
#include <shared_mutex>
#include <mutex>
#include <utility>

#include "trie.h"

template <class T>
class ValueGuard {
public:
    ValueGuard(Trie root, const T &value) : root_(std::move(root)), value_(value) {}
    auto operator*() const -> const T & { return value_; }

private:
    Trie root_;
    const T &value_;
};

class TrieStore {
public:
    template <class T>
    auto Get(std::string_view key) -> std::optional<ValueGuard<T>>;

    template <class T>
    void Put(std::string_view key, T value);

    void Remove(std::string_view key);

private:
    // Use shared_mutex to allow multiple readers
    mutable std::shared_mutex root_lock_;
    
    // Mutex for write operations
    std::mutex write_lock_;
    
    // Current root of the trie
    Trie root_;
};