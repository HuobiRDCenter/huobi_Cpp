#ifndef INPUTCHEKER_H
#define INPUTCHEKER_H

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <ctype.h>
#include <list>
#include <functional>
#include <regex>

#include "Huobi/HuobiApiException.h"

namespace Huobi {

    class InputChecker {
    private:
        static InputChecker* instance;
    public:
        static InputChecker* checker();
    private:

        bool isSpecialChar(const char* str) {

            int size = strlen(str);
            for (int i = 0; i < size; i++) {
                if (ispunct(str[i])) {
                    return true;
                }
            }
            return false;
        }

        InputChecker() {
        }
    public:

        template <typename T>
        InputChecker* shouldBiggerThanZero(T value, std::string name) {
            if (value <= 0) {
                throw HuobiApiException(HuobiApiException::INPUT_ERROR,
                        "[Input] " + name + " should greater than 0");
            }
            return checker();
        }

        template <typename T>
        InputChecker* shouldZero(T value, std::string name) {
            if (value != 0) {
                throw HuobiApiException(HuobiApiException::INPUT_ERROR,
                        "[Input] " + name + "is unnecessary");
            }
            return checker();
        }

        InputChecker* shouldNotNull(const std::string& value, const std::string& name) {
            if (value.empty()) {
                throw HuobiApiException(HuobiApiException::INPUT_ERROR,
                        "[Input] " + name + " should greater than 0");
            }
            return checker();
        }

        InputChecker* checkSymbol(const std::string& symbol) {
            if (symbol.empty()) {
                throw HuobiApiException(HuobiApiException::INPUT_ERROR,
                        "[Input] Symbol is mandatory");
            }
            if (isSpecialChar(symbol.c_str())) {
                throw HuobiApiException(HuobiApiException::INPUT_ERROR,
                        "[Input] " + symbol + " is invalid symbol");
            }
            return checker();
        }
        
        InputChecker* checkCurrency(const std::string& currency) {
            if (currency.empty()) {
                throw HuobiApiException(HuobiApiException::INPUT_ERROR,
                        "[Input] Currency is mandatory");
            }
            if (isSpecialChar(currency.c_str())) {
                throw HuobiApiException(HuobiApiException::INPUT_ERROR,
                        "[Input] " + currency + " is invalid currency");
            }
            return checker();
        }

        InputChecker* checkETF(const std::string& symbol) {
            if (symbol != "hb10") {
                throw HuobiApiException(HuobiApiException::INPUT_ERROR,
                        "currently only support hb10 :-)");
            }
            return checker();
        }

        InputChecker* checkRange(int size, int min, int max, std::string name) {
            if (!(min <= size && size <= max)) {
                throw HuobiApiException(HuobiApiException::INPUT_ERROR,
                        "[Input] " + name + " is out of bound. " + std::to_string(size) +
                        " is not in [" + std::to_string(min) + "," + std::to_string(max) + "]");
            }
            return checker();
        }

        InputChecker* checkSymbolList(std::list<std::string> symbols) {
            if (symbols.size() == 0) {
                throw HuobiApiException(HuobiApiException::INPUT_ERROR, "[Input] Symbol is mandatory");
            }
            for (std::string symbol : symbols) {
                checkSymbol(symbol);
            }
            return checker();
        }

        InputChecker* greaterOrEqual(int value, int base, std::string name) {
            if (value < base) {
                throw HuobiApiException(HuobiApiException::INPUT_ERROR,
                        "[Input] " + name + " should be greater than " + std::to_string(base));
            }
            return checker();
        }

        template <typename T>

        InputChecker* checkList(std::list<T> list, int min, int max, std::string name) {
            if (list .size() != 0) {
                if (list.size() > max) {
                    throw HuobiApiException(HuobiApiException::INPUT_ERROR,
                            "[Input] " + name + " is out of bound, the max size is " + std::to_string(max));
                } else if (list.size() < min) {
                    throw HuobiApiException(HuobiApiException::INPUT_ERROR,
                            "[Input] " + name + " should contain " + std::to_string(min) + " item(s) at least");
                }
            } else {
                throw HuobiApiException(HuobiApiException::INPUT_ERROR,
                        "[Input] " + name + "should have value");
            }
            return checker();
        }

        template <typename T>
        InputChecker* checkCallback(const std::function<void(const T&) >& callback) {
            if (callback) {
                return checker();
            }
            throw HuobiApiException(HuobiApiException::INPUT_ERROR, "no callback");
        }
        
        InputChecker* checkDate(const std::string& value, std::string name) {
            if (value.empty()) {
                return checker();
            }
            std::regex e("^\\d{4}\\-(0?[1-9]|[1][012])\\-(0?[1-9]|[12][0-9]|3[01])$");
            if (!std::regex_match (value.begin(), value.end(), e)) {
                throw HuobiApiException(HuobiApiException::INPUT_ERROR, "The " + name + "is not correct data format");
                return checker();
            }
            return checker();
        }

    };

}
#endif /* INPUTCHEKER_H */

