#ifndef _COMPILE_H_
#define _COMPILE_H_


///
/// Unit: preprocessor constants
///


#ifndef EXTERN_C
    #define EXTERN_C extern "C"
#endif







///
/// Unit: DLL_EXPORT and DLL_IMPORT
///
#if defined(_MSC_VER)
    // Microsoft
    #define DLL_EXPORT __declspec(dllexport)
    #define DLL_IMPORT __declspec(dllimport)

    #ifndef snprintf
        #define snprintf _snprintf
    #endif


#elif defined(__GNUC__)
    #ifndef __FUNCTION__
        #define __FUNCTION__ __func__
    #endif

    // GCC
    #define DLL_LOCAL  __attribute__((visibility("hidden")))
    #define DLL_EXPORT __attribute__((visibility("default")))
    #define DLL_IMPORT
    //#define EXPORT __declspec(dllexport)
    //#define IMPORT __declspec(dllimport)





#else
	#warning Undefined compilator. Some keywords may be not recognized





    // do nothing and hope for the best?
    #define DLL_EXPORT
    #define DLL_IMPORT
    #pragma warning Unknown dynamic link import/export semantics.
#endif



///
/// Unit: Call Declaration
/// Items: CDECL_cdecl, CDECL_stdcall
///
#define CDECL_stdcall __stdcall











#define ATTR_STORAGE_COMMON __attribute__((common))

#define ATTR_SECTION(str_name)	__attribute__((section(str_name)))
#define ATTR_SECTION_CODE		ATTR_SECTION(".text")
#define ATTR_SECTION_DATA		ATTR_SECTION(".data")
#define ATTR_SECTION_DATA_ZERO	ATTR_SECTION(".bss")



#define ATTR_F_CONST		__attribute__ ((const))






#define ASSERT_NDEBUG NDEBUG





#ifdef NDEBUG
	#define DEBUG_POINT(msg)
#else
	#define DEBUG_POINT(msg) fprintf(stderr, "\e[33mDEBUG:\e[0m" __FILE__ ":"  \
									 ":%d:\e[36m%s\e[0m() \e[91m%s\e[0m\n", \
									 __LINE__, __FUNCTION__, #msg)
#endif









#endif // _COMPILE_H_
