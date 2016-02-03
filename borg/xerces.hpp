#ifndef BORG_XERCES_HPP
#define BORG_XERCES_HPP

#include <borg/xerces/traits.hpp>
#include <borg/xerces/adapters.hpp>
#include <borg/xerces/http_input_stream.hpp>
#include <borg/xerces/allocator.hpp>

namespace borg {
namespace xerces {

//----------------------------------------------------------------------------
inline static
void initialize()
{
  using namespace ::XERCES_CPP_NAMESPACE;

  XMLPlatformUtils::Initialize();
}
  
//---------------------------------------------------------------------------
inline static
void shutdown()
{
  using namespace ::XERCES_CPP_NAMESPACE;
  
  XMLPlatformUtils::Terminate();
}

//---------------------------------------------------------------------------

} // namespace xerces
} // namespace borg

#endif //ndef BORG_XERCES_HPP
