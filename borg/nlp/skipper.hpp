#ifndef BORG_NLP_SKIPPER_HPP
#define BORG_NLP_SKIPPER_HPP

#include <borg/nlp/traits.hpp>

namespace borg {
namespace nlp {
  
using boost::spirit::space_p;
using boost::spirit::eol_p;
using boost::spirit::rule;
  
//----------------------------------------------------------------------------
struct skipper : public boost::spirit::grammar< skipper >
{
  skipper() {}

  template<typename ScannerT>
  struct definition
  {
    definition(skipper const &self)
    {
      skip 
        = space_p 
        | eol_p;
    }

    rule<ScannerT> skip;

    rule<ScannerT> const &
    start() const { return skip; }
  };
  
};

} // namespace nlp
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_NLP_SKIPPER_HPP
