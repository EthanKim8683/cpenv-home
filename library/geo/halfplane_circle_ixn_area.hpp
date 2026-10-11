// Finds the area of the intersection between a half-plane and a circle
template <class T, std::enable_if_t<std::is_floating_point_v<T>> * = nullptr>
T halfplane_circle_ixn_area(const vec2<T> &r0, const vec2<T> &v,
                            const vec2<T> &c, T r) {
  T w = std::clamp(comp(c - r0, perp(v)), -r, r);
  //   \int_{-r}^w 2\sqrt{r^2-x^2} \,dx
  // = w\sqrt{r^2-w^2} + r^2\arcsin(\frac{w}{r}) + \frac{\pi r^2}{2}
  return w * std::sqrt(r * r - w * w) + r * r * std::asin(w / r) +
         PI * r * r / 2;
}
