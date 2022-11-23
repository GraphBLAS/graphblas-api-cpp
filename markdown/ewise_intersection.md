## `ewise_intersection`

Perform an element-wise intersection between two GraphBLAS matrices or vectors.

#### Element-Wise Matrix Intersection
```cpp
template <MatrixRange A,
          MatrixRange B,
          BinaryOperator<grb::matrix_scalar_t<A>,
                         grb::matrix_scalar_t<B>> Combine,
          MaskMatrixRange M = grb::full_matrix_mask<>
>
auto ewise_intersection(A&& a, B&& b, Combine&& combine, M&& mask = M{});    (1)

template <MatrixRange A,
          MatrixRange B,
          BinaryOperator<grb::matrix_scalar_t<A>,
                         grb::matrix_scalar_t<B>> Combine,
          MaskMatrixRange M = grb::full_matrix_mask<>,
          BinaryOperator<grb::matrix_scalar_t<C>,
                         grb::elementwise_result_t<A, B, Combine>> Accumulate = grb::take_right,
          MutableMatrixRange<grb::elementwise_result_t<A, B, Combine>> C
>
void ewise_intersection(C&& c, A&& a, B&& b,
                        Combine&& combine, M&& mask = M{},
                        Accumulate&& acc = Accumulate{},
                        bool merge = false);                                 (2)
```

#### Element-Wise Vector Intersection
```cpp
template <VectorRange A,
          VectorRange B,
          BinaryOperator<grb::vector_scalar_t_t<A>,
                         grb::vector_scalar_t_t<B>> Combine,
          MaskVectorRange M = grb::full_vector_mask<>
          >
auto ewise_intersection(A&& a, B&& b, Combine&& combine, M&& mask = M{});    (3)

template <VectorRange A,
          VectorRange B,
          BinaryOperator<grb::vector_scalar_t_t<A>,
                         grb::vector_scalar_t_t<B>> Combine,
          MaskVectorRange M = grb::full_vector_mask<>,
          BinaryOperator<grb::matrix_scalar_t<C>,
                         grb::elementwise_result_t<A, B, Combine>> Accumulate = grb::take_right,
          MutableVectorRange<grb::elementwise_result_t<A, B, Combine>> C
>
void ewise_intersection(C&& c, A&& a, B&& b,
                        Combine&& combine, M&& mask = M{},
                        Accumulate&& acc = Accumulate{},
                        bool merge = false);                                 (4)
```

Perform an element-wise intersection.

### Parameters

`a` - matrix or vector on the left-hand side of the element-wise operation

`b` - matrix or vector on the right-hand side of the element-wise operation

`c` - output matrix or vector in which to store the result of the multiply operation

`combine` - binary operator used to combine elements of `a` and `b`

`mask` - determines which parts of the output matrix will be computed

`acc` - binary operator used to combine elements of the result with stored elements in corresponding locations in `c`

`merge` - flag declaring whether to merge in elements of `c` outside the range indicated by `mask`

#### Type Requirements

- `A` must meet the requirements of `MatrixRange` (1) or `VectorRange` (2)

- `B` must meet the requirements of `MatrixRange` (1) or `VectorRange` (2)

- `C` must meet the requirements of `MutableMatrixRange<grb::elementwise_result_t<A, B, Combine>>` (2) or `MutableVectorRange<grb::elementwise_result_t<A, B, Combine>>` (4)

- `Combine` must meet the requirements of `BinaryOperator<grb::matrix_scalar_t<A>, grb::matrix_scalar_t<B>>`.

- `M` must meet the requirements of `MaskMatrixRange` (1) or `MaskVectorRange` (2)

- `Accumulate` must meet the requirements of `BinaryOperator<grb::matrix_scalar_t<C>, grb::elementwise_result_t<A, B, Combine>>`

### Return Value

If the output matrix argument `c` is supplied, no value is returned.

If `c` is not supplied as an argument, returns a GraphBLAS matrix (1) or GraphBLAS vector (3) equal to the element-wise intersection of `a` and `b`, with the binary operator `combine` used to combine scalar values and `mask` used to determine which parts of the output are computed.  For (1), the type of the return value satisfies the requirements of `MatrixRange`, and for (3) the type of the return value satisfies the requirements of `VectorRange`.  The return value has the same shape as `a` and `b`.  Index `idx` will only hold an element in the return value if an element exists at `idx` in both `a`, `b`, and `mask`.  The value at that index will be equal to the value `fn(a[idx], b[idx])`.

### Preconditions

The arguments `a` and `b` must share the same shape.  If an output object `c` is given, it must also have the same shape.  For the argument `mask`, each dimension of its shape must be equal to or greater than the corresponding dimension of `a` and `b`'s shapes.  `fn` must not modify any element of `a`, `b`, or `mask`.

### Exceptions

The exception `grb::invalid_argument` may be thrown if any of the following conditions occur:

- The dimensions of `a` and `b` incompatible, that is `a.shape() != b.shape()`.
- The dimensions of `c`, if given, does not match `a`'s shape, that is `c.shape() != a.shape()`
- The dimensions of the mask are smaller than the dimensions of the output, that is `mask.shape()[0] < a.shape()[0] || mask.shape()[1] < a.shape()[1]` (1) or `mask.shape() < a.shape()`.

### Notes

### Example
