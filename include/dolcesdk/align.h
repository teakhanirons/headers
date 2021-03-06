#ifndef _DOLCESDKALIGN_H_
#define _DOLCESDKALIGN_H_

#ifdef  __cplusplus
extern "C" {
#endif

#if defined(_MSC_VER)
#define SCE_ALIGN(x) __declspec(align(x))
#else
#if defined(__GNUC__)
#define SCE_ALIGN(x) __attribute__ ((aligned(x)))
#endif
#endif

#ifdef __cplusplus
}
#endif
#endif
