# Intro
The GraphBLAS standard defines a set of generalized matrix and vector operations based
on semiring algebraic structures.  These operations can be used to expressed a variety
of graph algorithms.  This document defines the C++ programming interface for the
GraphBLAS standard.  We refer to this as the \emph{GraphBLAS C++ API (Application Programming Interface)}.
The GraphBLAS C++ API defines a collection of data structures, algorithms, views, arithmetic operators,
and concepts for implementing graph algorithms.

### Version Conformance
A GraphBLAS library should define the macro `GRAPHBLAS_CPP_VERSION` to indicate its
level of conformance with the GraphBLAS C++ API.  To indicate conformance with the
GraphBLAS 0.1a draft specification, a library should provide the macro `GRAPHBLAS_CPP_VERSION`
with a value greater than or equal to `202207L`.

#### Exposition Only
```cpp
// Define the `GRAPHBLAS_CPP_VERSION` macro to indicate
// conformance to the GraphBLAS 0.1 Draft Specification.
#define GRAPHBLAS_CPP_VERSION 202207L
```