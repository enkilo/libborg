#ifndef BORG_NSPR_TRAITS_HPP
#define BORG_NSPR_TRAITS_HPP

#include <nspr/prio.h>

namespace borg {
namespace nspr {

//----------------------------------------------------------------------------
struct traits
{
  typedef ::PRFileDesc    *socket_type;
  typedef ::PRFileDesc    *file_type;
  typedef ::PRIntn         af_type;
  typedef ::PRStatus       status_type;
  typedef ::PRIntervalTime interval_type;
//  typedef ::PRNetAddr      addr_type;
  typedef ::PRIntn         size_type;
  typedef ::PRInt32        result_type;
  typedef ::PRInt32        flags_type;
  typedef ::PRNetAddr      address_type;
  typedef const char      *string_type;
  typedef char             char_type;
  typedef ::PRUint16       port_type;
  typedef ::PRFileInfo     finfo_type;
  typedef ::PRIOVec        iovec_type;
  typedef ::PRDescType     desc_type;
  typedef ::PRSeekWhence   seek_type;
  typedef ::PRIntn         fileattrs_type;
  typedef ::PRIntn         fileperms_type;
//  typedef ::
};

//---------------------------------------------------------------------------

} // namespace nspr
} // namespace borg

#endif //ndef BORG_NSPR_TRAITS_HPP
