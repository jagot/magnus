//  @ Project : Magnus
//  @ File Name : chebyshev.h
//  @ Date : 2017-03-03
//  @ Author : Stefanos Carlström
//
//
#ifndef CHEBYSHEV_H

#define CHEBYSHEV_H

#include "chebyshev_bessel.h"
#include "cxxblas.h"
#include <algorithm>

namespace magnus {
  template<class T>
  void cheb_tri_exp(std::size_t m, std::size_t ldHm,
                    T* Hm,
                    T* Tk, T* Tkm,
                    T mu,
                    T* wtilde,
                    std::size_t kmax = 14)
  {
    std::fill(wtilde, wtilde+m, T(0));
    wtilde[0] = Jkik<T>[0];

    // T₀ ← Iₘ
    auto Tkm_p = Tkm;
    for(std::size_t i = 0; i < m; i++){
      *Tkm_p = 1;
      if(i < m-1) std::fill(Tkm_p+1, Tkm_p + ldHm + 1, 0);
      Tkm_p += ldHm + 1;
    }

    // T₁ ← μHₘ
    cxxblas::copy(ldHm*ldHm, Hm, 1, Tk, 1);
    cxxblas::scale(ldHm*ldHm, mu, Tk, 1);

    for(std::size_t k = 1; k < kmax; k++){
      cxxblas::axpy(m, Jkik<T>[k], Tk, 1, wtilde, 1);
      if(k < kmax-1){
        // Tₖ₊₁ ← 2μHₘTₖ - Tₖ₋₁
        cxxblas::gemm(CblasColMajor, CblasNoTrans, CblasNoTrans,
                      m, m, m,
                      T(2)*mu,
                      Hm, ldHm,
                      Tk, ldHm,
                      -T(1),
                      Tkm, ldHm);
        std::swap(Tk, Tkm);
      }
    }
  }
}  // magnus

#endif //CHEBYSHEV_H
