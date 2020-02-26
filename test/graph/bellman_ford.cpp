#define PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_B

#include "graph/bellman_ford.hpp"

#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

int main() {
    int V, E, r;
    cin >> V >> E >> r;
    vector<tuple<int, int, int>> edgelist(E);
    for(int i=0; i<E; ++i) {
        int s, t, d;
        cin >> s >> t >> d;
        edgelist[i] = {s, t, d};
    }

    auto dist = tklib::bellmanFord(V, edgelist, r);
    if(dist.size() == 0) {
        cout << "NEGATIVE CYCLE" << endl;
    } else {
        for(int i=0; i<V; ++i) {
            int d = dist[i];
            if(d == numeric_limits<int>::max()) cout << "INF" << endl;
            else cout << d << endl;
        }
    }
}