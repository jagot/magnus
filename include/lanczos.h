//  @ Project : Magnus
//  @ File Name : lanczos.h
//  @ Date : 2017-03-02
//  @ Author : Stefanos Carlström
//
//
#ifndef LANCZOS_H

#define LANCZOS_H

#include "krylov.h"

namespace magnus {
  template<class T, class R>
  void exp_lanczos(std::size_t n,
                   std::function<void(T*, T*)> A,
                   T* v,
                   T mu, std::size_t m,
                   T* w, T* V, T* wtilde,
                   T* Hm, T* Tk, T* Tkm,
                   R atol, R rtol,
                   bool verbose);
  
  template<class T, class R>
  class Lanczos : public Krylov<T> {
  public:
    Lanczos(std::size_t m, std::size_t n,
            R atol = R(1e-8),
            R rtol = R(1e-4))
      : Krylov<T>(m, n),
      Hm(m*m, T(0)), wtilde(m),
      Tk(m*m), Tkm(m*m),
      atol(atol), rtol(rtol)
    {}

    void operator()(std::function<void(T*, T*)> A,
                    T mu,
                    T* v, T* w,
                    bool verbose = false)
    {
      exp_lanczos(n, A, v, mu, m, w,
                  &Vm[0], &wtilde[0],
                  &Hm[0], &Tk[0], &Tkm[0],
                  atol, rtol, verbose);
    }

    std::vector<T> Hm, // Subspace Hamiltonian
      wtilde, // Subspace vector
      Tk, Tkm; // Chebyshev polynomials, for subspace matrix exponential
    R atol, rtol; // Relative and absolute tolerances
    using Krylov<T>::m;
    using Krylov<T>::n;
    using Krylov<T>::Vm;
  };
}

#endif //LANCZOS_H
