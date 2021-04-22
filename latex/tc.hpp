// Based on code from GraphBLAS Template Library, Version 2.1
// Copyright 2020, Carnegie Mellon University, Battelle Memorial Institute, and
// Authors. All Rights Reserved.

#include <vector>
#include <random>
#include <graphblas.hpp>

//************************************************************************
/**
 * @brief Compute the number of triangles in a graph
 *
 * @param[in] L  Strictly lower triangular NxN matrix from the graph's
 *               adjacency matrix.  Graph is assumed to be undirected and
 *               unweighted.
 */
template<typename MatrixT>
uint64_t triangle_count_appendixB7(MatrixT const &L)
{
    GrB::IndexType N(L.nrows());
    GrB::Matrix<uint64_t> C(N, N);

    GrB::mxm(C, L, GrB::NoAccumulate(),
             GrB::ArithmeticSemiring<uint64_t>(), L, GrB::transpose(L));

    uint64_t count(0);
    GrB::reduce(count, GrB::NoAccumulate(),
                GrB::PlusMonoid<uint64_t>(), C);

    return count;
}
