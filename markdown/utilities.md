# Utilities

_TODO: need "disablers" for all these CPOs. Also, "converted to its decayed type?"_

## `grb::get`

```cpp
inline constexpr /* unspecified */ get = /* unspecified */;
```

#### Call Signature
```cpp
template <std::size_t I, typename T>
requires /* see below */
constexpr std::tuple_element<I, T> get(T&& tuple);
```

_TODO: we need someone who understands CPOs a little better to understand this._

Returns the `I'th` element stored in the tuple-like object `tuple`.

A call to `grb::get` is expression-equivalent to:

1) `tuple.get<I>()`, if that expression is valid.
2) Otherwise, any calls to `get(tuple)` found through argument-dependent lookup.
3) Otherwise, `std::get<I>(tuple)`.

In all other cases, a call to `grb::get` is ill-formed.

## `grb::size`

```cpp
template <typename T>
inline constexpr /* unspecified */ size = std::ranges::size;
```

#### Call Signature
```cpp
template <typename T>
constexpr auto size(T&& t);
```

Returns the number of stored values in a GraphBLAS matrix, vector, or other range.
Whenever `grb::size(e)` is valid for an expression `e`, the return type is integer-like.

A call to `grb::size(t)` is expression-equivalent to:

1) `t.size()`, if that expression is valid.
2) Otherwise, any calls to `size(t)`, found through argument-dependent lookup.

In all other cases, a call to `grb::size` is ill-formed.

## `grb::shape`

```cpp
template <typename T>
inline constexpr /* unspecified */ shape = /* unspecified */;
```

#### Call Signature
```cpp
template <typename T>
requires /* see below */
constexpr auto shape(T&& t);
```

Returns the shape of a GraphBLAS object.  If `T` fulfills the requirements of `MatrixRange`, then the return type will be a tuple-like type storing two integer-like values, fulfilling the requirements of `TupleLike<I, I>`, where `I` is the index type of `T`.  If `T` fulfills the requirements of `VectorRange`, then the return type will be `I`, where `I` is the index type of `T`.

A call to `grb::shape` is expression-equivalent to:

1) `t.shape()` if that expression is valid.
2) Otherwise, `shape(t)`, if that expression is valid, including any declarations of `shape` found through argument-dependent lookup.

In all other cases, a call to `grb::shape` is ill-formed.

## `grb::find`

```cpp
template <typename T>
inline constexpr /* unspecified */ find = /* unspecified */;
```

#### Call Signature
```cpp
template <typename R, typename T>
requires /* see below */
constexpr auto find(R&& r, T&& t);
```

Return an iterator to the stored value in the GraphBLAS matrix or vector `r` at index location `t`.

A call to `grb::find` is expression-equivalent to:

1) `r.find(t)` if that expression is valid.
2) Otherwise, any calls to `find(r, t)` found through argument-dependent lookup.
2) Otherwise, any calls to `std::find(r, t)`, if that expression is valid.

In all other cases, a call to `grb::find` is ill-formed.

## `grb::insert`

```cpp
template <typename T>
inline constexpr /* unspecified */ insert = /* unspecified */;
```

#### Call Signature
```cpp
template <typename R, typename T>
requires /* see below */
constexpr auto insert(R&& r, T&& t);
```

Attempt to insert the value `t` into the GraphBLAS matrix or vector `r`.

A call to `grb::insert` is expression-equivalent to:

1) `r.insert(t)` if that expression is valid.
2) Otherwise, any calls to `insert(r, t)` found through argument-dependent lookup.

## `scalar_result_type_t`

```cpp
template <typename A, typename B, typename Combine>
using scalar_result_type_t = std::declval<Combine>()(
                                std::declval<scalar_type_t<A>>(),
                                std::declval<scalar_type_t<B>>());
```

The type of the scalar elements produced by combining GraphBLAS objects of type `A` and `B` elementwise using a binary operator of type `Combine`.

## `multiply_result_t`

```cpp
template <typename A, typename B, typename Reduce, typename Combine, typename Mask>
using multiply_result_t = /* undefined */;
```

The type returned when multiply is called on GraphBLAS matrix or vector ranges of type `A` and `B` using binary operators `Reduce` and `Combine` with mask `Mask`.

The scalar type of the returned matrix will be `combine_result_t<A, B, Combine>`, and the index type will be `grb::container_index_t<A>` or `grb::container_index_t<B>`, whichever is able to store the larger value.

## `combine_result_t`

```cpp
template <typename A, typename B, typename Combine>
using combine_result_t = std::invoke_result_t<Combine, A, B>;
```

The type returned when the binary operator `Combine` is called with an element of the scalar type of `A` as the first argument and an element of the scalar type of `B` as the second argument.  `A` and `B` must be GraphBLAS matrix or vector objects.

## `ewise_union_result_t`

```cpp
template <typename A, typename B, typename Combine, typename Mask>
using ewise_union_result_t = /* undefined */;
```

The type returned when `ewise_union` is called on the GraphBLAS matrix or vector ranges of type `A` and `B` using the binary operator `Combine`.

## `ewise_intersection_result_t`

```cpp
template <typename A, typename B, typename Combine, typename Mask>
using ewise_intersection_result_t = /* undefined */;
```

The type returned when `ewise_intersection` is called on the GraphBLAS matrix or vector ranges of type `A` and `B` using the binary operator `Combine`.