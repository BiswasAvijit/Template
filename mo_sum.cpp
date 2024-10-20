#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 100, M = 100, qq = 100;
const int k = 2;
int cnt[M];
int a[N];
struct query {
  int l, r, id;
}Q[N];

int l = 1, r = 0, ans[N];
int sum = 0;

void add(int i) {
  sum += a[i];
}
void remove(int i) {
  sum -= a[i];
}

void solve() {
  int n; cin >> n;
  int q; cin >> q;

  for(int i = 1; i <= n; i++){
    cin >> a[i];
  }

  // query Q[N];

  for(int i = 1; i <= q; i++){
    int l, r; cin >> l >> r;
    Q[i] = {l, r, i};
  }

  // sort(Q + 1, Q + q + 1, [&](query a, query b) {
  //   if(a.l / k == b.l == k) return a.r < b.r;
  //   return a.l < b.l;
  // });
  sort(Q + 1, Q + q + 1, [&](query i, query j) {
    int block_a = i.l / k;
    int block_b = j.l / k;
    if(block_b == block_a) return i.r < j.r;
    return block_a < block_b;
  });


  for(int i = 1; i <= q; i++){
    while(l < Q[i].l) remove(l++);
    while(Q[i].l < l) add(--l);
    while(Q[i].r < r) remove(r--);
    while(r < Q[i].r) add(++r);
    ans[Q[i].id] = sum;
  }


  for(int i = 1; i <= q; i++){
    cout << ans[i] << '\n';
  }

}

int32_t main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);int t = 1;
    
    #ifndef ONLINE_JUDGE
    freopen("output.txt", "w", stderr);
    #endif

    // cin >> t;

    for(int i = 1; i <= t; i++){
    //cout << "-----Case:" << i << "-----\n";
        solve();
    }

    return 0;
}
