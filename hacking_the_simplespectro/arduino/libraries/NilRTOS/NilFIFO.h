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
 * @file    NilFIFO.h
 * @brief   Nil RTOS FIFO template source
 *
 * @defgroup FIFO NilFIFO
 * @details Nil RTOS FIFO template.
 * @{
 */
#ifndef NilFIFO_h
#define NilFIFO_h
#include <NilRTOS.h>
//------------------------------------------------------------------------------
 /**
  * @class NilStatsFIFO
  * \brief A thread safe FIFO with statistics.
  *
  * A FIFO for a single producer/consumer pair with statistics.
  *
  */
template<typename Type, size_t Size>
class NilStatsFIFO {
 public:
  /** constructor */
  NilStatsFIFO() : _head(0), _maxOverrun(0),
    _minFree(Size), _overrun(0), _tail(0) {
    nilSemInit(&_dataSem, 0);
    nilSemInit(&_freeSem, Size);
  }
  /** Increment overrun count
   * @note Must only be called in producer thread.
   */
  void countOverrun() {
    if (_overrun == (size_t)-1) return;
    if (++_overrun > _maxOverrun) _maxOverrun = _overrun;
  }
  /** @return count of data records in the FIFO. */
  size_t dataCount() {return nilSemGetCounter(&_dataSem);}
  
  /** @return count of free records in the FIFO. */
  size_t freeCount() {return nilSemGetCounter(&_freeSem);}
  
  /**
   * Count of overruns since last call to signalData().
   * @note Must only be called in producer thread.
   * @return overrun count.
   *
   */
  size_t overrunCount() {return _overrun;}
  
  /** @return maximum overrun count. */
  size_t maxOverrunCount() {
    nilSysLock();
    size_t rtn = _maxOverrun;
    nilSysUnlock();
    return rtn;
  }
  /** @return minimum free count. */
  size_t minimumFreeCount() {
    nilSysLock();
    size_t rtn = _minFree;
    nilSysUnlock();
    return rtn;
  }

  /**
   * Print FIFO statistics.
   *
   * @param[in] pr Print stream for the output.
   *
   * @note Must be called when consumer/producer are idle
   *       for consistent results.
   */
  void printStats(Print* pr) {
    pr->print(F("FIFO record count: "));
    pr->println(Size);
    pr->print(F("Minimum free count: "));
    pr->println(_minFree);
    if (_maxOverrun) {
      pr->println();
      pr->println(F("** overrun errors **"));
      pr->print(F("Maximum overrun count: "));
      pr->println(_maxOverrun);
    }
  }
  
  /** Signal that a data record is ready.
   * @note Must only be called in producer thread.
   */
  void signalData() {
    _overrun = 0;
    nilSemSignal(&_dataSem);
  }
  /** Signal that a record is free.
   * @note Must only be called in consumer thread.
   */
  void signalFree() {
    cnt_t cnt = freeCount();
    if (cnt < _minFree) _minFree = cnt;
    nilSemSignal(&_freeSem);
  }
  
  /**
   * Wait for a data record.
   * @param[in] time      the number of ticks before the operation timeouts,
   *                      the following special values are allowed:
   *                      - @a TIME_IMMEDIATE immediate timeout.
   *                      - @a TIME_INFINITE no timeout.
   *                      .
   * @note Must only be called in consumer thread.
   * @return pointer to the data record or null if no data record is availabile.
   */
  Type* waitData(systime_t time) {
    if (nilSemWaitTimeout(&_dataSem, time) != NIL_MSG_OK) {
      return 0;
    }
    Type* rtn = &_data[_tail];
    _tail = _tail < (Size - 1) ? _tail + 1 : 0;
    return rtn;
  }
  
  /**
   * Wait for a free record.
   * @param[in] time      the number of ticks before the operation timeouts,
   *                      the following special values are allowed:
   *                      - @a TIME_IMMEDIATE immediate timeout.
   *                      - @a TIME_INFINITE no timeout.
   *                      .
   * @note Must only be called in producer thread.
   * @return pointer to the free record or null if no free record is availabile.
   */
  Type* waitFree(systime_t time) {
    if (nilSemWaitTimeout(&_freeSem, time) != NIL_MSG_OK) {
      countOverrun();
      return 0;
    }
    Type* rtn = &_data[_head];
    _head = _head < (Size - 1) ? _head + 1 : 0;
    return rtn;
  }

 private:
  Type _data[Size];
  semaphore_t _dataSem;
  semaphore_t _freeSem;
  size_t _head;
  size_t _maxOverrun;
  size_t _minFree;
  size_t _overrun;
  size_t _tail;
};
//------------------------------------------------------------------------------
 /**
  * @class NilFIFO
  * \brief A thread safe FIFO.
  *
  * A FIFO for a single producer/consumer pair.
  *
  */
template<typename Type, size_t Size>
class NilFIFO {
 public:
  /** constructor */
  NilFIFO() : _head(0), _tail(0) {
    nilSemInit(&_dataSem, 0);
    nilSemInit(&_freeSem, Size);
  }
  /** @return count of data records in the FIFO. */
  size_t dataCount() {return nilSemGetCounter(&_dataSem);}

  /** @return count of free records in the FIFO. */
  size_t freeCount() {return nilSemGetCounter(&_freeSem);}

  /** Signal that a data record is ready.
   * @note Must only be called in producer thread.
   */
  void signalData() {
    nilSemSignal(&_dataSem);
  }
  /** Signal that a record is free.
   * @note Must only be called in consumer thread.
   */
  void signalFree() {
    nilSemSignal(&_freeSem);
  }

  /**
   * Wait for a data record.
   * @param[in] time      the number of ticks before the operation timeouts,
   *                      the following special values are allowed:
   *                      - @a TIME_IMMEDIATE immediate timeout.
   *                      - @a TIME_INFINITE no timeout.
   *                      .
   * @note Must only be called in consumer thread.
   * @return pointer to the data record or null if no data record is availabile.
   */
  Type* waitData(systime_t time) {
    if (nilSemWaitTimeout(&_dataSem, time) != NIL_MSG_OK) {
      return 0;
    }
    Type* rtn = &_data[_tail];
    _tail = _tail < (Size - 1) ? _tail + 1 : 0;
    return rtn;
  }

  /**
   * Wait for a free record.
   * @param[in] time      the number of ticks before the operation timeouts,
   *                      the following special values are allowed:
   *                      - @a TIME_IMMEDIATE immediate timeout.
   *                      - @a TIME_INFINITE no timeout.
   *                      .
   * @note Must only be called in producer thread.
   * @return pointer to the free record or null if no free record is availabile.
   */
  Type* waitFree(systime_t time) {
    if (nilSemWaitTimeout(&_freeSem, time) != NIL_MSG_OK) {
      return 0;
    }
    Type* rtn = &_data[_head];
    _head = _head < (Size - 1) ? _head + 1 : 0;
    return rtn;
  }

 private:
  Type _data[Size];
  semaphore_t _dataSem;
  semaphore_t _freeSem;
  size_t _head;
  size_t _tail;
};
#endif  // NilFIFO_h
/** @} */