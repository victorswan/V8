/*=============================================================================
    Copyright (c) 2001-2009 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(SPIRIT_OPTIONAL_MARCH_23_2007_1117PM)
#define SPIRIT_OPTIONAL_MARCH_23_2007_1117PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/support/unused.hpp>
#include <boost/spirit/home/support/attributes.hpp>
#include <boost/spirit/home/support/info.hpp>
#include <boost/spirit/home/qi/parser.hpp>
#include <boost/spirit/home/qi/meta_compiler.hpp>
#include <boost/spirit/home/qi/detail/assign_to.hpp>
#include <boost/optional.hpp>
#include <vector>

namespace boost { namespace spirit
{
    ///////////////////////////////////////////////////////////////////////////
    // Enablers
    ///////////////////////////////////////////////////////////////////////////
    template <>
    struct use_operator<qi::domain, proto::tag::negate> // enables -p
      : mpl::true_ {};
}}

namespace boost { namespace spirit { namespace qi
{
    template <typename Subject>
    struct optional : unary_parser<optional<Subject> >
    {
        typedef Subject subject_type;

        template <typename Context, typename Iterator>
        struct attribute
        {
            // Build a boost::optional from the subject's attribute. Note
            // that boost::optional may return unused_type if the
            // subject's attribute is an unused_type.
            typedef typename
                traits::build_optional<
                    typename traits::
                        attribute_of<Subject, Context, Iterator>::type
                >::type
            type;
        };

        optional(Subject const& subject)
          : subject(subject) {}

        template <typename Iterator, typename Context
          , typename Skipper, typename Attribute>
        bool parse(Iterator& first, Iterator const& last
          , Context& context, Skipper const& skipper
          , Attribute& attr) const
        {
            // create a local value if Attribute is not unused_type
            typename spirit::result_of::optional_value<Attribute>::type val;

            if (subject.parse(first, last, context, skipper, val))
            {
                // assign the parsed value into our attribute
                spirit::traits::assign_to(val, attr);
            }
            return true;
        }

        template <typename Context>
        info what(Context& context) const
        {
            return info("optional", subject.what(context));
        }

        Subject subject;
    };

    ///////////////////////////////////////////////////////////////////////////
    // Parser generators: make_xxx function (objects)
    ///////////////////////////////////////////////////////////////////////////
    template <typename Elements, typename Modifiers>
    struct make_composite<proto::tag::negate, Elements, Modifiers>
      : make_unary_composite<Elements, optional>
    {};
}}}

namespace boost { namespace spirit { namespace traits
{
    template <typename Subject>
    struct has_semantic_action<qi::optional<Subject> >
      : unary_has_semantic_action<Subject> {};
}}}

#endif
