# $Id: $
#host = i686-pc-cygwin
#arch = i686
#system = cygwin
#prefix = /usr/i686-pc-mingw32

# Package and system info.
# ---------------------------------------------------------------------------
PACKAGE = libborg
VERSION = 1.0
MKRULES = borg.mk
#LIBPATH = abstract cairo libiconv pthreads wxWidgets
WARNINGS = all
SYMBOLS = 1
DEPMODE = 1
CMDECHO = short
#CMDECHO = full
MACHINE = 
OPTIMIZE = 0

SRCDIRS = \
  . \
  ast \
  base \
  boost \
  borg \
  borg/apache \
  borg/cairo \
  borg/event \
  borg/js \
  borg/libxml2 \
  borg/libxml2/dom \
  borg/libxml2/lib \
  borg/libxml2/xpath \
  borg/parse \
  borg/recls \
  borg/tk \
  borg/traits \
  borg/types \
  borg/util \
  borg/util/detail \
  borg/wrap \
  borg/wrap/concepts \
  borg/wrap/core \
  borg/wrap/traits \
  borg/wx \
  borg/wx/dom \
  borg/wx/lib \
  borg/xalan \
  borg/xerces \
  borg/xerces/dom \
  borg/xerces/lib \
  borg/xerces/xpath \
  borg/xml \
  borg/xml/dom \
  borg/xml/lib \
  borg/xml/xpath \
  brainstorm \
  cxx \
  gccxml \
  indent \
  interface \
  io \
  io/filter \
  io/filter/concepts \
  io/filter/detail \
  libs \
  libs/ansi \
  libs/util \
  libs/vstgui \
  libs/wx \
  libs/zend \
  nlp \
  sys \
  tools \
  tools/pkg \
  vst \
  vstgui \
  widgets

AUXDIRS = \
  trash \
  libs/wrap \
  libs/wrap/tests

# Default target
# ---------------------------------------------------------------------------
#all: $(LIBRARIES) $(PROGRAMS)

CPPFLAGS += -I.

PNG_LIBS += -lpng -lz

ifeq ($(system), cygwin)
WIN32_LIBS += -lcomdlg32 -lmsimg32 -lgdi32 -luuid -lole32
endif


# library build configuration.
# ---------------------------------------------------------------------------
libborg_EXTENSIONS = *.cpp *.hpp *.c
libborg_MASKS = $(foreach dir,$(SRCDIRS), $(addprefix $(dir)/,$(libborg_EXTENSIONS)))
libborg_SOURCES = $(filter-out $(libborg_EXCLUDE),$(patsubst ./%,%,$(wildcard $(libborg_MASKS))))
libborg_HEADERS = $(wildcard *.hpp */*.hpp)
libborg_OBJECTS = $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(filter %.cpp,$(libborg_SOURCES)) $(filter %.c,$(libborg_SOURCES))))
libborg_EXCLUDE = \
  $(borg_SOURCES) \
  cairo/cairo_wrappers.cpp \
  $(test_SOURCES) \
  test.cpp \
  $(wildcard wrap/*.cpp wrap/test/*.cpp)

test_OBJECTS = $(test_SOURCES:%.cpp=%.o)
test_SOURCES = \
  test.cpp \
  wrap/tests/test_is_mutable.cpp \
  wrap/tests/test_wrap_traits.cpp \
  wrap/tests/test_wrap_as_member.cpp \
  wrap/tests/test_implicit_wrapper.cpp \
  wrap/tests/test_pointer.cpp

borg_PROGRAMS = \
  proof$(binext) \
  wxtest$(binext) \
  rtldtest$(binext) \
  cpplexer_test$(binext) \
  io_test$(binext) \
  js_test$(binext) \
  pex_test$(binext) \
  xpdf_test$(binext) \
  xpdf_text$(binext) \
  apr_test$(binext) \
  xerces_test$(binext) \
  xerces_parser$(binext) \
  string_test$(binext) \
  allocator_test$(binext) \
  array_test$(binext) \
  ast_test$(binext) \
  xml_test$(binext) \
  nspr_test$(binext) \
  fs_test$(binext) \
  nlp_test$(binext) \
  libxml2_test$(binext) \
  wxxml_test$(binext) \
  xpath_shell$(binext) \
  spirit_test$(binext) \
  regex_test$(binext) \
  ast_calc$(binext) \
  php_test$(binext) \
  net_test$(binext) \
  file_test$(binext) \
  http_test$(binext) \
  zipios_test$(binext) \
  aterm_test$(binext) \
  juce_test$(binext) \
  template_test$(binext) \
  tokenizer_test$(binext) \
  yaml_test$(binext) \
  tk_test$(binext) \
  codegrep$(binext)

borg_NOCOMPILE = \
  gcc_test$(binext) \
  preproc_test$(binext) 
  
borg_PLUGINS = \
  vsttest.$(slibext) \
  wxvsttest.$(slibext)

borg_SOURCES = \
  $(borg_PROGRAMS:%$(binext)=%.cpp) \
  $(borg_NOCOMPILE:%$(binext)=%.cpp) \
  $(borg_PLUGINS:%.$(slibext)=%.cpp) \
  $(test_SOURCES) \
  test.cpp

borg_OBJECTS = $(borg_SOURCES:%.cpp=%.o)

# Global build configuration.
# ---------------------------------------------------------------------------
SOURCES = $(libborg_SOURCES) $(borg_SOURCES) $(test_SOURCES)
HEADERS = $(libborg_HEADERS)
OBJECTS = $(libborg_OBJECTS) $(borg_OBJECTS)
LIBRARIES = libborg.a 
SUPPORT = GNUmakefile $(topdir)$(MKRULES)
PROGRAMS = $(borg_PROGRAMS)

#DEPFILES = $(subst .o,.d,$(OBJECTS))
DEPFILES = $(wildcard *.d)
CLEANFILES = $(OBJECTS) $(DEPFILES) $(LIBRARIES)
DISTFILES = $(SUPPORT) $(SOURCES) $(HEADERS)

# Include global configuration.
# ---------------------------------------------------------------------------
TARGETS = $(PROGRAMS) $(LIBRARIES) vsttest.$(slibext) wxvsttest.$(slibext)

topdir ?= $(dir $(wildcard ../borg.mk))
include $(topdir)$(MKRULES)

ifeq ($(system), cygwin)
host = i686-pc-mingw32
endif

# Build targets.
# ---------------------------------------------------------------------------

# Installation target
install: all
	$(INSTALL) -d $(bindir) $(cxxincludedir) $(libdir)
	$(SHELL) install-header.sh $(libborg_HEADERS) $(includedir)
	$(INSTALL_DATA) libborg.a $(libdir)

# ---------------------------------------------------------------------------
#NSPR_LIBS = $(shell { $(CC) -L$(libdir)/nspr -L$(bindir) -lnspr4 2>/dev/null && echo -L$(libdir)/nspr -L$(bindir) -lnspr4; } || { $(CC) -L$(libdir)/nspr -lnspr 2>/dev/null && echo -L$(libdir)/nspr -lnspr; })

#CXX = g++-4.3.0
#CXXFLAGS += -std=c++0x

info:	
	@echo "prefix: $(prefix)"
	@echo "host: $(host)"
	@echo "arch: $(arch)"
	@echo "system: $(system)"
	@echo "NSPR_LIBS: $(NSPR_LIBS)"
#	@echo "libborg masks: $(libborg_MASKS)"
#	@echo "libborg sources: $(libborg_SOURCES)"
#	@echo "libborg objects: $(libborg_OBJECTS)"

# Library link targets.
# ---------------------------------------------------------------------------
#CXXFLAGS += -fdump-translation-unit -fdump-tree-original -fdump-class-hierarchy

ifeq ($(system), mingw32)
WIN32_LIBS = -lgdi32 -lws2_32 -lmswsock -lwinmm -lole32 -luuid
endif

ifeq ($(system), linux)
CPPFLAGS += -DLINUX
LINUX_LIBS = -lroken -lcrypt
#LINUX_LIBS := $(shell { $(CC) -lroken -lcrypt 2>/dev/null && echo -lroken -lcrypt; } || { $(CC) -lcrypt 2>/dev/null && echo -lcrypt; })
endif

ifneq ($(OPTIMIZE),0)
CXXFLAGS += -finline
endif

CXXFLAGS += -MD -fexceptions
#CXXFLAGS += -std='c++0x'
libborg.a: $(libborg_OBJECTS)

Thread.o: CPPFLAGS += -I$(topdir)pthreads

test.o: test.cpp
wxtest.o: wxtest.cpp
#gdmmtest.o: CPPFLAGS += -I$(topdir)gdmm
gdmmtest.o: gdmmtest.cpp
#sys/rtld.o: CPPFLAGS += -I$(topdir)dlcompat

ifeq ($(system), mingw32)
WX_CFLAGS = -D__WXMSW__ -DWXUSINGDLL -I$(includedir)/wx-2.8
WX_LIBS = -lwx_net -lwx_xml -lwx_core -lwx_base
else
WX_CFLAGS := $(shell wx-config --cflags)
WX_LIBS := $(shell wx-config --libs)
endif

PANGO_LIBS = -lpango-1.0 -lpangocairo-1.0
CAIRO_CFLAGS = -I$(includedir)/cairo
VST_CFLAGS = -I$(topdir)vstsdk -DVST_FORCE_DEPRECATED=1

LIBXML2_CFLAGS = -I$(includedir)/libxml2
LIBXML2_LIBS = -lxml2

NSPR_CFLAGS =
NSPR_LIBS = -L$(libdir)/nspr -L$(bindir) -lnspr4

PHP_CFLAGS = $(shell php-config --includes)
PHP_LIBS = 

JS_CFLAGS =
JS_LIBS = $(libdir)/libjs.a -L$(bindir) -lnspr4

#CRYPT_LIBS = $(shell $(CC) -lcrypt 2>/dev/null && echo -lcrypt)
GLOB_LIBS = $(shell $(CC) -lroken -lcrypt 2>/dev/null && echo -lroken -lcrypt)

wxtest.o \
wxvsttest.o \
vst/vst_wxeditor.o \
libs/wx/wx_tk.o \
libs/wx/wx_frame.o \
libs/wx/wx_widget.o: CFLAGS += $(WX_CFLAGS)

wxtest.o: CFLAGS += $(CAIRO_CFLAGS)

vsttest.o \
vsttest_main.o \
wxvsttest.o \
rtldtest.o: CFLAGS += $(VST_CFLAGS)

vsttest.o: vsttest.cpp

vst/vst_proxy.o \
vst/vst_plugin.o \
vst/vst_editor.o \
vst/vst_wxeditor.o \
vst/vst_loader.o \
vst/vst_master.o: CFLAGS += $(VST_CFLAGS)


#vst/vst_editor.o: CPPFLAGS += -DVSTSDK_INSTALLED

tk/vstgui.o: CPPFLAGS += -I$(topdir:%/=%)

#$(borg_OBJECTS): %.o: %.cpp $(libborg_HEADERS)

#test.o wxtest.o: CPPFLAGS += -D__WXMSW__ -DWXUSINGDLL

#$(borg_PROGRAMS): CPPFLAGS += -I$(topdir)pthreads

wxtest.o wxtest.ii wrap/cairo.o: CPPFLAGS += -I$(includedir)/cairo

#$(borg_PROGRAMS): CFLAGS += $(shell $(bindir)/wx-config --cflags)
#$(borg_PROGRAMS): LDFLAGS += -L../wxWidgets
#$(borg_PROGRAMS): CC = $(CXX)
#$(borg_PROGRAMS): CFLAGS = $(CXXFLAGS)
#$(borg_PROGRAMS): %$(binext): %.o libborg.a -lpthread
#$(borg_PROGRAMS): LIBS += $(shell $(bindir)/wx-config --libs)
#$(borg_PROGRAMS): -lwx_msw_adv-2.8 -lwx_msw_core-2.8 -lwx_base-2.8
#$(borg_PROGRAMS): ../libiconv/libiconv.a -lwx_adv -lwx_core -lwx_base
#$(borg_PROGRAMS): -lcairo

CPPFLAGS += -DVSTSDK_INSTALLED

vsttest.$(slibext): DRIVER = $(CXX)
vsttest.$(slibext): vsttest.o libborg.a vsttest.def
vsttest.$(slibext): LIBS += -lvstgui -lvstsdk -lpthread -lcairo

ifeq ($(system), mingw32)
vsttest.$(slibext): LIBS += -liconv
endif

vsttest.$(slibext): LIBS += $(WIN32_LIBS) 
#-lcomdlg32 -lgdi32 -luuid -lole32 
#../vstsdk/public.sdk/source/vst2.x/vstplugmain.o
#-lgdiplus 

wxvsttest.$(slibext): DRIVER = $(CXX)
wxvsttest.$(slibext): LIBS += -lwx_core -lwx_base -lvstsdk -lpthread -lcairo

ifeq ($(system), mingw32)
wxvsttest.$(slibext): LIBS += -liconv
endif

wxvsttest.$(slibext): LIBS += -luuid -lole32
wxvsttest.$(slibext): wxvsttest.o libborg.a vsttest.def 
#../vstsdk/public.sdk/source/vst2.x/vstplugmain.o
	$(DRIVER) -shared -o $@ $^ $(LIBS)

#tk/vstgui.o vsttest.o rtldtest.o wxtest.o: CPPFLAGS += -I$(topdir)vstgui -I$(topdir)vstsdk  -DVST_FORCE_DEPRECATED=1
rtldtest$(binext): LIBS += -lvstsdk -ldl

#gdmmtest$(binext): LIBS += -L$(topdir)gdmm -lgdmm -L$(topdir)gd -lgd
gdmmtest$(binext): gdmmtest.o

proof.o: proof.cpp
proof$(binext): LINK = $(CXXLINK)
proof$(binext): LIBS = -lxerces-c
proof$(binext): proof.o

wxtest$(binext): wxtest.o libborg.a
wxtest$(binext): LINK = $(CXXLINK)

ifeq ($(system), mingw32)
wxtest$(binext) vsttest.$(slibext): LIBS += -L. -liconv
endif
 
wxtest$(binext) vsttest.$(slibext): LIBS += -L. -lcairo $(WX_LIBS) $(PANGO_LIBS) -lboost_signals -ldl

cpplexer_test$(binext): LINK = $(CXXLINK)
cpplexer_test$(binext): LIBS += -lboost_wave -lboost_filesystem -lboost_iostreams -lboost_program_options
cpplexer_test$(binext): cpplexer_test.o
cpplexer_test.xml: CPPFLAGS += -DBOOST_PLATFORM=\"mingw32\" -DBOOST_COMPILER=\"g++\"

codegrep$(binext): LINK = $(CXXLINK)
codegrep$(binext): LIBS += -lboost_wave -lboost_filesystem -lboost_iostreams -lboost_program_options
codegrep$(binext): codegrep.o
#codegrep.xml: CPPFLAGS += -DBOOST_PLATFORM=\"mingw32\" -DBOOST_COMPILER=\"g++\"

io_test$(binext): LINK = $(CXXLINK)
io_test$(binext): LIBS += -lboost_iostreams
io_test$(binext): io_test.o

js_test$(binext): OPTIMIZE = 0
js_test$(binext): CXXFLAGS += -DBOOST_USE_WINDOWS_H -D__GNUWIN32__ -D_DEBUG  -D_WINDOWS  -D_MBCS  -D_USRDLL  -DBOOST_CLIPP_EXPORTS
js_test$(binext): LINK = $(CXXLINK)
#js_test$(binext): LIBS += -lboost_javascript -lboost_clipp 
js_test$(binext): LIBS += $(libdir)/libjs.a -L$(bindir) $(NSPR_LIBS) -ldl
js_test$(binext): js_test.o

pex_test$(binext): LINK = $(CXXLINK)
pex_test$(binext): LIBS += -L$(libdir) -liberty
pex_test$(binext): pex_test.o libs/util/pex.o

xpdf_test$(binext): LINK = $(CXXLINK)
xpdf_test$(binext): LIBS += -lrecls.1.gcc40 -lxpdf $(GLOB_LIBS) $(CRYPT_LIBS) $(WIN32_LIBS) $(LINUX_LIBS)
xpdf_test$(binext): xpdf_test.o

xpdf_text$(binext): LINK = $(CXXLINK)
xpdf_text$(binext): LIBS += -lxpdf $(WIN32_LIBS)
#-lgdi32
xpdf_text$(binext): xpdf_text.o

gcc_test$(binext): LINK = $(CXXLINK)
#gcc_test$(binext): LIBS += -L$(bindir) -lcc1plus -lbackend -lcpp -liberty $(libdir)/libintl.a $(libdir)/libiconv.a
gcc_test$(binext): CPPFLAGS += -I$(includedir)/gcc
gcc_test$(binext): LIBS += -lcc1plus -lbackend -lcpp -liberty -lintl -liconv
gcc_test$(binext): gcc_test.o

#APR_CFLAGS = $(shell $(bindir)/apr-1-config --cppflags --includes 2>/dev/null || $(bindir)/apr-config --cppflags --includes  2>/dev/null) -I$(includedir)/apr -I$(includedir)/apr-0
#APR_LIBS = $(shell $(bindir)/apr-1-config --link-ld --libs 2>/dev/null || $(bindir)/apr-config --link-ld --libs 2>/dev/null)
APR_CFLAGS = -I$(includedir)/apr
APR_LIBS = $(shell $(bindir)/apr-1-config --link-ld --libs 2>/dev/null || $(bindir)/apr-config --link-ld --libs 2>/dev/null)

APU_CFLAGS = $(shell $(bindir)/apu-1-config --includes 2>/dev/null || $(bindir)/apu-config --includes 2>/dev/null)
APU_LIBS = $(shell $(bindir)/apu-1-config --link-ld --libs 2>/dev/null || $(bindir)/apu-config --link-ld --libs 2>/dev/null)

apr_test.o: apr_test.cpp
apr_test$(binext): LINK = $(CXXLINK)
#apr_test$(binext): LDFLAGS += -static
apr_test$(binext): CFLAGS += $(APR_CFLAGS)
ifeq ($(system),mingw32)
apr_test$(binext): CFLAGS += -DWIN32 -DAPR_DECLARE_STATIC
endif
#apr_test$(binext): LIBS += -L$(bindir) $(APU_LIBS) $(APR_LIBS) $(WIN32_LIBS)
apr_test$(binext): LIBS += -L$(bindir) -laprutil -lapr
apr_test$(binext): apr_test.o

XERCES_LIBS = -lxalan-c -lxerces-c

xerces_test.o: xerces_test.cpp
xerces_test$(binext): LINK = $(CXXLINK)
xerces_test$(binext): LDFLAGS += $(XERCES_LDFLAGS)
xerces_test$(binext): CFLAGS += $(XERCES_CFLAGS)
xerces_test$(binext): LIBS += $(XERCES_LIBS)
xerces_test$(binext): xerces_test.o

xerces_parser.o: xerces_parser.cpp
xerces_parser$(binext): LINK = $(CXXLINK)
xerces_parser$(binext): LDFLAGS += $(XERCES_LDFLAGS)
xerces_parser$(binext): CFLAGS += $(XERCES_CFLAGS)
xerces_parser$(binext): LIBS += $(XERCES_LIBS)
xerces_parser$(binext): xerces_parser.o

rtldtest$(binext): LINK = $(CXXLINK)
rtldtest$(binext): rtldtest.o libborg.a

allocator_test.o string_test.o: CXXFLAGS += $(WX_CFLAGS) $(LIBXML2_CFLAGS) $(JS_CFLAGS) $(APR_CFLAGS)
allocator_test$(binext) string_test$(binext): LINK = $(CXXLINK)
allocator_test$(binext) string_test$(binext): LIBS += -lboost_unit_test_framework -ljuce -lxerces-c $(JS_LIBS) $(WX_LIBS) $(LIBXML2_LIBS) -L$(bindir) -lapr #$(APR_LIBS)
string_test$(binext): string_test.o
allocator_test$(binext): allocator_test.o

ast_test$(binext): LINK = $(CXXLINK)
ast_test.o: CPPFLAGS += -I$(includedir)/libxml2 -std=c++0x
ast_test$(binext): LIBS += -lxml2
ast_test$(binext): ast_test.o libborg.a
#ast_test.o: OPTIMIZE = s
#ast_test.o: CXXFLAGS += --param max-inline-insns-single=2048 -Winline

ast_calc$(binext): LINK = $(CXXLINK)
ast_calc$(binext): ast_calc.o libborg.a

xml_test.o: xml_test.cpp
xml_test$(binext): LINK = $(CXXLINK)
xml_test$(binext): LDFLAGS += $(XERCES_LDFLAGS)
xml_test$(binext): CFLAGS += -I. $(XERCES_CFLAGS)
xml_test$(binext): LIBS += $(XERCES_LIBS)
xml_test$(binext): xml_test.o

array_test$(binext): CXXFLAGS += $(WX_CFLAGS)
array_test$(binext): LINK = $(CXXLINK)
array_test$(binext): LIBS += $(WX_LIBS)
array_test$(binext): array_test.o libborg.a

nspr_test$(binext): LINK = $(CXXLINK)
#nspr_test$(binext): LDFLAGS += -static
# -ljs3250
nspr_test$(binext): LIBS += -L$(bindir) -L$(libdir)/nspr $(NSPR_LIBS) $(WIN32_LIBS)
nspr_test$(binext): nspr_test.o libborg.a

fs_test$(binext): LINK = $(CXXLINK)
#fs_test$(binext): LDFLAGS += -static
fs_test$(binext): LIBS += -L$(bindir) -lrecls.1.gcc40 -lboost_filesystem $(LINUX_LIBS)
fs_test$(binext): fs_test.o libborg.a

nlp_test$(binext): LINK = $(CXXLINK)
nlp_test$(binext): LIBS += -L$(bindir)
nlp_test$(binext): nlp_test.o libborg.a

libxml2_test$(binext): LINK = $(CXXLINK)
libxml2_test$(binext) libxml2_test.ii: CPPFLAGS += -I$(includedir)/libxml2
libxml2_test$(binext): LIBS += -L$(bindir) -lxml2
libxml2_test$(binext): libxml2_test.o libborg.a

wxxml_test$(binext): LINK = $(CXXLINK)
wxxml_test$(binext) wxxml_test.ii: CPPFLAGS += $(WX_CFLAGS)
wxxml_test$(binext): LIBS += $(WX_LIBS)
wxxml_test$(binext): wxxml_test.o libborg.a

ifeq ($(system), mingw32)
xpath_shell%: CXX = i686-pc-cygwin-g++
xpath_shell%: CXXLINK = i686-pc-cygwin-g++
xpath_shell%: CPPFLAGS += -DBOOST_HAS_DECLSPEC -DBOOST_ALL_DYN_LINK -D_WIN32
endif
xpath_shell%: CPPFLAGS += $(LIBXML2_CFLAGS)
xpath_shell$(binext): LIBS += -lboost_program_options -lboost_filesystem -lxml2 -lreadline -lhistory
xpath_shell$(binext): LINK = $(CXXLINK)
xpath_shell$(binext): xpath_shell.o libborg.a 

http_test%: CPPFLAGS += $(LIBXML2_CFLAGS) $(WX_CFLAGS)
http_test$(binext): LIBS += $(LIBXML2_LIBS) $(XERCES_LIBS) $(WX_LIBS)
http_test$(binext): LINK = $(CXXLINK)
http_test$(binext): http_test.o libborg.a 

spirit_test$(binext): LINK = $(CXXLINK)
#spirit_test$(binext): LIBS += -lboost_spirit
spirit_test$(binext): spirit_test.o libborg.a 

#regex_test%: CPPFLAGS += $(LIBXML2_CFLAGS)
regex_test$(binext): LINK = $(CXXLINK)
regex_test$(binext): CXXFLAGS += $(WX_CFLAGS) $(LIBXML2_CFLAGS)
regex_test$(binext): LIBS += -lboost_regex -ljuce -lxml2 -lxerces-c $(WX_LIBS) 
#$(libdir)/libjs.a -L$(bindir) -lnspr4
regex_test$(binext): regex_test.o 

tokenizer_test.o: CXXFLAGS += -DLINUX $(WX_CFLAGS) $(LIBXML2_CFLAGS)
tokenizer_test$(binext): LINK = $(CXXLINK)
tokenizer_test$(binext): LIBS += -ljuce -lxml2 -lxerces-c $(WX_LIBS) 
#$(libdir)/libjs.a -L$(bindir) -lnspr4
tokenizer_test$(binext): tokenizer_test.o

php_test$(binext): LINK = $(CXXLINK)
php_test.o: WARNINGS += no-deprecated
php_test.o: CPPFLAGS += $(PHP_CFLAGS)

zipios_test.o: zipios_test.cpp
zipios_test$(binext): zipios_test.o
zipios_test$(binext): LINK = $(CXXLINK)
zipios_test$(binext): LIBS = -L$(bindir) -lzipios

aterm_test.o: aterm_test.cpp
aterm_test$(binext): aterm_test.o
aterm_test$(binext): LINK = $(CXXLINK)
aterm_test$(binext): LIBS = -L$(bindir) -lATerm

juce_test.o: juce_test.cpp
juce_test$(binext): juce_test.o
juce_test$(binext): LINK = $(CXXLINK)
juce_test$(binext): LIBS = -L$(bindir) -ljuce

tk_test.o: tk_test.cpp
tk_test.o: CXXFLAGS += $(WX_CFLAGS)
tk_test$(binext): tk_test.o
tk_test$(binext): LINK = $(CXXLINK)
tk_test$(binext): LIBS += $(WX_LIBS)

ifeq ($(system), mingw32)
php_test$(binext): LIBS += -L$(bindir) -lphp5ts
else
php_test$(binext): LIBS += -L$(libdir) -lphp5 -ldl
endif

php_test$(binext): php_test.o libborg.a 

net_test$(binext) file_test$(binext): LINK = $(CXXLINK)
#net_test%: WARNINGS += no-deprecated
net_test.o: CPPFLAGS += $(APR_CFLAGS)
#net_test%: LIBS += -L$(bindir) -lphp5ts

ifeq ($(system), mingw32)
net_test$(binext) file_test$(binext): LIBS += -L$(bindir) $(NSPR_LIBS) $(APR_LIBS)
else
net_test$(binext) file_test$(binext): LIBS += $(NSPR_LIBS) $(APR_LIBS)
endif
net_test$(binext): net_test.o libborg.a

file_test.o: CFLAGS += $(APR_CFLAGS)
file_test$(binext): LIBS += -L$(bindir) -lapr
file_test$(binext): file_test.o libborg.a

libs/zend/tsrm.o: libs/zend/tsrm.c
libs/zend/tsrm.o: CPPFLAGS += -I$(includedir)/php/Zend

#vsttest.$(slibext): LIBS += -lgdiplus
#$(borg_PROGRAMS): LINK = $(CXXLINK)
#$(borg_PROGRAMS): %$(binext): %.c libborg.a

yaml_test.o: CPPFLAGS += -DYAML_DECLARE_STATIC
yaml_test$(binext): LIBS += $(libdir)/libyaml.a
yaml_test$(binext): yaml_test.o

template_test$(binext): template_test.o

%_test.o: %_test.cpp
%_test$(binext): LINK = $(CXXLINK)
%_test$(binext): %_test.o

%.hpp: ;
%.cpp: ;

# test suite
# ---------------------------------------------------------------------------
test$(binext): LINK = $(CXXLINK)
test$(binext): LIBS += -lboost_unit_test_framework
test$(binext): $(test_OBJECTS)

# wrap library
# ---------------------------------------------------------------------------
wrap_SOURCES = $(wildcard wrap/*.hpp)
wrap_TESTS = $(patsubst %.cpp,%$(binext),$(wildcard wrap/*.cpp))

$(wrap_TESTS): %$(binext): %.o
