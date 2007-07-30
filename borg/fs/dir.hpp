#ifndef BORG_FS_DIR_HPP
#define BORG_FS_DIR_HPP

#include <borg/wrap/preproc.hpp>
#include <borg/wrap/wrapper.hpp>

#define BORG_FS_DIR_TYPES(Traits) \
    typedef Traits::status_type status_type; \
    typedef Traits::string_type string_type;

//---------------------------------------------------------------------------
namespace borg {
namespace fs {
  
WRAP_PATTERN_FORWARD(dir)
    
//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct dir_i 
{
  BORG_FS_DIR_TYPES(typename Traits)
  
  typedef dir_impl<Traits> impl;
};

//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct dir_facade
{
};
  
//---------------------------------------------------------------------------
template<class Traits>
class dir_t
    : public wrapper< typename Traits::dir_type >
    , public dir_interface< Traits, dir_t<Traits> >
    , public dir_facade< Traits, dir_t<Traits> >
{
public:
  typedef typename Traits::dir_type dir_type;
  typedef wrapper<dir_type> base_type;

  dir_t(dir_type const &v) 
    : base_type(v) 
  {}

  template<template<class> class Adapter>
  dir_t(Adapter<Traits> const &a)
    : base_type(a)
  {}
};

} // namespace fs
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_FS_DIR_HPP
