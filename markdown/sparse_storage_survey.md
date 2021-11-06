# Survey of Sparse Matrix Formats
Name | Abbr. | Description | Row Iter. | Col. Iter.
----- | ----- | ----- | ----- | -----
Compressed sparse row | CSR | | X | 
Compressed sparse column | CSC | | | X
Coordinate | COO | Multiple variants: sorted, unsorted, hash table | ? | ?
Diagonal | DIA | Store dense diagonals | |
Jagged Diagonal | JDS | Remove zeros, then store dense diagonals | |
Doubly compressed row | DCSR | CSR, but rowptr array is a sparse vector | X |
Doubly compressed column | DCSC | CSC, but colptr array is a sparse vector | | X
Block compressed row | BCSR | Sparse storage of dense blocks | | |
Dense storage | - | Dense matrix + boolean map | X | X
