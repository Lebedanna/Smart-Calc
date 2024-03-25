#include <iostream>

#include "../Model/s21_smart_calc_model.h"
#include "gtest/gtest.h"

TEST(CalcTest, NoResults) {
    s21::SmartCalcModel a;
    EXPECT_EQ(a.GetResult(), 0);
}

TEST(CalcTest, SmartCalc0) {
    s21::SmartCalcModel a;
    std::string input = "100 + 100";
    a.Calculate(input);
    EXPECT_EQ(a.GetResult(), 200);
    input = "-200 + 200";
    a.Calculate(input);
    EXPECT_EQ(a.GetResult(), 0);
}

TEST(CalcTest, SmartCalc1) {
    s21::SmartCalcModel a;
    std::string input = "-15";
    a.Calculate(input);
    EXPECT_EQ(a.GetResult(), -15);
}

TEST(CalcTest, SmartCalc2) {
    s21::SmartCalcModel a;
    std::string input = "15.4 + 1.2";
    double result_real = 15.4 + 1.2;
    a.Calculate(input);
    EXPECT_NEAR(a.GetResult(), result_real, 1e-6);
}

TEST(CalcTest, SmartCalc3) {
    s21::SmartCalcModel a;
    std::string input = "0.2/2";
    double result_real = 0.2 / 2;
    a.Calculate(input);
    EXPECT_NEAR(a.GetResult(), result_real, 1e-6);
}

TEST(CalcTest, SmartCalc4) {
    s21::SmartCalcModel a;
    std::string input = "9^4 - 78 / 5";
    double result_real = std::pow(9, 4) - 78 / 5.0;
    a.Calculate(input);
    EXPECT_NEAR(a.GetResult(), result_real, 1e-6);
}

TEST(CalcTest, SmartCalc5) {
    s21::SmartCalcModel a;
    std::string input = "-45.6/5-67*4-(+8*2-5)";
    double result_real = -45.6 / 5 - 67 * 4 - (+8 * 2 - 5);
    a.Calculate(input);
    EXPECT_NEAR(a.GetResult(), result_real, 1e-6);
}

TEST(CalcTest, SmartCalc6) {
    s21::SmartCalcModel a;
    std::string input = "-45%-5";
    double result_real = -45 % -5;
    a.Calculate(input);
    EXPECT_NEAR(a.GetResult(), result_real, 1e-6);
}

TEST(CalcTest, SmartCalc7) {
    s21::SmartCalcModel a;
    std::string input = "999.99999 + 0.0001 + (9000^4 - 78 / 5)";
    double result_real = 999.99999 + 0.0001 + (pow(9000, 4) - 78 / 5.0);
    a.Calculate(input);
    EXPECT_NEAR(a.GetResult(), result_real, 1e-6);
}

TEST(CalcTest, SmartCalc8) {
    s21::SmartCalcModel a;
    std::string input = "-45.6/5-67*4-(+8*2-5)";
    double result_real = -45.6 / 5 - 67 * 4 - (+8 * 2 - 5);
    a.Calculate(input);
    EXPECT_NEAR(a.GetResult(), result_real, 1e-6);
}

TEST(CalcTest, SmartCalc9) {
    s21::SmartCalcModel a;
    std::string input = "0.00001 % 0.99";
    double result_real = fmod(0.00001, 0.999);
    a.Calculate(input);
    EXPECT_NEAR(a.GetResult(), result_real, 1e-6);
}

TEST(CalcTest, SmartCalc10) {
    s21::SmartCalcModel a;
    std::string input = "0.00001 % 0.99";
    double result_real = fmod(0.00001, 9.999);
    a.Calculate(input);
    EXPECT_NEAR(a.GetResult(), result_real, 1e-6);
}

TEST(CalcTest, SmartCalc11) {
    s21::SmartCalcModel a;
    std::string input = "0.000.01 + 0.999";
    bool status = a.Calculate(input);
    EXPECT_EQ(a.GetResult(), 0);
    EXPECT_EQ(status, false);
}

TEST(CalcTest, SmartCalc12) {
    s21::SmartCalcModel a;
    std::string input = "0.99 modulo 0.999";
    bool status = a.Calculate(input);
    EXPECT_EQ(a.GetResult(), 0);
    EXPECT_EQ(status, false);
}

TEST(CalcTest, SmartCalc13) {
    s21::SmartCalcModel a;
    std::string input = "0.00001+- 0.999=";
    bool status = a.Calculate(input);
    EXPECT_EQ(a.GetResult(), 0);
    EXPECT_EQ(status, false);
}

TEST(CalcTest, SmartCalc14) {
    s21::SmartCalcModel a;
    std::string input = "--+";
    bool status = a.Calculate(input);
    EXPECT_EQ(a.GetResult(), 0);
    EXPECT_EQ(status, false);
}

TEST(CalcTest, SmartCalc15) {
    s21::SmartCalcModel a;
    std::string input = "^0.999";
    bool status = a.Calculate(input);
    EXPECT_EQ(status, false);
}

TEST(CalcTest, SmartCalc16) {
    s21::SmartCalcModel a;
    std::string input = "ln(-100)";
    a.Calculate(input);
    EXPECT_TRUE(std::isnan(a.GetResult()));
}

TEST(CalcTest, SmartCalc17) {
    s21::SmartCalcModel a;
    std::string input = "asin(-10)";
    bool status = a.Calculate(input);
    EXPECT_TRUE(std::isnan(a.GetResult()));
    EXPECT_EQ(status, true);
}

TEST(CalcTest, SmartCalc18) {
    s21::SmartCalcModel a;
    std::string input = "sqrt(35)";
    double result_real = sqrt(35);
    a.Calculate(input);
    EXPECT_NEAR(a.GetResult(), result_real, 1e-6);
}

TEST(CalcTest, SmartCalc19) {
    s21::SmartCalcModel a;
    std::string input = "sin(5.89*67)-cos(4.99)-log(45.78)";
    double result_real = sin(5.89 * 67) - cos(4.99) - log10(45.78);
    a.Calculate(input);
    EXPECT_NEAR(a.GetResult(), result_real, 1e-6);
}

TEST(CalcTest, SmartCalc20) {
    s21::SmartCalcModel a;
    std::string input = "sin(5.8*67)";
    double result_real = sin(5.8 * 67);
    bool status = a.Calculate(input);
    EXPECT_NEAR(a.GetResult(), result_real, 1e-6);
    EXPECT_EQ(status, true);
}

TEST(CalcTest, SmartCalc21) {
    s21::SmartCalcModel a;
    std::string input = "cos(5.8*67)";
    double result_real = cos(5.8 * 67);
    bool status = a.Calculate(input);
    EXPECT_NEAR(a.GetResult(), result_real, 1e-6);
    EXPECT_EQ(status, true);
}

TEST(CalcTest, SmartCalc22) {
    s21::SmartCalcModel a;
    std::string input = "asin(0.2)";
    double result_real = asin(0.2);
    bool status = a.Calculate(input);
    EXPECT_NEAR(a.GetResult(), result_real, 1e-6);
    EXPECT_EQ(status, true);
}

TEST(CalcTest, SmartCalc23) {
    s21::SmartCalcModel a;
    std::string input = "((";
    bool status = a.Calculate(input);
    EXPECT_EQ(a.GetResult(), 0);
    EXPECT_EQ(status, false);
}

TEST(CalcTest, SmartCalc24) {
    s21::SmartCalcModel a;
    std::string input = "))";
    bool status = a.Calculate(input);
    EXPECT_EQ(a.GetResult(), 0);
    EXPECT_EQ(status, false);
}

TEST(CalcTest, SmartCalc25) {
    s21::SmartCalcModel a;
    std::string input = "(4+(2 + 3)";
    bool status = a.Calculate(input);
    EXPECT_EQ(a.GetResult(), 0);
    EXPECT_EQ(status, false);
}

TEST(CalcTest, SmartCalc26) {
    s21::SmartCalcModel a;
    std::string input = "4+(2 + 3) /3)";
    bool status = a.Calculate(input);
    EXPECT_EQ(a.GetResult(), 0);
    EXPECT_EQ(status, false);
}

TEST(CalcTest, SmartCalc27) {
    s21::SmartCalcModel a;
    std::string input = "((4+(2 + 3) /3)()";
    bool status = a.Calculate(input);
    EXPECT_EQ(a.GetResult(), 0);
    EXPECT_EQ(status, false);
}

TEST(CalcTest, SmartCalc28) {
    s21::SmartCalcModel a;
    std::string input = "+5+6";
    double result_real = +5 + 6;
    bool status = a.Calculate(input);
    EXPECT_NEAR(a.GetResult(), result_real, 1e-6);
    EXPECT_EQ(status, true);
}

TEST(CalcTest, SmartCalc29) {
    s21::SmartCalcModel a;
    std::string input = "+-5+6";
    bool status = a.Calculate(input);
    EXPECT_EQ(a.GetResult(), 0);
    EXPECT_EQ(status, false);
}

TEST(CalcTest, SmartCalc30) {
    s21::SmartCalcModel a;
    std::string input = "(56+67";
    bool status = a.Calculate(input);
    EXPECT_EQ(a.GetResult(), 0);
    EXPECT_EQ(status, false);
}

TEST(CalcTest, SmartCalc31) {
    s21::SmartCalcModel a;
    std::string input = "-8)";
    bool status = a.Calculate(input);
    EXPECT_EQ(a.GetResult(), 0);
    EXPECT_EQ(status, false);
}

TEST(CalcTest, SmartCalc32) {
    s21::SmartCalcModel a;
    std::string input =
            "tan(atan(0.5)) + acos(0.05 - 0.003) - cos(3^(2)) - "
            "ln(107-cos(sin(3.14)))";
    double result_real = tan(atan(0.5)) + acos(0.05 - 0.003) - cos(pow(3, 2)) -
                         log(107 - cos(sin(3.14)));
    bool status = a.Calculate(input);
    EXPECT_NEAR(a.GetResult(), result_real, 1e-6);
    EXPECT_EQ(status, true);
}

TEST(CalcTest, SmartCalc33) {
    s21::SmartCalcModel a;
    std::string input = "-log(10)";
    double result_real = -log10(10);
    a.Calculate(input);
    EXPECT_NEAR(a.GetResult(), result_real, 1e-6);
}

TEST(CalcTest, SmartCalc34) {
    s21::SmartCalcModel a;
    std::string input = "2^0.5 - 2^20";
    double result_real = pow(2, 0.5) - pow(2, 20);
    bool status = a.Calculate(input);
    EXPECT_NEAR(a.GetResult(), result_real, 1e-6);
    EXPECT_EQ(status, true);
}

TEST(CalcTest, SmartCalc35) {
    s21::SmartCalcModel a;
    std::string input =
            "sin(500) + cos(-200) - tan(15) - atan(0.33) + acos(-1) * asin(1) + "
            "ln(sqrt(144))";
    double result_real = sin(500) + cos(-200) - tan(15) - atan(0.33) +
                         acos(-1) * asin(1) + log(sqrt(144));
    bool status = a.Calculate(input);
    EXPECT_NEAR(a.GetResult(), result_real, 1e-6);
    EXPECT_EQ(status, true);
}

TEST(CalcTest, SmartCalc36) {
    s21::SmartCalcModel a;
    std::string input = "log(-10)";
    bool status = a.Calculate(input);
    EXPECT_TRUE(std::isnan(a.GetResult()));
    EXPECT_EQ(status, true);
}

TEST(CalcTest, SmartCalc37) {
    s21::SmartCalcModel a;
    std::string input = "asin(1)";
    double result_real = asin(1);
    bool status = a.Calculate(input);
    EXPECT_NEAR(a.GetResult(), result_real, 1e-6);
    EXPECT_EQ(status, true);
}

TEST(CalcTest, SmartCalc38) {
    s21::SmartCalcModel a;
    std::string input = "1 # 3";
    bool status = a.Calculate(input);
    EXPECT_EQ(a.GetResult(), 0);
    EXPECT_EQ(status, false);
}

TEST(CalcTest, SmartCalc39) {
    s21::SmartCalcModel a;
    std::string input = "!";
    bool status = a.Calculate(input);
    EXPECT_EQ(a.GetResult(), 0);
    EXPECT_EQ(status, false);
}

TEST(CalcTest, SmartCalc40) {
    s21::SmartCalcModel a;
    std::string input = ".";
    bool status = a.Calculate(input);
    EXPECT_EQ(a.GetResult(), 0);
    EXPECT_EQ(status, false);
}

TEST(CalcTest, SmartCalc41) {
    s21::SmartCalcModel a;
    std::string input = " ";
    bool status = a.Calculate(input);
    EXPECT_EQ(a.GetResult(), 0);
    EXPECT_EQ(status, false);
}

TEST(CalcTest, SmartCalc42) {
    s21::SmartCalcModel a;
    std::string input = "9.9919";
    bool status = a.Calculate(input);
    EXPECT_NEAR(a.GetResult(), 9.9919, 1e-6);
    EXPECT_EQ(status, true);
}

TEST(CalcTest, SmartCalc43) {
    s21::SmartCalcModel a;
    std::string input = "1/3";
    bool status = a.Calculate(input);
    EXPECT_NEAR(a.GetResult(), 1 / 3.0, 1e-6);
    EXPECT_EQ(status, true);
}

TEST(CalcTest, SmartCalc44) {
    s21::SmartCalcModel a;
    std::string input = "3.14 + 2.71";
    double result_real = 3.14 + 2.71;
    a.Calculate(input);
    EXPECT_NEAR(a.GetResult(), result_real, 1e-6);
}

TEST(CalcTest, SmartCalc45) {
    s21::SmartCalcModel a;
    std::string input = "3 4 + 5 *";
    EXPECT_TRUE(a.ReversedPolishNotation(input));
}

TEST(CalcTest, SmartCalc46) {
    s21::SmartCalcModel a;
    std::string input = " ";
    EXPECT_FALSE(a.ReversedPolishNotation(input));
}

TEST(CalcTest, SmartCalc47) {
    s21::SmartCalcModel a;
    std::string input = " ";
    EXPECT_FALSE(a.ReversedPolishNotation(input));
}

TEST(CalcTest, SmartCalc48) {
    s21::SmartCalcModel a;
    std::string input = " ";
    EXPECT_FALSE(a.ReversedPolishNotation(input));
}

TEST(CalcTest, SmartCalc49) {
    s21::SmartCalcModel a;
    std::string input = "5";
    EXPECT_TRUE(a.ReversedPolishNotation(input));
}

TEST(CalcTest, SmartCalc50) {
    s21::SmartCalcModel a;
    std::string input = "+";
    EXPECT_TRUE(a.ReversedPolishNotation(input));
}

TEST(CalcTest, SmartCalc51) {
    s21::SmartCalcModel a;
    std::string input = "log(100)";
    double result_real = log10(100);
    bool status = a.Calculate(input);
    EXPECT_NEAR(a.GetResult(), result_real, 1e-6);
    EXPECT_EQ(status, true);
}

TEST(CalcTest, SmartCalc52) {
    s21::SmartCalcModel a;
    std::string input = "tan(0.5)";
    double result_real = tan(0.5);
    bool status = a.Calculate(input);
    EXPECT_NEAR(a.GetResult(), result_real, 1e-6);
    EXPECT_EQ(status, true);
}

TEST(CalcTest, SMC) {
    s21::SmartCalcModel a;
    std::string input = "1.1111111 + 1.1111111";
    double result_real = 2.2222222;
    bool status = a.Calculate(input);
    EXPECT_NEAR(a.GetResult(), result_real, 1e-6);
    EXPECT_EQ(status, true);
}

