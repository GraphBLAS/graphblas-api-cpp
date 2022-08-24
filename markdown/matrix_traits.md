## `grb::matrix_traits`

```cpp
template <typename Matrix>
struct matrix_traits;
```

The `matrix_traits` template struct can be used to retrieve traits about a matrix-like
object.  It provides information such as the type of scalar values stored in the matrix,
the type used to store indices in the matrix, and the type of a matrix entry.


### `grb::matrix_value_t`

```cpp
template <typename Matrix>
using matrix_value_t = std::ranges::range_value_t<Matrix>;
```

Obtain the value type of the matrix-like type `Matrix`.  Equal to `std::ranges::range_value_t<Matrix>`.

### `grb::matrix_scalar_t`

```cpp
template <typename Matrix>
using matrix_scalar_t = std::remove_cvref_t<typename std::tuple_element<1, matrix_value_t<Matrix>>::type>;
```

Obtain the type of scalar values stored in the matrix-like type `Matrix`.  Equal to the second element stored in the matrix's tuple-like value type.

### `grb::matrix_key_t`

```cpp
template <typename Matrix>
using matrix_key_t = std::remove_cvref_t<typename std::tuple_element<0, matrix_value_t<Matrix>>::type>;
```

Obtain the key type of the matrix.  This is a tuple-like type used to store each scalar value's row and column indices.

### `grb::matrix_index_t`

```cpp
template <typename Matrix>
using matrix_index_t = std::remove_cvref_t<typename std::tuple_element<0, matrix_key_t<Matrix>>::type>;
```

Obtain the integer-like type used to store matrix indices.
