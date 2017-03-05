//  @ Project : Magnus
//  @ File Name : chebyshev_bessel.h
//  @ Date : 2017-03-03
//  @ Author : Stefanos Carlström
//
//
#ifndef CHEBYSHEV_BESSEL_H

#define CHEBYSHEV_BESSEL_H

namespace magnus {
  // Table of g(k)i^kJₖ(-i) ∈ R, for k ∈ [0,40], where g(k) = 2, except g(0) = 1.
  template<class T>
  constexpr T Jkik[] = {
    1.2660658777520082e+00,
    1.1303182079849701e+00,
    2.7149533953407667e-01,
    4.4336849848663810e-02,
    5.4742404420937323e-03,
    5.4292631191394422e-04,
    4.4977322954295190e-05,
    3.1984364624019926e-06,
    1.9921248066727963e-07,
    1.1036771725517341e-08,
    5.5058960796737495e-10,
    2.4979566169849818e-11,
    1.0391522306785740e-12,
    3.9912633564143977e-14,
    1.4237580108256627e-15,
    4.7409261025615024e-17,
    1.4801800572082964e-18,
    4.3499194949441473e-20,
    1.2074289272797564e-21,
    3.1753567370594433e-23,
    7.9336719716380284e-25,
    1.8879484042289102e-26,
    4.2886738765925794e-28,
    9.3189852817774746e-30,
    1.9406469749017366e-31,
    3.8798022492260213e-33,
    7.4585028873915884e-35,
    1.3807477824110445e-36,
    2.4648623717710954e-38,
    4.2485421925059793e-40,
    7.0790011762129451e-42,
    1.1414867782540921e-43,
    1.7831510375432693e-45,
    2.7011422638737947e-47,
    3.9714338657414944e-49,
    5.6723516956121426e-51,
    7.8767881305332338e-53,
    1.0642416282087371e-54,
    1.4000817885528946e-56,
    1.7946890853905641e-58,
    2.2430194826630055e-60,
  };
}  // magnus

#endif //CHEBYSHEV_BESSEL_H