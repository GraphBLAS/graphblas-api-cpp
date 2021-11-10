# GraphBLAS C++ API Working Subgroup Meeting Minutes - November 10, 2021

## Attendees
- [X] Ben Brock
- [X] Scott McMillan

## Agenda
- Discuss feedback from Andrew Lumsdaine related to range adaptors and potential interoperability between Graph Library and GraphBLAS.
- Discuss Ben's work on `grb::vector` interface
- Discuss some of Ben's backend matrix implementations
- Discuss complexities

## Minutes
- Discussed potentially adding matrix range adaptors
  * Would need to set guidelines for complexities
  * Complexity of c'ting range adaptor
  * Complexity of iteration through range adaptor
- Discussed Ben's `dense_vector` implementation
  * Similar to matrix, except key is `I` integral instead of tuple-like `grb::index<I>`
  * `insert` and `insert_or_assign` vs `set_element`, `get_element`, etc.
  * Ben thinks `insert` style is better and more standard

## TODOs
- Ben will write up matrix entry in markdown a little more formally
- Experiment with LaTeX generation from markdown
- Ben will aim to fix up `grb::matrix`, write tests, concurrently with writing documentation
- Scott will review Ben's new markdown
