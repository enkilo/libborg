#ifndef BORG_JUCE_TRAITS_HPP
#define BORG_JUCE_TRAITS_HPP

#include <juce/juce.h>

namespace borg {
namespace juce {

//----------------------------------------------------------------------------
struct traits
{
  typedef char               char_type;
  typedef wchar_t            wchar_type;
  typedef String             string_type;
  typedef String const       const_string_type; 
  typedef int                length_type;
  typedef int                index_type;
};

}// namespace juce
}// namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_JUCE_TRAITS_HPP
