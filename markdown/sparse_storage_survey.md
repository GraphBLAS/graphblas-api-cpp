# Survey of Sparse Matrix Formats
Name | Abbr. | Description | Row Iter. | Col. Iter. | Random Access
----- | ----- | ----- | ----- | ----- | -----
Compressed sparse row | CSR | | X | | O(n)
Compressed sparse column | CSC | | | X | O(m)
Coordinate | COO | Many variants: unsorted, sorted, hash table | ? | ? | O(nnz), O(log(nnz)), O(1)
Diagonal | DIA | Store dense diagonals | | | O(1)
Jagged Diagonal | JDS | Remove zeros, then store dense diagonals | | |
Doubly compressed row | DCSR | CSR, but rowptr array is a sparse vector | X | | O(m + n)
Doubly compressed column | DCSC | CSC, but colptr array is a sparse vector | | X | O(m + n)
Block compressed row | BCSR | Sparse storage of dense blocks | | | O(1)
Dense storage | - | Dense matrix + boolean map | X | X | O(1)

Above we assume a matrix with `m` rows and `n` columns containing `nnz` stored values.  So O(n) is bound by the number of columns and O(nnz) by the number of stored values.
