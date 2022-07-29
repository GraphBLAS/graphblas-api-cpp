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
template <typename Fn, typename T, typename U = T, typename V = grb::any>
concept BinaryOperator = requires(Fn fn, T t, U u) {
                           {fn(t, u)} -> std::convertible_to<V>;
                         };
```

### Remarks
The last two arguments are defaulted unless explicit template parameters are provided.  The second
parameter to the concept, `U`, which is the right-hand side input to the binary operator, defaults to
`T`.  The final parameter, `V`, which represents the output of the binary operator, defaults to
`grb::any`, meaning that the return value may have any type.

### Example

```cpp
// Constrain `Fn` to require a binary operator that accepts two integers
// as arguments and returns a value of any type.
template <BinaryOperator<int> Fn>
auto apply(Fn&& fn, int a, int b) {
  return fn(a, b);
}

// The following code will result in an error, since the function passed
// does not fulfill the BinaryOperator<int> requirement, as it cannot accept
// integers.
void test() {
  auto fn = [](std::string a, std::string b) { return a.size() + b.size(); };
  apply(fn, 12, 13);
}
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

## Tuple-Like Type
Tuple-like types are types that, similar to instantiations of `std::tuple` or `std::pair`, store multiple values.  The number of values stored in the tuple-like type, as well as the type of each value, are known at compile time.  We say that a type `T` is tuple-like if it fulfills the following semantic requirements.

### Semantic Requirements
1) The tuple `T` has a size accessible using template `std::tuple_size`.
2) The type of each stored value in the tuple `T` is accessible using `std::tuple_element`.
3) Each stored value in `T` is accessible using either the method `get()` or `std::get()`.

#### C++20 Concept
```cpp
// TODO
```

## Matrix Range
A matrix in GraphBLAS consists of a range of values distributed over a two-dimensional domain. In addition to [`grb::matrix`](#grb::matrix), which directly stores a collection of values, there are other types, such as views, that fulfill the same interface.  We say that a type `M` is a matrix range if the following semantic requirements are met.

### Semantic Requirements
1) `M` has a scalar type of the stored values, accessible with `grb::matrix_scalar_type_t<M>`
2) `M` has an index type used to reference the indices of the stored values, accessible with `grb::matrix_index_type_t<M>`.
3) `M` has a shape, which is a tuple-like object of size two, holding the number of rows and the number of columns, accessible by invoking the method `shape()` on an object of type `M`.
4) `M` is a range with a value type that represents a matrix tuple, containing both the index and scalar value for each stored value.
5) `M` has a method `find()` that takes an index tuple and returns an iterator.

#### C++20 Concept

_TODO: this is a bit sketchy, and needs to have some of the components fleshed out._
```cpp
template <typename M>
concept MatrixRange = std::ranges::sized_range<M> &&
  requires(M matrix) {
    typename grb::matrix_scalar_type_t<M>;
    typename grb::matrix_index_type_t<M>;
    {matrix.shape()} -> Tuplelike<grb::matrix_index_type_t<M>,
                                  grb::matrix_index_type_t<M>>;
    {std::declval<typename std::ranges::range_value_t<std::remove_cvref_t<M>>>()}
      -> MatrixValueType<grb::matrix_scalar_type_t<M>,
                         grb::matrix_index_type_t<M>>;
  };
```
## Mutable Matrix Range
Some matrices and matrix-like objects are *mutable*, meaning that their stored values may be modified.  Examples of mutable matrix ranges include instantiations of `grb::matrix` and certain matrix views that allow adding new values and modifying old values, such as `grb::transpose`.  We say that a type `M` is a mutable matrix range for the scalar value `T` if the following semantic requirements are met.

### Semantic Requirements
1) `M` is a matrix range.
2) `M` is an output range for type `T`.
3) `M` has a method `insert()` that takes a matrix entry tuple and attempts to insert the element into the matrix, returning an iterator to the new element on success and returning an iterator to the end on failure.

#### C++20 Concept

_TODO: this is also a bit sketchy, and furthermore depends on the matrix range concept above._

```cpp
template <typename M, typename T>
concept MutableMatrixRange = MatrixRange<M> &&
                             std::ranges::output_range<M, T> &&
  requires(M matrix, T value) {
    matrix.insert({{grb::matrix_index_type_t<M>{}, grb::matrix_index_type_t<M>{}},
                   value}) -> std::ranges::iterator_t<M>;
  }
```
## Mask Matrix Range
Some operations require masks, which can be used to avoid computing and storing certain parts of the output.  We say that a type `M` is a mask matrix range if the following semantic requirements are met.

### Semantic Requirements
1) `M` is a matrix range.
2) The scalar value type of `M` is convertible to `bool`.

#### C++20 Concept

```cpp
template <typename T>
concept MaskMatrixRange = MatrixRange<M> &&
                          std::is_convertible_v<grb::matrix_scalar_type_t<M>, bool>;
```




