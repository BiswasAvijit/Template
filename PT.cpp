#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 3e5 + 5;
int pref[N], suf[N], dp[N];


struct PT {
  struct node {
    int nxt[26], len, link, occ;
  };
  string s;
  vector<node> t;
  int sz, last;
  PT() {}
  PT(string _s) {
    s = _s;
    int n = s.size();
    t.clear();
    t.resize(n + 9);
    sz = 2, last = 2;
    t[1].len = -1, t[1].link = 1;
    t[2].len = 0, t[2].link = 1;
  }
  int insert(int pos) {
    int cur = last, curlen = 0;
    int ch = s[pos] - 'a';
    while (1) {
      curlen = t[cur].len;
      if (pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == s[pos]) break;
      cur = t[cur].link;
    }
    if (t[cur].nxt[ch]) {
      last = t[cur].nxt[ch];
      return 0;
    }

    // notun palindrome pawa mane uporer gula abar pabo

    sz++;
    last = sz;
    t[sz].len = t[cur].len + 2;
    t[cur].nxt[ch] = sz;

    t[last].occ = 1;

    if (t[sz].len == 1) {
      t[sz].link = 2;
    }
    while (true and !(t[sz].len == 1)) {
      cur = t[cur].link;
      curlen = t[cur].len;
      if (pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == s[pos]) {
        t[sz].link = t[cur].nxt[ch];
        break;
      }
    }

    dp[sz] = dp[t[sz].link] + 1;

    return 1;
  }
}T;


void solve() {
  string s; cin >> s;
  int n = s.size();
  T = PT(s);

  for(int i = 0; i < n; i++){
    T.insert(i);
    pref[i] = dp[T.last];
    // cout << pref[i] << " \n"[i == n - 1];
  }

  reverse(s.begin(), s.end());
  T = PT(s);

  for(int i = 0; i < n; i++){
    T.insert(i);
    if(i) {
      suf[i] = suf[i - 1] + dp[T.last];
    }
    else {
      suf[i] = dp[T.last];
    }
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
    ios_base::sync_with_stdio(false); cin.tie(nullptr);int t = 1;

    // cin >> t;

    for(int i = 1; i <= t; i++){
    //cout << "-----Case:" << i << "-----\n";
        solve();
    }

    return 0;
}
