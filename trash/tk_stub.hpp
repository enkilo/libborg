#warning "obsolete"
#ifndef TK_STUB_HPP
#define TK_STUB_HPP

namespace tk {

#define TK_STUB(type, name) \
  template<class toolkit, \
           class ty##pe = typename toolkit::type##_type, \
           class traits = type##_traits<toolkit, ty##pe> > class name;

} // end of namespace tk
#endif //ndef TK_STUB_HPP
