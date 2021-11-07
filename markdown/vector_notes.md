# Notes on grb::vector design

```cpp
template <typename T,
          typename I = std::size_t,
          typename Hint = grb::sparse,
          typename Allocator = std::allocator<T>>
class grb::vector;
```

## Member Types
Member Type | Definition
----- | -----
`?` | `T`, the type of elements stored in the matrix
`index_type`   | `I`, an integer type used to store matrix indices
`value_type`   | `grb::vector_entry<T, I>`, a tuple-like type storing copies of the index and the stored element
`size_type`    | A large unsigned integer type, usually `std::size_t`
`difference_type` | A large signed integer type, usually `std::ptrdiff_t`
`allocator_type` | `Allocator`
`iterator` | Fulfills `std::forward_iterator<value_type>`, with `operator*` returning `reference` [1]
`const_iterator` | Fulfills `std::forward_iterator<const value_type>`, with `operator*` returning `const_reference` [1]
`reference` | `grb::vector_reference<T, I>`
`const_reference` | `grb::vector_reference<const T, I>`
`hint_type` | `Hint`

## Methods
Method | Description
----- | -----
`(constructor)` | Constructs vector
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
class grb::vector {

  vector(index_type shape);
  
  vector();
  ~vector();
  vector(const vector&);
  vector(vector&&);
  vector& operator=(const vector&);
  vector& operator=(vector&&);

  size_type size() const noexcept;
  index_type shape() const noexcept;

  iterator begin() noexcept;
  iterator end() noexcept;
  const_iterator begin() const noexcept;
  const_iterator end() const noexcept;
  
  template <typename InputIt>
  void insert(InputIt first, InputIt last);
  
  std::pair<iterator, bool> insert(value_type&& value);
  
  template <typename M>
  std::pair<iterator, bool> insert_or_assign(key_type k, M&& obj);
  
  // NOTE: Should be generalized, not just T&
  T& operator[](index_type index);
  const T& operator[](index_type index) const;
  
  iterator find(key_type key) noexcept;
  const_iterator find(key_type key) const noexcept;
};
```

