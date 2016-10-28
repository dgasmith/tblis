#ifndef _TBLIS_1V_DOT_H_
#define _TBLIS_1V_DOT_H_

#include "util/thread.h"
#include "util/basic_types.h"

#ifdef __cplusplus

namespace tblis
{

extern "C"
{

#endif

void tblis_vector_dot(const tblis_comm* comm, const tblis_config* cfg,
                      const tblis_vector* A, const tblis_vector* B,
                      tblis_scalar* result);

#ifdef __cplusplus

}

template <typename T>
void dot(const_row_view<T> A, const_row_view<T> B, T& result)
{
    tblis_vector A_s(A);
    tblis_vector B_s(B);
    tblis_scalar result_s(result);

    tblis_vector_dot(nullptr, nullptr, &A_s, &B_s, &result_s);
}

template <typename T>
void dot(single_t s, const_row_view<T> A, const_row_view<T> B, T& result)
{
    tblis_vector A_s(A);
    tblis_vector B_s(B);
    tblis_scalar result_s(result);

    tblis_vector_dot(tblis_single, nullptr, &A_s, &B_s, &result_s);
}

template <typename T>
void dot(const communicator& comm, const_row_view<T> A, const_row_view<T> B, T& result)
{
    tblis_vector A_s(A);
    tblis_vector B_s(B);
    tblis_scalar result_s(result);

    tblis_vector_dot(comm, nullptr, &A_s, &B_s, &result_s);
}

template <typename T>
T dot(const_row_view<T> A, const_row_view<T> B)
{
    T result;
    dot(A, B, result);
    return result;
}

template <typename T>
T dot(single_t s, const_row_view<T> A, const_row_view<T> B)
{
    T result;
    dot(s, A, B, result);
    return result;
}

template <typename T>
T dot(const communicator& comm, const_row_view<T> A, const_row_view<T> B)
{
    T result;
    dot(comm, A, B, result);
    return result;
}

}

#endif

#endif
