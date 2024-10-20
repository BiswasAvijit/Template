// trie er i th node a jodi kono akta char c thake tahole oi ith node er suffix 
// link e geleo okhane char c thakbe eta akta property

#include<bits/stdc++.h>
using namespace std;

const int N = 1e2 + 9;
struct aho_corasick_static {
  int cnt[N], link[N], tot_node_cnt;
  map<char, int> next[N];

  void clear() {
    for(int i = 0; i < tot_node_cnt; i++)
      cnt[i] = 0, link[i] = -1, next[i].clear();

    tot_node_cnt = 1;
    link[0] = -1;
    cnt[0] = 0;
  }

  aho_corasick_static() {
    tot_node_cnt = N - 2;
    clear();
  }

  void add_word(string s) {
    int u = 0;
    for(char c : s) {
      if(!next[u].count(c)) next[u][c] = tot_node_cnt++;
      u = next[u][c];
      // cerr << c << ' ' << u << '\n';
    }

    cnt[u]++;
  }

  void push_links() {
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
        
        // ekane u er help niye v er jonno link ber kora hoyece akon link set korar somoi kono operation korar thakle ekane korte paro
        cnt[v] += cnt[link[v]];
        Q.push(v);
      }
    }
  }

  int get_count(string p) {
    int u = 0, ans = 0;
    for(char c : p) {
      while(u != -1 && !next[u].count(c)) u = link[u];
      if(u == -1) u = 0;
      else u = next[u][c];
      ans += cnt[u];
    }

    return ans;
  }
};

struct aho_corasick {
  vector<string> li[20];
  aho_corasick_static ac[20];

  void clear() {
    for(int i = 0; i < 20; i++) {
      li[i].clear();
      ac[i].clear();
    }
  }

  aho_corasick() {
    clear();
  }

  void add_word(string s) {
    int pos = 0;
    for(int l = 0; l < 20; l++)
      if(li[l].empty()) {
        pos = l;
        break;
      }

    li[pos].push_back(s);
    ac[pos].add_word(s);

    for(int bef = 0; bef < pos; bef++) {
      ac[bef].clear();
      for(string s2 : li[bef]) {
        li[pos].push_back(s2);
        ac[pos].add_word(s2);
      }

      li[bef].clear();
    }

    ac[pos].push_links();
  }
  //sum of occurrences of all patterns in this string
  int get_count(string s) {
    int ans = 0;
    for(int l = 0; l < 20; l++)
      ans += ac[l].get_count(s);

    return ans;
  }
};

string s[N];
aho_corasick_static aho;

int main() {
  int i, j, k, n, m;
  cin >> n;
  for(int i = 0; i < n; i++) cin >> s[i];
  // cout << "ashce\n";


  for(int i = 0; i < n; i++) {
    aho.add_word(s[i]);
  }
  
  // cout << aho.get_count("ff") << endl;
  aho.push_links();
  
  // for(int i = 1; i < aho.tot_node_cnt; i++){
  //   cout << aho.link[i] << '\n';
  // }
  
  for(auto it : aho.next[0]) {
    cout << it.first << ' ' << it.second << '\n';
  }


  // cout << aho.tot_node_cnt << '\n';

}