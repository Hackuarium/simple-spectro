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
 * @file    nilUtility.cpp
 * @brief   Nil RTOS Arduino library source file.
 * @defgroup arduino Arduino
 * @details Arduino Nil RTOS library.
 * @{
 */

#include <NilRTOS.h>
#include <avr_heap.h>
//------------------------------------------------------------------------------
/** Print size of all all stacks.
 * @param[in] pr Print stream for output.
 */
void nilPrintStackSizes(Print* pr) {
  const thread_config_t *tcp = nil_thd_configs;
  pr->print(F("Stack Sizes: "));
  while (tcp->wap) {
    pr->print(tcp->size);
    pr->print(' ');
    tcp++;
  }
  pr->println(nilHeapIdleSize());
}
//------------------------------------------------------------------------------
/** Print unused byte count for all stacks.
 * @param[in] pr Print stream for output.
 */
void nilPrintUnusedStack(Print* pr) {
  const thread_config_t *tcp = nil_thd_configs;
  pr->print(F("Unused Stack: "));
  while (tcp->wap) {
    pr->print(fillSize((uint8_t*)tcp->wap, (uint8_t*)tcp->wap + tcp->size));
    pr->print(' ');
    tcp++;
  }
  pr->println(fillSize((uint8_t*)heapEnd(), (uint8_t*)RAMEND));
}
 /** @} */