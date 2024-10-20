#include <bits/stdc++.h>
using namespace std;
//#define ll long long

struct AC {
  int N;
  vector <int> link, isend;
  vector<map<char,int>> next;
  
  AC(): N(0) {node();}
  int node() {
    next.emplace_back();
    link.emplace_back(0);
    isend.emplace_back(0);
    
    link[N] = -1;
    
    
    return psz++;
  }

  void add(string s, int i) {
    int u = 0;
    for(char c : s) {
      if(!next[u].count(c)) next[u][c] = node();
      u = next[u][c];
      // cout << c << ' ' << u << '\n';
    }

    isend[u] = i;
  }

  void push() {
    queue<int> Q;
    int u, v, j;
    char c;

    Q.push(0);
    link[0] = -1;

    while(!Q.empty()) {
      u = Q.front();
      Q.pop();

      for(auto it : next[u]) {
        v = it.second;
        c = it.first;
        j = link[u];

        while(j != -1 && !next[j].count(c)) j = link[j];
        if(j != -1) link[v] = next[j][c];
        else link[v] = 0;
        Q.push(v);
      }
    }
  }
  int advance (int u, char c) {
    while(u != -1 && !next[u].count(c)) u = link[u];
    if(u == -1) u = 0;
    else u = next[u][c];
    return u;
  }
};


void solve() {


}


int32_t main() {
  ios_base::sync_with_stdio(false); cin.tie(nullptr); int t = 1;
  
  //cin >> t;

  for(int i = 1; i <= t; i++){
    solve();
  }
  return 0;
}
