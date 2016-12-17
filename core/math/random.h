#pragma once

#include <vector>
#include <random>
#include <core/math/range.h>

namespace core {
    class random {
    public:
        explicit random(const std::size_t seed = 1234567)
        : e_(seed)
        {}
        std::vector<std::size_t> choice(
            const std::size_t upper, const std::size_t size)
        {
            std::vector<std::size_t> x;
            x.reserve(size);
            std::uniform_int_distribution<std::size_t> d;
            for (auto i : core::range(0, size)) {
                x.push_back(d(e_));
            }
            return x;
        }
    private:
        std::mt19937 e_;
    };
}