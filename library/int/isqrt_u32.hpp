// https://stackoverflow.com/a/70550680/19662543
constexpr unsigned short isqrt(unsigned n) {
  return isqrt((unsigned long long) n);
}
