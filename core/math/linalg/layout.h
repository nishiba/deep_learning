#pragma once

#include <vector>
#include <core/boost.h>

namespace core {
    inline ublas::matrix<double> zeros_layout_with(
        const ublas::matrix<double>& x)
    {
        return ublas::zero_matrix<double>(x.size1(), x.size2());
    }

    inline ublas::vector<double> zeros_layout_with(
        const ublas::vector<double>& x)
    {
        return ublas::zero_vector<double>(x.size());
    }
}