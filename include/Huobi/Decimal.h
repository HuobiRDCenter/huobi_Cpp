#ifndef DECIMAL_H
#define DECIMAL_H

#include <string>
#include <iostream>

extern "C" {
#include "decDouble.h"
}

namespace Huobi {

    class Decimal {
    public:

        class Context {
        public:

            Context() {
                decContextDefault(&set, DEC_INIT_BASE);
            }

            decContext* get() const {
                return const_cast<decContext*> (&set);
            }
        private:
            decContext set;
        };

        Decimal() {
            decDoubleZero(&data);
        }

        explicit Decimal(double value) {
            char buf[DECDOUBLE_String] = {0};
            snprintf(buf, DECDOUBLE_String, "%g", value);
            decDoubleFromString(&data, buf, context.get());
        }

        explicit Decimal(const char* value) {
            decDoubleFromString(&data, value, context.get());
        }

        Decimal(const Decimal& obj) : data(obj.data) {
        }

        Decimal(int value) {
            decDoubleFromInt32(&data, value);
        }

        Decimal operator+(const Decimal& obj) {
            decDouble result;
            return decDoubleAdd(&result, &data, &obj.data, context.get());
        }

        Decimal operator-(const Decimal& obj) {
            decDouble result;
            return decDoubleSubtract(&result, &data, &obj.data, context.get());
        }

        Decimal operator*(const Decimal& obj) {
            decDouble result;
            return decDoubleMultiply(&result, &data, &obj.data, context.get());
        }

        Decimal operator/(const Decimal& obj) {
            decDouble result;
            return decDoubleDivide(&result, &data, &obj.data, context.get());
        }

        Decimal& operator+=(const Decimal& obj) {
            decDoubleAdd(&data, &data, &obj.data, context.get());
            return *this;
        }

        Decimal& operator-=(const Decimal& obj) {
            decDoubleSubtract(&data, &data, &obj.data, context.get());
            return *this;
        }

        Decimal& operator*=(const Decimal& obj) {
            decDoubleMultiply(&data, &data, &obj.data, context.get());
            return *this;
        }

        Decimal& operator/=(const Decimal& obj) {
            decDoubleDivide(&data, &data, &obj.data, context.get());
            return *this;
        }

        Decimal operator%(const Decimal& obj) {
            decDouble result;
            return decDoubleRemainder(&result, &data, &obj.data, context.get());
        }

        Decimal& operator=(const Decimal& obj) {
            decDoubleCopy(&data, &obj.data);
            return *this;
        }

        bool operator==(const Decimal& obj) const {
            decDouble result;
            decDoubleCompare(&result, &data, &obj.data, const_cast<decContext*> (context.get()));
            return decDoubleIsZero(&result);
        }

        bool operator!=(const Decimal& obj) const {
            return !(this->operator==(obj));
        }

        bool isZero() {
            return decDoubleIsZero(&data);
        }

        bool operator<(const Decimal & obj) const {
            decDouble result;
            decDoubleCompare(&result, &data, &obj.data, const_cast<decContext*> (context.get()));
            return decDoubleIsNegative(&result);
        }

        bool operator<=(const Decimal & obj) const {
            decDouble result;
            decDoubleCompare(&result, &data, &obj.data, const_cast<decContext*> (context.get()));
            return decDoubleIsNegative(&result) || decDoubleIsZero(&result);
        }

        bool operator>(const Decimal & obj) const {
            return !(this->operator>(obj));
        }

        bool operator>=(const Decimal & obj) const {
            decDouble result;
            decDoubleCompare(&result, &data, &obj.data, const_cast<decContext*> (context.get()));
            return decDoubleIsPositive(&result) || decDoubleIsZero(&result);
        }

        Decimal abs(const Decimal & obj) const {
            decDouble result;
            return Decimal(decDoubleAbs(&result, &data, context.get()));
        }

        double toDouble() {
            char str[DECDOUBLE_String] = {0};
            decDoubleToString(&data, str);
            return strtod(str, 0);
        }

        std::string toString() const {
            char buf[DECDOUBLE_String] = {0};
            return std::string(decDoubleToString(&data, buf));
        }

        static Decimal NaN() {
            static Decimal NaN = Decimal(1) / Decimal(0);
            return NaN;
        }

    private:

        Decimal(decDouble value) : data(value) {
        }

        Decimal(decDouble * value) : data(*value) {
        }

        Context context;
        decDouble data;
    };

    static std::ostream & operator<<(std::ostream &out, const Decimal& obj) {
        out << obj.toString();
        return out;
    }

    static std::istream & operator>>(std::istream &in, Decimal& obj) {
        std::string str;
        in >> str;
        obj = Decimal(str.c_str());
        return in;
    }
}

#endif /* DECIMAL_H */

