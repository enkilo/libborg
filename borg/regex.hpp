#ifndef BORG_REGEX_HPP
#define BORG_REGEX_HPP

#include <string>
#include <boost/regex.hpp>
#include <boost/range.hpp>
#include <borg/string.hpp>

namespace borg
{
  using boost::basic_regex;
  using boost::regex_match;
  using boost::match_flag_type;
  using boost::match_default;
  
  template<class ForwardReadableRange, class CharT, class Traits>
  bool regex_match(const ForwardReadableRange &range,
                   const basic_regex<CharT, Traits> &e,
                   match_flag_type flags = match_default)
  {
    return regex_match(boost::begin(range), boost::end(range), e, flags);
  }
  
  template<class OutputIterator, class ForwardReadableRange, class CharT, 
           class RegexTraits>
  OutputIterator 
  regex_replace(OutputIterator out,
                const ForwardReadableRange &range,
                const basic_regex<CharT, RegexTraits> &e,
                const std::basic_string<CharT> &fmt,
                match_flag_type flags = match_default)
  {
    return regex_replace(out, boost::begin(range), boost::end(range), e,
                         fmt, flags);
  }
  
  template<class OutputIterator, class ForwardReadableRange, class CharT, 
           class RegexTraits>
  OutputIterator 
  regex_replace(OutputIterator out,
                const ForwardReadableRange &range,
                const basic_regex<CharT, RegexTraits> &e,
                const CharT *fmt,
                match_flag_type flags = match_default)
  {
    return regex_replace(out, boost::begin(range), boost::end(range), e,
                         fmt, flags);
  }
  
}

#endif //ndef BORG_REGEX_HPP
