### `grb::matrix_value_t`

```cpp
template <typename Matrix>
using matrix_value_t = std::ranges::range_value_t<Matrix>;
```

Obtain the value type of the matrix-like type `Matrix`.  Equal to `std::ranges::range_value_t<Matrix>`.

### `grb::vector_value_t`

```cpp
template <typename Vector>
using vector_value_t = std::ranges::range_value_t<Vector>;
```

Obtain the value type of the vector-like type `Vector`.  Equal to `std::ranges::range_value_t<Vector>`.

### `grb::matrix_scalar_t`

```cpp
template <typename Matrix>
using matrix_scalar_t = std::remove_cvref_t<typename std::tuple_element<1, matrix_value_t<Matrix>>::type>;
```

Obtain the type of scalar values stored in the matrix-like type `Matrix`.  Equal to the second element stored in the matrix's tuple-like value type.

### `grb::vector_scalar_t`

```cpp
template <typename Vector>
using vector_scalar_t = std::remove_cvref_t<typename std::tuple_element<1, vector_value_t<Vector>>::type>;
```

Obtain the type of scalar values stored in the vector-like type `Vector`.  Equal to the second element stored in the vector's tuple-like value type.

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

