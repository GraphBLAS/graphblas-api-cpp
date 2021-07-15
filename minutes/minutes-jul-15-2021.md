# GraphBLAS C++ API Working Subgroup Meeting Minutes - July 15, 2021

## Attendees
- [X] Ben Brock
- [X] Scott McMillan

## Agenda
Discuss Scott's draft of mxm, discuss Ben's draft of bin op, monoid, and matrix.

## Minutes

- Went over Scott's mxm, Ben's draft of binop and monoid, matrix.

- Action item for Scott: take a look at cppreference's `std::transform` [here](https://en.cppreference.com/w/cpp/algorithm/transform).

- Action item for Ben: flesh out matrix, as well as named requirements for MatrixReference and MatrixIterator.

```c++
  // Get a reference to matrix element {12, 12}
  // grb::matrix<float> matrix = ...;
  auto ref = matrix[{12, 12}];

  float value = ref;
  ref = 12.0f;

  matrix[{12, 12}] = 12;
  float value = matrix[{13, 12}];

  grb::index_t index = matrix[{12, 12}];

  grb::index_t can be converted to std::tuple

  auto [i, j] = ref;

  auto [i, j, v] = ref;

  std::transform(matrix.begin(), matrix.end(), [](auto i, auto j, auto v) {

  std::reduce(matrix.begin(), matrix.end());

```
