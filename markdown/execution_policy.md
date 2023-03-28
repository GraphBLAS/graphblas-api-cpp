## Execution Policy

Execution policies are objects that indicate the kind of parallelism allowed
when executing an algorithm.  For versions of GraphBLAS algorithms that support
execution policies, users may pass in the execution policies defined in the C++
standard library.

- `std::execution::sequenced_policy`
- `std::execution::parallel_policy`
- `std::execution::parallel_unsequenced_policy`
- `std::execution::unsequenced_policy`

GraphBLAS implementations may also provide implementation-defined execution
policies.  Implementations must define the execution behavior for any
execution policies they define.