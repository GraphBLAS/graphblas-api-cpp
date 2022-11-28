## `ewise_union`

Perform an element-wise union between two GraphBLAS matrices or vectors.

#### Element-Wise Matrix Union
```cpp
template <MatrixRange A,
          MatrixRange B,
          BinaryOperator<grb::matrix_scalar_t<A>,
                         grb::matrix_scalar_t<B>> Combine,
          MaskMatrixRange M = grb::full_matrix_mask<>
>
auto ewise_union(A&& a, B&& b, Combine&& combine, M&& mask = M{});           (1)

template <MatrixRange A,
          MatrixRange B,
          BinaryOperator<grb::matrix_scalar_t<A>,
                         grb::matrix_scalar_t<B>> Combine,
          MaskMatrixRange M = grb::full_matrix_mask<>,
          BinaryOperator<grb::matrix_scalar_t<C>,
                         grb::elementwise_result_t<A, B, Combine>> Accumulate = grb::take_right,
          MutableMatrixRange<grb::elementwise_result_t<A, B, Combine>> C
>
void ewise_union(C&& c, A&& a, B&& b,
                 Combine&& combine, M&& mask = M{},
                 Accumulate&& acc = Accumulate{},
                 bool merge = false);                                        (2)
```

#### Element-Wise Vector Union
```cpp
template <VectorRange A,
          VectorRange B,
          BinaryOperator<grb::vector_scalar_t<A>,
                         grb::vector_scalar_t<B>> Combine,
          MaskVectorRange M = grb::full_vector_mask<>
>
auto ewise_union(A&& a, B&& b, Combine&& combine, M&& mask = M{});           (3)

template <VectorRange A,
          VectorRange B,
          BinaryOperator<grb::vector_scalar_t_t<A>,
                         grb::vector_scalar_t_t<B>> Combine,
          MaskVectorRange M = grb::full_vector_mask<>,
          BinaryOperator<grb::matrix_scalar_t<C>,
                         grb::elementwise_result_t<A, B, Combine>> Accumulate = grb::take_right,
          MutableVectorRange<grb::elementwise_result_t<A, B, Combine>> C
>
void ewise_union(C&& c, A&& a, B&& b,
                 Combine&& combine, M&& mask = M{},
                 Accumulate&& acc = Accumulate{},
                 bool merge = false);                                        (4)
```

### Parameters

`a` - matrix or vector on the left-hand side of the element-wise operation

`b` - matrix or vector on the right-hand side of the element-wise operation

`c` - output matrix or vector in which to store the result of the multiply operation

`combine` - binary operator used to combine elements of `a` and `b`

`mask` - determines which parts of the output matrix will be computed

`acc` - binary operator used to combine elements of the result with stored elements in corresponding locations in `c`

`merge` - flag declaring whether to merge in elements of `c` outside the range indicated by `mask`

#### Type Requirements

- `A` must meet the requirements of `MatrixRange` (1,2) or `VectorRange` (3,4)

- `B` must meet the requirements of `MatrixRange` (1,2) or `VectorRange` (3,4)

- `C` must meet the requirements of `MutableMatrixRange<grb::elementwise_result_t<A, B, Combine>>` (2) or `MutableVectorRange<grb::elementwise_result_t<A, B, Combine>>` (4)

- `Combine` must meet the requirements of `BinaryOperator<grb::matrix_scalar_t<A>, grb::matrix_scalar_t<B>>`.

- `M` must meet the requirements of `MaskMatrixRange` (1,2) or `MaskVectorRange` (3,4)

- `Accumulate` must meet the requirements of `BinaryOperator<grb::matrix_scalar_t<C>, grb::elementwise_result_t<A, B, Combine>>`

### Return Value

If the output matrix argument `c` is supplied, no value is returned.

If `c` is not supplied as an argument, returns a GraphBLAS matrix (1) or GraphBLAS vector (3) equal to the element-wise union of `a` and `b`, with the binary operator `combine` used to combine scalar values stored at the same index and `mask` used to determine which parts of the output are computed.  For (1), the type of the return value satisfies the requirements of `MatrixRange`, and for (3) the type of the return value satisfies the requirements of `VectorRange`.  The return value has the same shape as `a` and `b`.  Index `idx` in the return value only holds a stored value if an element exists at that index in both `a` and `mask` , `b` and `mask`, or `a`, `b`, and `mask`.  If a value exists at `idx` in `a` but not in `b`, the return value will hold a value equal to `a[idx]`.  If a value exists in `b` but not in `a`, it will hold a value equal to `b[idx]`.  If a value exists at `idx` in both `a` and `b`, it will hold a value equal to `fn(a[idx], b[idx])`.

### Preconditions

The arguments `a` and `b` must share the same shape.  If an output object `c` is given, it must also have the same shape.  For the argument `mask`, each dimension of its shape must be equal to or greater than the corresponding dimension of `a` and `b`'s shapes.  `fn` must not modify any element of `a`, `b`, or `mask`.

### Exceptions

The exception `grb::invalid_argument` may be thrown if any of the following conditions occur:

- The dimensions of `a` and `b` incompatible, that is `a.shape() != b.shape()`.
- The dimensions of `c`, if given, does not match `a`'s shape, that is `c.shape() != a.shape()`
- The dimensions of the mask are smaller than the dimensions of the output, that is `mask.shape()[0] < a.shape()[0] || mask.shape()[1] < a.shape()[1]` (1) or `mask.shape() < a.shape()`.

### Notes

### Example

```cpp
#include <grb/grb.hpp>

int main(int argc, char** argv) {
  grb::matrix<float> x({10, 10});
  grb::matrix<float> y({10, 10});

  x[{0, 1}] = 12;
  x[{2, 5}] = 12;
  x[{2, 7}] = 12;
  x[{5, 3}] = 12;

  y[{0, 1}] = 12;
  y[{1, 5}] = 12;
  y[{2, 7}] = 12;
  y[{5, 3}] = 12;

  auto z = grb::ewise_union(x, y, grb::plus{});

  grb::print(z);

  return 0;
}
```
