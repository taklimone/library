[![Build Status](https://travis-ci.com/taklimone/library.svg?branch=master)](https://travis-ci.com/taklimone/library)

# library

This is a header-only library of algorithms and data structures for competetive programming.

## Repository structure

### ``` include/ ```

C++ headers

* data_structure
  * [union_find](https://github.com/taklimone/library/blob/master/include/data_structure/union_find.hpp)
  * [weighted_union_find](https://github.com/taklimone/library/blob/master/include/data_structure/weighted_union_find.hpp)
  * [segtree](https://github.com/taklimone/library/blob/master/include/data_structure/segtree.hpp)
  * [lazy_segtree](https://github.com/taklimone/library/blob/master/include/data_structure/lazy_segtree.hpp)

* graph  
  * [bellman_ford](https://github.com/taklimone/library/blob/master/include/graph/bellman_ford.hpp)
  * [dijkstra](https://github.com/taklimone/library/blob/master/include/graph/dijkstra.hpp)
  * [floyd_warshall](https://github.com/taklimone/library/blob/master/include/graph/floyd_warshall.hpp)
  * [kruskal](https://github.com/taklimone/library/blob/master/include/graph/kruskal.hpp)
  * [prim](https://github.com/taklimone/library/blob/master/include/graph/prim.hpp)
  * [diameter](https://github.com/taklimone/library/blob/master/include/graph/diameter.hpp)

### ``` test/ ```

Test programs (as solutions to problems on Aizu Online Judge)

## ToDo

* C+14 -> C++17 (Now we can use C++17 at AtCoder!)
* More algorithms and data structures!
* Test diff only.
* Eliminate ```using namespace std``` and put all the classes and functions in namespace ```tklib```
