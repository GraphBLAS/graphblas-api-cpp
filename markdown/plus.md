## `grb::plus`

```cpp
template <typename T = void, typename U = T, typename V = void>
struct plus;
```

`grb::plus` is a binary operator.  It forms a monoid on arithmetic types.

### Specializations
Specialization | Description
----- | -----
`plus<void, void, void>` | deduces argument and return types
`plus<T, U, void>` | deduces return type based on `T` and `U`


### Template Parameters
`T` - Type of the left hand argument of the operator

`U` - Type of the right hand argument of the operator

`V` - Return type of the operator

### Methods
Method | Description
----- | -----
`operator()` | returns the sum of the two arguments

#### `grb::plus::operator()` 
```cpp
constexpr V operator()( const T& lhs, const U& rhs ) const;
```

Returns the sum of `lhs` and `rhs`.

#### Parameters

`lhs`, `rhs` - values to sum

#### Return Value

The result of `lhs + rhs`.

#### Exceptions

May throw exceptions if the underlying `operator+()` operation throws exceptions

#### Monoid Traits

`grb::plus` forms a monoid on any arithmetic type `A` with the identity value `0`,
as long as `T`, `U`, and `V` are equal to void or `A`.

### Specialization Details
#### `grb::plus<void, void, void>`
```cpp
template <>
struct plus<void, void, void>;
```
Version of `grb::plus` with both arguments and return types deduced.

#### `grb::plus::operator()`

```cpp
template <typename T, typename U>
constexpr auto operator()(T&& lhs, U&& rhs) const
  -> decltype(std::forward<T>(lhs) + std::forward<U>(rhs));
```

#### `grb::plus<T, U, void>`

```cpp
template <typename T = void, typename U = T>
struct plus<T, U, void>;
```

Version of `grb::plus` with explicit types for the arguments, but return type deduced.

#### `grb::plus::operator()`

```cpp
constexpr auto operator()(const T& lhs, const U& rhs) const
  -> decltype(lhs + rhs);
```
