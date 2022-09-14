# `grb::vector`

```cpp
template <typename T,
          std::integral I = std::size_t,
          typename Hint = grb::sparse,
          typename Allocator = std::allocator<T>>
class grb::vector;
```

## Template Parameters
`T` - type of scalar values stored in the vector

`I` - type, satisfying `std::integral`, used to store indices in the vector

`Hint` - one or a composition of compile-time hints that may be used to affect the backend storage type

`Allocator` - allocator type used to allocate memory

## Member Types
Member Type | Definition
----- | -----
`scalar_type` | `T`, the type of scalar elements stored in the vector
`index_type`   | `I`, an integer type used to store vector indices
`key_type`     | `index_type`
`map_type`     | `scalar_type`
`value_type`   | `grb::vector_entry<T, I>`, a tuple-like type storing the indices and the stored element
`size_type`    | A large unsigned integer type, usually `std::size_t`
`difference_type` | A large signed integer type, usually `std::ptrdiff_t`
`allocator_type` | `Allocator`
`iterator` | An iterator type fulfilling `std::forward_iterator`
`const_iterator` | A const iterator fulfilling `std::forward_iterator`
`reference` | `grb::vector_ref<T, I>`
`const_reference` | `grb::vector_ref<const T, I>`
`scalar_reference` | Reference to `scalar_type`
`const_scalar_reference` | Const reference to `scalar_type`
`hint_type` | `Hint`

## Methods
Method | Description
----- | -----
`(constructor)` | Constructs vector
`size` | Number of stored elements in vector
`max_size` | Returns the maximum possible number of elements
`empty` | Return whether the vector is empty
`shape` | Return the dimension of the vector
`begin` <br />`cbegin` | Returns iterator to beginning of container
`end` <br />`cend` | Returns iterator to one past last element in container
`reshape` | Modify the dimension of the vector
`clear` | Clears all elements from the container
`insert` | Insert elements
`insert_or_assign` | Inserts or assigns elements
`find` | Finds an element
`operator[]` | Access or insert element

## `grb::vector::vector`

```cpp
vector();                                           (1)
vector(const Allocator& alloc);                     (2)
vector(index_type shape);                           (3)
vector(index_type shape, const Allocator& alloc);   (4)
```

Constructs new `grb::vector` data structure.

1) Constructs an empty vector of dimension 0.
2) Constructs an empty vector of dimension `shape`.

### Parameters
`shape` - shape of the vector to be constructed

### Complexity
1) Constant
2) Implementation defined

### Exceptions
May throw `std::bad_alloc`.

## `grb::vector::size`
```cpp
size_type size() noexcept;
```

Returns the number of elements stored in the vector.

### Parameters
(none)

### Return value
Number of stored elements.

### Complexity
Constant

## `grb::vector::max_size`
```cpp
size_type max_size() noexcept;
```

Returns the maximum possible number of elements that could be stored in the vector due to platform or implementation limitations.

### Parameters
(none)

### Return value
Maximum possible number of elements.

### Complexity
Constant

## `grb::vector::empty`
```cpp
bool empty() noexcept;
```

Returns whether the vector is empty, that is where `size() == 0`.

### Parameters
(none)

### Return value
Whether the vector is empty.

### Complexity
Constant

## `grb::vector::shape`
```cpp
index_type shape() const noexcept;
```

Returns the dimension of the vector.

### Parameters
(none)

### Return value
Dimension of the vector.

### Complexity
Constant

## `grb::vector::begin` and `grb::vector::cbegin`
```cpp
iterator begin() noexcept;
const_iterator begin() const noexcept;
const_iterator cbegin() const noexcept;
```

Returns an iterator to the first element of the vector data structure.  If the vector is empty, returns an element that compares as equal to `end()`.

### Parameters
(none)

### Return value
Iterator to the first element

### Complexity
Constant

## `grb::vector::end` and `grb::vector::cend`
```cpp
iterator end() noexcept;
const_iterator end() const noexcept;
const_iterator cend() const noexcept;
```

Returns an iterator to one past the last element of the vector data structure.  This element is used only to signify the end of the container, and accessing it has undefined behavior.

### Parameters
(none)

### Return value
Iterator to one past the last element.

### Complexity
Constant

## `grb::vector::reshape`
```cpp
void reshape(index_type shape);
```

Reshape the vector.  That is, modify the vector dimension such that vector is now of dimension `shape`.
If any nonzeros lie outside of the new vector shape, they are removed from the vector.

### Parameters
`shape` - New vector shape

### Return value
None

### Complexity
Implementation defined

## `grb::vector::clear`
```cpp
void clear();
```

Clear all stored scalar values from the vector.  The vector maintains the same shape, but after return will now have a size of 0.

### Complexity
Implementation defined

## `grb::vector::insert`
```cpp
template <typename InputIt>
void insert(InputIt first, InputIt last);                    (1)
std::pair<iterator, bool> insert(const value_type& value);   (2)
std::pair<iterator, bool> insert(value_type&& value);        (3)
```

Inserts an element or number of elements into the vector, if the vector doesn't already contain a stored element at the corresponding index.

(1) Insert elements in the range `[first, last)` if an element does not already exist in the vector at the corresponding index.  If multiple elements in `[first, last)` have the same indices, it is undefined which element is inserted.

(2) and (3) Insert the element `value` if an element does not already exist at the corresponding index in the vector.

### Parameters
`first`, `last` - Range of elements to insert

`value` - element to insert

### Return value
(1) None

(2) and (3) return a `std::pair` containing an `iterator` and a `bool` value.  The `bool` value indicates whether or not the insertion was successful.  If the insertion was successful, the first value contains an iterator to the newly inserted element.  If it was unsuccessful, it contains an iterator to the element that prevented insertion.

### Complexity
Implementation defined

## `grb::vector::insert_or_assign`
```cpp
template <class M>
std::pair<iterator, bool> insert_or_assign(key_type k, M&& obj);
```

Inserts an element into index `k` in the vector and assigns to the scalar value if one already exists.

If an element already exists at index location `k`, assigns `std::forward<M>(obj)` to the scalar value stored at that index.  If no element exists, inserts `obj` at the index as if by calling `insert` with `value_type(k, std::forward<M>(obj))`.

### Parameters
`k` - the index location to assign `obj`

`obj` - the scalar value to be assigned

### Type Requirements
`M` must fulfill `std::is_assignable<scalar_type&, M>`

### Return Value
Returns an `std::pair` with the first element holding an iterator to the newly inserted or assigned value and the second element holding a `bool` value that is `true` if the element was inserted and `false` otherwise.

### Complexity
Implementation defined.

## `grb::vector::erase`
```cpp
size_type erase(index_type index);
```

Erases the element stored at index `index` if one exists.

### Parameters
`index` - the index of the scalar value to erase

### Return Value
Returns the number of elements erased (0 or 1).

### Complexity
Implementation defined.

## `grb::vector::find`
```cpp
iterator find(index_type index);
const_iterator find(index_type index) const;
```

Finds the element at location `index` in the vector, returning an iterator to the element.  If no element is present at the location, returns `end()`.

### Parameters
`index` - Location of the vector element to find

### Return value
An iterator pointing to the vector element at the corresponding index, or `end()` if there is no element at the location.

### Complexity
Implementation defined

## `grb::vector::operator[]`
```cpp
scalar_reference operator[](index_type index);
const_scalar_reference operator[](index_type index) const;
```

Returns a reference to the scalar value stored at location `index` in the vector.  If no value is stored at the location, inserts a default constructed value at the location and returns a reference to it.

### Parameters
`index` - Location of the vector element

### Return value
A reference to the scalar value at location `index`.

### Complexity
Implementation defined

## `grb::vector::at`
```cpp
scalar_reference at(index_type index);
const_scalar_reference at(index_type index) const;
```

Returns a reference to the scalar value stored at location `index` in the vector.  If no value is stored at the location, throws the exception `grb::out_of_range`.

### Parameters
`index` - Location of the vector element

### Return value
A reference to the scalar value at location `index`.

### Complexity
Implementation defined

### Exceptions
If no element exists at location `index`, throws the exception `grb::out_of_range`.
