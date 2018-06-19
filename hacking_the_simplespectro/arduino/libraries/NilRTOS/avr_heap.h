/* Arduino NilRTOS Library
 * Copyright (C) 2013 by William Greiman
 *
 * This file is part of the Arduino NilRTOS Library
 *
 * This Library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This Library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with the Arduino NilRTOS Library.  If not, see
 * <http://www.gnu.org/licenses/>.
 */
#ifndef avr_heap_h
#define avr_heap_h
#include <stdlib.h>
/* End of heap. */
extern char* __brkval;

#if defined(CORE_TEENSY) || ARDUINO == 104 || ARDUINO == 152
extern char __bss_end;

/** @return Address of first byte after the heap. */
static inline char* heapEnd() {
  return __brkval ? __brkval : &__bss_end;
}
/** @return Size of heap and idle thread stack in bytes. */
static inline size_t nilHeapIdleSize() {
  return (char*)RAMEND - &__bss_end + 1;
}
#else  // CORE_TEENSY
/** @return Address of first byte after the heap. */
static inline char* heapEnd() {
 return __brkval ? __brkval : __malloc_heap_start;
}
/** @return Size of heap and idle thread stack in bytes. */
static inline size_t nilHeapIdleSize() {
  return (char*)RAMEND - __malloc_heap_start + 1;
}
#endif  // CORE_TEENSY
//------------------------------------------------------------------------------
#ifndef __DOXYGEN__
static __attribute__((noinline))
#endif  // __DOXYGEN__
size_t fillSize(uint8_t* bgn, uint8_t* end) {
  uint8_t* p = bgn;
  while (p < end && *p == 0X55) p++;
  return p - bgn;
}
#endif // avr_heap_h