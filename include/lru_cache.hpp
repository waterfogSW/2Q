#ifndef LRU_CACHE_HPP
#define LRU_CACHE_HPP

#include "cache.hpp"

namespace cache {
class LRU : public Cache {
   public:
    LRU(size_t size) : Cache(size) {}

    void Insert(const Key &key, const Value &value);
    Value Search(const Key &key);
    // void Erase(const Key &key);
};

void LRU::Insert(const Key &key, const Value &value) {
    auto iter = key_map.find(key);
	Node* node;

	if(iter != key_map.end()) {
		que.erase(key_map[key]);	

		node = *key_map[key];
		
		node->value = value;
		node->v_size = value.size();

		hit_count++;
	} else {
		if(que.size() >= max_csize) {
			Node* tmp = que.back();
			key_map.erase(tmp->key);	
			que.pop_back();

			delete tmp;
		}
		
		node = new Node(key, value);
	}
	
	que.push_front(node);
	key_map[key] = que.begin();
}

Value LRU::Search(const Key &key) {
	auto iter = key_map.find(key);
	Value rvalue;
	Node* node;
	
	if(iter != key_map.end()) {
		que.erase(key_map[key]);
		
		node = *key_map[key];
		rvalue = (*key_map[key])->value;

		hit_count++;
		
		que.push_front(node);
		key_map[key] = que.begin();
		return rvalue;
	} 
    
    else {
		return "";
	}

    
}
}  // namespace cache

#endif