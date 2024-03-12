#include "eksersajz/lru_cache.hpp"

LRUCache::LRUCache(int capacity) : capacity(capacity) {
  key_to_ptr.reserve(capacity);
}

int LRUCache::get(int key) {
  const auto it = key_to_ptr.find(key);
  if (it == key_to_ptr.end()) {
    return -1;
  }
  // make the value "recently used"

  // copy the key-value pair
  // erase it from the list
  // put the copy to the front of the list

  auto [k, v] = *it->second;
  kv.erase(it->second);
  kv.push_front({k, v});
  it->second = kv.begin();

  return v;
  // return std::get<1>(*it->second);
}

void LRUCache::put(int key, int value) {
  if (capacity > 0) {
    kv.push_front({key, value});
    key_to_ptr.insert_or_assign(key, kv.begin());

    capacity--;
  } else {
    // remove last element ("least recently used") from value list and hash Map
    // then push the new element to the front ("most recently used")
    const auto &[k, v] = kv.back();
    key_to_ptr.erase(k);

    kv.pop_back();
    kv.push_front({key, value});

    key_to_ptr.insert({key, kv.begin()});
  }
}
