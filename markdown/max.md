## `grb::max`

```cpp
template <typename T = void, typename U = T, typename V = void>
struct max;
```

`grb::max` is a binary operator that returns the larger of two arguments.
When both input arguments have integral types, `std::cmp_less` is used for comparison.  When one or both arguments have non-integral types, `operator<` is used for comparison.
It forms a monoid on arithmetic types.

### Specializations
Specialization | Description
----- | -----
`max<void, void, void>` | deduces argument and return types
`max<T, U, void>` | deduces return type based on `T` and `U`


### Template Parameters
`T` - Type of the left hand argument of the operator

`U` - Type of the right hand argument of the operator

`V` - Return type of the operator

### Methods
Method | Description
----- | -----
`operator()` | returns the larger of two arguments

#### `grb::max::operator()`

```cpp
constexpr V operator()( const T& lhs, const U& rhs ) const;
```

Returns the larger of `lhs` and `rhs`.

#### Parameters

`lhs`, `rhs` - values to take the max of

#### Return Value

The larger of `lhs` and `rhs`.

#### Exceptions

May throw exceptions if the underlying `operator<()` operation throws exceptions

#### Monoid Traits

`grb::max` forms a monoid for any arithmetic type `T` with the identity value
`std::min(std::numeric_limits<T>::lowest(), -std::numeric_limits<T>::infinity())`.
The only exception is the partial specialization `grb::max<T, U, void>` when
`T` and `U` are not the same type.

### Specialization Details
#### `grb::max<void, void, void>`
```cpp
template <>
struct max<void, void, void>;
```
Version of `grb::max` with both arguments and return types deduced.

#### `grb::max::operator()`

```cpp
template <std::integral T, std::integral U>
constexpr auto operator()(const T& a, const U& b) const
  -> std::conditional_t<
      std::cmp_less(std::numeric_limits<T>::max(),
                    std::numeric_limits<U>::max()),
      U, T
     >;

template <typename T, typename U>
constexpr auto operator()(const T& a, const U& b) const
  -> std::conditional_t<
      std::numeric_limits<T>::max() < std::numeric_limits<U>::max(),
      U, T
     >
requires(!(std::is_integral_v<T> && std::is_integral_v<U>));
```

#### `grb::max<T, U, void>`

```cpp
template <typename T = void, typename U = T>
struct max<T, U, void>;
```

Version of `grb::max` with explicit types for the arguments, but return type deduced.

#### `grb::max::operator()`

```cpp
constexpr auto operator()(const T& a, const U& b) const
  -> std::conditional_t<
      std::cmp_less(std::numeric_limits<T>::max(),
                    std::numeric_limits<U>::max()),
      U, T
     >;

constexpr auto operator()(const T& a, const U& b) const
  -> std::conditional_t<
      std::numeric_limits<T>::max() < std::numeric_limits<U>::max(),
      U, T
     >
requires(!(std::is_integral_v<T> && std::is_integral_v<U>));
```
