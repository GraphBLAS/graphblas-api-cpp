# Intro
The GraphBLAS standard defines a set of generalized matrix and vector operations based
on semiring algebraic structures.  These operations can be used to express a wide variety
of graph algorithms.  This specification document defines the C++ programming interface for the
GraphBLAS standard, referred to as the \emph{GraphBLAS C++ API (Application Programming Interface)}.
The GraphBLAS C++ API defines a collection of data structures, algorithms, views,
operators, and concepts for implementing graph algorithms.  These API components
are based around a mathematical objects, such as matrices and vectors, and
operations, such as generalized matrix multiplication and element-wise operations.
The [GraphBLAS Math Specification](https://github.com/GraphBLAS/graphblas-api-math)
provides a complete specification of the mechanics of these structures and operations.

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