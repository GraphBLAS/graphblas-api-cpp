# Pre-Defined Operators
The GraphBLAS C++ API defines a number of binary and unary operators.  Operators are defined as
function objects and typically perform arithmetic or logical operations like addition, multiplication,
negation, and logical and.

#### TODO: Discuss Unary Operators
They work the same way as binary operators, but are quite a bit simpler, since there is only one value to operate upon.

## Binary Operator Template Parameters
GraphBLAS's binary operators allow flexiblility in terms of whether all, some, or none of
the types are explicitly declared.  If one or more types are not explicitly declared,
they are deduced at the callsite where the operator is invoked.  For each binary operator
`op`, there are three partial specializations defined:

1) `op<T, U, V>`, where the input arguments are explicitly specified to be `T` and `U` and the return value is `V`.
2) `op<T, U, void>`, where the input arguments are explicitly specified to be `T` and `U`, and the return value is deduced.
3) `op<void, void, void>`, where the inputs arguments and return type are all deduced upon invocation.

All binary operators have the following default template parameters:

```cpp
template <typename T = void, typename U = T, typename V = void>
class op;
```

This means the user can use a binary operator with zero, one, two, or three template parameters explicitly specified.
The types of the input arguments and return value will be explicitly defined or reduced accordingly.

#### No Types Specified
If a user specifies no template parameters when using a binary operator, the result is a function object in which the
input argument and return value types are all deduced at the callsite.

```cpp
#include <grb/grb.hpp>
#include <iostream>
int main(int argc, char** argv) {
  // No types are explicitly specified.
  // We can use this operator with values of
  // any types for which an operator+() is defined.
  grb::plus<> p1;
  
  std::size_t a = 1024;
  std::uint8_t b = 12;
  
  // `std::size_t` and `std::uint8_t` deduced as types of input arguments.
  // `std::size_t` will be deduced as type of return value.
  // std::size_t + std::uint8_t -> std::size_t
  auto c = p1(a, b);
  
  return 0;
}
```

#### One Type Specified
If a user specifies one template parameters when using a binary operator, the result is a function object in which the
the two input arguments are of the type specified, and the return value type is deduced.

```cpp
#include <grb/grb.hpp>
#include <iostream>
int main(int argc, char** argv) {
  // Explicitly specify `int` as the type of both input values.
  // Return value type will be deduced as `int`.
  grb::plus<int> p1;
  
  int a = 1024;
  int b = 12;
  
  // int + int -> int
  int c = p1(a, b);
  
  return 0;
}
```

#### Two Types Specified
If a user specifies two template parameters when using a binary operator, the result is a function object in which the
the two input arguments are of the types specified, and the return value type is deduced.

```cpp
#include <grb/grb.hpp>
#include <iostream>
int main(int argc, char** argv) {
  // Explicitly specify `std::size_t` for the lefthand argument
  // and `std::uint8_t` for the righthand argument.
  // Return value type will be deduced as `std::size_t`.
  grb::plus<std::size_t, std::uint8_t> p1;
  
  std::size_t a = 1024;
  std::uint8_t b = 12;
  
  // std::size_t + std::uint8_t -> std::size_t
  std::size_t c = p1(a, b);
  
  return 0;
}
```

#### Three Types Specified
If a user specifies all three template parameters when using a binary operator, both of the input argument types
as well as the return value type of the function are explicitly specified.

```cpp
#include <grb/grb.hpp>
#include <iostream>
int main(int argc, char** argv) {
  // Explicitly specify `std::size_t` for the lefthand argument
  // and `std::uint8_t` for the righthand argument.
  // Return value type explicitly specified as `int`.
  grb::plus<std::size_t, std::uint8_t, int> p1;
  
  std::size_t a = 1024;
  std::uint8_t b = 12;
  
  // std::size_t + std::uint8_t -> std::size_t
  std::size_t c =  p1(a, b);
  
  return 0;
}
```

