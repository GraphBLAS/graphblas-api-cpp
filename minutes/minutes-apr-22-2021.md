# GraphBLAS C++ API Working Subgroup Meeting Minutes - April 22, 2021

## Attendees
- [X] Ben Brock
- [X] Scott McMillan

## Agenda

- Discuss 

## Minutes

**Minutes** by Ben Brock

- Sphinx's restructed text is not mature enough to write directly
- Header files -> Doxygen -> Sphinx output is not satisfactory for a standard
  (although it would be fine for an implementation, and we probably should use it for a reference to have documentation)

- find() -> does not except, will return end() even if indices outside bounds
- operator[] -> should not except (probably), may have undefined behavior if indices outside bounds

- at() -> should except if outside bounds, accept if no value

- begin()
- end()

- constructors

- could use matrix views for importing from raw pointer data

- Agreement that we should crystalize this small number of methods,
  which is limited but relatively complete, then move quickly to vector and
  then algorithms.

### Algorithms to Consider:

- mxm

- mxv

- apply

- reduce

- select

- extract
