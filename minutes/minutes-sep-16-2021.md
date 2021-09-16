# GraphBLAS C++ API Working Subgroup Meeting Minutes - September 16, 2021

## Attendees
- [X] Ben Brock
- [X] Scott McMillan

## Agenda
- Discuss progress on named requirements hierarchy, view methods.

- Discuss CppCon presentation.

- Discuss SG19 meeting on P1709 graph proposal.

## Minutes
- Discussed CppCon presentation.  Will need to include a lot of background for C++ audience.  Hope to have a few more points hammered down on our exact named requirements API, observations on how it might interact with graphs API.

- Discussed SG19 meeting on P1709.  P1709 focuses on creating concepts for iteration over graphs, which are 2D ranges.
  * One key is that there are adaptors that are always used to retrieve the ranges (e.g. `vertices(G)`).  This ensures that the API is distinct from the data structures.  (Writing an adaptor could be complicated if your underlying data structure is not suitable for 2D iteration.)
  * Ben thinks that we could allow for some interaction between the graph API and GraphBLAS, either by allowing their graph concepts to be usable in GraphBLAS or implementing GraphBLAS on top of their graph concepts.

- Perhaps most importantly, discussed views and the named requirements they need to fulfill.  We are currently encountering some difficulties deciding on the named requirements, since some of the restrictions on views are complex.
  * The plan going in to the meeting was to define Matrix, ConstMatrix, ConstMatrixView, ConstStructureView, and MaskView types.
  * Ben proposed loosening some of the restrictions on views, such as allowing ConstMatrixView to have (1) iteration and (2) element-wise access through `operator[]` and/or `find()`.
  * Scott asked Ben to write up a new proposal with "promoted" views.
