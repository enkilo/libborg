#ifndef _cxx_abstract_drawer_
#define _cxx_abstract_drawer_

#include <interface/dc.hpp>

namespace abstract {

  template<typename drawableT>
    class drawer
  {
  public:
    virtual ~drawer() {}
    virtual void operator()
      (drawableT &dst, const typename drawableT::rect_type &area) = 0;
  };

} // end of namespace abstract

#endif /* _CXX_Drawer_ */
