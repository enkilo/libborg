#ifndef BORG_NLP_GRAMMAR_HPP
#define BORG_NLP_GRAMMAR_HPP

#include <map>
#include <boost/spirit/core.hpp>
#include <boost/spirit/tree/parse_tree.hpp>

#include <borg/nlp/traits.hpp>

namespace borg {
namespace nlp {

using boost::spirit::rule;
using boost::spirit::chlit;
using boost::spirit::parse;
using boost::spirit::parser_id;
using boost::spirit::pt_parse;
using boost::spirit::alpha_p;
using boost::spirit::digit_p;
using boost::spirit::punct_p;
using boost::spirit::space_p;
using boost::spirit::blank_p;
using boost::spirit::eol_p;
using boost::spirit::parse_info;
using boost::spirit::parser_context;
using boost::spirit::tree_parse_info;
using boost::spirit::token_node_d;
using boost::spirit::node_iter_data_factory;
using boost::spirit::node_val_data_factory;
  
//----------------------------------------------------------------------------
template<class traits, class context = parser_context<> >
struct grammar : public boost::spirit::grammar< grammar<traits>, context >
{
  grammar() {}

  template<typename ScannerT>
  struct definition
  {
    definition(grammar<traits> const &self)
    {
      // Define the debug names.
      self.rule_names[word.id()] = "word";
      self.rule_names[space.id()] = "space";
      self.rule_names[punct.id()] = "punct";
      self.rule_names[sentence.id()] = "sentence";
      self.rule_names[text.id()] = "text";

#ifdef BOOST_SPIRIT_DEBUG
      debug();
#endif
      
      word
        = token_node_d[ +alpha_p ]
        ;

      space
        = +(space_p | blank_p | eol_p)
        ;
      
      punct
        = +punct_p
        ;
        
      sentence 
        = word >> *(space >> word) >> punct
        ;
      
      text 
        = sentence >> *(text | sentence)
        ;
    }

#ifdef BOOST_SPIRIT_DEBUG
    void
    debug()
    {
      BOOST_SPIRIT_DEBUG_RULE(word);
      BOOST_SPIRIT_DEBUG_RULE(space);
      BOOST_SPIRIT_DEBUG_RULE(punct);
      BOOST_SPIRIT_DEBUG_RULE(sentence);
      BOOST_SPIRIT_DEBUG_RULE(text);
    }
#endif
      
    rule<ScannerT> const &
    start() const { return text; }

    rule<ScannerT>
    word, space, punct, sentence, text;
    
  };
  
  mutable std::map<parser_id, std::string> rule_names;
};

} // namespace nlp
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_NLP_GRAMMAR_HPP
