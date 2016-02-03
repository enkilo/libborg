#warning "obsolete"
//----------------------------------------------------------------------------
//! \file  test_wrap_as_member.cpp
//! \brief Tests the wrap::wrap_as_member class.
//! \svn   $Id: wrapper.hpp 4 2007-03-14 00:48:00Z nexbyte $
//----------------------------------------------------------------------------

#include <boost/test/unit_test.hpp>
#include <boost/static_assert.hpp>
#include <wrap/wrap_as_member.hpp>
#include <wrap/tests/test_wrap_as_member.hpp>

using namespace wrap;
using namespace boost;

namespace
{
  struct bigger_than_word
  {
    double a;
    double b;
  };
  
  class not_copy_constructible
  {
    not_copy_constructible(const not_copy_constructible &) {}
    
  public:
    not_copy_constructible() {}
  };
  
  class some_object
  {
    bigger_than_word m;
    
  public:
    some_object(double a, double b)
    {
      m.a = a;
      m.b = b;
    }
    
    double sum() const
    {
      return m.a + m.b;
    }
  };
}

void *test_simple_wrap_as_member()
{
  static int a = 666;
  wrap_as_member<int &> wa(a);
  return &wa.get();
}

void test_wrap_as_member()
{
  bigger_than_word s1 = { 0.0, 0.0 };
//  bigger_than_word s2 = { 1.0, -1.0 };
  
  test_nonmutable_wrap_as_member<const int>(0);
  test_nonmutable_wrap_as_member<int const>(0);
  test_nonmutable_wrap_as_member<int &>(0);
  test_nonmutable_wrap_as_member<const bigger_than_word>(s1);

  test_mutable_wrap_as_member<int>(0, -1);
  test_mutable_wrap_as_member<int *>(0, (int *)-1);
  test_mutable_wrap_as_member<const int *>(0, (const int *)-1);

  test_mutable_wrap_as_member<double>(0, -1);
  test_mutable_wrap_as_member<double *>(0, (double *)-1);
  test_mutable_wrap_as_member<const double *>(0, (const double *)-1);
  
  test_simple_wrap_as_member();
  
  // Check wrapping an object.
  some_object obj1(4.0, -5.0);
  some_object obj2(-4.0, 5.0);
  
  // Wrap as <const some_object *>
  wrap_as_member<const some_object *> wptr_constobj(&obj1);
  BOOST_CHECK(wptr_constobj.is_mutable);
  const some_object *ptr_constobj = wptr_constobj.set(&obj2).get();
  BOOST_CHECK_EQUAL(ptr_constobj->sum(), 1.0);
  
  // Wrap as <some_object *>
  wrap_as_member<some_object *> wptr_obj(&obj1);
  BOOST_CHECK(wptr_obj.is_mutable);
  some_object *ptr_obj = wptr_obj.set(&obj2).get();
  BOOST_CHECK_EQUAL(ptr_obj->sum(), 1.0);
  
  // Wrap as <some_object *const>
  wrap_as_member<some_object *const> wconstptr_obj(&obj1);
  BOOST_CHECK(!wconstptr_obj.is_mutable);
  some_object *const constptr_obj = wconstptr_obj.get();
  BOOST_CHECK_EQUAL(constptr_obj->sum(), -1.0);
  
  // Wrap as <const some_object &>
  wrap_as_member<const some_object &> wref_constobj(obj1);
  BOOST_CHECK(!wref_constobj.is_mutable);
  const some_object &ref_constobj = wref_constobj.get();
  BOOST_CHECK_EQUAL(ref_constobj.sum(), -1.0);
  
  // Wrap as <some_object &>
  wrap_as_member<some_object &> wref_obj(obj1);
  BOOST_CHECK(!wref_obj.is_mutable);
  some_object &ref_obj = wref_obj.get();    
  BOOST_CHECK_EQUAL(ref_obj.sum(), -1.0);
  
  // Copy constructible?
  wrap_as_member<some_object &> wref2_obj(wref_obj);
  BOOST_CHECK(!wref2_obj.is_mutable);
  some_object &ref2_obj = wref2_obj.get();    
  BOOST_CHECK_EQUAL(ref2_obj.sum(), -1.0);
  
  // Copy constructible?
  wrap_as_member<some_object *> wptr2_obj(wptr_obj);
  BOOST_CHECK(wptr2_obj.is_mutable);
  some_object *ptr2_obj = wptr2_obj.set(&obj2).get();    
  BOOST_CHECK_EQUAL(ptr2_obj->sum(), 1.0);
  
  // Copy constructible from mutable when non-mutable?
  wrap_as_member<some_object *const> wconstptr2_obj(wptr_obj);
  BOOST_CHECK(!wconstptr2_obj.is_mutable);
  some_object *const constptr2_obj = wconstptr2_obj.get();    
  BOOST_CHECK_EQUAL(constptr2_obj->sum(), 1.0);
  
  // Copy constructible from non-mutable when mutable?
  wrap_as_member<some_object *> wptr3_obj(wconstptr_obj);
  BOOST_CHECK(wptr3_obj.is_mutable);
  some_object *ptr3_obj = wptr3_obj.set(&obj1).get();
  BOOST_CHECK_EQUAL(ptr3_obj->sum(), -1.0);
  
  // Copy constructible from mutable when mutable?
  wrap_as_member<some_object *> wptr4_obj(wptr3_obj);
  BOOST_CHECK(wptr4_obj.is_mutable);
  some_object *ptr4_obj = wptr4_obj.get();
  BOOST_CHECK_EQUAL(ptr4_obj->sum(), -1.0);
  
  // This should make the CopyConstructible concept check fail.
//  not_copy_constructible ncc;
//  wrap_as_member<not_copy_constructible> wncc(ncc);
}
