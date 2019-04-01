/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestDecimal.h
 * Author: mawenrui
 *
 * Created on March 22, 2019, 6:07 PM
 */

#ifndef TESTDECIMAL_H
#define TESTDECIMAL_H

#include <gtest/gtest.h>
#include "Huobi/Decimal.h"

using namespace Huobi;

TEST(TestDecimal, add) {
    {
        Decimal a("123.456");
        Decimal b("456.123");
        ASSERT_EQ(Decimal(579.579), a + b);
        a += b;
        ASSERT_EQ(Decimal(579.579), a);
    }
    {
        Decimal a("123.456");
        Decimal b("-123.456");
        ASSERT_EQ(Decimal(0), a + b);
        a += b;
        ASSERT_EQ(Decimal(0), a);
    }
}

TEST(TestDecimal, sub) {
    {
        Decimal a("123.456");
        Decimal b("456.123");
        ASSERT_EQ(Decimal(-332.667), a - b);
        a -= b;
        ASSERT_EQ(Decimal(-332.667), a);
    }
    {
        Decimal a("123.456");
        Decimal b("123.456");
        ASSERT_EQ(Decimal(0), a - b);
        a -= b;
        ASSERT_EQ(Decimal(0), a);
    }
}

TEST(TestDecimal, Mul) {
    {
        Decimal a("123.456");
        Decimal b("456.123");
        ASSERT_EQ(Decimal("56311.121088"), a * b);
        a *= b;
        ASSERT_EQ(Decimal("56311.121088"), a);
    }
    {
        Decimal a("123.456");
        Decimal b("0");
        ASSERT_EQ(Decimal(0), a * b);
        a *= b;
        ASSERT_EQ(Decimal(0), a);
    }
}

TEST(TestDecimal, Div) {
    {
        Decimal a("123.456");
        Decimal b("456.123");
        ASSERT_EQ(Decimal("0.2706638340973816"), a / b);
        a /= b;
        printf("!!!!!");
        printf(a.toString().c_str());
        ASSERT_EQ(Decimal("0.2706638340973816"), a);
    }
    {
        Decimal a("0");
        Decimal b("456.123");
        ASSERT_EQ(Decimal(0), a / b);
        a /= b;
        ASSERT_EQ(Decimal(0), a);
    }
    {
        Decimal a("123.456");
        Decimal b("0");
        ASSERT_EQ(Decimal::NaN(), a / b);
        a /= b;
        ASSERT_EQ(Decimal::NaN(), a);
    }
}


#endif /* TESTDECIMAL_H */

