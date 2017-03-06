//  @ Project : Magnus
//  @ File Name : exp.h
//  @ Date : 2017-03-03
//  @ Author : Stefanos Carlström
//
//
#ifndef EXP_H

#define EXP_H

#include "operator.h"

namespace magnus {
  template<class T>
  class Exp {
  public:
    Exp(){}
    virtual ~Exp(){}

    virtual void operator()(const A<T>& A,
                            T mu,
                            T* w, const T* v,
                            bool verbose = false) = 0;
  };
}

#endif //EXP_H
