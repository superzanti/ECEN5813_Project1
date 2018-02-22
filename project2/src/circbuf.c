/**
 * @file circbuf.c
 * @brief implementation of circbuf.h
 *
 * implements the circular buffer access functions found in circbuf.h
 *
 * @author Seth Miers and Jake Cazden
 * @date March 04, 2018
 *
 */
#include "circbuf.h"

/* @brief initializes the circular buffer with default values
 *
 * the circularbuffer must already be allowcated when it is
 * passed in. The function will then create dynamic memory
 * to allocate the entire buffer. It will then set the
 * head, tail, and other values to be what they should be.
 * destroy must be called before free-ing the CB that
 * is passed in, otherwise a stack overflow may occur.
 *
 *
 * @param[in] CB_t the CB_t object to initialize
 * @param[in] size_t the size of the buffer to initialize
 * @return CB_e This function returns the CB_e typedef to indicate errors
 */
CB_e CB_init(CB_t circbuff, size_t buffer_size)
{
    if ((int)buffer_size == 0)
        return NO_LENGTH;
    if ((void*)circbuff == NULL)
        return BAD_POINTER;
    circbuff.buff_size = buffer_size;
    circbuff.base = (BUFFER_TYPE*)malloc(((int)buff_size)*sizeof(BUFFER_TYPE*));
    circbuff.head = circbuff.base;
    circbuff.tail = bircbuff.base;
    circbuff.num_in = 0;
    circbuff.buff_empty_flag = SET;
    circbuff.buff_full_flag = UNSET;
    circbuff.buff_ovf_flag = UNSET;
    circbuff.buff_destroyed_flag = UNSET;
    if ((void*)circbuff.base == NULL)
    {
        circbuff.buff_size = 0;
        circbuff.buff_full_flag = SET;
        circbuff.buff_destroyed_flag = SET;
        circbuff.buff_ovf_flag = SET;
        return NO_BUFFER_IN_MEMORY;
    }
}

/* @brief frees the entire circular buffer
 *
 * this function simply frees the dynamic memory that it allowcated
 * when initializing the function.
 *
 * @param[in] CB_t the CB_t object to destroy
 * @return CB_e This function returns the CB_e typedef to indicate errors
 */
CB_e CB_destroy(CB_t circbuff)
{
    if ((void*)circbuff == NULL)
        return BAD_POINTER;
    /* we don't want to free something twice */
    if ((CB_f)circbuff.buff_destroyed_flag == SET)
        return DOUBLE_FREE;
    free((void*)circbuff.base);
    circbuff.buff_destroyed_flag = SET;
    return SUCCESS;
}

/* @brief adds an item to the circular buffer
 *
 * add an item in memory tot he circular buffer
 * increment the head, and update all the flags
 *
 *
 * @param[in] CB_t the CB_t object to operate on
 * @param[in] BUFFER_TYPE the object to add into the buffer
 * @return CB_e This function returns the CB_e typedef to indicate errors
 */
CB_e CB_buffer_add_item(CB_t circbuff, BUFFER_TYPE data)
{
    if ((void*)circbuff == NULL)
        return BAD_POINTER;
    /* if we have already destoryed the buffer */
    if ((CB_f)circbuff.buff_destroyed_flag == SET)
        return NO_BUFFER_IN_MEMORY;
    /* the buffer is already full */
    if ((CB_f)circbuff.buff_full_flag == SET)
    {
        circbuff.buff_ovf_flag = SET;
        /* data is trashed */
        return FULL;
    }
    *circbuff.head = data;
    circbuff.head = circbuff.head + sizeof(BUFFER_TYPE);
    circbuff.num_in++;
    circbuff.buff_empty_flag = UNSET;
    /* it's a circular buffer, so loop around if we go beyond the max */
    if (circbuff.head > (circbuff.base + (circbuff.buffsize - sizeof(BUFFER_TYPE))))
    {
        circbuff.head = circbuff.head - circbuff.buffsize + sizeof(BUFFER_TYPE);
    }
    /* the buffer must be full since we added something and the following is true*/
    if (circbuff.head == circbuff.tail)
    {
        circbuff.buff_full_flag = SET;
        /* this should never happen */
        if (circbuff.num_in != circbuff.buff_size)
            return CRITICAL_ERROR
    }
    return SUCCESS;
}

/* @brief removes an item from the circular buffer
 *
 * removes an item from the circular buffer by
 * incrementing the tail an decrementing the num_in
 *
 * @param[in] CB_t the CB_t object to operate on
 * @param[out] BUFFER_TYPE* put the data removed into this pointer
 * @return CB_e This function returns the CB_e typedef to indicate errors
 */
CB_e CB_buffer_remove_item(CB_t circbuff, BUFFER_TYPE* data)
{
    if ((void*)circbuff == NULL)
        return BAD_POINTER;
    /* if we have already destoryed the buffer */
    if ((CB_f)circbuff.buff_destroyed_flag == SET)
        return NO_BUFFER_IN_MEMORY;
    if ((CB_f)circbuff.buff_empty_flag == SET)
        return EMPTY;
    *data = circbuff.tail;
    circbuff.tail = circbuff.tail + sizeof(BUFFER_TYPE);
    circbuff.num_in--;
    circbuff.buff_full_flag = UNSET;
    /* it's a circular buffer, so loop around if we go beyond the max */
    if (circbuff.tail > (circbuff.base + (circbuff.buffsize - sizeof(BUFFER_TYPE))))
    {
        circbuff.tail = circbuff.tail - circbuff.buffsize + sizeof(BUFFER_TYPE);
    }
    /* the buffer must be empty since we removed somethign and the follwoing is true */
    if (circbuff.head == circbuff.tail)
    {
        circbuff.buff_empty_flag = SET;
        /* this should never happen */
        if (circbuff.num_in != 0)
            return CRITICAL_ERROR
    }
    return SUCCESS;
}

/* @brief checks to see if the buffer is full
 *
 * simply checks the full flag of the buffer to see
 * if the head ever passed the tail
 *
 * @param[in] CB_t the CB_t object to operate on
 * @return CB_e This function returns the CB_e typedef to indicate errors
 */
CB_e CB_is_full(CB_t circbuff)
{
    if ((void*)circbuff == NULL)
        return BAD_POINTER;
    if ((CB_f)circbuff.buff_full_flag == SET)
        return FULL;
    return SUCCESS;
}

/* @brief checks to see if the buffer is empty
 *
 * simply checks the empty flag of the buffer
 * to see if the head and tail are equal and
 * there is no data in the buffer
 *
 *
 * @param[in] CB_t the CB_t object to operate on
 * @return CB_e This function returns the CB_e typedef to indicate errors
 */
CB_e CB_is_empty(CB_t circbuff)
{
    if ((void*)circbuff == NULL)
        return BAD_POINTER;
    if ((CB_f)circbuff.buff_empty_flag == SET)
        return EMPTY;
    return SUCCESS;
}

/* @brief returns the value in the buffer at a position back from the head
 *
 * peeking at the 0th value will just return the last value
 * that was put into the buffer.
 *
 * @param[in] CB_t the CB_t object to operate on
 * @param[in] size_t the index away from the head
 * @param[out] BUFFER_TYPE* put the data peeked at into this pointer
 * @return CB_e This function returns the CB_e typedef to indicate errors
 */
CB_e CB_peek(CB_t circbuff, size_t position, BUFFER_TYPE* data)
{
    void* peekdata = (void*)circbuff.head;
    if ((void*)circbuff == NULL)
        return BAD_POINTER;
    /* since head points at an empty value we increment by one */
    position++;
    if (position > circbuff.num_in)
        return POSITION_TOO_LARGE;
    /* it's a circular buffer, so loop around if we go beyond the max */
    if (peekdata < circbuff.base)
    {
        peekdata = sizeof(BUFFER_TYPE)*(circbuff.buff_size-1) + peekdata;
    }
    *data = *peekdata;
    return SUCCESS;
}
