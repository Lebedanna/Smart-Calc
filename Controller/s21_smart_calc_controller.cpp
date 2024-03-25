#include "s21_smart_calc_controller.h"

namespace s21 {

    bool s21::SmartCalcController::Calculate(std::string &input) {
        try {
            return calc_model->Calculate(input);
        } catch (const std::exception &e) {
            throw std::runtime_error(e.what());
        }
    }
}  // namespace s21