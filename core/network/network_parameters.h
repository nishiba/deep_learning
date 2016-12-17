#pragma once
#include <vector>
#include <core/boost.h>
#include <core/network/network_layout.h> 

namespace core {
    class network_parameters {
    public:
        explicit network_parameters(const network_layout& layout)
            : weights_(layout.hidden().size()),
            biases_(layout.hidden().size())
        {
            std::vector<std::size_t> sizes;
            sizes.push_back(layout.input());
            sizes.insert(sizes.end(), layout.hidden().begin(), layout.hidden().end());
            sizes.push_back(layout.output());

            for (std::size_t i = 0; i < weights_.size(); ++i) {
                weights_[i] = ublas::zero_matrix<double>(sizes[i], sizes[i + 1]);
                biases_[i] = ublas::zero_vector<double>(sizes[i + 1]);
            }
        }

        ublas::matrix<double>& weight(std::size_t i)
        {
            return weights_[i];
        }
        ublas::vector<double>& bias(std::size_t i)
        {
            return biases_[i];
        }
        const ublas::matrix<double>& weight(std::size_t i) const
        {
            return weights_[i];
        }
        const ublas::vector<double>& bias(std::size_t i) const
        {
            return biases_[i];
        }
        std::size_t size() const 
        {
            return weights_.size();
        }
        network_parameters& operator-=(const network_parameters& x)
        {
            for (auto i : core::range(0, x.size())) {
                ublas::noalias(this->weight(i)) -= x.weight(i);
                ublas::noalias(this->bias(i)) -= x.bias(i);
            }
            return *this;
        }
    private:
        std::vector<ublas::matrix<double>> weights_;
        std::vector<ublas::vector<double>> biases_;
    };


    network_parameters zeros_layout_with(
        const network_parameters& x)
    {
        std::size_t s = x.size();
        if (s == 0) {
            return network_parameters(network_layout());
        }

        network_layout layout;
        layout.set_input(x.weight(0).size1());
        layout.set_output(x.weight(s - 1).size1());
        for (std::size_t i : core::range(1, s)) {
            layout.push_back_hidden(x.weight(i).size1());
        }
        return network_parameters{ layout };
    }

    inline network_parameters operator *(
        const double a,
        const network_parameters& x)
    {
        network_parameters y = zeros_layout_with(x);
        for (auto i : core::range(0, x.size())) {
            ublas::noalias(y.weight(i)) = a * x.weight(i);
            ublas::noalias(y.bias(i)) = a * x.bias(i);
        }
        return y;
    }

    inline network_parameters operator -(
        const network_parameters& x,
        const network_parameters& y)
    {
        network_parameters z = zeros_layout_with(x);
        for (auto i : core::range(0, x.size())) {
            ublas::noalias(y.weight(i)) = x.weight(i) - y.weight(i);
            ublas::noalias(y.bias(i)) = x.bias(i) - y.bias(i);
        }
        return z;
    }
}