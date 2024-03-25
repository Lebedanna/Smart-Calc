#pragma once

#include <array>
#include <iostream>
#include <stdexcept>

#include "../Model/s21_smart_calc_model.h"

namespace s21 {
    class SmartCalcController {
    public:
        SmartCalcController() { calc_model = new s21::SmartCalcModel; };
        bool Calculate(std::string &a);
        std::string GetResult() const noexcept {
            return std::to_string(calc_model->GetResult());
        }

    private:
        s21::SmartCalcModel *calc_model;
    };
}  // namespace s21