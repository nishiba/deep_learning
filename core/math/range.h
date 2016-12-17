#pragma once

#include <vector>

namespace core {
    inline std::vector<std::size_t> range(
        const std::size_t begin, const std::size_t end)
    {
        std::vector<std::size_t> x;
        x.reserve(end - begin - 1);
        for (std::size_t i = begin; i < end; ++i) {
            x.push_back(i);
        }
        return x;
    }

    template <typename T>
    inline std::vector<std::size_t> range(const T& t)
    {
        return range(0, t.size());
    }


}