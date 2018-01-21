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

#include <string.h>
#include <string>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "named_parameters.hpp"

#define strstr( ... ) \
        MAKE_NAMED_2( strstr, haystack, needle, __VA_ARGS__ )

#define memset( ... ) \
        MAKE_NAMED_3( memset, str, c, n, __VA_ARGS__ )

TEST_CASE( "Test strstr" )
{
        REQUIRE( nullptr == strstr( needle = "needle", haystack = "e" ) );
        REQUIRE( nullptr == strstr( haystack = "e", needle = "needle" ) );

        char hs[] = "Hello, World!";
        char nd[] = "World";

        REQUIRE( hs + 7 == strstr( needle = nd, haystack = hs ) );
        REQUIRE( hs + 7 == strstr( haystack = hs, needle = nd ) );
}

TEST_CASE( "Test memset" )
{
        std::string s = "Hello, World!";

        SECTION( "Args with normal order" )
        {
                memset( str = s.data() + 7, c = '#', n = 5 );
                REQUIRE( s == "Hello, #####!" );
        }

        SECTION( "Args with mixed order" )
        {
                memset( c = '#', str = s.data() + 7, n = 5 );
                REQUIRE( s == "Hello, #####!" );
        }

}
