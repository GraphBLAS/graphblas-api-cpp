# GraphBLAS C++ API Working Subgroup Meeting Minutes - July 8, 2021

## Attendees
- [X] Ben Brock
- [X] Scott McMillan

## Agenda

## Minutes

- Discussed progress on the spec document.  Ben is working on (1) named requirements for binary operators, monoids and (2) the matrix data structure.  Ben put up documentation for his [RGRI C++ stuff](https://github.com/BenBrock/rgri).

- Scott is working on writing up MXM in the spec.

- Discussed GRB hints.  Reached a consensus that hints should likely include `grb::sparse`, `grb::dense`, `grb::row` and `grb::column`, which can be combined to hint at various backend data structures, but do not guarantee anything.  In order to avoid messiness, they can be combined using a `grb::compose` struct (e.g. `grb::compose<grb::sparse, grb::row>`), which will then provide access to all the hints used in the backend like the parameter pack data structure in [Ben's futar code](https://github.com/BenBrock/futar/blob/master/futar/detail/detail.hpp#L46).  (This underlying template behavior is NOT defined in the spec, just the hints and the API for `grb::compose`).

- Discussed the issue about index parameters.  There are at most two separate indices, one used to reference element indices (so it will limit the *dimension* of the matrix) and one used to reference locations in data structures (so that will limit the *number of stored values*).
