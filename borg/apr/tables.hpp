#ifndef BORG_APR_TABLES_HPP
#define BORG_APR_TABLES_HPP

#include <apr_tables.h>
#include <borg/apr/types.hpp>
#include <borg/apr/exception.hpp>
#include <borg/wrap/pointer.hpp>

namespace borg {
namespace apr {

//---------------------------------------------------------------------------
template<typename ElementT>
class array : public borg::pointer< ::apr_array_header_t >
{
public:
  typedef ElementT elt_type;
  static const size_t elt_size = sizeof(elt_type);
  typedef borg::pointer< ::apr_array_header_t > base_type;
  typedef array<ElementT> this_type;
  
  /// create an array.
  array(pool_t &p, int nelts)
    : base_type(::apr_array_make(p, nelts, elt_size))
  {}
  
  /// determine if the array is empty.
  bool
  empty() const
  {
    return ::apr_is_empty_array(*this);
  }

  /// add a new element to an array (as a first-in, last-out stack).
  elt_type *
  push() const
  {
    return static_cast<elt_type *>(::apr_array_push(*this));
  }

  /// remove an element from an array (as a first-in, last-out stack).
  elt_type *
  pop() const
  {    
    return static_cast<elt_type *>(::apr_array_pop(*this));
  }

  /// concatenate two arrays together.
  void
  cat(const this_type &src) const
  {
    ::apr_array_cat(*this, src);
  }

  /// copy the entire array.
  this_type
  copy(pool_t &p) const
  {
    return ::apr_array_copy(p, *this);
  }

  /// copy the headers of the array, and arrange for the elements to be copied 
  /// if and only if the code subsequently does a push or arraycat.
  this_type
  copy_hdr(pool_t &p) const
  {
    return ::apr_array_copy(p, *this);
  }

  /// append one array to the end of this, creating a new array in the process.
  this_type
  append(pool_t &p, const this_type &a) const
  {
    return ::apr_array_append(p, *this, a);
  }

  /// generates a new string from the apr_pool_t containing the concatenated 
  /// sequence of substrings referenced as elements within the array. the string
  /// will be empty if all substrings are empty or null, or if there are no 
  /// elements in the array. if sep is non-NUL, it will be inserted between 
  /// elements as a separator.
  char *
  pstrcat(pool_t &p, const this_type &arr, const char sep = '\0') const
  {
    return ::apr_array_pstrcat(p, arr, sep);
  }
  
protected:
  
  /// construct from existing array.
  array(init_type a) : base_type(a) {}

  friend class table;
};
  
//---------------------------------------------------------------------------
class table : public borg::pointer< ::apr_table_t >
{
public:
  typedef borg::pointer< ::apr_table_t > base_type;
  typedef table this_type;
  typedef const char *elt_type;
  typedef const char *key_type;
  
  /// make a new table.
  table(pool_t &p, int nelts)
    : base_type(::apr_table_make(p, nelts))
  {}
  
  /// get the elements from a table.
  array<elt_type>
  elts() const
  {
    return const_cast< ::apr_array_header_t * >(::apr_table_elts(*this));
  }
  
  /// determine if the table is empty.
  bool
  empty() const
  {
    return ::apr_is_empty_table(*this);
  }

  /// create a new table and copy this table into it.
  this_type
  copy(pool_t &p) const
  {
    return ::apr_table_copy(p, *this);
  }
  
  /// delete all of the elements from a table.
  void
  clear() const
  {
    ::apr_table_clear(*this);
  }
  
  /// get the value associated with a given key from the table. 
  /// after this call, the data is still in the table.
  elt_type
  get(key_type key) const
  {
    return ::apr_table_get(*this, key);
  }
  
  /// add a key/value pair to a table, if another element already exists
  /// with the same key, this will over-write the old data.
  void
  set(key_type key, elt_type val) const
  {
    ::apr_table_set(*this, key, val);
  }
  
  /// same as set(), but won't make a copy of the key and the value.
  void
  setn(key_type key, elt_type val) const
  {
    ::apr_table_setn(*this, key, val);
  }
  
  /// remove data from the table.
  void
  unset(key_type key) const
  {
    ::apr_table_unset(*this, key);
  }
  
protected:
  
  /// construct from existing table.
  table(init_type a) : base_type(a) {}

};
  
} // namespace apr
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_APR_TABLES_HPP
