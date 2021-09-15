#ifndef TWO_Q_CACHE_HPP
#define TWO_Q_CACHE_HPP

#include "cache.hpp"

namespace cache {
class TWO_Q : public Cache {
   public:
    TWO_Q(size_t am_size, size_t a1_size) : Cache(am_size) {
        max_sub_csize = a1_size;
    }

    void Insert(const Key &key, const Value &value);
    Value Search(const Key &key);
    // void Erase(const Key &key);

   private:
    std::list<Node *> sub_que;
    std::unordered_map<Key, std::list<Node *>::iterator> sub_key_map;

    size_t max_sub_csize = 0;
};

void TWO_Q::Insert(const Key &key, const Value &value) {
    // Search Am Cash.
    auto iter = key_map.find(key);
    Node* node;

    // Am cache hit
    if (iter != key_map.end()) {
        que.erase(key_map[key]);

        node = *key_map[key];

        node->value = value;
        node->v_size = value.size();

        hit_count++;

        que.push_front(node);
        key_map[key] = que.begin();
    }

    // Am cache miss
    else {
        // Search A1 Cash.
        auto sub_iter = sub_key_map.find(key);
        // A1 cache hit
        if (sub_iter != sub_key_map.end()) {
            node = *sub_key_map[key];

            node->value = value;
            node->v_size = value.size();

            hit_count++;

            // erase from A1 cache
            sub_que.erase(sub_key_map[key]);
            sub_key_map.erase(sub_iter);

            // push Am cache
            if(que.size() >= max_csize) {
                Node* tmp = que.back();
                key_map.erase(tmp->key);
                que.pop_back();
                delete tmp;
            }

            node = new Node(key, value);
            
            que.push_front(node);
            key_map[key] = que.begin();
        }
        // A1 cache miss
        else {
            if (sub_que.size() >= max_sub_csize) {
                Node *tmp = sub_que.back();
                sub_key_map.erase(tmp->key);
                sub_que.pop_back();

                delete tmp;
            }

            node = new Node(key, value);

            sub_que.push_front(node);
            sub_key_map[key] = sub_que.begin();
        }
    }
}

Value TWO_Q::Search(const Key &key) {
    // Search Am Cash.
    auto iter = key_map.find(key);
    Value rvalue;
    Node *node;

    // Am cache hit
    if(iter != key_map.end()) {
        que.erase(key_map[key]);

        node = *key_map[key];
        rvalue = (*key_map[key])->value;

        hit_count++;

        que.push_front(node);
        key_map[key] = que.begin();
        return rvalue;
    }

    // Am cache miss
    else {
        // Search A1 Cash.
        auto sub_iter = sub_key_map.find(key);
        // A1 cache hit
        if(sub_iter != sub_key_map.end()) {
            sub_que.erase(sub_key_map[key]);

            node = *sub_key_map[key];
            rvalue = (*sub_key_map[key])->value;

            hit_count++;

            // erase from A1 cache
            sub_key_map.erase(sub_iter);
            sub_que.erase(sub_key_map[key]);

            // push Am cache
            que.push_front(node);
            key_map[key] = que.begin();

            return rvalue;
        }
        // A1 cache miss
        else {
            return "";
        }
    }
}

}  // namespace cache

#endif