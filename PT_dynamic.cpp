#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 35 + 5;
int pref[N], suf[N], dp[N];

string s;
struct PT {
  struct node {
    int nxt[26], len, link, pos;
    node() {
      fill(nxt, nxt + 26, 0);
      len = 0;
      link = 0;
      pos = 0;
    }
  };
  vector<node> t;
  int sz, last;

  PT() {
    t.clear();
    t.resize(3);
    sz = 2, last = 2;
    t[1].len = -1, t[1].link = 1;
    t[2].len = 0, t[2].link = 1;
  }

  void reset() {
    t.clear();
    t.resize(3);
    sz = 2, last = 2;
    t[1].len = -1, t[1].link = 1;
    t[2].len = 0, t[2].link = 1;
  }

  void create_node() {
    t.emplace_back();
  }

  int insert(int pos, int st = 0) {
    int cur = last, curlen = 0;
    int ch = s[pos] - 'a';
    while (1) {
      curlen = t[cur].len;
      if (pos - 1 - curlen >= st && s[pos - 1 - curlen] == s[pos]) break;
      cur = t[cur].link;
    }
    if (t[cur].nxt[ch]) {
      last = t[cur].nxt[ch];
      return 0;
    }

    create_node();
    sz++;
    last = sz;
    t[sz].len = t[cur].len + 2;

    t[cur].nxt[ch] = sz;
    t[sz].pos = pos;

    if (t[sz].len == 1) {
      t[sz].link = 2;
    }
    while (true && !(t[sz].len == 1)) {
      cur = t[cur].link;
      curlen = t[cur].len;
      if (pos - 1 - curlen >= st && s[pos - 1 - curlen] == s[pos]) {
        t[sz].link = t[cur].nxt[ch];
        break;
      }
    }
    dp[sz] = dp[t[sz].link] + 1;

    return 1;
  }
};


void solve() {
  cin >> s;
  int n = s.size();
  PT T;

  for(int i = 0; i < n; i++){
    T.insert(i);
    pref[i] = dp[T.last];
    // cout << pref[i] << " \n"[i == n - 1];

    // cout << pref[i] << " \n"[i == n - 1];
  }

  reverse(s.begin(), s.end());
  T.reset();

  for(int i = 0; i < n; i++){
    T.insert(i);
    if(i) {
      suf[i] = suf[i - 1] + dp[T.last];
    }
    else {
      suf[i] = dp[T.last];
    }
    // cout << suf[i] << " \n"[i == n - 1];

  }

  reverse(suf, suf + n);

  ll ans = 0;
  for(int i = 0; i < n; i++){
    ans += 1ll * pref[i] * suf[i + 1];
    // cout << suf[i] << " \n"[i == n - 1];
  }

  cout << ans << '\n';

}


int32_t main() {
  ios_base::sync_with_stdio(false); cin.tie(nullptr); int t = 1;
  
  //cin >> t;

  for(int i = 1; i <= t; i++){
    solve();
  }
  return 0;
}
