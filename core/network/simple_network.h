#pragma once

#include <vector>
#include <core/boost.h>
#include <core/math/math.h>
#include <core/math/range.h>
#include <core/math/random.h>
#include <core/math/linalg/layout.h>
#include <core/network/network_layout.h>
#include <core/network/network_parameters.h>

namespace core {
    class simple_network {
    public:
        explicit simple_network(const network_layout layout)
            : p_(layout)
        {
        }
        ublas::vector<double> predict(const ublas::vector<double>& x) const
        {
            //TODO layout check
            ublas::vector<double> z;
            for (std::size_t i = 0; i < p_.size(); ++i) {
                z = ublas::prod(x, p_.weight(i)) + p_.bias(i);
                if (i + 1 != p_.size()) {
                    z = sigmoid(z);
                }
                else {
                    z = softmax(z);
                }
            }
            return z;
        }
        void learn(
            const ublas::matrix<double>& x,
            const ublas::matrix<double>& t,
            const double learning_rate)
        {
            //TODO layout check.
            const network_parameters g = this->gradient(x, t);
            p_ -= learning_rate * g;
        }

        std::vector<double> learn(
            const ublas::matrix<double>& x,
            const ublas::matrix<double>& t,
            const std::size_t iteration_count,
            const std::size_t batch_size,
            const double learning_rate)
        {
            std::vector<double> loss;
            loss.reserve(iteration_count);
            //TODO layout check.
            core::random r{};
            for (auto i : core::range(iteration_count)) {
                const std::vector<std::size_t> mask = r.choice(x.size1(), batch_size);
                const auto x_batch = core::extract_rows(x, mask);
                const auto t_batch = core::extract_rows(t, mask);
                this->learn(x_batch, t_batch, learning_rate);
                loss.push_back(this->loss(x_batch, t_batch));
            }
            return loss;
        }

        double loss(
            const ublas::matrix<double>& x,
            const ublas::matrix<double>& t) const
        {
            //TODO layout check
            double sum = 0.0;
            for (auto i : core::range(x.size1())) {
                sum += cross_entropy_error(
                    this->predict(ublas::row(x, i)), ublas::row(t, i));
            }
            return sum / x.size1();
        }
    private:
        network_parameters gradient(
            const ublas::matrix<double>& x,
            const ublas::matrix<double>& t)
        {
            network_parameters g = core::zeros_layout_with(p_);

            for (std::size_t i : core::range(p_)) {
                g.weight(i) = gradient_impl(x, t, &p_.weight(i));
                g.bias(i) = gradient_impl(x, t, &p_.bias(i));
            }
            return g;
        }
        ublas::matrix<double> gradient_impl(
            const ublas::matrix<double>& x,
            const ublas::matrix<double>& t,
            ublas::matrix<double>* w) const
        {
            ublas::matrix<double> g = core::zeros_layout_with(*w);
            for (std::size_t i = 0; i < g.size1(); ++i) {
                for (std::size_t j = 0; j < g.size2(); ++j) {
                    g(i, j) = this->gradiend_impl(x, t, &(*w)(i, j));
                }
            }
            return g;
        }
        ublas::vector<double> gradient_impl(
            const ublas::matrix<double>& x,
            const ublas::matrix<double>& t,
            ublas::vector<double>* b) const
        {
            ublas::vector<double> g = core::zeros_layout_with(*b);
            for (std::size_t i : core::range(g)) {
                g(i) = this->gradiend_impl(x, t, &(*b)(i));
            }
            return g;
        }

        double gradiend_impl(
            const ublas::matrix<double>& x,
            const ublas::matrix<double>& t,
            double* a) const
        {
            const double h = 1e-4; //TODO remove magic number.
            const double save = *a;
            (*a) += h;
            const double v1 = this->loss(x, t);
            (*a) -= 2.0 * h;
            const double v0 = this->loss(x, t);
            (*a) = save;
            return (v1 - v0) / (2.0 * h);
        }
    private:
        network_parameters p_;
    };
}