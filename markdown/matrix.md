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
`scalar_reference` | Reference to `scalar_type`
`const_scalar_reference` | Const reference to `scalar_type`
`hint_type` | `Hint`

## Methods
Method | Description
----- | -----
`(constructor)` | Constructs matrix
`size` | Number of stored elements in matrix
`max_size` | Returns the maximum possible number of elements
`empty` | Return whether the matrix is empty
`begin`<br />`cbegin` | Returns iterator to beginning of container
`end`<br />`cend` | Returns iterator to one past last element in container
`insert` | Insert elements
`insert_or_assign` | Inserts or assigns elements
`find` | Finds an element
`operator[]` | Access or insert element

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

### `grb::matrix::size`
```cpp
size_type size() noexcept;
```

Returns the number of elements stored in the matrix.

#### Parameters
(none)

#### Return value
Number of stored elements.

#### Complexity
Constant

### `grb::matrix::max_size`
```cpp
size_type max_size() noexcept;
```

Returns the maximum possible number of elements that could be stored in the matrix due to platform or implementation limitations.

#### Parameters
(none)

#### Return value
Maximum possible number of elements.

#### Complexity
Constant

### `grb::matrix::empty`
```cpp
bool empty() noexcept;
```

Returns whether the matrix is empty, that is where `size() == 0`.

#### Parameters
(none)

#### Return value
Whether the matrix is empty.

#### Complexity
Constant

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

### `grb::matrix::end` and `grb::matrix::cend`
```cpp
iterator end() noexcept;
const_iterator end() const noexcept;
const_iterator cend() const noexcept;
```

Returns an iterator to one past the last element of the matrix data structure.  This element is used only to signify the end of the container, and accessing it has undefined behavior.

#### Parameters
(none)

#### Return value
Iterator to one past the last element.

#### Complexity
Constant

### `grb::matrix::insert`
```cpp
template <typename InputIt>
void insert(InputIt first, InputIt last);                    (1)
std::pair<iterator, bool> insert(const value_type& value);   (2)
std::pair<iterator, bool> insert(value_type&& value);        (3)
```

Inserts an element or number of elements into the matrix, if the matrix doesn't already contain a stored element at the corresponding index.

(1) Insert elements in the range `[first, last)` if an element does not already exist in the matrix at the corresponding index.  If multiple elements in `[first, last)` have the same indices, it is undefined which element is inserted.<br />
(2) and (3) Insert the element `value` if an element does not already exist at the corresponding index in the matrix.

#### Parameters
`first`, `last` - Range of elements to insert<br />
`value` - element to insert

#### Return value
(1) None<br />
(2) and (3) return a `std::pair` containing an `iterator` and a `bool` value.  The `bool` value indicates whether or not the insertion was successful.  If the insertion was successful, the first value contains an iterator to the newly inserted element.  If it was unsuccessful, it contains an iterator to the element that prevented insertion.

#### Complexity
Implementation defined

### `grb::matrix::find`
```cpp
iterator find(grb::index<I> index);
const_iterator find(grb::index<I> index) const;
```

Finds the element at location (`index[0]`, `index[1]`) in the matrix, returning an iterator to the element.  If no element is present at the location, returns `end()`.

#### Parameters
`index` - Location of the matrix element to find

#### Return value
An iterator pointing to the matrix element at the corresponding index, or `end()` if there is no element at the location.

#### Complexity
Implementation defined

# Notes on grb::index
These should all go in a different file
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
