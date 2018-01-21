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
#include <string>
#include <typeinfo>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "named_parameters.hpp"

struct Animal
{
        Animal( int id, std::string name )
          : m_id( id ), m_name( name )
        {
        }

        bool operator==( const Animal &ot )
        {
                return typeid( *this ) == typeid( ot )
                    && m_id == ot.m_id
                    && m_name == ot.m_name;
        }

        bool operator!=( const Animal &ot )
        {
                return !( *this == ot );
        }

        virtual std::string say( const std::string &s ) const = 0;

protected:
        int m_id;
        std::string m_name;
};

struct Cat : public Animal
{
        Cat( int id, std::string name )
          : Animal( id, name )
        {
        }

        std::string say( const std::string &s ) const override
        {
                return "[" + std::to_string( m_id ) + ":" + m_name + " talking] Meow " + s;
        }
};

struct Dog : public Animal
{
        Dog( int id, std::string name )
          : Animal( id, name )
        {
        }

        std::string say( const std::string &s ) const override
        {
                return "[" + std::to_string( m_id ) + ":" + m_name + " talking] Woof " + s;
        }
};

struct AnimalFactory
{
        static std::unique_ptr<Animal> CreateAnimal( std::string type, int id, std::string name )
        {
                if ( type == "cat" )
                {
                        return std::make_unique< Cat >( id, name );
                }

                if ( type == "dog" )
                {
                        return std::make_unique< Dog >( id, name );
                }

                return nullptr;
        }
};


#define MakeDog( ... ) \
        MAKE_NAMED_2( Dog, id, name, __VA_ARGS__ )

TEST_CASE( "Test constructors" )
{
        REQUIRE( Dog( 100, "Puppy" ) == MakeDog( id = 100, name = "Puppy" ) );
        REQUIRE( Dog( 101, "Puppy" ) != MakeDog( id = 100, name = "Puppy" ) );
        REQUIRE( Dog( 100, "Puppy" ) == MakeDog( name = "Puppy", id = 100 ) );
}

#define CreateAnimal( ... ) \
        MAKE_NAMED_3( AnimalFactory::CreateAnimal, type, id, name, __VA_ARGS__ )

TEST_CASE( "Test static member functions" )
{
        REQUIRE( Cat( 100, "qwe" ) == *CreateAnimal( type = "cat", id = 100, name = "qwe" ) );
        REQUIRE( Dog( 100, "qwe" ) != *CreateAnimal( type = "cat", id = 100, name = "qwe" ) );
}

#define AnimalSay( ... ) \
        MAKE_NAMED_MEMBER_1( say, what, __VA_ARGS__ )

TEST_CASE( "Test non-static member functions" )
{
        REQUIRE( Dog( 100, "Puppy" ).say( "hi" ) == "[100:Puppy talking] Woof hi" );

        Dog doggo( 100, "Puppy" );
        REQUIRE( AnimalSay( doggo, what = "hi" ) == "[100:Puppy talking] Woof hi" );

        // Check if preprocessor handles comma inside
        REQUIRE( AnimalSay( Cat( 3, "Kitty" ), what = "hello" ) == "[3:Kitty talking] Meow hello" );
}
