## `grb::divides`

```cpp
template <typename T = void, typename U = T, typename V = void>
struct divides;
```

`grb::divides` is a binary operator that divides two values.

### Specializations
Specialization | Description
----- | -----
`divides<void, void, void>` | deduces argument and return types
`divides<T, U, void>` | deduces return type based on `T` and `U`


### Template Parameters
`T` - Type of the left hand argument of the operator

`U` - Type of the right hand argument of the operator

`V` - Return type of the operator

### Methods
Method | Description
----- | -----
`operator()` | returns the difference of the two arguments

#### `grb::divides::operator()`

```cpp
constexpr V operator()( const T& lhs, const U& rhs ) const;
```

Returns the difference of `lhs` and `rhs`.

#### Parameters

`lhs`, `rhs` - values to divide

#### Return Value

The result of `lhs / rhs`.

#### Exceptions

May throw exceptions if the underlying `operator/()` operation throws exceptions

#### Monoid Traits

`grb::divides` does not form a monoid for arithmetic types.

### Specialization Details
#### `grb::divides<void, void, void>`
```cpp
template <>
struct divides<void, void, void>;
```
Version of `grb::divides` with both arguments and return types deduced.

#### `grb::divides::operator()`

```cpp
template <typename T, typename U>
constexpr auto operator()(T&& lhs, U&& rhs) const
  -> decltype(std::forward<T>(lhs) / std::forward<U>(rhs));
```

#### `grb::divides<T, U, void>`

```cpp
template <typename T = void, typename U = T>
struct divides<T, U, void>;
```

Version of `grb::divides` with explicit types for the arguments, but return type deduced.

##### grb::divides::operator()

```cpp
constexpr auto operator()(const T& lhs, const U& rhs) const
  -> decltype(lhs / rhs);
```
