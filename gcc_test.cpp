extern "C" 
{
#define GTY(x)
#define IN_GCC
#include <gcc/config.h>
#include <gcc/glimits.h>
#include <gcc/system.h>
#include <gcc/coretypes.h>
#include <gcc/insn-config.h>
#include <gcc/insn-modes.h>
#include <gcc/libiberty.h>
#include <gcc/symtab.h>
#include <gcc/tree.h>
#include <gcc/auto-host.h>
#include <gcc/c-common.h>

#include <gcc/toplev.h>
#include <gcc/intl.h>
#include <gcc/diagnostic.h>
#include <gcc/tree-check.h>
#include <gcc/langhooks.h>
#include <gcc/hosthooks.h>
#undef CONST
//#define AND _AND
enum reg_class {};  
#include <gcc/reload.h>
#include <gcc/rtl.h>
#include <gcc/output.h>

#include <gcc/params.h>

const unsigned char 
executable_checksum[16] = {'3','9','c','9','f','6','2','9','1','8','0','d','f','a','6','0'};

#ifdef libintl_printf
#undef libintl_printf
int
libintl_printf(const char *format, ...)
{
  va_list args;
  va_start(args, format);
  int ret = libintl_vprintf(format, args);
  va_end(args);
  return ret;
}
#endif

}

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef IS_DIR_SEPARATOR
#define IS_DIR_SEPARATOR(c) ((c) == '/' || (c) == '\\')
#endif //ndef IS_DIR_SEPARATOR

//extern "C" 
char **save_argv;

extern "C"
const param_info lang_independent_params[] = {
#define DEFPARAM(ENUM, OPTION, HELP, DEFAULT, MIN, MAX) \
  { OPTION, DEFAULT, MIN, MAX, HELP },
#include <gcc/params.def>
#undef DEFPARAM
  { NULL, 0, 0, 0, NULL }
};

/* Default tree printer.   Handles declarations only.  */
extern "C" bool
default_tree_printer(pretty_printer * pp, text_info *text, const char *spec,
                      int precision, bool wide, bool set_locus, bool hash)
{
  tree t;

  /* FUTURE: %+x should set the locus.  */
  if(precision != 0 || wide || hash)
    return false;

  switch(*spec)
    {
    case 'D':
      t = va_arg(*text->args_ptr, tree);
      if(DECL_DEBUG_EXPR_IS_FROM(t) && DECL_DEBUG_EXPR(t))
  t = DECL_DEBUG_EXPR(t);
      break;

    case 'F':
    case 'T':
      t = va_arg(*text->args_ptr, tree);
      break;

    default:
      return false;
    }

  if(set_locus && text->locus)
    *text->locus = DECL_SOURCE_LOCATION(t);

  if(DECL_P(t))
    {
      const char *n = DECL_NAME(t)
        ? lang_hooks.decl_printable_name(t, 2)
        : "<anonymous>";
      pp_string(pp, n);
    }
  else
    dump_generic_node(pp, t, 0, 0, 0);

  return true;
}

/* Handler for fatal signals, such as SIGSEGV.  These are transformed
   into ICE messages, which is much more user friendly.  In case the
   error printer crashes, reset the signal to prevent infinite recursion.  */
#ifdef SIG_DFL
extern "C"
void
crash_signal (int signo)
{
  signal (signo, SIG_DFL);

  /* If we crashed while processing an ASM statement, then be a little more
     graceful.  It's most likely the user's fault.  */
  if (this_is_asm_operands)
    {
      output_operand_lossage ("unrecoverable error");
      exit (FATAL_EXIT_CODE);
    }

  internal_error ("%s", strsignal (signo));
}
#endif

extern "C"
void
general_init(const char *argv0)
{
  const char *p;

  p = argv0 + strlen(argv0);
  while(p != argv0 && !IS_DIR_SEPARATOR(p[-1]))
    --p;
  progname = p;

  xmalloc_set_program_name(progname);

  hex_init();

  /* Unlock the stdio streams.  */
  unlock_std_streams();

  gcc_init_libintl();

  /* Initialize the diagnostics reporting machinery, so option parsing
     can give warnings and errors.  */
  diagnostic_initialize(global_dc);
  /* Set a default printer.  Language specific initializations will
     override it later.  */
  pp_format_decoder(global_dc->printer) = &default_tree_printer;


  /* Trap fatal signals, e.g. SIGSEGV, and convert them to ICE messages.  */
#ifdef SIGSEGV
  signal(SIGSEGV, crash_signal);
#endif
#ifdef SIGILL
  signal(SIGILL, crash_signal);
#endif
#ifdef SIGBUS
  signal(SIGBUS, crash_signal);
#endif
#ifdef SIGABRT
  signal(SIGABRT, crash_signal);
#endif
#if defined SIGIOT &&(!defined SIGABRT || SIGABRT != SIGIOT)
  signal(SIGIOT, crash_signal);
#endif
#ifdef SIGFPE
  signal(SIGFPE, crash_signal);
#endif

  /* Other host-specific signal setup.  */
 (*host_hooks.extra_signals)();

  /* Initialize the garbage-collector, string pools and tree type hash
     table.  */
  init_ggc();
  init_stringpool();
  linemap_init(&line_table);
  init_ttree();

  /* Initialize register usage now so switches may override.  */
  init_reg_sets();

  /* Register the language-independent parameters.  */
  add_params(lang_independent_params, LAST_PARAM);

  /* This must be done after add_params but before argument processing.  */
  init_ggc_heuristics();
  init_optimization_passes();
}


int main(int argc, char *argv[])
{
  save_argv = argv;
  
  /* Initialization of GCC's environment, and diagnostics.  */
  general_init(argv[0]);
  
  print_version(stdout, "");
  
//  c_parse_file();
}
