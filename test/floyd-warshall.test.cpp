#define PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_C

#include "../Graph/floyd-warshall.cpp"

#include <iostream>
#include <vector>
using namespace std;

int main() {
    int V, E;
    cin >> V >> E;
    vector<vector<int>> dist(V, vector<int>(V, numeric_limits<int>::max()));
    for(int i=0; i<V; ++i) dist[i][i] = 0;

    for(int i=0; i<E; ++i) {
        int s,t,d;
        cin >> s >> t >> d;
        dist[s][t] = d;
    }

    floyd_warshall<int>(dist);
    for(int i=0; i<V; ++i) {
        if(dist[i][i] < 0) {
            cout << "NEGATIVE CYCLE" << endl;
            return 0;
        }
    }

    for(int i=0; i<V; ++i) {
        for(int j=0; j<V; ++j) {
            if(dist[i][j] == numeric_limits<int>::max()) cout << "INF";
            else cout << dist[i][j];
            cout << (j+1==V ? '\n' : ' ');
        }
    }
}