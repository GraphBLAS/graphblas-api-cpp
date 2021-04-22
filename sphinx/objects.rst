#################
GraphBLAS Objects
#################

.. cpp:namespace:: grb

.. cpp:class:: template <typename T, typename I, typename Allocator, typename... Hints> matrix

.. cpp:type:: matrix::value_type

   T

.. cpp:type:: matrix::index_type

   I

.. cpp:type:: size_type

   Unsigned integer type (usually std::size_t)

.. cpp:type:: difference_type

   Signed integer type (usually std::ptrdiff_t)

.. cpp:type:: allocator_type

   Allocator

.. cpp:type:: iterator_type

   ForwardTupleIterator

.. cpp:function:: index_t shape()

   Return shape of the matrix

.. cpp:function:: index_type size()

   Return number of stored values

.. cpp:function:: iterator find(index_t index)

   Locate element with index `index`

.. cpp:function:: iterator begin()

   Return iterator to first element of matrix

.. cpp:function:: iterator end()

   Return iterator to element following last element of matrix
