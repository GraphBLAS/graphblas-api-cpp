# Notes on grb::matrix design

```cpp
template <typename T,
          typename I = std::size_t,
          typename Allocator = std::allocator<T>>
class grb::matrix;
```

## Member Types
Member Type | Definition
----- | -----
`element_type` | `T`, the type of elements stored in the matrix
`index_type`   | `I`, an integer type used to store matrix indices
`value_type`   | `grb::matrix_element<T, I>`, a tuple-like type storing copies of the indices and a reference to the stored element
`size_type`    | A large unsigned integer type, usually `std::size_t`
`difference_type` | A large signed integer type, usually `std::ptrdiff_t`
`allocator_type` | `Allocator`
`iterator` | An object fulfilling the concept `std::forward_iterator<value_type>` [1]
`const_iterator` | An object fulfilling the concept `std::forward_iterator<const value_type>` [1]

## Comparison
Member Type | Value for `unordered_map` | Value for `grb::matrix` | Notes
---- | ---- | ---- | ----
`key_type` | `std::pair<I, I>` | `grb::index<I>` | `grb::index<I>` behaves like `std::pair<I>`, but also supports `operator[]`, which is v. convenient
`map_type` | `T` | `T` | The stored element
`element_type` | `T` | `T` | What we call `map_type` in `grb::matrix`
`index_type` | `I` | `I` | Integral type used to store indices
`value_type` | `std::pair<const std::pair<I, I>, T>` | `grb::matrix_entry<T, I>`

## Notes
[1] Iterator type may vary based on backend storage type. Most will likely provide `std::random_access_iterator`.  Dense and COO are `std::random_access_iterator`, as are CSR and COO, with the exception that pointer addition and subtraction are bound by *O(m)* and *O(n)*, respectively, although they are likely to be *O(1)*.
