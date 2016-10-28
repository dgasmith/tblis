#ifndef _TBLIS_KERNELS_1V_REDUCE_HPP_
#define _TBLIS_KERNELS_1V_REDUCE_HPP_

#include "util/thread.h"
#include "util/basic_types.h"
#include "util/macros.h"

namespace tblis
{

template <typename T>
using reduce_ukr_t =
    void (*)(const communicator& comm, reduce_t op, len_type n,
             const T* A, stride_type inc_A, T& value, len_type& idx);

template <typename T>
void reduce_ukr_def(const communicator& comm, reduce_t op, len_type n,
                    const T* A, stride_type inc_A, T& value, len_type& idx)
{
    len_type first, last;
    std::tie(first, last, std::ignore) = comm.distribute_over_threads(n);

    A += first*inc_A;
    n = last-first;

    if (op == REDUCE_SUM)
    {
        TBLIS_SPECIAL_CASE(inc_A == 1,
        {
            for (len_type i = 0;i < n;i++) value += A[i*inc_A];
        })
    }
    else if (op == REDUCE_SUM_ABS)
    {
        TBLIS_SPECIAL_CASE(inc_A == 1,
        {
            for (len_type i = 0;i < n;i++) value += std::abs(A[i*inc_A]);
        })
    }
    else if (op == REDUCE_MAX)
    {
        TBLIS_SPECIAL_CASE(inc_A == 1,
        {
            for (len_type i = 0;i < n;i++)
            {
                if (A[i*inc_A] > value)
                {
                    value = A[i*inc_A];
                    idx = (first+i)*inc_A;
                }
            }
        })
    }
    else if (op == REDUCE_MAX_ABS)
    {
        TBLIS_SPECIAL_CASE(inc_A == 1,
        {
            for (len_type i = 0;i < n;i++)
            {
                if (std::abs(A[i*inc_A]) > value)
                {
                    value = std::abs(A[i*inc_A]);
                    idx = (first+i)*inc_A;
                }
            }
        })
    }
    else if (op == REDUCE_MIN)
    {
        TBLIS_SPECIAL_CASE(inc_A == 1,
        {
            for (len_type i = 0;i < n;i++)
            {
                if (A[i*inc_A] < value)
                {
                    value = A[i*inc_A];
                    idx = (first+i)*inc_A;
                }
            }
        })
    }
    else if (op == REDUCE_MIN_ABS)
    {
        TBLIS_SPECIAL_CASE(inc_A == 1,
        {
            for (len_type i = 0;i < n;i++)
            {
                if (std::abs(A[i*inc_A]) < value)
                {
                    value = std::abs(A[i*inc_A]);
                    idx = (first+i)*inc_A;
                }
            }
        })
    }
    else if (op == REDUCE_NORM_2)
    {
        TBLIS_SPECIAL_CASE(inc_A == 1,
        {
            for (len_type i = 0;i < n;i++) value += norm2(A[i*inc_A]);
        })
    }
}

}

#endif
