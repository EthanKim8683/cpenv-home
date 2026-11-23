// general discrete log
int mod_log(int a, int b, int m) {
  if (b % m == 1 % m) return 0;
  int n = sqrt(m) + 1, e = 1, f, j = 1, i = 2;
  unordered_map<int, int> A;
  while (j <= n && (e = f = e * a % m) != b % m) A[e * b % m] = j++;
  if (e == b % m) return j;
  if (gcd(m, e) == gcd(m, b))
    for (; i <= n + 2; ++i)
      if (A.count(e = e * f % m)) return n * i - A[e];
  return -1;
}
