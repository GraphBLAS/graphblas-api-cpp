# `grb::matrix`

```cpp
template <typename T,
          std::integral I = std::size_t,
          typename Hint = grb::sparse,
          typename Allocator = std::allocator<T>>
class grb::matrix;
```

## Template Parameters
`T` - type of scalar values stored in the matrix<br />
`I` - type, satisfying `std::integral`, used to store indices in the matrix<br />
`Hint` - one or a composition of compile-time hints that may be used to affect the backend storage type<br />
`Allocator` - allocator type used to allocate memory for the matrix

## Member Types
Member Type | Definition
----- | -----
`scalar_type` | `T`, the type of elements stored in the matrix
`index_type`   | `I`, an integer type used to store matrix indices
`value_type`   | `grb::matrix_entry<T, I>`, a tuple-like type storing the indices and the stored element
`size_type`    | A large unsigned integer type, usually `std::size_t`
`difference_type` | A large signed integer type, usually `std::ptrdiff_t`
`allocator_type` | `Allocator`
`iterator` | An iterator type fulfilling `std::forward_iterator`
`const_iterator` | A const iterator fulfilling `std::forward_iterator`
`reference` | `grb::matrix_reference<T, I>`
`const_reference` | `grb::matrix_reference<const T, I>`
`hint_type` | `Hint`

## Methods
Method | Description
----- | -----
`(constructor)` | Constructs matrix
`begin`<br />`cbegin` | Returns iterator to beginning of container
`end`<br />`cend` | Returns iterator to one past last element in container
`insert` | Insert elements
`insert_or_assign` | Inserts or assigns elemens

### `grb::matrix::matrix`

```cpp
matrix();                               (1)
matrix(grb::index<index_type> shape);   (2)
matrix(std::string file_path);          (3)
```

Constructs new `grb::matrix` data structure.

1) Constructs an empty matrix of dimension `0 x 0`.
2) Constructs an empty matrix of dimension `shape[0] x shape[1]`.
3) Constructs a matrix with the dimensions and contents of the Matrix Market file at file path `file_path`.

#### Parameters
`shape` - shape of the matrix to be constructed<br />
`file_path` - string containing the file path of the file to be loaded.

#### Complexity
1) Constant
2) Implementation defined
3) Implementation defined

#### Exceptions
(1), (2), and (3) may all throw `std::bad_alloc`.  (3) may also throw the exception `grb::matrix_io::file_error`
in the case that there is an error opening the file at path `file_path` or reading the file.

### `grb::matrix::begin` and `grb::matrix::cbegin`
```cpp
iterator begin() noexcept;
const_iterator begin() const noexcept;
const_iterator cbegin() const noexcept;
```

Returns an iterator to the first element of the matrix data structure.  If the matrix is empty, returns an element that compares as equal to `end()`.

#### Parameters
(none)

#### Return value
Iterator to the first element

#### Complexity
Constant

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
