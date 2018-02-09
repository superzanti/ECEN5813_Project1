/*
 * @file conversion.c
 * @brief This file is to be used to project 1.
 *
 * @author Jake Cazden and Seth Miers
 * @date February 4, 2018
 *
 * */
#include <stdint.h>
#include "conversion.h"
#include "memory.h"

/*TODO remove this*/
#include "platform.h"

int32_t exponent(int32_t base,int32_t power)
{
    if(power<0) return 0;
    uint32_t i=0;
    int32_t retval=1;
    for(i=1;i<=power;i++)
    {
        retval*=base;
    }
    return retval;
}

uint8_t my_itoa(int32_t data, uint8_t * ptr, uint32_t base)
{
    uint8_t length=0;
    uint8_t negative=0;
    if(data == 0)
        return 0;
    if(base<BASE_2||base>BASE_16)
    {
        return 0;
    }
    if(data<0)
    {
        *ptr++='-';
        data=-data; /*make the number positive*/
        negative=1;
    }
    while(1) /* figure out the magnitude of the number */
    {
        *(ptr+length) = data%base;
        data = data/base;
        length++;
        if ((data == 0) || (length > 32 ))
            break;
    }
    my_reverse(ptr, length);
    int32_t j=length-1;
    uint8_t num;
    for(j=length-1;j>=0;j--)
    {
        num = *(ptr+j);
        if(num>9)
        {
            *(ptr+j)=num+55;
        }
        else
        {
            *(ptr+j)=num+48;
        }
    }
    length = length + negative;
    return length;
}

int32_t my_atoi(uint8_t * ptr, uint8_t digits, uint32_t base)
{
    int8_t i = 0;
    uint8_t negative = 0;
    int32_t return_value = 0;
    if(digits == 0)
        return 0;
    /* check to see if the integer is negative*/
    if(*ptr=='-')/* using int is okay here */
    {
        negative = 1;
        ptr++;
        digits--;
    }
    /* base starts at 0 so subtract one more */
    digits--;
    /* loop through each digit and add it to the return_value*/
    for(i=digits;i>=0;i--)
    {
        /* the digit is between a 0 and a 9 */
        if (*ptr >= 48 && *ptr <= 57)
        {
            if((*ptr - 48) > base)
                /* an error has occured, we've encountered an unsupported character */
                return 1;
            return_value += (*ptr++ - 48) * exponent(base, i);
        }
        /* the digit is between an uppercase A and a F */
        else if (*ptr >= 65 && *ptr <= 70)
        {
            if((*ptr - 55) > base)
                /* an error has occured, we've encountered an unsupported character */
                return 2;
            return_value += (*ptr++ - 55) * exponent(base, i);
        }
        /* the digit is between a lowercase a and a f */
        else if (*ptr >= 97 && *ptr <= 102)
        {
            if((*ptr - 87) > base)
                /* an error has occured, we've encountered an unsupported character */
                return 3;
            return_value += (*ptr++ - 87) * exponent(base, i);
        }
        else
        {
            /* an error has occurred, we've encountered an unsupported character */
            return 4;
        }
    }
    if(negative)
    {
        return -return_value;
    }
    return return_value;
}