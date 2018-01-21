// The MIT License (MIT)
//
// Copyright (c) 2018 Mustafa Serdar Sanli
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "code_generator.hpp"

TEST_CASE( "Check generated code" )
{
        std::string expected = R"(
#define MAKE_NAMED_15( fnname,                                                 \
    pnam01, pnam02, pnam03, pnam04, pnam05, pnam06, pnam07, pnam08,            \
    pnam09, pnam10, pnam11, pnam12, pnam13, pnam14, pnam15,                    \
    pval01, pval02, pval03, pval04, pval05, pval06, pval07, pval08,            \
    pval09, pval10, pval11, pval12, pval13, pval14, pval15 )                   \
    [&]() -> auto                                                              \
    {                                                                          \
        auto&& _ref_ ## pval01;                                                \
        auto&& _ref_ ## pval02;                                                \
        auto&& _ref_ ## pval03;                                                \
        auto&& _ref_ ## pval04;                                                \
        auto&& _ref_ ## pval05;                                                \
        auto&& _ref_ ## pval06;                                                \
        auto&& _ref_ ## pval07;                                                \
        auto&& _ref_ ## pval08;                                                \
        auto&& _ref_ ## pval09;                                                \
        auto&& _ref_ ## pval10;                                                \
        auto&& _ref_ ## pval11;                                                \
        auto&& _ref_ ## pval12;                                                \
        auto&& _ref_ ## pval13;                                                \
        auto&& _ref_ ## pval14;                                                \
        auto&& _ref_ ## pval15;                                                \
        return fnname(                                                         \
            std::forward< decltype( _ref_ ## pnam01 ) >( _ref_ ## pnam01 ),    \
            std::forward< decltype( _ref_ ## pnam02 ) >( _ref_ ## pnam02 ),    \
            std::forward< decltype( _ref_ ## pnam03 ) >( _ref_ ## pnam03 ),    \
            std::forward< decltype( _ref_ ## pnam04 ) >( _ref_ ## pnam04 ),    \
            std::forward< decltype( _ref_ ## pnam05 ) >( _ref_ ## pnam05 ),    \
            std::forward< decltype( _ref_ ## pnam06 ) >( _ref_ ## pnam06 ),    \
            std::forward< decltype( _ref_ ## pnam07 ) >( _ref_ ## pnam07 ),    \
            std::forward< decltype( _ref_ ## pnam08 ) >( _ref_ ## pnam08 ),    \
            std::forward< decltype( _ref_ ## pnam09 ) >( _ref_ ## pnam09 ),    \
            std::forward< decltype( _ref_ ## pnam10 ) >( _ref_ ## pnam10 ),    \
            std::forward< decltype( _ref_ ## pnam11 ) >( _ref_ ## pnam11 ),    \
            std::forward< decltype( _ref_ ## pnam12 ) >( _ref_ ## pnam12 ),    \
            std::forward< decltype( _ref_ ## pnam13 ) >( _ref_ ## pnam13 ),    \
            std::forward< decltype( _ref_ ## pnam14 ) >( _ref_ ## pnam14 ),    \
            std::forward< decltype( _ref_ ## pnam15 ) >( _ref_ ## pnam15 )     \
        );                                                                     \
    }()
)" + 1;

        std::stringstream gen;
        generate_named_param_macro( gen, 15, false );

        CHECK( gen.str() == expected );
}

TEST_CASE( "Check generated nonstatic code" )
{
        std::string expected = R"(
#define MAKE_NAMED_MEMBER_3( fnname,                                           \
    pnam01, pnam02, pnam03,                                                    \
    thisexpr,                                                                  \
    pval01, pval02, pval03 )                                                   \
    [&]() -> auto                                                              \
    {                                                                          \
        auto&& _ref_ ## pval01;                                                \
        auto&& _ref_ ## pval02;                                                \
        auto&& _ref_ ## pval03;                                                \
        return (thisexpr).fnname(                                              \
            std::forward< decltype( _ref_ ## pnam01 ) >( _ref_ ## pnam01 ),    \
            std::forward< decltype( _ref_ ## pnam02 ) >( _ref_ ## pnam02 ),    \
            std::forward< decltype( _ref_ ## pnam03 ) >( _ref_ ## pnam03 )     \
        );                                                                     \
    }()
)" + 1;

        std::stringstream gen;
        generate_named_param_macro( gen, 3, true );

        CHECK( gen.str() == expected );
}
