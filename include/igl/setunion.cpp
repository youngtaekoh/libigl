// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2016 Alec Jacobson <alecjacobson@gmail.com>
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
#include "setunion.h"
#include "unique.h"

template <
  typename DerivedA,
  typename DerivedB,
  typename DerivedC,
  typename DerivedIA,
  typename DerivedIB>
IGL_INLINE void igl::setunion(
  const Eigen::DenseBase<DerivedA> & A,
  const Eigen::DenseBase<DerivedB> & B,
  Eigen::PlainObjectBase<DerivedC> & C,
  Eigen::PlainObjectBase<DerivedIA> & IA,
  Eigen::PlainObjectBase<DerivedIB> & IB)
{
  DerivedC CS(A.size()+B.size(),1);
  {
    int k = 0;
    for(int j = 0;j<A.cols();j++)
    {
      for(int i = 0;i<A.rows();i++)
      {
        CS(k++) = A(i,j);
      }
    }
    for(int j = 0;j<B.cols();j++)
    {
      for(int i = 0;i<B.rows();i++)
      {
        CS(k++) = B(i,j);
      }
    }
    assert(k==CS.size());
  }
  DerivedIA IAC;
  {
    DerivedIA IC;
    unique(CS,C,IAC,IC);
  }
  const int nia = (IAC.array()<A.size()).count();
  IA.resize(nia);
  IB.resize(IAC.size() - nia);
  {
    int ka = 0;
    int kb = 0;
    for(int i = 0;i<IAC.size();i++)
    {
      if(IAC(i)<A.size())
      {
        IA(ka++) = IAC(i);
      }else
      {
        IB(kb++) = IAC(i)-A.size();
      }
    }
    assert(ka == IA.size());
    assert(kb == IB.size());
  }

}