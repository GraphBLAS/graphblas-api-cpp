# Utilities

## `grb::get`

```cpp
inline namespace /* unspecified */ {
  inline constexpr /* unspecified */ get = /* unspecified */;
}
```

```cpp
template <std::size_t I, typename T>
requires /* see below */
constexpr std::tuple_element<I, T> get(T&& tuple);
```

_TODO: we need someone who understands CPOs a little better to understand this._

Returns the `I'th` element stored in the tuple-like object `tuple`.

A call to `grb::get` is expression-equivalent to:

1) `tuple.get<I>()`, if that expression is valid.
2) Otherwise, `std::get<I>(tuple)`.

In all other cases, a call to `grb::get` is ill-formed.
