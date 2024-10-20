#include <bits/stdc++.h>
using namespace std;
//#define ll long long

const int B = 20, N = 2e5 + 7;
int t[B][N], a[N];

void build(int n) {
  for(int i = 1; i <= n; i++) t[0][i] = a[i];
  for(int k = 1; k < B; k++){
    for(int i = 1; i + (1 << k) - 1 <= n; i++){
      t[k][i] = min(t[k - 1][i], t[k - 1][i + (1 << (k - 1))]);
    }
  }
}

int query(int l, int r) {
  int k = __lg(r - l + 1);
  return min(t[k][l], t[k][r - (1 << k) + 1]);
}

  build(n);
  
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
