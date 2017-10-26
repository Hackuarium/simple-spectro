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
 * @file    NilRTOS.h
 * @brief   Nil RTOS Arduino library header file.
 *
 * @defgroup arduino Arduino
 * @details Arduino Nil RTOS library.
 * @{
 */
#ifndef NilRTOS_h
#define  NilRTOS_h

#include "nil.h"
//------------------------------------------------------------------------------
/** NilRTOS version YYYYMMDD */
#define NIL_RTOS_VERSION 20130719
//------------------------------------------------------------------------------
#if NIL_CFG_TIMEDELTA
#error tick-less mode is not supported
#endif  // NIL_CFG_TIMEDELTA

/**
 * @brief   Static semaphore initializer.
 * @details Statically initialized semaphores require no explicit
 *          initialization using @p nilSemInit().
 *
 * @param[in] name      the name of the semaphore variable
 * @param[in] n         the counter initial value, this value must be
 *                      non-negative
 */
#define SEMAPHORE_DECL(name, n) semaphore_t name = {n}

/**
 * @brief   Delays the invoking thread for the specified number of
 *          milliseconds.
 * @note    This function does not sleep and will block all lower
 *          priority threads.  This function should only be used
 *          in the idle thread.
 * @note    The specified time is rounded up to a value allowed by the real
 *          system clock.
 * @note    The maximum specified value is implementation dependent.
 *
 * @param[in] msec      time in milliseconds, must be different from zero
 *
 * @api
 */
#define nilThdDelayMilliseconds(msec) nilThdDelay(MS2ST(msec))

/**
 * @brief   Decreases the semaphore counter.
 * @details This macro can be used when the counter is known to be positive.
 *
 * @iclass
 */
#define nilSemFastWaitI(sp)      ((sp)->cnt--)

/**
 * @brief   Increases the semaphore counter.
 * @details This macro can be used when the counter is known to be not
 *          negative.
 *
 * @iclass
 */
#define nilSemFastSignalI(sp)    ((sp)->cnt++)

/**
 * @brief   Returns the semaphore counter current value.
 *
 * @iclass
 */
#define nilSemGetCounterI(sp)    ((sp)->cnt)
/**
 * @brief   Returns true if current thread is the idle thread.
 */
#define nilIsIdleThread() (nil.current == nil.idlep)

#ifdef __cplusplus
#include <Arduino.h>
void nilPrintStackSizes(Print* pr);
void nilPrintUnusedStack(Print* pr);
extern "C" {
#endif
  void boardInit();
  cnt_t nilSemGetCounter(semaphore_t *sp);
  bool nilSysBegin(void);
  bool nilSysBeginNoFill();
  void nilThdDelay(systime_t time);
  void nilThdDelayUntil(systime_t time);
  size_t nilUnusedHeapIdle();
  size_t nilUnusedStack(uint8_t nt);
#ifdef __cplusplus
}
#endif
#endif /*NilRTOS_h */
/** @} */