# Utilities

## `grb::get`

```cpp
inline namespace /* unspecified */ {
  inline constexpr /* unspecified */ get = /* unspecified */;
}
```

```cpp
template <std::size_t I, typename T>
requires /* see below */
constexpr std::tuple_element<I, T> get(T&& tuple);
```

_TODO: we need someone who understands CPOs a little better to understand this._

Returns the `I'th` element stored in the tuple-like object `tuple`.

A call to `grb::get` is expression-equivalent to:

1) `tuple.get<I>()`, if that expression is valid.
2) Otherwise, `std::get<I>(tuple)`.

In all other cases, a call to `grb::get` is ill-formed.

## `grb::matrix_scalar_type_t`
_TODO: should re-write to simply use `matrix_traits` template struct._

```cpp
template <typename M>
using matrix_scalar_type_t = std::remove_cvref_t<typename M::scalar_type>;
```

Returns the type of stored scalar values in a GraphBLAS matrix or matrix range.

## `grb::matrix_index_type_t`

```cpp
template <typename M>
using matrix_index_type_t = std::remove_cvref_t<typename M::index_type>;
```

Return the type used to store indices in a GraphBLAS matrix or matrix range.

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
template <typename A, typename B, typename Reduce, typename Combine>
using multiply_result_t = /* undefined */;
```

The type of the matrix returned when multiply GraphBLAS matrix ranges of type `A` and `B` using the binary operators `Reduce` and `Combine`.


