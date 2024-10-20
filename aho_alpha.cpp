#include<bits/stdc++.h>
using namespace std;
const int N = 105 + 9;
//credit: Alpha_Q


struct AC {
  int total_node, P;
  const int B = 128;
  vector<vector<int>> next;
  vector<int> link;

  AC() : total_node(0), P(1) {
    node();
  }

  void reset() {
    total_node = 0;
    P = 1;
    next.clear();
    ni.clear();
    link.clear();
    node();
  }

  int node() {
    next.emplace_back(B, 0);
    link.emplace_back(0);
    ni.emplace_back(0);
    return total_node++;
  }

  inline int get(char c) {
    return c - 'a'; //changed
  }

  int add(const string &T) {
    int u = 0;
    for (auto c : T) {
      if (!next[u][get(c)]) next[u][get(c)] = node();
      u = next[u][get(c)];
    }
    return P++;
  }

  void push() {
    queue<int> q;
    for (q.push(0); !q.empty();) {
      int u = q.front();
      q.pop();
      for (int c = 0; c < B; ++c) {
        int v = next[u][c];
        if (!v) next[u][c] = next[link[u]][c]; // leaf node
        else {
          link[v] = u ? next[link[u]][c] : 0;
          q.push(v);
          for (int x : ni[link[v]]) {
            ni[v].push_back(x);
          }
        }
      }
    }
  }

  int advance(int u, char c) {
    while (u && !next[u][get(c)]) u = link[u];
    u = next[u][get(c)];
    return u;
  }
};



void solve() {
  AC aho;

}


int32_t main() {
  ios_base::sync_with_stdio(false); cin.tie(nullptr); int t = 1;
  
  //cin >> t;

  for(int i = 1; i <= t; i++){
    solve();
  }
  return 0;
}
