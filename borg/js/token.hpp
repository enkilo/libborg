#ifndef BORG_JS_TOKEN_HPP
#define BORG_JS_TOKEN_HPP

#include <borg/parse/token_buf.hpp>
#include <borg/js/traits.hpp>
#include <borg/js/context.hpp>
#include <js/jsscan.h>

namespace borg {
namespace parse {

using borg::script::context_t;
  
//----------------------------------------------------------------------------
template<>
struct token_impl<js::traits>
{
  BORG_PARSE_TOKEN_TYPES(js::traits)

  enum type
  {
    tok_error = ::TOK_ERROR,           /* well-known as the only code < EOF */
    tok_eof = ::TOK_EOF,               /* end of file */
    tok_eol = ::TOK_EOL,               /* end of line */
    tok_semi = ::TOK_SEMI,             /* semicolon */
    tok_comma = ::TOK_COMMA,           /* comma operator */
    tok_assign = ::TOK_ASSIGN,         /* assignment ops (= += -= etc.) */
    tok_hook = ::TOK_HOOK,             /* conditional (?:) */
    tok_colon = ::TOK_COLON,
    tok_or = ::TOK_OR,                 /* logical or (||) */
    tok_and = ::TOK_AND,               /* logical and (&&) */
    tok_bitor = ::TOK_BITOR,           /* bitwise-or (|) */
    tok_bitxor = ::TOK_BITXOR,         /* bitwise-xor (^) */
    tok_bitand = ::TOK_BITAND,         /* bitwise-and (&) */
    tok_eqop = ::TOK_EQOP,             /* equality ops (== !=) */
    tok_relop = ::TOK_RELOP,           /* relational ops (< <= > >=) */
    tok_shop = ::TOK_SHOP,             /* shift ops (<< >> >>>) */
    tok_plus = ::TOK_PLUS,             /* plus */
    tok_minus = ::TOK_MINUS,           /* minus */
    tok_star = ::TOK_STAR,             /* multiply/divide ops (* / %) */
    tok_divop = ::TOK_DIVOP, 
    tok_unaryop = ::TOK_UNARYOP,       /* unary prefix operator */
    tok_inc = ::TOK_INC,               /* increment/decrement (++ --) */
    tok_dec = ::TOK_DEC,
    tok_dot = ::TOK_DOT,               /* member operator (.) */
    tok_lb = ::TOK_LB,                 /* left and right brackets */
    tok_rb = ::TOK_RB,
    tok_lc = ::TOK_LC,                 /* left and right curlies (braces) */
    tok_rc = ::TOK_RC,
    tok_lp = ::TOK_LP,                 /* left and right parentheses */
    tok_rp = ::TOK_RP,
    tok_name = ::TOK_NAME,             /* identifier */
    tok_number = ::TOK_NUMBER,         /* numeric constant */
    tok_string = ::TOK_STRING,         /* string constant */
    tok_object = ::TOK_OBJECT,         /* RegExp or other object constant */
    tok_primary = ::TOK_PRIMARY,       /* true, false, null, this, super */
    tok_function = ::TOK_FUNCTION,     /* function keyword */
    tok_export = ::TOK_EXPORT,         /* export keyword */
    tok_import = ::TOK_IMPORT,         /* import keyword */
    tok_if = ::TOK_IF,                 /* if keyword */
    tok_else = ::TOK_ELSE,             /* else keyword */
    tok_switch = ::TOK_SWITCH,         /* switch keyword */
    tok_case = ::TOK_CASE,             /* case keyword */
    tok_default = ::TOK_DEFAULT,       /* default keyword */
    tok_while = ::TOK_WHILE,           /* while keyword */
    tok_do = ::TOK_DO,                 /* do keyword */
    tok_for = ::TOK_FOR,               /* for keyword */
    tok_break = ::TOK_BREAK,           /* break keyword */
    tok_continue = ::TOK_CONTINUE,     /* continue keyword */
    tok_in = ::TOK_IN,                 /* in keyword */
    tok_var = ::TOK_VAR,               /* var keyword */
    tok_with = ::TOK_WITH,             /* with keyword */
    tok_return = ::TOK_RETURN,         /* return keyword */
    tok_new = ::TOK_NEW,               /* new keyword */
    tok_delete = ::TOK_DELETE,         /* delete keyword */
    tok_defsharp = ::TOK_DEFSHARP,     /* #n= for object/array initializers */
    tok_usesharp = ::TOK_USESHARP,     /* #n# for object/array initializers */
    tok_try = ::TOK_TRY,               /* try keyword */
    tok_catch = ::TOK_CATCH,           /* catch keyword */
    tok_finally = ::TOK_FINALLY,       /* finally keyword */
    tok_throw = ::TOK_THROW,           /* throw keyword */
    tok_instanceof = ::TOK_INSTANCEOF, /* instanceof keyword */
    tok_debugger = ::TOK_DEBUGGER,     /* debugger keyword */
    tok_xmlstago = ::TOK_XMLSTAGO,     /* XML start tag open (<) */
    tok_xmletago = ::TOK_XMLETAGO,     /* XML end tag open (</) */
    tok_xmlptagc = ::TOK_XMLPTAGC,     /* XML point tag close (/>) */
    tok_xmltagc = ::TOK_XMLTAGC,       /* XML start or end tag close (>) */
    tok_xmlname = ::TOK_XMLNAME,       /* XML start-tag non-final fragment */
    tok_xmlattr = ::TOK_XMLATTR,       /* XML quoted attribute value */
    tok_xmlspace = ::TOK_XMLSPACE,     /* XML whitespace */
    tok_xmltext = ::TOK_XMLTEXT,       /* XML text */
    tok_xmlcomment = ::TOK_XMLCOMMENT, /* XML comment */
    tok_xmlcdata = ::TOK_XMLCDATA,     /* XML CDATA section */
    tok_xmlpi = ::TOK_XMLPI,           /* XML processing instruction */
    tok_at = ::TOK_AT,                 /* XML attribute op (@) */
    tok_dblcolon = ::TOK_DBLCOLON,     /* namespace qualified name op (::) */
    tok_anyname = ::TOK_ANYNAME,       /* XML AnyName singleton (*) */
    tok_dbldot = ::TOK_DBLDOT,         /* XML descendant op (..) */
    tok_filter = ::TOK_FILTER,         /* XML filtering predicate op (.()) */
    tok_xmlelem = ::TOK_XMLELEM,       /* XML element node type (no token) */
    tok_xmllist = ::TOK_XMLLIST,       /* XML list node type (no token) */
    tok_reserved,                      /* reserved keywords */
    tok_limit                          /* domain size */
  };

  static token_id_type
  id(const token_type &tok)
  {
    return tok.type;
  }
  
  static position_type
  pos(const token_type &tok)
  {
    return tok.pos;
  }
  
  static length_type
  size(const token_type &tok)
  {
    return tok.pos.end.index - tok.pos.begin.index;
  }
  
  static token_id_type
  get_id(const token_type &tok)
  {
    return (token_id_type)tok.type;
  }
  
  static std::string
  get_value(const token_type &tok)
  {
    return std::string(tok.ptr, tok.ptr + size(tok));
  }
  
};
  
//----------------------------------------------------------------------------
const char *
get_token_name(token_impl<js::traits>::type tokid)
{
  switch(tokid)
  {
#define JS_TOKEN_CASE(name) \
  case token_impl<js::traits>::name: return #name;

    JS_TOKEN_CASE(tok_error)
    JS_TOKEN_CASE(tok_eof)
    JS_TOKEN_CASE(tok_eol)
    JS_TOKEN_CASE(tok_semi)
    JS_TOKEN_CASE(tok_comma)
    JS_TOKEN_CASE(tok_assign)
    JS_TOKEN_CASE(tok_hook)
    JS_TOKEN_CASE(tok_colon)
    JS_TOKEN_CASE(tok_or)
    JS_TOKEN_CASE(tok_and)
    JS_TOKEN_CASE(tok_bitor)
    JS_TOKEN_CASE(tok_bitxor)
    JS_TOKEN_CASE(tok_bitand)
    JS_TOKEN_CASE(tok_eqop)
    JS_TOKEN_CASE(tok_relop)
    JS_TOKEN_CASE(tok_shop)
    JS_TOKEN_CASE(tok_plus)
    JS_TOKEN_CASE(tok_minus)
    JS_TOKEN_CASE(tok_star)
    JS_TOKEN_CASE(tok_divop)
    JS_TOKEN_CASE(tok_unaryop)
    JS_TOKEN_CASE(tok_inc)
    JS_TOKEN_CASE(tok_dec)
    JS_TOKEN_CASE(tok_dot)
    JS_TOKEN_CASE(tok_lb)
    JS_TOKEN_CASE(tok_rb)
    JS_TOKEN_CASE(tok_lc)
    JS_TOKEN_CASE(tok_rc)
    JS_TOKEN_CASE(tok_lp)
    JS_TOKEN_CASE(tok_rp)
    JS_TOKEN_CASE(tok_name)
    JS_TOKEN_CASE(tok_number)
    JS_TOKEN_CASE(tok_string)
    JS_TOKEN_CASE(tok_object)
    JS_TOKEN_CASE(tok_primary)
    JS_TOKEN_CASE(tok_function)
    JS_TOKEN_CASE(tok_export)
    JS_TOKEN_CASE(tok_import)
    JS_TOKEN_CASE(tok_if)
    JS_TOKEN_CASE(tok_else)
    JS_TOKEN_CASE(tok_switch)
    JS_TOKEN_CASE(tok_case)
    JS_TOKEN_CASE(tok_default)
    JS_TOKEN_CASE(tok_while)
    JS_TOKEN_CASE(tok_do)
    JS_TOKEN_CASE(tok_for)
    JS_TOKEN_CASE(tok_break)
    JS_TOKEN_CASE(tok_continue)
    JS_TOKEN_CASE(tok_in)
    JS_TOKEN_CASE(tok_var)
    JS_TOKEN_CASE(tok_with)
    JS_TOKEN_CASE(tok_return)
    JS_TOKEN_CASE(tok_new)
    JS_TOKEN_CASE(tok_delete)
    JS_TOKEN_CASE(tok_defsharp)
    JS_TOKEN_CASE(tok_usesharp)
    JS_TOKEN_CASE(tok_try)
    JS_TOKEN_CASE(tok_catch)
    JS_TOKEN_CASE(tok_finally)
    JS_TOKEN_CASE(tok_throw)
    JS_TOKEN_CASE(tok_instanceof)
    JS_TOKEN_CASE(tok_debugger)
    JS_TOKEN_CASE(tok_xmlstago)
    JS_TOKEN_CASE(tok_xmletago)
    JS_TOKEN_CASE(tok_xmlptagc)
    JS_TOKEN_CASE(tok_xmltagc)
    JS_TOKEN_CASE(tok_xmlname)
    JS_TOKEN_CASE(tok_xmlattr)
    JS_TOKEN_CASE(tok_xmlspace)
    JS_TOKEN_CASE(tok_xmltext)
    JS_TOKEN_CASE(tok_xmlcomment)
    JS_TOKEN_CASE(tok_xmlcdata)
    JS_TOKEN_CASE(tok_xmlpi)
    JS_TOKEN_CASE(tok_at)
    JS_TOKEN_CASE(tok_dblcolon)
    JS_TOKEN_CASE(tok_anyname)
    JS_TOKEN_CASE(tok_dbldot)
    JS_TOKEN_CASE(tok_filter)
    JS_TOKEN_CASE(tok_xmlelem)
    JS_TOKEN_CASE(tok_xmllist)
    default: return "unknown";
  }
}  

//----------------------------------------------------------------------------

} // namespace parse

namespace js {

typedef borg::parse::token_impl<traits>::type token_type;
typedef borg::parse::token<traits> token;
  
} // namespace js
} // namespace borg

//----------------------------------------------------------------------------
#endif //ndef BORG_JS_TOKEN_HPP
