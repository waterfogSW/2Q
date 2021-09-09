# 2Q - A low overhead high-performance buffer management replacement algorithm

## LRU
LRU는 Least Recently Used의 약자로 페이지 폴트가 발생하게 되면 가장 오래전에 접근했던 페이지를 퇴출시켜 공간을 확보합니다.

버퍼에 존재하는 페이지에 접근하는 경우 리스트의 head로 페이지를 이동시킵니다. 이러한 방식으로 최근에 접근한 페이지 일수록 head에 가깝게, 오래전에 접근한 페이지일수록 tail에 가까이 위치하게 됩니다. 새로운 페이지를 위한 공간이 필요할 경우 tail에 존재하는 페이지를 퇴출시킵니다. 

LRU는 주로 이중 연결리스트와 해시테이블을 통해 구현합니다. 구현이 간단하고, 알고리즘의 효율성 때문에 80년대 초반까지 대부분의 시스템에서 차용되었던 알고리즘입니다. 하지만, 이러한 장점들에도 불구하고 특정 상황에서 최악의 성능을 보입니다.

![img](https://user-images.githubusercontent.com/4745789/100534745-43ae8400-3238-11eb-8855-752a6ef2f3c6.png)

## Sub-Optimality during DB scans

데이터베이스 테이블이 LRU 캐시보다 큰 경우, 테이블을 스캔할 때 DB 프로세스는 전체 LRU 캐시를 삭제하고 스캔한 테이블의 페이지들로 채우게 됩니다. 이러한 페이지들이 다시 참조되지 않는다면 데이터 베이스의 성능을 크게 저하시킬 수 있습니다.

## 2Q
LRU의 이러한 단점을 보완하기 위해 2Q는 추가적인 대기열을 통해 실제로 Hot한 페이지가 LRU캐시에 위치할 수 있도록 합니다. 즉, 2Q는 접근 빈도 뿐만 아니라, 페이지의 Hot여부도 판단합니다.

## Simplified 2Q

![img](https://user-images.githubusercontent.com/4745789/100536835-41a0f100-3249-11eb-920b-0bcaff905906.png)

2Q 알고리즘은 기본 LRU버퍼 Am과 보조 FIFO버퍼 A1으로 구성됩니다. Page Fault가 발생하면 먼저 A1버퍼에 페이지를 push합니다. 이후 페이지가 다시 참조되면 LRU버퍼 Am으로 페이지를 push합니다. 이를통해 Am버퍼에 있는 페이지의 hot함을 보장할 수 있습니다. 

만약 A1버퍼의 page가 다시 참조되지 않으면 A1버퍼의 fifo정책에 따라 퇴출됩니다. 
이는 해당 페이지가 cold하며, 캐시될 필요가 없음을 암시합니다. 

```python
def access_page(X: page):
    # if the page already exists in the LRU cache
    # in buffer Am
    if X in Am:
         Am.move_front(X)

    # if the page exists in secondary storage
    # and not it gets access.
    # since the page is accessed again, indicating interest
    # and long-term need, move it to Am.
    elif X in A1:
         A1.remove(X)
         Am.add_front(X)

    # page X is accessed for the first time
    else:
         # if A1 is full then free a slot.
         if A1.is_full():
             A1.pop()

         # add X to the front of the FIFO A1 queue
         A1.add_front(X)
```

A1버퍼의 크기가 너무 작다면, hot의 기준이 너무 높아지게 되며, A1버퍼의 크기가 너무 커지게 되면 메모리의 한계로 인해 Am버퍼의 크기를 줄이게 되고 이는 데이터 베이스의 성능을 저하시킬 수 있습니다. 

## 2Q Full Version

![img](https://user-images.githubusercontent.com/4745789/100538168-0bb53a00-3254-11eb-8f69-ddcaf8d33a84.png)

일반적인 데이터베이스 접근 패턴에서 페이지는 짧은 시간동안 많은 참조를 받은 다음, 오랜시간 동안 참조되지 않습니다. 만약 캐시를 해야한다면, 짧은 시간의 많은 참조 이후에도 정기적으로 참조되는 페이지가 캐시되야 할 것입니다.

이러한 데이터 베이스 접근패턴에서 2Q를 활용하기 위해, 2Q Full Version은 보조 버퍼 A1을 A1-in, A1-out으로 나눕니다.

새로운 페이지는 항상 A1-in에 저장이 되고 페이지가 다시 참조될때까지 A1에 머무릅니다.
만약 페이지가 오래되어 퇴출되는 경우 메모리에서는 페이지가 삭제되지만, A1-out에 디스크 참조를 저장합니다. A1-out의 페이지가 다시 액세스 되는 경우 Am버퍼로 이동합니다.

## References

- [2Q Cache Management Algorithm - Arpit's Newsletter](https://arpitbhayani.me/blogs/2q-cache)
- [LRU - Wikipedia](https://en.wikipedia.org/wiki/Cache_replacement_policies#Least_recently_used_(LRU))
- [The Saga of the ARC Algorithm and Patent](http://www.varlena.com/GeneralBits/96.php)
- [2Q: A low overhead high-performance buffer management replacement algorithm](https://www.semanticscholar.org/paper/2Q%3A-A-Low-Overhead-High-Performance-Buffer-Johnson-Shasha/5fa357b43c8351a5d8e7124429e538ad7d687abc)