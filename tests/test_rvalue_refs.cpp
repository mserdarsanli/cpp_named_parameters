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

#include <memory>
#include <vector>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "named_parameters.hpp"


#define VectorPushBack( ... ) \
        MAKE_NAMED_MEMBER_1( push_back, value, __VA_ARGS__ )

#define VectorInsert( ... ) \
        MAKE_NAMED_MEMBER_2( insert, position, value, __VA_ARGS__ )

TEST_CASE( "Test vector operations" )
{
        using Catch::Matchers::Equals;

        std::vector< std::unique_ptr< int > > v;

        v.push_back( std::make_unique<int>( 100 ) );
        REQUIRE( v.size() == 1 );
        REQUIRE( *v[0] == 100 );

        VectorPushBack( v, value = std::make_unique<int>( 200 ) );
        REQUIRE( v.size() == 2 );
        REQUIRE( *v[0] == 100 );
        REQUIRE( *v[1] == 200 );

        VectorInsert( v, position = v.begin(), value = std::make_unique<int>( 999 ) );
        VectorInsert( v, value = std::make_unique<int>( 888 ), position = v.end() );
        REQUIRE( v.size() == 4 );
        REQUIRE( *v[0] == 999 );
        REQUIRE( *v[1] == 100 );
        REQUIRE( *v[2] == 200 );
        REQUIRE( *v[3] == 888 );
}
