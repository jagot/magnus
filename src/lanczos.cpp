#include "lanczos.h"
#include "chebyshev.h"
#include "cxxblas.h"

#include <iostream>

namespace magnus {
  template<class T, class R>
  void exp_lanczos(std::size_t n,
                   std::function<void(T*, T*)> A,
                   T* v,
                   T mu, std::size_t m,
                   T* w, T* V, T* wtilde,
                   T* Hm, T* Tk, T* Tkm,
                   R atol, R rtol,
                   bool verbose)
  {
    if(verbose) std::cout << "Lanczos" << std::endl;

    auto beta0 = cxxblas::norm2(n, v, 1);
    auto eps = atol + rtol * beta0;

    if(verbose)
      std::cout << "Initial norm: β₀ = "
                << beta0
                << ", stopping threshold: "
                << eps
                << std::endl;

    cxxblas::copy(n, v, 1, V, 1);
    cxxblas::scale(n, T(1)/beta0, V, 1);

    T *x = V, *y = V + n;
    std::size_t jj = 1; // Which Krylov subspace to use in the end

    R a, b, bp;

    T* Hmm_p = Hm;

    for(std::size_t j = 0; j < m; j++){
      A(y,x);

      // Orthogonalisation to previous vectors
      a = std::real(cxxblas::dot(n, x, 1, y, 1));
      Hmm_p[0] = a;
      if(j > 0){
        cxxblas::axpy(n, -T(bp), x-n, 1, y, 1);
        Hmm_p[-1] = Hmm_p[-m] = bp;
      }
      cxxblas::axpy(n, -T(a), x, 1, y, 1);
      b = cxxblas::norm2(n, y, 1);
      cxxblas::scale(n, T(1)/b, y, 1);

      cheb_tri_exp(j+1, m, Hm, Tk, Tkm, mu, wtilde);

      auto sigma = b*std::abs(wtilde[j]);

      if(verbose)
        std::cout << "iter " << j
                  << ", α[" << j << "] " << a
                  << ", β[" << j << "] " << b
                  << ", σ " << sigma
                  << std::endl << std::endl;

      if(sigma < eps) break;
      else if(j < m) jj++;

      x += n;
      y += n;
      bp = b;
      Hmm_p += m + 1;
    }
    if(verbose) std::cout << "Krylov subspace size: " << jj << std::endl;
    cxxblas::gemv(CblasColMajor, CblasNoTrans,
                  n, jj,
                  beta0, V, n,
                  wtilde, 1,
                  0, w, 1);
  }

#define EXP_LANCZOS(T,R)                                \
  template                                              \
  void exp_lanczos<T>(std::size_t n,                    \
                      std::function<void(T*, T*)> A,    \
                      T* v,                             \
                      T mu, std::size_t m,              \
                      T* w, T* V, T* wtilde,            \
                      T* Hm, T* Tk, T* Tkm,             \
                      R atol, R rtol,                   \
                      bool verbose);
  EXP_LANCZOS(float, float);
  EXP_LANCZOS(double, double);
  EXP_LANCZOS(std::complex<float>, float);
  EXP_LANCZOS(std::complex<double>, double);
} // magnus
