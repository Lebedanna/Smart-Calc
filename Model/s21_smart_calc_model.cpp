#include "s21_smart_calc_model.h"

namespace s21 {
    //  check stack and get result
    long double SmartCalcModel::GetResult() const noexcept {
        try {
            if (!result_.empty()) {
                return std::stold(result_.top());
            } else {
                return 0;
            }
        } catch (const std::exception& e) {
            return 0;
        }
    }

    //  check if string (for example, "bebra") is a function
    bool SmartCalcModel::IsFunction(std::string str) noexcept {
        static const std::unordered_set<std::string> functions = {
                "sin", "cos", "tan", "asin", "acos", "atan", "sqrt", "log", "ln"};
        return functions.count(str) > 0;
    }

    //  check if symbol is delimeter
    bool SmartCalcModel::IsDelimeter(char c) noexcept {
        static const std::unordered_set<char> delimeters = {
                ' ', '+', '-', '/', '*', '%', '^', '=', '(', ')', '\r', 9, 0};
        return delimeters.count(c) > 0;
    }

    //  rpn logic
    bool SmartCalcModel::ReversedPolishNotation(std::string& input) {
        if (input.empty()) {
            return false;
        }
        size_t i = 0;
        while (i < input.size()) {
            std::string token = "";
            std::string tmp = input.substr(i);
            GetToken(token, tmp, i);
            if (token.empty() || !InsertTokenToStack(token)) {
                return false;
            }
        }
        std::string delim;
        while (!operators_stack_.empty()) {
            if (!values_stack_.empty()) {
                delim = operators_stack_.top();
                values_stack_.push(delim);
            }
            operators_stack_.pop();
        }
        return true;
    }

    //  priority for rpn
    int SmartCalcModel::GetOperatorPriority(std::string op) {
        if (op == "(")
            return 3;
        else if (op == "^")
            return 2;
        else if (IsFunction(op))
            return 2;
        else if (op == "*" || op == "/" || op == "%")
            return 1;
        else if (op == "+" || op == "-")
            return 0;
        else
            return -1;
    }

    //  gets token from input
    std::string SmartCalcModel::GetToken(std::string& token, std::string& prog,
                                    size_t& i) {
        if (!token.empty()) {
            token.clear();
        }
        if (prog.empty()) {
            return token;
        }
        while (!prog.empty() && std::isspace(prog[0])) {
            prog.erase(0, 1);
            ++i;
        }
        if (!prog.empty() && std::isalpha(prog[0])) {
            while (!prog.empty() && std::isalpha(prog[0])) {
                token += prog[0];
                prog.erase(0, 1);
                ++i;
            }
        } else if (!prog.empty() && !std::isdigit(prog[0]) &&
                   prog.find_first_of("+-*/%^()") != std::string::npos) {
            token += prog[0];
            prog.erase(0, 1);
            ++i;
        } else if (!prog.empty() && std::isdigit(prog[0])) {
            while (prog[0] &&
                   (!std::ispunct(prog[0]) || prog[0] == '.' || prog[0] == ',') &&
                   !std::isspace(prog[0])) {
                token += prog[0];
                prog.erase(0, 1);
                ++i;
            }
        }
        return token;
    }

    //  puts token to stack
    bool SmartCalcModel::InsertTokenToStack(std::string token) {
        if (IsDelimeter(token[0]) || IsFunction(token)) {
            if (operators_stack_.empty()) {
                operators_stack_.push(token);
            } else {
                if (token == ")") {
                    if (values_stack_.empty() || operators_stack_.empty()) {
                        return false;
                    }
                    while (!operators_stack_.empty() && operators_stack_.top() != "(") {
                        values_stack_.push(operators_stack_.top());
                        operators_stack_.pop();
                    }
                    if (!operators_stack_.empty()) {
                        operators_stack_.pop();
                    }
                } else {
                    if (!operators_stack_.empty() &&
                        (GetOperatorPriority(operators_stack_.top()) == -1 ||
                         GetOperatorPriority(token) == -1)) {
                        return false;
                    }
                    while (!operators_stack_.empty() && operators_stack_.top() != "(" &&
                           GetOperatorPriority(operators_stack_.top()) >=
                           GetOperatorPriority(token)) {
                        values_stack_.push(operators_stack_.top());
                        operators_stack_.pop();
                    }
                    operators_stack_.push(token);
                }
            }
        } else {
            values_stack_.push(token);
        }

        return true;
    }

    bool SmartCalcModel::Calculate(std::string& input) {
        if (input.empty()) {
            std::cerr << "Empty input" << std::endl;
            return false;
        }

        if (std::count(input.begin(), input.end(), '(') !=
            std::count(input.begin(), input.end(), ')')) {
            std::cerr << "Mismatched parentheses" << std::endl;
            return false;
        }

        std::string processedInput;
        if (!Unaries(input, processedInput)) {
            std::cerr << "Failed to process unary operators" << std::endl;
            return false;
        }

        if (!ReversedPolishNotation(processedInput)) {
            std::cerr << "Failed to convert to reversed polish notation" << std::endl;
            return false;
        }

        std::stack<std::string> reversed_stack_;
        while (!values_stack_.empty()) {
            reversed_stack_.push(values_stack_.top());
            values_stack_.pop();
        }
        values_stack_ = reversed_stack_;

        if (!CalculateResult()) {
            std::cerr << "Failed to calculate" << std::endl;
            return false;
        }

        return true;
    }


    //  ***  CALCULATIONS  ***

    //  calls right funcs and checks if result is decimal
    bool SmartCalcModel::CountFunction() {
        if (result_.empty()) {
            return false;
        }
        std::string token = values_stack_.top();
        values_stack_.pop();
        bool flag = true;
        if (token == "+") {
            flag = Sum();
        } else if (token == "/") {
            flag = Division();
        } else if (token == "*") {
            flag = Multiplication();
        } else if (token == "-") {
            flag = Difference();
        } else if (token == "%") {
            flag = Mod();
        } else if (token == "^") {
            flag = Pow();
        } else if (token == "sin") {
            flag = Sin();
        } else if (token == "cos") {
            flag = Cos();
        } else if (token == "tan") {
            flag = Tan();
        } else if (token == "atan") {
            flag = Atan();
        } else if (token == "acos") {
            flag = Acos();
        } else if (token == "asin") {
            flag = Asin();
        } else if (token == "sqrt") {
            flag = Sqrt();
        } else if (token == "ln") {
            flag = LnFunc();
        } else if (token == "log") {
            flag = LogFunc();
        }
        if (stold(result_.top()) != floor(stold(result_.top()))) {
            std::string resultString = result_.top();
            size_t i = resultString.length() - 1;
            while (i > 0 && (resultString[i] == '0' || resultString[i] == '.')) {
                if (resultString[i] == '.') {
                    i--;
                    break;
                }
                i--;
            }
            result_.top() = resultString.substr(0, i + 1);
        }
        return flag;
    }

    //  final calculations in stack
    bool SmartCalcModel::CalculateResult() {
        bool flag = true;
        while (values_stack_.size() > 0) {
            if (CountChars(values_stack_.top(), ',') > 1 ||
                CountChars(values_stack_.top(), '.') > 1) {
                flag = false;
                break;
            } else if (IsDelimeter(values_stack_.top()[0]) ||
                       IsFunction(values_stack_.top())) {
                flag = CountFunction();

                if (!flag) break;
            } else {
                result_.push(values_stack_.top());
                values_stack_.pop();
            }
        }
        return flag;
    }


    bool SmartCalcModel::Sum() {
        if (result_.size() < 2) {
            return false;
        }
        long double operand1 = stold(result_.top());
        result_.pop();
        long double operand2 = stold(result_.top());
        result_.pop();
        long double result = operand1 + operand2;
        result_.push(std::to_string(result));
        return true;
    }


    bool SmartCalcModel::Difference() {
        if (result_.size() < 2) {
            return false;
        }
        long double operand2 = stold(result_.top());
        result_.pop();
        long double operand1 = stold(result_.top());
        result_.pop();
        long double result = operand1 - operand2;
        result_.push(std::to_string(result));
        return true;
    }


    bool SmartCalcModel::Division() {
        if (result_.size() < 2) {
            return false;
        }
        long double operand2 = stold(result_.top());
        result_.pop();
        long double operand1 = stold(result_.top());
        result_.pop();
        long double result = operand1 / operand2;
        result_.push(std::to_string(result));
        return true;
    }


    bool SmartCalcModel::Multiplication() {
        if (result_.size() < 2) {
            return false;
        }
        long double operand1 = stold(result_.top());
        result_.pop();
        long double operand2 = stold(result_.top());
        result_.pop();
        long double result = operand1 * operand2;
        result_.push(std::to_string(result));
        return true;
    }


    bool SmartCalcModel::Mod() {
        if (result_.size() < 2) {
            return false;
        }
        long double operand2 = stold(result_.top());
        result_.pop();
        long double operand1 = stold(result_.top());
        result_.pop();
        long double result = fmod(operand1, operand2);
        result_.push(std::to_string(result));
        return true;
    }


    bool SmartCalcModel::Pow() {
        if (result_.size() < 2) {
            return false;
        }
        long double exponent = stold(result_.top());
        result_.pop();
        long double base = stold(result_.top());
        result_.pop();
        long double result = pow(base, exponent);
        result_.push(std::to_string(result));
        return true;
    }


    bool SmartCalcModel::Sin() {
        if (result_.empty()) {
            return false;
        }
        long double angle = stold(result_.top());
        result_.pop();
        long double result = sin(angle);
        result_.push(std::to_string(result));
        return true;
    }


    bool SmartCalcModel::Cos() {
        if (result_.empty()) {
            return false;
        }
        long double angle = stold(result_.top());
        result_.pop();
        long double result = cos(angle);
        result_.push(std::to_string(result));
        return true;
    }


    bool SmartCalcModel::Tan() {
        if (result_.empty()) {
            return false;
        }
        long double angle = stold(result_.top());
        result_.pop();
        long double result = tan(angle);
        result_.push(std::to_string(result));
        return true;
    }


    bool SmartCalcModel::Asin() {
        if (result_.empty()) {
            return false;
        }
        long double value = stold(result_.top());
        result_.pop();
        long double result = asin(value);
        result_.push(std::to_string(result));
        return true;
    }


    bool SmartCalcModel::Acos() {
        if (result_.empty()) {
            return false;
        }
        long double value = stold(result_.top());
        result_.pop();
        long double result = acos(value);
        result_.push(std::to_string(result));
        return true;
    }


    bool SmartCalcModel::Atan() {
        if (result_.empty()) {
            return false;
        }
        long double value = stold(result_.top());
        result_.pop();
        long double result = atan(value);
        result_.push(std::to_string(result));
        return true;
    }


    bool SmartCalcModel::Sqrt() {
        if (result_.empty()) {
            return false;
        }
        long double value = stold(result_.top());
        result_.pop();
        long double result = sqrt(value);
        result_.push(std::to_string(result));
        return true;
    }


    bool SmartCalcModel::LogFunc() {
        if (result_.empty()) {
            return false;
        }
        long double value = stold(result_.top());
        result_.pop();
        long double result = log10(value);
        result_.push(std::to_string(result));
        return true;
    }


    bool SmartCalcModel::LnFunc() {
        if (result_.empty()) {
            return false;
        }
        long double value = stold(result_.top());
        result_.pop();
        long double result = log(value);
        result_.push(std::to_string(result));
        return true;
    }


    //  checks how many times character is in string
    int SmartCalcModel::CountChars(const std::string& str, char c) {
        return std::count(str.begin(), str.end(), c);
    }


    //  checks for correct unary operators
    bool SmartCalcModel::Unaries(std::string& input, std::string& dest) {
        std::string token, prev_token, copy;
        size_t i = 0, prev_i, input_size = input.size();
        while (i < input_size) {
            prev_i = i;
            std::string tmp = input.substr(i);
            GetToken(token, tmp, i);
            if (prev_i == i) break;

            if (token.empty()) {
                return false;
            }

            if ((prev_token.empty() || (IsDelimeter(prev_token[0]))) &&
                (token == "+" || token == "-")) {
                if ((prev_token == "+" && token == "+") ||
                    (prev_token == "+" && token == "-") ||
                    (prev_token == "-" && token == "+") ||
                    (prev_token == "-" && token == "-")) {
                    return false;
                } else {
                    std::string temp_token = token;
                    tmp = input.substr(i);
                    GetToken(token, tmp, i);
                    if (IsFunction(token)) {
                        copy += '+';
                    }
                    copy += '(';
                    copy += '0';
                    copy += temp_token[0];
                    if (IsFunction(token)) {
                        copy += '1';
                        copy += ')';
                        copy += '*';
                        copy += token;
                    } else {
                        copy += token;
                        copy += ')';
                    }
                }
            } else {
                copy += token;
            }
            prev_token = token;
        }
        dest = copy;
        return true;
    }
}  // namespace s21