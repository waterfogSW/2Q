#include <bits/stdc++.h>
using namespace std;

#include "lru_cache.hpp"
#include "fifo_cache.hpp"
#include "two_q_cache.hpp"

int main() {
    cache::TWO_Q a(5);

    a.Insert("key1","val1");
    a.Search("key1");
}