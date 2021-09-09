#include <bits/stdc++.h>
using namespace std;

#include "lru_cache.hpp"

int main() {
    cache::LRU a(5);
    a.Insert("key1", "val1");
    cout << a.Search("key1");
}