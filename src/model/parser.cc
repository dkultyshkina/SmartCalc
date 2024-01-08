/*!
\file
\brief Исходный файл parser.cc с реализацией парсера строки в стек

Данный файл содержит в себе описание класса Parser и его методов для реализации
парсера строки в стек значения, типа и приоритета
*/

#include "parser.h"

namespace Calc {

Parser::Parser() : str_(" "), length_(0){};

/*!
Параметризованный конструктор
\param[in] str переменная, которая содержит строку с выражением
*/
Parser::Parser(std::string str) : str_(str), length_(str.length()){};

/*!
Деструктор
*/
Parser::~Parser() = default;

/*!
Возвращает стек результата значения приватного поля
\return стек результата значения
*/
std::stack<double> Parser::GetStackValue() const noexcept {
  return stack_value_;
}

/*!
Возвращает стек результата приоритета приватного поля
\return стек результата приоритета
*/
std::stack<int> Parser::GetStackPriority() const noexcept {
  return stack_priority_;
}

/*!
Возвращает стек результата типа приватного поля
\return стек результата типа
*/
std::stack<int> Parser::GetStackType() const noexcept { return stack_type_; }

/*!
Метод для парсера строки
*/
void Parser::ParserStrToStack() {
  for (size_t i = 0; i < length_; ++i) {
    CheckAndPushDoubleNumber(&i);
    CheckAndPushOperator(&i);
    CheckAndPushDifficultOperator(&i);
    CheckAndPushX(&i);
  }
  ReverseStacks();
}

/*!
Метод для проверки элемента на число
\param[out] i индекс строки выражения
\return текущий элемент число или нет
*/
bool Parser::IsDigit(size_t *i) const {
  if (str_[*i] >= '0' && str_[*i] <= '9') {
    return true;
  }
  return false;
}

/*!
Проверка и помещение вещественного числа в стек
\param[out] i индекс строки выражения
*/
void Parser::CheckAndPushDoubleNumber(size_t *i) {
  if (IsDigit(i)) {
    std::string double_number;
    std::string double_E;
    while (IsDigit(i) || str_[*i] == '.') {
      double_number.push_back(str_[*i]);
      *i = *i + 1;
    }
    if (str_[*i] == 'e' || str_[*i] == 'E') {
      *i = *i + 1;
      char operator_E = ' ';
      if (str_[*i] == '+' || str_[*i] == '-') {
        operator_E = str_[*i];
        *i = *i + 1;
      }
      while (IsDigit(i) || str_[*i] == '.') {
        double_E.push_back(str_[*i]);
        *i = *i + 1;
      }
      double E = stod(double_E);
      if (operator_E == '-') {
        E *= -1;
      }
      stack_value_.push(atof(double_number.c_str()) * pow(10, E));
      stack_priority_.push(0);
      stack_type_.push(1);
      return;
    }
    stack_value_.push(atof(double_number.c_str()));
    stack_priority_.push(0);
    stack_type_.push(1);
  }
}

/*!
Проверка и помещение х в стек
\param[out] i индекс строки выражения
*/
void Parser::CheckAndPushX(size_t *i) {
  if (str_[*i] == 'x' || str_[*i] == 'X') {
    stack_value_.push(0);
    stack_priority_.push(0);
    stack_type_.push(X);
  }
}

/*!
Проверка и помещение операции в стек
\param[out] i индекс строки выражения
*/
void Parser::CheckAndPushOperator(size_t *i) {
  if (str_[*i] == '+') {
    stack_value_.push(0);
    stack_priority_.push(1);
    stack_type_.push(addition);
    return;
  }
  if (str_[*i] == '-') {
    stack_value_.push(0);
    stack_priority_.push(1);
    stack_type_.push(subtraction);
    return;
  }
  if (str_[*i] == '/') {
    stack_value_.push(0);
    stack_priority_.push(2);
    stack_type_.push(division);
    return;
  }
  if (str_[*i] == '*') {
    stack_value_.push(0);
    stack_priority_.push(2);
    stack_type_.push(multiplication);
    return;
  }
  if (str_[*i] == '^') {
    stack_value_.push(0);
    stack_priority_.push(3);
    stack_type_.push(power);
    return;
  }
  if (str_[*i] == '(') {
    stack_value_.push(0);
    stack_priority_.push(5);
    stack_type_.push(brackets_left);
    return;
  }
  if (str_[*i] == ')') {
    stack_value_.push(0);
    stack_priority_.push(5);
    stack_type_.push(brackets_right);
  }
}

/*!
Проверка границ
\param[out] i индекс строки выражения
*/
bool Parser::CheckBorders(size_t *i) const {
  if (length_ > 4 && *i != length_ && *i != length_ - 1 && *i != length_ - 2 &&
      *i != length_ - 3 && *i != length_ - 4) {
    return true;
  }
  return false;
}

/*!
Проверка и помещение сложных операции в стек
\param[out] i индекс строки выражения
*/
void Parser::CheckAndPushDifficultOperator(size_t *i) {
  std::string diff_operator;
  if (CheckBorders(i) || str_[*i] == 'm') {
    diff_operator.push_back(str_[*i]);
    diff_operator.push_back(str_[*i + 1]);
    diff_operator.push_back(str_[*i + 2]);
    diff_operator.push_back(str_[*i + 3]);
  } else {
    return;
  }
  PushDifficultOperator(diff_operator, i);
}

/*!
Помещение сложной операции в стек
\param[in] diff_operator переменная, которая хранит в себе строку со сложной
операцией \param[out] i индекс строки выражения
*/
void Parser::PushDifficultOperator(std::string &diff_operator, size_t *i) {
  if (diff_operator == "sqrt") {
    stack_value_.push(0);
    stack_priority_.push(4);
    stack_type_.push(squareroot);
    *i += 3;
    return;
  }
  if (diff_operator == "asin") {
    stack_value_.push(0);
    stack_priority_.push(4);
    stack_type_.push(arcsine);
    *i += 3;
    return;
  }
  if (diff_operator == "acos") {
    stack_value_.push(0);
    stack_priority_.push(4);
    stack_type_.push(arccosine);
    *i += 3;
    return;
  }
  if (diff_operator == "atan") {
    stack_value_.push(0);
    stack_priority_.push(4);
    stack_type_.push(arctangent);
    *i += 3;
    return;
  }
  diff_operator.pop_back();
  if (diff_operator == "cos") {
    stack_value_.push(0);
    stack_priority_.push(4);
    stack_type_.push(cosine);
    *i += 2;
    return;
  }
  if (diff_operator == "sin") {
    stack_value_.push(0);
    stack_priority_.push(4);
    stack_type_.push(sine);
    *i += 2;
    return;
  }
  if (diff_operator == "tan") {
    stack_value_.push(0);
    stack_priority_.push(4);
    stack_type_.push(tangent);
    *i += 2;
    return;
  }
  if (diff_operator == "log") {
    stack_value_.push(0);
    stack_priority_.push(4);
    stack_type_.push(commonlogarithm);
    *i += 2;
    return;
  }
  if (diff_operator == "mod") {
    stack_value_.push(0);
    stack_priority_.push(4);
    stack_type_.push(modulus);
    *i += 2;
    return;
  }
  diff_operator.pop_back();
  if (diff_operator == "ln") {
    stack_value_.push(0);
    stack_priority_.push(4);
    stack_type_.push(naturallogarithm);
    *i += 1;
    return;
  }
}

/*!
Метод для переворота стеков
*/
void Parser::ReverseStacks() {
  size_t size = stack_value_.size();
  std::stack<double> new_stack_value;
  std::stack<int> new_stack_priority;
  std::stack<int> new_stack_type;
  double value = 0.0;
  int priority = 0;
  int type = 0;
  for (size_t i = 0; i < size; ++i) {
    value = stack_value_.top();
    priority = stack_priority_.top();
    type = stack_type_.top();
    stack_value_.pop();
    stack_priority_.pop();
    stack_type_.pop();
    new_stack_value.push(value);
    new_stack_priority.push(priority);
    new_stack_type.push(type);
  }
  stack_value_ = new_stack_value;
  stack_priority_ = new_stack_priority;
  stack_type_ = new_stack_type;
}
};  // namespace Calc
