/*!
\file
\brief Исходный файл validator.h с реализацией проверки на корректность строки

Данный файл содержит в себе описания класса Validator и его методов для
реализации проверки на корректность строки
*/
#include "validator.h"

namespace Calc {

/*!
Конструктор по умолчанию
*/
Validator::Validator()
    : str_(" "),
      length_(0),
      count_number_(0),
      count_backet_(0),
      count_point_(0){};

/*!
Параметризованный конструктор
\param[in] str переменная, которая содержит строку с выражением
*/
Validator::Validator(std::string str)
    : str_(str),
      length_(str.length()),
      count_number_(0),
      count_backet_(0),
      count_point_(0){};

/*!
Деструктор
*/
Validator::~Validator() = default;

/*!
Возвращает значение строки приватного поля
\return значение строки приватного поля
*/
std::string Validator::GetStr() const noexcept { return str_; };

/*!
Метод для проверки на корректность строки
\return результат - корректность строки true или false
*/
bool Validator::ValidationOfInputStrings() {
  if (empty()) {
    return false;
  }
  bool result = true;
  for (size_t i = 0; i < length_; ++i) {
    result = CheckChar(&i);
    if (!result) {
      return false;
    }
  }
  if (!CheckBracket() || count_number_ > 1) {
    return false;
  }
  return true;
}

/*!
Метод для проверки элемента на число
\param[out] i индекс строки выражения
\return текущий элемент число или нет
*/
bool Validator::IsDigit(size_t *i) const {
  if (str_[*i] >= '0' && str_[*i] <= '9') {
    return true;
  }
  return false;
}

/*!
Метод для проверки элемента на точку
\param[out] i индекс строки выражения
\return текущий элемент точка или нет
*/
bool Validator::IsPoint(size_t *i) {
  if (str_[*i] == '.') {
    size_t j = *i - 1;
    size_t k = *i + 1;
    if (*i != 0 && IsDigit(&j) && IsDigit(&k)) {
      count_point_++;
      if (count_point_ == 1) {
        return true;
      } else {
        return false;
      }
    }
  }
  return false;
}

/*!
Метод для проверки элемента на простую операцию
\param[out] i индекс строки выражения
\return текущий элемент простая операция или нет
*/
bool Validator::IsOperator(size_t *i) const {
  if (str_[*i] == '*' || str_[*i] == '+' || str_[*i] == '-' ||
      str_[*i] == '^' || str_[*i] == '/') {
    return true;
  }
  return false;
}

/*!
Метод для проверки элемента на х
\param[out] i индекс строки выражения
\return текущий элемент х или нет
*/
bool Validator::IsX(size_t *i) const {
  if (str_[*i] == 'x' || str_[*i] == 'X') {
    return true;
  }
  return false;
}

/*!
Метод для проверки элемента на левую круглую скобку
\param[out] i индекс строки выражения
\return текущий элемент левую круглую скобку или нет
*/
bool Validator::IsBracketLeft(size_t *i) {
  if (str_[*i] == '(') {
    count_backet_++;
    count_number_ = 2;
    return true;
  }
  return false;
}

/*!
Метод для проверки элемента на правую круглую скобку
\param[out] i индекс строки выражения
\return текущий элемент правую круглую скобку или нет
*/
bool Validator::IsBracketRight(size_t *i) {
  if (str_[*i] == ')') {
    count_backet_--;
    return true;
  }
  return false;
}

/*!
Метод для проверки элемента на унарный минус
\param[out] i индекс строки выражения
\return текущий элемент унарный минус или нет
*/
bool Validator::CheckUnaryMinus(size_t *i) {
  if (str_[*i] == '-' || str_[*i] == '+') {
    if (*i + 1 < length_) {
      size_t k = *i + 1;
      size_t j = *i - 1;
      if (((*i == 0) || str_[j] == 'd' || str_[j] == '(') &&
          (IsDigit(&k) || IsX(&k) || (str_[k] == '('))) {
        str_.insert(*i, "0");
        length_ = str_.length();
        return true;
      }
    }
  }
  return false;
}

/*!
Проверка границ
\param[out] i индекс строки выражения
*/
bool Validator::CheckBorders(size_t *i) const {
  if (length_ > 4 && *i != length_ && *i != length_ - 1 && *i != length_ - 2 &&
      *i != length_ - 3) {
    return true;
  }
  return false;
}

/*!
Проверка на соответствие количества скобок
*/
bool Validator::CheckBracket() const {
  if (count_backet_ == 0) {
    return true;
  }
  return false;
}

/*!
Метод для проверки элемента на mod
\param[out] i индекс строки выражения
\return текущий элемент mod или нет
*/
bool Validator::IsMod(size_t *i) {
  std::string diff_operator;
  if (CheckBorders(i)) {
    diff_operator.push_back(str_[*i]);
    diff_operator.push_back(str_[*i + 1]);
    diff_operator.push_back(str_[*i + 2]);
  }
  if (diff_operator == "mod") {
    size_t j = *i - 1;
    *i += 2;
    size_t k = *i + 1;
    if ((IsDigit(&j) || str_[j] == ')' || IsX(&j)) &&
        (IsDigit(&k) || str_[k] == '(' || IsX(&k))) {
      return true;
    }
  }
  return false;
}

/*!
Метод для проверки элемента на сложную операцию
\param[out] i индекс строки выражения
\return текущий элемент сложная операция или нет
*/
bool Validator::IsDifficultOperator(size_t *i) {
  std::string diff_operator;
  if (CheckBorders(i) && *i != length_ - 4) {
    diff_operator.push_back(str_[*i]);
    diff_operator.push_back(str_[*i + 1]);
    diff_operator.push_back(str_[*i + 2]);
    diff_operator.push_back(str_[*i + 3]);
    diff_operator.push_back(str_[*i + 4]);
  } else {
    return false;
  }
  if (diff_operator == "atan(" || diff_operator == "acos(" ||
      diff_operator == "sqrt(" || diff_operator == "asin(") {
    count_backet_++;
    size_t j = *i;
    *i += 4;
    if (length_ > 6 && CheckAroundDifficult(&j)) {
      return true;
    }
  }
  diff_operator.pop_back();
  if (diff_operator == "sin(" || diff_operator == "cos(" ||
      diff_operator == "log(" || diff_operator == "tan(") {
    size_t j = *i;
    count_backet_++;
    *i += 3;
    if (length_ > 5 && CheckAroundDifficult(&j)) {
      return true;
    }
  }
  diff_operator.pop_back();
  if (diff_operator == "ln(") {
    count_backet_++;
    size_t j = *i;
    *i += 2;
    if (length_ > 4 && CheckAroundDifficult(&j)) {
      return true;
    }
  }
  return false;
}

/*!
Метод для проверки окружения простой операции
\param[out] i индекс строки выражения
\return вокруг простой операции корректные элементы или нет
*/
bool Validator::CheckAround(size_t *i) const {
  bool right = false, left = false;
  if (*i + 1 < length_) {
    size_t j = *i + 1;
    if (IsDigit(&j) || str_[j] == '(' || IsX(&j) ||
        CheckDifficultOperatorRight(i)) {
      right = true;
    }
  }
  if (*i > 0) {
    size_t j = *i - 1;
    if (IsDigit(&j) || IsX(&j) || str_[j] == ')' ||
        (IsExhibotor(&j) && (str_[*i] == '+' || str_[*i] == '-'))) {
      left = true;
    }
  }
  if (left && right) {
    return true;
  }
  return false;
}

/*!
Метод для проверки окружения числа
\param[out] i индекс строки выражения
\return вокруг числа корректные значения или нет
*/
bool Validator::CheckAroundNumber(size_t *i) const {
  bool right = false, left = false;
  if (*i == length_ - 1) {
    right = true;
  } else {
    if (*i + 1 < length_) {
      size_t j = *i + 1;
      if (str_[j] == ')' || IsOperator(&j) || str_[j] == 'm' ||
          IsExhibotor(&j)) {
        right = true;
      }
      if (IsDigit(i) && (IsDigit(&j) || str_[j] == '.')) {
        right = true;
      }
    }
  }
  if (*i == 0) {
    left = true;
  } else {
    size_t j = *i - 1;
    if (str_[j] == '(' || IsOperator(&j) || str_[j] == 'd' || IsExhibotor(&j)) {
      left = true;
    }
    if (IsDigit(i) && (IsDigit(&j) || str_[j] == '.')) {
      left = true;
    }
  }
  if (left && right) {
    return true;
  }
  return false;
}

/*!
Метод для проверки окружения сложной операции
\param[out] i индекс строки выражения
\return вокруг сложной операции корректные элементы или нет
*/
bool Validator::CheckAroundDifficult(size_t *i) const {
  if (*i > 0) {
    size_t j = *i - 1;
    if (str_[j] == '(' || IsOperator(&j)) {
      return true;
    }
  } else {
    return true;
  }
  return false;
}

/*!
Проверка на соответствие количества чисел
*/
void Validator::CountNumber() {
  if (count_number_ == 2) {
    count_number_ = 1;
  }
}

/*!
Метод для проверки элемента строки
\param[out] i индекс строки выражения
\return результат - корректность true или false
*/
bool Validator::CheckChar(size_t *i) {
  if (IsExhibotor(i)) {
    return CheckExhibotor(i);
  }
  if (IsDigit(i)) {
    CountNumber();
    return CheckAroundNumber(i);
  }
  if (IsX(i)) {
    CountNumber();
    return CheckAroundNumber(i);
  }
  if (IsPoint(i)) {
    return true;
  }
  if (count_point_ > 1) {
    return false;
  } else {
    count_point_ = 0;
  }
  bool result = false;
  if (CheckUnaryMinus(i)) {
    return true;
  }
  if (IsOperator(i)) {
    result = CheckAround(i);
    return result;
  }
  if (IsMod(i)) {
    return true;
  }
  if (IsDifficultOperator(i)) {
    return true;
  }
  if (IsBracketRight(i)) {
    return true;
  }
  if (IsBracketLeft(i)) {
    return true;
  }
  return result;
}

/*!
Метод для проверки на пустоту строки
\return пустая строка или нет
*/
bool Validator::empty() const {
  if (str_ == "" && length_ == 0) {
    return true;
  }
  return false;
}

/*!
Вспомогательный метод для проверки с правой стороны сложной операции
\param[out] i индекс строки выражения
\return корректна или нет
*/
bool Validator::CheckDifficultOperatorRight(size_t *i) const {
  if ((*i + 1) < length_) {
    if (str_[*i + 1] == 'a' || str_[*i + 1] == 's' || str_[*i + 1] == 'l' ||
        str_[*i + 1] == 'c' || str_[*i + 1] == 't' || str_[*i + 1] == 'm') {
      return true;
    }
  }
  return false;
}

/*!
Проверка на экспоненту
\param[out] i индекс строки выражения
*/
bool Validator::IsExhibotor(size_t *i) const {
  if (str_[*i] == 'E' || str_[*i] == 'e') {
    return true;
  }
  return false;
}

/*!
Проверка границ экспоненты
\param[out] i индекс строки выражения
*/
bool Validator::CheckExhibotor(size_t *i) {
  if (*i != length_ - 1 && *i != 0) {
    size_t j = *i + 1;
    size_t k = *i - 1;
    if (IsDigit(&k) && (IsDigit(&j) || str_[j] == '+' || str_[j] == '-')) {
      return true;
    }
  }
  return false;
}
}  // namespace Calc