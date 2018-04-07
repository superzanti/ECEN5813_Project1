/*
 * @file project3.c
 * @brief implements project3.h
 *
 *	Project 3 functionality
 *
 *  @author Seth Miers and Jake Cazden
 *  @date March 15, 2018
 */

#include "project3.h"

#ifdef KL25Z
	#include "nordic.h"
	#include "spi.h"
	#include "port.h"
	#include "uart.h"
	#include "circbuf.h"
	#include "conversion.h"
	#include "arch_arm32.h"
	#include <string.h>
#endif

extern CB_t* recieve_buffer;
extern CB_t* transmit_buffer;

extern volatile uint32_t DMA_end_value;

void project3()
{
	spi_setup_and_test();
	profiler();
}

void profiler()
{
	/* TODO buildtime settings must be adjusted so that the heap can support these regions (at least 1kB) */
	/* TODO refactor this code to be smaller */
	/* TODO run with highest optimizations and lowest optimizations to see difference */

	/* areas to copy and move to */
	uint8_t *area_one = (uint8_t *) malloc(sizeof(uint8_t)*5000);
	uint8_t *area_two = (uint8_t *) malloc(sizeof(uint8_t)*5000);

	/* timer values */
	volatile uint32_t start_value = 0;
	volatile uint32_t end_value = 0;

	/* strings used for printing */
    uint8_t my_string;
	uint8_t printsize = 0x00;

	/*******************/
	/* MEMSET PROFILER */
	/*******************/

	/* standard library */
	/* 10 bytes */
	SysTick_Base_Ptr->CSR |= __SYSTICK_ENABLE_MASK; /* enable counting */
	start_value = SysTick_Base_Ptr->CVR;
	memset(area_one, '1', 10);
	end_value = SysTick_Base_Ptr->CVR;
	SysTick_Base_Ptr->CVR = 0;
	SysTick_Base_Ptr->CSR &= ~(__SYSTICK_ENABLE_MASK); /* disable counting */
    my_string = "Profiling the standard memset library with 10 bytes took ";
	UART_send_n(my_string, 57);
	printsize = my_itoa((int32_t)(start_value-end_value), my_string, 10);
	UART_send_n(my_string, printsize);
    my_string = " clock cycles to run\r\n";
	UART_send_n(my_string, 22);
	/* 100 bytes */
	SysTick_Base_Ptr->CSR |= __SYSTICK_ENABLE_MASK; /* enable counting */
	start_value = SysTick_Base_Ptr->CVR;
	memset(area_one, '2', 100);
	end_value = SysTick_Base_Ptr->CVR;
	SysTick_Base_Ptr->CVR = 0;
	SysTick_Base_Ptr->CSR &= ~(__SYSTICK_ENABLE_MASK); /* disable counting */
    my_string = "Profiling the standard memset library with 100 bytes took ";
	UART_send_n(my_string, 58);
	printsize = my_itoa((int32_t)(start_value-end_value), my_string, 10);
	UART_send_n(my_string, printsize);
    my_string = " clock cycles to run\r\n";
	UART_send_n(my_string, 22);
	/* 1000 bytes */
	SysTick_Base_Ptr->CSR |= __SYSTICK_ENABLE_MASK; /* enable counting */
	start_value = SysTick_Base_Ptr->CVR;
	memset(area_one, '3', 1000);
	end_value = SysTick_Base_Ptr->CVR;
	SysTick_Base_Ptr->CVR = 0;
	SysTick_Base_Ptr->CSR &= ~(__SYSTICK_ENABLE_MASK); /* disable counting */
    my_string = "Profiling the standard memset library with 1000 bytes took ";
	UART_send_n(my_string, 59);
	printsize = my_itoa((int32_t)(start_value-end_value), my_string, 10);
	UART_send_n(my_string, printsize);
    my_string = " clock cycles to run\r\n";
	UART_send_n(my_string, 22);
	/* 5000 bytes */
	SysTick_Base_Ptr->CSR |= __SYSTICK_ENABLE_MASK; /* enable counting */
	start_value = SysTick_Base_Ptr->CVR;
	memset(area_one, '4', 5000);
	end_value = SysTick_Base_Ptr->CVR;
	SysTick_Base_Ptr->CVR = 0;
	SysTick_Base_Ptr->CSR &= ~(__SYSTICK_ENABLE_MASK); /* disable counting */
    my_string = "Profiling the standard memset library with 5000 bytes took ";
	UART_send_n(my_string, 59);
	printsize = my_itoa((int32_t)(start_value-end_value), my_string, 10);
	UART_send_n(my_string, printsize);
    my_string = " clock cycles to run\r\n";
	UART_send_n(my_string, 22);
	/* my library */
	/* 10 bytes */
	SysTick_Base_Ptr->CSR |= __SYSTICK_ENABLE_MASK; /* enable counting */
	start_value = SysTick_Base_Ptr->CVR;
	my_memset(area_one, '1', 10);
	end_value = SysTick_Base_Ptr->CVR;
	SysTick_Base_Ptr->CVR = 0;
	SysTick_Base_Ptr->CSR &= ~(__SYSTICK_ENABLE_MASK); /* disable counting */
    my_string = "Profiling the custom memset function with 10 bytes took ";
	UART_send_n(my_string, 56);
	printsize = my_itoa((int32_t)(start_value-end_value), my_string, 10);
	UART_send_n(my_string, printsize);
    my_string = " clock cycles to run\r\n";
	UART_send_n(my_string, 22);
	/* 100 bytes */
	SysTick_Base_Ptr->CSR |= __SYSTICK_ENABLE_MASK; /* enable counting */
	start_value = SysTick_Base_Ptr->CVR;
	my_memset(area_one, '2', 100);
	end_value = SysTick_Base_Ptr->CVR;
	SysTick_Base_Ptr->CVR = 0;
	SysTick_Base_Ptr->CSR &= ~(__SYSTICK_ENABLE_MASK); /* disable counting */
    my_string = "Profiling the custom memset function with 100 bytes took ";
	UART_send_n(my_string, 57);
	printsize = my_itoa((int32_t)(start_value-end_value), my_string, 10);
	UART_send_n(my_string, printsize);
    my_string = " clock cycles to run\r\n";
	UART_send_n(my_string, 22);
	/* 1000 bytes */
	SysTick_Base_Ptr->CSR |= __SYSTICK_ENABLE_MASK; /* enable counting */
	start_value = SysTick_Base_Ptr->CVR;
	my_memset(area_one, '3', 1000);
	end_value = SysTick_Base_Ptr->CVR;
	SysTick_Base_Ptr->CVR = 0;
	SysTick_Base_Ptr->CSR &= ~(__SYSTICK_ENABLE_MASK); /* disable counting */
    my_string = "Profiling the custom memset function with 1000 bytes took ";
	UART_send_n(my_string, 58);
	printsize = my_itoa((int32_t)(start_value-end_value), my_string, 10);
	UART_send_n(my_string, printsize);
    my_string = " clock cycles to run\r\n";
	UART_send_n(my_string, 22);
	/* 5000 bytes */
	SysTick_Base_Ptr->CSR |= __SYSTICK_ENABLE_MASK; /* enable counting */
	start_value = SysTick_Base_Ptr->CVR;
	my_memset(area_one, '4', 5000);
	end_value = SysTick_Base_Ptr->CVR;
	SysTick_Base_Ptr->CVR = 0;
	SysTick_Base_Ptr->CSR &= ~(__SYSTICK_ENABLE_MASK); /* disable counting */
    my_string = "Profiling the custom memset function with 5000 bytes took ";
	UART_send_n(my_string, 58);
	printsize = my_itoa((int32_t)(start_value-end_value), my_string, 10);
	UART_send_n(my_string, printsize);
    my_string = " clock cycles to run\r\n";
	UART_send_n(my_string, 22);
	/* TODO the entire dma profiler */
	/* dma library */
	/* 10 bytes */
	SysTick_Base_Ptr->CSR |= __SYSTICK_ENABLE_MASK; /* enable counting */
	start_value = SysTick_Base_Ptr->CVR;
	memset_dma(area_one, 10, '1', 1);
	SysTick_Base_Ptr->CVR = 0;
	SysTick_Base_Ptr->CSR &= ~(__SYSTICK_ENABLE_MASK); /* disable counting */
    my_string = "Profiling the DMA memset function with 10 bytes took ";
	UART_send_n(my_string, 53);
	printsize = my_itoa((int32_t)(start_value-DMA_end_value), my_string, 10);
	UART_send_n(my_string, printsize);
    my_string = " clock cycles to run\r\n";
	UART_send_n(my_string, 22);
	/* 100 bytes */
	SysTick_Base_Ptr->CSR |= __SYSTICK_ENABLE_MASK; /* enable counting */
	start_value = SysTick_Base_Ptr->CVR;
	memset_dma(area_one, 100, '2', 1);
	SysTick_Base_Ptr->CVR = 0;
	SysTick_Base_Ptr->CSR &= ~(__SYSTICK_ENABLE_MASK); /* disable counting */
    my_string = "Profiling the DMA memset function with 100 bytes took ";
	UART_send_n(my_string, 54);
	printsize = my_itoa((int32_t)(start_value-DMA_end_value), my_string, 10);
	UART_send_n(my_string, printsize);
    my_string = " clock cycles to run\r\n";
	UART_send_n(my_string, 22);
	/* 1000 bytes */
	SysTick_Base_Ptr->CSR |= __SYSTICK_ENABLE_MASK; /* enable counting */
	start_value = SysTick_Base_Ptr->CVR;
	memset_dma(area_one, 1000, '3', 1);
	SysTick_Base_Ptr->CVR = 0;
	SysTick_Base_Ptr->CSR &= ~(__SYSTICK_ENABLE_MASK); /* disable counting */
    my_string = "Profiling the DMA memset function with 1000 bytes took ";
	UART_send_n(my_string, 55);
	printsize = my_itoa((int32_t)(start_value-DMA_end_value), my_string, 10);
	UART_send_n(my_string, printsize);
    my_string = " clock cycles to run\r\n";
	UART_send_n(my_string, 22);
	/* 5000 bytes */
	SysTick_Base_Ptr->CSR |= __SYSTICK_ENABLE_MASK; /* enable counting */
	start_value = SysTick_Base_Ptr->CVR;
	memset_dma(area_one, 5000, '4', 1);
	SysTick_Base_Ptr->CVR = 0;
	SysTick_Base_Ptr->CSR &= ~(__SYSTICK_ENABLE_MASK); /* disable counting */
    my_string = "Profiling the DMA memset function with 5000 bytes took ";
	UART_send_n(my_string, 55);
	printsize = my_itoa((int32_t)(start_value-DMA_end_value), my_string, 10);
	UART_send_n(my_string, printsize);
    my_string = " clock cycles to run\r\n";
	UART_send_n(my_string, 22);
	/* dma library - 4 byte transfer */
	/* 10 bytes */
	SysTick_Base_Ptr->CSR |= __SYSTICK_ENABLE_MASK; /* enable counting */
	start_value = SysTick_Base_Ptr->CVR;
	memset_dma(area_one, 10, '1', 4);
	SysTick_Base_Ptr->CVR = 0;
	SysTick_Base_Ptr->CSR &= ~(__SYSTICK_ENABLE_MASK); /* disable counting */
    my_string = "Profiling the DMA memset function with 10 bytes and 4 byte transfer took ";
	UART_send_n(my_string, 73);
	printsize = my_itoa((int32_t)(start_value-DMA_end_value), my_string, 10);
	UART_send_n(my_string, printsize);
    my_string = " clock cycles to run\r\n";
	UART_send_n(my_string, 22);
	/* 100 bytes */
	SysTick_Base_Ptr->CSR |= __SYSTICK_ENABLE_MASK; /* enable counting */
	start_value = SysTick_Base_Ptr->CVR;
	memset_dma(area_one, 100, '2', 4);
	SysTick_Base_Ptr->CVR = 0;
	SysTick_Base_Ptr->CSR &= ~(__SYSTICK_ENABLE_MASK); /* disable counting */
    my_string = "Profiling the DMA memset function with 100 bytes and 4 byte transfer took ";
	UART_send_n(my_string, 74);
	printsize = my_itoa((int32_t)(start_value-DMA_end_value), my_string, 10);
	UART_send_n(my_string, printsize);
    my_string = " clock cycles to run\r\n";
	UART_send_n(my_string, 22);
	/* 1000 bytes */
	SysTick_Base_Ptr->CSR |= __SYSTICK_ENABLE_MASK; /* enable counting */
	start_value = SysTick_Base_Ptr->CVR;
	memset_dma(area_one, 1000, '3', 4);
	SysTick_Base_Ptr->CVR = 0;
	SysTick_Base_Ptr->CSR &= ~(__SYSTICK_ENABLE_MASK); /* disable counting */
    my_string = "Profiling the DMA memset function with 1000 bytes and 4 byte transfer took ";
	UART_send_n(my_string, 75);
	printsize = my_itoa((int32_t)(start_value-DMA_end_value), my_string, 10);
	UART_send_n(my_string, printsize);
    my_string = " clock cycles to run\r\n";
	UART_send_n(my_string, 22);
	/* 5000 bytes */
	SysTick_Base_Ptr->CSR |= __SYSTICK_ENABLE_MASK; /* enable counting */
	start_value = SysTick_Base_Ptr->CVR;
	memset_dma(area_one, 5000, '4', 4);
	SysTick_Base_Ptr->CVR = 0;
	SysTick_Base_Ptr->CSR &= ~(__SYSTICK_ENABLE_MASK); /* disable counting */
    my_string = "Profiling the DMA memset function with 5000 bytes and 4 byte transfer took ";
	UART_send_n(my_string, 75);
	printsize = my_itoa((int32_t)(start_value-DMA_end_value), my_string, 10);
	UART_send_n(my_string, printsize);
    my_string = " clock cycles to run\r\n";
	UART_send_n(my_string, 22);

	/********************/
	/* MEMMOVE PROFILER */
	/********************/
	/* standard library */
	/* 10 bytes */
	SysTick_Base_Ptr->CSR |= __SYSTICK_ENABLE_MASK; /* enable counting */
	start_value = SysTick_Base_Ptr->CVR;
	memmove(area_one, area_two, 10);
	end_value = SysTick_Base_Ptr->CVR;
	SysTick_Base_Ptr->CVR = 0;
	SysTick_Base_Ptr->CSR &= ~(__SYSTICK_ENABLE_MASK); /* disable counting */
    my_string = "Profiling the standard memmove library with 10 bytes took ";
	UART_send_n(my_string, 58);
	printsize = my_itoa((int32_t)(start_value-end_value), my_string, 10);
	UART_send_n(my_string, printsize);
    my_string = " clock cycles to run\r\n";
	UART_send_n(my_string, 22);
	/* 100 bytes */
	SysTick_Base_Ptr->CSR |= __SYSTICK_ENABLE_MASK; /* enable counting */
	start_value = SysTick_Base_Ptr->CVR;
	memmove(area_one, area_two, 100);
	end_value = SysTick_Base_Ptr->CVR;
	SysTick_Base_Ptr->CVR = 0;
	SysTick_Base_Ptr->CSR &= ~(__SYSTICK_ENABLE_MASK); /* disable counting */
    my_string = "Profiling the standard memmove library with 100 bytes took ";
	UART_send_n(my_string, 59);
	printsize = my_itoa((int32_t)(start_value-end_value), my_string, 10);
	UART_send_n(my_string, printsize);
    my_string = " clock cycles to run\r\n";
	UART_send_n(my_string, 22);
	/* 1000 bytes */
	SysTick_Base_Ptr->CSR |= __SYSTICK_ENABLE_MASK; /* enable counting */
	start_value = SysTick_Base_Ptr->CVR;
	memmove(area_one, area_two, 1000);
	end_value = SysTick_Base_Ptr->CVR;
	SysTick_Base_Ptr->CVR = 0;
	SysTick_Base_Ptr->CSR &= ~(__SYSTICK_ENABLE_MASK); /* disable counting */
    my_string = "Profiling the standard memmove library with 1000 bytes took ";
	UART_send_n(my_string, 60);
	printsize = my_itoa((int32_t)(start_value-end_value), my_string, 10);
	UART_send_n(my_string, printsize);
    my_string = " clock cycles to run\r\n";
	UART_send_n(my_string, 22);
	/* 5000 bytes */
	SysTick_Base_Ptr->CSR |= __SYSTICK_ENABLE_MASK; /* enable counting */
	start_value = SysTick_Base_Ptr->CVR;
	memmove(area_one, area_two, 5000);
	end_value = SysTick_Base_Ptr->CVR;
	SysTick_Base_Ptr->CVR = 0;
	SysTick_Base_Ptr->CSR &= ~(__SYSTICK_ENABLE_MASK); /* disable counting */
    my_string = "Profiling the standard memmove library with 5000 bytes took ";
	UART_send_n(my_string, 60);
	printsize = my_itoa((int32_t)(start_value-end_value), my_string, 10);
	UART_send_n(my_string, printsize);
    my_string = " clock cycles to run\r\n";
	UART_send_n(my_string, 22);
	/* my library */
	/* 10 bytes */
	SysTick_Base_Ptr->CSR |= __SYSTICK_ENABLE_MASK; /* enable counting */
	start_value = SysTick_Base_Ptr->CVR;
	my_memmove(area_one, area_two, 10);
	end_value = SysTick_Base_Ptr->CVR;
	SysTick_Base_Ptr->CVR = 0;
	SysTick_Base_Ptr->CSR &= ~(__SYSTICK_ENABLE_MASK); /* disable counting */
    my_string = "Profiling the custom memmove function with 10 bytes took ";
	UART_send_n(my_string, 57);
	printsize = my_itoa((int32_t)(start_value-end_value), my_string, 10);
	UART_send_n(my_string, printsize);
    my_string = " clock cycles to run\r\n";
	UART_send_n(my_string, 22);
	/* 100 bytes */
	SysTick_Base_Ptr->CSR |= __SYSTICK_ENABLE_MASK; /* enable counting */
	start_value = SysTick_Base_Ptr->CVR;
	my_memmove(area_one, area_two, 100);
	end_value = SysTick_Base_Ptr->CVR;
	SysTick_Base_Ptr->CVR = 0;
	SysTick_Base_Ptr->CSR &= ~(__SYSTICK_ENABLE_MASK); /* disable counting */
    my_string = "Profiling the custom memmove function with 100 bytes took ";
	UART_send_n(my_string, 58);
	printsize = my_itoa((int32_t)(start_value-end_value), my_string, 10);
	UART_send_n(my_string, printsize);
    my_string = " clock cycles to run\r\n";
	UART_send_n(my_string, 22);
	/* 1000 bytes */
	SysTick_Base_Ptr->CSR |= __SYSTICK_ENABLE_MASK; /* enable counting */
	start_value = SysTick_Base_Ptr->CVR;
	my_memmove(area_one, area_two, 1000);
	end_value = SysTick_Base_Ptr->CVR;
	SysTick_Base_Ptr->CVR = 0;
	SysTick_Base_Ptr->CSR &= ~(__SYSTICK_ENABLE_MASK); /* disable counting */
    my_string = "Profiling the custom memmove function with 1000 bytes took ";
	UART_send_n(my_string, 59);
	printsize = my_itoa((int32_t)(start_value-end_value), my_string, 10);
	UART_send_n(my_string, printsize);
    my_string = " clock cycles to run\r\n";
	UART_send_n(my_string, 22);
	/* 5000 bytes */
	SysTick_Base_Ptr->CSR |= __SYSTICK_ENABLE_MASK; /* enable counting */
	start_value = SysTick_Base_Ptr->CVR;
	my_memmove(area_one, area_two, 5000);
	end_value = SysTick_Base_Ptr->CVR;
	SysTick_Base_Ptr->CVR = 0;
	SysTick_Base_Ptr->CSR &= ~(__SYSTICK_ENABLE_MASK); /* disable counting */
    my_string = "Profiling the custom memsmovefunction with 5000 bytes took ";
	UART_send_n(my_string, 59);
	printsize = my_itoa((int32_t)(start_value-end_value), my_string, 10);
	UART_send_n(my_string, printsize);
    my_string = " clock cycles to run\r\n";
	UART_send_n(my_string, 22);
	/* TODO the entire dma profiler */
	/* dma library */
	/* 10 bytes */
	SysTick_Base_Ptr->CSR |= __SYSTICK_ENABLE_MASK; /* enable counting */
	start_value = SysTick_Base_Ptr->CVR;
	memmove_dma(area_one, area_two, 10, 1);
	SysTick_Base_Ptr->CVR = 0;
	SysTick_Base_Ptr->CSR &= ~(__SYSTICK_ENABLE_MASK); /* disable counting */
    my_string = "Profiling the DMA memmove function with 10 bytes took ";
	UART_send_n(my_string, 54);
	printsize = my_itoa((int32_t)(start_value-DMA_end_value), my_string, 10);
	UART_send_n(my_string, printsize);
    my_string = " clock cycles to run\r\n";
	UART_send_n(my_string, 22);
	/* 100 bytes */
	SysTick_Base_Ptr->CSR |= __SYSTICK_ENABLE_MASK; /* enable counting */
	start_value = SysTick_Base_Ptr->CVR;
	memmove_dma(area_one, area_two, 100, 1);
	SysTick_Base_Ptr->CVR = 0;
	SysTick_Base_Ptr->CSR &= ~(__SYSTICK_ENABLE_MASK); /* disable counting */
    my_string = "Profiling the DMA memmove function with 100 bytes took ";
	UART_send_n(my_string, 55);
	printsize = my_itoa((int32_t)(start_value-DMA_end_value), my_string, 10);
	UART_send_n(my_string, printsize);
    my_string = " clock cycles to run\r\n";
	UART_send_n(my_string, 22);
	/* 1000 bytes */
	SysTick_Base_Ptr->CSR |= __SYSTICK_ENABLE_MASK; /* enable counting */
	start_value = SysTick_Base_Ptr->CVR;
	memmove_dma(area_one, area_two, 1000, 1);
	SysTick_Base_Ptr->CVR = 0;
	SysTick_Base_Ptr->CSR &= ~(__SYSTICK_ENABLE_MASK); /* disable counting */
    my_string = "Profiling the DMA memmove function with 1000 bytes took ";
	UART_send_n(my_string, 56);
	printsize = my_itoa((int32_t)(start_value-DMA_end_value), my_string, 10);
	UART_send_n(my_string, printsize);
    my_string = " clock cycles to run\r\n";
	UART_send_n(my_string, 22);
	/* 5000 bytes */
	SysTick_Base_Ptr->CSR |= __SYSTICK_ENABLE_MASK; /* enable counting */
	start_value = SysTick_Base_Ptr->CVR;
	memmove_dma(area_one, area_two, 5000, 1);
	SysTick_Base_Ptr->CVR = 0;
	SysTick_Base_Ptr->CSR &= ~(__SYSTICK_ENABLE_MASK); /* disable counting */
    my_string = "Profiling the DMA memmove function with 5000 bytes took ";
	UART_send_n(my_string, 56);
	printsize = my_itoa((int32_t)(start_value-DMA_end_value), my_string, 10);
	UART_send_n(my_string, printsize);
    my_string = " clock cycles to run\r\n";
	UART_send_n(my_string, 22);
	/* dma library - 4 byte transfer */
	/* 10 bytes */
	SysTick_Base_Ptr->CSR |= __SYSTICK_ENABLE_MASK; /* enable counting */
	start_value = SysTick_Base_Ptr->CVR;
	memmove_dma(area_one, area_two, 10, 4);
	SysTick_Base_Ptr->CVR = 0;
	SysTick_Base_Ptr->CSR &= ~(__SYSTICK_ENABLE_MASK); /* disable counting */
    my_string = "Profiling the DMA memmove function with 10 bytes and 4 byte transfer took ";
	UART_send_n(my_string, 74);
	printsize = my_itoa((int32_t)(start_value-DMA_end_value), my_string, 10);
	UART_send_n(my_string, printsize);
    my_string = " clock cycles to run\r\n";
	UART_send_n(my_string, 22);
	/* 100 bytes */
	SysTick_Base_Ptr->CSR |= __SYSTICK_ENABLE_MASK; /* enable counting */
	start_value = SysTick_Base_Ptr->CVR;
	memmove_dma(area_one, area_two, 100, 4);
	SysTick_Base_Ptr->CVR = 0;
	SysTick_Base_Ptr->CSR &= ~(__SYSTICK_ENABLE_MASK); /* disable counting */
    my_string = "Profiling the DMA memmove function with 100 bytes and 4 byte transfer took ";
	UART_send_n(my_string, 75);
	printsize = my_itoa((int32_t)(start_value-DMA_end_value), my_string, 10);
	UART_send_n(my_string, printsize);
    my_string = " clock cycles to run\r\n";
	UART_send_n(my_string, 22);
	/* 1000 bytes */
	SysTick_Base_Ptr->CSR |= __SYSTICK_ENABLE_MASK; /* enable counting */
	start_value = SysTick_Base_Ptr->CVR;
	memmove_dma(area_one, area_two, 1000, 4);
	SysTick_Base_Ptr->CVR = 0;
	SysTick_Base_Ptr->CSR &= ~(__SYSTICK_ENABLE_MASK); /* disable counting */
    my_string = "Profiling the DMA memmove function with 1000 bytes and 4 byte transfer took ";
	UART_send_n(my_string, 76);
	printsize = my_itoa((int32_t)(start_value-DMA_end_value), my_string, 10);
	UART_send_n(my_string, printsize);
    my_string = " clock cycles to run\r\n";
	UART_send_n(my_string, 22);
	/* 5000 bytes */
	SysTick_Base_Ptr->CSR |= __SYSTICK_ENABLE_MASK; /* enable counting */
	start_value = SysTick_Base_Ptr->CVR;
	memmove_dma(area_one, area_two, 5000, 4);
	SysTick_Base_Ptr->CVR = 0;
	SysTick_Base_Ptr->CSR &= ~(__SYSTICK_ENABLE_MASK); /* disable counting */
    my_string = "Profiling the DMA memmove function with 5000 bytes and 4 byte transfer took ";
	UART_send_n(my_string, 76);
	printsize = my_itoa((int32_t)(start_value-DMA_end_value), my_string, 10);
	UART_send_n(my_string, printsize);
    my_string = " clock cycles to run\r\n";
	UART_send_n(my_string, 22);
}

void spi_setup_and_test()
{
	GPIO_Configure();
	SPI_init();
    UART_configure();
    uint8_t my_string[] = "Starting project 3...";
    uint8_t return_string[] = "\r\n";
    uint8_t hex_string[] = "Status Reg is: 0x";
    UART_send_n(my_string, sizeof(my_string));
    UART_send_n(return_string, sizeof(return_string));
	uint16_t i = 0x00;
	uint8_t j = 0x00;
	uint8_t statreg = 0x00;
	uint8_t printsize = 0x00;
	nrf_write_register(0x05, j);
	statreg = nrf_read_register(0x05);
	printsize = my_itoa((int32_t)statreg, my_string, 16);
	UART_send_n(hex_string, sizeof(hex_string));
	UART_send_n(my_string, printsize);
	UART_send_n(return_string, sizeof(return_string));
}