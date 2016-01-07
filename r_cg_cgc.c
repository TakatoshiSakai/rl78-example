/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only 
* intended for use with Renesas products. No other uses are authorized. This 
* software is owned by Renesas Electronics Corporation and is protected under 
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING 
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT 
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE 
* AND NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS 
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE 
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR 
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE 
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software 
* and to discontinue the availability of this software.  By using this software, 
* you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2012 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_cg_cgc.c
* Version      : Applilet3 for RL78/L12 V1.00.00 [23 Mar 2012]
* Device(s)    : R5F10RLC
* Tool-Chain   : GNURL78 v13.01
* Description  : This file implements device driver for CGC module.
* Creation Date: 21/01/2013
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_cgc.h"
#include "r_cg_lcd.h"
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* CRC check result for the normal mode */
uint16_t g_result = 0;

/* Indicates state of STOP power mode */
uint8_t g_stop_mode = 0;


/***********************************************************************************************************************
* Function Name: R_CGC_Create
* Description  : This function initialises the clock generator.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_CGC_Create (void)
{
    /* Temporary delay counter */
    volatile uint16_t w_count;
    
    /* Set fMX (sub-clock configured for ultra-low power consumption oscillation */
    CMC = 0x14;
    
    /* Disable the X1 oscillator */
    MSTOP = 1U;
    
    /* Set fMAIN */
    MCM0 = 0U;
    
    /* Set fSUB (enable the sub-clock) */
    XTSTOP = 0U;
    
    /* Software wait 5us or more */
    for (w_count = 0U; w_count <= CGC_SUBWAITTIME; w_count++)
    {
        /* Add 1 instruction delay */
        asm("nop");
    }
    
    /* Enable sub-clock supply to all peripherals */
    OSMC = 0x00;
    
    /* Set fCLK */
    CSS = 0U;
    
    /* Enable fIH (enable high-speed on-chip oscillator) */
    HIOSTOP = 0U;
}
/***********************************************************************************************************************
* End of function R_CGC_Create
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: SFR_Guard
* Description  : This function demonstrates the SFR guard function.
* Arguments    : uint8_t protect_on 
* Return Value : None
***********************************************************************************************************************/
void SFR_Guard (uint8_t const protect_on)
{
    /* Check if SFR guard is requested or not */
    if (1u == protect_on)
    {
        /* SFR protected */
        IAWCTL  |= 0x04u;
    }
    else
    {
        /* SFR unprotected */
        IAWCTL  &= ~0x04u;
    }
}
/***********************************************************************************************************************
* End of function SFR_Guard
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: RAM_Guard
* Description  : This function demonstrates the RAM guard function.
* Arguments    : uint8_t protect_on 
* Return Value : None
***********************************************************************************************************************/
void RAM_Guard (uint8_t const protect_on)
{
    /* Check if RAM guard is requested or not */
    if (1u == protect_on)
    {
        /* RAM protection on (First 128 bytes) */
        IAWCTL  |= 0x10u;
    }
    else
    {
        /* RAM protection off */
        IAWCTL  &= ~0x10u;
    }
}
/***********************************************************************************************************************
* End of function RAM_Guard
***********************************************************************************************************************/
