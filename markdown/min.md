## `grb::min`

```cpp
template <typename T = void, typename U = T, typename V = void>
struct min;
```

`grb::min` is a binary operator that returns the smaller of two arguments.
using `operator<` for comparison.
When both input arguments have integral types, `std::cmp_less` is used for comparison.  When one or both arguments have non-integral types, `operator<` is used for comparison.
It forms a monoid on arithmetic types.

### Specializations
Specialization | Description
----- | -----
`min<void, void, void>` | deduces argument and return types
`min<T, U, void>` | deduces return type based on `T` and `U`


### Template Parameters
`T` - Type of the left hand argument of the operator

`U` - Type of the right hand argument of the operator

`V` - Return type of the operator

### Methods
Method | Description
----- | -----
`operator()` | returns the smaller of two arguments

#### `grb::min::operator()`

```cpp
constexpr V operator()( const T& lhs, const U& rhs ) const;
```

Returns the smaller of `lhs` and `rhs`.

#### Parameters

`lhs`, `rhs` - values to take the min of

#### Return Value

The smaller of `lhs` and `rhs`.

#### Exceptions

May throw exceptions if the underlying `operator<()` operation throws exceptions

#### Monoid Traits

`grb::min` forms a monoid on any arithmetic type `A` with the identity value
`std::max(std::numeric_limits<A>::max(), std::numeric_limits<A>::infinity())`,
as long as `T`, `U`, and `V` are equal to void or `A`.

### Specialization Details
#### `grb::min<void, void, void>`
```cpp
template <>
struct min<void, void, void>;
```
Version of `grb::min` with both arguments and return types deduced.

#### `grb::min::operator()`

```cpp
template <std::integral T, std::integral U>
constexpr auto operator()(const T& a, const U& b) const
  -> std::conditional_t<
       std::cmp_less(std::numeric_limits<U>::lowest(),
                     std::numeric_limits<T>::lowest()),
       U, T
     >;

template <typename T, typename U>
constexpr auto operator()(const T& a, const U& b) const
  -> std::conditional_t<
       std::numeric_limits<U>::lowest() < std::numeric_limits<T>::lowest(),
       U, T
     >
requires(!(std::is_integral_v<T> && std::is_integral_v<U>));
```

#### `grb::min<T, U, void>`

```cpp
template <typename T = void, typename U = T>
struct min<T, U, void>;
```

Version of `grb::min` with explicit types for the arguments, but return type deduced.

#### `grb::min::operator()`

```cpp
constexpr auto operator()(const T& a, const U& b) const
  -> std::conditional_t<
       std::cmp_less(std::numeric_limits<U>::lowest(),
                     std::numeric_limits<T>::lowest()),
       U, T
     >;

constexpr auto operator()(const T& a, const U& b) const
  -> std::conditional_t<
       std::numeric_limits<U>::lowest() < std::numeric_limits<T>::lowest(),
       U, T
     >
requires(!(std::is_integral_v<T> && std::is_integral_v<U>));
```
