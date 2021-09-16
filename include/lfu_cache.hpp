#ifndef LFU_CACHE_HPP
#define LFU_CACHE_HPP

#include "cache.hpp"

namespace cache {
class LFU : public Cache {
   public:
    LFU(size_t size) : Cache(size) {}

    void Insert(const Key &key, const Value &value);
    Value Search(const Key &key);

   private:
    // find least frequently referenced page
    std::list<Node *>::iterator findLFPage();
};

void LFU::Insert(const Key &key, const Value &value) {
    auto iter = key_map.find(key);
	Node* node;

	if(iter != key_map.end()) {
		que.erase(key_map[key]);	

		node = *key_map[key];
		
		node->value = value;
		node->v_size = value.size();

		hit_count++;
        node->cnt++;
	} else {
		if(que.size() >= max_csize) {
            auto it = findLFPage();
			Node* tmp = *it;

			key_map.erase(tmp->key);	
			que.erase(it);

			delete tmp;
		}
		
		node = new Node(key, value);
	}
	
	que.push_front(node);
	key_map[key] = que.begin();
}

Value LFU::Search(const Key &key) {
    auto iter = key_map.find(key);
    Value rvalue;
    Node *node;

    if(iter != key_map.end()) {
        que.erase(key_map[key]);

        node = *key_map[key];
        rvalue = (*key_map[key])->value;

        hit_count++;
        node->cnt++;

        que.push_front(node);
        key_map[key] = que.begin();
        return rvalue;
    }

    else {
        return "";
    }
}

std::list<Node *>::iterator LFU::findLFPage() {
    auto min_it = que.begin();
    int min = que.front()->cnt;

    for (auto it = que.begin(); it != que.end(); it++) {
        Node *tmp = *it;
        if (min > tmp->cnt) {
            min_it = it;
            min = tmp->cnt;
        }
    }

    return min_it;
}
}  // namespace cache

#endif