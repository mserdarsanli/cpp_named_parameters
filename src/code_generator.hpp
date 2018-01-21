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

#include <iomanip>
#include <iostream>
#include <sstream>

// Adds aligned backslashes on `endl` to make macros look nice
class macro_linebuf
{
public:
        macro_linebuf( std::ostream &out )
            : m_out( out )
        {
        }

        ~macro_linebuf()
        {
                if ( m_line_buf.str().size() )
                {
                        m_out << m_line_buf.str();
                }
        }

        void endl()
        {
                size_t line_size = m_line_buf.str().size();
                if ( line_size < 78 )
                {
                        m_line_buf << std::string( 78 - line_size, ' ' );
                }
                m_line_buf << " \\\n";

                m_out << m_line_buf.str();
                std::stringstream().swap( m_line_buf );
        }

        std::stringstream& get_line_buf()
        {
                return m_line_buf;
        }

private:
        std::ostream& m_out;
        std::stringstream m_line_buf;
};

struct macro_linebuf_endl
{
} endl;

template <typename T>
macro_linebuf& operator<<( macro_linebuf &lb, const T &val )
{
        lb.get_line_buf() << val;
        return lb;
}

template <>
macro_linebuf& operator<<( macro_linebuf &lb, const macro_linebuf_endl &endl )
{
        lb.endl();
        return lb;
}

void generate_named_param_macro( std::ostream &raw_out, int param_cnt, bool is_nonstatic )
{
        macro_linebuf out( raw_out );

        out << "#define MAKE_NAMED_" << ( is_nonstatic ? "MEMBER_" : "" ) << param_cnt << "( fnname," << endl;

        for ( int i = 1; i <= param_cnt; ++i )
        {
                if ( i % 8 == 1 )
                {
                        out << "    ";
                }
                out << "pnam" << std::setfill( '0' ) << std::setw( 2 ) << i << ", ";

                if ( i % 8 == 0 || i == param_cnt )
                {
                        out << endl;
                }
        }

        if ( is_nonstatic )
        {
                out << "    thisexpr," << endl;
        }

        for ( int i = 1; i <= param_cnt; ++i )
        {
                if ( i % 8 == 1 )
                {
                        out << "    ";
                }
                out << "pval" << std::setfill( '0' ) << std::setw( 2 ) << i;

                if ( i < param_cnt )
                {
                        out << ", ";
                }
                else
                {
                        out << " )";
                }

                if ( i % 8 == 0 || i == param_cnt )
                {
                        out << endl;
                }
        }

        out << "    [&]() -> auto" << endl;
        out << "    {" << endl;

        for ( int i = 1; i <= param_cnt; ++i )
        {
                out << "        auto&& _ref_ ## pval" << std::setfill( '0' ) << std::setw( 2 ) << i << ";" << endl;
        }

        out << "        return " << ( is_nonstatic ? "(thisexpr)." : "" ) << "fnname(" << endl;

        for ( int i = 1; i <= param_cnt; ++i )
        {
                out << "            std::forward< decltype( _ref_ ## pnam" << std::setfill( '0' ) << std::setw( 2 ) << i
                    << " ) >( _ref_ ## pnam" << std::setfill( '0' ) << std::setw( 2 ) << i << " )";
                if ( i < param_cnt )
                {
                        out << ",";
                }
                out << endl;
        }

        out << "        );" << endl;
        out << "    }()\n";
}
