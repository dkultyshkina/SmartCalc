/*!
\file
\brief Исходный файл calculation.cc с методами класса Calculation,которые
используются при реализации подсчёта результата выражения с использованием
стеков после польской нотации

Данный файл содержит в себе описание методов класса Calculation, которые
используются при реализации подсчёта результата выражения с использованием стека
после польской нотации
*/
#include "calculation.h"

namespace Calc {

/*!
Конструктор по умолчанию
*/
Calculation::Calculation()
    : x_(0), stack_value_(), stack_priority_(), stack_type_(), error_(false){};
;

/*!
Параметризованный конструктор
\param[in] value переменная, которая содержит в себе стек значений
\param[in] priority переменная, которая содержит в себе стек приоритетов
\param[in] type переменная, которая содержит в себе стек типов
\param[in] x переменная, которая содержит в себе значение для переменной x
*/
Calculation::Calculation(std::stack<double> value, std::stack<int> priority,
                         std::stack<int> type, double x)
    : x_(x),
      stack_value_(value),
      stack_priority_(priority),
      stack_type_(type),
      error_(false){};

/*!
Деструктор
*/
Calculation::~Calculation() = default;

/*!
Возвращает значение приватного поля вычисляемого значения
\return переменная, которая содержит в себе вычисляемое значение
*/
double Calculation::GetValue() const noexcept { return value_; }

/*!
Возвращает значение приватного поля ошибки
\return значение ошибки true или false
*/
bool Calculation::GetError() const noexcept { return error_; }

/*!
Метод вычисления результата выражения
*/
void Calculation::CalculationValue() {
  if (stack_value_.empty()) {
    return;
  }
  size_t size = stack_priority_.size();
  double value = 0.0;
  int type = 0;
  for (size_t i = 0; i < size; ++i) {
    value = stack_value_.top();
    type = stack_type_.top();
    if (type != number && type != X) {
      PerformOperations(&type);
      if (error_ == true) {
        return;
      }
    } else {
      ReplaceX(&value, &type);
    }
    stack_value_.pop();
    stack_priority_.pop();
    stack_type_.pop();
  }
  value_ = result_stack_value_.top();
  result_stack_value_.pop();
  result_stack_priority_.pop();
  result_stack_type_.pop();
}

/*!
Метод для вычисления результата для сложных операций (sin, cos, tan и т.д.)
\param[out] first переменная для вычисления
\param[out] final переменная для получаемого значения в результате операции
\param[out] type переменная, которая содержит тип операции
*/
void Calculation::DifficultOperations(double* first, double* final, int* type) {
  if (*type == cosine) {
    *final = cos(*first);
    if (*final <= 1 && *final >= -1) {
      PushStack(final);
    } else {
      error_ = true;
    }
  }
  if (*type == sine) {
    *final = sin(*first);
    if (*final <= 1 && *final >= -1) {
      PushStack(final);
    } else {
      error_ = true;
    }
  }
  if (*type == tangent) {
    if (fmod(*first, pi_ + pi_ / 2) != 0 || *first == 0) {
      *final = tan(*first);
      PushStack(final);
    } else {
      error_ = true;
    }
  }
  if (*type == arccosine) {
    if (*first >= -1 && *first <= 1) {
      *final = acos(*first);
      PushStack(final);
    } else {
      error_ = true;
    }
  }
  if (*type == arcsine) {
    if (*first >= -1 && *first <= 1) {
      *final = asin(*first);
      PushStack(final);
    } else {
      error_ = true;
    }
  }
  if (*type == arctangent) {
    *final = atan(*first);
    if ((*final > (-pi_ / 2) && *final < (pi_ / 2)) || *first == 0) {
      PushStack(final);
    } else {
      error_ = true;
    }
  }
  if (*type == squareroot) {
    if (*first >= 0) {
      *final = sqrt(*first);
      PushStack(final);
    } else {
      error_ = true;
    }
  }
  if (*type == naturallogarithm) {
    if (*first >= 0) {
      *final = log(*first);
      PushStack(final);
    } else {
      error_ = true;
    }
  }
  if (*type == commonlogarithm) {
    if (*first >= 0) {
      *final = log10(*first);
      PushStack(final);
    } else {
      error_ = true;
    }
  }
}

/*!
Метод заменения x на необходимое значение
\param[out] value значение текущего элемента
\param[out] type тип текущего элемента
*/
void Calculation::ReplaceX(double* value, int* type) {
  if (*type == X) {
    *value = x_;
    *type = 1;
  }
  result_stack_value_.push(*value);
  result_stack_type_.push(*type);
  result_stack_priority_.push(0);
}

/*!
Метод помещения элемента в стеки значений, приоритетов, типов
\param[out] final значение текущего элемента
*/
void Calculation::PushStack(double* final) {
  result_stack_value_.push(*final);
  result_stack_priority_.push(0);
  result_stack_type_.push(number);
}

/*!
Метод для вычисления результата для простых операций (+, -, / и т.д.)
\param[out] first первая переменная для вычисления
\param[out] second вторая переменная для вычисления
\param[out] final переменная для получаемого значения в результате операции
\param[out] type переменная, которая содержит тип операции
\return результат ошибки, если она возникла в ходе вычисления
*/
bool Calculation::SimpleOperations(double* first, double* second, double* final,
                                   int* type) {
  if (*type != addition && *type != subtraction && *type != multiplication &&
      *type != division && *type != power && *type != modulus) {
    return false;
  }
  *second = result_stack_value_.top();
  result_stack_value_.pop();
  result_stack_priority_.pop();
  result_stack_type_.pop();
  if (*type == addition) {
    *final = *first + *second;
    PushStack(final);
  }
  if (*type == subtraction) {
    *final = *second - *first;
    PushStack(final);
  }
  if (*type == multiplication) {
    *final = (*first) * (*second);
    PushStack(final);
  }
  if (*type == division) {
    if (*first != 0) {
      *final = *second / *first;
      PushStack(final);
    } else {
      error_ = true;
    }
  }
  if (*type == power) {
    *final = pow(*second, *first);
    PushStack(final);
  }
  if (*type == modulus) {
    if (*first != 0) {
      *final = fmod(*second, *first);
      PushStack(final);
    } else {
      error_ = true;
    }
  }
  return true;
}

/*!
Вспомогательный метод для вычисления результата при операциях
\param[out] type переменная, которая содержит тип операции
*/
void Calculation::PerformOperations(int* type) {
  double first = 0.0, second = 0.0, final = 0.0;
  first = result_stack_value_.top();
  result_stack_value_.pop();
  result_stack_priority_.pop();
  result_stack_type_.pop();
  bool result = SimpleOperations(&first, &second, &final, type);
  if (error_ || result) {
    return;
  }
  DifficultOperations(&first, &final, type);
}
}  // namespace Calc
