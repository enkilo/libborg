#ifndef PROPERTY_INTERFACE_HPP
#define PROPERTY_INTERFACE_HPP

namespace borg { namespace detail {
  
//----------------------------------------------------------------------------
template<class ObjectT, int Id, typename ValueT>
class class_property_impl;
  
#define CLASS_PROPERTY(Namespace, ObjectT, Id, ValueT, GetCode, SetCode) \
template<> \
class Namespace::class_property_impl<ObjectT, Id, ValueT> \
{ \
public: \
  static ValueT \
  get(const ObjectT *obj) \
  { return (GetCode); } \
  \
  static void \
  set(ObjectT *obj, const ValueT &v) \
  { (SetCode); } \
  \
};

//----------------------------------------------------------------------------
template<template<class, class, class> class TemplateT, int Id, typename ValueT>
class template_ccc_property_impl;
  
#define TEMPLATE_CCC_PROPERTY(TemplateT, Id, ValueT, GetCode, SetCode) \
template<> \
class template_ccc_property_impl<TemplateT, Id, ValueT> \
{ \
public: \
  static const int id = Id; \
  typedef ValueT value_type; \
  \
  template<class A, class B, class C> \
  static ValueT \
  get(/*const*/ TemplateT<A, B, C> *obj) \
  { return (GetCode); } \
  \
  template<class A, class B, class C> \
  static void \
  set(TemplateT<A, B, C> *obj, const ValueT &value) \
  { (SetCode); } \
  \
};

#define TEMPLATE_CCC_PROPERTY_TYPE(Namespace, TemplateT, Id, ValueT) \
  Namespace::template_ccc_property_impl<TemplateT, Id, ValueT>

//----------------------------------------------------------------------------
template<template<class, class, class, bool> class TemplateT, int Id, typename ValueT>
class template_cccb_property_impl;
  
#define TEMPLATE_CCCB_PROPERTY(TemplateT, Id, ValueT, GetCode, SetCode) \
template<> \
class template_cccb_property_impl<TemplateT, Id, ValueT> \
{ \
public: \
  static const int id = Id; \
  typedef ValueT value_type; \
  \
  template<class A, class B, class C, bool D> \
  static ValueT \
  get(const TemplateT<A, B, C, D> *obj) \
  { return (GetCode); } \
  \
  template<class A, class B, class C, bool D> \
  static void \
  set(TemplateT<A, B, C, D> *obj, const ValueT &value) \
  { (SetCode); } \
  \
};

#define TEMPLATE_CCCB_PROPERTY_TYPE(Namespace, TemplateT, Id, ValueT) \
  Namespace::template_cccb_property_impl<TemplateT, Id, ValueT>

}// namespace detail
}// namespace borg
  
//---------------------------------------------------------------------------
#endif //ndef PROPERTY_INTERFACE_HPP
