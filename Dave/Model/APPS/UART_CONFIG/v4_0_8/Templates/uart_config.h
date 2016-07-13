/**
 * @file uart_config.h
 * @date 2015-08-19
 *
 * NOTE:
 * This file is generated by DAVE-4. Any manual modification done to this file will be lost when the code is
 * regenerated.
 *
 * @cond
 ***********************************************************************************************************************
 * UART_CONFIG v4.0.8 - Configures a USIC channel to perform transmit & receive operations using UART protocol.
 *
 * Copyright (c) 2015, Infineon Technologies AG
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,are permitted provided that the
 * following conditions are met:
 *
 *   Redistributions of source code must retain the above copyright notice, this list of conditions and the  following
 *   disclaimer.
 *
 *   Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
 *   disclaimer in the documentation and/or other materials provided with the distribution.
 *
 *   Neither the name of the copyright holders nor the names of its contributors may be used to endorse or promote
 *   products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE  FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY,OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT  OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * To improve the quality of the software, users are encouraged to share modifications, enhancements or bug fixes
 * with Infineon Technologies AG (dave@infineon.com).
 ***********************************************************************************************************************
 *
 * Change History
 * --------------
 *
 * 2015-07-09:
 *     - Initial version for DAVEv4
 *
 * 2015-08-19
 *     - Removed internal pad consumption
 *
 * @endcond
 */
/***********************************************************************************************************************
 * HEADER FILES
 **********************************************************************************************************************/
#ifndef UART_CONFIG_H
#define UART_CONFIG_H

#include <xmc_uart.h>

#if (!((XMC_LIB_MAJOR_VERSION == 2U) && \
    (XMC_LIB_MINOR_VERSION >= 0U) && \
    (XMC_LIB_PATCH_VERSION >= 0U)))
#error "UART_CONFIG requires XMC Peripheral Library v2.0.0 or higher"
#endif

#include <DAVE_common.h>
#include "uart_config_conf.h"

/***********************************************************************************************************************
 * MACROS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * enumS
 **********************************************************************************************************************/
/**
 * @ingroup UART_CONFIG_enumerations
 * @{
 */
/**
 * @brief enum to describe the possible status values, returned by UART_CONFIG APIs.
 */
typedef enum UART_CONFIG_STATUS
{
  UART_CONFIG_STATUS_SUCCESS = 0U,   /**< Indicates App initialization state successful */
  UART_CONFIG_STATUS_FAILURE         /**< Unknown error */

} UART_CONFIG_STATUS_t;

/**
 * @brief enum used to describe the UART_CONFIG mode of operation
 */
typedef enum UART_CONFIG_MODE
{
  UART_CONFIG_MODE_FULLDUPLEX,   /**< Full Duplex mode selected */
  UART_CONFIG_MODE_HALFDUPLEX,   /**< Half Duplex mode selected */
  UART_CONFIG_MODE_LOOPBACK,     /**< Loop Back mode selected */
  UART_CONFIG_MODE_IRDA          /**< IrDA mode selected */

} UART_CONFIG_MODE_t;
/**
 * @}
 */

/***********************************************************************************************************************
 * DATA STRUCTURES
 **********************************************************************************************************************/
typedef void (*UART_CONFIG_func_ptr) (void);

/**
 * @ingroup UART_CONFIG_datastructures
 * @{
 */

/**
 * @brief Structure for holding the configuration parameters of the UART channel.
 */
typedef struct UART_CONFIG_CONF
{
  const XMC_UART_CH_CONFIG_t * const channel_config;          /**< UART configuration from the GUI */
  const uint8_t sample_point;                                 /**< Sample point of the bit value maximum = oversampling - 1 (DCTQ) */
  const uint8_t pulse_length;                                 /**< Length of a 0 data bit (in time quanta). Used for IrDA. maximum = oversampling - 1 (DCTQ) */
  const UART_CONFIG_func_ptr uart_config_init;                /**< Function pointer to configure usic channel for UART */
  const UART_CONFIG_MODE_t mode;                              /**< UART operation mode */
  const XMC_USIC_CH_FIFO_SIZE_t tx_fifo_size;                 /**< Transmit FIFO size configuration */
  const XMC_USIC_CH_FIFO_SIZE_t rx_fifo_size;                 /**< Receive FIFO size configuration */
  const uint8_t tx_fifo_limit;                                /**< Transmit FIFO limit for interrupt generation */
  const uint8_t rx_fifo_limit;                                /**< Receive FIFO limit for interrupt generation */

} UART_CONFIG_CONF_t;

/**
 * @brief Handler structure with pointers to static parameters.
 */
typedef struct UART_CONFIG
{
  XMC_USIC_CH_t * const channel;                  /**< USIC channel */
  const UART_CONFIG_CONF_t * const config;   /**< UART_CONFIG configuration structure pointer */
} UART_CONFIG_t;
/**
 * @}
 */

/***********************************************************************************************************************
 * API Prototypes
 **********************************************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @ingroup UART_CONFIG_apidoc
 * @{
 */

/**
 * @brief Get the UART_CONFIG APP version.
 * @return DAVE_APP_VERSION_t APP version information (major, minor and patch number)
 *
 * Example Usage:
 * @code
 *   #include <DAVE.h>
 *
 *   int main(void)
 *   {
 *     UART_CONFIG_STATUS_t init_status;
 *     DAVE_APP_VERSION_t uart_config_version;
 *     uint8_t valid_str[] = "UART_CONFIG APP supported!";
 *
 *     init_status = (UART_CONFIG_STATUS_t)UART_CONFIG_Init(&UART_CONFIG_0);
 *     if(init_status == UART_CONFIG_STATUS_SUCCESS)
 *     {
 *       uart_config_version = UART_CONFIG_GetAppVersion();
 *       if((uart_config_version.major == 0) &&
 *          (uart_config_version.minor == 1))
 *       {
 *       }
 *     }
 *     else
 *     {
 *       XMC_DEBUG("main: Application initialization failed");
 *       while(1U)
 *       {
 *       }
 *     }
 *      return 1U;
 *  }
 *  @endcode
 */
DAVE_APP_VERSION_t UART_CONFIG_GetAppVersion(void);

/**
 * @brief Function to initialize the UART module as per the configuration made
 * in GUI.
 * @param handle Pointer to static content of APP configuration.
 * @return UART_CONFIG_STATUS_t: Status of the UART driver initialization.\n
 *   @ref UART_CONFIG_STATUS_SUCCESS - on successful initialization.\n
 *   @ref UART_CONFIG_STATUS_FAILURE - if initialization fails.\n
 *
 * \par<b>Description:</b><br>
 * This function configures USIC registers based on the settings provided in the GUI.
 * <BR>
 *
 * Example Usage:
 * @code
 *   #include <DAVE.h>   // Declarations from DAVE Code Generation (includes SFR declaration)
 *
 *   int main(void)
 *   {
 *     UART_CONFIG_STATUS_t init_status;
 *
 *     init_status = (UART_CONFIG_STATUS_t)UART_CONFIG_Init(&UART_CONFIG_0);
 *     if(init_status == UART_CONFIG_STATUS_SUCCESS)
 *     {
 *         while(1U)
 *         {
 *         }
 *     }
 *     else
 *     {
 *      XMC_DEBUG("main: Application initialization failed");
 *      while(1U)
 *      {
 *      }
 *     }
 *      return 1U;
 *  }
 *  @endcode
 */
UART_CONFIG_STATUS_t UART_CONFIG_Init(const UART_CONFIG_t *const handle);

/**
 * @}
 */

/* Include App extern declaration file */
#include "uart_config_extern.h"

#ifdef __cplusplus
}
#endif

#endif /* UART_CONFIG_H_ */
