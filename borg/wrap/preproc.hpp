#ifndef WRAP_PREPROC_HPP
#define WRAP_PREPROC_HPP

#include <boost/preprocessor.hpp>
#include <borg/preproc.hpp>

//---------------------------------------------------------------------------
//! Suffixes of all possible wrapper pattern classes.
//---------------------------------------------------------------------------
#define WRAP_PATTERN_SEQ \
    (_impl) \
    (_interface) \
    (_facade) \
    (_t) \
    ()

//---------------------------------------------------------------------------
//! Same as WRAP_PATTERN_SEQ sequence, but as array.
//---------------------------------------------------------------------------
#define WRAP_PATTERN_ARRAY \
    BOOST_PP_SEQ_TO_ARRAY(WRAP_PATTERN_SEQ)

//---------------------------------------------------------------------------
//! Full pattern names.
//---------------------------------------------------------------------------
/*#define WRAP_PATTERN_NAME_a _impl
#define WRAP_PATTERN_NAME_i _interface
#define WRAP_PATTERN_NAME_f _facade
#define WRAP_PATTERN_NAME_t _t
#define WRAP_PATTERN_NAME

//#define WRAP_PATTERN_RESOLVE(name, suffix) name##suffix
#define WRAP_PATTERN_RESOLVE(name, suffix) BOOST_PP_CAT(*/

//---------------------------------------------------------------------------
//! Basic template argument sequences for every pattern.
//---------------------------------------------------------------------------
#define WRAP_TEMPLATE_ARGS_impl  (class Traits)                 // impl
#define WRAP_TEMPLATE_ARGS_interface (class Traits) (class Derived) // interface
#define WRAP_TEMPLATE_ARGS_facade    (class Traits) (class Derived) // facade
#define WRAP_TEMPLATE_ARGS_t         (class Traits)                 // adapter
#define WRAP_TEMPLATE_ARGS           (class Traits)                 // object


#define WRAP_SEQ_FOREACH(seq, macro, user_data) \
    BOOST_PP_SEQ_FOR_EACH(macro, user_data, seq)

#define WRAP_PATTERN_FOREACH(macro, user_data) \
    WRAP_SEQ_FOREACH(WRAP_PATTERN_SEQ, macro, user_data)

#define WRAP_CLASS_FORWARD(name, pattern, extra_args) \
    WRAP_CLASS_TEMPLATE(name, pattern, extra_args);

#define WRAP_CLASS_TEMPLATE(name, pattern, extra_args) \
    template< BOOST_PP_SEQ_ENUM(WRAP_TEMPLATE_ARGS##pattern extra_args) > \
    class name##pattern

//---------------------------------------------------------------------------
//! Gets called for every iteration and expands to a forward declaration.
//---------------------------------------------------------------------------
#define WRAP_ITERATE_FORWARD(r, user_data, elem) \
    WRAP_CLASS_FORWARD(BOOST_PP_TUPLE_ELEM(2, 0, user_data), \
                       elem, \
                       BOOST_PP_TUPLE_ELEM(2, 1, user_data))

//---------------------------------------------------------------------------
#define WRAP_SEQ_FORWARD(name, seq, extra...) \
    WRAP_SEQ_FOREACH(seq, WRAP_ITERATE_FORWARD, (name, extra))
  
//---------------------------------------------------------------------------
//! Generate a forward declaration of every pattern template for the 
//! specified class name.
//---------------------------------------------------------------------------
#define WRAP_PATTERN_FORWARD(name, extra...) \
    WRAP_PATTERN_FOREACH(WRAP_ITERATE_FORWARD, (name, extra))

//---------------------------------------------------------------------------
#endif //ndef WRAP_PREPROC_HPP
