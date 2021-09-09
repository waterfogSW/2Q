#pragma once
#ifndef CACHE_HPP
#define CAHCE_HPP

#include <list>
#include <string>
#include <unordered_map>

namespace cache {
typedef std::string Key;
typedef std::string Value;

class Node {
   public:
    Node(Key key, Value value) : key(key), value(value) {
        k_size = key.size();
        v_size = value.size();
    }

    Key key;
    Value value;

    //metadata
    size_t k_size;
    size_t v_size;
};

class Cache {
   public:
    Cache(size_t size) : max_csize(size) {}
    virtual ~Cache() { Clear(); }

    virtual void Insert(const Key &key, const Value &value) = 0;
    virtual Value Search(const Key &key) = 0;

    size_t getSize() { return max_csize; }
    size_t getHit() { return hit_count; }

   protected:
    void Clear() {
        que.clear();
        key_map.clear();
    }

    std::list<Node *> que;
    std::unordered_map<Key, std::list<Node *>::iterator> key_map;

    size_t max_csize;
    size_t hit_count = 0;
};

}  // namespace cache

#endif