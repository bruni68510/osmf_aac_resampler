/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.4
 * 
 * This file is not intended to be easily readable and contains a number of 
 * coding conventions designed to improve portability and efficiency. Do not make
 * changes to this file unless you know what you are doing--modify the SWIG 
 * interface file instead. 
 * ----------------------------------------------------------------------------- */

#ifdef __cplusplus
/* SwigValueWrapper is described in swig.swg */
template<typename T> class SwigValueWrapper {
  struct SwigMovePointer {
    T *ptr;
    SwigMovePointer(T *p) : ptr(p) { }
    ~SwigMovePointer() { delete ptr; }
    SwigMovePointer& operator=(SwigMovePointer& rhs) { T* oldptr = ptr; ptr = 0; delete oldptr; ptr = rhs.ptr; rhs.ptr = 0; return *this; }
  } pointer;
  SwigValueWrapper& operator=(const SwigValueWrapper<T>& rhs);
  SwigValueWrapper(const SwigValueWrapper<T>& rhs);
public:
  SwigValueWrapper() : pointer(0) { }
  SwigValueWrapper& operator=(const T& t) { SwigMovePointer tmp(new T(t)); pointer = tmp; return *this; }
  operator T&() const { return *pointer.ptr; }
  T *operator&() { return pointer.ptr; }
};

template <typename T> T SwigValueInit() {
  return T();
}
#endif

/* -----------------------------------------------------------------------------
 *  This section contains generic SWIG labels for method/variable
 *  declarations/attributes, and other compiler dependent labels.
 * ----------------------------------------------------------------------------- */

/* template workaround for compilers that cannot correctly implement the C++ standard */
#ifndef SWIGTEMPLATEDISAMBIGUATOR
# if defined(__SUNPRO_CC) && (__SUNPRO_CC <= 0x560)
#  define SWIGTEMPLATEDISAMBIGUATOR template
# elif defined(__HP_aCC)
/* Needed even with `aCC -AA' when `aCC -V' reports HP ANSI C++ B3910B A.03.55 */
/* If we find a maximum version that requires this, the test would be __HP_aCC <= 35500 for A.03.55 */
#  define SWIGTEMPLATEDISAMBIGUATOR template
# else
#  define SWIGTEMPLATEDISAMBIGUATOR
# endif
#endif

/* inline attribute */
#ifndef SWIGINLINE
# if defined(__cplusplus) || (defined(__GNUC__) && !defined(__STRICT_ANSI__))
#   define SWIGINLINE inline
# else
#   define SWIGINLINE
# endif
#endif

/* attribute recognised by some compilers to avoid 'unused' warnings */
#ifndef SWIGUNUSED
# if defined(__GNUC__)
#   if !(defined(__cplusplus)) || (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))
#     define SWIGUNUSED __attribute__ ((__unused__)) 
#   else
#     define SWIGUNUSED
#   endif
# elif defined(__ICC)
#   define SWIGUNUSED __attribute__ ((__unused__)) 
# else
#   define SWIGUNUSED 
# endif
#endif

#ifndef SWIG_MSC_UNSUPPRESS_4505
# if defined(_MSC_VER)
#   pragma warning(disable : 4505) /* unreferenced local function has been removed */
# endif 
#endif

#ifndef SWIGUNUSEDPARM
# ifdef __cplusplus
#   define SWIGUNUSEDPARM(p)
# else
#   define SWIGUNUSEDPARM(p) p SWIGUNUSED 
# endif
#endif

/* internal SWIG method */
#ifndef SWIGINTERN
# define SWIGINTERN static SWIGUNUSED
#endif

/* internal inline SWIG method */
#ifndef SWIGINTERNINLINE
# define SWIGINTERNINLINE SWIGINTERN SWIGINLINE
#endif

/* exporting methods */
#if (__GNUC__ >= 4) || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4)
#  ifndef GCC_HASCLASSVISIBILITY
#    define GCC_HASCLASSVISIBILITY
#  endif
#endif

#ifndef SWIGEXPORT
# if defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
#   if defined(STATIC_LINKED)
#     define SWIGEXPORT
#   else
#     define SWIGEXPORT __declspec(dllexport)
#   endif
# else
#   if defined(__GNUC__) && defined(GCC_HASCLASSVISIBILITY)
#     define SWIGEXPORT __attribute__ ((visibility("default")))
#   else
#     define SWIGEXPORT
#   endif
# endif
#endif

/* calling conventions for Windows */
#ifndef SWIGSTDCALL
# if defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
#   define SWIGSTDCALL __stdcall
# else
#   define SWIGSTDCALL
# endif 
#endif

/* Deal with Microsoft's attempt at deprecating C standard runtime functions */
#if !defined(SWIG_NO_CRT_SECURE_NO_DEPRECATE) && defined(_MSC_VER) && !defined(_CRT_SECURE_NO_DEPRECATE)
# define _CRT_SECURE_NO_DEPRECATE
#endif

/* Deal with Microsoft's attempt at deprecating methods in the standard C++ library */
#if !defined(SWIG_NO_SCL_SECURE_NO_DEPRECATE) && defined(_MSC_VER) && !defined(_SCL_SECURE_NO_DEPRECATE)
# define _SCL_SECURE_NO_DEPRECATE
#endif



#include <stdlib.h>
#include <string.h>
#include "AS3/AS3.h"
#define swig_as3(X) inline_as3("import com.adobe.flascc.swig.*; " X)


/* Contract support */

#define SWIG_contract_assert(expr, msg) if (!(expr)) {int msglen = strlen(msg);__asm__ volatile ("throw new Exception(CModule.readString(%0, %1))": : "r"(msg), "r"(msglen));}



#include "AACDecompress.h"

__attribute__((annotate("as3sig:public function _wrap_new_AACDecompress():int")))
void _wrap_new_AACDecompress() {
  AACDecompress *result ;
  
  result = (AACDecompress *)new AACDecompress();
  {
    AS3_DeclareVar(asresult, int);
    AS3_CopyScalarToVar(asresult, result);
  }
  {
    AS3_ReturnAS3Var(asresult);
  }
}


__attribute__((annotate("as3sig:public function _wrap_AACDecompress_decompress(self, data:int, size:int, out_size:int):int")))
void _wrap_AACDecompress_decompress() {
  AACDecompress *arg1 = (AACDecompress *) 0 ;
  unsigned char *arg2 = (unsigned char *) 0 ;
  int arg3 ;
  int *arg4 = (int *) 0 ;
  unsigned char *result ;
  
  {
    AS3_GetScalarFromVar(arg1, self);
  }
  {
    AS3_GetScalarFromVar(arg2, data);
  }
  {
    AS3_GetScalarFromVar(arg3, size);
  }
  {
    AS3_GetScalarFromVar(arg4, out_size);
  }
  result = (unsigned char *)(arg1)->decompress(arg2,arg3,arg4);
  {
    AS3_DeclareVar(asresult, int);
    AS3_CopyScalarToVar(asresult, result);
  }
  {
    AS3_ReturnAS3Var(asresult);
  }
}


__attribute__((annotate("as3sig:public function _wrap_AACDecompress_terminate(self, out_size:int):int")))
void _wrap_AACDecompress_terminate() {
  AACDecompress *arg1 = (AACDecompress *) 0 ;
  int *arg2 = (int *) 0 ;
  unsigned char *result ;
  
  {
    AS3_GetScalarFromVar(arg1, self);
  }
  {
    AS3_GetScalarFromVar(arg2, out_size);
  }
  result = (unsigned char *)(arg1)->terminate(arg2);
  {
    AS3_DeclareVar(asresult, int);
    AS3_CopyScalarToVar(asresult, result);
  }
  {
    AS3_ReturnAS3Var(asresult);
  }
}


__attribute__((annotate("as3sig:public function _wrap_delete_AACDecompress(self):void")))
void _wrap_delete_AACDecompress() {
  AACDecompress *arg1 = (AACDecompress *) 0 ;
  
  {
    AS3_GetScalarFromVar(arg1, self);
  }
  delete arg1;
  {
    
  }
  {
    AS3_ReturnAS3Var(undefined);
  }
}


__attribute__((annotate("as3sig:public function _wrap_AACDecompress_samplerate_set(self, samplerate:int):void")))
void _wrap_AACDecompress_samplerate_set() {
  AACDecompress *arg1 = (AACDecompress *) 0 ;
  unsigned long arg2 ;
  
  {
    AS3_GetScalarFromVar(arg1, self);
  }
  {
    AS3_GetScalarFromVar(arg2, samplerate);
  }
  if (arg1) (arg1)->samplerate = arg2;
  {
    
  }
  {
    AS3_ReturnAS3Var(undefined);
  }
}


__attribute__((annotate("as3sig:public function _wrap_AACDecompress_samplerate_get(self):int")))
void _wrap_AACDecompress_samplerate_get() {
  AACDecompress *arg1 = (AACDecompress *) 0 ;
  unsigned long result ;
  
  {
    AS3_GetScalarFromVar(arg1, self);
  }
  result = (unsigned long) ((arg1)->samplerate);
  {
    AS3_DeclareVar(asresult, int);
    AS3_CopyScalarToVar(asresult, result);
  }
  {
    AS3_ReturnAS3Var(asresult);
  }
}


__attribute__((annotate("as3sig:public function _wrap_AACDecompress_channels_set(self, channels:String):void")))
void _wrap_AACDecompress_channels_set() {
  AACDecompress *arg1 = (AACDecompress *) 0 ;
  unsigned char arg2 ;
  
  {
    AS3_GetScalarFromVar(arg1, self);
  }
  {
    inline_nonreentrant_as3(
      "%0 = channels.charCodeAt(0)" : "=r"(arg2)
      );
  }
  if (arg1) (arg1)->channels = arg2;
  {
    
  }
  {
    AS3_ReturnAS3Var(undefined);
  }
}


__attribute__((annotate("as3sig:public function _wrap_AACDecompress_channels_get(self):String")))
void _wrap_AACDecompress_channels_get() {
  AACDecompress *arg1 = (AACDecompress *) 0 ;
  unsigned char result ;
  
  {
    AS3_GetScalarFromVar(arg1, self);
  }
  result = (unsigned char) ((arg1)->channels);
  {
    AS3_DeclareVar(asresult, String);
    AS3_CopyCStringToVar(asresult, &result, 1);
  }
  {
    AS3_ReturnAS3Var(asresult);
  }
}



#include "AudioResampler.h"

__attribute__((annotate("as3sig:public function _wrap_new_AudioResampler(sample_rate_in:int, sample_rate_out:int, channels:int):int")))
void _wrap_new_AudioResampler() {
  int arg1 ;
  int arg2 ;
  int arg3 ;
  AudioResampler *result ;
  
  {
    AS3_GetScalarFromVar(arg1, sample_rate_in);
  }
  {
    AS3_GetScalarFromVar(arg2, sample_rate_out);
  }
  {
    AS3_GetScalarFromVar(arg3, channels);
  }
  result = (AudioResampler *)new AudioResampler(arg1,arg2,arg3);
  {
    AS3_DeclareVar(asresult, int);
    AS3_CopyScalarToVar(asresult, result);
  }
  {
    AS3_ReturnAS3Var(asresult);
  }
}


__attribute__((annotate("as3sig:public function _wrap_AudioResampler_bufferize(self, data_in:int, size:int):void")))
void _wrap_AudioResampler_bufferize() {
  AudioResampler *arg1 = (AudioResampler *) 0 ;
  unsigned char *arg2 = (unsigned char *) 0 ;
  int arg3 ;
  
  {
    AS3_GetScalarFromVar(arg1, self);
  }
  {
    AS3_GetScalarFromVar(arg2, data_in);
  }
  {
    AS3_GetScalarFromVar(arg3, size);
  }
  (arg1)->bufferize(arg2,arg3);
  {
    
  }
  {
    AS3_ReturnAS3Var(undefined);
  }
}


__attribute__((annotate("as3sig:public function _wrap_AudioResampler_process(self):void")))
void _wrap_AudioResampler_process() {
  AudioResampler *arg1 = (AudioResampler *) 0 ;
  
  {
    AS3_GetScalarFromVar(arg1, self);
  }
  (arg1)->process();
  {
    
  }
  {
    AS3_ReturnAS3Var(undefined);
  }
}


__attribute__((annotate("as3sig:public function _wrap_AudioResampler_flush(self, written:int):int")))
void _wrap_AudioResampler_flush() {
  AudioResampler *arg1 = (AudioResampler *) 0 ;
  int *arg2 = (int *) 0 ;
  unsigned char *result ;
  
  {
    AS3_GetScalarFromVar(arg1, self);
  }
  {
    AS3_GetScalarFromVar(arg2, written);
  }
  result = (unsigned char *)(arg1)->flush(arg2);
  {
    AS3_DeclareVar(asresult, int);
    AS3_CopyScalarToVar(asresult, result);
  }
  {
    AS3_ReturnAS3Var(asresult);
  }
}


__attribute__((annotate("as3sig:public function _wrap_delete_AudioResampler(self):void")))
void _wrap_delete_AudioResampler() {
  AudioResampler *arg1 = (AudioResampler *) 0 ;
  
  {
    AS3_GetScalarFromVar(arg1, self);
  }
  delete arg1;
  {
    
  }
  {
    AS3_ReturnAS3Var(undefined);
  }
}

