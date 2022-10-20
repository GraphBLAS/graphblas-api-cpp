# Basic Concepts

GraphBLAS defines a collection of objects, functions, and concepts to facilitate
the implementation of graph algorithms.  These programming facilities are further
separated into _GraphBLAS containers_, which include matrices and vectors,
_GraphBLAS operations_, which are algorithms such as matrix-vector multiplication that
operate over GraphBLAS containers, and _GraphBLAS operators_, which are binary and unary operators
that operate over scalar elements that may be held in a container.
The C++ API also defines a series of _concepts_ defining the interface a container
or operator must fulfill in order to to be used with a particular operation, as well
as _views_, which provide lazily evaluated, mutated views of a GraphBLAS object.

## GraphBLAS Containers
GraphBLAS containers, which include matrices and vectors, are sparse data
structures holding a collection of stored scalar values.  Each GraphBLAS container
has a shape, which defines the dimension(s) of the object.  Stored values can be
inserted at indices within the dimensions of the object.  Since GraphBLAS containers are
sparse, they keep explicit track of which index locations in the object hold
stored values.  There is no implied zero value associated with a GraphBLAS
container, since the annhilator value will change from operation to operation,
and the insertion of explicit "zeros" could cause incorrect results.  As such,
no GraphBLAS operation will arbitrarily insert explicit zeros.  In the GraphBLAS
C++ API, each container has associated with it a scalar type, which is the type
of the stored scalar values, as well as an index type, which is the type used to
indicate the locations of stored values, as well as the matrix shape.

___TODO: be more specific here. Could use some help from math spec?___

### Matrices
GraphBLAS matrices are two-dimensional sparse arrays.  As previously discussed,
they have a scalar type, which defines the type of scalar values stored inside
the matrix, as well as an index type, which is used to refer to the row and column
index of each stored value.  For a matrix type `A`, these types can be retrieved
using the expression `grb::matrix_scalar_t<A>` to retrieve the scalar type and
  `grb::matrix_index_t<A>` to retrieve the index type.
In the GraphBLAS C++ API, matrices are associative arrays similar to
instantiations of `std::unordered_map`.  They map keys, which are row and column
indices, to values, which are the stored scalar values.  Like the C++ standard
library's associative containers, GraphBLAS matrices are ranges, and iterating
through a GraphBLAS matrix reveals a collection of tuples, with each tuple
holding a key and value.  The key is a tuple-like type holding the row and column
indices, and the value is the stored scalar value.  The row and column are provided
only as const references, while the value may be mutated.
Matrices also support insert, assign, and find operations to write or read to a
particular location in the matrix.

### Vectors
GraphBLAS similars are analogous to matrices, except that they are only one-dimensional
sparse arrays.  They hold a scalar type, which defines the scalar values stored
inside the vector, as well as an index type, which holds the index of an element
within the vector.  For a vector `V`, these types can be retrieved with the
expressions `grb::vector_scalar_t<V>` and `grb::vector_index_t<V>`.
Like matrices, vectors are associative arrays, except that their key values are
a single index type element, and not a tuple.  Like matrices, vectors are ranges,
with the value type being a tuple holding the index type and scalar type, with
only the scalar type being mutable if the vector is non-const.  Individual elements
can be modified using insert, assign, and find.

