#ifndef BORG_WX_APPLICATION_HPP
#define BORG_WX_APPLICATION_HPP

#include <borg/wx/traits.hpp>
#include <borg/tk/application.hpp>

namespace borg {
namespace tk {

//----------------------------------------------------------------------------
template<>
struct application_impl< wx::traits >
{
};

//----------------------------------------------------------------------------

}// namespace tk
namespace wx {
  
typedef tk::application<traits> application;
  
}// namespace wx
}// namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_WX_APPLICATION_HPP
