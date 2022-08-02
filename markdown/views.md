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
grb::structure_view<M> structure(M&& matrix);
```

### Parameters

`matrix` - a 

## grb::complement

```cpp
template <MaskMatrixRange M>
grb::complement_view<M> complement(M&& mask);
```

### Parameters

`mask` - a GraphBLAS mask

#### Type Requirements

- `M` must meet the requirements of `MaskMatrixRange`

### Return Value

Returns a matrix view satisfying the requirements `MaskMatrixRange`.












