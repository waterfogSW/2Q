#include <bits/stdc++.h>
using namespace std;

#include "lru_cache.hpp"
#include "fifo_cache.hpp"
#include "two_q_cache.hpp"

int main() {
    cache::TWO_Q a(5);

    a.Insert("key1","val1");
    a.Insert("key1","val1");
    cout << a.Search("key1");

    // cache::FIFO a(5);

    // a.Insert("key1", "val1");
    // a.Insert("key2", "val1");
    // a.Insert("key3", "val1");
    // a.Insert("key4", "val1");
    // a.Insert("key5", "val1");
    // a.Insert("key6", "val6");

    // cout << (a.Search("key1").size() == 0) ? 1 : 0;

    // cache::LRU b(5);

    // b.Insert("key1", "val1");
    // b.Insert("key2", "val1");
    // b.Insert("key3", "val1");
    // b.Search("key1");
    // b.Insert("key4", "val1");
    // b.Insert("key5", "val1");
    // b.Insert("key6", "val6");

    // cout << (b.Search("key1").size() == 0) ? 1 : 0;

    
}