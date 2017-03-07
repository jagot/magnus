//  @ Project : Magnus
//  @ File Name : operator.h
//  @ Date : 2017-03-07
//  @ Author : Stefanos Carlström
//
//
#ifndef OPERATOR_H

#define OPERATOR_H

#include <functional>
#include <complex>

namespace magnus {
  template<typename T>
  class Real {
  public:
    typedef T type;
  };

  template<class T>
  class Real<std::complex<T>> {
  public:
    typedef T type;
  };

  template<typename T>
  class Op {
  public:
    typedef typename Real<T>::type Time;
    typedef T S;
    typedef std::function<void(typename Real<T>::type, T*, T*)> OpFunc;
  };

  // Operators of no time dependence, A
  template<class T>
  using A = std::function<void(T*, T*)>;

  // Operators of general time dependence, A(t)
  template<class T>
  using At = typename Op<T>::OpFunc;

  // Operators with time dependence
  // A(t) = B + f(t)C
  template<class T>
  struct BftC {
    std::function<T(typename Real<T>::type)> f;
    std::function<void(T,T*,T*)> A;
  };
}  // magnus

#endif //OPERATOR_H
