# Matrix-matrix multiplication: `mxm`

Multiplies two GraphBLAS matrices using the operators and identity defined by a GraphBLAS semiring. An optional accumulator and write mask can also be specified. The result is stored in third GraphBLAS matrix.


```cpp
    // TODO: replace all typenames with concept names
    template<typename CMatrixType,
             typename MaskType,
             typename AccumulatorType,
             typename SemiringType,
             typename AMatrixType,
             typename BMatrixType>
    void mxm(CMatrixType            &C,
             MaskType         const &Mask,
             AccumulatorType         accum,   // pass by value or const& or &&?
             SemiringType            op,      // pass by value or const& or &&?
             AMatrixType      const &A,
             BMatrixType      const &B,
             OutputControlEnum       outp = MERGE);  // or bool replace_flag = false);
```
-----
```cpp
    // ...or...
    template<typename CMatrixType,
             typename MaskType,
             typename AccumulatorType,
             typename ReduceType,
             typename MapType
             typename AMatrixType,
             typename BMatrixType>
    void mxm(CMatrixType            &C,
             MaskType         const &Mask,
             AccumulatorType         accum,   // pass by value or const& or &&?
             ReduceType              reduce,  // pass by value or const& or &&?
             MapType                 map,     // pass by value or const& or &&?
             AMatrixType      const &A,
             BMatrixType      const &B,
             OutputControlEnum       outp = MERGE);  // or bool replace_flag = false);
```
-----
```cpp
    // ...or...from RGRI...
    template<typename AMatrixType,
             typename BMatrixType,
             typename ReduceType = std::plus<>,       // is this a reasonable default?
             typename MapType    = std::multiplies<>, // is this a reasonable default?
             typename MaskType   = std::full_mask>    // instead of no_mask?
    auto mxm(AMatrixType&&     A,
             BMatrixType&&     B,
             ReduceType&&      reduce = ReduceType(),
             MapType&&         map    = MapType(),        // or CombineFn
             MaskType&&        Mask   = grb::full_mask(), // or grb::no_mask()
             OutputControlEnum outp   = MERGE);           // or bool replace_flag = false);
```
-----

## Notes

(any notes go here)

## Parameters
Parameter | In/Out | Definition
----- | ----- | -----
`C` | In/Out | An existing GraphBLAS matrix.  On input, the matrix provides values that may be accumulated with the result of the matrix product, or values that are merged with masked results. 
`Mask` | In  | An optional "write" mask (or mask view) that controls which results from this operation are stored into the output matrix `C`.  The mask dimensions must match thoese of the matrix `C`. If no masking is desired, pass `grb::no_mask` (or `grb::full_mask`).  To use the structure of a matrix as the mask use `grb::structure(Mask)`
`accum`  | In  | An optional accumulation binary operator.  If no accumulation is desired this should be `grb::no_accumulator`(?)
`op`   | In | A semiring containing a binary map operator and a commutative monoid operator for reduction.
`reduce` | In | A commutative monoid or a commutative binary operator with type restrictions(?)
`map`    | In | A binary operator
`A` | In | Fulfills `std::forward_iterator<value_type>`, with `operator*` returning `reference` [1]
`B` | In | `grb::matrix_reference<T, I>`
`outp` | In | `Hint`

## Type requirements

Method | Description
----- | -----
`CMatrixType` | Must meet the requirements of `MatrixView`(?)
`AMatrixType`, `BMatrixType` | Must meet the requirements of `ConstMatrixView`
`MaskType` | Must meet the requirements of `ConstMaskView` (or just `MaskView` if they are all const)
`AccumulatorType` | Must meet the requirements of `BinaryOperator` (is this a thing?)
`Semiring` | Must meet the requirements of `SemiringOperator` (is this a thing?)
`ReduceType` or `ReduceFn` | Must meet the requirements `CommutativeMonoid` (or must `Monoid` or `GraphBLASMonoid`?)
`MapType` or `MapFn` or `CombineFn` | Must meet the requirements of `BinaryOperator` (is this a thing?)


## Methods
Method | Description
----- | -----
`(constructor)` | Constructs matrix
`begin` | Returns iterator to beginning of container
`end` | Returns iterator to one past last element in container
`insert` | Insert elements
`insert_or_assign` | Inserts or assigns element

## Method Declarations
```cpp
template <typename T,
          typename I = std::size_t,
          typename Hint = grb::sparse,
          typename Allocator = std::allocator<T>>
class grb::matrix {

  matrix(grb::index<I> shape);
  template <grb::ranges::const_matrix_range R>
  matrix(R other);
  
  matrix();
  ~matrix();
  matrix(const csr_matrix&);
  matrix(csr_matrix&&);
  matrix& operator=(const csr_matrix&);
  matrix& operator=(csr_matrix&&);

  size_type size() const noexcept;
  grb::index<I> shape() const noexcept;

  iterator begin() noexcept;
  iterator end() noexcept;
  const_iterator begin() const noexcept;
  const_iterator end() const noexcept;
  
  template <typename InputIt>
  void insert(InputIt first, InputIt last);
  
  std::pair<iterator, bool> insert(value_type&& value);
  
  template <typename M>
  std::pair<iterator, bool> insert_or_assign(key_type k, M&& obj);
  
  iterator find(key_type key) noexcept;
  const_iterator find(key_type key) const noexcept;
};
```

## Comparison
Member Type | Value for `unordered_map` | Value for `grb::matrix` | Notes
---- | ---- | ---- | ----
`key_type` | `std::pair<I, I>` | `grb::index<I>` | `grb::index<I>` behaves like `std::pair<I, I>`, but also supports `operator[]`, which is v. convenient
`map_type` | `T` | `T` | Type of stored elements
`?` | `T` | `T` | What we call `map_type` in `grb::matrix`
`index_type` | `I` | `I` | Integral type used to store indices
`value_type` | `std::pair<const std::pair<I, I>, T>` | `grb::matrix_entry<T, I>` | `grb::matrix_entry<T, I>` behaves like `std::pair<const std::pair<I, I>, T>`, but adds some convenience functions
`reference` | `std::pair<const std::pair<I, I>, T>&` | `grb::matrix_reference<T, I>` | `grb::matrix_reference<T, I>` behaves like `std::pair<const std::pair<I, I>, T>&` (allows obtaining a reference to value, copies of indices)
`const_reference` | `const std::pair<const std::pair<I, I>, T>&` | `grb::matrix_reference<const T, I>` | `grb::matrix_reference<const T, I>` behaves like `const std::pair<const std::pair<I, I>, T>&` (allows obtaining a constant reference to value, copies of indices)

## Notes
[1] Iterator type may vary based on backend storage type. Most will likely provide `std::random_access_iterator`.  Dense and COO are `std::random_access_iterator`, as are CSR and COO, with the exception that pointer addition and subtraction are bound by *O(m)* and *O(n)*, respectively, although they are likely to be *O(1)*.

# Notes on grb::index
```cpp
template <typename T>
struct grb::index;
```

## Description
`grb::index` is a pair-like class that stores row and column indices associated with a matrix element.

`T` must fulfill the concept `std::integral`.

## Template Parameters
`T` - an integral type used to store indices.

## Member Types
Member Type | Definition
----- | -----
`index_type` | `T`, an integer type used to store matrix indices
`first_type`   | `T`, an integer type used to store matrix indices
`second_type`   | `T`, an integer type used to store matrix indices

## Member Objects
Member Name | Type
----- | -----
`first` | `T`
`second` | `T`

