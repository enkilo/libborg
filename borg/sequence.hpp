#ifndef BORG_SEQUENCE_HPP
#define BORG_SEQUENCE_HPP

#include <borg/range.hpp>
#include <borg/util/dereference_cast.hpp>

namespace borg {

//---------------------------------------------------------------------------
template<class Sequence, class ConstIterator, class Iterator, class Traits>
struct sequence_impl
{
  typedef Sequence sequence_type;
  typedef Iterator iterator;
  typedef ConstIterator const_iterator;
  
  static ConstIterator
  begin(Sequence const &seq) { return seq.begin(); }
  
  static Iterator
  begin(Sequence       &seq) { return seq.begin(); }

  static ConstIterator
  end  (Sequence const &seq) { return seq.end(); }  

  static Iterator
  end  (Sequence       &seq) { return seq.end(); }
};
  
//---------------------------------------------------------------------------
template<class Derived, class Sequence, class ConstIterator, class Iterator, class Traits>
struct sequence_interface
{
  typedef sequence_interface
  <
      Derived
    , Sequence
    , ConstIterator
    , Iterator
    , Traits
  > this_type;

  typedef sequence_impl<Sequence, ConstIterator, Iterator, Traits> impl;

  typedef Sequence sequence_type;
  typedef ConstIterator const_iterator;
  typedef Iterator iterator;
  
  ConstIterator
  begin() const
  {
    return impl::begin
      (dereference_cast<Derived const>(this));
  }
  
  Iterator
  begin()
  {
    return impl::begin
      (dereference_cast<Derived>(this));
  }
  
  ConstIterator
  end() const
  {
    return impl::end
      (dereference_cast<Derived const>(this));
  } 
  
  Iterator
  end()
  {
    return impl::end
      (dereference_cast<Derived>(this));
  } 
};  

//---------------------------------------------------------------------------

} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_SEQUENCE_HPP
