#!/usr/bin/cmake -P

# Usage:
# - cmake script mode: cmake -P gl3w_gen.cmake or ./gl3w_gen.cmake
# - from a cmake project: include(gl3w_gen) then gl3w_gen(OUTPUT_PATH)
# Pavel Rojtberg 2016

function(gl3w_gen OUTDIR)
set(UNLICENSE
"/*

    This file was generated with gl3w_gen.cmake, part of glXXw
    (hosted at https://github.com/paroj/glXXw-cmake)

    This is free and unencumbered software released into the public domain.

    Anyone is free to copy, modify, publish, use, compile, sell, or
    distribute this software, either in source code form or as a compiled
    binary, for any purpose, commercial or non-commercial, and by any
    means.

    In jurisdictions that recognize copyright laws, the author or authors
    of this software dedicate any and all copyright interest in the
    software to the public domain. We make this dedication for the benefit
    of the public at large and to the detriment of our heirs and
    successors. We intend this dedication to be an overt act of
    relinquishment in perpetuity of all present and future rights to this
    software under copyright law.

    THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
    IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
    OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
    ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
    OTHER DEALINGS IN THE SOFTWARE.

*/\n
")

file(MAKE_DIRECTORY ${OUTDIR}/include/GL)
file(MAKE_DIRECTORY ${OUTDIR}/include/KHR)
file(MAKE_DIRECTORY ${OUTDIR}/src)

if(NOT EXISTS ${OUTDIR}/include/GL/glcorearb.h)
    message(STATUS "Downloading glcorearb.h to include/GL...")
    file(DOWNLOAD
        https://www.khronos.org/registry/OpenGL/api/GL/glcorearb.h
        ${OUTDIR}/include/GL/glcorearb.h)
else()
    message(STATUS "Reusing glcorearb.h from include/GL...")
endif()

if(NOT EXISTS ${OUTDIR}/include/KHR/khrplatform.h)
    message(STATUS "Downloading khrplatform.h to include/KHR...")
    file(DOWNLOAD
        https://www.khronos.org/registry/EGL/api/KHR/khrplatform.h
        ${OUTDIR}/include/KHR/khrplatform.h)
else()
    message(STATUS "Reusing glcorearb.h from include/GL...")
endif()
message(STATUS "Parsing glcorearb.h header...")

file(STRINGS ${OUTDIR}/include/GL/glcorearb.h GLCOREARB)

foreach(LINE ${GLCOREARB})
    string(REGEX MATCH "GLAPI.*APIENTRY[ ]+([a-zA-Z0-9_]+)" MATCHES ${LINE})
    if(MATCHES)
        list(APPEND PROCS ${CMAKE_MATCH_1})
    endif()
endforeach()

list(SORT PROCS)

set(SPACES "                                                    ") # 52 spaces

macro(getproctype PROC)
    string(TOUPPER ${PROC} P_T)
    set(P_T "PFN${P_T}PROC")
endmacro()

macro(getproctype_aligned PROC)
    getproctype(${PROC})
    string(LENGTH ${P_T} LEN)
    math(EXPR LEN "52 - ${LEN}")
    if (LEN LESS 0)
        set(LEN 0)
    endif()
    string(SUBSTRING ${SPACES} 0 ${LEN} PAD)
    set(P_T "${P_T}${PAD}")
endmacro()

macro(getprocsignature PROC)
    string(SUBSTRING ${PROC} 2 -1 P_S)
    set(P_S "gl3w${P_S}")
endmacro()

message(STATUS "Generating gl3w.h in include/GL...")

set(HDR_OUT ${OUTDIR}/include/GL/gl3w.h)
file(WRITE ${HDR_OUT} ${UNLICENSE})
file(APPEND ${HDR_OUT}
"#ifndef __gl3w_h_
#define __gl3w_h_

#include <GL/glcorearb.h>

#ifndef __gl_h_
#define __gl_h_
#endif

#ifdef __cplusplus
extern \"C\" {
#endif

typedef void (*GL3WglProc)(void);
typedef GL3WglProc (*GL3WGetProcAddressProc)(const char *proc);

/* gl3w api */
int gl3wInit(void);
int gl3wInit2(GL3WGetProcAddressProc proc);
int gl3wIsSupported(int major, int minor);
GL3WglProc gl3wGetProcAddress(const char *proc);

/* OpenGL functions */
")

foreach(PROC ${PROCS})
    getprocsignature(${PROC})
    getproctype_aligned(${PROC})
    file(APPEND ${HDR_OUT} "extern ${P_T} ${P_S};\n")
endforeach()

foreach(PROC ${PROCS})
    string(SUBSTRING ${PROC} 2 -1 P_S)
    string(LENGTH ${PROC} LEN)
    math(EXPR LEN "45 - ${LEN}")
    if (LEN LESS 0)
        set(LEN 0)
    endif()
    string(SUBSTRING ${SPACES} 0 ${LEN} PAD)
    file(APPEND ${HDR_OUT} "#define ${PROC}${PAD} gl3w${P_S}\n")
endforeach()

file(APPEND ${HDR_OUT}
"
#ifdef __cplusplus
}
#endif

#endif
")

message(STATUS "Generating gl3w.c in src...")
set(SRC_OUT ${OUTDIR}/src/gl3w.c)
file(WRITE ${SRC_OUT} ${UNLICENSE})
file(APPEND ${SRC_OUT} "#include <GL/gl3w.h>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>

static HMODULE libgl;

static void open_libgl(void)
{
	libgl = LoadLibraryA(\"opengl32.dll\");
}

static void close_libgl(void)
{
	FreeLibrary(libgl);
}

static GL3WglProc get_proc(const char *proc)
{
	GL3WglProc res;

	res = (GL3WglProc)wglGetProcAddress(proc);
	if (!res)
		res = (GL3WglProc)GetProcAddress(libgl, proc);
	return res;
}
#elif defined(__APPLE__) || defined(__APPLE_CC__)
#include <Carbon/Carbon.h>

CFBundleRef bundle;
CFURLRef bundleURL;

static void open_libgl(void)
{
	bundleURL = CFURLCreateWithFileSystemPath(kCFAllocatorDefault,
		CFSTR(\"/System/Library/Frameworks/OpenGL.framework\"),
		kCFURLPOSIXPathStyle, true);

	bundle = CFBundleCreate(kCFAllocatorDefault, bundleURL);
	assert(bundle != NULL);
}

static void close_libgl(void)
{
	CFRelease(bundle);
	CFRelease(bundleURL);
}

static GL3WglProc get_proc(const char *proc)
{
	GL3WglProc res;

	CFStringRef procname = CFStringCreateWithCString(kCFAllocatorDefault, proc,
		kCFStringEncodingASCII);
	*(void **)(&res) = CFBundleGetFunctionPointerForName(bundle, procname);
	CFRelease(procname);
	return res;
}
#else
#include <dlfcn.h>
#include <GL/glx.h>

static void *libgl;
static PFNGLXGETPROCADDRESSPROC glx_get_proc_address;

static void open_libgl(void)
{
	libgl = dlopen(\"libGL.so.1\", RTLD_LAZY | RTLD_GLOBAL);
    *(void **)(&glx_get_proc_address) = dlsym(libgl, \"glXGetProcAddressARB\");
}

static void close_libgl(void)
{
	dlclose(libgl);
}

static GL3WglProc get_proc(const char *proc)
{
	GL3WglProc res;

	res = glx_get_proc_address((const GLubyte *)proc);
    if (!res)
		*(void **)(&res) = dlsym(libgl, proc);
	return res;
}
#endif

static struct {
	int major, minor;
} version;

static int parse_version(void)
{
	if (!glGetIntegerv)
		return -1;

	glGetIntegerv(GL_MAJOR_VERSION, &version.major);
	glGetIntegerv(GL_MINOR_VERSION, &version.minor);

	if (version.major < 3)
		return -1;
	return 0;
}

static void load_procs(GL3WGetProcAddressProc proc);

int gl3wInit(void)
{
	open_libgl();
	load_procs(get_proc);
	close_libgl();
	return parse_version();
}

int gl3wInit2(GL3WGetProcAddressProc proc)
{
	load_procs(proc);
	return parse_version();
}

int gl3wIsSupported(int major, int minor)
{
	if (major < 3)
		return 0;
	if (version.major == major)
		return version.minor >= minor;
	return version.major >= major;
}

GL3WglProc gl3wGetProcAddress(const char *proc)
{
	return get_proc(proc);
}

")

foreach(PROC ${PROCS})
    getprocsignature(${PROC})
    getproctype_aligned(${PROC})
    file(APPEND ${SRC_OUT} "${P_T} ${P_S};\n")
endforeach()

file(APPEND ${SRC_OUT} "
static void load_procs(GL3WGetProcAddressProc proc)
{\n")

foreach(PROC ${PROCS})
    getprocsignature(${PROC})
    getproctype(${PROC})
    file(APPEND ${SRC_OUT} "\t${P_S} = (${P_T})proc(\"${PROC}\");\n")
endforeach()

file(APPEND ${SRC_OUT} "}\n")
endfunction()

if(NOT CMAKE_PROJECT_NAME)
    gl3w_gen(".")
endif()
