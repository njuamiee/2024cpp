#include "trie.h"
#include <string_view>

// trie.cpp modifications

template <class T>
auto Trie::Get(std::string_view key) const -> const T * {
  if (root_ == nullptr) {
    return nullptr;
  }

  const TrieNode* current = root_.get();
  
  // Walk through each character in the key
  for (char c : key) {
    auto it = current->children_.find(c);
    if (it == current->children_.end()) {
      return nullptr;
    }
    current = it->second.get();
  }

  // Check if we reached a value node
  if (!current->is_value_node_) {
    return nullptr;
  }

  // Try to cast to TrieNodeWithValue<T>
  auto* value_node = dynamic_cast<const TrieNodeWithValue<T>*>(current);
  return value_node ? value_node->value_.get() : nullptr;
}

template <class T>
auto Trie::Put(std::string_view key, T value) const -> Trie {
  std::shared_ptr<const TrieNode> new_root;
  
  if (root_ == nullptr) {
    if (key.empty()) {
      return Trie(std::make_shared<TrieNodeWithValue<T>>(std::make_shared<T>(std::move(value))));
    }
    new_root = std::make_shared<TrieNode>();
  } else {
    new_root = std::shared_ptr<TrieNode>(root_->Clone().release());
  }

  auto current = std::const_pointer_cast<TrieNode>(new_root);
  std::shared_ptr<TrieNode> parent = nullptr;
  char last_char = 0;
  
  // Walk through the key, creating new nodes as needed
  for (char c : key) {
    parent = current;
    last_char = c;
    
    auto it = current->children_.find(c);
    if (it == current->children_.end()) {
      current->children_[c] = std::make_shared<TrieNode>();
    } else {
      current->children_[c] = std::shared_ptr<TrieNode>(it->second->Clone().release());
    }
    current = std::const_pointer_cast<TrieNode>(current->children_[c]);
  }

  // Create value node
  auto value_node = std::make_shared<TrieNodeWithValue<T>>(
    current->children_,
    std::make_shared<T>(std::move(value))
  );

  if (key.empty()) {
    return Trie(value_node);
  }

  parent->children_[last_char] = value_node;
  return Trie(new_root);
}

auto Trie::Remove(std::string_view key) const -> Trie {
  if (root_ == nullptr) {
    return Trie();
  }

  // If key is empty and root is a value node
  if (key.empty()) {
    if (root_->is_value_node_) {
      if (root_->children_.empty()) {
        return Trie();
      }
      return Trie(std::make_shared<TrieNode>(root_->children_));
    }
    return Trie(root_);
  }

  std::shared_ptr<const TrieNode> new_root = std::shared_ptr<TrieNode>(root_->Clone().release());
  auto current = std::const_pointer_cast<TrieNode>(new_root);
  
  struct PathNode {
    std::shared_ptr<TrieNode> node;
    char character;
  };
  std::vector<PathNode> path;
  
  // Walk to the node to remove
  for (char c : key) {
    auto it = current->children_.find(c);
    if (it == current->children_.end()) {
      return Trie(root_);  // Key not found
    }
    path.push_back({current, c});
    current->children_[c] = std::shared_ptr<TrieNode>(it->second->Clone().release());
    current = std::const_pointer_cast<TrieNode>(current->children_[c]);
  }

  if (!current->is_value_node_) {
    return Trie(root_);
  }

  if (!current->children_.empty()) {
    // Convert to regular node if it has children
    auto new_node = std::make_shared<TrieNode>(current->children_);
    path.back().node->children_[path.back().character] = new_node;
  } else {
    // Remove childless nodes
    for (auto it = path.rbegin(); it != path.rend(); ++it) {
      it->node->children_.erase(it->character);
      if (!it->node->children_.empty() || it->node->is_value_node_) {
        break;
      }
    }
  }

  if (new_root->children_.empty() && !new_root->is_value_node_) {
    return Trie();
  }

  return Trie(new_root);
}

// Below are explicit instantiation of template functions.
template auto Trie::Put(std::string_view key, uint32_t value) const -> Trie;
template auto Trie::Get(std::string_view key) const -> const uint32_t *;

template auto Trie::Put(std::string_view key, uint64_t value) const -> Trie;
template auto Trie::Get(std::string_view key) const -> const uint64_t *;

template auto Trie::Put(std::string_view key, std::string value) const -> Trie;
template auto Trie::Get(std::string_view key) const -> const std::string *;

using Integer = std::unique_ptr<uint32_t>;

template auto Trie::Put(std::string_view key, Integer value) const -> Trie;
template auto Trie::Get(std::string_view key) const -> const Integer *;

template auto Trie::Put(std::string_view key, MoveBlocked value) const -> Trie;
template auto Trie::Get(std::string_view key) const -> const MoveBlocked *;