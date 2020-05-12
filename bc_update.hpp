// Based on code from GraphBLAS Template Library, Version 2.1
// Copyright 2020, Carnegie Mellon University, Battelle Memorial Institute, and
// Authors. All Rights Reserved.

#include <graphblas.hpp>

// Compute the betweenness centrality contribution of all vertices in the graph
// for a given source node and add it to an existing BC vector (delta)
template<typename MatrixT, typename BCVectorT>
void bc(MatrixT               const &A,
        typename MatrixT::IndexType  source,
        BCVectorT                   &delta)
{
    using Int  = int32_t;
    using Real = float;
    using IdxT = typename MatrixT::IndexType
    auto const N(A.nrows());
    grb::Matrix<Int, IdxT> sigma(N, N);

    grb::Vector<Int, IdxT> wavefront(N);
    wavefront.setElement(source, 1);

    grb::Vector<Int, IdxT> path(wavefront);

    grb::vxm(wavefront, grb::complement(path), grb::NoAccumulate(),
             grb::ArithmeticSemiring<Int>(), wavefront, A, grb::REPLACE);

    // BFS phase
    IdxT depth(0);
    do {
        grb::assign(sigma, grb::NoMask(), grb::NoAccumulate(),
                    wavefront, depth, grb::AllIndices());
        grb::eWiseAdd(path, grb::NoMask(), grb::NoAccumulate(),
                      grb::Plus<Int>(), path, wavefront);
        grb::vxm(wavefront, grb::complement(path), grb::NoAccumulate(),
                 grb::ArithmeticSemiring<Int>(), wavefront, A, grb::REPLACE);

        ++depth;
    } while (wavefront.nvals() > 0);

    // BC computation phase
    grb::Vector<Real> t1(N), t2(N), t3(N), t4(N);

    for (int i = depth-1; i > 0; --i) {
        grb::assign(t1, grb::NoMask(), grb::NoAccumulate(),
                    1.f, grb::AllIndices());
        grb::eWiseAdd(t1, grb::NoMask(), grb::NoAccumulate(),
                      grb::Plus<Real>(), t1, delta);
        grb::extract(t2, grb::NoMask(), grb::NoAccumulate(),
                     grb::transpose(sigma), grb::AllIndices(), i);
        grb::eWiseMult(t2, grb::NoMask(), grb::NoAccumulate(),
                       grb::Div<Real>(), t1, t2);
        grb::mxv(t3, grb::NoMask(), grb::NoAccumulate(),
                 grb::ArithmeticSemiring<Real>(), A, t2);
        grb::extract(t4, grb::NoMask(), grb::NoAccumulate(),
                     grb::transpose(sigma), grb::AllIndices(), i-1);
        grb::eWiseMult(t4, grb::NoMask(), grb::NoAccumulate(),
                       grb::Times<Real>(), t4, t3);
        grb::eWiseAdd(delta, grb::NoMask(), grb::NoAccumulate(),
                      grb::Plus<Real>(), delta, t4);
    }
}
