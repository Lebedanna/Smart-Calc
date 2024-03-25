#pragma once

#include <algorithm>
#include <array>
#include <clocale>
#include <cmath>
#include <iostream>
#include <memory>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <unordered_set>
#include <vector>
#include <iomanip>

namespace s21 {
    class SmartCalcModel {
    public:
        SmartCalcModel()= default;
        virtual ~SmartCalcModel()= default;
        bool ReversedPolishNotation(std::string& input);
        bool Calculate(std::string& input);
        [[nodiscard]] long double GetResult() const noexcept;

    private:
        std::stack<std::string> operators_stack_{};
        std::stack<std::string> values_stack_{};
        std::stack<std::string> result_{};
        bool IsFunction(std::string str) noexcept;
        bool IsDelimeter(char c) noexcept;
        int GetOperatorPriority(std::string);
        std::string GetToken(std::string& token, std::string& prog, size_t& i);
        bool InsertTokenToStack(std::string token);
        bool Sum();
        bool Multiplication();
        bool Division();
        bool Difference();
        bool Mod();
        bool Pow();
        bool Sin();
        bool Cos();
        bool Tan();
        bool Atan();
        bool Asin();
        bool Acos();
        bool Sqrt();
        bool LnFunc();
        bool LogFunc();
        bool CountFunction();
        int CountChars(const std::string& str, char c);
        bool CalculateResult();
        bool Unaries(std::string& input, std::string& dest);
    };

}  // namespace s21