# GraphBLAS C++ API Working Subgroup Meeting Minutes - May 6, 2021

## Attendees
- [X] Ben Brock
- [X] Scott McMillan

## Agenda

- Discuss what Scott found about iterator adaptors.
- Go over Ben's mxv draft implementation.

## Minutes

- Went over Ben's analysis of MXM.

- Agreed that all facilities of the C API's `GrB_Matrix_mxm` can be achieved with the generic operation `C = mask(op(AB, C)) U merge(~mask(C))`.

- This will have an API similar to the below, but likely with parameter order swapped.

```
void mxm(MatrixA A, MatrixB B, MatrixC C,
         Mask mask
         SemiR semiring,
         Acc op,
         bool merge = true);
```

- We agreed that we should include a `grb::mxm` function that hews closely to the C API, and likely an additional API that is simpler and more user-friendly.  (Options include a NumPy-like `.dot()` API, although more experimentation is necessary.)

## TODO
- Ben will get his `grb::mxv` implementation working.
- Scott will research and provide a take on iterator adaptors / Ben's current implementation of allowing references to provide indices.
