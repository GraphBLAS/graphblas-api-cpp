# Concepts

## Binary Operator
Binary operators are function objects that are invocable with two arguments, returning a single value.
Binary operators can be callables defined by a GraphBLAS library, the C++ Standard Library, or application developers.
Binary operators may be callable with a variety of different types, or only with elements of a single type.
We say a binary operator is valid for a particular operation `T x U -> V` if it is callable with arguments of type `T` and `U`
and returns a value convertible to type `V`.

### Semantic Requirements
1) Callable of type `Fn` can be invoked with two arguments of type `T` and `U`.
2) The return value is convertible to type `V`.

#### C++20 Concept
```cpp
template <typename Fn, typename T, typename U, typename V>
concept BinaryOperator = requires(Fn fn, T t, U u) {
                           {fn(t, u)} -> std::convertible_to<V>;
                         };
```

## Monoid
*GraphBLAS monoids* are commutative monoids. Throughout this specification, they are referred to simply as monoids.  They are binary operators that have
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

## Matrix Range
A matrix in GraphBLAS consists of a range of values distributed over a two-dimensional domain. In addition to [`grb::matrix`](#grb::matrix), which directly stores a collection of values, there are other types, such as views, that fulfill the same interface.  We say that a type `M` is a matrix range if the
following semantic requirements are met.

### Semantic Requirements
1) `M` has a scalar type of the stored values, accessible with `grb::matrix_scalar_type_t<M>`
2) `M` has an index type used to reference the indices of the stored values, accessible with `grb::matrix_index_type_t<M>`.
3) `M` has a shape, which is a tuple-like object of size two, holding the number of rows and the number of columns, accessible by invoking the method `shape()` on an object of type `M`.
4) `M` is a range with a value type that represents a matrix tuple, containing both the index and scalar value for each stored value.
5) `M` has a `find()` method that takes an index tuple and returns an iterator.

#### C++20 Concept

_TODO: this is a bit sketchy, and needs to have some of the components fleshed out._
```cpp
template <typename Matrix>
concept MatrixRange = std::ranges::sized_range<Matrix> &&
  requires(Matrix matrix) {
    typename grb::matrix_scalar_type_t<Matrix>;
    typename grb::matrix_index_type_t<Matrix>;
    {matrix.shape()} -> Tuplelike<grb::matrix_index_type_t<Matrix>,
                                  grb::matrix_index_type_t<Matrix>>;
    {std::declval<typename std::ranges::range_value_t<std::remove_cvref_t<Matrix>>>()}
      -> MatrixValueType<grb::matrix_scalar_type_t<Matrix>,
                         grb::matrix_index_type_t<Matrix>>;
  };
```



