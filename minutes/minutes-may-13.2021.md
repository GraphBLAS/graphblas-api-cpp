# GraphBLAS C++ API Working Subgroup Meeting Minutes - May 13, 2021

## Attendees
- [X] Ben Brock
- [X] Scott McMillan

## Agenda

- Discuss what Scott found about iterator adaptors.
- Go over Ben's mxv draft implementation.

## Minutes

- Went over Ben's mxv draft implementation.
- Agreed on the basic structure for mxv.
- Uncovered issue of types. Semiring has combiner `T x U -> V` and reducer `V x V -> V`
