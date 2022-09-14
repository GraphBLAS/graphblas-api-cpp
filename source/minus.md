## `grb::minus`

```cpp
template <typename T = void, typename U = T, typename V = void>
struct minus;
```

`grb::minus` is a binary operator that subtracts two values.

### Specializations
Specialization | Description
----- | -----
`minus<void, void, void>` | deduces argument and return types
`minus<T, U, void>` | deduces return type based on `T` and `U`


### Template Parameters
`T` - Type of the left hand argument of the operator

`U` - Type of the right hand argument of the operator

`V` - Return type of the operator

### Methods
Method | Description
----- | -----
`operator()` | returns the difference of the two arguments

#### `grb::minus::operator()`

```cpp
constexpr V operator()( const T& lhs, const U& rhs ) const;
```

Returns the difference of `lhs` and `rhs`.

#### Parameters

`lhs`, `rhs` - values to subtract

#### Return Value

The result of `lhs - rhs`.

#### Exceptions

May throw exceptions if the underlying `operator-()` operation throws exceptions

#### Monoid Traits

`grb::minus` does not form a monoid for arithmetic types.

### Specialization Details
#### `grb::minus<void, void, void>`
```cpp
template <>
struct minus<void, void, void>;
```
Version of `grb::minus` with both arguments and return types deduced.

#### `grb::minus::operator()`

```cpp
template <typename T, typename U>
constexpr auto operator()(T&& lhs, U&& rhs) const
  -> decltype(std::forward<T>(lhs) - std::forward<U>(rhs));
```

#### `grb::minus<T, U, void>`

```cpp
template <typename T = void, typename U = T>
struct minus<T, U, void>;
```

Version of `grb::minus` with explicit types for the arguments, but return type deduced.

#### `grb::minus::operator()`

```cpp
constexpr auto operator()(const T& lhs, const U& rhs) const
  -> decltype(lhs - rhs);
```
