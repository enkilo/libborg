#ifndef BORG_APR_TYPES_HPP
#define BORG_APR_TYPES_HPP

#include <apr.h>
#include <apr_file_io.h>

namespace borg {
namespace apr {

//---------------------------------------------------------------------------

typedef apr_size_t      size_t;
typedef apr_off_t       off_t;
typedef apr_int32_t     int32_t;
typedef apr_fileperms_t fileperms_t;
typedef apr_fileattrs_t fileattrs_t;
typedef apr_time_t      time_t;
typedef apr_finfo_t     finfo_t;
  //typedef apr_status_t status_t;
typedef void *data_type;

//---------------------------------------------------------------------------
//! \name forward declarations.
//@{
//class allocator;
template<typename ElementT> class array;
class bucket;
class bucket_brigade;
class pool;
//@}

//---------------------------------------------------------------------------
enum
{
  success = APR_SUCCESS,
  eof = APR_EOF,
  enomem = APR_ENOMEM,
};

typedef apr_status_t status_t;

} // namespace apr
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_APR_TYPES_HPP
