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
 * @file    NilSerial.h
 * @brief   Nil RTOS serial library header.
 *
 * @defgroup Serial NilSerial
 * @details Nil RTOS serial library.
 * @{
 */
#ifndef NilSerial_h
#define NilSerial_h
#include <Arduino.h>
/**
 * @class NilSerialClass
 * @brief Mini serial class derived from the Arduino Print class.
 */
class NilSerialClass : public Print {
 public:
  int available();
  void begin(unsigned long);
  int read();
  size_t write(uint8_t b);
  using Print::write;
};
#ifdef UDR0
extern NilSerialClass NilSerial;
#endif  // UDR0
#endif  // NilSerial_h

/** @} */