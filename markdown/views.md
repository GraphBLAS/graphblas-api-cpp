# Views

## grb::transpose

```cpp
template <MatrixRange M>
grb::transpose_view<M> transpose(M&& matrix);
```

### Parameters

`matrix` - a GraphBLAS matrix or matrix view

#### Type Requirements

- `M` must meet the requirements of `MatrixRange`

### Return Value
_TODO: Discuss issues with allowing transpose view in output_
Returns a matrix view that is equal to the transpose of `matrix`, satisfying `MatrixRange`.
If `M` meets the requirements of `MutableMatrixRange`, then the return value will also meet the
requirements of `MutableMatrixRange`.

If the value returned by `transpose` outlives the lifetime of `matrix`, then the behavior is undefined.

## grb::transform

```cpp
template <MatrixRange M, typename Fn>
grb::transform_view<M, Fn> transform(M&& matrix, Fn&& fn);    (1)

template <VectorRange V, typename Fn>
grb::transform_view<V, Fn> transform(V&& vector, Fn&& fn);    (2)
```

(1) `fn` must accept an argument of type `std::ranges::range_value_t<M>` and return a value of some type.  The return type of `fn` will be the scalar type of the transform view.

(2) `fn` must accept an argument of type `std::ranges::range_value_t<V>` and return a value of some type.  The return type of `fn` will be the scalar type of the transform view.

### Parameters

`matrix` - a GraphBLAS matrix or matrix view satisfying `MatrixRange`

`vector` - a GraphBLAS vector or vector view satisfying `VectorRange`

`fn` - function used to transform matrix values element-wise

#### Type Requirements

- `M` must meet the requirements of `MatrixRange`

- `V` must meet the requirements of `VectorRange`

### Return Value

(1) Returns a view of the matrix `matrix` in which every stored scalar value has been transformed using the function `fn`.

(2) Returns a view of the vector `vector` in which every stored scalar value has been transformed using the function `fn`.

### Example

```cpp
#include <grb/grb.hpp>

int main(int argc, char** argv) {
  grb::matrix<float> a({10, 10});

  a[{1, 2}] = 12.0f;
  a[{3, 4}] = 123.2f;
  a[{7, 8}] = 8.0f;;

  grb::print(a, "original matrix");

  // Transform each scalar value based on its
  // row and column index.
  auto idx_view = grb::transform(a, [](auto&& entry) {
  	                                  auto&& [idx, v] = entry;
  	                                  auto&& [i, j] = idx;
  	                                  return i + j;
  	                                });

  grb::print(idx_view, "index transformed view");

  return 0;
}
```

## grb::structure
```cpp
template <MatrixRange M>
grb::structure_view<M> structure(M&& matrix);                 (1) 

template <VectorRange V>
grb::structure_view<V> structure(V&& vector);                 (2)
```

### Parameters

`matrix` - a GraphBLAS matrix or matrix view

`vector` - a GraphBLAS vector or vector view

#### Type Requirements

- `matrix` must meet the requirements of `MatrixRange`

- `vector` must meet the requirements of `VectorRange`

### Return Value

(1) Returns a view of the matrix 

#### Possible Implementation

```cpp
template <typename Entry>
inline constexpr bool always_true(Entry&&) { return true; }

template <typename O>
using structure_view = grb::transform_view<O, decltype(always_true)>;

template <MatrixRange M>
grb::structure_view<M> structure(M&& matrix) {
  return grb::transform(std::forward<M>(matrix), always_true);
}

template <VectorRange V>
grb::structure_view<V> structure(V&& vector) {
  return grb::transform(std::forward<V>(vector), always_true);
}
```

## grb::filter

```cpp
template <MatrixRange M, typename Fn>
grb::filter_view<M> filter(M&& matrix, Fn&& fn);              (1)

template <VectorRange V, typename Fn>
grb::filter_view<V> filter(V&& vector, Fn&& fn);              (2)
```

### Parameters

`matrix` - a GraphBLAS matrix

`vector` - a GraphBLAS vector

`fn` - a function determining which elements should be filtered out

#### Type Requirements

- `M` must meet the requirements of `MaskMatrixRange`

- `V` must meet the requirements of `MaskVectorRange`

- `fn` must accept an argument of type `std::ranges::value_type_t<M>` (1) or `std::ranges::value_type_t<V>` (2) and return a value of type `bool`.

### Return Value

Returns a filtered view of the matrix `matrix` or vector `vector`.  The return value fulfills the requirements of `MatrixRange` (1) or `VectorRange` (2) .  The return value has the same shape as the input object, but without elements for which `fn(e)` evaluates to false.

## grb::complement

```cpp
template <MaskMatrixRange M>
grb::complement_view<M> complement(M&& mask);                 (1)

template <MaskVectorRange V>
grb::complement_view<V> complement(V&& mask);                 (2)
```

### Parameters

`mask` - a GraphBLAS mask

#### Type Requirements

- `M` must meet the requirements of `MaskMatrixRange`

- `V` must meet the requirements of `MaskVectorRange`

### Return Value

_TODO: Scott, Jose, is this the behavior we want?_
Returns the complement view of a matrix or vector mask.  At every index in `mask` with no stored value or with a scalar value equal to `false` when converted to `bool`, the returned view has a stored value with the scalar value `true`.  At every stored value in `mask` with a scalar value equal to `true` when converted to `bool`, the return view has no stored value.

(1) Returns a matrix view satisfying the requirements `MaskMatrixRange`.

(2) Returns a vector view satisfying the requirements `MaskVectorRange`.












