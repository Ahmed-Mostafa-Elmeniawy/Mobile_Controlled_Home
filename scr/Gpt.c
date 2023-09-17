/*
 * Gpt.c
 *
 *  Created on: Feb 24, 2023
 *      Author: ahmad
 */


#include "Types.h"
#include "Registers.h"
#include "Macros.h"
#include "Interrupts.h"
#include "Gpt.h"

void (*Gpt_Callback_TIM0_COMP ) (void) = NULL_PTR;
void (*Gpt_Callback_TIM0_OVF  ) (void) = NULL_PTR;
void (*Gpt_Callback_TIM1A_COMP) (void) = NULL_PTR;
void (*Gpt_Callback_TIM1B_COMP) (void) = NULL_PTR;
void (*Gpt_Callback_TIM1_OVF  ) (void) = NULL_PTR;
void (*Gpt_Callback_TIM1_CAPT ) (void) = NULL_PTR;
void (*Gpt_Callback_TIM2_OVF  ) (void) = NULL_PTR;
void (*Gpt_Callback_TIM2_COMP ) (void) = NULL_PTR;

ISR(VECTOR_TIM0_COMP) {
    if (NULL_PTR != Gpt_Callback_TIM0_COMP) {
        Gpt_Callback_TIM0_COMP();
    }
}

ISR(VECTOR_TIM0_OVF) {
    if (NULL_PTR != Gpt_Callback_TIM0_OVF) {
        Gpt_Callback_TIM0_OVF();
    }
}

/** TODO: Complete all ISRs (4 ISRs for Timer 1, 2 ISRs for Tomer 2)*/


void Gpt_Init(Gpt_ChannelType channel, const Gpt_ConfigType* config) {
    switch (channel)
    {
    case GPT_CHANNEL_TIM0:
    {
        switch (config->mode)
        {
        case GPT_MODE_NORMAL:
            CLR_BIT(TCCR0, 3);
            CLR_BIT(TCCR0, 6);
            break;
        case GPT_MODE_CTC:
            CLR_BIT(TCCR0, 3);
            SET_BIT(TCCR0, 6);
            break;
        default:
            break;
        }
        switch (config->compareMode)
        {
        case GPT_COMP_OUT_MODE_DISCONNECTED:
            CLR_BIT(TCCR0, 4);
            CLR_BIT(TCCR0, 5);
            break;
        case GPT_COMP_OUT_MODE_TOGGLE:
            SET_BIT(TCCR0, 4);
            CLR_BIT(TCCR0, 5);
            break;
        case GPT_COMP_OUT_MODE_CLEAR:
            CLR_BIT(TCCR0, 4);
            SET_BIT(TCCR0, 5);
            break;
        case GPT_COMP_OUT_MODE_SET:
            SET_BIT(TCCR0, 4);
            SET_BIT(TCCR0, 5);
            break;
        default:
            break;
        }
        break;
    }
    case GPT_CHANNEL_TIM2:
    {
        switch (config->mode)
        {
        case GPT_MODE_NORMAL:
            CLR_BIT(TCCR2, 3);
            CLR_BIT(TCCR2, 6);
            break;
        default:
            break;
        }
        switch (config->compareMode)
        {
        case GPT_COMP_OUT_MODE_DISCONNECTED:
            CLR_BIT(TCCR2, 3);
            CLR_BIT(TCCR2, 6);
            break;
        default:
            break;
        }
        break;
    }
    /** TODO: Complete all cases (TIM1, TIM2) */
    default:
        break;
    }
}

void Gpt_Start(Gpt_ChannelType channel, Gpt_PrescalerType prescaler) {
    switch (channel)
    {
    case GPT_CHANNEL_TIM0:
    {
        switch (prescaler)
        {
        case GPT_PRESCALER_1:
            SET_BIT(TCCR0,0);
            CLR_BIT(TCCR0,1);
            CLR_BIT(TCCR0,2);
            break;
        case GPT_PRESCALER_8:
            CLR_BIT(TCCR0,0);
            SET_BIT(TCCR0,1);
            CLR_BIT(TCCR0,2);
            break;
        case GPT_PRESCALER_64:
            SET_BIT(TCCR0,0);
            SET_BIT(TCCR0,1);
            CLR_BIT(TCCR0,2);
            break;
        case GPT_PRESCALER_256:
            CLR_BIT(TCCR0,0);
            CLR_BIT(TCCR0,1);
            SET_BIT(TCCR0,2);
            break;
        case GPT_PRESCALER_1024:
            SET_BIT(TCCR0,0);
            CLR_BIT(TCCR0,1);
            SET_BIT(TCCR0,2);
            break;
        case GPT_PRESCALER_EXT_FALLING:
            CLR_BIT(TCCR0,0);
            SET_BIT(TCCR0,1);
            SET_BIT(TCCR0,2);
            break;
        case GPT_PRESCALER_EXT_RISING:
            SET_BIT(TCCR0,0);
            SET_BIT(TCCR0,1);
            SET_BIT(TCCR0,2);
            break;
        default:
            break;
        }
        TCNT0 = 0;
        break;
    }
    case GPT_CHANNEL_TIM2:
    {
        switch (prescaler)
        {
        case GPT_PRESCALER_1024:
            SET_BIT(TCCR2, 0);
            SET_BIT(TCCR2, 1);
            SET_BIT(TCCR2, 2);
            break;
        
        }
        TCNT2 = 0;
        break;
    }
    default:
        break;
    }
}

void Gpt_Stop(Gpt_ChannelType channel) {
    switch (channel)
    {
    case GPT_CHANNEL_TIM0:
        CLR_BIT(TCCR0, 2);
        CLR_BIT(TCCR0, 1);
        CLR_BIT(TCCR0, 0);
        break;
    case GPT_CHANNEL_TIM2:
        CLR_BIT(TCCR2, 2);
        CLR_BIT(TCCR2, 1);
        CLR_BIT(TCCR2, 0);
        break;
    /** TODO: Complete all Cases (TIM1, TIM2)*/
    default:
        break;
    }
}

void Gpt_Reset (Gpt_ChannelType channel) {
    switch (channel)
    {
    case GPT_CHANNEL_TIM0:
        TCNT0 = 0;
        break;
    /** TODO: Complete all Cases (TIM1, TIM2)*/
    default:
        break;
    }
}

void Gpt_SetCounterValue (Gpt_ChannelType channel, u16 value) {
    switch (channel)
    {
    case GPT_CHANNEL_TIM0:
        TCNT0 = value;
        break;
    /** TODO: Complete all Cases (TIM1, TIM2)*/
    default:
        break;
    }
}

void Gpt_SetCompareValue (Gpt_CompareRegType reg, u16 value) {
    switch (reg)
    {
    case GPT_COMP_REG_TIM0:
        OCR0 = value;
        break;
    /** TODO: Complete all Cases (TIM1A, TIM1B, TIM2)*/
    default:
        break;
    }
}

void Gpt_EnableNotification(Gpt_InterruptSourceType source) {
    switch (source)
    {
    case GPT_INT_SOURCE_TIM0_COMP:
        SET_BIT(TIMSK, 1);
        break;
    case GPT_INT_SOURCE_TIM0_OVF:
        SET_BIT(TIMSK, 0);
        break;
    /** TODO: Complete all Cases (4 ISRs for Timer 1, 2 ISRs for Tomer 2)*/
    default:
        break;
    }
}

void Gpt_DisableNotification(Gpt_InterruptSourceType source) {
    switch (source)
    {
    case GPT_INT_SOURCE_TIM0_COMP:
        CLR_BIT(TIMSK, 1);
        break;
    case GPT_INT_SOURCE_TIM0_OVF:
        CLR_BIT(TIMSK, 0);
        break;
    /** TODO: Complete all Cases (4 ISRs for Timer 1, 2 ISRs for Tomer 2)*/
    default:
        break;
    }
}

void Gpt_SetCallback(Gpt_InterruptSourceType source, void (*funcPtr) (void)) {
    switch (source)
    {
    case GPT_INT_SOURCE_TIM0_COMP:
        Gpt_Callback_TIM0_COMP = funcPtr;
        break;
    case GPT_INT_SOURCE_TIM0_OVF:
        Gpt_Callback_TIM0_OVF = funcPtr;
        break;
    /** TODO: Complete all Cases (4 ISRs for Timer 1, 2 ISRs for Tomer 2)*/
    default:
        break;
    }
}


u16  Gpt_GetElapsedTime(Gpt_ChannelType channel) {
    u16 ret_value = 0;
    switch (channel)
    {
    case GPT_CHANNEL_TIM0:
        ret_value = TCNT0;
        break;
    case GPT_CHANNEL_TIM1:
        /** TODO: */
        break;
    case GPT_CHANNEL_TIM2:
        /** TODO: */
        break;
    default:
        break;
    }
    return ret_value;
}

void Gpt_Delay(u16 milli_sec)
{

    volatile u8 overflow_counter = 0;
    volatile u16 No_of_overflows = 0;
    volatile u8 overflow_flag = 0;

    No_of_overflows = (milli_sec / 33); // The number 33 is the overflow duration in milli-seconds of a 1024 prescaler

    Gpt_Start(GPT_CHANNEL_TIM2, GPT_PRESCALER_1024);

    while (overflow_counter < No_of_overflows)
    {
        overflow_counter++;

        while (overflow_flag == 0) //Busy wait
        {
            Gpt_GetOverflowFlag(GPT_CHANNEL_TIM2, &overflow_flag);
        }

        Gpt_ClearFlag(GPT_CHANNEL_TIM2, GPT_INT_SOURCE_TIM2_OVF);
        overflow_flag = 0;
    }

    overflow_counter = 0;
    Gpt_Stop(GPT_CHANNEL_TIM2);

}


void Gpt_ClearFlag(Gpt_ChannelType channel, Gpt_InterruptSourceType interrupt_type)
{

    switch (channel)
    {
    case GPT_CHANNEL_TIM0:
        switch (interrupt_type)
        {
        case GPT_INT_SOURCE_TIM0_OVF:
            SET_BIT(TIFR, 0);
            break;
        default:
            break;
        }
        /*Continue the rest*/
        break;

    case GPT_CHANNEL_TIM2:
        switch (interrupt_type)
        {
        case GPT_INT_SOURCE_TIM2_OVF:
            SET_BIT(TIFR, 6);
            break;
        default:
            break;
        }
        /*Continue the rest*/
        break;

        /*Continue the rest*/
    default:
        break;
    }

}


void Gpt_GetOverflowFlag(Gpt_ChannelType channel, volatile u8* returnValue)
{

    switch (channel)
    {
    case GPT_CHANNEL_TIM0:
        *returnValue = GET_BIT(TIFR, 0);
        break;
    case GPT_CHANNEL_TIM2:
        *returnValue = GET_BIT(TIFR, 6);
        break;
        /* Continue the remaining cases of TIM1 */
    default:
        break;
    }

}
