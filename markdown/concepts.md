# Concepts

## Binary Operator
Binary operators are function objects that are invocable with two arguments, returning a single value.
Binary operators can be callables defined by a GraphBLAS library, the C++ Standard Library, or application developers.
Binary operators may be callable with a variety of different types, or only with elements of a single type.
We say a binary operator is valid for a particular operation `T x U -> V` if it is callable with arguments of type `T` and `U`
and returns a value convertible to type `V`.

### Semantic Requirements
1) Callable of type `Fn` is callable with two arguments of type `T` and `U`.
2) The return value is convertible to type `V`.

#### C++20 Concept
```cpp
template <typename Fn, typename T, typename U, typename V>
concept BinaryOperator = requires(Fn fn, T t, U u) {
                           {fn(t, u)} -> std::convertible_to<V>;
                         };
```

## Monoid
*GraphBLAS monoids*, which are commutative monoids, referred to throughout the specification simply as monoids, are binary operators that have
special properties when applied to elements of some type `T`.  We say that a function object `Fn` forms on a monoid on type `T` if the
following semantic requirements are met.

### Semantic Requirements
1) Callable of type `Fn` fulfills the concept `BinaryOperator<T, T, T>` for some type `T`.
2) The operation is associative and commutative for type `T`.
3) The operation has an identity element for type `T`, accessible using `grb::monoid_traits<Fn, T>::identity()`.


#### C++20 Concept
```cpp
template <typename Fn, typename T>
concept Monoid = BinaryOperator<Fn, T, T, T> &&
                 requires { {grb::monoid_traits<Fn, T>::identity()} -> std::same_as<T>; };
```
