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
  };
}

#include "lanczos.h"
#include "midpoint.h"

#endif //MAGNUS_H
