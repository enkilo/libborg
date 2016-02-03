#ifndef BORG_PREPROC_HPP
#define BORG_PREPROC_HPP

//---------------------------------------------------------------------------
//! operator->
//---------------------------------------------------------------------------
#define BORG_PP_USE_TYPE(traits, type) \
    typedef traits::type type;

#define BORG_PP_ALIAS_TYPE(type, alias) \
    typedef type alias##_type;

//---------------------------------------------------------------------------
//! Typedefs the argument as traits_type in the current scope.
//---------------------------------------------------------------------------
#define BORG_PP_DEF_TRAITS(Traits) \
    BORG_PP_ALIAS_TYPE(Traits, traits)

//---------------------------------------------------------------------------
//! Forwards a typedef from traits (after declaring BORG_PP_DEF_TRAITS) to
//! the current scope.
//---------------------------------------------------------------------------
#define BORG_PP_ALIAS_TRAITS(type) \
    BORG_PP_USE_TYPE(typename traits, type)

#define BORG_PP_ALIAS_TYPEDEF(traits, type, alias) \
    typedef traits::type##_type alias##_type;

#define BORG_PP_USE_TYPEDEF(traits, type) \
    BORG_PP_ALIAS_TYPEDEF(traits, type, type)

#define BORG_PP_USE_TRAITS(type) \
    BORG_PP_USE_TYPE(typename traits_type, type)

//---------------------------------------------------------------------------
//! operator->
//---------------------------------------------------------------------------
#define BORG_PP_OPERATOR_ARROW(type) \
    type operator->() const
  
#define BORG_PP_OPERATOR_ARROW_EXPR(type, expr) \
        BORG_PP_OPERATOR_ARROW(type) \
        { return expr; }
  
//---------------------------------------------------------------------------
//! operator type
//---------------------------------------------------------------------------
#define BORG_PP_OPERATOR_CONVERT(type) \
    operator type() const

#define BORG_PP_OPERATOR_CONVERT_EXPR(type, expr) \
        BORG_PP_OPERATOR_CONVERT(type) \
        { return expr; }
  

#define BORG_PP_VERBOSE_CODE(expr) std::cout << #expr ": " << (expr) << std::endl;


#endif //ndef BORG_PREPROC_HPP
