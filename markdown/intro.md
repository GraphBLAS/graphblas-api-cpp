# Intro
The GraphBLAS standard defines a set of generalized matrix and vector operations based
on semiring algebraic structures.  These operations can be used to express a wide variety
of graph algorithms.  This specification document defines the C++ programming interface for the
GraphBLAS standard, referred to as the \emph{GraphBLAS C++ API (Application Programming Interface)}.
The GraphBLAS C++ API defines a collection of data structures, algorithms, views,
operators, and concepts for implementing graph algorithms.  These API components
are based around mathematical objects, such as matrices and vectors, and
operations, such as generalized matrix multiplication and element-wise operations.
The [GraphBLAS Math Specification](https://github.com/GraphBLAS/graphblas-api-math)
provides a complete specification of the mechanics of these structures and operations, and provides a rigorous mathematical definition of the operations
and data structures provided in this specification.

## Data Structures
This specification provides data structures for storing matrices and vectors.
These implement the matrix and vector range [concepts](#concepts) also defined
in this specification.

### Matrices
Matrices are two-dimensional collections of sparse values.  Each matrix has a
defined number of rows and columns, which define its \emph{shape}.  In addition,
each matrix has a defined number of \emph{stored values}, which are indices
inside the bounds of the matrix which actually contain scalar values.  A matrix
has a fixed \emph{scalar type}, which is the type of the stored values, as well
as an \emph{index type}, which is the type of the indices.

GraphBLAS matrices are sparse, consist of a well-defined set of stored values,
and have no implicit zero value for empty indices.  As such, operations may not
arbitrarily insert explicit zero values into the matrix, but must produce an
output with the exact set of values as specified by the GraphBLAS Math
Specification.

The GraphBLAS matrix data structure defined in this specification, `grb::matrix`,
provides mechanisms for creating, manipulating, and iterating through
GraphBLAS matrices.  It also includes a mechanism for influencing the storage
format through compile-time hints.  GraphBLAS operations that accept matrices
can be called with other types so long as they fulfill the GraphBLAS matrix concepts.

### Vectors
Vectors are one-dimensional collections of sparse values.  Each vector has a
defined number of indices, which defines its shape.  Similarly, it has a defined
number of stored stored values, which must lie at indices within its shape.  Its
scalar values have a fixed scalar type, and it has a fixed index type for storing
indices.  Vectors follow the same sparsity rules as matrices, and similarly
the GraphBLAS matrix concepts.

## Concepts
The GraphBLAS C++ Specification defines matrix and vector concepts.  These
define the interface that a type must support in order to be used by GraphBLAS
operations.  The intention is that data structures defined by other libraries
may be used in GraphBLAS operations so long as they define a small number of
customization points that perform insert, find, and iteration operations over
the matrix or vector.

### Version Conformance
A C++ GraphBLAS library should define the macro `GRAPHBLAS_CPP_VERSION` to indicate its
level of conformance with the GraphBLAS C++ API.  To indicate conformance with the
GraphBLAS 0.1a draft specification, a library should provide the macro `GRAPHBLAS_CPP_VERSION`
with a value greater than or equal to `202207L`.

#### Exposition Only
```cpp
// Define the `GRAPHBLAS_CPP_VERSION` macro to indicate
// conformance to the GraphBLAS 0.1 Draft Specification.
#define GRAPHBLAS_CPP_VERSION 202207L
```

This is Tim's new sentence.
