# Matrix-matrix multiplication: `mxm`

_TODO: this should probably be brought under "operations" as a header, to align with the way I'm writing multiply. Basically all the headings would need to go down one level. I'll take a look at this after I've worked out more of multiply._

Multiplies two GraphBLAS matrices using the operators and identity defined by a GraphBLAS semiring. An optional accumulator and write mask can also be specified. The result is stored in third GraphBLAS matrix.

```cpp
    // Attempt at using the concepts
    // First some dependencies (these go somewhere else)
    template <typename T, typename U>
    U no_accumulate(T&& t, U&& u) {    // move definition somewhere else
        return u;
    }

    template <typename Matrix>
    using matrix_scalar_type_t = typename std::remove_cvref_t<Matrix>::scalar_type;

    template <typename BinaryFn, typename AMat, typename BMat = AMat>
    using grb::binop_result_type_t = decltype(
        std::declval<BinaryFn>()(grb::matrix_scalar_type_t<AMat>,
                                 grb::matrix_scalar_type_t<BMat>));

    // Binary Operator overload
    template<MatrixRange                                                 A,
             MatrixRange                                                 B,
             BinaryOperator<grb::matrix_scalar_type_t<A>,
                            grb::matrix_scalar_type_t<B>>                Combine,
             BinaryOperator<grb::binop_result_type_t<Combine, A, B>,
                            grb::binop_result_type_t<Combine, A, B>,
                            grb::binop_result_type_t<Combine, A, B>>     Reduce,
             BinaryOperator<grb::matrix_scalar_type_t<C>,
                            grb::binop_result_type<
                               Reduce,
                               grb::binop_result_type_t<Combine, A, B>,
                               grb::binop_result_type_t<Combine, A, B>>,
                            grb::matrix_value_type_t<C>>                 Accumulate = grb::no_accumulate,
             MutableMatrixRange<
                 grb::binop_result_type_t<
                     Accumulate,
                     grb::matrix_scalar_type_t<C>,
                     grb::binop_result_type<
                         Reduce,
                         grb::binop_result_type_t<Combine, A, B>,
                         grb::binop_result_type_t<Combine, A, B>>>       C,
             MaskMatrixRange                                             Mask = grb::no_mask>   // or grb::full_mask
    void mxm(C             &c,  // use &&?
             A            &&a,
             B            &&b,
             Reduce       &&reduce,
             Combine      &&combine,
             Accumulate   &&accum   = Accumulator(),
             Mask         &&m       = Mask(),
             bool           replace = false);      // or use an enumerated type?

```


```cpp
    // Binary Operator overload
    template<MatrixView       CMatrixType,
             BinaryOp         ReduceType,
             BinaryOp         CombineType,
             ConstMatrixView  AMatrixType,
             ConstMatrixView  BMatrixType,
             BinaryOp         AccumulatorType = std::no_accumulate,
             MaskMatrixView   MaskType = std::no_mask>      // instead of full_mask
    void mxm(CMatrixType            &C,                     // use &&?
             ReduceType            &&reduce,                // In general, what is the style
             CombineType           &&combine,               // to document [IN] vs. [IN,OUT]
             AMatrixType     const &&A,                     // intentions
             BMatrixType     const &&B,
             AccumulatorType       &&accum = AccumulatorType(),
             MaskType        const &&Mask = MaskType(),
             bool                    replace = false);      // or use an enumerated type?
```

-----


```cpp
    // Semiring operator overload
    template<MatrixView       CMatrixType,
             Semiring         SemiringType,
             ConstMatrixView  AMatrixType,
             ConstMatrixView  BMatrixType,
             BinaryOp         AccumulatorType = std::no_accumulate,
             MaskMatrixView   MaskType = std::no_mask>      // instead of full_mask
    void mxm(CMatrixType            &C,
             SemiringType          &&op,
             AMatrixType     const &&A,
             BMatrixType     const &&B,
             AccumulatorType       &&accum = AccumulatorType(),
             MaskType        const &&Mask = MaskType(),
             bool                    replace = false);      // or use an enumerated type?
```

-----

```cpp
    // Overload that returns output
    template<ConstMatrixView AMatrixType,
             ConstMatrixView BMatrixType,
             BinaryOp        ReduceType  = std::plus<>,       // default? yes or no
             BinaryOp        CombineType = std::multiplies<>, // default? yes or no;
             MaskMatrixView  MaskType    = std::no_mask>      // instead of full_mask?
    auto mxm(AMatrixType     &&A,                             // mxm(..) or multiply(..)?
             BMatrixType     &&B,
             ReduceType      &&reduce   = ReduceType(),
             CombineType     &&combine  = CombinType(),       // or CombineFn
             MaskType        &&Mask     = MaskType(),         // or grb::no_mask()
             bool              replace  = false);             // or use an enumerated type?
```

-----

## Notes

(any notes go here)

TODO list
- Overload on operator: Should we have two overloads: pair of binary operators AND a semiring? (vote against latter)
- Function name: Should the overload that does not have an in/out parameter (and no accumulator) also be called `mxm`? RGRI calls it `multiply`
  - mxm is legacy (known), C++ allows overloading
- Mask: Should we move mask to end so that it can be defaulted?
  - Pro: belongs with replace flag
  - Pro: matches rgri parameter order for multiply
  - is `no_mask` the best default name?
- replace: Should `replace` flag be a boolean or enumerated type
- Times: Tim does not like `Combine`.  What should it be called
- Plus:  Scott likes `Reduce`...Tim does not.
- Parameter Order:  Should we move operators to after the input containers or keep before
  - Currently the third overload is not a consistent order with either of the first two.
- Accumulator
  - Should we move the optional accumulator to the end as well so that it can be defaulted as well?
  - is `no_accumulate` the best default name?
- Type and concept naming conventions
  - Type: MatrixType vs matrix_t
  - Concept: MatrixView vs matrix_view vs matrix_view_c

## Parameters
Parameter | In/Out | Definition
----- | ----- | -----
`C` | In/Out | An existing GraphBLAS matrix.  On input, the matrix provides values that may be accumulated with the result of the matrix product, or values that are merged with masked results. 
`op`   | In | A semiring containing a binary map operator and a commutative monoid operator for reduction.
`reduce` | In | A commutative monoid or a commutative binary operator with type restrictions(?) for reduction. The signature of the function should be equivalent to the following: <br> `T fn(T const &c1, T const &c2);`
`combine` | In | A binary times/multiplies/map operator. The signature of the function should be equivalent to the following: <br> `T fn(U const &a, V const &b);`
`A` | In | The left-hand input matrix (view, const).  Using the transpose of the matrix may be accomplished by passing `grb::transpose(A)`.
`B` | In | The right-hand input matrix (view, const).  Using the transpose of the matrix may be accomplished by passing `grb::transpose(B)`.
`accum`  | In  | An optional accumulation binary operator.  If assignment rather than accumulation is desired, pass `grb::no_accumulator`(`grb::assign`?)
`Mask` | In  | An optional "write" mask (or mask view) that controls which results from this operation are stored into the output matrix `C`.  The mask dimensions must match thoese of the matrix `C`. If no masking is desired, pass `grb::no_mask` (or `grb::full_mask`).  To use the structure of a matrix as the mask, call with `grb::structure(Mask)`.  To complement the logic of the mask, call with `grb::complement(Mask)`
`replace` | In | If a non-full mask is specified this parameter controls the prior contents of C that is 'masked out'.  If `true` is specified the elements in `C` are cleared (replace semantics); otherwise `false` leaves these elements unmodified (merge semantics).

### Type requirements

Method | Description
----- | -----
`CMatrixType`/`C_matrix_t` | Must meet the requirements of `MatrixView`/`matrix_c` (?)
`AMatrixType`/`A_matrix_t`, `BMatrixType`/`B_matrix_t` | Must meet the requirements of `ConstMatrixView`/`const_matrix_view_c`
`MaskType`/`mask_t` | Must meet the requirements of `MaskMatrixView`/`mask_matrix_view_c` (they are all const) [Note: the elements of the mask view must be convertible to bool.]
`AccumulatorType`/`accum_op_t` | Must meet the requirements of `BinaryOp`/`binary_op_c` 
`SemiringType`/`semiring_op_t` | Must meet the requirements of `SemiringOp`/`semiring_op_c` (is this a thing?)
`ReduceType` or `ReduceFn`/`reduce_op_t` | Must meet the requirements `CommutativeMonoid`/`commutative_monoid_c` (or must `Monoid`/`monoid_c` or `GraphBLASMonoid`/`graphblas_monoid_c`?)
`MapType` or `MapFn` or `CombineType` / `combine_op_t` | Must meet the requirements of `BinaryOp`/`binary_op_c` (is this a thing?)


## Return value

The first two overloads of `mxm` do not have a return value.  In blocking mode, the operation has completed successfully on return. In non-blocking mode, this indicates that the compatibility tests on dimensions \scott{and domains for the input arguments passed successfully}. Either way, output matrix {\sf C} is ready to be used in the next method of the sequence.

The return value of (third) `mxm` (or `multiply`) variant is a GraphBLAS matrix of dimensions `A.nrows() x B.ncols()`. The scalar type is the output type of the `reduce` operator.

## Exceptions

- `grb::bad_alloc` any allocation failure (is there `std::bad_alloc` instead?)
- `grb::panic_error` (execution error, `grb::runtime_error`) unknown internal error
- `grb::invalid_object` (execution error, `grb::runtime_error`) any execution mode; whenever any of the graphblas objects is in an invalid state.
- `grb::dimension_mismatch` (API error, logic error) mask or matrix dimensions are incompatible.

## Description

Does the C++ specification need to have a long, largely duplicative description of what can be found in the C API description?

Carries out matrix multiplication using reduce and combine operators or a semiring (containing this pair) of in put matrices A and B, optionally accumulates using the accum operator with the output matrix C, and writes this results back into the C matrix under control of the optional write mask and replace flag.  ...according to the math provided in the math specification.

## Examples

```c++
        grb::Matrix A<float>({5, 10});
        grb::Matrix B<float>({10, 5});
        grb::Matrix C5<float>({5, 5});
        grb::Matrix M5<bool>({5, 5});
        grb::Matrix C10<float>({10, 10});
        grb::Matrix M10<bool>({10, 10});

        // ... fill the matrices

        // using no matrix views
        grb::mxm(C5, grb::NoAccumulate{} 
                 grb::PlusTimesSemiring<float>{}, A, B,
                 M5, false); //grb::MERGE);
        
        // using all possible matrix views
        grb::mxm(C10, grb::NoAccumulate{}, 
                 grb::PlusTimesSemiring<float>{}, grb::transpose(A), grb::transpose(B),
                 grb::complement(grb::structure(M10)), true); //grb::REPLACE);

        // the alternate map-reduce form
        // using all possible matrix views
        grb::mxm(C10, grb::NoAccumulate{}, 
                 grb::Plus<float>{}, grb::Times<float>{},
                 grb::transpose(A), grb::transpose(B),
                 grb::complement(grb::structure(M10)), true); // grb::REPLACE);

        // the alternate map-reduce form using lambdas
        // using all possible matrix views
        grb::mxm(C10, grb::NoAccumulate{}, 
                 [&](auto &&c1, auto &&c2) { return c1 + c2; }, // reduce  (is && right?)
                 [&](auto &&a,  auto &&b)  { return a * b; },   // combine (is && right?)
                 grb::transpose(A), grb::transpose(B),
                 grb::complement(grb::structure(M10)), true); //grb::REPLACE);

        // multiply alternative
        auto C = grb::mxm(grb::transpose(A), grb::transpose(B), 
                          [&](auto const &c1, auto const &c2) {return c1+c2;}, // reducer
                          [&](auto const &a,  auto const &b)  {return a * b;}, // mapper
                          grb::complement(grb::structure(M10)), true); //grb::REPLACE);
```

