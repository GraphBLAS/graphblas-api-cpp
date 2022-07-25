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
