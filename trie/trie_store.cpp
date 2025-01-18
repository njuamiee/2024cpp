#include "trie_store.h"

template <class T>
auto TrieStore::Get(std::string_view key) -> std::optional<ValueGuard<T>> {
  // Only acquire shared lock for reading
  std::shared_lock<std::shared_mutex> guard(root_lock_);
  
  // Get current state of the trie
  auto current_root = root_;
  
  // Lookup value while holding the shared lock
  const T* value = current_root.Get<T>(key);
  if (value == nullptr) {
    return std::nullopt;
  }
  
  // Return ValueGuard with copy of current root and reference to value
  return ValueGuard<T>(current_root, *value);
}

template <class T>
void TrieStore::Put(std::string_view key, T value) {
  // First prepare the new value outside the lock
  auto new_value = std::move(value);
  
  // Then acquire exclusive lock for writing
  std::unique_lock<std::shared_mutex> guard(root_lock_);
  
  // Update root with new value
  root_ = root_.Put(key, std::move(new_value));
}

void TrieStore::Remove(std::string_view key) {
  // Acquire exclusive lock for writing
  std::unique_lock<std::shared_mutex> guard(root_lock_);
  
  // Remove key and update root
  root_ = root_.Remove(key);
}

// Below are explicit instantiation of template functions.

template auto TrieStore::Get(std::string_view key) -> std::optional<ValueGuard<uint32_t>>;
template void TrieStore::Put(std::string_view key, uint32_t value);

template auto TrieStore::Get(std::string_view key) -> std::optional<ValueGuard<std::string>>;
template void TrieStore::Put(std::string_view key, std::string value);

using Integer = std::unique_ptr<uint32_t>;

template auto TrieStore::Get(std::string_view key) -> std::optional<ValueGuard<Integer>>;
template void TrieStore::Put(std::string_view key, Integer value);

template auto TrieStore::Get(std::string_view key) -> std::optional<ValueGuard<MoveBlocked>>;
template void TrieStore::Put(std::string_view key, MoveBlocked value);