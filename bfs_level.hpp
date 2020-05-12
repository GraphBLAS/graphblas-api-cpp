// Based on code from GraphBLAS Template Library, Version 2.1
// Copyright 2020, Carnegie Mellon University, Battelle Memorial Institute, and
// Authors. All Rights Reserved.

#include <graphblas.hpp>

// Given a unweighted N x N adjacency matrix 'graph', and a 'source' vertex ID,
// performs a BFS traversal and sets levels[i] to the level in which vertex i
// is visited (where levels[source] == 1).  If i is not reachable from source,
// then no value is stored at levels[i] (levels should be cleared before calling).

template <typename MatrixT,
          typename LevelsVectorT>
void bfs_level(MatrixT               const &graph,
               typename MatrixT::IndexType  source,
               LevelsVectorT               &levels)
{
    //using T    = typename MatrixT::ScalarType;
    using IdxT = typename MatrixT::IndexType
    auto const N(graph.nrows());

    /// @todo Assert graph is square
    levels.clear();  // TODO: should this be a precondition?

    grb::Vector<bool> wavefront(N);
    wavefront.setElement(source, true);

    IdxT depth(0);
    do {
        ++depth;        // Increment the level

        // Apply the level to all newly visited nodes
        grb::assign(levels, wavefront, grb::NoAccumulate(),
                    depth, grb::AllIndices());

        grb::vxm(wavefront, complement(levels), grb::NoAccumulate(),
                 grb::LorLandSemiring<bool>(), wavefront, graph, grb::REPLACE);
    } while (wavefront.nvals() > 0)
}
