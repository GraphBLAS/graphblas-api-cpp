## `grb::plus`

```cpp
template <typename T = void, typename U = T, typename V = void>
class plus;
```

`grb::plus` is a binary operator.

## Specializations
Specialization | Description
----- | -----
`plus<void, void, void>` | deduces argument and return types
`plus<T, U, void>` | deduces return type based on `T` and `U`


## Template Parameters
`T` - Type of the left hand argument of the operator

`U` - Type of the right hand argument of the operator

`V` - Return type of the operator

## Methods
Method | Description
----- | -----
`operator()` | returns the sum of the two arguments

### grb::plus::operator()

```cpp
constexpr V operator()( const T& lhs, const U& rhs ) const;
```

Returns the sum of `lhs` and `rhs`.

### Parameters

`lhs`, `rhs` - values to sum

### Return Value

The result of `lhs + rhs`.

### Exceptions

May throw exceptions if the underlying `operator+()` operation throws exceptions

### Specialization Details
#### `grb::plus<void, void, void>`
```cpp
template <>
class plus<void, void, void>;
```
Version of `grb::plus` with argument and return types deduced.

#### grb::plus::operator()

```cpp
template <typename T, typename U>
constexpr auto operator()(T&& lhs, U&& rhs) const
  -> decltype(std::forward<T>(lhs) + std::forward<U>(rhs));
```

#### `grb::plus<T, U, void>`

```cpp
template <typename T = void, typename U = T>
class plus<T, U, void>;
```

Version of `grb::plus` with return type deduced.

#### grb::plus::operator()

```cpp
constexpr auto operator()(const T& lhs, const U& rhs) const
  -> decltype(std::forward<T>(lhs) + std::forward<U>(rhs));
```
