## `assign`

```cpp
template <grb::MatrixRange B,
          grb::MutableMatrixRange<grb::matrix_scalar_t<B>> A>
void assign(A&& a, B&& b);                                                   (1)

template <typename T, grb::MutableMatrixRange A<T>>
void assign(A&& a, const T& value);                                          (2)


template <grb::VectorRange V,
          grb::MutableVectorRange<grb::vector_scalar_t<V> U>
void assign(U&& u, V&& v);                                                   (3)


template <typename T, grb::MutableVectorRange V<T>>
void assign(U&& u, const T& value);                                          (4)
```

Assigns every element of a GraphbLAS matrix or vector to either (1, 3) another GraphBLAS matrix or vector with the same shape, or (2, 4) a single scalar value.

### Parameters

`a` - the matrix to be assigned

`b` - the matrix whose contents will be assigned to `a`

`u` - the vector to be assigned

`v` - the vector whose contents will be assigned to `v`

`value` - a scalar value to be assigned to every index location in `a`

#### Type Requirements

- `A` must be a mutable matrix range for the scalar value being assigned, that is it must meet the requirements of `grb::MutableMatrixRange<grb::matrix_scalar_t<B>>` (1) or `grb::MutableMatrixRange<T>` (2)

- `B` must meet the requirements of `grb::MatrixRange`

- `U` must be a mutable vector range for the scalar value being assigned, that is it must meet the requirements of `grb::MutableVectorRange<grb::vector_scalar_t<V>` (3) or `grb::MutableVectorRange<T>` (4)

- `V` must meet the requirements of `grb::VectorRange`

### Exceptions
The exception `grb::invalid_argument` is thrown if `a` and `b` or `u` and `v` are not the same shape.
`std::bad_alloc` may be thrown if `a` or `u`'s allocator is unable to allocate memory.

Other exceptions may be thrown while assigning or constructing to `a` or `u`.
