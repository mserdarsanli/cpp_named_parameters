# The MIT License (MIT)
#
# Copyright (c) 2018 Mustafa Serdar Sanli
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

CC=g++ -std=c++17 -Wall -Wpedantic

THIRD_PARTY_FLAGS=-I third_party/catch_1.9.6

dist/named_parameters.hpp: out/code_generator
	out/code_generator > dist/named_parameters.hpp

out/code_generator: src/code_generator.hpp src/code_generator.cpp
	${CC} -o out/code_generator src/code_generator.cpp

out/test_%: tests/test_%.cpp dist/named_parameters.hpp
	${CC} -I dist -I src ${THIRD_PARTY_FLAGS} -o $@ $<

# There is probably a better way to do this in make..
test: $(subst .cpp,,$(subst tests/,out/,$(wildcard tests/test_*.cpp)))
	true $(subst out/,&& out/, $^)

.PHONY: clean
clean:
	rm -f out/*
	rm -f dist/named_parameters.hpp
