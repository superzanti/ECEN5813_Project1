/*
 * @file conversion.h
 * @brief this file contains implementations of integer<>character conversion
 *
 * @author Jake Cazden and Seth Miers
 * @date February 4, 2018
 *
 * */
#ifndef __CONVERSION_H__
#define __CONVERSION_H__

/* needed for function prototypes */
#include <stdint.h>

#define BASE_2  (2)
#define BASE_3  (3)
#define BASE_4  (4)
#define BASE_5  (5)
#define BASE_6  (6)
#define BASE_7  (7)
#define BASE_8  (8)
#define BASE_9  (9)
#define BASE_10  (10)
#define BASE_11  (11)
#define BASE_12  (12)
#define BASE_13  (13)
#define BASE_14  (14)
#define BASE_15  (15)
#define BASE_16  (16)

/**
 * @brief take the exponent of a number
 *
 * This function takes in a number (base)
 * and raises it to an exponent (power)
 *
 * @param base is equal to X in the expression X^Y (where ^ is exponent)
 * @param power is equal to Y in the expression X^Y (where ^ is exponent)
 * @return int8_t the result of the exponent
 */
int32_t exponent(int32_t base,int32_t power);

/**
 * @brief function to convert an integer to ascii equivalant
 * 
 * This function takes in an integer and converts it
 * to an array of bytes that represent the ascii
 * value of that number in a particular base. A null
 * terminator '\0' is placed at the end of the string.
 * A negative sign is included at the begining of the
 * string if needed.
 *
 * The entire function is done using only
 * pointer arithmetic.
 *
 * @param data the 32 bit signed integer that we wish to convert
 * @param ptr is a pointer to an array of bytes that will be written to
 *              this poitner must be at least 32 bytes long
 * @param base is the base we want to convert to, bases 2-16 are supported
 * @return uint8_t the length of the string (including the minus sign)
 */
uint8_t my_itoa(int32_t data, uint8_t * ptr, uint32_t base);

/**
 * @brief function to convert an ascii string into an integer
 * 
 * This function takes in an array of data (ptr) and
 * convertes it to the 4byte equivalant. It is assumed
 * that the array of ascii formatted bytes (string) that
 * is passed in is null '\0' terminated. However,
 * the number of digits in this string is also passed in.
 * The function can convert anything of base 2 to 16.
 * The first character of the string may be a '-' to
 * indicate that it is a negative number.
 *
 * The entire function is done using only
 * pointer arithmetic.
 *
 * @param ptr a pointer to the array of bytes that store ascii characters
 * @param digits the number of characters in the string
 * @param base is the base we want to convert from, bases 2-16 are supported
 * @return int8_t the converted number
 */
int32_t my_atoi(uint8_t * ptr, uint8_t digits, uint32_t base);


#endif /* __CONVERSION_H__*/
