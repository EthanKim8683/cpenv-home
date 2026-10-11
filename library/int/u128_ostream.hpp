// https://stackoverflow.com/a/25115163/19662543
std::ostream &operator<<(std::ostream &out, unsigned __int128 n) {
  std::ostream::sentry s(out);
  if (s) {
    char buf[39], *ptr = std::end(buf);
    do {
      *--ptr = '0' + n % 10;
      n /= 10;
    } while (n != 0);

    int len = std::end(buf) - ptr;
    if (out.rdbuf()->sputn(ptr, len) != len) {
      out.setstate(std::ios_base::badbit);
    }
  }
  return out;
}
