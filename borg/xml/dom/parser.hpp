#ifndef BORG_XML_DOM_PARSER_HPP
#define BORG_XML_DOM_PARSER_HPP

#include <boost/filesystem/path.hpp>
#include <borg/util/dereference_cast.hpp>
#include <borg/xml/lib/adapter.hpp>
#include <borg/xml/dom/types.hpp>
#include <borg/xml/dom/forward.hpp>

namespace borg {
namespace xml {
namespace dom {

#define BORG_XML_DOM_PARSER_OPTION(Traits, name) \
  BOOST_STATIC_CONSTANT(Traits::options_type, parse_ ## name = xml::dom::parser_impl<Traits>::name)

#define BORG_XML_DOM_PARSER_OPTIONS(Traits) \
  BORG_XML_DOM_PARSER_OPTION(Traits, recover); \
  BORG_XML_DOM_PARSER_OPTION(Traits, noent); \
  BORG_XML_DOM_PARSER_OPTION(Traits, dtdload); \
  BORG_XML_DOM_PARSER_OPTION(Traits, dtdattr); \
  BORG_XML_DOM_PARSER_OPTION(Traits, dtdvalid); \
  BORG_XML_DOM_PARSER_OPTION(Traits, noerror); \
  BORG_XML_DOM_PARSER_OPTION(Traits, nowarning); \
  BORG_XML_DOM_PARSER_OPTION(Traits, pedantic); \
  BORG_XML_DOM_PARSER_OPTION(Traits, noblanks);

//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct parser_interface
{
  XML_DOM_TYPES(typename Traits)
//  typedef typename Traits::template string<char_type>::type string_type;

  typedef parser_impl<Traits> impl;
  typedef unsigned long option;

  //! Parse a string.
  //-----------------------------------------------------------------------
  bool
  parse_string(const string_t<Traits, wchar_type> &str)
  {
    return impl::parse_string
      (dereference_cast<Derived>(this), str);
  }

  //! Parse a file.
  //-----------------------------------------------------------------------
  bool
  parse_file(const boost::filesystem::path &path)
  {
//    using namespace std;
//    cout << "parse_file(" << path.string() << ")" << endl;
//    cout.flush();

    return impl::parse_file
      (dereference_cast<Derived>(this), path.string().c_str());
  }

  bool
  parse_file(const boost::filesystem::path &path, const options_type &opt)
  {
//    using namespace std;
//    cout << "parse_file(" << path.string() << ", " << opt << ")" << endl;
//    cout.flush();
    
    return impl::parse_file
      (dereference_cast<Derived>(this), path.string().c_str(), opt);
  }

  //! Parse arbitrary input.
  //-----------------------------------------------------------------------
/*  template<class CharT>
  bool
  parse_file(const string<Traits, CharT> &input)
  {
    return impl::parse_file(dereference_cast<Derived>(this), input);
  }*/

  //! Return the parsed document.
  //-----------------------------------------------------------------------
  document_t<Traits>
  document() const
  {
    return impl::document
      (dereference_cast<Derived const>(this));
  }

  //! Return number of errors.
  //-----------------------------------------------------------------------
  bool
  error() const
  {
    return impl::error
      (dereference_cast<Derived const>(this));
  }

  //! Destroy the parser.
  //-----------------------------------------------------------------------
  void
  destroy()
  {
    impl::destroy
      (dereference_cast<Derived>(this));
  }
};

//---------------------------------------------------------------------------    
/*template<class Traits, class Derived>
struct parser_interface
{
  XML_DOM_TYPES(typename Traits)
  typedef typename traits::template string<char_type>::type string_type;

  typedef parser_impl<Traits> impl;
  
  bool parse(const string<Traits, wchar_type> &str)
  {
    return impl::parse(
  }
  
};*/

//---------------------------------------------------------------------------    
template<class Traits, class Derived>
struct parser_facade
{};

//---------------------------------------------------------------------------    
template<class Traits>
class parser
    : public boost::noncopyable
    , public parser_interface< Traits, parser<Traits> >
    , public parser_facade< Traits, parser<Traits> >
{
  typedef parser_impl<Traits> impl;

public:
  XML_DOM_TYPES(typename Traits)

  parser() 
      : m_parser(impl::create())
  {}
    
  template<typename A1>
  parser(const A1 &a1, typename boost::enable_if_c<
             !boost::is_same<A1, parser_type>::value, void
         >::type const *dummy = 0)
      : m_parser(impl::create(a1))
  {}

  template<typename A1, typename A2>
  parser(const A1 &a1, typename boost::enable_if_c<
             !boost::is_same<A1, parser_type>::value, A2 
         >::type const &a2)
      : m_parser(impl::create(a1, a2))
  {}

  ~parser()
  {
    impl::destroy(m_parser); 
  }

  operator parser_type() const { return m_parser; }

  parser_type
  operator->() const { return m_parser; }

private:
  friend class parser_impl< Traits >;
  friend class parser_facade< Traits, parser<Traits> >;

  parser_type m_parser;
  parser_type get() const { return m_parser; }
};

//---------------------------------------------------------------------------    

  
} // namespace dom
} // namespace xml
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_XML_DOM_PARSER_HPP
