//  @ Project : Magnus
//  @ File Name : krylov.h
//  @ Date : 2017-03-03
//  @ Author : Stefanos Carlström
//
//
#ifndef KRYLOV_H

#define KRYLOV_H

#include "exp.h"
#include <cstddef>
#include <vector>
#include "operator.h"

namespace magnus {
  template<class T>
  class Krylov : public Exp<T> {
  public:
    Krylov(std::size_t m, std::size_t n)
      : m(m), n(n), Vm((m+1)*n) {}
    virtual ~Krylov(){}

    virtual void operator()(const A<T>& A,
                            T mu,
                            T* w, const T* v,
                            bool verbose = false) = 0;

    const std::size_t m, n;
    std::vector<T> Vm;
  };
} // magnus

#endif //KRYLOV_H
