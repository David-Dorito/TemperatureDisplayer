#ifndef _DEFINITIONS_H_
#define _DEFINITIONS_H_

#include <stddef.h>
#include <stdint.h>

#define HIGH                                1
#define LOW                                 0
#define TRUE                                1
#define FALSE                               0
#define ENABLE                              1
#define DISABLE                             0

#define WEAK                                __attribute__((weak))

typedef int64_t                             i64;
typedef int32_t                             i32;
typedef int16_t                             i16;
typedef int8_t                              i8;
typedef uint64_t                            u64;
typedef uint32_t                            u32;
typedef uint16_t                            u16;
typedef uint8_t                             u8;

#endif