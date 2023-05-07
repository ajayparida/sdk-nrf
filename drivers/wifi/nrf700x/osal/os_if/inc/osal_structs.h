/*
 * Copyright (c) 2022 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */
/**
 * @file osal_structs.h
 * @brief Contains structure declaration for the OSAL Layer.
 */

#ifndef __OSAL_STRUCTS_H__
#define __OSAL_STRUCTS_H__

#include <stddef.h>

/**@brief The status of an operation performed by the RPU driver. */
enum wifi_nrf_status {
	WIFI_NRF_STATUS_SUCCESS,	/**< Successful. */
	WIFI_NRF_STATUS_FAIL = -1,	/**< Failed. */
};


/**@brief DMA direction for a DMA operation. */
enum wifi_nrf_osal_dma_dir {
	WIFI_NRF_OSAL_DMA_DIR_TO_DEV,	/**< DMAed to the device. */
	WIFI_NRF_OSAL_DMA_DIR_FROM_DEV, /**< DMAed from the device. */
	WIFI_NRF_OSAL_DMA_DIR_BIDI	/**< DMAed in either direction */
};


struct wifi_nrf_osal_host_map {
	unsigned long addr;
	unsigned long size;
};


struct wifi_nrf_osal_priv {
	const struct wifi_nrf_osal_ops *ops;
};
#endif /* __OSAL_STRUCTS_H__ */
