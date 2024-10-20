#include <bits/stdc++.h>
using namespace std;
//#define ll long long

const int inf = 1e9 + 7;
struct dsu {
  struct node {
    int rep, sz, mx, mn;
    node(int mx = 0, int mn = inf, int sz = 1) : mx(mx), mn(mn), sz(sz) {}
  };
  
  vector<node> parent;
  stack<tuple<int,int,int>> changes;
  int cmp;
  
  dsu(int _n) {
    parent.resize(_n + 5);
    cmp = _n;
    for(int i = 1; i <= _n; i++) {
      parent[i].rep = i;
      parent[i].sz = 1;
      // parent[i].mx = i;
      // parent[i].mn = i;
    }
  }

  int find_rep(int u) {
    if(parent[u].rep == u) return u;
    return parent[u].rep = find_rep(parent[u].rep);
  }

  void merge(int u, int v) {
    int a = find_rep(u);
    int b = find_rep(v);

    if(parent[a].sz < parent[b].sz) swap(a, b);
    if(a != b) {
      parent[b].rep = a;
      parent[a].sz += parent[b].sz;
      parent[a].mx = max(parent[a].mx, parent[b].mx);
      parent[a].mn = min(parent[a].mn, parent[b].mn);
      
      cmp--;
      // changes.push({b, a, parent[a].sz});
    }
  }

  void undo(int x) {
    while(x--) {
      auto [u, v, s] = changes.top();
      changes.pop();

      parent[u].rep = u;
      parent[v].sz -= s;
    }
  }

};


void solve() {
  int n = 5;
  
  dsu t(5);

  t.merge(1, 3);
  t.merge(4, 5);
  // undo(2);
  cout << (t.find_rep(4) == t.find_rep(5)) << '\n';

}

int32_t main() {
  ios_base::sync_with_stdio(false); cin.tie(nullptr); int t = 1;
  
  //cin >> t;

  for(int i = 1; i <= t; i++){
    solve();
  }
  return 0;
}
