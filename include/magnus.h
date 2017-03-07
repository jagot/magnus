//  @ Project : Magnus
//  @ File Name : magnus.h
//  @ Date : 2017-03-02
//  @ Author : Stefanos Carlström
//
//
#ifndef MAGNUS_H

#define MAGNUS_H

#include "exp.h"
#include <cstddef>
#include <memory>
#include "operator.h"

namespace magnus {
  template<class T>
  class Magnus {
  public:
    Magnus(std::size_t n,
           std::shared_ptr<Exp<T>> exp)
      : n(n), exp(exp){}
    virtual ~Magnus(){}

    std::size_t n;
    std::shared_ptr<Exp<T>> exp;

    virtual void operator()(int i,
                            const At<T>& A, T mu,
                            T* y, T* x) = 0;


    virtual void operator()(int i,
                            const BftC<T>& A, T mu,
                            T* y, T* x) = 0;
  };
}

#include "lanczos.h"
#include "midpoint.h"
#include "cfet4.h"

#endif //MAGNUS_H
