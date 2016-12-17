#pragma once

#include <core/boost.h>

namespace core {
    template <typename E>
    inline ublas::vector<double> //TODO return expression type
    operator -(
        const ublas::vector_expression<E>& v,
        const typename E::value_type& x)
    {
        return v() - ublas::scalar_vector<typename E::value_type>(v().size(), x);
    }

    template <typename E>
    inline ublas::vector<double> //TODO return expression type
        operator +(
            const ublas::vector_expression<E>& v,
            const typename E::value_type& x)
    {
        return v() + ublas::scalar_vector<typename E::value_type>(v().size(), x);
    }

    template <typename E>
    inline ublas::vector<double> //TODO return expression type
        operator /(
            const typename E::value_type& x,
            const ublas::vector_expression<E>& v)
    {
        return ublas::element_div(
            ublas::scalar_vector<typename E::value_type>(v().size(), x),
            v());
    }
}