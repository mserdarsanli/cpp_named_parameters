# C++ Named Parameters

This project helps you use named parameters idiom in C++, with no runtime cost[1].
It differs from other libraries such that the user don't need to modify the
function they want to use with named parameters.

## Usage

Obtain a version of `named_parameters.hpp` from [release page](https://github.com/mserdarsanli/cpp_named_parameters/releases)
and include it in your project.
If you want to build it yourself, follow instructions at [Building](#building) section.

The header file contains macros which help writing wrappers with named parameters.
Create wrappers as follows:

    #define Vector3d( ... ) \
        MAKE_NAMED_3( Eigen::Vector3d, x, y, z, __VA_ARGS__ )

This examples wraps Eigen's `Vector3d` in a macro with the same name. Macro is defined
to accept 3 parameters with names x, y and z. The order of parameters used in the
macro should match the function definition. `...` and `__VA_ARGS__` need to be present
in the definition as shown above.

With the macro defined, it can be called as follows:

    Vector3d( x = 1.0, y = 2.0, z = 3.0 ); // Equivalent to Eigen::Vector3d( 1.0, 2.0, 3.0 )

    Vector3d( z = 3.0, y = 2.0, x = 1.0 ); // Also equivalent to Eigen::Vector3d( 1.0, 2.0, 3.0 )

### Member Functions

As this library is impleented with macros, wrapping non-static member functions can
be done when `this` is also passed as a parameter. An example is `std::vector`'s `insert`
function, which accepts `position` and `value` paremeters. Notice the `MEMBER` part of
the `MAKE_NAMED_XXX` macro, which causes `this` parameter to be added (not-named).

    #define VectorInsert( ... ) \
            MAKE_NAMED_MEMBER_2( insert, position, value, __VA_ARGS__ )

Now `v.insert( v.end(), 100 )` can be replaced by one of the following calls with named parameters.

    VectorInsert( v, position = v.end(), value = 100 );
    VectorInsert( v, value = 100, position = v.end() );

## Runtime Cost

As part of the implementation, this library wraps named parameter calls in a trivial lambda
expression. GCC generates indentical or equivalent assemblies on optimized builds.
TODO compiler explorer link here after publishing.

## Building

cd into directory and type `make`, which should generate `dist/named_parameters.hpp`.

## License

The MIT License. See COPYING file.
