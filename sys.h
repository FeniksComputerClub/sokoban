#ifdef CWDEBUG
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <libcwd/sys.h>
#endif

#ifdef __cplusplus
#define UNUSED(x)
#else
#define UNUSED(x) x
#endif

#ifndef CWDEBUG
#define NDEBUG
#endif

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef __INTEL_COMPILER
// Define this to avoid compiler bug.
#define _GCC_LIMITS_H_
#endif

// This allows us to use protected_notdocumented: instead of protected: in a class definition.
// The result is that the following methods will not appear in the doxygen documentation.
#define protected_notdocumented protected
// Same for public_notdocumented.
#define public_notdocumented public

#ifdef __i386
#define CW_MASK_T_CONST(x) x##ULL
#else
#ifdef __x86_64
#define CW_MASK_T_CONST(x) x##UL
#else
#error Unsupported architecture
#endif
#endif

// Compilers and preprocessor used.  Put here to cause a recompile when changed.
// CC    : Configured with: ../src/configure -v --with-pkgversion='Debian 4.4.4-8' --with-bugurl=file:///usr/share/doc/gcc-4.4/README.Bugs --enable-languages=c,c++,fortran,objc,obj-c++ --prefix=/usr --enable-shared --enable-multiarch --enable-linker-build-id --with-system-zlib --libexecdir=/usr/lib --without-included-gettext --enable-threads=posix --with-gxx-include-dir=/usr/include/c++/4.4 --program-suffix=-4.4 --enable-nls --enable-clocale=gnu --enable-libstdcxx-debug --enable-objc-gc --with-arch-32=i586 --with-tune=generic --enable-checking=release --build=x86_64-linux-gnu --host=x86_64-linux-gnu --target=x86_64-linux-gnu
// CXX   : Configured with: ../src/configure -v --with-pkgversion='Debian 4.4.4-8' --with-bugurl=file:///usr/share/doc/gcc-4.4/README.Bugs --enable-languages=c,c++,fortran,objc,obj-c++ --prefix=/usr --enable-shared --enable-multiarch --enable-linker-build-id --with-system-zlib --libexecdir=/usr/lib --without-included-gettext --enable-threads=posix --with-gxx-include-dir=/usr/include/c++/4.4 --program-suffix=-4.4 --enable-nls --enable-clocale=gnu --enable-libstdcxx-debug --enable-objc-gc --with-arch-32=i586 --with-tune=generic --enable-checking=release --build=x86_64-linux-gnu --host=x86_64-linux-gnu --target=x86_64-linux-gnu
// CXXCPP: Configured with: ../src/configure -v --with-pkgversion='Debian 4.4.4-8' --with-bugurl=file:///usr/share/doc/gcc-4.4/README.Bugs --enable-languages=c,c++,fortran,objc,obj-c++ --prefix=/usr --enable-shared --enable-multiarch --enable-linker-build-id --with-system-zlib --libexecdir=/usr/lib --without-included-gettext --enable-threads=posix --with-gxx-include-dir=/usr/include/c++/4.4 --program-suffix=-4.4 --enable-nls --enable-clocale=gnu --enable-libstdcxx-debug --enable-objc-gc --with-arch-32=i586 --with-tune=generic --enable-checking=release --build=x86_64-linux-gnu --host=x86_64-linux-gnu --target=x86_64-linux-gnu
//
// Also cause a full recompile when the definition of CWDEBUG is changed.
// CWDEBUG: yes
//
// Also cause a full recompile if CXXFLAGS is changed.
// CXXFLAGS: -g3 -DDEBUG
