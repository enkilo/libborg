#ifndef BORG_FS_FILE_HPP
#define BORG_FS_FILE_HPP

#include <stdint.h>
#include <borg/wrap/preproc.hpp>
#include <borg/wrap/wrapper.hpp>
#include <borg/util/dereference_cast.hpp>

#define BORG_FS_FILE_TYPES(Traits) \
    BORG_PP_USE_TYPE(Traits, file_type) \
    BORG_PP_USE_TYPE(Traits, finfo_type) \
    BORG_PP_USE_TYPE(Traits, fileperms_type) \
    typedef Traits::fileattrs_type fileattrs_type; \
    typedef Traits::flags_type flags_type; \
    typedef Traits::status_type status_type; \
    typedef Traits::size_type size_type; \
    typedef Traits::result_type result_type; \
    typedef Traits::string_type string_type; \
    typedef Traits::char_type char_type; \
    typedef Traits::iovec_type iovec_type; \
    typedef Traits::interval_type interval_type;

//---------------------------------------------------------------------------
namespace borg {
namespace fs {

enum status_t
{
  failure = -1,
  success = 0
};
  
typedef ::int32_t result_t;
typedef ::size_t size_t;
  
WRAP_PATTERN_FORWARD(file)
    
//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct file_interface
{
  BORG_FS_FILE_TYPES(typename Traits)
  
  typedef file_impl<Traits> impl;
  
  status_t
  close()
  {
    status_t st = (status_t)impl::close(dereference_cast<Derived>(this));
    dereference_cast<Derived>(this) = 0;
    return st;
  }
  
  result_t
  write(const void *buf, size_t n)
  {
    return impl::write(dereference_cast<Derived>(this), buf, n);
  }
};

//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct file_facade
{
};
  
//---------------------------------------------------------------------------
template<class Traits>
class file_t
    : public wrapper< typename Traits::file_type >
    , public file_interface< Traits, file_t<Traits> >
    , public file_facade< Traits, file_t<Traits> >
{
public:
  BORG_FS_FILE_TYPES(typename Traits)

  typedef wrapper<file_type> base_type;

  operator file_type &() const
  {
    return base_type::get();
  }

  file_t(file_type const &v) 
    : base_type(v) 
  {}

  template<template<class> class Adapter>
  file_t(Adapter<Traits> const &a)
    : base_type(a)
  {}
};

//---------------------------------------------------------------------------
template<class Traits>
class file
    : public file_interface< Traits, file_t<Traits> >
    , public file_facade< Traits, file_t<Traits> >
{
public:
  BORG_FS_FILE_TYPES(typename Traits)

  typedef file_impl<Traits> impl;
    
  file_type m_file;
  file_type &get() { return m_file; }
  
  file(const string_type &fname, const flags_type &flag, 
       const fileperms_type &perm)
  {
    impl::open(m_file, fname, flag, perm);
  }

  operator file_type() const
  {
    return m_file;
  }
  
private:
  friend class file_impl<Traits>;
  
  file<Traits> &
  operator=(const file_type &file)
  {
    m_file = file;
  }
  
};
  

} // namespace fs
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_FS_FILE_HPP
