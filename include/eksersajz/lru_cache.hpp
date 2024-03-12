#pragma once

#include <list>
#include <memory>
#include <unordered_map>

class LRUCache {
public:
  LRUCache(int capacity);
  ~LRUCache() = default;

  int get(int key);
  void put(int key, int value);

private:
  using KeyT = int;
  using ValT = int;

  int capacity;

  std::unordered_map<KeyT, std::list<std::tuple<KeyT, ValT>>::iterator>
      key_to_ptr{};
  // hash map will store pointers to elements in the list
  std::list<std::tuple<KeyT, ValT>> kv{};
};
