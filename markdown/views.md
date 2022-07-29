# Views

## grb::transpose

```cpp
template <MatrixRange M>
grb::transpose_view<M> transpose(M&& matrix);
```

### Parameters

`matrix` - a GraphBLAS matrix

#### Type Requirements

- `M` must meet the requirements of `MatrixRange`

### Return Value
Returns a matrix view that is equal to the transpose of `matrix`.
If `M` meets the requirements of `MutableMatrixRange`, then the return value will meet the
requirements of `MutableMatrixRange`.  If `M` meets the requirments of `MatrixRange` but not
`MutableMatrixRange`, then the return value will meet the requirements of `MatrixRange`.

If the lifetime of the return value of `transpose` outlives the lifetimes of `matrix`, then the
behavior is undefined.

## grb::transform

```cpp
template <MatrixRange M, typename Fn>
grb::structure_view<M> transform(M&& matrix, Fn&& fn);

template <VectorRange M, typename Fn>
grb::structure_view<M> transform(M&& matrix, Fn&& fn);
```

### Parameters

`matrix` - a GraphBLAS matrix

`fn` - function used to transform matrix values element-wise

#### Type Requirements

- `M` must meet the requirements of `MatrixRange`

### Return Value

Returns a view of the matrix `matrix` in which every stored scalar value has been transformed using the function `fn`.  `fn` accepts the full matrix entry, which includes a 

### Example

## grb::structure
```cpp
template <MatrixRange M>
grb::structure_view<M> structure(M&& matrix);
```

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

MaskMatrixRange -> MaskMatrixRange













