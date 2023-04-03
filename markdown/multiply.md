## Multiply

The function `grb::multiply` in GraphBLAS is used to multiply a matrix times a matrix, a matrix times a vector, or a vector times a matrix, depending on the types of the input arguments.

#### Matrix Times Matrix
```cpp
template <MatrixRange A,
          MatrixRange B,
          BinaryOperator<grb::matrix_scalar_t<A>, grb::matrix_scalar_t<B>> Combine,
          BinaryOperator<grb::combine_result_t<A, B, Combine>,
                         grb::combine_result_t<A, B, Combine>,
                         grb::combine_result_t<A, B, Combine>> Reduce,
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
          BinaryOperator<grb::combine_result_t<A, B, Combine>,
                         grb::combine_result_t<A, B, Combine>,
                         grb::combine_result_t<A, B, Combine>> Reduce,
          MaskMatrixRange M = grb::full_matrix_mask<>,
          BinaryOperator<grb::matrix_scalar_t<C>,
                         grb::combine_result_t<A, B, Combine>> Accumulate = grb::take_right,
          MutableMatrixRange<grb::combine_result_t<A, B, Combine>> C
>
void multiply(C&& c,                                                                    (2)
              A&& a,
              B&& b,
              Reduce&& reduce = Reduce{},
              Combine&& combine = Combine{},
              M&& mask = M{},
              Accumulate&& acc = Accumulate{},
              bool merge = false);

template <typename ExecutionPolicy,
          MatrixRange A,
          MatrixRange B,
          BinaryOperator<grb::matrix_scalar_t<A>, grb::matrix_scalar_t<B>> Combine,
          BinaryOperator<grb::combine_result_t<A, B, Combine>,
                         grb::combine_result_t<A, B, Combine>,
                         grb::combine_result_t<A, B, Combine>> Reduce,
          MaskMatrixRange M = grb::full_matrix_mask<>
>
multiply_result_t<A, B, Reduce, Combine>
multiply(ExecutionPolicy&& policy,                                                      (3)
         A&& a,
         B&& b,
         Reduce&& reduce = Reduce{},
         Combine&& combine = Combine{},
         M&& mask = M{});

template <typename ExecutionPolicy,
          MatrixRange A,
          MatrixRange B,
          BinaryOperator<grb::matrix_scalar_t<A>, grb::matrix_scalar_t<B>> Combine,
          BinaryOperator<grb::combine_result_t<A, B, Combine>,
                         grb::combine_result_t<A, B, Combine>,
                         grb::combine_result_t<A, B, Combine>> Reduce,
          MaskMatrixRange M = grb::full_matrix_mask<>,
          BinaryOperator<grb::matrix_scalar_t<C>,
                         grb::combine_result_t<A, B, Combine>> Accumulate = grb::take_right,
          MutableMatrixRange<grb::combine_result_t<A, B, Combine>> C
>
void multiply(ExecutionPolicy&& policy,                                                 (4)
              C&& c,
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
          BinaryOperator<grb::combine_result_t<A, B, Combine>,
                         grb::combine_result_t<A, B, Combine>,
                         grb::combine_result_t<A, B, Combine>> Reduce,
          MaskVectorRange M = grb::full_vector_mask<>
>
mutiply_result<A, B, Reduce, Combine>
multiply(A&& a,                                                                         (5)
         B&& b,
         Reduce&& reduce = Reduce{},
         Combine&& combine = Combine{},
         M&& mask = M{});

template <MatrixRange A,
          VectorRange B,
          BinaryOperator<grb::matrix_scalar_t<A>, grb::vector_scalar_t<B>> Combine,
          BinaryOperator<grb::combine_result_t<A, B, Combine>,
                         grb::combine_result_t<A, B, Combine>,
                         grb::combine_result_t<A, B, Combine>> Reduce,
          MaskVectorRange M = grb::full_vector_mask<>,
          BinaryOperator<grb::matrix_scalar_t<C>,
                         grb::combine_result_t<A, B, Combine>> Accumulate = grb::take_right,
          MutableVectorRange<grb::combine_result_t<A, B, Combine>> C
>
void multiply(C&& c,                                                                    (6)
              A&& a,
              B&& b,
              Reduce&& reduce = Reduce{},
              Combine&& combine = Combine{},
              M&& mask = M{},
              Accumulate&& acc = Accumulate{},
              bool merge = false);

template <typename ExecutionPolicy,
          MatrixRange A,
          VectorRange B,
          BinaryOperator<grb::matrix_scalar_t<A>, grb::vector_scalar_t<B>> Combine,
          BinaryOperator<grb::combine_result_t<A, B, Combine>,
                         grb::combine_result_t<A, B, Combine>,
                         grb::combine_result_t<A, B, Combine>> Reduce,
          MaskVectorRange M = grb::full_vector_mask<>
>
mutiply_result<A, B, Reduce, Combine>
multiply(A&& a,                                                                         (7)
         B&& b,
         Reduce&& reduce = Reduce{},
         Combine&& combine = Combine{},
         M&& mask = M{});

template <typename ExecutionPolicy,
          MatrixRange A,
          VectorRange B,
          BinaryOperator<grb::matrix_scalar_t<A>, grb::vector_scalar_t<B>> Combine,
          BinaryOperator<grb::combine_result_t<A, B, Combine>,
                         grb::combine_result_t<A, B, Combine>,
                         grb::combine_result_t<A, B, Combine>> Reduce,
          MaskVectorRange M = grb::full_vector_mask<>,
          BinaryOperator<grb::matrix_scalar_t<C>,
                         grb::combine_result_t<A, B, Combine>> Accumulate = grb::take_right,
          MutableVectorRange<grb::combine_result_t<A, B, Combine>> C
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

#### Vector Times Vector

```cpp
template <VectorRange A,
          VectorRange B,
          BinaryOperator<grb::vector_scalar_t<A>, grb::vector_scalar_t<B>> Combine,
          BinaryOperator<grb::combine_result_t<A, B, Combine>,
                         grb::combine_result_t<A, B, Combine>,
                         grb::combine_result_t<A, B, Combine>> Reduce,
>
mutiply_result<A, B, Reduce, Combine>
multiply(A&& a,                                                                         (9)
         B&& b,
         Reduce&& reduce = Reduce{},
         Combine&& combine = Combine{});

template <VectorRange A,
          VectorRange B,
          BinaryOperator<grb::vector_scalar_t<A>, grb::vector_scalar_t<B>> Combine,
          BinaryOperator<grb::combine_result_t<A, B, Combine>,
                         grb::combine_result_t<A, B, Combine>,
                         grb::combine_result_t<A, B, Combine>> Reduce,
          BinaryOperator<grb::vector_scalar_t<C>,
                         grb::combine_result_t<A, B, Combine>> Accumulate = grb::take_right,
          std::assignable_from<grb::combine_result_t<A, B, Combine>> C
>
void multiply(C&& c,                                                                   (10)
              A&& a,
              B&& b,
              Reduce&& reduce = Reduce{},
              Combine&& combine = Combine{},
              Accumulate&& acc = Accumulate{},
              bool merge = false);

template <typename ExecutionPolicy,
          VectorRange A,
          VectorRange B,
          BinaryOperator<grb::vector_scalar_t<A>, grb::vector_scalar_t<B>> Combine,
          BinaryOperator<grb::combine_result_t<A, B, Combine>,
                         grb::combine_result_t<A, B, Combine>,
                         grb::combine_result_t<A, B, Combine>> Reduce,
>
mutiply_result<A, B, Reduce, Combine>
multiply(ExecutionPolicy&& policy,                                                     (11)
         A&& a,
         B&& b,
         Reduce&& reduce = Reduce{},
         Combine&& combine = Combine{});

template <typename ExecutionPolicy,
          VectorRange A,
          VectorRange B,
          BinaryOperator<grb::vector_scalar_t<A>, grb::vector_scalar_t<B>> Combine,
          BinaryOperator<grb::combine_result_t<A, B, Combine>,
                         grb::combine_result_t<A, B, Combine>,
                         grb::combine_result_t<A, B, Combine>> Reduce,
          BinaryOperator<grb::vector_scalar_t<C>,
                         grb::combine_result_t<A, B, Combine>> Accumulate = grb::take_right,
          std::assignable_from<grb::combine_result_t<A, B, Combine>> C
>
void multiply(ExecutionPolicy&& policy,                                                (12)
              C&& c,
              A&& a,
              B&& b,
              Reduce&& reduce = Reduce{},
              Combine&& combine = Combine{},
              Accumulate&& acc = Accumulate{},
              bool merge = false);
```

#### Vector Times Matrix

```cpp
template <VectorRange A,
          MatrixRange B,
          BinaryOperator<grb::vector_scalar_t<A>, grb::matrix_scalar_t<B>> Combine,
          BinaryOperator<grb::combine_result_t<A, B, Combine>,
                         grb::combine_result_t<A, B, Combine>,
                         grb::combine_result_t<A, B, Combine>> Reduce,
          MaskVectorRange M = grb::full_vector_mask<>
>
mutiply_result<A, B, Reduce, Combine>
multiply(A&& a,                                                                        (13)
         B&& b,
         Reduce&& reduce = Reduce{},
         Combine&& combine = Combine{},
         M&& mask = M{});

template <VectorRange A,
          MatrixRange B,
          BinaryOperator<grb::vector_scalar_t<A>, grb::matrix_scalar_t<B>> Combine,
          BinaryOperator<grb::combine_result_t<A, B, Combine>,
                         grb::combine_result_t<A, B, Combine>,
                         grb::combine_result_t<A, B, Combine>> Reduce,
          MaskVectorRange M = grb::full_vector_mask<>,
          BinaryOperator<grb::vector_scalar_t<C>,
                         grb::combine_result_t<A, B, Combine>> Accumulate = grb::take_right,
          MutableVectorRange<grb::combine_result_t<A, B, Combine>> C
>
void multiply(C&& c,                                                                   (14)
              A&& a,
              B&& b,
              Reduce&& reduce = Reduce{},
              Combine&& combine = Combine{},
              M&& mask = M{},
              Accumulate&& acc = Accumulate{},
              bool merge = false);

template <typename ExecutionPolicy,
          VectorRange A,
          MatrixRange B,
          BinaryOperator<grb::vector_scalar_t<A>, grb::matrix_scalar_t<B>> Combine,
          BinaryOperator<grb::combine_result_t<A, B, Combine>,
                         grb::combine_result_t<A, B, Combine>,
                         grb::combine_result_t<A, B, Combine>> Reduce,
          MaskVectorRange M = grb::full_vector_mask<>
>
mutiply_result<A, B, Reduce, Combine>
multiply(ExecutionPolicy&& policy,                                                     (15)
         A&& a,
         B&& b,
         Reduce&& reduce = Reduce{},
         Combine&& combine = Combine{},
         M&& mask = M{});

template <typename ExecutionPolicy,
          VectorRange A,
          MatrixRange B,
          BinaryOperator<grb::vector_scalar_t<A>, grb::matrix_scalar_t<B>> Combine,
          BinaryOperator<grb::combine_result_t<A, B, Combine>,
                         grb::combine_result_t<A, B, Combine>,
                         grb::combine_result_t<A, B, Combine>> Reduce,
          MaskVectorRange M = grb::full_vector_mask<>,
          BinaryOperator<grb::vector_scalar_t<C>,
                         grb::combine_result_t<A, B, Combine>> Accumulate = grb::take_right,
          MutableVectorRange<grb::combine_result_t<A, B, Combine>> C
>
void multiply(ExecutionPolicy&& policy,                                                (16)
              C&& c,
              A&& a,
              B&& b,
              Reduce&& reduce = Reduce{},
              Combine&& combine = Combine{},
              M&& mask = M{},
              Accumulate&& acc = Accumulate{},
              bool merge = false);
```

Behavior is non-deterministic if `reduce` is not associative or not commutative.

### Parameters
`policy` - the execution policy to use

`a` - the left-hand side of the product being computed

`b` - the right-hand side of the product being computed

`reduce` - a binary operator

`combine` - a binary operator

`mask` - write mask used to determine which elements of the output will be computed

`c` - if given, the output object to which to write the result

`acc` - the accumulator used to accumulate partial results into the output object

`merge` - whether to merge in values from `c` outside of the write area indicated by `mask`

#### Type Requirements
- `A` must meet the requirements of `MatrixRange` (1-8) or `VectorRange` (9-16)

- `B` must meet the requirements of `MatrixRange` (1-4,13-16) or `VectorRange` (5-12)

- `Reduce` must meet the requirements of `BinaryOperator<grb::combine_result_type_t<A, B, Combine>, grb::combine_result_type_t<A, B, Combine>, grb::combine_result_type_t<A, B, Combine>>`

- `Combine` must meet the requirements of `BinaryOperator<grb::container_value_t<A>, grb::container_value_t<B>>`

- `M` must meet the requirements of `MaskMatrixRange` (1-8) or `VectorMaskRange` (9-16)

### Return Value

If the output matrix or vector argument, `c`, is supplied, no value is returned.

__NOTE: `combine_result_t<A, B, Combine> is actually incorrect here. Should be result of reduction.__

If `c` is not supplied as an argument, returns the result of the multiplication.

(1) - A GraphBLAS matrix with shape `a.shape()[0]` by `b.shape()[1]`

(3) - A GraphBLAS vector with shape `a.shape()[0]`

(5) - `combine_result_t<A, B, Combine>`

(7) - A GraphBLAS vector with shape `b.shape()[1]`

In the case that a GraphBLAS matrix or vector is returned, its scalar type is
`combine_result_t<A, B, Combine>`, and its index type is equal to either
`grb::matrix_index_t<A>` or `grb::matrix_index_t<B>`, whichever one has the larger
`std::numeric_limits<T>::max()`.
An element of the result at index location `index` will only be computed if
a scalar value equal to `true` when converted to `bool` exists in `mask`, that is
`grb::find(mask, index) != grb::end(mask) && bool(grb::get<1>(*grb::find(mask, index)))`.

##### Matrix Times Matrix
A generalized matrix times matrix multiplication is performed, as defined in the
[GraphBLAS Math Specification](https:://github.com/GraphBLAS/graphblas-api-math).
Each element of the output is produced by combing the elements in corresponding indices of a row of `a`
and column of `b` and using `reduce` to perform a reduction to a single value.

##### Matrix Times Vector
A generalized matrix times vector multiplication is performed, as defined in the
[GraphBLAS Math Specification](https:://github.com/GraphBLAS/graphblas-api-math).
Each element of the output vector is produced by combining elements in each row
of `a` with the corresponding elements of the vector `b` and using `reduce` to
perform a reduction of these to a single value in the output vector.

##### Vector Times Vector
A generalized dot product is performed, as defined in the
[GraphBLAS Math Specification](https:://github.com/GraphBLAS/graphblas-api-math).
The corresponding elements of vectors `a` and `b` are combined and reduced into
a single value using `reduce`.

##### Vector Times Matrix
A generalized matrix times vector multiplication is performed, as defined in the
[GraphBLAS Math Specification](https:://github.com/GraphBLAS/graphblas-api-math).
Each element of the output vector is produced by combining elements in each column
of `b` with the corresponding elements of the vector `a` and using `reduce` to
perform a reduction of these to a single value in the output vector.

### Complexity
Complexity is implementation-defined.

### Exceptions
The exception `grb::invalid_argument` may be thrown if any of the following conditions occur:

##### Matrix Times Matrix
- The dimensions of the matrices being multiplied are incompatible, that is `a.shape()[1] != b.shape()[0]`.
- The dimensions of the mask are smaller than the dimensions of the output, that is `mask.shape()[0] < a.shape()[0] || mask.shape()[1] < b.shape()[1]`
- The dimensions of the output matrix, if provided, are incompatible, that is `c.shape()[0] != a.shape()[0] || c.shape()[1] != b.shape()[1]`.

##### Matrix Times Vector
- The dimensions of the matrix and vector being multiplied are incompatible, that is `a.shape()[1] != b.shape()`.
- The dimensions of the mask are smaller than the dimensions of the output, that is `mask.shape() < a.shape()[0]`
- The dimensions of the output vector, if provided, are incompatible, that is `c.shape() != a.shape()[0]`.

##### Vector Times Vector
- The dimensions of the vectors being multiplied are incompatible, that is `a.shape() != b.shape()`.
- The dimensions of the mask are smaller than the dimensions of the output, that is `mask.shape() < a.shape()[0]`
- The dimensions of the output vector, if provided, are incompatible, that is `c.shape() != a.shape()[0]`.

##### Vector Times Matrix
- The dimensions of the matrix and vector being multiplied are incompatible, that is `a.shape() != b.shape()[0]`.
- The dimensions of the mask are smaller than the dimensions of the output, that is `mask.shape() < b.shape()[1]`
- The dimensions of the output vector, if provided, are incompatible, that is `c.shape() != b.shape()[1]`.

If the algorithm fails to allocate memory, `std::bad_alloc` is thrown.

### Notes

### Example
