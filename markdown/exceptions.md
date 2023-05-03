## Exceptions and Error Handling

Exceptions may be thrown to indicate error conditions.  A number of exceptions
are defined which will be thrown in different error conditions.

### GraphBLAS-Defined Exceptions
- `grb::out_of_range` is thrown if an index is provided which lies outside the
  dimensions of the matrix, or if a value is not present at the index.

- `grb::matrix_io::file_error` is thrown if a file cannot be read.

- `grb::invalid_argument` is thrown if objects' dimensions are incompatible.

### Other Exceptions
- Some functions and methods may allocate temporary memory.  These may throw

`std::bad_alloc`.
- Some functions and methods may allocate memory using a user-provided allocator, which may throw.

- Some functions and methods accept user-defined binary or unary operators.  These may throw.
