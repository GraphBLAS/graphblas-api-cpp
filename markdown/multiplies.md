## `grb::multiplies`

```cpp
template <typename T = void, typename U = T, typename V = void>
struct multiplies;
```

`grb::multiplies` is a binary operator.  It forms a monoid on arithmetic types.

### Specializations
Specialization | Description
----- | -----
`multiplies<void, void, void>` | deduces argument and return types
`multiplies<T, U, void>` | deduces return type based on `T` and `U`


### Template Parameters
`T` - Type of the left hand argument of the operator

`U` - Type of the right hand argument of the operator

`V` - Return type of the operator

### Methods
Method | Description
----- | -----
`operator()` | returns the product of the two arguments

#### `grb::multiplies::operator()`

```cpp
constexpr V operator()( const T& lhs, const U& rhs ) const;
```

Returns the product of `lhs` and `rhs`.

#### Parameters

`lhs`, `rhs` - values to multiply

#### Return Value

The result of `lhs * rhs`.

#### Exceptions

May throw exceptions if the underlying `operator*()` operation throws exceptions

#### Monoid Traits

`grb::multiplies` forms a monoid for arithmetic types with the identity value `1`.
The only exception is the partial specialization `grb::multiplies<T, U, void>` when
`T` and `U` are not the same type.

#### Specialization Details
##### `grb::multiplies<void, void, void>`
```cpp
template <>
struct multiplies<void, void, void>;
```
Version of `grb::multiplies` with both arguments and return types deduced.

##### `grb::multiplies::operator()`

```cpp
template <typename T, typename U>
constexpr auto operator()(T&& lhs, U&& rhs) const
  -> decltype(std::forward<T>(lhs) * std::forward<U>(rhs));
```

##### `grb::multiplies<T, U, void>`

```cpp
template <typename T = void, typename U = T>
struct multiplies<T, U, void>;
```

Version of `grb::multiplies` with explicit types for the arguments, but return type deduced.

##### `grb::multiplies::operator()`

```cpp
constexpr auto operator()(const T& lhs, const U& rhs) const
  -> decltype(lhs * rhs);
```
