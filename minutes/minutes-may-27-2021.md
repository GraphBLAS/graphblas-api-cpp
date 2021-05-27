# GraphBLAS C++ API Working Subgroup Meeting Minutes - May 27, 2021

## Attendees
- [X] Ben Brock
- [X] Scott McMillan

## Agenda

- Dsicuss Semirings and monoids
- Discuss what Scott found about iterator adaptors.

## Minutes

- Agreed on "issue of types and accumulation."
  - Regardless of whether combiner and reducer are strictly typed, we can define `T x U -> V` based on the return type of `combiner(T(), U())`, where `T` and `U` are determined by A and B.  Reduction will happen in type `V`, which may not necessarily correspond to the type of output C (could necessitate temporaries, but is mathematically correct).

- Discussed Ben's idea for `monoid_traits` struct that inspects a functor of type `T` and defines an identity for the functor.  For user- or library-defined types, this would be defining `identity` based on `identity` defined in the type `T`, but for other things (e.g. `std::plus<>`, `std::times<>`, etc.) could be defined separately.  This corresponds very closely to how `std::iterator_traits` works.

- There is still an open question of whether monoids (or binary ops that are "lifted" to monoids by having a specialization of `monoid_traits`) should be required to have a fixed type, and if not how the identity should be acquired (e.g. a template function / template struct).
