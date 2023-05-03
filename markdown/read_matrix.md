## `read_matrix`


#### Matrix Times Matrix
```cpp

template <typename T,
          std::integral I = std::size_t,
          typename Hint = grb::sparse,
          typename Allocator = std::allocator<T>>
grb::matrix<T, I, Hint, Allocator>
read_matrix(std::string file_path);
```

Constructs a new GraphBLAS matrix based on the contents of a file.

## Template Parameters
`T` - type of scalar values stored in matrix

`I` - type of matrix indices

`Hint` - compile-time hint for backend storage format.

`Allocator` - allocator type

### Parameters
`file_path` - string holding the file path of the matrix to be read

### Return Value

Returns a GraphBLAS matrix whose dimensions and contents correspond to the
file located at `file_path`.

### Complexity
Complexity is implementation-defined.

### Exceptions
- If the file at `file_path` cannot be read, the exception `grb::matrix_io::file_error` is thrown.
- If the file at `file_path` is recognized as an unsupported format, the exception `grb::matrix_io::unsupported_file_format` is thrown.
- Calls to `Allocator::allocate` may throw.

### Notes
GraphBLAS implementations must define the file formats that they support.  Implementations are strongly encouraged to support the MatrixMarket format.

### Example
