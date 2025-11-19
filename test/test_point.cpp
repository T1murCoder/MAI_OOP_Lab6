#include <gtest/gtest.h>
#include "../include/utils/Point.h"
#include <cmath>

class PointTest : public ::testing::Test {
protected:
    Point p1{100.0f, 200.0f};
    Point p2{150.0f, 250.0f};
    Point p3{100.0f, 200.0f};
};

TEST_F(PointTest, DefaultConstructor) {
    Point p;
    EXPECT_FLOAT_EQ(p.getX(), 0.0f);
    EXPECT_FLOAT_EQ(p.getY(), 0.0f);
}

TEST_F(PointTest, ParameterizedConstructor) {
    EXPECT_FLOAT_EQ(p1.getX(), 100.0f);
    EXPECT_FLOAT_EQ(p1.getY(), 200.0f);
}

TEST_F(PointTest, Getters) {
    EXPECT_FLOAT_EQ(p1.getX(), 100.0f);
    EXPECT_FLOAT_EQ(p1.getY(), 200.0f);
}

TEST_F(PointTest, ValidCoordinates) {
    Point valid{250.0f, 250.0f};
    EXPECT_TRUE(valid.isValid());
    
    Point edge1{0.0f, 0.0f};
    EXPECT_TRUE(edge1.isValid());
    
    Point edge2{500.0f, 500.0f};
    EXPECT_TRUE(edge2.isValid());
}

TEST_F(PointTest, InvalidCoordinates) {
    Point invalid1{-1.0f, 100.0f};
    EXPECT_FALSE(invalid1.isValid());
    
    Point invalid2{100.0f, 501.0f};
    EXPECT_FALSE(invalid2.isValid());
    
    Point invalid3{-10.0f, -10.0f};
    EXPECT_FALSE(invalid3.isValid());
    
    Point invalid4{600.0f, 600.0f};
    EXPECT_FALSE(invalid4.isValid());
}

TEST_F(PointTest, DistanceCalculation) {
    Point a{0.0f, 0.0f};
    Point b{3.0f, 4.0f};
    
    float distance = a.distanceTo(b);
    EXPECT_FLOAT_EQ(distance, 5.0f);
}

TEST_F(PointTest, DistanceToSelf) {
    float distance = p1.distanceTo(p1);
    EXPECT_FLOAT_EQ(distance, 0.0f);
}

TEST_F(PointTest, DistanceSymmetric) {
    float dist1 = p1.distanceTo(p2);
    float dist2 = p2.distanceTo(p1);
    EXPECT_FLOAT_EQ(dist1, dist2);
}

TEST_F(PointTest, EqualityOperator) {
    EXPECT_TRUE(p1 == p3);
    EXPECT_FALSE(p1 == p2);
}

TEST_F(PointTest, InequalityOperator) {
    EXPECT_TRUE(p1 != p2);
    EXPECT_FALSE(p1 != p3);
}