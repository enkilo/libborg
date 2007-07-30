#ifndef BORG_APR_FILE_IO_HPP
#define BORG_APR_FILE_IO_HPP

#include <apr_file_io.h>

#include <borg/fs/file.hpp>
#include <borg/fs/dir.hpp>
#include <borg/apr/types.hpp>
#include <borg/apr/traits.hpp>
#include <borg/apr/pools.hpp>
#include <borg/apr/exception.hpp>
#include <borg/wrap/pointer.hpp>

namespace borg {
namespace fs {

#define BORG_APR_FILE_TYPES(Traits) \
   BORG_FS_FILE_TYPES(Traits) \
   typedef Traits::pool_type pool_type;
  
//---------------------------------------------------------------------------
#ifdef APR_MAX_IOVEC_SIZE
static const apr::traits::size_type max_iovec_size = APR_MAX_IOVEC_SIZE;
#endif
  
//---------------------------------------------------------------------------
//typedef file const file_t;
  
//---------------------------------------------------------------------------
struct flock {
  enum {
    /// shared lock. more than one process or thread can hold a shared lock
    /// at any given time. essentially this is a "read lock", preventing 
    /// writes from establishing an exclusive lock.
    shared = APR_FLOCK_SHARED,   

    /// exclusive lock. only one process may hold an exclusive lock at any
    /// given time. this is analogous to a "write lock".
    exclusive = APR_FLOCK_EXCLUSIVE,

    /// mask to extract lock type.
    typemask = APR_FLOCK_TYPEMASK,
      
    /// do not block while acquiring the file lock.
    nonblock = APR_FLOCK_NONBLOCK,
  };
};
  
//---------------------------------------------------------------------------
template<>
class file_impl< apr::traits >
{
public:
  BORG_APR_FILE_TYPES( apr::traits )
  
  enum {
#if APR_MAJOR_VERSION == 0
    o_read     = APR_READ,      ///< open the file for reading.
    o_write    = APR_WRITE,     ///< open the file for writing.
    o_create   = APR_CREATE,    ///< create the file if not there.
    o_append   = APR_APPEND,    ///< append to the end of the file.
    o_truncate = APR_TRUNCATE,  ///< open the file and truncate to 0 length.
    o_binary   = APR_BINARY,    ///< open the file in binary mode.
    o_excl     = APR_EXCL,      ///< open should fail if fopen::create and file exists.
    o_buffered = APR_BUFFERED,  ///< open the file for buffered i/o.
#else    
    o_read     = APR_FOPEN_READ,      ///< open the file for reading.
    o_write    = APR_FOPEN_WRITE,     ///< open the file for writing.
    o_create   = APR_FOPEN_CREATE,    ///< create the file if not there.
    o_append   = APR_FOPEN_APPEND,    ///< append to the end of the file.
    o_truncate = APR_FOPEN_TRUNCATE,  ///< open the file and truncate to 0 length.
    o_binary   = APR_FOPEN_BINARY,    ///< open the file in binary mode.
    o_excl     = APR_FOPEN_EXCL,      ///< open should fail if fopen::create and file exists.
    o_buffered = APR_FOPEN_BUFFERED,  ///< open the file for buffered i/o.
#endif
  };
  
  enum 
  {
    seek_set = APR_SET, ///< set the file position
    seek_cur = APR_CUR, ///< current
    seek_end = APR_END  ///< go to the end of file
  };

  /// file attribute flags
  struct attr {
    enum {
      readonly   = APR_FILE_ATTR_READONLY,   ///< file is read-only.
      executable = APR_FILE_ATTR_EXECUTABLE, ///< file is executable.
      hidden     = APR_FILE_ATTR_HIDDEN,     ///< file is hidden.
    };
  };
  
  /// open the specified file.
  static status_type
  open(file_type &file, const string_type &fname, const flags_type &flag,
       const fileperms_type &perm, const pool_type &pool)
  {
    return ::apr_file_open(&file, fname, flag, perm, pool);
  }

  /// close the file.
  static status_type
  close(const file_type &file)
  {
    return ::apr_file_close(file);
  }
  
  /// delete the specified file.
  static status_type
  remove(const string_type &path, const pool_type &pool)
  {
    return ::apr_file_remove(path, pool);
  }
  
  /// rename the specified file.
  static status_type
  rename(const string_type &from_path, const string_type &to_path, 
         const pool_type &pool)
  {
    return ::apr_file_rename(from_path, to_path, pool);
  }

  /// copy the specified file.
  static status_type
  copy(const string_type &from_path, const string_type &to_path, 
       const fileperms_type &perms, const pool_type &pool)
  {
    return ::apr_file_copy(from_path, to_path, perms, pool);
  }

  /// append the specified file to another file.
  static status_type
  append(const string_type &from_path, const string_type &to_path, 
         const fileperms_type &perms, const pool_type &pool)
  {
    return ::apr_file_append(from_path, to_path, perms, pool);
  }

  /// are we at the end of the file?
  /// returns apr::eof if we are at the end of file, apr::success otherwise.
  static status_type
  eof(const file_type &file)
  {
    return ::apr_file_eof(file);
  }
  
  /// open standard error as an apr::file.
  static status_type
  open_stderr(file_type &file, const pool_type &pool)
  {
    return ::apr_file_open_stderr(&file, pool);
  }
  
  /// open standard output as an apr::file.
  static status_type
  open_stdout(file_type &file, const pool_type &pool)
  {
    return ::apr_file_open_stdout(&file, pool);
  }
  
  /// open standard input as an apr::file.
  static status_type
  open_stdin(file_type &file, const pool_type &pool)
  {
    return ::apr_file_open_stdin(&file, pool);
  }

  /// read data from the file.
  static status_type
  read(const file_type &file, void *buf, size_type &nbytes)
  {
    return ::apr_file_read(file, buf, &nbytes);
  }

  /// write data from the file.
  static status_type
  write(const file_type &file, const void *buf, size_type nbytes)
  {
    size_type n = nbytes;
    status_type r;
    
    if((r = ::apr_file_write(file, buf, &n)) == 0)
      return n;
    
    return r;
  }

  /// write data from iovec array to the file.
  static status_type
  writev(const file_type &file, const struct iovec *vec,
         const size_type &nvec, size_type &nbytes)
  {
    return ::apr_file_writev(file, vec, nvec, &nbytes);
  }
  
  /// read data from the file, ensuring that the buffer is filled
  /// before returning.
  static status_type
  read_full(const file_type &file, void *buf, 
            const size_type &nbytes, size_type &bytes_read)
  {
    return ::apr_file_read_full(file, buf, nbytes, &bytes_read);
  }

  /// write data to the file, ensuring that all of the data is
  /// written before returning.
  static status_type
  write_full(const file_type &file, const void *buf, const size_type &nbytes, 
             size_type &bytes_written)
  {
    return ::apr_file_write_full(file, buf, nbytes, &bytes_written);
  }

  /// write data from iovec array to the file, ensuring that all of the
  /// data is written before returning.
#if APR_MAJOR_VERSION > 0
  static status_type
  writev_full(const struct iovec *vec, const size_type &nvec, 
              const size_type &nbytes)
  {
    return ::apr_file_writev_full(file, vec, nvec, nbytes);
  }
#endif
  
  /// write a character into the file.
  static status_type
  putc(const file_type &file, const char ch)
  {
    return ::apr_file_putc(ch, file);
  }

  /// read a character from the file.
  static status_type
  getc(const file_type &file, char_type &ch)
  {
    return ::apr_file_getc(&ch, file);
  }

  /// put a character back onto the stream.
  static status_type
  ungetc(const file_type &file, const char &ch)
  {
    return ::apr_file_ungetc(ch, file);
  }
  
  /// read a string from the file.
  static status_type
  gets(const file_type &file, char *str, const size_type &len)
  {
    return ::apr_file_gets(str, len, file);
  }
  
  /// write the string into the file.
  static status_type
  puts(const file_type &file, const char *str)
  {
    return ::apr_file_puts(str, file);
  }
  
  /// flush the file's buffer.
  static status_type
  flush(const file_type &file)
  {
    return ::apr_file_flush(file);
  }
  
  /// formatted print to file
  static int
  printf(const file_type &file, const char *format, ...)
      __attribute__((format(printf,2,3)))
//      __attribute__((dllimport))
//      __attribute__((weak, alias("_apr_file_printf")))
        ;

  /// set the specified file's permission bits.
  static status_type
  set_perms(const string_type &fname, const fileperms_type &perms)
  {
    return ::apr_file_perms_set(fname, perms);
  }
  
  /// set attributes of the specified file.
  static status_type
  set_attrs(const string_type &fname, const fileattrs_type &attributes, 
            const fileattrs_type &attr_mask, const pool_type &pool)
  {
    return ::apr_file_attrs_set(fname, attributes, attr_mask, pool);
  }
  
  /// set the mtime of the specified file.
  static status_type
  set_mtime(const string_type &fname, time_t mtime, const pool_type &pool)
  {
    return ::apr_file_mtime_set(fname, mtime, pool);
  }
  
  /// get the file's stats.
  static status_type
  get_info(const file_type &file, finfo_type &finfo, int32_t wanted)
  {
    return ::apr_file_info_get(&finfo, wanted, file);
  }

  /// truncate the file
  static status_type
  trunc(const file_type &file, off_t offset)
  {
    return ::apr_file_trunc(file, offset);
  }
  
  /// get the file's flags.
  static flags_type
  get_flags(const file_type &file)
  {
    return ::apr_file_flags_get(file);
  }

  /// open a temporary file.
  static status_type
  mktemp(file_type &file, char *templ, int32_t flags, const pool_type &p)
  {
    return ::apr_file_mktemp(&file, templ, flags, p);
  }
};

//---------------------------------------------------------------------------
template<>
class file< apr::traits >
    : public file_interface< apr::traits, file< apr::traits > >
    , public file_facade< apr::traits, file< apr::traits > >
{
public:
  BORG_APR_FILE_TYPES( apr::traits )

  typedef file_impl< apr::traits > impl;
  
  enum
  {
    o_rdonly   = APR_FOPEN_READ,
    o_wronly   = APR_FOPEN_WRITE,
    o_rdwr     = APR_FOPEN_READ|APR_FOPEN_WRITE,
    o_create   = APR_FOPEN_CREATE,
    o_truncate = APR_FOPEN_TRUNCATE,
  };

  file_type m_file;
  file_type &get()
  {
    return m_file; 
  }

/*  file(const string_type &fname, const flags_type &flag,
       const fileperms_type &perm)
  {
    impl::open(m_file, fname, flag, perm);
  }*/

  file(const string_type &fname, const flags_type &flag,
       const fileperms_type &perm, const pool_type &pool = apr::pool::shared())
  {
    impl::open(m_file, fname, flag, perm, pool);
  }

  operator file_type() const
  {
    return m_file;
  }
  
private:
  friend class file_impl< apr::traits >;
  friend class file_interface< apr::traits, file< apr::traits > >;
  
  file< apr::traits > &
  operator=(const file_type &file)
  {
    m_file = file;
    return *this;
  }
};
  
//---------------------------------------------------------------------------
template<>
struct dir_impl< apr::traits >
{
public:
  BORG_APR_FILE_TYPES( apr::traits )

  /// create a new directory on the file system.
  static status_type
  make(const string_type &path, const fileperms_type &perm, 
       const pool_type &pool)
  {
    return ::apr_dir_make(path, perm, pool);
  }
  
  /// creates a new directory on the file system, but behaves like
  /// 'mkdir -p'. creates intermediate directories as required. no error
  /// will be reported if PATH already exists.
  static status_type
  make_recursive(const string_type &path, const fileperms_type &perm, 
                 const pool_type &pool)
  {
    return ::apr_dir_make_recursive(path, perm, pool);
  }
  
  /// remove directory from the file system.
  static status_type
  remove(const string_type &path, const pool_type &pool)
  {
    return ::apr_dir_remove(path, pool);
  }

  /// find an existing directory suitable as a temporary storage location.
  static status_type
  get_temp(string_type &temp_dir, const pool_type &p)
  {
    return ::apr_temp_dir_get(&temp_dir, p);
  }
};
  
} // namespace fs
namespace apr {
    
typedef fs::file_impl<traits> file_a;
typedef fs::file_t<traits> file_t;
typedef fs::file<traits> file;

} // namespace apr
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_APR_FILE_IO_HPP
