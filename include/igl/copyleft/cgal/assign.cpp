// This file is part of libigl, a simple c++ geometry processing library.
// 
// Copyright (C) 2016 Alec Jacobson <alecjacobson@gmail.com>
// 
// This Source Code Form is subject to the terms of the Mozilla Public License 
// v. 2.0. If a copy of the MPL was not distributed with this file, You can 
// obtain one at http://mozilla.org/MPL/2.0/.
#include "assign.h"
#include "assign_scalar.h"

template <typename DerivedC, typename DerivedD>
IGL_INLINE void igl::copyleft::cgal::assign(
  const Eigen::MatrixBase<DerivedC> & C,
  Eigen::PlainObjectBase<DerivedD> & D)
{
  D.resizeLike(C);
  for(int i = 0;i<C.rows();i++)
  {
    for(int j = 0;j<C.cols();j++)
    {
      assign_scalar(C(i,j),D(i,j));
    }
  }
}

template <typename ReturnScalar, typename DerivedC>
IGL_INLINE 
Eigen::Matrix<
  ReturnScalar,
  DerivedC::RowsAtCompileTime, 
  DerivedC::ColsAtCompileTime, 
  1,
  DerivedC::MaxRowsAtCompileTime, 
  DerivedC::MaxColsAtCompileTime>
igl::copyleft::cgal::assign(
  const Eigen::MatrixBase<DerivedC> & C)
{
  Eigen::Matrix<
    ReturnScalar,
    DerivedC::RowsAtCompileTime, 
    DerivedC::ColsAtCompileTime, 
    1,
    DerivedC::MaxRowsAtCompileTime, 
    DerivedC::MaxColsAtCompileTime> D;
  assign(C,D);
  return D;
}

#ifdef IGL_STATIC_LIBRARY
// Explicit template instantiation
template void igl::copyleft::cgal::assign<Eigen::Matrix<CGAL::Lazy_exact_nt<CGAL::Gmpq>, -1, -1, 0, -1, -1>, Eigen::Matrix<double, -1, 3, 0, -1, 3> >(Eigen::MatrixBase<Eigen::Matrix<CGAL::Lazy_exact_nt<CGAL::Gmpq>, -1, -1, 0, -1, -1> > const&, Eigen::PlainObjectBase<Eigen::Matrix<double, -1, 3, 0, -1, 3> >&);
template void igl::copyleft::cgal::assign<Eigen::Matrix<CGAL::Lazy_exact_nt<CGAL::Gmpq>, -1, -1, 0, -1, -1>, Eigen::Matrix<CGAL::Lazy_exact_nt<CGAL::Gmpq>, -1, 3, 0, -1, 3> >(Eigen::MatrixBase<Eigen::Matrix<CGAL::Lazy_exact_nt<CGAL::Gmpq>, -1, -1, 0, -1, -1> > const&, Eigen::PlainObjectBase<Eigen::Matrix<CGAL::Lazy_exact_nt<CGAL::Gmpq>, -1, 3, 0, -1, 3> >&);
template void igl::copyleft::cgal::assign<Eigen::Matrix<double, -1, -1, 1, -1, -1>, Eigen::Matrix<double, -1, -1, 0, -1, -1> >(Eigen::MatrixBase<Eigen::Matrix<double, -1, -1, 1, -1, -1> > const&, Eigen::PlainObjectBase<Eigen::Matrix<double, -1, -1, 0, -1, -1> >&);
template void igl::copyleft::cgal::assign<Eigen::Matrix<double, -1, -1, 1, -1, -1>, Eigen::Matrix<CGAL::Lazy_exact_nt<CGAL::Gmpq>, -1, -1, 0, -1, -1> >(Eigen::MatrixBase<Eigen::Matrix<double, -1, -1, 1, -1, -1> > const&, Eigen::PlainObjectBase<Eigen::Matrix<CGAL::Lazy_exact_nt<CGAL::Gmpq>, -1, -1, 0, -1, -1> >&);
template void igl::copyleft::cgal::assign<Eigen::Matrix<double, -1, -1, 0, -1, -1>, Eigen::Matrix<double, -1, -1, 0, -1, -1> >(Eigen::MatrixBase<Eigen::Matrix<double, -1, -1, 0, -1, -1> > const&, Eigen::PlainObjectBase<Eigen::Matrix<double, -1, -1, 0, -1, -1> >&);
template void igl::copyleft::cgal::assign<Eigen::Matrix<double, -1, -1, 0, -1, -1>, Eigen::Matrix<CGAL::Lazy_exact_nt<CGAL::Gmpq>, -1, -1, 0, -1, -1> >(Eigen::MatrixBase<Eigen::Matrix<double, -1, -1, 0, -1, -1> > const&, Eigen::PlainObjectBase<Eigen::Matrix<CGAL::Lazy_exact_nt<CGAL::Gmpq>, -1, -1, 0, -1, -1> >&);
template void igl::copyleft::cgal::assign<Eigen::Matrix<double, -1, 3, 0, -1, 3>, Eigen::Matrix<double, -1, 3, 0, -1, 3> >(Eigen::MatrixBase<Eigen::Matrix<double, -1, 3, 0, -1, 3> > const&, Eigen::PlainObjectBase<Eigen::Matrix<double, -1, 3, 0, -1, 3> >&);
template void igl::copyleft::cgal::assign<Eigen::Matrix<double, -1, 3, 0, -1, 3>, Eigen::Matrix<CGAL::Lazy_exact_nt<CGAL::Gmpq>, -1, 3, 0, -1, 3> >(Eigen::MatrixBase<Eigen::Matrix<double, -1, 3, 0, -1, 3> > const&, Eigen::PlainObjectBase<Eigen::Matrix<CGAL::Lazy_exact_nt<CGAL::Gmpq>, -1, 3, 0, -1, 3> >&);
template void igl::copyleft::cgal::assign<Eigen::Matrix<CGAL::Lazy_exact_nt<CGAL::Gmpq>, -1, -1, 0, -1, -1>, Eigen::Matrix<double, -1, -1, 0, -1, -1> >(Eigen::MatrixBase<Eigen::Matrix<CGAL::Lazy_exact_nt<CGAL::Gmpq>, -1, -1, 0, -1, -1> > const&, Eigen::PlainObjectBase<Eigen::Matrix<double, -1, -1, 0, -1, -1> >&);
template void igl::copyleft::cgal::assign<Eigen::Matrix<CGAL::Lazy_exact_nt<CGAL::Gmpq>, -1, 3, 0, -1, 3>, Eigen::Matrix<CGAL::Lazy_exact_nt<CGAL::Gmpq>, -1, 3, 0, -1, 3> >(Eigen::MatrixBase<Eigen::Matrix<CGAL::Lazy_exact_nt<CGAL::Gmpq>, -1, 3, 0, -1, 3> > const&, Eigen::PlainObjectBase<Eigen::Matrix<CGAL::Lazy_exact_nt<CGAL::Gmpq>, -1, 3, 0, -1, 3> >&);
template void igl::copyleft::cgal::assign<Eigen::Matrix<CGAL::Lazy_exact_nt<CGAL::Gmpq>, -1, 3, 0, -1, 3>, Eigen::Matrix<double, -1, 3, 0, -1, 3> >(Eigen::MatrixBase<Eigen::Matrix<CGAL::Lazy_exact_nt<CGAL::Gmpq>, -1, 3, 0, -1, 3> > const&, Eigen::PlainObjectBase<Eigen::Matrix<double, -1, 3, 0, -1, 3> >&);
template void igl::copyleft::cgal::assign<Eigen::Matrix<CGAL::Lazy_exact_nt<CGAL::Gmpq>, 8, 3, 0, 8, 3>, Eigen::Matrix<CGAL::Lazy_exact_nt<CGAL::Gmpq>, 8, 3, 0, 8, 3> >(Eigen::MatrixBase<Eigen::Matrix<CGAL::Lazy_exact_nt<CGAL::Gmpq>, 8, 3, 0, 8, 3> > const&, Eigen::PlainObjectBase<Eigen::Matrix<CGAL::Lazy_exact_nt<CGAL::Gmpq>, 8, 3, 0, 8, 3> >&);
template void igl::copyleft::cgal::assign<Eigen::Matrix<CGAL::Lazy_exact_nt<CGAL::Gmpq>, 8, 3, 0, 8, 3>, Eigen::Matrix<double, 8, 3, 0, 8, 3> >(Eigen::MatrixBase<Eigen::Matrix<CGAL::Lazy_exact_nt<CGAL::Gmpq>, 8, 3, 0, 8, 3> > const&, Eigen::PlainObjectBase<Eigen::Matrix<double, 8, 3, 0, 8, 3> >&);
#endif
