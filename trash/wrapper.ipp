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

//----------------------------------------------------------------------------
//! \file wrap/wrapper.ipp
//! \svn  $Revision: $
//!
//! Declares the abstract::wrapper interface.
//----------------------------------------------------------------------------

#ifndef WRAPPER_IPP
#define WRAPPER_IPP

//----------------------------------------------------------------------------
//! Define this macro to add function extents (e.g. virtual F = 0).
//----------------------------------------------------------------------------
#ifndef FN
#define FN(F) F
#endif // FN

//----------------------------------------------------------------------------
//! Define this macro to force (non-)constness on all methods.
//----------------------------------------------------------------------------
#ifndef CONST
#define CONST(C) C
#endif // CONST

//----------------------------------------------------------------------------
//! Define this macro to override the protection scheme.
//----------------------------------------------------------------------------
#ifndef PROT
#define PROT(P) P
#endif // PROT

//----------------------------------------------------------------------------
// Include interface dependencies:
//----------------------------------------------------------------------------
#include <wrap/const_wrapper.ipp>

//----------------------------------------------------------------------------
//! \name wrapper interface:
//----------------------------------------------------------------------------

//@{

PROT( protected ):

//----------------------------------------------------------------------------
//! Get a non-const reference to the wrapped data.
//----------------------------------------------------------------------------
FN(
  wrap_type &
  get()

  CONST() 
);

//@}

//----------------------------------------------------------------------------
// Undefine customisation macros.
//----------------------------------------------------------------------------
//#undef FN
//#undef CONST
//#undef PROT

//----------------------------------------------------------------------------
// Prevent include recursion, but not multiple inclusion.
//----------------------------------------------------------------------------
#undef WRAPPER_IPP
#endif // WRAPPER_IPP
