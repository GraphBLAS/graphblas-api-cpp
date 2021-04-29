# GraphBLAS C++ API Working Subgroup Meeting Minutes - April 29, 2021

## Attendees
- [X] Ben Brock
- [X] Scott McMillan

## Agenda

- Briefly discuss Matrix / Vector API drafts in standard document.

- Discuss API for mxm

## Minutes

- Went over `grb::matrix` and `grb::vector` classes as implemented, discussing several issues.

1. Currently, we impose the limit that the number of stored values must be strictly less than `std::numeric_limits<index_type>::max()`, or else undefined behavior may occur (e.g. `index_type` must be able to reference all stored values).  In addition, we require that `std::max(shape[0], shape[1]) < std::numeric_limits<index_type>::max()` (The indices must fit in the index type. This one is totally unavoidable.).  At an implementation level, this means that for types like CSR where one array refers to indices in the stored values array and one directly contains indices, both will contain values of type `index_type`.  In cases where nnz >> n, it may be desired to use a larger type only for the arrays which refer to locations in the values array (e.g. rowptr in CSR), while using a smaller type for values that contain indices (e.g. colind in CSR).  We could do this by adding an extra template parameter or simply always using `std::size_t` for arrays that point to stored values.  The second one seems like the most consistent with C++ STL conatiners, since they guarantee (from an indices perspective) that they can hold up to `std::size_t` values.  However, this has the possible disadvantage that it still requires the underlying backend to support operations where different index types are used at the same time.  This is supported by at least one industry-standard sparse matrix libraries (like CuSPARSE), but not supported by many others (MKL, IBM's ESSL).  It seems dangerous to preclude from using MKL as a backend from the start.

2. `grb::matrix<...>::reference` is a valid C++ reference to `value_type`, where `value_type` is the type of the stored value.  This means it has a conversion operator to `value_type` (allows reading from value) and an assignment operator to `value_type` (allows writing to the value).  However, in addition, you can call the `index` function to return the index of the nonzero.  There is also a conversion operator to `grb::index_t`, which allows retrieving the indices with a statement like `grb::index_t index = *iterator`.  This is somewhat nonstandard, and presents a ambiguity issue if we are to make the index type of `grb::vector` scalar.
  - Scott suggested that we should use iterator adaptors to resolve this issue.  Scott will provide details on this in the next meeting.
  - Ben suggests that the most "C++" way to solve this would be modifying the `value_type` to be an `std::tuple` include the indices, as in `unordered_map`, but this would make the API significantly more annoying to use.
  - There is actually some precedent for augmenting iterators with access to indices, in Eigen [https://gallery.rcpp.org/articles/sparse-iterators/].  So this strategy of an "augmented reference" may not be that unorthodox.  Ben feels strongly that the current user syntax is good, and we should try to maintain it.

3. If we choose to implement a non-blocking mode, we would likely do so using `future` objects that are returned instead of the defaults.  (e.g. `future<reference> operator[](grb::index_t)`)  With futures, we would need to decide what errors would be thrown on function invocation and what might be thrown from inside the future (presumably on calling `wait` or `get`).

4. We discussed `mxm`.  There are a *lot* of mask variations, so this very well may require a descriptor.

## TODO

- Ben will implement a draft of `mxv` for next time.
- Scott will do some research about iterator adaptors for accessing indices.
- Both will think about possible alternatives to using a descriptor in `mxm`.
