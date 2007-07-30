#ifndef _cxx_interface_rectangular_hpp_
#define _cxx_interface_rectangular_hpp_

#include <interface/moveable.hpp>
#include <interface/resizeable.hpp>
#include <types/rect_type.hpp>
#include <boost/mpl/if.hpp>
//#include <boost/mpl/empty_base.hpp>

namespace abstract {
 
#define rectangular_PROTOTYPE_rect(_name) void _name(rect_type &rt) const
  
//! Interface to resizeable objects.
#define rectangular_INTERFACE(_decl) \
  moveable_INTERFACE(_decl); \
  resizeable_INTERFACE(_decl); \
  _decl(rectangular, rect); 

  //! Generic interface for rectangular artefacts.
  template<typename vectorT, bool resize = true>
    class rectangular : public moveable<vectorT>,
                        public boost::mpl::if_c<resize, abstract::resizeable<vectorT>, abstract::sized<vectorT> >::type
  {
  public:
    typedef abstract::moveable<vectorT> moveable_type;
    typedef abstract::resizeable<vectorT> resizeable_type;
    typedef borg::rect<vectorT> rect_type;
    typedef abstract::positioned<vectorT> positioned_type;
//    typedef boost::mpl::if_c<resize, abstract::resizeable<vectorT>, abstract::sized<vectorT> >::type sized_type;
    
    // Alternate implementation: return size as a std::size.
    virtual void rect(rect_type &rt) const;
  };

  template<typename vectorT, bool resize>
    inline void
    rectangular<vectorT, resize>::rect(rect_type &rt) const
  {
    positioned_type::pos(rt);
    boost::mpl::if_c<resize, abstract::resizeable<vectorT>, abstract::sized<vectorT> >::type::size(rt);
  }
  
} // end of namespace abstract
#endif // _cxx_interface_rectangular_hpp_
