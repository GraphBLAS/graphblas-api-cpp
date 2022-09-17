# `grb::index`

```cpp
template <std::integral T>
struct grb::index;
```

`grb::index` is a tuple-like type used to store matrix indices and dimensions.

## Template Parameters
`T` - type, satisfying `std::integral`, used to store indices

## Member Types
Member Type | Definition
----- | -----
`index_type` | `T`
`first_type` | `T`
`second_type` | `T`

## Member Objects
Member Name | Type
----- | -----
`first` | `T`
`second` | `T`

## Methods
Method | Description
----- | -----
`(constructor)` | Constructs index
`operator[]` | Get one of the indices
`get` | Get one of the indices

