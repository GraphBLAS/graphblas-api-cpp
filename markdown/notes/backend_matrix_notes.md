# Notes on grb::csr_matrix design

## *WARNING* These notes are specific to the rgri backend implementation

```cpp
template <typename T,
          typename I = std::size_t,
          typename Allocator = std::allocator<T>>
class grb::csr_matrix;
```

## Member Types
Member Type | Definition
----- | -----
`?` | `T`, the type of elements stored in the matrix
`index_type`   | `I`, an integer type used to store matrix indices
`value_type`   | `grb::matrix_entry<T, I>`, a tuple-like type storing copies of the indices and the stored element
`size_type`    | A large unsigned integer type, usually `std::size_t`
`difference_type` | A large signed integer type, usually `std::ptrdiff_t`
`allocator_type` | `Allocator`
`iterator` | Fulfills `std::forward_iterator<value_type>`, with `operator*` returning `reference` [1]
`const_iterator` | Fulfills `std::forward_iterator<const value_type>`, with `operator*` returning `const_reference` [1]
`reference` | `grb::matrix_reference<T, I>`
`const_reference` | `grb::matrix_reference<const T, I>`

## Methods
Method | Description
----- | -----
`(constructor)` | Constructs matrix
`begin()` | Returns iterator to beginning of container
`end()` | Returns iterator to one past last element in container
`insert(first, last)` | Insert range of elements
`insert(elem)` | Inserts single element
`private assign_tuples` | Assigns state to sorted tuples
`find(index)` | Finds index in matrix

## Notes
[1] Iterator type may vary based on backend storage type. Most will likely provide `std::random_access_iterator`.  Dense and COO are `std::random_access_iterator`, as are CSR and COO, with the exception that pointer addition and subtraction are bound by *O(m)* and *O(n)*, respectively, although they are likely to be *O(1)*.
