#include <bits/stdc++.h>
using namespace std;

#include "lru_cache.hpp"
#include "fifo_cache.hpp"
#include "two_q_cache.hpp"

int main() {
    cache::TWO_Q a(10,10);

    a.Insert("key1", "val1");
    a.Insert("key1", "val1");
    a.Insert("key1", "val1");
    cout << a.getHit();

    // cache::FIFO b(10);

    // b.Insert("key1", "val1");
    // b.Insert("key1", "val1");

    // cout << b.getHit();
    
}