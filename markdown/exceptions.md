## Error Handling and Exceptions

Various exceptions are thrown to indicate a variety of error conditions.  The GraphBLAS API defines its own exceptions that are derived from various Standard Library exceptions.  This section lists all of the exceptions required by the API.

Any operation could throw exceptions if the operators used by the operation can throw exceptions.

Any function or method that must not throw an exception shall be declared `noexcept`.

- Allocation errors: `std::bad_alloc` is thrown anytime allocation fails
- Accessing a value at a location that has no stored value: currently `grb::out_of_range` (or a more C-API-like name:`grb::no_value`), could be related to `std::out_of_range`
- `grb::matrix_io::file_error` could be related to `std::runtime_error` or `std::system_error`
- `grb::invalid_argument`  is thrown for incompatible dimensions (this is `DIMENSION_MISMATCH` in the C API), consider `grb::invalid_dimensions`)

Should we require no_throw on operators??  Probably not because the operator might allocate memory?

(Note: do we allow implementations to define their own exceptions)

Will GraphBLAS API Spec allow implementation-defined exceptions?  Must implementator define the conditions under which any of these additional exceptions will be thrown?  Or will implementation-defined exceptions be treated like any other `std::exception` (i.e. treat it like an unrecoverable PANIC condition)?

What guarantees?  Input parameters are modified and output parameters are probably in an undefined state.

### Notes on C API errors
#### Informational return values

- `SUCCESS`: not necessary with exceptions
- `NO_VALUE`: happens in extractElement() method when providing a transparent destination scalar and no stored value. Using `grb::out_of_range` exception. The justification for changing informational return with exception is the consistency with STL container `at()` method behaviour.

#### API errors
- `UNINITIALIZED_OBJECT`: not necessary with RAII philosophy
- `NULL_POINTER`: not necessary, no pointers used in C++ API
- `INVALID_VALUE`: 
    - used with incorrect enum values (not necessary in C++)
    - used if a dimension is defined as 0 (like in vector or matrix construction or resize, (do we need this?)
    - duplicate indices during build (do we need this?).
- `INVALID_INDEX`: This is specifically for indices that are outside the defined dimensions (for `setElement()`, `extractElement()`, `removeElement()`).  Does this overload with `NO_VALUE`?
- `DOMAIN_MISMATCH`: not applicable in C++...if it compiles there is no mismatch.
- `OUTPUT_NOT_EMPTY`: was used when trying to `build` with a container that is not empty....what should C++ do?
- `NOT_IMPLEMENTED`: ???

### Execution Errors
- `PANIC` - do we need this?
- `OUT_OF_MEMORY`: using `std::bad_alloc`... why not `grb::bad_alloc`?  Because allocators not part of GraphBLAS spec.
- `INSUFFICIENT_SPACE`: ???
- `INVALID_OBJECT`: The requires a discussion of exception quarantees.  I.e. what is the state of an output object when an exception is thrown during an operation it was called with? This is also complicated by non-blocking mode which is deferred for now.
- `INDEX_OUT_OF_BOUNDS`: `grb::out_of_range`  (This is overloaded use...for two different meanings)
- `EMPTY_OBJECT`: (only called in reduce to scalar...does C++ API side step this)
- 