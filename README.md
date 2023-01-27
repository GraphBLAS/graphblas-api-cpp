# GraphBLAS C++ Specification

Click here for the [most recent HTML draft](https://graphblas.org/graphblas-api-cpp) and [most recent PDF draft](https://github.com/GraphBLAS/graphblas-api-cpp/actions/workflows/build-spec.yml).

The currently under development GraphBLAS C++ API aims to provide a C++ API for implementing graph algorithms in the language of linear algebra, and is part of the larger [GraphBLAS](https://graphblas.github.io/) project.  The API provides data structures for storing matrices and vectors, as well as a collection of algorithms, such as generalized matrix multiplication, that can be used with custom or pre-defined operators, monoids, and semirings.

The standard document itself can be found in the folder [markdown](https://github.com/GraphBLAS/graphblas-api-cpp/tree/master/markdown),
while minutes for meetings of the GraphBLAS C++ API subcommittee can be found in the folder [minutes](https://github.com/GraphBLAS/graphblas-api-cpp/tree/master/minutes).

## Brief API Example
```C++
  // Create a GraphBLAS matrix of size 128 x 128.
  grb::matrix<float> x({128, 128});
  
  // Write to elements along the diagonal.
  for (size_t i = 0; i < 128; i++) {
    x[{i, i}] = i*i;
  }
  
  float sum = 0;
  // Sum up all the elements stored in the matrix.
  for (auto&& [index, value] : x) {
    sum += value;
  }
```


## Libraries

* [rgri](https://github.com/BenBrock/rgri) is being developed as a reference implementation alongside the API.
* [GBTL](https://github.com/cmu-sei/gbtl) has heavily influenced the development of the C++ API, and is also being updated alongside the development of the API.
