#ifndef BORG_APR_BUCKETS_HPP
#define BORG_APR_BUCKETS_HPP

#include <apr_buckets.h>
#include <borg/apr/types.hpp>
#include <borg/apr/traits.hpp>
#include <borg/apr/pools.hpp>
#include <borg/wrap/pointer.hpp>
#include <borg/wrap/integer_facade.hpp>

namespace borg {
namespace apr {

//---------------------------------------------------------------------------
enum 
{
  block_read,    ///< block until data becomes available
  nonblock_read  ///< return immediately if no data is available
};

typedef ::apr_read_type_e read_type;
  
typedef void free_func_t(void *data);
  
class bucket_brigade;
class bucket_alloc_t;

//! basic bucket type.
class bucket_type : public borg::pointer< ::apr_bucket_type_t >
{
public:
  /// default bucket buffer size:
  /// 8kb minus room for memory allocator headers
  static const size_t buffer_size = 8000;

};  

//! bucket structures are allocated on the heap and their
//! lifetime is controlled by the parent bucket_brigade
//! object. buckets can move from one brigade to another
//! e.g. by calling brigade::concat(bucket). in general
//! the data in a bucket has the same lifetime as the 
//! bucket and is deleted when the bucket is destroyed;
//! if the data is shared by  more than one bucket (e.g.
//! after a split) the data is deleted when the last bucket
//! goes away.
class bucket : public borg::pointer< ::apr_bucket >
{
public:
  typedef apr::traits::data_type data_type;
  typedef borg::pointer< ::apr_bucket > base_type;
  typedef bucket this_type;
  
  bucket(init_type b) : base_type(b) {}
//  bucket(bucket_alloc_t &a) : base_type() {}

  /// get the length of the data.
  const size_t &
  length() const 
  { 
    return (*this)->length; 
  }

  /// adjust the length of the data.
  void
  set_length(size_t n) const
  { 
    (*this)->length = n; 
  }

  /// get a pointer to the bucket-type specific data.
  data_type
  data() const 
  { 
    return (*this)->data; 
  }

  /// set the pointer to the bucket-type specific data.
  void
  set_data(data_type d) const
  { 
    (*this)->data = d; 
  }

  /// get the next bucket in the list.
  this_type 
  next() const
  {
    return APR_BUCKET_NEXT(*this);
  }
  
  /// remove the bucket from its bucket brigade.
  void
  remove() const
  {
    APR_BUCKET_REMOVE(*this);
  }
  
  /// initialize a new bucket's prev/next pointers.
  void
  init() const
  {
    APR_BUCKET_INIT(*this);
  }
  
  /// determine if a bucket contains metadata. an empty
  /// bucket is safe to arbitrarily remove if and only
  /// if this is false.
  bool
  is_metadata() const
  {
    return APR_BUCKET_IS_METADATA(*this);
  }
  
  /// determine if a bucket is a FLUSH bucket.
  bool
  is_flush() const
  {
    return APR_BUCKET_IS_FLUSH(*this);
  }
  
  /// determine if a bucket is an EOS bucket.
  bool
  is_eos() const
  {
    return APR_BUCKET_IS_FLUSH(*this);
  }
  
  /// determine if a bucket is a FILE bucket.
  bool
  is_file() const
  {
    return APR_BUCKET_IS_FILE(*this);
  }
  
  /// determine if a bucket is a PIPE bucket.
  bool
  is_pipe() const
  {
    return APR_BUCKET_IS_PIPE(*this);
  }
  
  /// determine if a bucket is a SOCKET bucket.
  bool
  is_socket() const
  {
    return APR_BUCKET_IS_SOCKET(*this);
  }
  
  /// determine if a bucket is a HEAP bucket.
  bool
  is_heap() const
  {
    return APR_BUCKET_IS_HEAP(*this);
  }
  
  /// determine if a bucket is a TRANSIENT bucket.
  bool
  is_transient() const
  {
    return APR_BUCKET_IS_TRANSIENT(*this);
  }
  
  /// determine if a bucket is an IMMORTAL bucket.
  bool
  is_immortal() const
  {
    return APR_BUCKET_IS_IMMORTAL(*this);
  }
  
#if APR_HAS_MMAP

  /// determine if a bucket is an MMAP bucket.
  bool
  is_mmap() const
  {
    return APR_BUCKET_IS_MMAP(*this);
  }
#endif

  /// determine if a bucket is a POOL bucket.
  bool
  is_pool() const
  {
    return APR_BUCKET_IS_POOL(*this);
  }

  /// read data from the bucket
  status_t
  read(const char **str, size_t *len, read_type block) const
  {
    return apr_bucket_read(*this, str, len, block);
  }
  
  /// setaside data so that stack data is not destroyed on returning from
  /// the function
  status_t
  setaside(pool_t &pool) const
  {    
    return apr_bucket_setaside(*this, pool);
  }
  
  /// split one bucket in two.
  status_t
  split(off_t point) const
  {    
    return apr_bucket_split(*this, point);
  }
  
};

//! bucket allocator
class bucket_alloc_t : public borg::pointer<apr_bucket_alloc_t>
{
public:
  typedef borg::pointer<apr_bucket_alloc_t> base_type;
  
  /// create a bucket allocator
  explicit
  bucket_alloc_t(pool_t &p)
  {
    base_type::set(apr_bucket_alloc_create(p));
  }
  
  /// create a bucket allocator
  explicit
  bucket_alloc_t(allocator<char> const &a = allocator<char>::singleton())
  {
    base_type::set(apr_bucket_alloc_create_ex(a));
  }

  /// destroy the bucket allocator
  ~bucket_alloc_t()
  {
    ::apr_bucket_alloc_destroy(*this);
  }
  
  /// allocate memory for use by the buckets
  void *
  alloc(size_t size) const
  {
    return ::apr_bucket_alloc(size, *this);
  }
  
  /// free memory previously allocated with alloc().
  static void
  free(void *block)
  {
    ::apr_bucket_free(block);
  }
};  
  
//! end of stream bucket
class eos_bucket : public bucket
{
public:
  explicit
  eos_bucket(const bucket_alloc_t &a)
    : bucket(::apr_bucket_eos_create(a))
  {}

  eos_bucket(const bucket &b)
    : bucket(::apr_bucket_eos_make(b))
  {}
};  
  
//! flush bucket
class flush_bucket : public bucket
{
public:
  explicit
  flush_bucket(const bucket_alloc_t &a)
    : bucket(::apr_bucket_flush_create(a))
  {}

  flush_bucket(const bucket &b)
    : bucket(::apr_bucket_flush_make(b))
  {}
};  
  
//! bucket reference counter
struct bucket_refcount 
  : public ::apr_bucket_refcount
  , public borg::integer_facade<bucket_refcount, int >
{
  typedef ::apr_bucket_refcount base_type;

  int const &
  get() const { return base_type::refcount; }
    
  void
  set(int i) { base_type::refcount = i; }
};

//! bucket heap
class bucket_heap : public borg::pointer<apr_bucket_heap>
{
public:
  const bucket_refcount &
  refcount() const { return *reinterpret_cast<const bucket_refcount *>(&(*this)->refcount); }
    
  bucket_refcount &
  refcount() { return *reinterpret_cast<bucket_refcount *>(&(*this)->refcount); }
    
  /// how much memory was allocated.
  size_t
  alloc_len() const { return (*this)->alloc_len; }

  /// function to use to delete the data.
  free_func_t *
  free_func() const { return (*this)->free_func; }
  
  /// gets the start of the data actually allocated.
  char *
  base() const { return (*this)->base; }
    
};
  
//---------------------------------------------------------------------------
typedef bucket const bucket_t;  
typedef bucket_brigade const bucket_brigade_t;

//! bucket brigade
class bucket_brigade : public borg::pointer< ::apr_bucket_brigade >
{
public:
  typedef borg::pointer< ::apr_bucket_brigade > base_type;
  
  bucket_brigade(init_type br) : base_type(br) {}
  
  /// determine if the bucket brigade is empty.
  bool
  empty() const { return APR_BRIGADE_EMPTY(*this); }
  
  /// return the first bucket in a brigade.
/*  const bucket &
  first() const 
  {
    ::apr_bucket **b = &APR_BRIGADE_FIRST(*this);
    return *reinterpret_cast<const bucket *>(b);
  }*/
  
  bucket &
  first() const
  {
    ::apr_bucket **e = &APR_BRIGADE_FIRST(*this);
    return *reinterpret_cast<bucket *>(e);
  }
  
  /// return the last bucket in a brigade.
/*  const bucket &
  last() const 
  {
    ::apr_bucket **b = &APR_BRIGADE_LAST(*this);
    return *reinterpret_cast<const bucket *>(b);
  }*/
  
  bucket &
  last() const
  {
    ::apr_bucket **e = &APR_BRIGADE_LAST(*this);
    return *reinterpret_cast<bucket *>(e);
  }
  
  /// insert a list of buckets at the front of the brigade.
  void
  insert_head(bucket_t &e) const
  {
    APR_BRIGADE_INSERT_HEAD(*this, e);
  }
  
  /// insert a list of buckets at the end of the brigade.
  void
  insert_tail(bucket_t &e) const
  {
    APR_BRIGADE_INSERT_TAIL(*this, e);
  }
  
  /// concatenate specified brigade \a b onto the end
  /// of the brigade, leaving brigade \a b empty.
  void
  concat(bucket_brigade_t &b) const
  {
    APR_BRIGADE_CONCAT(*this, b);
  }
  
  /// prepend brigade \a b onto the beginning of the brigade,
  /// leaving brigade \a b empty.
  void
  prepend(bucket_brigade_t &b) const
  {
    APR_BRIGADE_PREPEND(*this, b);
  }
  
protected:
  
  const pool_t &
  pool() const { return *reinterpret_cast<const pool_t *>((*this)->p); }
  
  void
  set_pool(const pool_t &p) { (*this)->p = p; }
};
  
//! function called when a brigade should be flushed
typedef status_t brigade_flush_t(bucket_brigade bb, void *ctx);
  
} // namespace apr
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef APR_BUCKETS_HPP
