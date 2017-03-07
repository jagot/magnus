//  @ Project : Magnus
//  @ File Name : cfet4.h
//  @ Date : 2017-03-06
//  @ Author : Stefanos Carlström
//
//
#ifndef CFET4_H

#define CFET4_H

#include "magnus.h"
#include <stdexcept>

namespace magnus {
  template<class T>
  class CFET4 : public Magnus<T> {
  public:
    CFET4(std::size_t n,
          std::shared_ptr<Exp<T>> exp)
      : Magnus<T>(n, exp){}
    virtual ~CFET4(){}

    void operator()(int,
                    const At<T>&, T,
                    T*, T*)
    {
      throw std::runtime_error("Unimplemented for integrator CFET4");
    }

    void operator()(int i,
                    const BftC<T>& A, T mu,
                    T* y, T* x)
    {
      const typename Real<T>::type
        di1 = 1./2 - std::sqrt(3./20),
        di2 = 1./2,
        di3 = 1./2 + std::sqrt(3./20);
      
      const typename Real<T>::type
        h1 = 37./66 - 400./957*std::sqrt(5./3),
        h2 = -4./33,
        h3 = 37./66 + 400./957*std::sqrt(5./3),
        h4 = -11./162,
        h5 = 92./81;

      T f1p = A.f(i+di1),
        f2p = A.f(i+di2),
        f3p = A.f(i+di3);
      
      T f1 = h1*f1p + h2*f2p + h3*f3p,
        f2 = h4*f1p + h5*f2p + h4*f3p,
        f3 = h3*f1p + h2*f2p + h1*f3p;

      const typename Real<T>::type
        dmu1 = (11./40),
        dmu2 = (9./20);
      
      (*exp)([&](T* y, T* x)
             { A.A(f3, y, x); },
             dmu1*mu, y, x);
      
      (*exp)([&](T* y, T* x)
             { A.A(f2, y, x); },
             dmu2*mu, x, y); // The swapping here is intentional (x
                             // used as temporary)
      
      (*exp)([&](T* y, T* x)
             { A.A(f1, y, x); },
             dmu1*mu, y, x);
    }

    using Magnus<T>::exp;
  };
} // magnus

#endif //CFET4_H
