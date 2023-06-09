//  Copyright (c) 2001-2009 Joel de Guzman
//  Copyright (c) 2001-2009 Hartmut Kaiser
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_KARMA_RULE_MAR_05_2007_0455PM)
#define BOOST_SPIRIT_KARMA_RULE_MAR_05_2007_0455PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/assert.hpp>
#include <boost/function.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/utility/enable_if.hpp>

#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/size.hpp>
#include <boost/fusion/include/make_vector.hpp>
#include <boost/fusion/include/cons.hpp>
#include <boost/fusion/include/as_list.hpp>
#include <boost/fusion/include/as_vector.hpp>

#include <boost/spirit/home/support/unused.hpp>
#include <boost/spirit/home/support/argument.hpp>
#include <boost/spirit/home/support/context.hpp>
#include <boost/spirit/home/support/info.hpp>
#include <boost/spirit/home/support/attributes.hpp>
#include <boost/spirit/home/support/nonterminal/extract_param.hpp>
#include <boost/spirit/home/support/nonterminal/locals.hpp>
#include <boost/spirit/home/karma/reference.hpp>
#include <boost/spirit/home/karma/detail/output_iterator.hpp>
#include <boost/spirit/home/karma/nonterminal/detail/generator_binder.hpp>
#include <boost/spirit/home/karma/nonterminal/detail/parameterized.hpp>

namespace boost { namespace spirit { namespace karma
{
    BOOST_PP_REPEAT(SPIRIT_ATTRIBUTES_LIMIT, SPIRIT_USING_ATTRIBUTE, _)

    using spirit::_pass;
    using spirit::_val;
    using spirit::_a;
    using spirit::_b;
    using spirit::_c;
    using spirit::_d;
    using spirit::_e;
    using spirit::_f;
    using spirit::_g;
    using spirit::_h;
    using spirit::_i;
    using spirit::_j;

    using spirit::info;
    using spirit::locals;

    template <
        typename OutputIterator
      , typename T1 = unused_type
      , typename T2 = unused_type
      , typename T3 = unused_type
    >
    struct rule
      : proto::extends<
            typename proto::terminal<
                reference<rule<OutputIterator, T1, T2, T3> const>
            >::type
          , rule<OutputIterator, T1, T2, T3>
        >
      , generator<rule<OutputIterator, T1, T2, T3> >
    {
        typedef mpl::int_<generator_properties::all_properties> properties;

        typedef OutputIterator iterator_type;
        typedef rule<OutputIterator, T1, T2, T3> this_type;
        typedef reference<this_type const> reference_;
        typedef typename proto::terminal<reference_>::type terminal;
        typedef proto::extends<terminal, this_type> base_type;
        typedef mpl::vector<T1, T2, T3> template_params;

        // the output iterator is always wrapped by karma
        typedef detail::output_iterator<OutputIterator, properties> 
            output_iterator;

        // locals_type is a sequence of types to be used as local variables
        typedef typename
            spirit::detail::extract_locals<template_params>::type
        locals_type;

        // The delimiter-generator type
        typedef typename
            spirit::detail::extract_component<
                karma::domain, template_params>::type
        delimiter_type;

        typedef typename
            spirit::detail::extract_sig<template_params>::type
        sig_type;

        // This is the rule's attribute type
        typedef typename
            spirit::detail::attr_from_sig<sig_type>::type
        attr_type;
        typedef typename add_reference<
            typename add_const<attr_type>::type>::type 
        attr_reference_type;

        // parameter_types is a sequence of types passed as parameters to the rule
        typedef typename
            spirit::detail::params_from_sig<sig_type>::type
        parameter_types;

        static size_t const params_size =
            fusion::result_of::size<parameter_types>::type::value;

        // the context passed to the right hand side of a rule contains
        // the attribute and the parameters for this particular rule invocation
        typedef context<
            fusion::cons<attr_reference_type, parameter_types>
          , locals_type>
        context_type;

        typedef function<
            bool(output_iterator&, context_type&, delimiter_type const&)>
        function_type;

        explicit rule(std::string const& name_ = "unnamed-rule")
          : base_type(terminal::make(alias()))
          , name_(name_)
        {
        }

        rule(rule const& rhs)
          : base_type(rhs)
          , name_(rhs.name_)
          , f(rhs.f)
        {
        }

        template <typename Expr>
        rule (Expr const& expr, std::string const& name_ = "unnamed-rule")
          : base_type(terminal::make(alias()))
          , name_(name_)
        {
            // Report invalid expression error as early as possible.
            // If you got an error_invalid_expression error message here, then
            // the expression (expr) is not a valid spirit karma expression.
            BOOST_SPIRIT_ASSERT_MATCH(karma::domain, Expr);

            f = detail::bind_generator<mpl::false_>(compile<karma::domain>(expr));
        }

        rule& operator=(rule const& rhs)
        {
            // The following assertion fires when you try to initialize a rule
            // from an uninitialized one. Did you mean to refer to the right
            // hand side rule instead of assigning from it? In this case you 
            // should write lhs = rhs.alias();
            BOOST_ASSERT(rhs.f);

            f = rhs.f;
            name_ = rhs.name_;
            return *this;
        }

        std::string const& name() const
        {
            return name_;
        }

        void name(std::string const& str)
        {
            name_ = str;
        }

        template <typename Expr>
        rule& operator=(Expr const& expr)
        {
            // Report invalid expression error as early as possible.
            // If you got an error_invalid_expression error message here, then
            // the expression (expr) is not a valid spirit karma expression.
            BOOST_SPIRIT_ASSERT_MATCH(karma::domain, Expr);

            f = detail::bind_generator<mpl::false_>(compile<karma::domain>(expr));
            return *this;
        }

        // g++ 3.3 barfs if this is a member function :(
        template <typename Expr>
        friend rule& operator%=(rule& r, Expr const& expr)
        {
            // Report invalid expression error as early as possible.
            // If you got an error_invalid_expression error message here, then
            // the expression (expr) is not a valid spirit karma expression.
            BOOST_SPIRIT_ASSERT_MATCH(karma::domain, Expr);

            r.f = detail::bind_generator<mpl::true_>(compile<karma::domain>(expr));
            return r;
        }

        // non-const version needed to suppress proto's %= kicking in
        template <typename Expr>
        friend rule& operator%=(rule& r, Expr& expr)
        {
            return r %= static_cast<Expr const&>(expr);
        }

        template <typename Context, typename Unused>
        struct attribute
        {
            typedef attr_type type;
        };

        template <typename Context, typename Delimiter, typename Attribute>
        bool generate(output_iterator& sink, Context&, Delimiter const& delim
          , Attribute const& attr) const
        {
            if (f)
            {
                // Create an attribute if none is supplied. 
                typedef traits::make_attribute<attr_type, Attribute> 
                    make_attribute;

                // If you are seeing a compilation error here, you are probably
                // trying to use a rule or a grammar which has inherited
                // attributes, without passing values for them.
                context_type context(traits::pre_transform<attr_type>(
                    make_attribute::call(attr)));

                // If you are seeing a compilation error here stating that the 
                // third parameter can't be converted to a karma::reference
                // then you are probably trying to use a rule or a grammar with 
                // an incompatible delimiter type.
                if (f(sink, context, delim))
                {
                    return true;
                }
            }
            return false;
        }

        template <typename Context, typename Delimiter, typename Attribute
          , typename Params>
        bool generate(output_iterator& sink, Context& caller_context
          , Delimiter const& delim, Attribute const& attr
          , Params const& params) const
        {
            if (f)
            {
                // Create an attribute if none is supplied. 
                typedef traits::make_attribute<attr_type, Attribute> 
                    make_attribute;

                // If you are seeing a compilation error here, you are probably
                // trying to use a rule or a grammar which has inherited
                // attributes, passing values of incompatible types for them.
                context_type context(traits::pre_transform<attr_type>(
                    make_attribute::call(attr)), params, caller_context);

                // If you are seeing a compilation error here stating that the 
                // third parameter can't be converted to a karma::reference
                // then you are probably trying to use a rule or a grammar with 
                // an incompatible delimiter type.
                if (f(sink, context, delim))
                {
                    return true;
                }
            }
            return false;
        }

        template <typename Context>
        info what(Context& /*context*/) const
        {
            return info(name_);
        }

        reference_ alias() const
        {
            return reference_(*this);
        }

        typename proto::terminal<this_type>::type copy() const
        {
            typename proto::terminal<this_type>::type result = {*this};
            return result;
        }

        // bring in the operator() overloads
        rule const& get_parameterized_subject() const { return *this; }
        typedef rule parameterized_subject_type;
        #include <boost/spirit/home/karma/nonterminal/detail/fcall.hpp>

        std::string name_;
        function_type f;
    };

}}}

#endif
