#ifndef BORG_WX_STRING_HPP
#define BORG_WX_STRING_HPP

#include <borg/string.hpp>
#include <borg/range.hpp>
#include <borg/wx/traits.hpp>

namespace borg {

//----------------------------------------------------------------------------
/*  char *begin(wxString &str) { std::cout << "begin()" << std::endl; return const_cast<char *>(str.data()); }
char const *begin(const wxString &str) { std::cout << "begin()" << std::endl; return str.data(); }

char *end(wxString &str) { return const_cast<char *>(str.data() + str.Length()); }
char const *end(const wxString &str) { return str.data() + str.Length(); }*/

template<class StringT, class CharT>
struct sequence_impl< StringT, CharT const *, CharT *, wx::traits >
{
  BORG_STRING_TYPES( wx::traits )

  typedef CharT value_type;

  //------------------------------------------------------------------------
  //! Get the string beginning.
  //------------------------------------------------------------------------
  static char *
  begin(StringT &s)
  {
    return (value_type *)s.data();
  }
  
  static char const *
  begin(StringT const &s)
  {
    return const_cast<string_type *>(&s)->data();
  }
  
  //------------------------------------------------------------------------
  //! Get the string end.
  //------------------------------------------------------------------------
  static char *
  end(StringT &s)
  {
    return (CharT *)(s.data() + s.Length());
  }
  
  static char const *
  end(StringT const &s)
  {
    return const_cast<string_type *>(&s)->data() + s.Length();
  }
};

//----------------------------------------------------------------------------
template<class CharT>
class string_impl< CharT, wx::traits >
{
public:
  BORG_STRING_TYPES( wx::traits )

  typedef CharT value_type;
    
  //------------------------------------------------------------------------
  //! Create new string.
  //------------------------------------------------------------------------
  static string_type
  create(const_string_type const &s)
  {
    return string_type(s);
  }
  
  //------------------------------------------------------------------------
  //! Destroy string.
  //------------------------------------------------------------------------
  static void
  destroy(string_type &s)
  {
    s.Clear();
  }
  
  //------------------------------------------------------------------------
  //! Get the string length.
  //------------------------------------------------------------------------
  static index_type
  length(string_type const &s)
  {
    return s.Length();
  }
  
  static bool
  empty(string_type const &s)
  {
    return s.Length() == 0;
  }
  
  static bool
  equal(string_type const &s1, string_type const &s2)
  {
    return s1.Cmp(s2) == 0;
  }
  
  //------------------------------------------------------------------------
  static const CharT *
  c_str(const string_type &s)
  {
    return (CharT *)s.data();
  }

  //------------------------------------------------------------------------
  template<class Append>
  static string_type &
  append(string_type &s, const Append &a)
  {
    s.Append(a);
    
//    std::cout << "appended char: " << a << std::endl;
    
    return s;
  }
  
  
};
  
//----------------------------------------------------------------------------
/*template<class T>
class string< wx::traits, T >
    : public string_interface< wx::traits, string< wx::traits, T >, T >
    , public string_facade< wx::traits, string< wx::traits, T >, T >
{
public:
  BORG_ABSTRACT_STRING_TYPES( wx::traits )
  typedef wx::traits::string_type string_type;

  //! Copy constructor.
  string(string_type const &s)
    : m_str(s)
  {}

  //! Construct from raw string.
  string(const char_type *s)
    : m_str(s)
  {}

  string_type m_str;
};
*/
namespace wx {

typedef ::borg::string< wxChar, traits > string;
typedef ::borg::string_t< wxChar, traits > string_t;

} // namespace wx
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_WX_STRING_HPP
