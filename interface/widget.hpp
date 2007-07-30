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

#ifndef _cxx_abstract_widget_hpp_
#define _cxx_abstract_widget_hpp_

#include <interface/rectangular.hpp>
#include <interface/showable.hpp>

namespace abstract {

#define widget_INTERFACE(_decl) \
  rectangular_INTERFACE(_decl); \
  showable_INTERFACE(_decl);

/*#define widget_TYPEDEF(vector, color) \
  typedef vector vector_type; \
  typedef std::point<vector_type> point_type; \
  typedef std::size<vector_type> size_type; \
  typedef borg::rect<vector_type> rect_type; \
  \
  typedef color color_type; \
  typedef borg::rgba<color_type> rgba_type; \*/
                       
  
  //! Generic interface for widgets.
  template<bool resizeable = false> 
    class widget : public rectangular<int, resizeable>,
                 public sized<int>,
                 public showable
  {
  };

/*  template<>
    class widget<true> : public rectangular<int, faksemoveable<int>,
                       public resizeable<int>,
                       public showable
  {
  };*/

} // end of namespace abstract
#endif // _cxx_abstract_widget_hpp_
