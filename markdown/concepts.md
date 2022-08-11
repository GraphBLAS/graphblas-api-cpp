# Concepts

## Binary Operator
Binary operators are function objects that are invocable with two arguments, returning a single value.
Binary operators can be callables defined by a GraphBLAS library, the C++ Standard Library, or application developers.
Binary operators may be callable with a variety of different types, or only with elements of a single type.
We say a binary operator is valid for a particular operation `T x U -> V` if it is callable with arguments of type `T` and `U`
and returns a value convertible to type `V`.

### Requirements
1) Callable of type `Fn` can be invoked with two arguments of type `T` and `U`.
2) The return value is convertible to type `V`.

#### Concept
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
following requirements are met.

### Requirements
1) Callable of type `Fn` fulfills the concept `BinaryOperator<T, T, T>` for some type `T`.
2) The operation is associative and commutative for type `T`.
3) The operation has an identity element for type `T`, accessible using `grb::monoid_traits<Fn, T>::identity()`.


#### Concept
```cpp
template <typename Fn, typename T>
concept Monoid = BinaryOperator<Fn, T, T, T> &&
                 requires { {grb::monoid_traits<Fn, T>::identity()} -> std::same_as<T>; };
```

## Tuple-Like Type
Tuple-like types are types that, similar to instantiations of `std::tuple` or `std::pair`, store multiple values.  The number of values stored in the tuple-like type, as well as the type of each value, are known at compile time.  We say that a type `T` is tuple-like for the parameter pack of types `Types` if it fulfills the following requirements.

### Requirements
1) The tuple `T` has a size accessible using template `std::tuple_size` whose type is equal to `std::size_t` and whose value is equal to `sizeof...(Types)`.
2) The type of each stored value in the tuple `T` is accessible using `std::tuple_element`, with the N'th stored value equal to the N'th type in `Types`.
3) Each stored value in `T` is accessible using the customization point object `grb::get`, which will invoke either the method `get()` if it is present in the tuple type `T` or `std::get()`.  The type of the return value for the N'th element must be convertible to the N'th element of `Types`.

#### Concept
_TODO: This works fine, but is perhaps a bit sketchy._
```cpp
template <typename T, std::size_t I, typename U = grb::any>
concept TupleElementGettable = requires(T tuple) {
                                 {grb::get<I>(tuple)} -> std::convertible_to<U>;
                               };
template <typename T, typename... Args>
concept TupleLike =
  requires {
    typename std::tuple_size<std::remove_cvref_t<T>>::type;
    requires std::same_as<std::remove_cvref_t<decltype(std::tuple_size_v<std::remove_cvref_t<T>>)>, std::size_t>;
  } &&
  sizeof...(Args) == std::tuple_size_v<std::remove_cvref_t<T>> &&
  []<std::size_t... I>(std::index_sequence<I...>) {
    return (TupleElementGettable<T, I, Args> && ...);
  }(std::make_index_sequence<std::tuple_size_v<std::remove_cvref_t<T>>>());
```

### Example

```cpp
// The Concept `TupleLike<int, int, float>` constraints `T`
// to be a tuple-like type storing int, int, float.
template<TupleLike<int, int, float> T>
void print_tuple(T&& tuple) {
  auto&& [i, j, v] = tuple;
  printf("%d, %d, %f\n", i, j, v);
}
```

## Matrix Entry
Matrix entries represent entries in a GraphBLAS matrix, which include both a tuple-like index storing the row and column index of the stored scalar value, as well as the scalar value itself.  We say that a type `Entry` is a valid matrix entry for the scalar type `T` and index type `I` if the following requirements are met.

### Requirements
1) `Entry` is a tuple-like type with a size of 2.
2) The first element stored in the tuple-like type `Entry` is a tuple-like type fulfilling `TupleLike<I, I>`, storing the row and column index of the matrix entry.
3) The second element stored in the tuple-like type `Entry` holds the matrix entry's scalar value, and is convertible to `T`.

#### Concept
_TODO: review this concept._

```cpp
template <typename Entry, typename T, typename I>
concept MatrixEntry = TupleLike<Entry, grb::any, grb::any> &&
                      requires(Entry entry) { {grb::get<0>(entry)} -> TupleLike<I, I>; } &&
                      requires(Entry entry) { {grb::get<1>(entry)} -> std::convertible_to<T>; };
```

## Mutable Matrix Entry
A mutable matrix entry is an entry in a matrix that fulfills all the requirements of matrix entry, but whose 
stored scalar value can be mutated by assigning to a value of type `U`.  We say that a matrix entry `Entry` is a mutable matrix entry for scalar type `T`, index type `I`, and output type `U`, if it fulfills all the requirements of matrix entry as well as the following requirements.

### Requirements
1) The second element of the tuple `Entry`, representing the scalar value, is indirectly writable to elements of type `U`.

#### Concept
_TODO: review this concept._

```cpp
template <typename Entry, typename T, typename I, typename U>
concept MutableMatrixEntry = MatrixEntry<Entry, T, I> &&
                             std::indirectly_writable<decltype(std::get<1>(std::declval<Entry>())), U>;
```

## Matrix Range
A matrix in GraphBLAS consists of a range of values distributed over a two-dimensional domain. In addition to [`grb::matrix`](#grb::matrix), which directly stores a collection of values, there are other types, such as views, that fulfill the same interface.  We say that a type `M` is a matrix range if the following requirements are met.

### Requirements
1) `M` has a scalar type of the stored values, accessible with `grb::matrix_scalar_type_t<M>`
2) `M` has an index type used to reference the indices of the stored values, accessible with `grb::matrix_index_type_t<M>`.
3) `M` is a range with a value type that represents a matrix tuple, containing both the index and scalar value for each stored value.
4) `M` has a shape, which is a tuple-like object of size two, holding the number of rows and the number of columns, accessible by invoking the method `shape()` on an object of type `M`.
5) `M` has a method `find()` that takes an index tuple and returns an iterator.

#### Concept

_TODO: this is a bit sketchy, and needs to have some of the components fleshed out._
```cpp
template <typename M>
concept MatrixRange = std::ranges::sized_range<M> &&
  requires(M matrix) {
    typename grb::matrix_scalar_type_t<M>;
    typename grb::matrix_index_type_t<M>;
    {std::declval<std::ranges::range_value_t<std::remove_cvref_t<M>>>()}
      -> MatrixEntry<grb::matrix_scalar_type_t<M>,
                     grb::matrix_index_type_t<M>>;
    {grb::shape(matrix)} -> Tuplelike<grb::matrix_index_type_t<M>,
                                  grb::matrix_index_type_t<M>>;
    {grb::find(matrix, {grb::matrix_index_type_t<M>{}, grb::matrix_index_type_t<M>{}})}
                 -> std::convertible_to<std::ranges::iterator_t<M>>;
  };
```
## Mutable Matrix Range
Some matrices and matrix-like objects are *mutable*, meaning that their stored values may be modified.  Examples of mutable matrix ranges include instantiations of `grb::matrix` and certain matrix views that allow adding new values and modifying old values, such as `grb::transpose`.  We say that a type `M` is a mutable matrix range for the scalar value `T` if the following requirements are met.

### Requirements
1) `M` is a matrix range.
2) The value type of `M` fulfills the requirements of `MutableMatrixEntry<T, I>`.
3) `M` has a method `insert()` that takes a matrix entry tuple and attempts to insert the element into the matrix, returning an iterator to the new element on success and returning an iterator to the end on failure.

#### Concept

_TODO: this is also a bit sketchy, and furthermore depends on the matrix range concept above._

```cpp
template <typename M, typename T>
concept MutableMatrixRange = MatrixRange<M> &&
                             MutableMatrixEntry<std::ranges::range_value_t<M>
                                                grb::matrix_scalar_type_t<M>,
                                                grb::matrix_index_type_t<M>,
                                                T> &&
  requires(M matrix, T value) {
    {grb::insert(matrix, {{grb::matrix_index_type_t<M>{}, grb::matrix_index_type_t<M>{}},
                          value}) -> std::ranges::iterator_t<M>;
    }
  }
```
## Mask Matrix Range
Some operations require masks, which can be used to avoid computing and storing certain parts of the output.  We say that a type `M` is a mask matrix range if the following requirements are met.

### Requirements
1) `M` is a matrix range.
2) The scalar value type of `M` is convertible to `bool`.

#### Concept

```cpp
template <typename M>
concept MaskMatrixRange = MatrixRange<M> &&
                          std::is_convertible_v<grb::matrix_scalar_type_t<M>, bool>;
```

## Vector Entry
Vector entries represent entries in a GraphBLAS vector, which include both an `std::integral` index storing the index of the stored scalar value, as well as the scalar value itself.  We say that a type `Entry` is a valid matrix entry for the scalar type `T` and index type `I` if the following requirements are met.

### Requirements
1) `Entry` is a tuple-like type with a size of 2.
2) The first element stored in the tuple-like type `Entry` fulfills `std::integral`.
3) The second element stored in the tuple-like type `Entry` holds the vector's scalar value, and is convertible to `T`.

#### Concept
_TODO: review this concept._

```cpp
template <typename Entry, typename T, typename I>
concept VectorEntry = TupleLike<Entry, grb::any, grb::any> &&
                      requires(Entry entry) { {grb::get<0>(entry)} -> std::integral; } &&
                      requires(Entry entry) { {grb::get<1>(entry)} -> std::convertible_to<T>; };
```

## Vector Range
A vector in GraphBLAS consists of a range of values distributed over a one-dimensional domain. In addition to [`grb::vector`](#grb::vector), which directly stores a collection of values, there are other types, such as views, that fulfill the same interface.  We say that a type `V` is a vector range if the following requirements are met.

_TODO: make requirements list find CPO, not method._

### Requirements
1) `V` has a scalar type of the stored values, accessible with `grb::vector_scalar_type_t<V>`
2) `V` has an index type used to reference the indices of the stored values, accessible with `grb::vector_index_type_t<V>`.
3) `V` is a range with a value type that represents a vector tuple, containing both the index and scalar value for each stored value.
4) `V` has a shape, which is an integer-like object, holding the dimension of the vector, accessible by invoking the method `shape()` on an object of type `V`.
5) `V` has a method `find()` that takes an index and returns an iterator.

#### Concept

_TODO: this is a bit sketchy, and needs to have some of the components fleshed out._
```cpp
template <typename M>
concept VectorRange = std::ranges::sized_range<V> &&
  requires(V vector) {
    typename grb::vector_scalar_type_t<V>;
    typename grb::vector_index_type_t<V>;
    {std::declval<std::ranges::range_value_t<std::remove_cvref_t<V>>>()}
      -> VectorEntry<grb::vector_scalar_type_t<V>,
                     grb::vector_index_type_t<V>>;
    {grb::shape(vector)} -> std::same_as<grb::vector_index_type_t<V>>;
    {grb::find(vector, grb::vector_index_type_t<V>)} -> std::convertible_to<std::ranges::iterator_t<V>>;
  };
```
