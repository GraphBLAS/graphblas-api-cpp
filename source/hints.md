# Sparse Storage Format Hints

This section defines compile-time hints that can be used to direct the storage format used to organize data inside GraphBLAS objects.  Storage hints can be used as optional template arguments to `grb::matrix`, `grb::vector`, as well as some API functions that return a matrix or vector.  These compile-time hints provide a mechanism for users to suggest to the GraphBLAS implementation which storage format might be most appropriate for a particular matrix.  However, these compile-time hints are indeed *hints* to the implementation and do not enforce any change in semantics to a matrix or vector data structure and do not require it to use any particular storage format.  GraphBLAS implementations are encouraged to document which storage formats they support, as well as how different hints will affect which storage formats are used.

### Example

```cpp
#include <grb/grb.hpp>

int main(int argc, char** argv) {
  // Create a matrix with the `dense` compile-time hint.
  // The implementation may choose to employ a dense storage format.
  grb::matrix<float, std::size_t, grb::dense> x({10, 10});

  // Create a matrix with the compile-time hint compose<sparse, row>.
  // A GraphBLAS implementation may choose to employ a compressed sparse row
  // storage format.
  grb::matrix<float, std::size_t, grb::compose<grb::sparse, grb::row>> y({10, 10});


  // No change in data structure semantics is implied by a hint.
  x[{2, 3}] = 12;
  x[{3, 6}] = 12;

  y[{6, 7}] = 1;
  y[{6, 7}] = 2.5;

  grb::print(x);
  grb::print(y);

  return 0;
}
```


## `grb::sparse`

```cpp
using sparse = /* undefined */;
```

Compile-time hint to suggest to the GraphBLAS implementation that a sparse or compressed storage format is appropriate.

## `grb::dense`

```cpp
using dense = /* undefined */;
```

Compile-time hint to suggest to the GraphBLAS implementation that a dense storage format is appropriate.

## `grb::row`

```cpp
using row = /* undefined */;
```

Compile-time hint to suggest to the GraphBLAS implementation that a row-major storage format is appropriate.

## `grb::column`

```cpp
using column = /* undefined */;
```

Compile-time hint to suggest to the GraphBLAS implementation that a column-major storage format is appropriate.

## `grb::compose`

```cpp
template <typename... Hints>
using compose = /* undefined */;
```

Type alias used to combine multiple compile-time hints together.
