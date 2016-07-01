#ifndef _TBLIS_SUMV_HPP_
#define _TBLIS_SUMV_HPP_

#include "tblis.hpp"

namespace tblis
{

template <typename T> void tblis_sumv(idx_type n, const T* A, stride_type inc_A, T& sum);

template <typename T>    T tblis_sumv(idx_type n, const T* A, stride_type inc_A);

template <typename T> void tblis_sumv(const_row_view<T> A, T& sum);

template <typename T>    T tblis_sumv(const_row_view<T> A);

}

#endif