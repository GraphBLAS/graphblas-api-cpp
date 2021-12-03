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
    auto multiply(AMatrixType&&     A,
                  BMatrixType&&     B,
                  ReduceType&&      reduce = ReduceType(),
                  MapType&&         map    = MapType(),        // or CombineFn
                  MaskType&&        Mask   = grb::full_mask(), // or grb::no_mask()
                  OutputControlEnum outp   = MERGE);           // bool replace = false);
```

-----

## Notes

(any notes go here)

## Parameters
Parameter | In/Out | Definition
----- | ----- | -----
`C` | In/Out | An existing GraphBLAS matrix.  On input, the matrix provides values that may be accumulated with the result of the matrix product, or values that are merged with masked results. 
`Mask` | In  | An optional "write" mask (or mask view) that controls which results from this operation are stored into the output matrix `C`.  The mask dimensions must match thoese of the matrix `C`. If no masking is desired, pass `grb::no_mask` (or `grb::full_mask`).  To use the structure of a matrix as the mask, call with `grb::structure(Mask)`.  To complement the logic of the mask, call with `grb::complement(Mask)`
`accum`  | In  | An optional accumulation binary operator.  If assignment rather than accumulation is desired, pass `grb::no_accumulator`(`grb::assign`?)
`op`   | In | A semiring containing a binary map operator and a commutative monoid operator for reduction.
`reduce` | In | A commutative monoid or a commutative binary operator with type restrictions(?) for reduction. The signature of the function should be equivalent to the following: <br> `T fn(T const &c1, T const &c2);`
`map`    | In | A binary map operator. The signature of the function should be equivalent to the following: <br> `T fn(U const &a, V const &b);`
`A` | In | The left-hand input matrix (view, const).  Using the transpose of the matrix may be accomplished by passing `grb::transpose(A)`.
`B` | In | The right-hand input matrix (view, const).  Using the transpose of the matrix may be accomplished by passing `grb::transpose(B)`.
`outp` | In | If a non-full mask is specified this parameter controls the prior contents of C that is 'masked out'.  If `grb::REPLACE` is specified the elements in `C` are cleared; otherwise `grb::MERGE` leaves these elements unmodified.

### Type requirements

Method | Description
----- | -----
`CMatrixType` | Must meet the requirements of `MatrixView`(?)
`AMatrixType`, `BMatrixType` | Must meet the requirements of `ConstMatrixView`
`MaskType` | Must meet the requirements of `ConstMaskView` (or just `MaskView` if they are all const) [Note: the elements of the mask view must be convertible to bool.]
`AccumulatorType` | Must meet the requirements of `BinaryOperator` (is this a thing?)
`Semiring` | Must meet the requirements of `SemiringOperator` (is this a thing?)
`ReduceType` or `ReduceFn` | Must meet the requirements `CommutativeMonoid` (or must `Monoid` or `GraphBLASMonoid`?)
`MapType` or `MapFn` or `CombineFn` | Must meet the requirements of `BinaryOperator` (is this a thing?)

## Return value

`mxm` does not have a return value.  In blocking mode, the operation has completed successfully on return. In non-blocking mode, this indicates that the compatibility tests on dimensions \scott{and domains for the input arguments passed successfully}. Either way, output matrix {\sf C} is ready to be used in the next method of the sequence.

The return value of `multiply` variant is a GraphBLAS matrix of dimensions `A.nrows() x B.ncols()`. The scalar type is the output type of the `reduce` operator.

## Exceptions

- `grb::bad_alloc` any allocation failure (is there `std::bad_alloc` instead?)
- `grb::panic_error` (execution error, `grb::runtime_error`) unknown internal error
- `grb::invalid_object` (execution error, `grb::runtime_error`) any execution mode; whenever any of the graphblas objects is in an invalid state.
- `grb::dimension_mismatch` (API error, logic error) mask or matrix dimensions are incompatible.

## Description

Does the C++ specification need to have a long, largely duplicative description of what can be found in the C API description?

## Example

```c++
        grb::Matrix A<float>({5, 10});
        grb::Matrix B<float>({5, 10});
        grb::Matrix C<float>({5, 5});
        grb::Matrix M<bool>({5, 5});
        // ...
        grb::mxm(C, M, grb::NoAccumulate(), 
                 grb::PlusTimesSemiring<float>(), A, B,
                 grb::MERGE);
        // ...
        // using all possible matrix views
        grb::mxm(C, grb::complement(grb::structure(M)), grb::NoAccumulate(), 
                 grb::PlusTimesSemiring<float>(), grb::transpose(A), grb::transpose(B),
                 grb::REPLACE);

        // the alternate map-reduce form
        // using all possible matrix views
        grb::mxm(C, grb::complement(grb::structure(M)), grb::NoAccumulate(), 
                 grb::Plus<float>(), grb::Times<float>(),
                 grb::transpose(A), grb::transpose(B),
                 grb::REPLACE);

        // the alternate map-reduce form using lambdas
        // using all possible matrix views
        grb::mxm(C, grb::complement(grb::structure(M)), grb::NoAccumulate(), 
                 [&](auto const &c1, auto const &c2) { return c1 + c2; }, // reducer
                 [&](auto const &a,  auto const &b)  { return a * b; },   // mapper
                 grb::transpose(A), grb::transpose(B),
                 grb::REPLACE);

        // multiply alternative
        auto C = grb::multiply(A, grb::transpose(B), 
                               [&](auto const &c1, auto const &c2) {return c1+c2;}, // reducer
                               [&](auto const &a,  auto const &b)  {return a * b;}, // mapper
                               grb::complement(grb::structure(M)));
```

