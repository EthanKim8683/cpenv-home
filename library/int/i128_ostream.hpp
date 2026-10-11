std::ostream &operator<<(std::ostream &out, __int128 n) {
  std::ostream::sentry s(out);
  if (s) {
    bool neg = false;
    if (n < 0) {
      n = -n;
      neg = true;
    }

    char buf[40], *ptr = std::end(buf);
    do {
      *--ptr = '0' + n % 10;
      n /= 10;
    } while (n != 0);
    if (neg) {
      *--ptr = '-';
    }

    int len = std::end(buf) - ptr;
    if (out.rdbuf()->sputn(ptr, len) != len) {
      out.setstate(std::ios_base::badbit);
    }
  }
  return out;
}
