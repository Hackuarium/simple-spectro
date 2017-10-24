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
/**
 * @file    NilRTOS.c
 * @brief   Nil RTOS Arduino library source file.
 *
 * @defgroup arduino Arduino
 * @details Arduino Nil RTOS library.
 * @{
 */

#include <NilRTOS.h>
#include <avr_heap.h>
//------------------------------------------------------------------------------
static __attribute__((noinline)) void fill8(uint8_t* bgn, uint8_t* end) {
  while (bgn < end) *bgn++ = 0X55;
}
//------------------------------------------------------------------------------
/**
 * @brief   Returns the semaphore counter current value.
 * @param[in] sp        pointer to a @p Semaphore structure.
 * @return the value of the semaphore counter.
 * @api
 */
cnt_t nilSemGetCounter(semaphore_t *sp) {
  nilSysLock();
  cnt_t cnt = sp->cnt;
  nilSysUnlock();
  return cnt;
}
//------------------------------------------------------------------------------
/**
 * Determine unused stack for a thread.
 *
 * @param[in] nt Task index.
 *
 * @return Number of unused stack bytes.
 */
size_t nilUnusedStack(uint8_t nt) {
  thread_config_t *tcp = &nil_thd_configs[nt];
  return fillSize(tcp->wap, tcp->wap + tcp->size);
}
//------------------------------------------------------------------------------
/**
 * Determine unused bytes in the heap and idle yhread stack area.
 *
 * @return Number of unused bytes.
 */
size_t nilUnusedHeapIdle() {
  return fillSize(heapEnd(), RAMEND);
}
//------------------------------------------------------------------------------
/** Fill stacks with 0X55.*/
static void nilFillStacks() {
  thread_config_t *tcp = nil_thd_configs;
  
  while (tcp->wap) {
    fill8(tcp->wap, tcp->wap + tcp->size);
    tcp++;
  }
  // fill heap/idle stack
  fill8(heapEnd(), (uint8_t*)&tcp - 16);
}
//------------------------------------------------------------------------------
/** Start Nil RTOS with all stack memory initialized to a known value.
 *
 * @return TRUE for success else FALSE.
 */
bool nilSysBegin() {
  nilFillStacks();
  return nilSysBeginNoFill();
}
//------------------------------------------------------------------------------
/** Start Nil RTOS with raw uninitialized stack memory.
 *  This call saves a little flash compared to nilSysBegin().
 *
 * @return TRUE for success else FALSE.
 */
bool nilSysBeginNoFill() {
  if (!nil_thd_count) return FALSE;
  nilSysLock();
  boardInit();
  nilSysInit();
  return TRUE;
}
//------------------------------------------------------------------------------
/**
 * @brief   Delay the invoking thread for the specified time.
 *
 * @param[in] time      the delay in system ticks.
 *
 * @note    This function does not sleep and will block all lower
 *          priority threads.  This function should only be used
 *          in the idle thread.
 * @api
 */
void nilThdDelay(systime_t time) {
  systime_t t0 = nilTimeNow();
  while ((nilTimeNow() - t0) < time) {}
}
//------------------------------------------------------------------------------
/**
 * @brief   Delay the invoking thread until the system time reaches to the
 *          specified value.
 *
 * @param[in] time      absolute system time
 *
 * @note    This function does not sleep and will block all lower
 *          priority threads.  This function should only be used
 *          in the idle thread.
 *
 * @api
 */
void nilThdDelayUntil(systime_t time) {
  nilThdDelay(time - nilTimeNow());
}
//------------------------------------------------------------------------------
#if NIL_DBG_ENABLED
/** Debug version of port_halt */
void port_halt(void) {
  const char* msg = nil.dbg_msg ? nil.dbg_msg : "halt";
  while (*msg) {
    while (((1 << UDRIE0) & UCSR0B) || !(UCSR0A & (1 << UDRE0))) {}
    UDR0 = *msg++;
  }
  port_disable();
  while(1);
}
#endif  /* NIL_DBG_ENABLED */
/** @} */