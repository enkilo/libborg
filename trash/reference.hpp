#warning "obsolete"
// Copyright (C) 2007  Roman Senn <r.senn@nexbyte.com>

// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the wrapied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License along
// with this library; see the file COPYING.  If not, write to the Free
// Software Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307,
// USA.

// As a special exception, you may use this file as part of a free software
// library without restriction.  Specifically, if other files instantiate
// templates or use macros or inline functions from this file, or you compile
// this file and link it with other files to produce an executable, this
// file does not by itself cause the resulting executable to be covered by
// the GNU General Public License.  This exception does not however
// invalidate any other reasons why the executable file might be covered by
// the GNU General Public License.

#ifndef _cxx_wrap_reference_hpp_
#define _cxx_wrap_reference_hpp_

// Helper for wrapping arbitrary class into (pure virtual) interface through
// a reference.

namespace wrap {
 
  //! References class refT inside of a _T_interface descendant.
  template<typename refT>
    class reference /*: public virtual base<refT>*/
  {
  private:
    refT &m_referenced;
    
  protected:
    //@{
    //! Implement the base wrapping interface, \see base.hpp.
    const refT &get() const { return m_referenced; }
    refT &get() { return m_referenced; };
    //@}
    
  public:
    // The type we're wrapping:
    typedef refT type;

    reference(refT &__reference) :
      m_referenced(__reference)
    {}
    
    // Empty virtual destructor. We want to track inheritance.
    virtual ~reference()
    {}
    
    // Implicit conversion to m_reference const reference.
    operator const refT &() const
    {
      return m_referenced;
    }    
    
    // Implicit conversion to m_reference reference.
    operator refT &()
    {
      return m_referenced;
    }    
  };
  
} // end of namespace wrap
#endif // _cxx_wrap_reference_hpp_
