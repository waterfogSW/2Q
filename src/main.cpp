#include <bits/stdc++.h>
using namespace std;

#include "lru_cache.hpp"
#include "fifo_cache.hpp"

int main() {
    cache::FIFO f(5);
    f.Insert("k1","a");
    f.Insert("k2","a");
    f.Insert("k3","a");
    f.Insert("k4","a");
    f.Insert("k5","a");
    f.Insert("k6","a");
    cout << f.Search("k1");
}