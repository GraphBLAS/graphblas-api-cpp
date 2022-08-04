## `ewise_union`

```cpp
template <MatrixRange A,
          MatrixRange B,
          BinaryOperator<grb::matrix_scalar_type_t<A>,
                         grb::matrix_scalar_type_t<B>> Combine,
          MaskMatrixRange M = grb::full_mask<>
          >
auto ewise_union(A&& a, B&& b, Combine&& combine, M&& mask = M{});           (1)

template <VectorRange A,
          VectorRange B,
          BinaryOperator<grb::vector_scalar_type_t<A>,
                         grb::vector_scalar_type_t<B>> Combine,
          MaskVectorRange M = grb::full_mask<>
          >
auto ewise_union(A&& a, B&& b, Combine&& combine, M&& mask = M{});           (1)
```

Perform an element-wise union.

### Parameters

`a` - matrix or vector on the left-hand side of the element-wise operation

`b` - matrix or vector on the right-hand side of the element-wise operation

`combine` - binary operator used to combine elements of `a` and `b`

`mask` - determines which parts of the output matrix will be computed

#### Type Requirements

- `A` must meet the requirements of `MatrixRange` (1) or `VectorRange` (2)

- `B` must meet the requirements of `MatrixRange` (1) or `VectorRange` (2)

- `Combine` must meet the requirements of `BinaryOperator<grb::matrix_scalar_type_t<A>, grb::matrix_scalar_type_t<B>>`.

- `M` must meet the requirements of `MaskMatrixRange` (1) or `MaskVectorRange` (2)

### Return Value

### Complexity

### Exceptions

### Notes

### Example