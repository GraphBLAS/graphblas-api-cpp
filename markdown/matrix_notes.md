# Notes on grb::matrix design

```cpp
template <typename T,
          typename I = std::size_t,
          typename Hint = grb::sparse,
          typename Allocator = std::allocator<T>>
class grb::matrix;
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
`hint_type` | `Hint`

## Methods
Method | Description
----- | -----
`(constructor)` | Constructs matrix
`begin` | Returns iterator to beginning of container
`end` | Returns iterator to one past last element in container
`insert` | Insert elements
`insert_or_assign` | Inserts or assigns element

## Method Declarations
```cpp
template <typename T,
          typename I = std::size_t,
          typename Hint = grb::sparse,
          typename Allocator = std::allocator<T>>
class grb::matrix {

  matrix(grb::index<I> shape);
  template <grb::ranges::const_matrix_range R>
  matrix(R other);
  
  matrix();
  ~matrix();
  matrix(const csr_matrix&);
  matrix(csr_matrix&&);
  matrix& operator=(const csr_matrix&);
  matrix& operator=(csr_matrix&&);

  size_type size() const noexcept;
  grb::index<I> shape() const noexcept;

  iterator begin() noexcept;
  iterator end() noexcept;
  const_iterator begin() const noexcept;
  const_iterator end() const noexcept;
  
  template <typename InputIt>
  void insert(InputIt first, InputIt last);
  
  std::pair<iterator, bool> insert(value_type&& value);
  
  template <typename M>
  std::pair<iterator, bool> insert_or_assign(key_type k, M&& obj);
  
  iterator find(key_type key) noexcept;
  const_iterator find(key_type key) const noexcept;
};
```

## Comparison
Member Type | Value for `unordered_map` | Value for `grb::matrix` | Notes
---- | ---- | ---- | ----
`key_type` | `std::pair<I, I>` | `grb::index<I>` | `grb::index<I>` behaves like `std::pair<I, I>`, but also supports `operator[]`, which is v. convenient
`map_type` | `T` | `T` | Type of stored elements
`?` | `T` | `T` | What we call `map_type` in `grb::matrix`
`index_type` | `I` | `I` | Integral type used to store indices
`value_type` | `std::pair<const std::pair<I, I>, T>` | `grb::matrix_entry<T, I>` | `grb::matrix_entry<T, I>` behaves like `std::pair<const std::pair<I, I>, T>`, but adds some convenience functions
`reference` | `std::pair<const std::pair<I, I>, T>&` | `grb::matrix_reference<T, I>` | `grb::matrix_reference<T, I>` behaves like `std::pair<const std::pair<I, I>, T>&` (allows obtaining a reference to value, copies of indices)
`const_reference` | `const std::pair<const std::pair<I, I>, T>&` | `grb::matrix_reference<const T, I>` | `grb::matrix_reference<const T, I>` behaves like `const std::pair<const std::pair<I, I>, T>&` (allows obtaining a constant reference to value, copies of indices)

## Notes
[1] Iterator type may vary based on backend storage type. Most will likely provide `std::random_access_iterator`.  Dense and COO are `std::random_access_iterator`, as are CSR and COO, with the exception that pointer addition and subtraction are bound by *O(m)* and *O(n)*, respectively, although they are likely to be *O(1)*.

# Notes on grb::index
```cpp
template <typename T>
struct grb::index;
```

## Description
`grb::index` is a pair-like class that stores row and column indices associated with a matrix element.

`T` must fulfill the concept `std::integral`.

## Template Parameters
`T` - an integral type used to store indices.

## Member Types
Member Type | Definition
----- | -----
`index_type` | `T`, an integer type used to store matrix indices
`first_type`   | `T`, an integer type used to store matrix indices
`second_type`   | `T`, an integer type used to store matrix indices

## Member Objects
Member Name | Type
----- | -----
`first` | `T`
`second` | `T`

# Survey of Sparse Matrix Formats
Name | Abbr. | Description | Row Iter. | Col. Iter.
----- | ----- | -----
Compressed sparse row | CSR | Classis format | X | 
Compressed sparse column | CSC | Classic format | | X
Diagonal | DIA | Store dense diagonals | |
Jagged Diagonal | JDS | Remove zeros, Store dense diagonalsthen store diagonals | |
Doubly compressed row | DCSR | CSR, but rowptr array is a sparse vector | X |
Doubly compressed column | DCSC | CSC, but colptr array is a sparse vector | | X
Coordinate | COO | Multiple variants: sorted, unsorted, hash table | ? | ?
Dense storage | - | Dense matrix + boolean map | X | X
Block compressed row | BCSR | Sparse storage of dense blocks | | |
