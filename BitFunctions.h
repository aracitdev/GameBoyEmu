/**
 * \file BitFunctions.h
 * \author Sean C
 * \version 1.0
 * Provides functions for bit manipulation.
 */

#ifndef BITFUNCTIONS_H_INCLUDED
#define BITFUNCTIONS_H_INCLUDED
#include <cstdint>

#define KB(x) x*1024
#define MB(x) x*1048576


/**
 * uint8_t Bit(T byte, uint8_t Bit)
 * \param byte The byte to get the bit from.
 * \param Bit the bit number to get.
 * \return The value of the bit, 1 for true, 0 for false.
 * Gets a bit from a number and returns its value.
 */
//template <class T>
//uint8_t Bit(T Byte, uint8_t Bit);

/**
 * uint8_t Pow2(uint8_t v)
 * \param v The exponent power.
 * Returns a power of 2.
 * \return returns 2 to the power of v.
 */
uint8_t Pow2(uint8_t v);

/**
 * void SetBit(bool Value, uint8_t& Byte, uint8_t BitNumber)
 * \param Value the value to set the bit to (true or false)
 * \param Byte a reference to the byte to change the value of.
 * \param BitNumber the bit to set in the byte.
 * Sets a bit within a byte to the specified value.
 */
void SetBit(bool Value, uint8_t& Byte, uint8_t BitNumber);

/**
 * uint8_t BitField(uint8_t Byte, uint8_t BitStart, uint8_t BitEnd)
 * \param Byte The byte to get the bits from.
 * \param BitStart the first bit of the bit field.
 * \param BitEnd the last bit of the bit field.
 * returns a number represented by a bitfield between bitstart and end in the byte.
 * \return The number equal to the bit field.
 */
//uint8_t BitField(uint8_t Byte, uint8_t BitStart, uint8_t BitEnd);
#define Bit(Byte, Bt)   (((Byte) >>(Bt)) & 0x1)
#define BITF(n)                  ( 1<<(n) )
#define BitMask(len)           ( BITF(len)-1 )
#define BitField(y, start, end)   (((y)>>(start)) & BitMask(end - start + 1) )


uint8_t Get2Bits(uint8_t Byte, uint8_t Bits);
#endif // BITFUNCTIONS_H_INCLUDED
