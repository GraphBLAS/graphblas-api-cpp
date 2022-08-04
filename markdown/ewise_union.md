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

Returns a GraphBLAS matrix (1) or GraphBLAS vector (2) equal to the element-wise union of `a` and `b`, with the binary operator `combine` used to combine scalar values stored at the same index and `mask` used to determine which parts of the output are computed.  For (1), the type of the return value satisfies the requirements of `MatrixRange`, and for (2) the type of the return value satisfies the requirements of `VectorRange`.  The return value has the same shape as `a` and `b`.  Index `idx` in the return value only holds a stored value if an element exists at that index in both `a` and `mask` , `b` and `mask`, or `a`, `b`, and `mask`.  If a value exists at `idx` in `a` but not in `b`, the return value will hold a value equal to `a[idx]`.  If a value exists in `b` but not in `a`, it will hold a value equal to `b[idx]`.  If a value exists at `idx` in both `a` and `b`, it will hold a value equal to `fn(a[idx], b[idx])`.

### Preconditions

The arguments `a` and `b` must share the same shape.  For the argument `mask`, each dimension of its shape must be equal to or greater than the corresponding dimension of `a` and `b`'s shapes.  `fn` must not modify any element of `a`, `b`, or `mask`.

### Exceptions

The exception `grb::invalid_argument` may be thrown if any of the following conditions occur:

- The dimensions of `a` and `b` incompatible, that is `a.shape() != b.shape()`.
- The dimensions of the mask are smaller than the dimensions of the output, that is `mask.shape()[0] < a.shape()[0] || mask.shape()[1] < a.shape()[1]` (1) or `mask.shape() < a.shape()`.

### Notes

### Example