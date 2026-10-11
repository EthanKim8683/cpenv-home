tuple<int, int, int> ee(int a, int b) {
  int x = 1, x2 = 0, y = 0, y2 = 1;
  while (b) {
    int q = a / b;
    tie(x, x2) = pii{x2, x - q * x2};
    tie(y, y2) = pii{y2, y - q * y2};
    tie(a, b) = pii{b, a - q * b};
  }
  return a;
}
