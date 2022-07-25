## Multiply

```cpp
template <typename A,
          typename B,
          typename Reduce = grb::plus<>,
          typename Combine = grb::multiplies<>,
          typename Mask = grb::full_mask<>
>
auto multiply(A&& a,
	          B&& b,
	          Reduce&& reduce = Reduce{},
	          Combine&& combine = Combine{},
	          Mask&& mask = Mask{});
```

```cpp
template <MatrixRange A,
          MatrixRange B,
          BinaryOperator<grb::scalar_product_type_t<A, B>> Reduce,
          BinaryOperator<grb::matrix_value_type_t<A>, grb::matrix_value_type_t<B>> Combine,
          MaskMatrixRange Mask = grb::full_mask<>
>
multiply_result_t<A, B, Combine>
multiply(A&& a,
	     B&& b,
	     Reduce&& reduce = Reduce{},
	     Combine&& combine = Combine{},
	     Mask&& mask = Mask{});
```

The behavior is non-deterministic if `reduce` is not associative or not commutative.

### Parameters
`a` - the left-hand side of the matrix product being computed

`b` - the right-hand side of the matrix product being computed

`reduce` - a binary operator

`combine` - a binary operator

`mask` - write mask used to determine which elements of the output will be computed

#### Type Requirements
- `A` must meet the requirements of `MatrixRange`

- `B` must meet the requirements of `MatrixRange`

- `Reduce` must meet the requirements of `BinaryOperator<grb::scalar_product_type_t<A, B, Combine>>`

- `Combine` must meet the requirements of `BinaryOperator<grb::matrix_value_type_t<A>, grb::matrix_value_type_t<B>>`

- `Mask` must meet the requirements of `MaskMatrixRange`

### Return Value

Returns a matrix of shape `a.shape()[0]` by `b.shape()[1]` with scalar type
`scalar_product_type_t<A, B, Combine>` and the index type equal to that of `matrix_index_type_t<A>`
or `matrix_index_type_t<B>`, whichever has the larger `std::numeric_limits<T>::max()`.  An element `i, j`
of the output matrix will only be computed if element `i, j` exists in `mask` and is equal to `true`
when converted to `bool`.

Each element of the output is produced by combing the elements in corresponding indices of a row of `a`
and column of `b` and using `reduce` to perform a reduction to a single values, as defined in the
[GraphBLAS Math Specification](https://github.com/GraphBLAS/graphblas-api-math).
