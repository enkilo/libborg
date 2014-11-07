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

#ifndef _cxx_abstract_mousehandler_hpp_
#define _cxx_abstract_mousehandler_hpp_

namespace abstract {
 
  //! Mouse button constants.
  enum mousebutton
  {
    button_left = 1,
    button_right = 2,
    button_middle = 4,
  };
  
  //! Keyboard modifier constants.
  enum modifier
  {
    modifier_shift = 1,
    modifier_control = 2,
    modifier_alt = 4
  };
  
  //! Generic interface for handling mouse events.
  class mousehandler
  {
  public:
    virtual void mousedown
      (int x, int y, mousebutton button, int modifiers) = 0;

    virtual void mouseup
      (int x, int y, mousebutton button, int modifiers) = 0;

    virtual void doubleclick
      (int x, int y, mousebutton button, int modifiers) = 0;

    virtual void mousemove
      (int x, int y, int buttons, int modifiers) = 0;
    
    virtual void mousewheel
      (int x, int y, int rotation, int modifiers) = 0;
  };

} // end of namespace abstract
#endif // _cxx_std_rgba_hpp_
