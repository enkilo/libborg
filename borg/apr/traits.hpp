#ifndef BORG_APR_TRAITS_HPP
#define BORG_APR_TRAITS_HPP

#include <apr_network_io.h>

namespace borg {
namespace apr {

//----------------------------------------------------------------------------
struct traits
{
  typedef ::apr_socket_t       *socket_type;
  typedef int                   af_type;
  typedef ::apr_status_t        status_type;
  typedef ::apr_interval_time_t interval_type;
  typedef ::apr_size_t          size_type;
  typedef ::apr_int32_t         result_type;
  typedef ::apr_int32_t         flags_type;
  typedef ::apr_sockaddr_t     *address_type;
  typedef const char           *string_type;
  typedef ::apr_port_t          port_type;
  typedef ::apr_pool_t         *pool_type;
  typedef ::apr_file_t         *file_type;
  typedef ::apr_fileperms_t     fileperms_type;
  typedef ::apr_fileattrs_t     fileattrs_type;
  typedef ::apr_finfo_t         finfo_type;
  typedef ::apr_allocator_t    *allocator_type;
  typedef void                 *data_type;
  typedef char                  char_type;
  typedef struct iovec          iovec_type;
};

//---------------------------------------------------------------------------

} // namespace apr
} // namespace borg

#endif //ndef BORG_APR_TRAITS_HPP
