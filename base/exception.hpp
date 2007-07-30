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

#ifndef _base_exception_hpp_
#define _base_exception_hpp_

#include <exception>
#include <sstream>
#include <ostream>

namespace base {
 
  //! Generic interface for exception artefacts.
  class exception : public std::exception
  {
  protected:
    std::ostringstream m_what;
    
  public:
    exception() : std::exception() {}
    virtual ~exception() throw() {}
    
    virtual const char *what() const throw()
    { return m_what.str().c_str(); }
    
    template<typename _Tp>
      exception &operator<<(const _Tp &arg)
    {
      m_what << arg;
      return *this;
    }
  };

} // end of namespace abstract
#endif // _base_exception_hpp_