#include "stdafx.h"
#include <gtest/gtest.h>
#include <core/math/math.h>

using namespace core;

TEST(softmax, case0) {
    ublas::vector<double> x{2};
    x[0] = 1.0;
    x[1] = 2.0;

    const ublas::vector<double> y = softmax(x);

    EXPECT_EQ(exp(x[0]) / (exp(x[0]) + exp(x[1])), y[0]);
    EXPECT_EQ(exp(x[1]) / (exp(x[0]) + exp(x[1])), y[1]);
}

TEST(sigmoid, case0) {
    ublas::vector<double> x{ 2 };
    x[0] = 1.0;
    x[1] = 2.0;

    const ublas::vector<double> y = sigmoid(x);

    EXPECT_EQ(1.0 / (exp(-x[0]) + 1.0), y[0]);
    EXPECT_EQ(1.0 / (exp(-x[1]) + 1.0), y[1]);
}

TEST(cross_entropy_error, case0) {
    ublas::vector<double> y{ 2 };
    y[0] = 1.0;
    y[1] = 2.0;

    ublas::vector<double> t{ 2 };
    t[0] = 1.1;
    t[1] = 2.1;

    const double x = cross_entropy_error(y, t);

    EXPECT_EQ(
        - t[0] * log(y[0]) - t[1] * log(y[1]), 
        x);
}

