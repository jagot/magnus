//  @ Project : Magnus
//  @ File Name : midpoint.h
//  @ Date : 2017-03-06
//  @ Author : Stefanos Carlström
//
//
#ifndef MIDPOINT_H

#define MIDPOINT_H

#include "magnus.h"

namespace magnus {
  template<class T>
  class Midpoint : public Magnus<T> {
  public:
    Midpoint(std::size_t n,
             std::shared_ptr<Exp<T>> exp)
      : Magnus<T>(n, exp){}
    virtual ~Midpoint(){}

    void operator()(int i,
                    const At<T>& A, T mu,
                    T* y, const T* x)
    {
      (*exp)([&](T* y, T* x)
             { A(i+0.5, y, x); },
             mu, y, x);
    }

    using Magnus<T>::exp;
  };
} // magnus

#endif //MIDPOINT_H
