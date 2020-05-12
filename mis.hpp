// Based on code from GraphBLAS Template Library, Version 2.1
// Copyright 2020, Carnegie Mellon University, Battelle Memorial Institute, and
// Authors. All Rights Reserved.

#include <vector>
#include <random>
#include <graphblas.hpp>

//************************************************************************
// Return a random value that is scaled by the inverse of the degree passed in.
template <typename T=float>
class SetInvDegreeRandom
{
public:
    typedef T result_type;
    SetInvDegreeRandom(double seed = 0.) { m_generator.seed(seed); }

    template <typename DegreeT>
    inline result_type operator()(bool,   // candidate_flag,
                                  DegreeT degree)
    {
        return static_cast<T>(0.0001 +
                              m_distribution(m_generator)/(1. + 2.*degree));
    }

private:
    std::default_random_engine             m_generator;
    std::uniform_real_distribution<double> m_distribution;
};
    
//************************************************************************
// Compute the Maximal Independent Set for a given graph using a variant
// of Luby's randomized algorithm (Luby 1985).

/* @param[out] iset    N-vector of flags, 'true' indicates vertex
 *                     is selected.  Must be empty on call.
 * @param[in]  A       NxN adjacency matrix of graph to compute
 *                     the maximal independent set on. This
 *                     must be an unweighted and undirected graph
 *                     (meaning the matrix is symmetric).  The
 *                     structural zero needs to be '0' and edges
 *                     are indicated by '1' to support use of the
 *                     Arithmetic semiring.
 * @param[in]  seed    The seed for the random number generator
 *
 */
template <typename MatrixT>
void mis_appendixB6(grb::Vector<bool> &iset, MatrixT const &A,
                    double seed = 0.)
{
    gen.seed(seed);
    grb::IndexType N(A.nrows());

    grb::Vector<float> prob(N);
    grb::Vector<float> neighbor_max(N);
    grb::Vector<bool>  new_members(N);
    grb::Vector<bool>  new_neighbors(N);
    grb::Vector<bool>  candidates(N);

    grb::Vector<double> degrees(N);
    grb::reduce(degrees, grb::NoMask(), grb::NoAccumulate(), grb::Plus<double>(), A);

    // Remove isolated vertices
    grb::assign(candidates, degrees, grb::NoAccumulate(), true, grb::AllIndices());

    // Add all singletons to the independent set (iset)
    grb::assign(iset, grb::complement(degrees), grb::NoAccumulate(),
                true, grb::AllIndices(), grb::REPLACE);

    SetInvDegreeRandom<RealT> set_random(seed);

    while (candidates.nvals() > 0) {
        // compute a random probability scaled by inverse of degree.
        grb::eWiseMult(prob, grb::NoMask(), grb::NoAccumulate(),
                       set_random, candidates, degrees);

        // find the max probability of all neighbors
        grb::mxv(neighbor_max, candidates, grb::NoAccumulate(),
                 grb::MaxSecondSemiring<float>(), A, prob, grb::REPLACE);

        // Select source node if its probability is > neighbor_max
        grb::eWiseAdd(new_members, grb::NoMask(), grb::NoAccumulate(),
                      grb::GreaterThan<double>(), prob, neighbor_max);
        grb::apply(new_members, new_members, grb::NoAccumulate(),
                   grb::Identity<bool>(), new_members, grb::REPLACE);

        // Add new members to independent set.
        grb::eWiseAdd(iset, grb::NoMask(), grb::NoAccumulate(),
                      grb::LogicalOr<bool>(), iset, new_members);

        // Remove new_members from set of candidates
        grb::eWiseMult(candidates, grb::complement(new_members), grb::NoAccumulate(),
                       grb::LogicalAnd<bool>(), candidates, candidates, grb::REPLACE);


        if (candidates.nvals() == 0) break;

        // Neighbors of new members can also be removed
        grb::mxv(new_neighbors, candidates, grb::NoAccumulate(),
                 grb::LorLandSemiring<bool>(), A, new_members);
        grb::eWiseMult(candidates, grb::complement(new_neighbors), grb::NoAccumulate(),
                       grb::LogicalAnd<bool>(), candidates, candidates, grb::REPLACE);
    }
}
