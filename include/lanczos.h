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
  template<class T>
  void exp_lanczos(std::size_t n,
                   const A<T>& A,
                   const T* v,
                   T mu, std::size_t m,
                   T* w, T* V, T* wtilde,
                   T* Hm, T* Tk, T* Tkm,
                   typename Real<T>::type atol,
                   typename Real<T>::type rtol,
                   std::size_t kmax,
                   bool verbose);
  
  template<class T>
  class Lanczos : public Krylov<T> {
  public:
    Lanczos(std::size_t m, std::size_t n,
            typename Real<T>::type atol = typename Real<T>::type(1e-8),
            typename Real<T>::type rtol = typename Real<T>::type(1e-4),
            std::size_t kmax=14)
      : Krylov<T>(m, n),
      Hm(m*m, T(0)), wtilde(m),
      Tk(m*m), Tkm(m*m),
      atol(atol), rtol(rtol),
      kmax(kmax)
    {}

    void operator()(const A<T>& A,
                    T mu,
                    T* w, const T* v,
                    bool verbose = false)
    {
      exp_lanczos(n, A, v, mu, m, w,
                  &Vm[0], &wtilde[0],
                  &Hm[0], &Tk[0], &Tkm[0],
                  atol, rtol, kmax,
                  verbose);
    }

    std::vector<T> Hm, // Subspace Hamiltonian
      wtilde, // Subspace vector
      Tk, Tkm; // Chebyshev polynomials, for subspace matrix exponential
    typename Real<T>::type atol, rtol; // Relative and absolute tolerances
    std::size_t kmax;
    using Krylov<T>::m;
    using Krylov<T>::n;
    using Krylov<T>::Vm;
  };
}

#endif //LANCZOS_H
