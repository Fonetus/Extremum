#include <iostream>
#include <string>
#include <cmath>
#include <cstring>

/**
 * @brief Вычисляет математическое выражение, представленное в виде строки.
 *
 * @param str Строка, содержащая математическое выражение.
 * @param chislo Переменная для хранения промежуточных результатов или констант.
 * @return Результат вычисленного выражения.
 */
double calculate(std::string &str, double chislo);

/**
 * @brief Парсит и вычисляет выражение с операциями сложения и вычитания.
 *
 * @param str Строка, содержащая математическое выражение.
 * @param index Текущая позиция в строке.
 * @param chislo Переменная для хранения промежуточных результатов или констант.
 * @return Результат вычисленного выражения.
 */
double expression(std::string &str, unsigned &index, double chislo);

/**
 * @brief Парсит и вычисляет выражение с операциями умножения и деления.
 *
 * @param str Строка, содержащая математическое выражение.
 * @param index Текущая позиция в строке.
 * @param chislo Переменная для хранения промежуточных результатов или констант.
 * @return Результат вычисленного выражения.
 */
double multiply_divide(std::string &str, unsigned &index, double chislo);

/**
 * @brief Парсит и вычисляет выражение с операциями знаков (+ или -).
 *
 * @param str Строка, содержащая математическое выражение.
 * @param index Текущая позиция в строке.
 * @param chislo Переменная для хранения промежуточных результатов или констант.
 * @return Результат вычисленного выражения.
 */
double sign(std::string &str, unsigned &index, double chislo);

/**
 * @brief Парсит и вычисляет выражение с скобками и вложенными выражениями.
 *
 * @param str Строка, содержащая математическое выражение.
 * @param index Текущая позиция в строке.
 * @param chislo Переменная для хранения промежуточных результатов или констант.
 * @return Результат вычисленного выражения.
 */
double brackets(std::string &str, unsigned &index, double chislo);

/**
 * @brief Парсит и вычисляет числовое значение в строке.
 *
 * @param str Строка, содержащая математическое выражение.
 * @param index Текущая позиция в строке.
 * @param chislo Переменная для хранения промежуточных результатов или констант.
 * @return Числовое значение.
 */
double number(std::string &str, unsigned &index, double chislo);

/**
 * @brief Парсит и вычисляет идентификатор (переменную или функцию) в строке.
 *
 * @param str Строка, содержащая математическое выражение.
 * @param index Текущая позиция в строке.
 * @param chislo Переменная для хранения промежуточных результатов или констант.
 * @return Значение идентификатора.
 */
double identificator(std::string &str, unsigned &index, double chislo);

/**
 * @brief Вычисляет значение функции по ее имени и аргументу.
 *
 * @param name Имя функции.
 * @param str Строка, содержащая математическое выражение.
 * @param index Текущая позиция в строке.
 * @param chislo Переменная для хранения промежуточных результатов или констант.
 * @return Значение функции.
 */
double function(std::string &name, std::string &str, unsigned &index, double chislo);

double calculate(std::string &str, double chislo) {
    unsigned index = 0;
    double result = expression(str, index, chislo);

    if (index < str.length()) {
        std::cout << "Некорректный символ в позиции " << index + 1 << std::endl;
        exit(-1);
    }

    return result;
}

double expression(std::string &str, unsigned &index, double chislo) {
    double result;
    char operation;

    result = multiply_divide(str, index, chislo);

    while (index < str.length() &&
           (str[index] == '+' || str[index] == '-')) {
        operation = str[index];
        ++index;

        switch (operation) {
            case '+':
                result += multiply_divide(str, index, chislo);
                break;
            case '-':
                result -= multiply_divide(str, index, chislo);
                break;
        }
    }

    return result;
}

double multiply_divide(std::string &str, unsigned &index, double chislo) {
    double result;
    char operation;
    double div;

    result = sign(str, index, chislo);

    while (index < str.length() &&
           (str[index] == '*' || str[index] == '/')) {
        operation = str[index];
        ++index;

        switch (operation) {
            case '*':
                result *= sign(str, index, chislo);
                break;
            case '/':
                div = sign(str, index, chislo);

                if (div == 0.0) {
                    std::cout << "Деление на ноль" << std::endl;
                    exit(-1);
                }

                result /= div;
                break;
        }
    }

    return result;
}

double sign(std::string &str, unsigned &index, double chislo) {
    double result;

    if (index >= str.length()) {
        std::cout << "Неожиданный конец строки" << std::endl;
        exit(-1);
    }
    switch (str[index]) {
        case '+':
            ++index;
            result = sign(str, index, chislo);
            break;
        case '-':
            ++index;
            result = -sign(str, index, chislo);
            break;
        default:
            result = brackets(str, index, chislo);

            if (index <= str.length() - 1 && str[index] == '^') {
                ++index;
                result = pow(result, sign(str, index, chislo));
            }
    }
    return result;
}

double brackets(std::string &str, unsigned &index, double chislo) {
    double result;

    if (index >= str.length()) {
        std::cout << "Неожиданный конец строки" << std::endl;
        exit(-1);
    }

    if (str[index] == '(') {
        ++index;
        result = expression(str, index, chislo);

        if (index >= str.length() || str[index] != ')') {
            std::cout << "Ожидается \")\" в позиции " << index + 2 << std::endl;
            exit(-1);
        }

        ++index;
    } else {
        if (str[index] >= '0' && str[index] <= '9')
            result = number(str, index, chislo);
        else {
            if ((str[index] >= 'A' && str[index] <= 'Z') ||
                (str[index] >= 'a' && str[index] <= 'z') ||
                (str[index] == '_'))
                result = identificator(str, index, chislo);
            else {
                std::cout << "Некорректный символ в позиции " << index + 1 << std::endl;
                exit(-1);
            }
        }
    }

    return result;
}

double number(std::string &str, unsigned &index, double chislo) {
    double result = 0.0;
    char digit;
    double k = 10.0;

    while (index < str.length()) {
        digit = str[index++];

        if (digit >= '0' && digit <= '9')
            result = result * 10.0 + (digit - '0');
        else {
            --index;
            break;
        }
    }

    bool subtract = false;

    if (index < str.length()) {
        digit = str[index++];
        subtract = true;
    }

    if (digit == '.') {
        while (index < str.length()) {
            digit = str[index++];

            if (digit >= '0' && digit <= '9') {
                result += (digit - '0') / k;
                k *= 10.0;
            } else {
                --index;
                break;
            }
        }
    } else if (subtract) {
        --index;
    }

    return result;
}

double identificator(std::string &str, unsigned &index, double chislo) {
    std::string name = "";
    double result;

    while (index < str.length() &&
           ((str[index] >= 'a' && str[index] <= 'z') ||
            (str[index] >= 'A' && str[index] <= 'Z') ||
            (str[index] >= '0' && str[index] <= '9') ||
            (str[index] == '_')))
        name += str[index++];

    if (index < str.length() && str[index] == '(') {
        ++index;
        result = function(name, str, index, chislo);

        if (index >= str.length() || str[index] != ')') {
            std::cout << "Ожидается \")\" в позиции " << index + 2 << std::endl;
            exit(-1);
        }

        ++index;
    } else {
        result = chislo;
    }

    return result;
}

double function(std::string &name, std::string &str, unsigned &index, double chislo) {
    double argument = expression(str, index, chislo);

    if (strcmp(name.c_str(), "acos") == 0)
        return acos(argument);

    if (strcmp(name.c_str(), "asin") == 0)
        return asin(argument);

    if (strcmp(name.c_str(), "atan") == 0)
        return atan(argument);

    if (strcmp(name.c_str(), "cos") == 0)
        return cos(argument);

    if (strcmp(name.c_str(), "cosh") == 0)
        return cosh(argument);

    if (strcmp(name.c_str(), "exp") == 0)
        return exp(argument);

    if (strcmp(name.c_str(), "log") == 0)
        return log(argument);

    if (strcmp(name.c_str(), "log10") == 0)
        return log10(argument);

    if (strcmp(name.c_str(), "sin") == 0)
        return sin(argument);

    if (strcmp(name.c_str(), "sinh") == 0)
        return sinh(argument);

    if (strcmp(name.c_str(), "sqrt") == 0)
        return sqrt(argument);

    if (strcmp(name.c_str(), "tan") == 0)
        return tan(argument);

    if (strcmp(name.c_str(), "tanh") == 0)
        return tanh(argument);

    std::cout << "Неизвестная функция" << std::endl;
    exit(-1);
}