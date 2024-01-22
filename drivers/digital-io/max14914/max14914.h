/***************************************************************************//**
 *   @file   max14914.h
 *   @brief  Header file of MAX14914 Driver.
 *   @author Radu Sabau (radu.sabau@analog.com)
********************************************************************************
 * Copyright 2024(c) Analog Devices, Inc.
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *  - Neither the name of Analog Devices, Inc. nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *  - The use of this software may or may not infringe the patent rights
 *    of one or more patent holders.  This license does not release you
 *    from the requirement that you obtain separate licenses from these
 *    patent holders to use this software.
 *  - Use of the software either in source or binary form, must be run
 *    on or directly connected to an Analog Devices Inc. component.
 *
 * THIS SOFTWARE IS PROVIDED BY ANALOG DEVICES "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, NON-INFRINGEMENT,
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL ANALOG DEVICES BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, INTELLECTUAL PROPERTY RIGHTS, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*******************************************************************************/
#ifndef _MAX14914_H
#define _MAX14914_H

#include <stdint.h>
#include <stdbool.h>
#include "no_os_gpio.h"
#include "no_os_util.h"

enum max14914_state {
	MAX14914_DIGITAL_OUTPUT_PP,
	MAX14914_DIGITAL_OUTPUT_HIGH_SIDE,
	MAX14914_DIGITAL_OUTPUT_LOW_SIDE,
	MAX14914_DIGITAL_INPUT_IEC_TYPE1_3,
	MAX14914_DIGITAL_INPUT_IEC_TYPE2
};

/**
 * @brief Structure holding the MAX14914 device descriptor
*/
struct max14914_desc {
	enum max14914_state current_state;
	struct no_os_gpio_desc *fault_gpio;
	struct no_os_gpio_desc *doilvl_gpio;
	struct no_os_gpio_desc *di_en_gpio;
	struct no_os_gpio_desc *in_gpio;
	struct no_os_gpio_desc *pp_gpio;
};

/**
 * @brief Structure holding the MAX14914 initialization parameter.
*/
struct max14914_init_param {
	struct no_os_gpio_init_param *fault_init_param;
	struct no_os_gpio_init_param *doilvl_init_param;
	struct no_os_gpio_init_param *di_en_init_param;
	struct no_os_gpio_init_param *in_init_param;
	struct no_os_gpio_init_param *pp_init_param;
};

/* Set the state of the MAX14914. */
int max14914_set_state(struct max14914_desc *desc, enum max14914_state state);

/* Initialize the MAX14914 device descriptor. */
int max14914_init(struct max14914_desc **desc,
		  struct max14914_init_param *init_param);

/* Free resources allocate by the init function. */
int max14914_remove(struct max14914_desc *desc);

#endif /* _MAX14914_H */
