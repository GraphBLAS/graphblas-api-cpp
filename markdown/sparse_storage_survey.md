# Survey of Sparse Matrix Formats
Name | Abbr. | Description | Row Iter. | Col. Iter. | Random Access
----- | ----- | ----- | ----- | ----- | -----
Compressed sparse row | CSR | | X | | O(n)[^1]
Compressed sparse column | CSC | | | X | O(m)[^2]
Coordinate | COO | Many variants: unsorted, sorted, hash table | ? | ? | O(nnz), O(log(nnz)), O(1)
Diagonal | DIA | Store dense diagonals | | | O(1)
Jagged Diagonal | JDS | Remove zeros, then store dense diagonals | | |
Doubly compressed row | DCSR | CSR, but rowptr array is a sparse vector | X | | O(m + n)[^3]
Doubly compressed column | DCSC | CSC, but colptr array is a sparse vector | | X | O(m + n)[^4]
Block compressed row | BCSR | Sparse storage of dense blocks | | | O(1)
Dense storage | - | Dense matrix + boolean map | X | X | O(1)

Above we assume a matrix with `m` rows and `n` columns containing `nnz` stored values.  So O(n) is bound by the number of columns and O(nnz) by the number of stored values.

[^1]: CSR becomes O(log(n)) if rows are sorted

[^2]: CSC becomes O(log(m)) if columns are sorted

[^3]: DCSR becomes O(log(m) + n) if the sparse row_ptr vector is sorted, and O(log(m) + log(n)) if rows are also sorted

[^4]: DCSC becomes O(log(n) + m) if the sparse column_ptr vector is sorted, and O(log(n) + log(m)) if columns are also sorted
