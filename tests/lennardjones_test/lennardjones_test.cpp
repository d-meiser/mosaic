#include <gtest/gtest.h>
#include <lennardjones.h>

#include <cmath>

TEST(LennardJones, Constructor) {
    float epsilon = 1.0f;
    float sigma = 1.0f;
    MoLennardJones lj(epsilon, sigma);
}

TEST(LennardJones, IsZeroAtSigma) {
    float sigma = 23.0f;
    MoLennardJones lj(11.0f, sigma);
    float potential = lj.evaluateAt(sigma);
    ASSERT_NEAR(0.0f, potential, 1.0e-6f);
}

TEST(LennardJones, IsEpsilonAtMinimum) {
    float sigma = 23.0f;
    float epsilon = 17.0f;
    MoLennardJones lj(epsilon, sigma);
    float potential = lj.evaluateAt(std::pow(2.0f, 1.0f / 6.0f) * sigma);
    ASSERT_NEAR(-epsilon, potential, 1.0e-6f);
}

TEST(LennardJones, FallsOffAs1OverRToThe6th) {
    float sigma = 10.0f;
    MoLennardJones lj(11.0f, sigma);
    float potential1 = lj.evaluateAt(20 * sigma);
    float potential2 = lj.evaluateAt(40 * sigma);
    ASSERT_NEAR(potential1 / (2 * 2 * 2 * 2 * 2 * 2), potential2,
                1.0e-8f);
}

TEST(LennardJones, CanBeCopied) {
    float sigma = 10.0f;
    MoLennardJones lj(11.0f, sigma);
    float potential1 = lj.evaluateAt(20 * sigma);
    MoLennardJones lj2(lj);
    float potential2 = lj2.evaluateAt(20 * sigma);
    ASSERT_FLOAT_EQ(potential1, potential2);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
