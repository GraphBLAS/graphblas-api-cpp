## Multiply

The function `grb::multiply` in GraphBLAS is used to multiply a matrix times a matrix, a matrix times a vector, or a vector times a matrix, depending on the types of the input arguments.

#### Matrix Times Matrix
```cpp
template <MatrixRange A,
          MatrixRange B,
          BinaryOperator<grb::matrix_scalar_t<A>, grb::matrix_scalar_t<B>> Combine,
          BinaryOperator<grb::elementwise_result_t<A, B, Combine>,
                         grb::elementwise_result_t<A, B, Combine>,
                         grb::elementwise_result_t<A, B, Combine>> Reduce,
          MaskMatrixRange M = grb::full_matrix_mask<>
>
multiply_result_t<A, B, Reduce, Combine>
multiply(A&& a,                                                                         (1)
         B&& b,
         Reduce&& reduce = Reduce{},
         Combine&& combine = Combine{},
         M&& mask = M{});

template <MatrixRange A,
          MatrixRange B,
          BinaryOperator<grb::matrix_scalar_t<A>, grb::matrix_scalar_t<B>> Combine,
          BinaryOperator<grb::elementwise_result_t<A, B, Combine>,
                         grb::elementwise_result_t<A, B, Combine>,
                         grb::elementwise_result_t<A, B, Combine>> Reduce,
          MaskMatrixRange M = grb::full_matrix_mask<>,
          BinaryOperator<grb::matrix_scalar_t<C>,
                         grb::elementwise_result_t<A, B, Combine>> Accumulate = grb::take_left,
          MutableMatrixRange<grb::elementwise_result_t<A, B, Combine>> C
>
void multiply(C&& c,                                                                    (2)
              A&& a,
              B&& b,
              Reduce&& reduce = Reduce{},
              Combine&& combine = Combine{},
              M&& mask = M{},
              Accumulate&& acc = Accumulate{},
              bool merge = false);
```

#### Matrix Times Vector

```cpp
template <MatrixRange A,
          VectorRange B,
          BinaryOperator<grb::matrix_scalar_t<A>, grb::vector_scalar_t<B>> Combine,
          BinaryOperator<grb::elementwise_result_t<A, B, Combine>,
                         grb::elementwise_result_t<A, B, Combine>,
                         grb::elementwise_result_t<A, B, Combine>> Reduce,
          MaskVectorRange M = grb::full_vector_mask<>
>
mutiply_result<A, B, Reduce, Combine>
multiply(A&& a,                                                                         (3)
         B&& b,
         Reduce&& reduce = Reduce{},
         Combine&& combine = Combine{},
         M&& mask = M{});

template <MatrixRange A,
          VectorRange B,
          BinaryOperator<grb::matrix_scalar_t<A>, grb::vector_scalar_t<B>> Combine,
          BinaryOperator<grb::elementwise_result_t<A, B, Combine>,
                         grb::elementwise_result_t<A, B, Combine>,
                         grb::elementwise_result_t<A, B, Combine>> Reduce,
          MaskVectorRange M = grb::full_vector_mask<>,
          BinaryOperator<grb::matrix_scalar_t<C>,
                         grb::elementwise_result_t<A, B, Combine>> Accumulate = grb::take_left,
          MutableVectorRange<grb::elementwise_result_t<A, B, Combine>> C
>
void multiply(C&& c,                                                                    (4)
              A&& a,
              B&& b,
              Reduce&& reduce = Reduce{},
              Combine&& combine = Combine{},
              M&& mask = M{},
              Accumulate&& acc = Accumulate{},
              bool merge = false);
```

#### Vector Times Vector

```cpp
template <VectorRange A,
          VectorRange B,
          BinaryOperator<grb::vector_scalar_t<A>, grb::vector_scalar_t<B>> Combine,
          BinaryOperator<grb::elementwise_result_t<A, B, Combine>,
                         grb::elementwise_result_t<A, B, Combine>,
                         grb::elementwise_result_t<A, B, Combine>> Reduce,
          MaskVectorRange M = grb::full_vector_mask<>
>
mutiply_result<A, B, Reduce, Combine>
multiply(A&& a,                                                                         (5)
         B&& b,
         Reduce&& reduce = Reduce{},
         Combine&& combine = Combine{},
         M&& mask = M{});

template <VectorRange A,
          VectorRange B,
          BinaryOperator<grb::vector_scalar_t<A>, grb::vector_scalar_t<B>> Combine,
          BinaryOperator<grb::elementwise_result_t<A, B, Combine>,
                         grb::elementwise_result_t<A, B, Combine>,
                         grb::elementwise_result_t<A, B, Combine>> Reduce,
          MaskVectorRange M = grb::full_vector_mask<>,
          BinaryOperator<grb::vector_scalar_t<C>,
                         grb::elementwise_result_t<A, B, Combine>> Accumulate = grb::take_left,
          MutableVectorRange<grb::elementwise_result_t<A, B, Combine>> C
>
void multiply(C&& c,                                                                    (6)
              A&& a,
              B&& b,
              Reduce&& reduce = Reduce{},
              Combine&& combine = Combine{},
              M&& mask = M{},
              Accumulate&& acc = Accumulate{},
              bool merge = false);
```

#### Vector Times Matrix

```cpp
template <VectorRange A,
          MatrixRange B,
          BinaryOperator<grb::vector_scalar_t<A>, grb::matrix_scalar_t<B>> Combine,
          BinaryOperator<grb::elementwise_result_t<A, B, Combine>,
                         grb::elementwise_result_t<A, B, Combine>,
                         grb::elementwise_result_t<A, B, Combine>> Reduce,
          MaskVectorRange M = grb::full_vector_mask<>
>
mutiply_result<A, B, Reduce, Combine>
multiply(A&& a,                                                                         (7)
         B&& b,
         Reduce&& reduce = Reduce{},
         Combine&& combine = Combine{},
         M&& mask = M{});

template <VectorRange A,
          MatrixRange B,
          BinaryOperator<grb::vector_scalar_t<A>, grb::matrix_scalar_t<B>> Combine,
          BinaryOperator<grb::elementwise_result_t<A, B, Combine>,
                         grb::elementwise_result_t<A, B, Combine>,
                         grb::elementwise_result_t<A, B, Combine>> Reduce,
          MaskVectorRange M = grb::full_vector_mask<>,
          BinaryOperator<grb::vector_scalar_t<C>,
                         grb::elementwise_result_t<A, B, Combine>> Accumulate = grb::take_left,
          MutableVectorRange<grb::elementwise_result_t<A, B, Combine>> C
>
void multiply(C&& c,                                                                    (8)
              A&& a,
              B&& b,
              Reduce&& reduce = Reduce{},
              Combine&& combine = Combine{},
              M&& mask = M{},
              Accumulate&& acc = Accumulate{},
              bool merge = false);
```

The behavior is non-deterministic if `reduce` is not associative or not commutative.

### Parameters
`a` - the left-hand side of the matrix product being computed

`b` - the right-hand side of the matrix product being computed

`reduce` - a binary operator

`combine` - a binary operator

`mask` - write mask used to determine which elements of the output will be computed


`c` - if given, the output matrix to which to write the result

`acc` - the accumulator used to accumulate partial results 

`merge` - whether to merge in values from `c` outside of the write area indicated by `mask`

#### Type Requirements
- `A` must meet the requirements of `MatrixRange`

- `B` must meet the requirements of `MatrixRange`

- `Reduce` must meet the requirements of `BinaryOperator<grb::elementwise_result_type_t<A, B, Combine>, grb::elementwise_result_type_t<A, B, Combine>, grb::elementwise_result_type_t<A, B, Combine>>`

- `Combine` must meet the requirements of `BinaryOperator<grb::matrix_value_t<A>, grb::matrix_value_t<B>>`

- `M` must meet the requirements of `MaskMatrixRange`

### Return Value

Returns a matrix of shape `a.shape()[0]` by `b.shape()[1]` with scalar type
`elementwise_result_type_t<A, B, Combine>` and the index type equal to that of `matrix_index_type_t<A>`
or `matrix_index_type_t<B>`, whichever has the larger `std::numeric_limits<T>::max()`.  An element `i, j`
of the output matrix will only be computed if element `i, j` exists in `mask` and is equal to `true`
when converted to `bool`.

Each element of the output is produced by combing the elements in corresponding indices of a row of `a`
and column of `b` and using `reduce` to perform a reduction to a single values, as defined in the
[GraphBLAS Math Specification](https://github.com/GraphBLAS/graphblas-api-math).

### Complexity
TODO: do we make any promises about complexity?
Something along the lines of $n^3$.

### Exceptions
The exception `grb::invalid_argument` may be thrown if any of the following conditions occur:

- The dimensions of the matrices being multiplied are incompatible, that is `a.shape()[1] != b.shape()[0]`.
- The dimensions of the mask are smaller than the dimensions of the output, that is `mask.shape()[0] < a.shape()[0] || mask.shape()[1] < b.shape()[1]`

If the algorithm fails to allocate memory, `std::bad_alloc` is thrown.

### Notes

### Example
