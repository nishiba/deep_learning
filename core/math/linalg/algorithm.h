#pragma once

#include <core/boost.h>
#include <numeric>
#include <core/math/range.h>

namespace core {
    inline double max(const ublas::vector<double>& x)
    {
        const auto y = std::max_element(x.begin(), x.end());
        return y != x.end() ? *y : -std::numeric_limits<double>::max();
    }

    inline double sum(const ublas::vector<double>& x)
    {
        return std::accumulate(x.begin(), x.end(), 0.0);
    }

    inline ublas::vector<double> extract(
        const ublas::vector<double>& x,
        const std::vector<std::size_t>& indexes)
    {
        ublas::vector<double> y(indexes.size());
        for (const auto i : core::range(y)) {
            y[i] = x[indexes[i]];
        }
        return y;
    }

    inline ublas::matrix<double> extract_rows(
        const ublas::matrix<double>& x,
        const std::vector<std::size_t>& indexes)
    {
        ublas::matrix<double> y(indexes.size(), x.size2());
        for (const auto i : core::range(0, y.size1())) {
            ublas::row(y, i) = ublas::row(x, indexes[i]);
        }
        return y;
    }
}