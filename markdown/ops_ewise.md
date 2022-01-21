# Element-Wise Operations

```cpp
template <typename CMatrixType,
          typename AMatrixType,
          typename BMatrixType,
          typename Fn,
          typename Accumulator,
          typename MaskType = grb::full_mask>
auto ewise_mult(CMatrixType&& c, AMatrixType&& a, BMatrixType&& b, Fn&& fn, Accumulator&& acc, MaskType&& mask = MaskType());

template <typename AMatrixType,
          typename BMatrixType,
          typename Fn,
          typename MaskType = grb::full_mask>
auto ewise_mult(AMatrixType&& a, BMatrixType&& b, Fn&& fn, MaskType&& mask = MaskType());

template <typename CMatrixType,
          typename AMatrixType,
          typename BMatrixType,
          typename Fn,
          typename Accumulator,
          typename MaskType = grb::full_mask>
auto ewise_add(CMatrixType&& c, AMatrixType&& a, BMatrixType&& b, Fn&& fn, Accumulator&& acc, MaskType&& mask = MaskType());

template <typename AMatrixType,
          typename BMatrixType,
          typename Fn,
          typename MaskType = grb::full_mask>
auto ewise_add(AMatrixType&& a, BMatrixType&& b, Fn&& fn, MaskType&& mask = MaskType());
```

### Example
