//  Copyright (c) 2001-2009 Hartmut Kaiser
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_LEX_TOKEN_DEF_MAR_13_2007_0145PM)
#define BOOST_SPIRIT_LEX_TOKEN_DEF_MAR_13_2007_0145PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/support/unused.hpp>
#include <boost/spirit/home/support/argument.hpp>
#include <boost/spirit/home/support/info.hpp>
#include <boost/spirit/home/qi/parser.hpp>
#include <boost/spirit/home/qi/skip_over.hpp>
#include <boost/spirit/home/qi/detail/construct.hpp>
#include <boost/spirit/home/qi/detail/assign_to.hpp>
#include <boost/spirit/home/lex/reference.hpp>
#include <boost/spirit/home/lex/lexer_type.hpp>
#include <boost/spirit/home/lex/lexer/terminals.hpp>

#include <boost/fusion/include/vector.hpp>
#include <boost/mpl/if.hpp>
#include <boost/detail/iterator.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/variant.hpp>

#include <string>
#include <cstdlib>

namespace boost { namespace spirit { namespace lex
{
    ///////////////////////////////////////////////////////////////////////////
    //  This component represents a token definition
    ///////////////////////////////////////////////////////////////////////////
    template<typename Attribute = unused_type
      , typename Char = char
      , typename Idtype = std::size_t>
    struct token_def
      : proto::extends<
            typename proto::terminal<
                lex::reference<token_def<Attribute, Char, Idtype> const, Idtype> 
            >::type
          , token_def<Attribute, Char, Idtype> >
      , qi::parser<token_def<Attribute, Char, Idtype> >
      , lex::lexer_type<token_def<Attribute, Char, Idtype> >
    {
    private:
        // initialize proto base class
        typedef lex::reference<token_def const, Idtype> reference_;
        typedef typename proto::terminal<reference_>::type terminal_type;
        typedef proto::extends<terminal_type, token_def> proto_base_type;

        reference_ alias() const
        {
            return reference_(*this);
        }

    public:
        // Qi interface: metafunction calculating parser return type
        template <typename Context, typename Iterator>
        struct attribute
        {
            //  The return value of the token_def is either the specified 
            //  attribute type, or the pair of iterators from the match of the 
            //  corresponding token (if no attribute type has been specified),
            //  or unused_type (if omit has been specified).
            typedef typename Iterator::base_iterator_type iterator_type;
            typedef typename mpl::if_<
                traits::not_is_unused<Attribute>
              , typename mpl::if_<
                    is_same<Attribute, lex::omit>, unused_type, Attribute
                >::type
              , iterator_range<iterator_type>
            >::type type;
        };

    public:
        // Qi interface: parse functionality
        template <typename Iterator, typename Context
          , typename Skipper, typename Attribute_>
        bool parse(Iterator& first, Iterator const& last
          , Context& /*context*/, Skipper const& skipper
          , Attribute_& attr) const
        {
            qi::skip_over(first, last, skipper);   // always do a pre-skip

            if (first != last) {
                typedef typename 
                    boost::detail::iterator_traits<Iterator>::value_type 
                token_type;

                //  If the following assertion fires you probably forgot to  
                //  associate this token definition with a lexer instance.
                BOOST_ASSERT(std::size_t(~0) != token_state_);

                token_type &t = *first;
                if (token_id_ == t.id() && token_state_ == t.state()) {
                    spirit::traits::assign_to(t, attr);
                    ++first;
                    return true;
                }
            }
            return false;
        }

        template <typename Context>
        info what(Context& /*context*/) const
        {
            return info("token_def");
        }

        ///////////////////////////////////////////////////////////////////////
        // Lex interface: collect token definitions and put it into the 
        // provided lexer def
        template <typename LexerDef, typename String>
        void collect(LexerDef& lexdef, String const& state) const
        {
            std::size_t state_id = lexdef.add_state(state.c_str());

            // If the following assertion fires you are probably trying to use 
            // a single token_def instance in more than one lexer state. This 
            // is not possible. Please create a separate token_def instance 
            // from the same regular expression for each lexer state it needs 
            // to be associated with.
            BOOST_ASSERT(std::size_t(~0) == token_state_ || state_id == token_state_);

            token_state_ = state_id;
            if (0 == token_id_)
                token_id_ = lexdef.get_next_id();

            if (0 == def_.which()) {
                unique_id_ = lexdef.add_token(state.c_str()
                  , get<string_type>(def_), token_id_);
            }
            else {
                unique_id_ = lexdef.add_token(state.c_str()
                  , get<char_type>(def_), token_id_);
            }
        }

        template <typename LexerDef>
        void add_actions(LexerDef&) const {}

    public:
        typedef Char char_type;
        typedef Idtype id_type;
        typedef std::basic_string<char_type> string_type;

        // Lex interface: constructing token definitions
        token_def() 
          : proto_base_type(terminal_type::make(alias()))
          , def_('\0'), token_id_()
          , unique_id_(std::size_t(~0)), token_state_(std::size_t(~0))  {}

        explicit token_def(char_type def_, Idtype id_ = Idtype())
          : proto_base_type(terminal_type::make(alias()))
          , def_(def_)
          , token_id_(std::size_t(Idtype() == id_ ? def_ : id_))
          , unique_id_(std::size_t(~0)), token_state_(std::size_t(~0)) {}

        explicit token_def(string_type const& def_, Idtype id_ = Idtype())
          : proto_base_type(terminal_type::make(alias()))
          , def_(def_), token_id_(id_)
          , unique_id_(std::size_t(~0)), token_state_(std::size_t(~0)) {}

        template <typename String>
        token_def& operator= (String const& definition)
        {
            def_ = definition;
            token_id_ = Idtype();
            unique_id_ = std::size_t(~0);
            token_state_ = std::size_t(~0);
            return *this;
        }
        token_def& operator= (token_def const& rhs)
        {
            def_ = rhs.def_;
            token_id_ = rhs.token_id_;
            unique_id_ = rhs.unique_id_;
            token_state_ = rhs.token_state_;
            return *this;
        }

        // general accessors 
        Idtype const& id() const { return token_id_; }
        void id(Idtype const& id) { token_id_ = id; }
        std::size_t unique_id() const { return unique_id_; }

        string_type definition() const 
        { 
            return (0 == def_.which()) 
              ? get<string_type>(def_) : string_type(1, get<char_type>(def_));
        }
        std::size_t state() const { return token_state_; }

    private:
        variant<string_type, char_type> def_;
        mutable Idtype token_id_;
        mutable std::size_t unique_id_;
        mutable std::size_t token_state_;
    };

}}}

#endif
