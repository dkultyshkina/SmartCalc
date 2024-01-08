#include <gtest/gtest.h>

#include <stack>

#include "../model/calculation.h"
#include "../model/model.h"
#include "../model/notation.h"
#include "../model/parser.h"
#include "../model/validator.h"
#include "../model/creditcalc.h"
#include "../model/depositcalc.h"

TEST(TestValidator, ValidatorFirst)
{
  Calc::Validator valid("1+5");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, true);
}

TEST(TestValidator, ValidatorSecond)
{
  Calc::Validator valid("1+-5");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, false);
}

TEST(TestValidator, ValidatorThird)
{
  Calc::Validator valid("(1+5");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, false);
}

TEST(TestValidator, ValidatorFourth)
{
  Calc::Validator valid("sin(");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, false);
}

TEST(TestValidator, ValidatorFifth)
{
  Calc::Validator valid("cos(");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, false);
}

TEST(TestValidator, ValidatorSixth)
{
  Calc::Validator valid("asin(");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, false);
}

TEST(TestValidator, ValidatorSeventh)
{
  Calc::Validator valid("log(");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, false);
}

TEST(TestValidator, ValidatorEighth)
{
  Calc::Validator valid("ln(");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, false);
}

TEST(TestValidator, ValidatorNinth)
{
  Calc::Validator valid("acos(");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, false);
}

TEST(TestValidator, ValidatorTenth)
{
  Calc::Validator valid("atan(");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, false);
}

TEST(TestValidator, ValidatorEleventh)
{
  Calc::Validator valid("sqrt(");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, false);
}

TEST(TestValidator, ValidatorTwelfth)
{
  Calc::Validator valid("2^");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, false);
}

TEST(TestValidator, ValidatorThirteenth)
{
  Calc::Validator valid("*4");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, false);
}

TEST(TestValidator, ValidatorFourteenth)
{
  Calc::Validator valid("/6");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, false);
}

TEST(TestValidator, ValidatorFifteenth)
{
  Calc::Validator valid("sin(x");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, false);
}

TEST(TestValidator, ValidatorNineteenth)
{
  Calc::Validator valid("sin(x)");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, true);
}

TEST(TestValidator, ValidatorSixteenth)
{
  Calc::Validator valid("(1+3)*x");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, true);
}

TEST(TestMapErase, EraseSeventeenth)
{
  Calc::Validator valid("2^2");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, true);
}

TEST(TestValidator, ValidatorEighteenth)
{
  Calc::Validator valid("(1/4)");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, true);
}

TEST(TestValidator, ValidatorTwentieth)
{
  Calc::Validator valid("-1+4");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, true);
}

TEST(TestValidator, ValidatorTwentyFirst)
{
  Calc::Validator valid("2.3445+10");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, true);
}

TEST(TestValidator, ValidatorTwentySecond)
{
  Calc::Validator valid("2.34.55+10");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, false);
}

TEST(TestValidator, ValidatorTwentyThird)
{
  Calc::Validator valid(" ");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, false);
}

TEST(TestValidator, ValidatorTwentyFourth)
{
  Calc::Validator valid("(-1)*3");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, true);
}

TEST(TestValidator, ValidatorTwentyFifth)
{
  Calc::Validator valid("tan(x*2)+(sin(x^2)-ln(x))*cos(x)");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, true);
}

TEST(TestValidator, ValidatorTwentySixth)
{
  Calc::Validator valid("tan(x*2)+(sin(x^2)-ln(x))*cos(x");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, false);
}

TEST(TestValidator, ValidatorTwentySeventh)
{
  Calc::Validator valid("tan(x*2)+(sin(x^2)-ln(x)*cos(x");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, false);
}

TEST(TestValidator, ValidatorTwentyEighth)
{
  Calc::Validator valid("log(sin(x))");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, true);
}

TEST(TestValidator, ValidatorTwentyNinth)
{
  Calc::Validator valid("log(sin(x)");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, false);
}

TEST(TestValidator, ValidatorThirtieth)
{
  Calc::Validator valid("log(sin(x))+x*2");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, true);
}

TEST(TestValidator, ValidatorThirtyFirst)
{
  Calc::Validator valid("1+3+cos(x+1)");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, true);
}

TEST(TestValidator, ValidatorThirtySecond)
{
  Calc::Validator valid("log(sin(x*10-3))");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, true);
}

TEST(TestValidator, ValidatorThirtyThird)
{
  Calc::Validator valid("log(sin(x*10-3)");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, false);
}

TEST(TestValidator, ValidatorThirtyFourth)
{
  Calc::Validator valid("10+(1+3)*(4-5)+5");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, true);
}

TEST(TestValidator, ValidatorThirtyFifth)
{
  Calc::Validator valid("(sqrt(x))-(1/2*sin(x^2-2))");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, true);
}

TEST(TestValidator, ValidatorThirtySixth)
{
  Calc::Validator valid("(sqrt(x))-(1/2*sin(x^2-2)");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, false);
}

TEST(TestValidator, ValidatorThirtySeventh)
{
  Calc::Validator valid("2.789*x+23.21");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, true);
}

TEST(TestValidator, ValidatorThirtyEighth)
{
  Calc::Validator valid("27.8.9*x+23.2.1");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, false);
}

TEST(TestValidator, ValidatorThirtyNingth)
{
  Calc::Validator valid("cos(30*x+9/7)+ln(5)^3/2");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, true);
}

TEST(TestValidator, ValidatorFortieth)
{
  Calc::Validator valid("25mod5");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, true);
}

TEST(TestValidator, ValidatorFortyFirst)
{
  Calc::Validator valid("25mod(-5)");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, true);
}

TEST(TestValidator, ValidatorFortySecond)
{
  Calc::Validator valid("-25mod5");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, true);
}

TEST(TestValidator, ValidatorFortyThird)
{
  Calc::Validator valid("---25mod5");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, false);
}

TEST(TestValidator, ValidatorFortyFourth)
{
  Calc::Validator valid("ln(x)");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, true);
}

TEST(TestValidator, ValidatorFortyFifth)
{
  Calc::Validator valid("x");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, true);
}

TEST(TestValidator, ValidatorFortySixth)
{
  Calc::Validator valid("log(x)");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, true);
}

TEST(TestValidator, ValidatorFortySeventh)
{
  Calc::Validator valid("1");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, true);
}

TEST(TestValidator, ValidatorFortyEighth)
{
  Calc::Validator valid("tan(sin(5sqrt(10mod106)))");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, false);
}

TEST(TestValidator, ValidatorFortyNinth)
{
  Calc::Validator valid("");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, false);
}

TEST(TestValidator, ValidatorFiftieth)
{
  Calc::Validator valid("tan(sin(sqrt(5mod6)))");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, true);
}

TEST(TestValidator, ValidatorFiftyFirst)
{
  Calc::Validator valid("tan(sin(sqrt(mod106)))");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, false);
}

TEST(TestValidator, ValidatorFiftySecond)
{
  Calc::Validator valid("z+5");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, false);
}

TEST(TestValidator, ValidatorFiftyThird)
{
  Calc::Validator valid("1sin(xc)");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, false);
}

TEST(TestValidator, ValidatorFiftyFourth)
{
  Calc::Validator valid("6x+sin(x)");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, false);
}

TEST(TestValidator, ValidatorFiftyFifth)
{
  Calc::Validator valid("6x820+9sin(x)");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, false);
}

TEST(TestValidator, ValidatorFiftySixth)
{
  Calc::Validator valid("ln()");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, false);
}

TEST(TestValidator, ValidatorFiftySeventh)
{
  Calc::Validator valid("(1.345+1.345)");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, true);
}

TEST(TestValidator, ValidatorFiftyEighth)
{
  Calc::Validator valid("(*1.345)");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, false);
}

TEST(TestValidator, ValidatorFiftyNingth)
{
  Calc::Validator valid("()");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, false);
}

TEST(TestValidator, ValidatorSixtieth)
{
  Calc::Validator valid("(1.345+)");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, false);
}

TEST(TestValidator, ValidatorSixtyFirst)
{
  Calc::Validator valid(" ");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, false);
}

TEST(TestValidator, ValidatorSixtySecond)
{
  Calc::Validator valid("sin(x)sin(x)");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, false);
}

TEST(TestValidator, ValidatorSixtyThird)
{
  Calc::Validator valid("");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, false);
}

TEST(TestValidator, ValidatorSixtyFourth)
{
  Calc::Validator valid("3.2E*3");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, false);
}

TEST(TestValidator, ValidatorSixtyFifth)
{
  Calc::Validator valid("3.2E-3");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, true);
}

TEST(TestValidator, ValidatorSixtySixth)
{
  Calc::Validator valid("3.2E+3");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, true);
}

TEST(TestValidator, ValidatorSixtySeventh)
{
  Calc::Validator valid("3.2E3");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, true);
}

TEST(TestValidator, ValidatorSixtyEighth)
{
  Calc::Validator valid("3.2/E3");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, false);
}

TEST(TestValidator, ValidatorSixtyNinth)
{
  Calc::Validator valid("tan(E3)");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, false);
}

TEST(TestValidator, ValidatorSeventy)
{
  Calc::Validator valid("xE+02");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, false);
}

TEST(TestValidator, ValidatorSeventyFirst)
{
  Calc::Validator valid("modE+02");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, false);
}

TEST(TestValidator, ValidatorSeventySecond)
{
  Calc::Validator valid("48.7Emod9");
  bool result = valid.ValidationOfInputStrings();
  ASSERT_EQ(result, false);
}

TEST(TestNotation, NotationFirst)
{
  Calc::Model model("1+3");
  model.ValidationOfInputString();
  model.СalculateTheFinalValue();
  ASSERT_EQ(model.GetValue(), 4);
  ASSERT_EQ(model.GetError(), false);
}

TEST(TestNotation, NotationSecond)
{
  Calc::Model model("(1+3)*10");
  model.ValidationOfInputString();
  model.СalculateTheFinalValue();
  ASSERT_EQ(model.GetValue(), 40);
  ASSERT_EQ(model.GetError(), false);
}

TEST(TestNotation, NotationThird)
{
  Calc::Model model("tan(0)");
  model.ValidationOfInputString();
  model.СalculateTheFinalValue();
  ASSERT_EQ(model.GetValue(), 0);
  ASSERT_EQ(model.GetError(), false);
}

TEST(TestNotation, NotationFourth)
{
  Calc::Model model("2^3^2");
  model.ValidationOfInputString();
  model.СalculateTheFinalValue();
  ASSERT_EQ(model.GetValue(), 512);
  ASSERT_EQ(model.GetError(), false);
}

TEST(TestNotation, NotationFifth)
{
  Calc::Model model("10mod3");
  model.ValidationOfInputString();
  model.СalculateTheFinalValue();
  ASSERT_EQ(model.GetValue(), 1);
  ASSERT_EQ(model.GetError(), false);
}

TEST(TestNotation, NotationSixth)
{
  Calc::Model model("(-1)*3");
  model.ValidationOfInputString();
  model.СalculateTheFinalValue();
  ASSERT_EQ(model.GetValue(), -3);
  ASSERT_EQ(model.GetError(), false);
}

TEST(TestNotation, NotationSeventh)
{
  Calc::Model model("-1*9");
  model.ValidationOfInputString();
  model.СalculateTheFinalValue();
  ASSERT_EQ(model.GetValue(), -9);
  ASSERT_EQ(model.GetError(), false);
}

TEST(TestNotation, NotationEighth)
{
  Calc::Model model("10+(1+3)*(4-5)+5");
  model.ValidationOfInputString();
  model.СalculateTheFinalValue();
  ASSERT_EQ(model.GetValue(), 11);
  ASSERT_EQ(model.GetError(), false);
}

TEST(TestNotation, NotationNinghth)
{
  Calc::Model model("2^3");
  model.ValidationOfInputString();
  model.СalculateTheFinalValue();
  ASSERT_EQ(model.GetValue(), 8);
  ASSERT_EQ(model.GetError(), false);
}

TEST(TestNotation, NotationTenth)
{
  Calc::Model model("1.34/5");
  model.ValidationOfInputString();
  model.СalculateTheFinalValue();
  ASSERT_EQ(model.GetValue(), 0.268);
  ASSERT_EQ(model.GetError(), false);
}

TEST(TestNotation, NotationEleventh)
{
  Calc::Model model("2^3");
  model.ValidationOfInputString();
  model.СalculateTheFinalValue();
  ASSERT_EQ(model.GetValue(), 8);
  ASSERT_EQ(model.GetError(), false);
}

TEST(TestNotation, NotationTwelfth)
{
  Calc::Model model("1.34+5.122");
  model.ValidationOfInputString();
  model.СalculateTheFinalValue();
  ASSERT_EQ(model.GetValue(), 6.462);
  ASSERT_EQ(model.GetError(), false);
}

TEST(TestNotation, NotationThirteenth)
{
  Calc::Model model("1.3*5.3");
  model.ValidationOfInputString();
  model.СalculateTheFinalValue();
  ASSERT_EQ(model.GetValue(), 6.89);
  ASSERT_EQ(model.GetError(), false);
}

TEST(TestNotation, NotationFourteenth)
{
  Calc::Model model("1.34-5.35");
  model.ValidationOfInputString();
  model.СalculateTheFinalValue();
  ASSERT_EQ(model.GetValue(), -4.01);
  ASSERT_EQ(model.GetError(), false);
}

TEST(TestNotation, NotationFifteenth)
{
  Calc::Model model("((9*0.2+18)+10)*3");
  model.ValidationOfInputString();
  model.СalculateTheFinalValue();
  ASSERT_EQ(model.GetValue(), 89.4);
  ASSERT_EQ(model.GetError(), false);
}

TEST(TestNotation, NotationSixteenth)
{
  Calc::Model model("3/2+6*10");
  model.ValidationOfInputString();
  model.СalculateTheFinalValue();
  ASSERT_EQ(model.GetValue(), 61.5);
  ASSERT_EQ(model.GetError(), false);
}

TEST(TestNotation, NotationSeventeenth)
{
  Calc::Model model("6*10*2*4");
  model.ValidationOfInputString();
  model.СalculateTheFinalValue();
  ASSERT_EQ(model.GetValue(), 480);
  ASSERT_EQ(model.GetError(), false);
}

TEST(TestNotation, NotationEighteenth)
{
  Calc::Model model("ln(1)");
  model.ValidationOfInputString();
  model.СalculateTheFinalValue();
  ASSERT_EQ(model.GetValue(), 0);
  ASSERT_EQ(model.GetError(), false);
}

TEST(TestNotation, NotationNinteenth)
{
  Calc::Model model("55+(5mod3-17)*12");
  model.ValidationOfInputString();
  model.СalculateTheFinalValue();
  ASSERT_EQ(model.GetValue(), -125);
  ASSERT_EQ(model.GetError(), false);
}

TEST(TestNotation, NotationTwentieth)
{
  Calc::Model model("(10/2+5)*(10*7-12)+3");
  model.ValidationOfInputString();
  model.СalculateTheFinalValue();
  ASSERT_EQ(model.GetValue(), 583);
  ASSERT_EQ(model.GetError(), false);
}

TEST(TestNotation, NotationTwentyFirst)
{
  Calc::Model model("((9*0.2+18)+10)*3");
  model.ValidationOfInputString();
  model.СalculateTheFinalValue();
  ASSERT_EQ(model.GetValue(), 89.4);
  ASSERT_EQ(model.GetError(), false);
}

TEST(TestNotation, NotationTwentySecond)
{
  Calc::Model model("sqrt(-1)");
  model.ValidationOfInputString();
  model.СalculateTheFinalValue();
  ASSERT_EQ(model.GetValue(), 0);
  ASSERT_EQ(model.GetError(), true);
}

TEST(TestNotation, NotationTwentyThird)
{
  Calc::Model model("ln(-1)");
  model.ValidationOfInputString();
  model.СalculateTheFinalValue();
  ASSERT_EQ(model.GetValue(), 0);
  ASSERT_EQ(model.GetError(), true);
}

TEST(TestNotation, NotationTwentyFourth)
{
  Calc::Model model("x+3", 1);
  model.ValidationOfInputString();
  model.СalculateTheFinalValue();
  ASSERT_EQ(model.GetValue(), 4);
  ASSERT_EQ(model.GetError(), false);
}

TEST(TestNotation, NotationTwentyFifth)
{
  Calc::Model model("log(-1)");
  model.ValidationOfInputString();
  model.СalculateTheFinalValue();
  ASSERT_EQ(model.GetValue(), 0);
  ASSERT_EQ(model.GetError(), true);
}

TEST(TestNotation, NotationTwentySixth)
{
  Calc::Model model("sqrt(4)");
  model.ValidationOfInputString();
  model.СalculateTheFinalValue();
  ASSERT_EQ(model.GetValue(), 2);
  ASSERT_EQ(model.GetError(), false);
}

TEST(TestNotation, NotationTwentySeventh)
{
  Calc::Model model("atan(0)");
  model.ValidationOfInputString();
  model.СalculateTheFinalValue();
  ASSERT_EQ(model.GetValue(), 0);
  ASSERT_EQ(model.GetError(), false);
}

TEST(TestNotation, NotationTwentyEighth)
{
  Calc::Model model("acos(1)");
  model.ValidationOfInputString();
  model.СalculateTheFinalValue();
  ASSERT_EQ(model.GetValue(), 0);
  ASSERT_EQ(model.GetError(), false);
}

TEST(TestNotation, NotationTwentyNinth)
{
  Calc::Model model("asin(0)");
  model.ValidationOfInputString();
  model.СalculateTheFinalValue();
  ASSERT_EQ(model.GetValue(), 0);
  ASSERT_EQ(model.GetError(), false);
}

TEST(TestNotation, NotationThirtieth)
{
  Calc::Model model("log(1)");
  model.ValidationOfInputString();
  model.СalculateTheFinalValue();
  ASSERT_EQ(model.GetValue(), 0);
  ASSERT_EQ(model.GetError(), false);
}

TEST(TestNotation, NotationThirtyFirst)
{
  Calc::Model model("ln(1)");
  model.ValidationOfInputString();
  model.СalculateTheFinalValue();
  ASSERT_EQ(model.GetValue(), 0);
  ASSERT_EQ(model.GetError(), false);
}

TEST(TestNotation, NotationThirtySecond)
{
  Calc::Model model("tan(0)");
  model.ValidationOfInputString();
  model.СalculateTheFinalValue();
  ASSERT_EQ(model.GetValue(), 0);
  ASSERT_EQ(model.GetError(), false);
}

TEST(TestNotation, NotationThirtyThird)
{
  Calc::Model model("cos(0)");
  model.ValidationOfInputString();
  model.СalculateTheFinalValue();
  ASSERT_EQ(model.GetValue(), 1);
  ASSERT_EQ(model.GetError(), false);
}

TEST(TestNotation, NotationThirtyFourth)
{
  Calc::Model model("sin(0)");
  model.ValidationOfInputString();
  model.СalculateTheFinalValue();
  ASSERT_EQ(model.GetValue(), 0);
  ASSERT_EQ(model.GetError(), false);
}

TEST(TestNotation, NotationThirtyFifth)
{
  Calc::Model model("5mod(-3)");
  model.ValidationOfInputString();
  model.СalculateTheFinalValue();
  ASSERT_EQ(model.GetValue(), 2);
  ASSERT_EQ(model.GetError(), false);
}

TEST(TestNotation, NotationThirtySixth)
{
  Calc::Model model("(-5)mod3");
  model.ValidationOfInputString();
  model.СalculateTheFinalValue();
  ASSERT_EQ(model.GetValue(), -2);
  ASSERT_EQ(model.GetError(), false);
}

TEST(TestNotation, NotationThirtySeventh)
{
  Calc::Model model("(-5)mod(-3)");
  model.ValidationOfInputString();
  model.СalculateTheFinalValue();
  ASSERT_EQ(model.GetValue(), -2);
  ASSERT_EQ(model.GetError(), false);
}

TEST(TestNotation, NotationThirtyEighth)
{
  Calc::Model model("cos(sin(x))", 0);
  model.ValidationOfInputString();
  model.СalculateTheFinalValue();
  ASSERT_EQ(model.GetValue(), 1);
  ASSERT_EQ(model.GetError(), false);
}

TEST(TestNotation, NotationThirtyNineth)
{
  Calc::Model model("10/0");
  model.ValidationOfInputString();
  model.СalculateTheFinalValue();
  ASSERT_EQ(model.GetValue(), 0);
  ASSERT_EQ(model.GetError(), true);
}

TEST(TestNotation, NotationFortieth)
{
  Calc::Model model("10mod0");
  model.ValidationOfInputString();
  model.СalculateTheFinalValue();
  ASSERT_EQ(model.GetError(), true);
}

TEST(TestNotation, NotationFortyFirst)
{
  Calc::Model model("acos(10)");
  model.ValidationOfInputString();
  model.СalculateTheFinalValue();
  ASSERT_EQ(model.GetValue(), 0);
  ASSERT_EQ(model.GetError(), true);
}

TEST(TestNotation, NotationFortySecond)
{
  Calc::Model model("asin(10)");
  model.ValidationOfInputString();
  model.СalculateTheFinalValue();
  ASSERT_EQ(model.GetValue(), 0);
  ASSERT_EQ(model.GetError(), true);
}

TEST(TestNotation, NotationFortyThird)
{
  Calc::Model model("tan(3.14+3.14/2)", 1);
  model.ValidationOfInputString();
  model.СalculateTheFinalValue();
  ASSERT_EQ(model.GetValue(), 0);
  ASSERT_EQ(model.GetError(), true);
}

TEST(TestNotation, NotationFortyFourth)
{
  std::stack<double> value;
  std::stack<int> priority;
  std::stack<int> type;
  Calc::Calculation calc(value, priority, type, 1);
  double first = INFINITY, final = 0;
  int type_ = cosine;
  calc.DifficultOperations(&first, &final, &type_);
  ASSERT_EQ(calc.GetError(), true);
}

TEST(TestNotation, NotationFortyFifth)
{
  std::stack<double> value;
  std::stack<int> priority;
  std::stack<int> type;
  Calc::Calculation calc(value, priority, type, 1);
  double first = INFINITY, final = 0;
  int type_ = sine;
  calc.DifficultOperations(&first, &final, &type_);
  ASSERT_EQ(calc.GetError(), true);
}

TEST(TestNotation, NotationFortySixth)
{
  Calc::Model model("62/(3-(4+(5*6)))");
  model.ValidationOfInputString();
  model.СalculateTheFinalValue();
  ASSERT_EQ(model.GetValue(), -2);
}

TEST(TestNotation, NotationFortySeventh)
{
  std::stack<double> value;
  std::stack<int> priority;
  std::stack<int> type;
  Calc::Calculation calc(value, priority, type, 1);
  double first = INFINITY, final = 0;
  int type_ = arctangent;
  calc.DifficultOperations(&first, &final, &type_);
  ASSERT_EQ(calc.GetError(), true);
}

TEST(TestNotation, NotationFortyEighth)
{
  Calc::Model model("3/(3-3)", 1);
  model.ValidationOfInputString();
  model.СalculateTheFinalValue();
  ASSERT_EQ(model.GetValue(), 0);
  ASSERT_EQ(model.GetError(), true);
}

TEST(TestNotation, NotationFortyNinth)
{
  Calc::Model model("3+(-(-3))", 1);
  model.ValidationOfInputString();
  model.СalculateTheFinalValue();
  ASSERT_EQ(model.GetValue(), 6);
  ASSERT_EQ(model.GetError(), false);
}

TEST(TestNotation, NotationSixty)
{
  Calc::Model model("3+(-(-3)", 1);
  model.ValidationOfInputString();
  model.СalculateTheFinalValue();
  ASSERT_EQ(model.GetValue(), 0);
  ASSERT_EQ(model.GetError(), true);
}

TEST(TestNotation, NotationSixtyFirst)
{
  Calc::Model model("3.3E+2", 1);
  model.ValidationOfInputString();
  model.СalculateTheFinalValue();
  ASSERT_EQ(model.GetValue(), 330);
  ASSERT_EQ(model.GetError(), false);
}

TEST(TestNotation, NotationSixtySecond)
{
  Calc::Model model("2.34E-3", 1);
  model.ValidationOfInputString();
  model.СalculateTheFinalValue();
  ASSERT_EQ(model.GetValue(), 0.00234);
  ASSERT_EQ(model.GetError(), false);
}

TEST(TestNotation, NotationSixtyFourth)
{
  Calc::Model model("2.5E-2+10", 1);
  model.ValidationOfInputString();
  model.СalculateTheFinalValue();
  ASSERT_EQ(model.GetValue(), 10.025);
  ASSERT_EQ(model.GetError(), false);
}

TEST(TestNotation, NotationSixtyFifth)
{
  Calc::Model model("3.3E2", 1);
  model.ValidationOfInputString();
  model.СalculateTheFinalValue();
  ASSERT_EQ(model.GetValue(), 330);
  ASSERT_EQ(model.GetError(), false);
}

TEST(TestNotation, NotationSixtySixth)
{
  Calc::Model model("1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+11", 1);
  model.ValidationOfInputString();
  model.СalculateTheFinalValue();
  ASSERT_EQ(model.GetValue(), 138);
  ASSERT_EQ(model.GetError(), false);
}

TEST(TestCredit, CreditFirst)
{
  double S = 100000;
  double N = 12;
  double R = 9;
  Calc::CreditCalc credit(S, N, R);
  credit.CalculationAnnuity();
  double P = credit.GetP();
  double overpayment = credit.GetOverpayment();
  double total = credit.GetTotal();
  ASSERT_EQ(8746, ceil(P));
  ASSERT_EQ(4942, ceil(overpayment));
  ASSERT_EQ(104942, ceil(total));
}

TEST(TestCredit, CreditSecond)
{
  double S = 50000;
  double N = 12;
  double R = 6;
  Calc::CreditCalc credit(S, N, R);
  credit.СalculationDifferentiated();
  double start = credit.GetStart();
  double end = credit.GetEnd();
  double overpayment = credit.GetOverpayment();
  double total = credit.GetTotal();
  ASSERT_EQ(4417, ceil(start));
  ASSERT_EQ(4188, ceil(end));
  ASSERT_EQ(1625, ceil(overpayment));
  ASSERT_EQ(51625, ceil(total));
}

TEST(TestCredit, CreditThird)
{
  double S = 10000;
  double N = 12;
  double R = 20;
  Calc::CreditCalc credit(S, N, R);
  credit.CalculationAnnuity();
  double P = credit.GetP();
  double overpayment = credit.GetOverpayment();
  double total = credit.GetTotal();
  ASSERT_EQ(927, ceil(P));
  ASSERT_EQ(1117, ceil(overpayment));
  ASSERT_EQ(11117, ceil(total));
}

TEST(TestCredit, CreditFourth)
{
  double S = 500000;
  double N = 108;
  double R = 13.9;
  Calc::CreditCalc credit(S, N, R);
  credit.СalculationDifferentiated();
  double start = credit.GetStart();
  double end = credit.GetEnd();
  double overpayment = credit.GetOverpayment();
  double total = credit.GetTotal();
  ASSERT_EQ(10422, ceil(start));
  ASSERT_EQ(4684, ceil(end));
  ASSERT_EQ(315646, ceil(overpayment));
  ASSERT_EQ(815646, ceil(total));
}

TEST(TestDeposit, DepositFirst)
{
  double P = 100000;
  double re = 1000;
  double wd = 500;
  int N = 366;
  double R = 12;
  int procent_fine = 13;
  int index_period_pay = 3;
  int index_re = 2;
  int index_wd = 2;
  Calc::DepositCalc deposit(P, re, wd, N, R, index_period_pay, index_re,
                               index_wd, procent_fine);
  deposit.DepositCalculation();
  double fine = deposit.GetFine();
  double total = deposit.GetTotal();
  double S = deposit.GetS();
  ASSERT_EQ(0, ceil(fine));
  ASSERT_EQ(12540, ceil(S));
  ASSERT_EQ(120040, ceil(total));
}

TEST(TestDeposit, DepositSecond)
{
  double P = 100000;
  double re = 1000;
  double wd = 500;
  int N = 366;
  double R = 12;
  int procent_fine = 13;
  int index_period_pay = 3;
  int index_re = 2;
  int index_wd = 2;
  Calc::DepositCalc deposit(P, re, wd, N, R, index_period_pay, index_re,
                               index_wd, procent_fine);
  deposit.DepositCalculationCapitalization();
  double fine = deposit.GetFine();
  double total = deposit.GetTotal();
  double S = deposit.GetS();
  ASSERT_EQ(0, ceil(fine));
  ASSERT_EQ(13148, ceil(S));
  ASSERT_EQ(120648, ceil(total));
}

TEST(TestDeposit, DepositThird) {
  double P = 100000;
  double re = 1000;
  double wd = 500;
  int N = 731;
  double R = 14;
  int procent_fine = 13;
  int index_period_pay = 4;
  int index_re = 3;
  int index_wd = 3;
  Calc::DepositCalc deposit(P, re, wd, N, R, index_period_pay, index_re,
                               index_wd, procent_fine);
  deposit.DepositCalculationCapitalization();
  double fine = deposit.GetFine();
  double total = deposit.GetTotal();
  double S = deposit.GetS();
  ASSERT_EQ(0, ceil(fine));
  ASSERT_EQ(32223, ceil(S));
  ASSERT_EQ(137223, ceil(total));
}

TEST(TestDeposit, DepositFourth)
{
  double P = 100000;
  double re = 1000;
  double wd = 500;
  int N = 731;
  double R = 14;
  int procent_fine = 13;
  int index_period_pay = 4;
  int index_re = 3;
  int index_wd = 3;
  Calc::DepositCalc deposit(P, re, wd, N, R, index_period_pay, index_re,
                               index_wd, procent_fine);
  deposit.DepositCalculation();
  double fine = deposit.GetFine();
  double total = deposit.GetTotal();
  double S = deposit.GetS();
  ASSERT_EQ(0, ceil(fine));
  ASSERT_EQ(28840, ceil(S));
  ASSERT_EQ(133840, ceil(total));
}

TEST(TestDeposit, DepositFifth) {
  double P = 10000;
  double re = 100;
  double wd = 50;
  int N = 7305;
  double R = 14;
  int procent_fine = 13;
  int index_period_pay = 5;
  int index_re = 5;
  int index_wd = 5;
  Calc::DepositCalc deposit(P, re, wd, N, R, index_period_pay, index_re,
                               index_wd, procent_fine);
  deposit.DepositCalculationCapitalization();
  double fine = deposit.GetFine();
  double total = deposit.GetTotal();
  double S = deposit.GetS();
  ASSERT_EQ(300, ceil(fine));
  ASSERT_EQ(132307, ceil(S));
  ASSERT_EQ(143357, ceil(total));
}

TEST(TestDeposit, DepositSixth)
{
  double P = 100000;
  double re = 100;
  double wd = 50;
  int N = 7305;
  double R = 14;
  int procent_fine = 13;
  int index_period_pay = 5;
  int index_re = 5;
  int index_wd = 5;
  Calc::DepositCalc deposit(P, re, wd, N, R, index_period_pay, index_re,
                               index_wd, procent_fine);
  deposit.DepositCalculation();
  double fine = deposit.GetFine();
  double total = deposit.GetTotal();
  double S = deposit.GetS();
  ASSERT_EQ(19636, ceil(fine));
  ASSERT_EQ(281039, ceil(S));
  ASSERT_EQ(382089, ceil(total));
}

TEST(TestDeposit, DepositSeventh) {
  double P = 120000;
  double re = 100;
  double wd = 30;
  int N = 30;
  double R = 4;
  int procent_fine = 13;
  int index_period_pay = 0;
  int index_re = 0;
  int index_wd = 0;
  Calc::DepositCalc deposit(P, re, wd, N, R, index_period_pay, index_re,
                               index_wd, procent_fine);
  deposit.DepositCalculationCapitalization();
  double fine = deposit.GetFine();
  double total = deposit.GetTotal();
  double S = deposit.GetS();
  ASSERT_EQ(0, ceil(fine));
  ASSERT_EQ(503, ceil(S));
  ASSERT_EQ(183503, ceil(total));
}

TEST(TestDeposit, DepositEight)
{
  double P = 120000;
  double re = 100;
  double wd = 30;
  int N = 30;
  double R = 4;
  int procent_fine = 0;
  int index_period_pay = 0;
  int index_re = 0;
  int index_wd = 0;
  Calc::DepositCalc deposit(P, re, wd, N, R, index_period_pay, index_re,
                               index_wd, procent_fine);
  deposit.DepositCalculation();
  double fine = deposit.GetFine();
  double total = deposit.GetTotal();
  double S = deposit.GetS();
  ASSERT_EQ(0, ceil(fine));
  ASSERT_EQ(502, ceil(S));
  ASSERT_EQ(183502, ceil(total));
}

TEST(TestDeposit, DepositNinth) {
  double P = 50000;
  double re = 100;
  double wd = 30;
  int N = 30;
  double R = 4;
  int procent_fine = 13;
  int index_period_pay = 1;
  int index_re = 1;
  int index_wd = 1;
  Calc::DepositCalc deposit(P, re, wd, N, R, index_period_pay, index_re,
                               index_wd, procent_fine);
  deposit.DepositCalculationCapitalization();
  double fine = deposit.GetFine();
  double total = deposit.GetTotal();
  double S = deposit.GetS();
  ASSERT_EQ(0, ceil(fine));
  ASSERT_EQ(155, ceil(S));
  ASSERT_EQ(50435, ceil(total));
}

TEST(TestDeposit, DepositTenth)
{
  double P = 50000;
  double re = 100;
  double wd = 30;
  int N = 30;
  double R = 4;
  int procent_fine = 13;
  int index_period_pay = 1;
  int index_re = 1;
  int index_wd = 1;
  Calc::DepositCalc deposit(P, re, wd, N, R, index_period_pay, index_re,
                               index_wd, procent_fine);
  deposit.DepositCalculation();
  double fine = deposit.GetFine();
  double total = deposit.GetTotal();
  double S = deposit.GetS();
  ASSERT_EQ(0, ceil(fine));
  ASSERT_EQ(154, ceil(S));
  ASSERT_EQ(50434, ceil(total));
}

TEST(TestDeposit, DepositEleventh) {
  double P = 50000;
  double re = 6000;
  double wd = 1000;
  int N = 121;
  double R = 4;
  int procent_fine = 13;
  int index_period_pay = 2;
  int index_re = 4;
  int index_wd = 4;
  Calc::DepositCalc deposit(P, re, wd, N, R, index_period_pay, index_re,
                               index_wd, procent_fine);
  deposit.DepositCalculationCapitalization();
  double fine = deposit.GetFine();
  double total = deposit.GetTotal();
  double S = deposit.GetS();
  ASSERT_EQ(0, ceil(fine));
  ASSERT_EQ(826, ceil(S));
  ASSERT_EQ(70826, ceil(total));
}

TEST(TestDeposit, DepositTwelve)
{
  double P = 78000;
  double re = 6000;
  double wd = 1000;
  int N = 121;
  double R = 24;
  int procent_fine = 13;
  int index_period_pay = 6;
  int index_re = 6;
  int index_wd = 6;
  Calc::DepositCalc deposit(P, re, wd, N, R, index_period_pay, index_re,
                               index_wd, procent_fine);
  deposit.DepositCalculation();
  double fine = deposit.GetFine();
  double total = deposit.GetTotal();
  double S = deposit.GetS();
  ASSERT_EQ(0, ceil(fine));
  ASSERT_EQ(6604, ceil(S));
  ASSERT_EQ(89604, ceil(total));
}

TEST(TestDeposit, DepositThitheenth) {
  double P = 50000;
  double re = 100;
  double wd = 30;
  int N = 182;
  double R = 4;
  int procent_fine = 13;
  int index_period_pay = 1;
  int index_re = 1;
  int index_wd = 1;
  Calc::DepositCalc deposit(P, re, wd, N, R, index_period_pay, index_re,
                               index_wd, procent_fine);
  deposit.DepositCalculationCapitalization();
  double fine = deposit.GetFine();
  double total = deposit.GetTotal();
  double S = deposit.GetS();
  ASSERT_EQ(0, ceil(fine));
  ASSERT_EQ(1026, ceil(S));
  ASSERT_EQ(52846, ceil(total));
}

TEST(TestDeposit, DepositFourteenth)
{
  double P = 50000;
  double re = 100;
  double wd = 30;
  int N = 182;
  double R = 4;
  int procent_fine = 13;
  int index_period_pay = 1;
  int index_re = 1;
  int index_wd = 1;
  Calc::DepositCalc deposit(P, re, wd, N, R, index_period_pay, index_re,
                               index_wd, procent_fine);
  deposit.DepositCalculation();
  double fine = deposit.GetFine();
  double total = deposit.GetTotal();
  double S = deposit.GetS();
  ASSERT_EQ(0, ceil(fine));
  ASSERT_EQ(1017, ceil(S));
  ASSERT_EQ(52837, ceil(total));
}

TEST(TestEmptyConstruct, EmptyConstruct)
{
  Calc::Model();
  Calc::Notation();
  Calc::Parser();
  Calc::Validator();
  Calc::CreditCalc();
  Calc::DepositCalc();
  Calc::Calculation();
}

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
