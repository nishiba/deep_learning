#pragma once

#include <core/boost.h>
#include <core/math/linalg/operator.h>
#include <core/math/linalg/math.h>
#include <core/math/linalg/algorithm.h>

namespace core {
    inline ublas::vector<double> softmax(const ublas::vector<double>& x)
    {
        const double c = core::max(x);
        const ublas::vector<double> e = core::exp(x - c);
        const double sum = core::sum(e);
        return e / sum;
    }

    inline ublas::vector<double> sigmoid(const ublas::vector<double>& x)
    {
        return 1.0 / (core::exp(-x) + 1.0);
    }

    inline double cross_entropy_error(
        const ublas::vector<double>& y,
        const ublas::vector<double>& t)
    {
        return -ublas::inner_prod(t, core::log(y));
    }
}