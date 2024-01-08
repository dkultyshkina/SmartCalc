/*!
\file
\brief Исходный файл notation.h с реализацией вычисления польской нотации

Данный файл содержит в себе определение класса Notation и его методов для
реализации вычисления польской нотации
*/

#include "notation.h"

namespace Calc {
/*
Конструтор по умолчанию
*/
Notation::Notation() : stack_value_(), stack_priority_(), stack_type_(){};
/*!
Параметризованный конструктор
\param[in] value переменная, которая содержит в себе стек значений
\param[in] priority переменная, которая содержит в себе стек приоритетов
\param[in] type переменная, которая содержит в себе стек типов
*/
Notation::Notation(std::stack<double> value, std::stack<int> priority,
                   std::stack<int> type)
    : stack_value_(value), stack_priority_(priority), stack_type_(type){};

/*!
Деструктор
*/
Notation::~Notation() = default;

/*!
Возвращает стек результата значения приватного поля
\return стек результата значения
*/
std::stack<double> Notation::GetStackValue() const noexcept {
  return result_stack_value_;
}

/*!
Возвращает стек результата приоритета приватного поля
\return стек результата приоритета
*/
std::stack<int> Notation::GetStackPriority() const noexcept {
  return result_stack_priority_;
}

/*!
Возвращает стек результата типа приватного поля
\return стек результата типа
*/
std::stack<int> Notation::GetStackType() const noexcept {
  return result_stack_type_;
}

/*!
Метод вычисления польской нотации
*/
void Notation::CalculationNotation() {
  size_t size = stack_value_.size();
  double value = 0.0;
  int priority = 0;
  int type = 0;
  for (size_t i = 0; i < size; ++i) {
    value = stack_value_.top();
    priority = stack_priority_.top();
    type = stack_type_.top();
    CheckTypeForNotation(value, priority, type);
    stack_value_.pop();
    stack_priority_.pop();
    stack_type_.pop();
  }
  RemainderInSupportStack();
  ReverseStacks();
}

/*!
Метод для работы со значениями, которые остались в стеке после выполнения
основной польской нотации
*/
void Notation::RemainderInSupportStack() {
  size_t size = support_stack_priority_.size();
  double value_support = 0.0;
  int priority_support = 0;
  int type_support = 0;
  for (size_t i = 0; i < size; ++i) {
    value_support = support_stack_value_.top();
    priority_support = support_stack_priority_.top();
    type_support = support_stack_type_.top();
    if (type_support != brackets_left && type_support != brackets_right) {
      result_stack_value_.push(value_support);
      result_stack_type_.push(type_support);
      result_stack_priority_.push(priority_support);
    }
    support_stack_value_.pop();
    support_stack_priority_.pop();
    support_stack_type_.pop();
  }
}

/*!
Метод для проверки типа элемента для вычисления польской нотации
\param[in] value переменная со значением текущего элемента
\param[in] priority переменная с приоритетом текущего элемента
\param[in] type переменная с типом текущего элемента
*/
void Notation::CheckTypeForNotation(double& value, int& priority, int& type) {
  if (type == number || type == X) {
    result_stack_value_.push(value);
    result_stack_type_.push(type);
    result_stack_priority_.push(priority);
  } else {
    if (support_stack_priority_.empty()) {
      support_stack_value_.push(value);
      support_stack_type_.push(type);
      support_stack_priority_.push(priority);
      return;
    }
    CheckPriorityForNotation(value, priority, type);
  }
}

/*!
Вспомогательный метод для вычисления польской нотации
\param[out] i значение итератора стека
\param[out] prioruty_support приоритет текущего элемента из вспомогательного
стека \param[out] value_support значение текущего элемента из вспомогательного
стека \param[out] type_support тип текущего элемента из вспомогательного стека
\param[in] type тип текущего элемента из основного стека
*/
void Notation::HelperForNotation(size_t* i, int* priority_support,
                                 double* value_support, int* type_support,
                                 int type) {
  *i = *i + 1;
  if (!support_stack_value_.empty()) {
    *value_support = support_stack_value_.top();
    *priority_support = support_stack_priority_.top();
    *type_support = support_stack_type_.top();
    if (*type_support == brackets_left && type == brackets_right) {
      support_stack_value_.pop();
      support_stack_type_.pop();
      support_stack_priority_.pop();
    }
  }
}

/*!
Вспомогательный метод для вычисления польской нотации в ситуации, когда
приоритет основного стека меньше или равен приоритету вспомогательного стека
\param[in] value значение текущего элемента из основного стека
\param[in] priority приоритет текущего элемента из основного стека
\param[in] type тип текущего элемента из основного стека
\param[in] value_support значение текущего элемента из вспомогательного стека
\param[in] priority_support приоритет текущего элемента из вспомогательного
стека \param[in] type_support тип текущего элемента из вспомогательного стека
*/
void Notation::PriorityLessOrEqualPrioritySupport(double& value, int& priority,
                                                  int& type,
                                                  double& value_support,
                                                  int& priority_support,
                                                  int& type_support) {
  size_t size = support_stack_priority_.size();
  size_t i = 0;
  while (priority <= priority_support && type_support != brackets_left &&
         i < size) {
    if (type_support != brackets_right && type_support != brackets_left) {
      result_stack_value_.push(value_support);
      result_stack_type_.push(type_support);
      result_stack_priority_.push(priority_support);
    }
    support_stack_value_.pop();
    support_stack_type_.pop();
    support_stack_priority_.pop();
    HelperForNotation(&i, &priority_support, &value_support, &type_support,
                      type);
  }
  if (type_support == brackets_left && type == brackets_right) {
    support_stack_value_.pop();
    support_stack_type_.pop();
    support_stack_priority_.pop();
  }
  if (type != brackets_left && type != brackets_right) {
    support_stack_value_.push(value);
    support_stack_type_.push(type);
    support_stack_priority_.push(priority);
  }
}

/*!
Вспомогательный метод для вычисления польской нотации в ситуации, когда
приоритет основного стека больше приоритету вспомогательного стека и тип не
равен правой скобки \param[in] type тип текущего элемента из основного стека
\param[in] value_support значение текущего элемента из вспомогательного стека
\param[in] priority_support приоритет текущего элемента из вспомогательного
стека \param[in] type_support тип текущего элемента из вспомогательного стека
*/
void Notation::TypeNotEqualBracketsRight(int& type, double& value_support,
                                         int& priority_support,
                                         int& type_support) {
  size_t size = support_stack_priority_.size();
  size_t i = 0;
  while (type_support != brackets_left && i < size) {
    if (type_support != brackets_right && type_support != brackets_left) {
      result_stack_value_.push(value_support);
      result_stack_type_.push(type_support);
      result_stack_priority_.push(priority_support);
      support_stack_value_.pop();
      support_stack_type_.pop();
      support_stack_priority_.pop();
    }
    HelperForNotation(&i, &priority_support, &value_support, &type_support,
                      type);
  }
}

/*!
Метод для проверки приоритета для нотации
\param[in] value значение текущего элемента из основного стека
\param[in] priority приоритет текущего элемента из основного стека
\param[in] type тип текущего элемента из основного стека
*/
void Notation::CheckPriorityForNotation(double& value, int& priority,
                                        int& type) {
  double value_support = support_stack_value_.top();
  int priority_support = support_stack_priority_.top();
  int type_support = support_stack_type_.top();
  if (priority <= priority_support && type != power) {
    PriorityLessOrEqualPrioritySupport(value, priority, type, value_support,
                                       priority_support, type_support);
  } else {
    if (type != brackets_right) {
      support_stack_value_.push(value);
      support_stack_type_.push(type);
      support_stack_priority_.push(priority);
    } else {
      TypeNotEqualBracketsRight(type, value_support, priority_support,
                                type_support);
    }
  }
}

/*!
Метод для переворота стеков
*/
void Notation::ReverseStacks() {
  size_t size = result_stack_value_.size();
  std::stack<double> new_stack_value;
  std::stack<int> new_stack_priority;
  std::stack<int> new_stack_type;
  double value = 0.0;
  int priority = 0;
  int type = 0;
  for (size_t i = 0; i < size; ++i) {
    value = result_stack_value_.top();
    priority = result_stack_priority_.top();
    type = result_stack_type_.top();
    result_stack_value_.pop();
    result_stack_priority_.pop();
    result_stack_type_.pop();
    new_stack_value.push(value);
    new_stack_priority.push(priority);
    new_stack_type.push(type);
  }
  result_stack_value_ = new_stack_value;
  result_stack_priority_ = new_stack_priority;
  result_stack_type_ = new_stack_type;
}
};  // namespace Calc