# Type Traits

## `grb::monoid_traits`

```cpp
template <typename Fn, typename T>
struct monoid_traits;
```

The `monoid_traits` template struct provides information about the monoid that
is formed by the commutative binary operator `Fn` on the type `T`.  Namely,
it provides a way to retrieve the monoid's identity.

Users can specialize `monoid_traits` for custom operators, which will make their
identity elements available to GraphBLAS algorithms, possibly enabling optimizations.
The default specialization of `monoid_traits` detects and provides the identity
of the monoid if it has an `identity` method.

## Template Parameters
`Fn` - type of commutative binary operator

`T` - type on which `Fn` forms a commutative monoid

### Member Types
Member Type | Definition | Description
----- | ----- | -----
`type` | `T` | type of the monoid

The default specialization has the following member functions:

### Member Functions
Function | Description
----- | ----- | -----
`identity` | the identity value of the monoid

### `grb::monoid_traits<Fn, T>::identity`

```cpp
static constexpr T identity() noexcept;
```

Returns the identity of the monoid.

#### Parameters
None

#### Complexity
Constant

#### Exceptions
May not throw exceptions

#### Possible Implementation

```cpp
template <typename Fn, typename T>
static constexpr T grb::monoid_traits<Fn, T>::identity() noexcept {
  if constexpr(requires { {Fn::identity() } -> std::same_as<T> }) {
    return Fn::identity();
  } else if constexpr(requires { {Fn:: template identity<T>()} -> std::same_as<T> }) {
    return Fn:: template identity<T>();
  }
}
```

### Specializations

```cpp
template <std::arithmetic T>
struct grb::monoid_traits<std::plus<T>, T>;

template <std::arithmetic T>
struct grb::monoid_traits<std::plus<void>, T>;
```

```cpp
template <std::arithmetic T>
struct grb::monoid_traits<std::multiplies<T>, T>;

template <std::arithmetic T>
struct grb::monoid_traits<std::multiplies<void>, T>;
```
