// Based on code from GraphBLAS Template Library, Version 2.1
// Copyright 2020, Carnegie Mellon University, Battelle Memorial Institute, and
// Authors. All Rights Reserved.

#include <graphblas.hpp>

// Given a unweighted N x N adjacency matrix 'graph', and a 'source' vertex ID,
// performs a BFS traversal and sets parents[i] to a vertex ID of any immediate
// predecessor of vertex i, (where parents[source] == source).  If i is not reachable
// from source, then no value is stored at parents[i] (parents should be cleared before calling).

template <typename MatrixT,
		  typename ParentsVectorT>
void bfs_parent(MatrixT const               &graph,
                typename MatrixT::IndexType  source,
				ParentsVectorT              &parents)
{
    //using T    = typename MatrixT::ScalarType;
    using IdxT = typename MatrixT::IndexType
	auto const N(A.nrows());

	// create index ramp for index_of() functionality
	grb::Vector<IdxT> index_ramp(N);
	for (IdxT i = 0; i < N; ++i)
		index_ramp.setElement(i, i);

	parents.clear();  // TODO: should this be a precondition?
	parents.setElement(src, src);

	grb::Vector<IdxT> q(N);
	q.setElement(src, 1UL);

	// BFS traversal and label the vertices.
	while (q.nvals() > 0) {
		grb::eWiseMult(q, grb::NoMask(), grb::NoAccumulate(),
					   grb::First<IdxT>(), index_ramp, q);
		grb::vxm(q,
				 grb::complement(grb::structure(parents)),
				 grb::NoAccumulate(),
				 grb::MinFirstSemiring<IdxT>(),
				 q, A,
				 grb::REPLACE);
		grb::apply(parents, grb::NoMask(), grb::Plus<IdxT>(),
				   grb::Identity<IdxT>(), q);
	}
}
