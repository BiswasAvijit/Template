#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 6, inf = 1e9 + 7;
int a[N];

struct node {
  int x;
  // node(int mx1 = 0, int mx2 = 0, int f1 = 0, int f2 = 0, vector<int> v = vector<int>(5, 0), pair<int, int> p = {0, 0}) 
  //     : mx1(mx1), mx2(mx2), f1(f1), f2(f2), v(v), p(p) {}
  node(int x = 0) : x(x) {}
};

struct ST {
  vector<node> t;
  ST(int _n) {
    t.resize(4 * _n + 7);
  }

  node merge(node l, node r) {
    node x;
    x.x = max(l.x, r.x);
    return x;
  }

  void build(int n, int b, int e) {
    if (b == e) {
      t[n] = node(a[b]);
      return;
    }
    int mid = (b + e) >> 1, l = n << 1, r = l | 1;
    build(l, b, mid);
    build(r, mid + 1, e);
    t[n] = merge(t[l], t[r]);
  }

  void upd(int n, int b, int e, int i, int x) {
    if (b > i || e < i) return;
    if (b == e && b == i) {
      t[n] = node(0);
      return;
    }
    int mid = (b + e) >> 1, l = n << 1, r = l | 1;
    upd(l, b, mid, i, x);
    upd(r, mid + 1, e, i, x);
    t[n] = merge(t[l], t[r]);
  }

  node query(int n, int b, int e, int i, int j) {
    if (b > j || e < i) return node(0);
    if (b >= i && e <= j) return t[n];
    int mid = (b + e) >> 1, l = n << 1, r = l | 1;
    return merge(query(l, b, mid, i, j), query(r, mid + 1, e, i, j));
  }
};

void solve() {
  int n, q; 
  cin >> n >> q;
  for(int i = 1; i <= n; i++) {
    cin >> a[i];
  }

  ST t(n);
  t.build(1, 1, n);

  for(int i = 1; i <= q; i++) {
    int ty; 
    cin >> ty;
    if(ty == 1) {
      int idx, val; 
      cin >> idx >> val;
      t.upd(1, 1, n, idx, val);
    } 
    else {
      int l, r; 
      cin >> l >> r;
      node temp = t.query(1, 1, n, l, r);
      cout << temp.x << '\n';
    }
  }
}

int32_t main() {
  ios_base::sync_with_stdio(false); cin.tie(nullptr); int t = 1;
  
  //cin >> t;

  for(int i = 1; i <= t; i++){
    solve();
  }
  return 0;
}
