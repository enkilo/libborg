#ifndef BORG_XML_DOM_WRITER_HPP
#define BORG_XML_DOM_WRITER_HPP

#include <boost/noncopyable.hpp>
#include <boost/utility/enable_if.hpp>
#include <borg/xml/dom/node.hpp>
#include <borg/util/dereference_cast.hpp>
#include <cstdarg>

namespace borg {
namespace xml {
namespace dom {

//---------------------------------------------------------------------------
//! Writer interface.
//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct writer_interface 
{
  XML_DOM_TYPES(typename Traits)

  typedef writer_impl<Traits> impl;

  //! Gets the character encoding.
  //-----------------------------------------------------------------------
  string_t<Traits, const wchar_type>
  get_encoding() const
  {
    return impl::get_encoding(dereference_cast<Derived const>(this));
  }
  
  //! Sets the character encoding.
  //-----------------------------------------------------------------------
  void
  set_encoding(const string<wchar_type, Traits> &str) const
  {
    return impl::set_encoding(dereference_cast<Derived const>(this), str);
  }  
  
  //! Set/get features.
  //-----------------------------------------------------------------------
  void
  set_feature(const string<wchar_type, Traits> &name, bool state) const
  {
    return impl::set_feature(dereference_cast<Derived const>(this), name, state);
  }  
  
  bool
  get_feature(const string<wchar_type, Traits> &name) const
  {
    return impl::get_feature(dereference_cast<Derived const>(this));
  }  
  
  //! Sets the line ending sequence.
  //-----------------------------------------------------------------------
  void
  set_newline(const string<wchar_type, Traits> &nl) const
  {
    return impl::set_newline(dereference_cast<Derived const>(this), nl);
  }  
  
  string<Traits, const wchar_type>
  get_newline() const
  {
    return impl::get_newline(dereference_cast<Derived const>(this));
  }  
  
  //! Writes node to the specified format target.
  //-----------------------------------------------------------------------
  template<class FormatTarget, class NodeT>
  status_type
  write(const FormatTarget &t, const NodeT &n) const
  {
    return impl::write(dereference_cast<Derived const>(this), t, n);
  }  
  
  //! Writes node to the associated format target.
  //-----------------------------------------------------------------------
  status_type
  write(const node_t<Traits> &node) const
  {
    return impl::write
      (dereference_cast<Derived const>(this), (node_type)node);
  }  
  
  status_type
  write(const attribute_t<Traits> &attr) const
  {
    return impl::write
      (dereference_cast<Derived const>(this), (attribute_type)attr);
  }  
  
  status_type
  write(const string_t<wchar_type, Traits> &str) const
  {
    return impl::write
      (dereference_cast<Derived const>(this), str);
  }  
  
  status_type
  write(const char *format, ...) const
  {
    status_type ret;
    va_list args;
    va_start(args, format);
    
    ret = impl::write
      (dereference_cast<Derived const>(this), format, args);

    va_end(args);
    return ret;
  }
  
  //! Start writing a node (Write the part before the children).
  //-----------------------------------------------------------------------
  template<class NodeT>
  status_type
  start(const NodeT &n) const
  {
    return impl::start(dereference_cast<Derived const>(this), n);
  }  
  
  template<class NodeT>
  status_type
  end(const NodeT &n) const
  {
    return impl::end(dereference_cast<Derived const>(this), n);
  }  
  
  //-----------------------------------------------------------------------
  void
  flush() const
  {
    impl::flush(dereference_cast<Derived const>(this));
  }
  
  //-----------------------------------------------------------------------
  void
  dump() const
  {
    impl::dump(dereference_cast<Derived const>(this));
  }
  
  //-----------------------------------------------------------------------
  status_type
  set_indent(int i = true)
  {
    return impl::set_indent(dereference_cast<Derived>(this), i);
  }
  
  status_type
  set_indent(const char *i/* = " "*/)
  {
    return set_indent(string_t<wchar_type, Traits>(i));
  }

  status_type
  set_indent(const string_t<wchar_type, Traits> &i)
  {
    return impl::set_indent
      (dereference_cast<Derived>(this), (wchar_type *)i);
  }
  
  int
  get_indent() const
  {
    return impl::get_indent
      (dereference_cast<Derived const>(this));
  }
  
/*  void
  set_indent(int i)
  {
    impl::set_indent(dereference_cast<Derived>(this), i);
  }

  void
  set_indent(const char *s)
  {
    impl::set_indent(dereference_cast<Derived>(this), s);
  }*/
};

//---------------------------------------------------------------------------
//! Writer facade.
//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct writer_facade
{
  typedef writer_impl<Traits> impl;

  XML_DOM_TYPES(typename Traits)
    
  operator writer_type() const
  {
    return dereference_cast<Derived const>(this).get();
  }
};

//---------------------------------------------------------------------------
template<class Traits>
class writer 
    : public boost::noncopyable
    , public writer_interface< Traits, writer<Traits> >
    , public writer_facade< Traits, writer<Traits> >
{
  typedef writer_impl<Traits> impl;
  
public:
  XML_DOM_TYPES(typename Traits)

  template<typename A1>
  writer(const A1 &a1, typename boost::enable_if_c<
             !boost::is_same<A1, writer_type>::value, void 
         >::type const *dummy = 0)
      : m_writer(impl::create(a1))
  {}

  template<typename A1, typename A2>
  writer(const A1 &a1, const typename boost::enable_if_c< !boost::is_same<A1, writer_type>::value, A2 >::type &a2)
      : m_writer(impl::create(a1, a2))
  {}
  
  ~writer() { impl::destroy(m_writer); }

  operator writer_type() const { return m_writer; }

  writer_type
  operator->() const { return m_writer; }

private:
  friend class writer_impl<Traits>;    
  friend class writer_facade< Traits, writer<Traits> >;
  
  writer_type m_writer;
  writer_type get() const { return m_writer; }
};  
  
} // namespace dom
} // namespace xml
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_XML_DOM_WRITER_HPP
