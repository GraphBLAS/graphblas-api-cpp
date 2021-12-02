## `grb::min`

```cpp
template <typename T = void, typename U = T, typename V = void>
class min;
```

`grb::min` is a binary operator that returns the smaller of two arguments
using `operator<` for comparison.
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

#### grb::min::operator()

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

`grb::min` forms a monoid for any arithmetic type `T` with the identity value
`std::numeric_limits<T>::min()`.
The only exception is the partial specialization `grb::min<T, U, void>` when
`T` and `U` are not the same type.

### Specialization Details
#### `grb::min<void, void, void>`
```cpp
template <>
class min<void, void, void>;
```
Version of `grb::min` with both arguments and return types deduced.

#### grb::min::operator()

```cpp
template <typename T, typename U>
constexpr auto min(const T& lhs, const U& rhs)
  -> decltype(std::numeric_limits<U>::min() < std::numeric_limits<T>::min()
                ? std::declval<U>()
                : std::declval<T>());
```

#### `grb::min<T, U, void>`

```cpp
template <typename T = void, typename U = T>
class min<T, U, void>;
```

Version of `grb::min` with explicit types for the arguments, but return type deduced.

#### grb::min::operator()

```cpp
constexpr auto min(const T& lhs, const U& rhs)
  -> decltype(std::numeric_limits<U>::min() < std::numeric_limits<T>::min()
                ? std::declval<U>()
                : std::declval<T>());
```
