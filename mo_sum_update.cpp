#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 100, M = 100, qq = 100;
const int k = 2700;
int last[N];
int a[N];
struct query {
  int l, r, t, id;
}Q[N];

struct update {
  int x, pre, now;
}U[N];


int l = 1, r = 0, ans[N];
int sum = 0;

void add(int i) {
  sum += a[i];
}
void remove(int i) {
  sum -= a[i];
}

void apply(int i, int y) {
  if(l <= i and i <= r) {
    remove(i);
    a[i] = y;
    add(i);
  }
  else {
    a[i] = y;
  }
}

bool cmp(query &a, query &b) {
  int l1 = a.l / k, l2 = b.l / k,
    r1 = a.r / k, r2 = b.r / k;
  // Left blocks differ, they aren't in same group,
  // first comes who have smaller left block.
  if(l1 != l2) return l1 < l2;  
  // So here we have same Left Block, but if Right Blocks aren't equal,
  // then who have right block smaller comes first.
  if(r1 != r2) return r1 < r2;
  // Now we have l1 == l2 and r1 == r2,
  // So both a and b query is in same group,
  // sort them based on time.
  return a.t < b.t;
}

void solve() {
  int n; cin >> n;
  int q; cin >> q;

  for(int i = 1; i <= n; i++){
    cin >> a[i];
  }

  for(int i = 1; i <= n; i++){
    last[i] = a[i];
  }

  int update_id = 0, queryer_update_id = 0;


  for(int i = 1; i <= q; i++){
    int type; cin >> type;
    if(type == 1) {
      //query
      int l, r; cin >> l >> r;
      Q[i] = {l, r, update_id, ++queryer_update_id};

    }
    else {
      // update
      int x, y; cin >> x >> y; // Ax ke y koro

      U[++update_id] = {x, last[x], y};
      last[x] = y;
    }
  }

  // sort(Q + 1, Q + q + 1, [&](query a, query b) {
  //   if(a.l / k == b.l == k) return a.r < b.r;
  //   return a.l < b.l;
  // });
  // sort(Q + 1, Q + q + 1, [&](query i, query j) {
  //   int block_a = i.l / k;
  //   int block_b = j.l / k;
  //   if(block_b == block_a) return i.r < j.r;
  //   return block_a < block_b;
  // });
  sort(Q + 1, Q + q + 1, cmp);



  int t = 0;

  for(int i = 1; i <= q; i++){
    while(t < Q[i].t) t++, apply(U[t].x, U[t].now); // Forward Update
    while(t > Q[i].t) apply(U[t].x, U[t].pre), t--; // Reverse Update


    while(l < Q[i].l) remove(l++);
    while(Q[i].l < l) add(--l);
    while(Q[i].r < r) remove(r--);
    while(r < Q[i].r) add(++r);
    ans[Q[i].id] = sum;
  }


  for(int i = 1; i <= queryer_update_id; i++){
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
