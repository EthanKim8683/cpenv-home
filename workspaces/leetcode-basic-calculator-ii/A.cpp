#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>

using namespace std;

#define int long long
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define eb emplace_back
#define pb push_back
#define vc vector
#define fs first
#define sd second
typedef pair<int, int> pii;
typedef vc<int> vi;

struct int2 {
  int x;
};

struct pratt_parser {
  using S = int2;

  vc<string> d;
  int i = 0;

  pratt_parser(vc<string> _d) : d(_d), i(0) {}

  string peek() { return i < sz(d) ? d[i] : ""; }
  string get() { return i < sz(d) ? d[i++] : ""; }

  int pre_bp(string op) { return -1; }

  int post_bp(string op) { return -1; }

  pair<int, int> in_bp(string op) {
    if (op == "+") {
      return {10, 11};
    } else if (op == "-") {
      return {10, 11};
    } else if (op == "*") {
      return {20, 21};
    } else if (op == "/") {
      return {20, 21};
    }
    return {-1, -1};
  }

  S pre_op(string op, S rhs) { return S{}; }

  S post_op(S lhs, string op) { return S{}; }

  S in_op(S lhs, string op, S rhs) {
    if (op == "+") {
      return {lhs.x + rhs.x};
    } else if (op == "-") {
      return {lhs.x - rhs.x};
    } else if (op == "*") {
      return {lhs.x * rhs.x};
    } else if (op == "/") {
      return {lhs.x / rhs.x};
    }
    return {0};
  }

  S atom(string t) { return {stoll(t)}; }

  S eval(int x = 0) {
    auto t = get();
    S rv;
    if (t == "(") {
      rv = eval(0), get();
    } else if (int r = pre_bp(t); r != -1) {
      rv = pre_op(t, eval(r));
    } else {
      rv = atom(t);
    }
    while (1) {
      auto op = peek();
      if (op == "") break;
      if (int l = post_bp(op); l != -1) {
        if (l < x) break;
        get(), rv = post_op(rv, op);
      } else if (auto [l, r] = in_bp(op); l != -1) {
        if (l < x) break;
        get(), rv = in_op(rv, op, eval(r));
      } else {
        break;
      }
    }
    return rv;
  }
};

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

class Solution {
 public:
  int calculate(string s) {
    vc<string> tokens;
    string number = "";
    for (int i = 0; i < sz(s); i++) {
      if (s[i] == ' ') {
        if (number != "") {
          tokens.pb(number);
          number = "";
        }
      } else if (isdigit(s[i])) {
        number += s[i];
      } else {
        if (number != "") {
          tokens.pb(number);
          number = "";
        }
        tokens.pb(s.substr(i, 1));
      }
    }
    if (number != "") {
      tokens.pb(number);
    }
    pratt_parser pp(tokens);
    return pp.eval().x;
  }
};

#ifdef U
signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  //

  string S;
  getline(cin, S);

  Solution *sol = new Solution();
  cout << sol->calculate(S) << '\n';
}
#endif
