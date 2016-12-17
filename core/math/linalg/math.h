#pragma once

#include <core/boost.h>
#include <core/math/linalg/unary_vector_expression.h>

namespace core {
    template <typename E>
    auto exp(const ublas::vector_expression<E>& x)
    {
        return make_unary_vector_expression(x, [](const auto& x) {return std::exp(x); });
    }

    template <typename E>
    auto log(const ublas::vector_expression<E>& x)
    {
        return make_unary_vector_expression(x, [](const auto& x) {return std::log(x); });
    }
}