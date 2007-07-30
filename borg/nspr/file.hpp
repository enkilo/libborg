#ifndef BORG_NSPR_FILE_HPP
#define BORG_NSPR_FILE_HPP

#include <nspr/prio.h>

#include <borg/fs/file.hpp>
#include <borg/fs/dir.hpp>
#include <borg/nspr/traits.hpp>
#include <borg/wrap/pointer.hpp>

namespace borg {
namespace fs {

#define BORG_NSPR_FILE_TYPES(Traits) \
   BORG_FS_FILE_TYPES(Traits)
  
//---------------------------------------------------------------------------
  
//---------------------------------------------------------------------------
  
typedef PRSeekWhence seek_where_t;
  
//---------------------------------------------------------------------------
#ifdef APR_MAX_IOVEC_SIZE
static const nspr::traits::size_type max_iovec_size = APR_MAX_IOVEC_SIZE;
#endif
  
//---------------------------------------------------------------------------
template<>
class file_impl< nspr::traits >
{
public:
  BORG_FS_FILE_TYPES( nspr::traits )

  /// open the specified file.
  static status_type
  open(file_type &file, const string_type &fname, const flags_type &flag,
       const fileperms_type &perm)
  {
    if((file = ::PR_Open(fname, flag, perm)))
      return PR_SUCCESS;
    
    std::cout << "open failed!" << std::endl;
    
    return PR_FAILURE;
  }

  /// close the file.
  static status_type
  close(const file_type &file)
  {
    return ::PR_Close(file);
  }
  
  /// delete the specified file.
  static status_type
  remove(const string_type &path)
  {
    return ::PR_Delete(path);
  }
  
  /// rename the specified file.
  static status_type
  rename(const string_type &from_path, const string_type &to_path)
  {
    return ::PR_Rename(from_path, to_path);
  }

  /// copy the specified file.
/*  static status_type
  copy(const string_type &from_path, const string_type &to_path, 
       const fileperms_type &perms, const pool_type &pool)
  {
    return ::apr_file_copy(from_path, to_path, perms, pool);
  }*/

  /// append the specified file to another file.
/*  static status_type
  append(const string_type &from_path, const string_type &to_path, 
         const fileperms_type &perms, const pool_type &pool)
  {
    return ::apr_file_append(from_path, to_path, perms, pool);
  }*/

  /// are we at the end of the file?
  /// returns nspr::eof if we are at the end of file, nspr::success otherwise.
/*  static status_type
  eof(const file_type &file)
  {
    return ::apr_file_eof(file);
  }*/
  
  /// open standard error as an nspr::file.
  static status_type
  open_stderr(file_type &file)
  {
    if((file = PR_GetSpecialFD(PR_StandardError)))
      return PR_SUCCESS;
    
    return PR_FAILURE;
  }
  
  /// open standard output as an nspr::file.
  static status_type
  open_stdout(file_type &file)
  {
    if((file = PR_GetSpecialFD(PR_StandardOutput)))
      return PR_SUCCESS;
    
    return PR_FAILURE;
  }
  
  /// open standard input as an nspr::file.
  static status_type
  open_stdin(file_type &file)
  {
    if((file = PR_GetSpecialFD(PR_StandardInput)))
      return PR_SUCCESS;
    
    return PR_FAILURE;
  }

  /// read data from the file.
  static result_type
  read(const file_type &file, void *buf, const size_type &nbytes)
  {
    return ::PR_Read(file, buf, nbytes);
  }

  /// write data from the file.
  static result_type
  write(const file_type &file, const void *buf, size_type nbytes)
  {
    return ::PR_Write(file, buf, nbytes);
  }

  /// write data from iovec array to the file.
  static result_type
  writev(const file_type &file, const iovec_type *vec,
         const size_type &iov_size, const interval_type &timeout)
  {
    return ::PR_Writev(file, vec, iov_size, timeout);
  }
  
  /// read data from the file, ensuring that the buffer is filled
  /// before returning.
/*  static status_type
  read_full(const file_type &file, void *buf, 
            const size_type &nbytes, size_type &bytes_read)
  {
    return ::apr_file_read_full(file, buf, nbytes, &bytes_read);
  }*/

  /// write data to the file, ensuring that all of the data is
  /// written before returning.
/*  static status_type
  write_full(const file_type &file, const void *buf, const size_type &nbytes, 
             size_type &bytes_written)
  {
    return ::apr_file_write_full(file, buf, nbytes, &bytes_written);
  }*/

  /// write data from iovec array to the file, ensuring that all of the
  /// data is written before returning.
/*#if APR_MAJOR_VERSION > 0
  static status_type
  writev_full(const struct iovec *vec, const size_type &nvec, 
              const size_type &nbytes)
  {
    return ::apr_file_writev_full(file, vec, nvec, nbytes);
  }
#endif*/
  
  /// write a character into the file.
/*  static status_type
  putc(const file_type &file, const char ch)
  {
    return ::apr_file_putc(ch, file);
  }*/

  /// read a character from the file.
/*  static status_type
  getc(const file_type &file, char_type &ch)
  {
    return ::apr_file_getc(&ch, file);
  }*/

  /// put a character back onto the stream.
/*  static status_type
  ungetc(const file_type &file, const char &ch)
  {
    return ::apr_file_ungetc(ch, file);
  }*/
  
  /// read a string from the file.
/*  static status_type
  gets(const file_type &file, char *str, const size_type &len)
  {
    return ::apr_file_gets(str, len, file);
  }*/
  
  /// write the string into the file.
/*  static status_type
  puts(const file_type &file, const char *str)
  {
    return ::apr_file_puts(str, file);
  }*/
  
  /// flush the file's buffer.
/*  static status_type
  flush(const file_type &file)
  {
    return ::apr_file_flush(file);
  }*/
  
  /// formatted print to file
  static int
  printf(const file_type &file, const char *format, ...)
      __attribute__((format(printf,2,3)))
//      __attribute__((dllimport))
//      __attribute__((weak, alias("_apr_file_printf")))
        ;

  /// set the specified file's permission bits.
/*  static status_type
  set_perms(const string_type &fname, const fileperms_type &perms)
  {
    return ::apr_file_perms_set(fname, perms);
  }*/
  
  /// set attributes of the specified file.
/*  static status_type
  set_attrs(const string_type &fname, const fileattrs_type &attributes, 
            const fileattrs_type &attr_mask, const pool_type &pool)
  {
    return ::apr_file_attrs_set(fname, attributes, attr_mask, pool);
  }*/
  
  /// set the mtime of the specified file.
/*  static status_type
  set_mtime(const string_type &fname, time_t mtime, const pool_type &pool)
  {
    return ::apr_file_mtime_set(fname, mtime, pool);
  }*/
  
  /// get the file's stats.
/*  static status_type
  get_info(const file_type &file, finfo_type &finfo, int32_t wanted)
  {
    return ::apr_file_info_get(&finfo, wanted, file);
  }*/

  /// truncate the file
/*  static status_type
  trunc(const file_type &file, off_t offset)
  {
    return ::apr_file_trunc(file, offset);
  }*/
  
  /// get the file's flags.
/*  static flags_type
  get_flags(const file_type &file)
  {
    return ::apr_file_flags_get(file);
  }*/

  /// open a temporary file.
/*  static status_type
  mktemp(file_type &file, char *templ, int32_t flags, const pool_type &p)
  {
    return ::apr_file_mktemp(&file, templ, flags, p);
  }*/
};

//---------------------------------------------------------------------------
template<>
class file< nspr::traits >
   // : public file_impl< nspr::traits >
    : public file_interface< nspr::traits, file< nspr::traits > >
    , public file_facade< nspr::traits, file< nspr::traits > >
{
public:
  BORG_NSPR_FILE_TYPES( nspr::traits )
  
  enum 
  {
    o_rdonly   = PR_RDONLY,
    o_wronly   = PR_WRONLY,
    o_rdwr     = PR_RDWR,
    o_create   = PR_CREATE_FILE,
    o_append   = PR_APPEND,
    o_truncate = PR_TRUNCATE,
    o_sync     = PR_SYNC,
    o_excl     = PR_EXCL
  };

  enum 
  {
    seek_set = PR_SEEK_SET,
    seek_cur = PR_SEEK_CUR,
    seek_end = PR_SEEK_END
  };

  typedef file_impl< nspr::traits > impl;

  file_type m_file;
  file_type &get()
  {
    return m_file; 
  }

  file(const string_type &fname, const flags_type &flag,
       const fileperms_type &perm)
  {
    impl::open(m_file, fname, flag, perm);
  }

  operator file_type() const
  {
    return m_file;
  }
  
private:
  friend class file_impl< nspr::traits >;
  friend class file_interface< nspr::traits, file< nspr::traits > >;
  
  file< nspr::traits > &
  operator=(const file_type &file)
  {
    m_file = file;
    return *this;
  }
};
  
//---------------------------------------------------------------------------
template<>
struct dir_impl< nspr::traits >
{
public:
  BORG_NSPR_FILE_TYPES( nspr::traits )

  /// create a new directory on the file system.
/*  static status_type
  make(const string_type &path, const fileperms_type &perm, 
       const pool_type &pool)
  {
    return ::apr_dir_make(path, perm, pool);
  }*/
  
  /// creates a new directory on the file system, but behaves like
  /// 'mkdir -p'. creates intermediate directories as required. no error
  /// will be reported if PATH already exists.
/*  static status_type
  make_recursive(const string_type &path, const fileperms_type &perm, 
                 const pool_type &pool)
  {
    return ::apr_dir_make_recursive(path, perm, pool);
  }*/
  
  /// remove directory from the file system.
/*  static status_type
  remove(const string_type &path, const pool_type &pool)
  {
    return ::apr_dir_remove(path, pool);
  }*/

  /// find an existing directory suitable as a temporary storage location.
/*  static status_type
  get_temp(string_type &temp_dir, const pool_type &p)
  {
    return ::apr_temp_dir_get(&temp_dir, p);
  }*/
};
  
} // namespace fs
namespace nspr {
    
typedef fs::file_impl<traits> file_a;
typedef fs::file_t<traits> file_t;
typedef fs::file<traits> file;

} // namespace nspr
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_NSPR_FILE_HPP
