#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/variant/recursive_wrapper.hpp>
#include <boost/lexical_cast.hpp>

class Parser
{
    public:
        bool evaluate(std::string e);
    private:
    protected:
};

#endif // PARSER_H_INCLUDED
