array<int, 3> ee(int a, int b) {
  int x = 1, y = 0, z = 0, w = 1;
  while (b) {
    int q = a / b;
    x -= q * z, swap(x, z);
    y -= q * w, swap(y, w);
    a -= q * b, swap(a, b);
  }
  return {x, y, a};
}
