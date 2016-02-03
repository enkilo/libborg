#warning "obsolete"
// 

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

#ifndef _cxx_wrap_rectangular_hpp_
#define _cxx_wrap_rectangular_hpp_

#include <types/size_type.hpp>

namespace wrap {
 
  //! Generic interface for rectangular artefacts.
  template<_T_vec>
    class rectangular : virtual public object
  {
  public:
    // This one has to be implemented in descendants.
    void
    size(_T_vec &__w, _T_vec &__h) const = 0;
    
    // Alternate implementation: return size as a std::size.
    std::size<_T_vec>
    size() const;

    // Alternate implementation: write size to pointer locations
    // if the corresponding pointer is non-zero.
    void
    size(_T_vec *__pw, _T_vec *__ph) const;

    // This one has to be implemented in descendants:
    // Move the sizeable objects to the absolute size x,y.
    void
    move(const _T_vec &__w, const _T_vec &__h) = 0;
    
    // Alternate form:
    // Move the sizeable objects by the relative offsets x,y.
    void
    offset(const _T_vec &__w, const _T_vec &__h);
  };

  template<_T_vec>
    inline std::point<_T_vec> 
    rectangular<_T_vec>::get_size()
  {
    std::point<_T_vec> ret;
    get_size(ret.x(), ret.y());
    return ret;
  }

  template<_T_vec>
    inline void
    rectangular<_T_vec>::get_size(_T_vec *__pw, _T_vec *__ph)
  {
    std::point<_T_vec> ret = get_size();
    if(__pw) *__pw = ret.x();
    if(__ph) *__ph = ret.y();
  }
  
  template<_T_vec>
    inline void
    rectangular<_T_vec>::offset(const _T_vec &__w, const _T_vec &__h)
  {
    T_vec x, y;
    get_size(x, y);
    move(x + __w, y + __h);    
  }

} // end of namespace wrap
#endif // _cxx_wrap_rectangular_hpp_
