# Element-Wise Operations

## Element-wise multiplication

```cpp
template <typename CMatrixType,
          typename AMatrixType,
          typename BMatrixType,
          typename Fn,            // Named requirement is BinaryOp, template name should reflect
          typename Accumulator,
          typename MaskType = grb::full_mask>
auto ewise_mult(CMatrixType&& c, AMatrixType&& a, BMatrixType&& b, Fn&& fn, Accumulator&& acc, MaskType&& mask = MaskType());

template <typename AMatrixType,
          typename BMatrixType,
          typename Fn,            // Named requirement is BinaryOp, template name should reflect
          typename MaskType = grb::full_mask>
auto ewise_mult(AMatrixType&& a, BMatrixType&& b, Fn&& fn, MaskType&& mask = MaskType());
```
---

Need to add vector versions

---

## Element-wise addition

```cpp
template <typename CMatrixType,
          typename AMatrixType,
          typename BMatrixType,
          typename Fn,            // Named requirement is BinaryOp, template name should reflect
          typename Accumulator,
          typename MaskType = grb::full_mask>
auto ewise_add(CMatrixType&& c, AMatrixType&& a, BMatrixType&& b, Fn&& fn, Accumulator&& acc, MaskType&& mask = MaskType());

template <typename AMatrixType,
          typename BMatrixType,
          typename Fn,            // Named requirement is BinaryOp, template name should reflect
          typename MaskType = grb::full_mask>
auto ewise_add(AMatrixType&& a, BMatrixType&& b, Fn&& fn, MaskType&& mask = MaskType());
```
---

Need to add vector versions

---


### Examples
