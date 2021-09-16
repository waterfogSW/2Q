#include <bits/stdc++.h>
using namespace std;

#include "fifo_cache.hpp"
#include "lru_cache.hpp"
#include "lfu_cache.hpp"
#include "two_q_cache.hpp"

int main(int argc, char const *argv[]) {
    /* 
    1 : workload path
    2 : max cache size
    3 : a1 size = max cache size * ratio
    */

    string fpath = argv[1];
    size_t csize = atoi(argv[2]);
    size_t a1_size_ratio = atoi(argv[3]);

    size_t a1_size = csize * (0.01 * a1_size_ratio);
    size_t am_size = csize - a1_size;

    cout << "a1_size : " << a1_size << '\n';
    cout << "am_size : " << am_size << '\n';

    cache::FIFO fifo_cache(csize);
    cache::LRU lru_cache(csize);
    cache::LFU lfu_cache(csize);
    cache::TWO_Q twoQ_cache(am_size, a1_size);

    ifstream wfile(fpath.data());
    if(wfile.is_open()) {
		string line;
		while(getline(wfile, line)) {
			string gline = line.substr(0, line.size()-1); 
			fifo_cache.Insert(gline, "A");
            lru_cache.Insert(gline, "A");
            lfu_cache.Insert(gline, "A");
            twoQ_cache.Insert(gline, "A");
		}
		wfile.close();
	}

	cout << "FIFO  : Hit: " << fifo_cache.getHit() << '\n';
	cout << "LRU   : Hit: " << lru_cache.getHit() << '\n';
    cout << "LFU   : Hit: " << lfu_cache.getHit() << '\n';
    cout << "TWO Q : Hit: " << twoQ_cache.getHit() << '\n';

    return 0;
}
