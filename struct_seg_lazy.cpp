#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int N = 2e5 + 6, inf = 1e9 + 7;
int a[N];

struct node {
  ll x;
  // node(int mx1 = 0, int mx2 = 0, int f1 = 0, int f2 = 0, vector<int> v = vector<int>(5, 0), pair<int, int> p = {0, 0}) 
  //     : mx1(mx1), mx2(mx2), f1(f1), f2(f2), v(v), p(p) {}
  node(ll x = 0) : x(x) {}
};


struct ST {
  vector<node> t;
  vector<node> lazy;
  ST(int _n) {
    t.resize(4 * _n + 7);
    lazy.resize(4 * _n + 7);
  }


  node merge(node l, node r) {
    node ans = {l.x + r.x};
    return ans;
  }

  void push(int n, int b, int e) {
    if(lazy[n].x == 0) return;
    t[n].x += 1ll * lazy[n].x * (e - b + 1);
    if(b != e) {
      int mid = (b + e) >> 1, l = n << 1, r = l | 1;
      lazy[l].x += lazy[n].x;
      lazy[r].x += lazy[n].x;
    }
    lazy[n].x = 0;
  }
  void build(int n, int b, int e) {
    if(b == e) {
      lazy[n].x = 0;
      t[n].x = a[b];
      return;
    }
    int mid = (b + e) >> 1, l = n << 1, r = l | 1;
    build(l, b, mid);
    build(r, mid + 1, e);
    t[n] = merge(t[l], t[r]);
  }
  void upd(int n, int b, int e, int i, int j, int x) {
    push(n, b, e);
    if(e < i or j < b) return;
    if(i <= b and e <= j) {
      lazy[n].x = x;
      push(n, b, e);
      return;
    }

    int mid = (b + e) >> 1, l = n << 1, r = l | 1;
    upd(l, b, mid, i, j, x);
    upd(r, mid + 1, e, i, j, x);
    t[n] = merge(t[l], t[r]);

  }

  node query(int n, int b, int e, int i, int j) {
    push(n, b, e);
    if(e < i or j < b) return node{0};
    if(i <= b and e <= j) return t[n];
    int mid = (b + e) >> 1, l = n << 1, r = l | 1;
    return  merge(query(l, b, mid, i, j), query(r, mid + 1, e, i, j));
  }
};

  ST t(n);
  t.build(1, 1, n);


void solve() {
  int n; cin >> n;
  int q; cin >> q;
  for(int i = 1; i <= n; i++){
    cin >> a[i];
  }
  
  ST t(n);
  t.build(1, 1, n);
  
  for(int i = 1; i <= q; i++){
    int ty; cin >> ty;
    if(ty == 1) {
      int l, r, x; cin >> l >> r >> x;
      t.upd(1, 1, n, l, r, x);
    }
    else {
      int id; cin >> id;
      cout << t.query(1, 1, n, id, id).x << '\n';
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
