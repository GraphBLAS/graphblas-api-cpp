// Based on code from GraphBLAS Template Library, Version 2.1
// Copyright 2020, Carnegie Mellon University, Battelle Memorial Institute, and
// Authors. All Rights Reserved.

#include <vector>
#include <graphblas.hpp>

// Compute the betweenness centrality contribution of all vertices in the graph
// for a given set of source nodes and add it to an existing BC vector (delta)
template<typename MatrixT, typename BCVectorT>
void bc_update(MatrixT                            const &A,
               std::vector<typename MatrixT::IndexType>  sources,
               BCVectorT                                &delta)
{
    using Int  = int32_t;
    using Real = float;
    using IdxT = typename MatrixT::IndexType
	
    auto const N(A.nrows());
	auto const NS(source.size());

	/// @todo assert proper dimensions and NS > 0

	// index and value arrays needed to build NumSP
	std::vector<IdxT> GrB_ALL_NS;     // fill with sequence
	GrB_ALL_NS.reserve(NS);
	for (grb::IndexType idx = 0; idx < NS; ++idx) {
		GrB_ALL_NS.push_back(idx);
	}

	// NumSP holds # of shortest paths to each vertex from each src.
	// Initialized to source vertices
	// NumSP[s[i],i] = 1 where 0 <= i < NS; implied zero elsewhere
	grb::Matrix<Int> NumSP(N, NS);
	NumSP.build(sources, GrB_ALL_NS, std::vector<Int>(NS, 1));

	// The current frontier for all BFS's (from all roots)
	// Initialized to out neighbors of each source node in src
	grb::Matrix<Int> Frontier(N, NS);
	grb::extract(Frontier, grb::complement(NumSP), grb::NoAccumulate(),
				 grb::transpose(A), grb::AllIndices(), src, grb::REPLACE);

	// std::vector manages allocation
	std::vector<grb::Matrix<bool>*> Sigmas;  //todo use smart pointers

	Int depth = 0;

	// ==================== BFS phase ====================
	while (Frontier.nvals() > 0) {
		Sigmas.push_back(new grb::Matrix<bool>(N, NS));
		grb::apply(*(Sigmas[depth), grb::NoMask(), grb::NoAccumulate(),
				   grb::Identity<Int, bool>(), Frontier);

		grb::eWiseAdd(NumSP, grb::NoMask(), grb::NoAccumulate(),
					  grb::Plus<Int>(), NumSP, Frontier);
		grb::mxm(Frontier, grb::complement(NumSP), grb::NoAccumulate(),
				 grb::ArithmeticSemiring<Int>(),
				 grb::transpose(A), Frontier, grb::REPLACE);
		++depth;

	}

	grb::Matrix<Real> NspInv(N, NS);

	grb::apply(NspInv, grb::NoMask(), grb::NoAccumulate(),
			   grb::MultiplicativeInverse<Real>(), NumSP);

	grb::Matrix<Real> BCu(N, NS);
	grb::assign(BCu, grb::NoMask(), grb::NoAccumulate(),
				1.0f, grb::AllIndices(), grb::AllIndices());

	grb::Matrix<Real> W(N, NS);

	// ================== backprop phase ==================
	for (Int i = depth-1; i > 0; --i) {
		grb::eWiseMult(W, *Sigmas[i], grb::NoAccumulate(),
					   grb::Times<Real>(), BCu, NspInv, grb::REPLACE);

		grb::mxm(W, *Sigmas[i-1], grb::NoAccumulate(),
				 grb::ArithmeticSemiring<Real>(), A, W, grb::REPLACE);
		grb::eWiseMult(BCu, grb::NoMask(), grb::Plus<Real>(),
					   grb::Times<Real>(), W, NumSP);
	}

	// adjust result
	grb::assign(delta, grb::NoMask(), grb::NoAccumulate(),
				-1.f*NS, grb::AllIndices());
	grb::reduce(delta, grb::NoMask(), grb::Plus<float>(),
				grb::Plus<float>(), BCu);

	// Release resources
	for (auto it = Sigmas.begin(); it != Sigmas.end(); ++it)
		delete *it;
}
