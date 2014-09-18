#
# This Makefile requires GNU make.
#
# Do not make changes here.
# Use the included .mak files.
#

it: all

CC = $(error Please use ./configure first)

SHARED_LIBS := libskarnet.so
STATIC_LIBS := libskarnet.a

include package/deps.mak
-include config.mak

version_m := $(basename $(version))
version_M := $(basename $(version_m))
version_l := $(basename $(version_M))
CPPFLAGS_ALL := -Isrc/include $(CPPFLAGS)
CFLAGS_ALL := $(CFLAGS) -pipe -Wall
CFLAGS_SHARED := -fPIC
LDFLAGS_ALL := $(LDFLAGS)
LDFLAGS_SHARED := -shared
LDLIBS_ALL := $(LDLIBS)
REALCC = $(CROSS_COMPILE)$(CC)
AR := $(CROSS_COMPILE)ar
RANLIB := $(CROSS_COMPILE)ranlib
STRIP := $(CROSS_COMPILE)strip
INSTALL := ./tools/install.sh

ALL_SRCS := $(wildcard src/lib*/*.c)
ALL_SOBJS := $(ALL_SRCS:%.c=%.o)
ALL_DOBJS := $(ALL_SRCS:%.c=%.lo)
ALL_LIBS := $(SHARED_LIBS) $(STATIC_LIBS)
ALL_INCLUDES := $(wildcard src/include/$(package)/*.h)
BUILT_INCLUDES := \
src/include/$(package)/sysdeps.h \
src/include/$(package)/uint16.h \
src/include/$(package)/uint32.h \
src/include/$(package)/uint64.h \
src/include/$(package)/ushort.h \
src/include/$(package)/uint.h \
src/include/$(package)/ulong.h \
src/include/$(package)/error.h \
src/include/$(package)/gidstuff.h \
src/include/$(package)/ip46.h \
src/include/$(package)/setgroups.h
ALL_SYSDEPS := $(wildcard $(sysdeps)/*)
ALL_DATA := $(wildcard src/etc/*)

all: $(ALL_LIBS) $(ALL_INCLUDES) $(ALL_SYSDEPS) $(ALL_DATA)

clean:
	@exec rm -f $(ALL_LIBS) $(ALL_BINS) $(ALL_SOBJS) $(ALL_DOBJS) $(BUILT_INCLUDES)

distclean: clean
	@exec rm -rf config.mak src/include/${package}/config.h sysdeps.cfg

tgz: distclean
	@. package/info && \
        rm -rf /tmp/$$package-$$version && \
        cp -a .  /tmp/$$package-$$version && \
        cd /tmp && \
	tar -zpcv --owner=0 --group=0 --numeric-owner -f /tmp/$$package-$$version.tar.gz $$package-$$version && \
	exec rm -rf /tmp/$$package-$$version

strip: $(ALL_LIBS)
	exec ${STRIP} -x -R .note -R .comment -R .note.GNU-stack $(ALL_LIBS)

install: install-data install-sysdeps install-dynlib install-lib install-include
install-data: $(ALL_DATA:src/etc/%=$(DESTDIR)$(datadir)/%)
install-sysdeps: $(ALL_SYSDEPS:$(sysdeps)/%=$(DESTDIR)$(sysdepdir)/%)
install-dynlib: $(SHARED_LIBS:lib%.so=$(DESTDIR)$(dynlibdir)/lib%.so)
install-lib: $(STATIC_LIBS:lib%.a=$(DESTDIR)$(libdir)/lib%.a)
install-include: $(ALL_INCLUDES:src/include/$(package)/%.h=$(DESTDIR)$(includedir)/$(package)/%.h)

ifneq ($(exthome),)

update:
	exec $(INSTALL) -l $(notdir $(home)) $(DESTDIR)$(exthome)

global-links: $(DESTDIR)$(exthome) $(SHARED_LIBS:lib%.so=$(DESTDIR)$(sproot)/library.so/lib%.so)

$(DESTDIR)$(sproot)/library.so/lib%.so: $(DESTDIR)$(home)/library.so/lib%.so
	exec $(INSTALL) -D -l ..$(exthome)/library.so/$(<F) $@

.PHONY: update global-links

endif

$(DESTDIR)$(datadir)/%: src/etc/%
	exec $(INSTALL) -D -m 644 $< $@

$(DESTDIR)$(sysdepdir)/%: $(sysdeps)/%
	exec $(INSTALL) -D -m 644 $< $@

$(DESTDIR)$(dynlibdir)/%.so: %.so
	$(INSTALL) -D -m 755 $< $@.$(version) && \
	$(INSTALL) -l $<.$(version) $@.$(version_m) && \
	$(INSTALL) -l $<.$(version_m) $@.$(version_M) && \
	$(INSTALL) -l $<.$(version_M) $@.$(version_l) && \
	exec $(INSTALL) -l $<.$(version_l) $@

$(DESTDIR)$(libdir)/lib%.a: lib%.a
	exec $(INSTALL) -D -m 644 $< $@

$(DESTDIR)$(includedir)/$(package)/%.h: src/include/$(package)/%.h
	exec $(INSTALL) -D -m 644 $< $@

%.o: %.c
	exec $(REALCC) $(CPPFLAGS_ALL) $(CFLAGS_ALL) -c -o $@ $<

%.lo: %.c
	exec $(REALCC) $(CPPFLAGS_ALL) $(CFLAGS_ALL) $(CFLAGS_SHARED) -c -o $@ $<

libskarnet.a: $(ALL_SOBJS)
	exec $(AR) rc $@ $^
	exec $(RANLIB) $@

libskarnet.so: $(ALL_DOBJS)
	exec $(REALCC) -o $@ $(CFLAGS_ALL) $(CFLAGS_SHARED) $(LDFLAGS_ALL) $(LDFLAGS_SHARED) -Wl,-soname,$@.$(version_l) $^

.PHONY: it all clean distclean tgz strip install install-data install-sysdeps install-dynlib install-lib install-include

.DELETE_ON_ERROR:

src/include/${package}/sysdeps.h: $(sysdeps)/sysdeps.h
	exec cat < $< > $@

src/include/${package}/uint16.h: src/include/${package}/uint64.h $(sysdeps)/sysdeps src/headers/uint16-header src/headers/uint16-footer src/headers/uint16-lendian src/headers/uint16-bendian
	@{ \
	  cat src/headers/uint16-header ; \
	  if grep -qF 'endianness: little' $(sysdeps)/sysdeps ; then cat src/headers/uint16-lendian ; \
	  elif grep -qF 'endianness: big' $(sysdeps)/sysdeps ; then cat src/headers/uint16-bendian ; \
	  else echo 'Error ! Unsupported endianness' 1>&2 ; ./crash ; \
	  fi ; \
	  exec cat src/headers/uint16-footer ; \
	} > $@

src/include/${package}/uint32.h: src/include/${package}/uint64.h $(sysdeps)/sysdeps src/headers/uint32-header src/headers/uint32-footer src/headers/uint32-lendian src/headers/uint32-bendian
	@{ \
	  cat src/headers/uint32-header ; \
	  if grep -qF 'endianness: little' $(sysdeps)/sysdeps ; then cat src/headers/uint32-lendian ; \
	  elif grep -qF 'endianness: big' $(sysdeps)/sysdeps ; then cat src/headers/uint32-bendian ; \
	  else echo 'Error ! Unsupported endianness' 1>&2 ; ./crash ; \
	  fi ; \
	  exec cat src/headers/uint32-footer ; \
	} > $@

src/include/${package}/uint64.h: $(sysdeps)/sysdeps src/headers/uint64-header src/headers/uint64-footer src/headers/uint64-ulong64 src/headers/uint64-noulong64 src/headers/uint64-lendian src/headers/uint64-bendian
	@{ \
	  cat src/headers/uint64-header ; \
	  if grep -qF 'uint64t: yes' $(sysdeps)/sysdeps ; then cat src/headers/uint64-stdinth ; \
	  elif grep -qF 'sizeofulong: 8' $(sysdeps)/sysdeps ; then cat src/headers/uint64-ulong64 ; \
	  else cat uint64-noulong64 ; \
	  fi ; \
	  if grep -qF 'endianness: little' $(sysdeps)/sysdeps ; then cat src/headers/uint64-lendian ; \
	  elif grep -qF 'endianness: big' $(sysdeps)/sysdeps ; then cat src/headers/uint64-bendian ; \
	  else echo 'Error ! Unsupported endianness' 1>&2 ; ./crash ; \
	  fi ; \
	  exec cat src/headers/uint64-footer ; \
	} > $@

src/include/${package}/ushort.h: src/include/${package}/uint16.h src/include/${package}/uint32.h $(sysdeps)/sysdeps src/headers/ushort-header src/headers/ushort-footer src/headers/ushort-16 src/headers/ushort-32
	@{ \
	  cat src/headers/ushort-header ; \
	  if grep -qF 'sizeofushort: 2' $(sysdeps)/sysdeps ; then cat src/headers/ushort-16 ; \
	  elif grep -qF 'sizeofushort: 4' $(sysdeps)/sysdeps ; then cat src/headers/ushort-32 ; \
	  else echo 'Error ! Unsupported unsigned short size' 1>&2 ; ./crash ; \
	  fi ; \
	  exec cat src/headers/ushort-footer ; \
	} > $@

src/include/${package}/uint.h: src/include/${package}/uint16.h src/include/${package}/uint32.h src/include/${package}/uint64.h $(sysdeps)/sysdeps src/headers/uint-header src/headers/uint-footer src/headers/uint-16 src/headers/uint-32 src/headers/uint-64
	@{ \
	  cat src/headers/uint-header ; \
	  if grep -qF 'sizeofuint: 2' $(sysdeps)/sysdeps ; then cat src/headers/uint-16 ; \
	  elif grep -qF 'sizeofuint: 4' $(sysdeps)/sysdeps ; then cat src/headers/uint-32 ; \
	  elif grep -qF 'sizeofuint: 8' $(sysdeps)/sysdeps ; then cat src/headers/uint-64 ; \
	  else echo 'Error ! Unsupported unsigned int size' 1>&2 ; ./crash ; \
	  fi ; \
	  exec cat src/headers/uint-footer ; \
	} > $@

src/include/${package}/ulong.h: src/include/${package}/uint32.h src/include/${package}/uint64.h $(sysdeps)/sysdeps src/headers/ulong-header src/headers/ulong-footer src/headers/ulong-32 src/headers/ulong-64
	@{ \
	  cat src/headers/ulong-header ; \
	  if grep -qF 'sizeofulong: 4' $(sysdeps)/sysdeps ; then cat src/headers/ulong-32 ; \
	  elif grep -qF 'sizeofulong: 8' $(sysdeps)/sysdeps ; then cat src/headers/ulong-64 ; \
	  else echo 'Error ! Unsupported unsigned long size' 1>&2 ; ./crash ; \
	  fi ; \
	  exec cat src/headers/ulong-footer ; \
	} > $@

src/include/${package}/error.h: src/include/${package}/gccattributes.h $(sysdeps)/sysdeps src/headers/error-addrinuse src/headers/error-already src/headers/error-proto src/headers/error-header src/headers/error-footer
	@{ \
	  cat src/headers/error-header ; \
	  if grep -F target: $(sysdeps)/sysdeps | grep -qiF bsd ; then cat src/headers/error-addrinuse ; \
	  else cat src/headers/error-already ; \
	  fi ; \
	  if grep -qF 'eproto: yes' $(sysdeps)/sysdeps ; then : ; \
	  else cat src/headers/error-proto ; \
	  fi ; \
	  exec cat src/headers/error-footer ; \
	} > $@

src/include/${package}/gidstuff.h: src/include/${package}/uint16.h src/include/${package}/uint32.h src/include/${package}/uint64.h $(sysdeps)/sysdeps src/headers/gidstuff-header src/headers/gidstuff-footer src/headers/gidstuff-16 src/headers/gidstuff-32 src/headers/gidstuff-64
	@{ \
	  cat src/headers/gidstuff-header ; \
	  if grep -qF 'sizeofgid: 2' $(sysdeps)/sysdeps ; then cat src/headers/gidstuff-16 ; \
	  elif grep -qF 'sizeofgid: 4' $(sysdeps)/sysdeps ; then cat src/headers/gidstuff-32 ; \
	  elif grep -qF 'sizeofgid: 8' $(sysdeps)/sysdeps ; then cat src/headers/gidstuff-64 ; \
	  else echo 'Error ! Unsupported gid_t size' 1>&2 ; ./crash ; \
	  fi ; \
	  exec cat src/headers/gidstuff-footer ; \
	} > $@

src/include/${package}/ip46.h: src/include/${package}/uint16.h src/include/${package}/bytestr.h src/include/${package}/fmtscan.h src/include/${package}/tai.h src/include/${package}/socket.h $(sysdeps)/sysdeps src/headers/ip46-header src/headers/ip46-footer src/headers/ip46-with src/headers/ip46-without
	@{ \
	  cat src/headers/ip46-header ; \
	  if $(ipv6) && grep -qF 'ipv6: yes' $(sysdeps)/sysdeps ; then cat src/headers/ip46-with ; \
	  else cat src/headers/ip46-without ; \
	  fi ; \
	  exec cat src/headers/ip46-footer ; \
	} > $@

src/include/${package}/setgroups.h: $(sysdeps)/sysdeps src/headers/setgroups-header src/headers/setgroups-footer src/headers/setgroups-stub
	@{ \
	  cat src/headers/setgroups-header ; \
	  if grep -qF 'setgroups: yes' $(sysdeps)/sysdeps ; then : ; \
	  else cat src/headers/setgroups-stub ; \
	  fi ; \
	  exec cat src/headers/setgroups-footer ; \
	} > $@
