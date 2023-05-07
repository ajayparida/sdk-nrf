/*
 * Copyright (c) 2022 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

/**
 * @file fmac_api.h
 * @brief API for the FMAC IF Layer of the Wi-Fi driver.
 */

#ifndef __FMAC_API_H__
#define __FMAC_API_H__

#include <stdbool.h>

#include "osal_api.h"
#include "host_rpu_umac_if.h"
#include "host_rpu_data_if.h"
#include "host_rpu_sys_if.h"

#include "fmac_structs.h"
#include "fmac_cmd.h"
#include "fmac_event.h"
#include "fmac_vif.h"
#include "fmac_bb.h"


#ifdef CONFIG_NRF700X_RADIO_TEST
/**
 * @brief Initializes the UMAC IF layer.
 *
 * @details This function initializes the UMAC IF layer of the RPU WLAN FullMAC driver.
 * 	    It does the following:
 *
 *		- Creates and initializes the context for the UMAC IF layer.
 *		- Initializes the HAL layer.
 *		- Registers the driver to the underlying OS.
 *
 * @return Pointer to the context of the UMAC IF layer.
 */
struct wifi_nrf_fmac_priv *wifi_nrf_fmac_init(void);


/**
 * @brief Issue a request to get stats from the RPU.
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 * @param op_mode Production/FCM mode.
 * @param stats Pointer to memory where the stats are to be copied.
 *
 * @details This function is used to send a command to
 * 	    instruct the firmware to return the current RPU statistics.
 * 	    The RPU will send the event with the current statistics.
 *
 * @return Command execution status
 */
enum wifi_nrf_status wifi_nrf_fmac_stats_get(struct wifi_nrf_fmac_dev_ctx *fmac_dev_ctx,
					     int op_mode,
					     struct rpu_op_stats *stats);


/**
 * @brief Initialize the RPU for radio tests.
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 * @param params Parameters necessary for the initialization.
 *
 * @details This function is used to send a command to RPU to initialize it
 *	    for the radio test mode.
 *
 * @return Command execution status
 */
enum wifi_nrf_status wifi_nrf_fmac_radio_test_init(struct wifi_nrf_fmac_dev_ctx *fmac_dev_ctx,
						   struct rpu_conf_params *params);

/**
 * @brief Start TX tests in radio test mode.
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 * @param params Parameters necessary for the TX tests.
 *
 * @details This function is used to send a command to RPU to start
 *	    the TX tests in radio test mode.
 *
 * @return Command execution status
 */
enum wifi_nrf_status wifi_nrf_fmac_radio_test_prog_tx(struct wifi_nrf_fmac_dev_ctx *fmac_dev_ctx,
						      struct rpu_conf_params *params);

/**
 * @brief Start RX tests in radio test mode.
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 * @param params Parameters necessary for the RX tests.
 *
 * @details This function is used to send a command to RPU to start
 *	    the RX tests in radio test mode.
 *
 * @return Command execution status
 */
enum wifi_nrf_status wifi_nrf_fmac_radio_test_prog_rx(struct wifi_nrf_fmac_dev_ctx *fmac_dev_ctx,
						      struct rpu_conf_params *params);


/**
 * @brief Start RF test capture in radio test mode.
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 * @param cap_data Pointer to the memory where the RF test capture is to be stored.
 * @param num_samples Number of RF test samples to capture.
 * @param lna_gain LNA gain value.
 * @param bb_gain Baseband gain value.
 *
 * @details This function is used to send a command to RPU to start
 *	    the RF test capture in radio test mode.
 *
 * @return Command execution status
 */
enum wifi_nrf_status nrf_wifi_fmac_rf_test_rx_cap(struct wifi_nrf_fmac_dev_ctx *fmac_dev_ctx,
						  enum nrf_wifi_rf_test rf_test_type,
						  void *cap_data,
						  unsigned short int num_samples,
						  unsigned char lna_gain,
						  unsigned char bb_gain);


/**
 * @brief Start/Stop RF TX tone test in radio test mode.
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 * @param enable Enable/Disable TX tone test.
 * @param tone_freq Desired tone frequency in MHz in steps of 1 MHz from -10 MHz to +10 MHz.
 * @param tx_power Desired TX power in the range -16dBm to +24dBm.
 *
 * @details This function is used to send a command to RPU to start the RF TX tone test
 * 	    in radio test mode.
 *
 * @return Command execution status
 */
enum wifi_nrf_status nrf_wifi_fmac_rf_test_tx_tone(struct wifi_nrf_fmac_dev_ctx *fmac_dev_ctx,
						  unsigned char enable,
						  signed char tone_freq,
						  signed char tx_power);



/**
 * @brief Start/Stop RF DPD test in radio test mode.
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 * @param enable Enable/Disable DPD test.
 *
 * @details This function is used to send a command to RPU to start
 *	    the RF DPD test in radio test mode.
 *
 * @return Command execution status
 */
enum wifi_nrf_status nrf_wifi_fmac_rf_test_dpd(struct wifi_nrf_fmac_dev_ctx *fmac_dev_ctx,
					       unsigned char enable);



/**
 * @brief Get temperature in fahrenheit using temperature sensor.
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 *
 * @details This function is used to send a command to RPU to get the current temperature.
 *	    using the radio test mode.
 *
 * @return Command execution status
 */
enum wifi_nrf_status nrf_wifi_fmac_rf_get_temp(struct wifi_nrf_fmac_dev_ctx *fmac_dev_ctx);



/**
 * @brief Get RF RSSI status.
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 *
 * @details This function is used to send a command to RPU to get
 *	    RF RSSI status in radio test mode.
 *
 * @return Command execution status
 */
enum wifi_nrf_status nrf_wifi_fmac_rf_get_rf_rssi(struct wifi_nrf_fmac_dev_ctx *fmac_dev_ctx);


/**
 * @brief set XO adjustment value.
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 * @param value XO adjustment value.
 *
 * @details This function is used to send a command to RPU to set XO adjustment
 *	    value in radio test mode.
 *
 * @return Command execution status
 */
enum wifi_nrf_status nrf_wifi_fmac_set_xo_val(struct wifi_nrf_fmac_dev_ctx *fmac_dev_ctx,
					      unsigned char value);

/**
 * @brief Get XO calibrated value.
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 *
 * @details This function is used to send a command to RPU. RPU estimates and
 *	    returns optimal XO value.
 *
 * @return Command execution status
 */
enum wifi_nrf_status nrf_wifi_fmac_rf_test_compute_xo(struct wifi_nrf_fmac_dev_ctx *fmac_dev_ctx);
#else

/**
 * @brief Initializes the UMAC IF layer.
 *
 * @param rx_buf_pools Pointer to configuration of Rx queue buffers.
 *		       See rx_buf_pool_params
 *
 * @details This function initializes the UMAC IF layer.It does the following:
 *	    - Creates and initializes the context for the UMAC IF layer.
 *	    - Initializes the HAL layer. 
 *	    - Registers the driver to the underlying OS.
 *
 * @return Pointer to the context of the UMAC IF layer.
 */
struct wifi_nrf_fmac_priv *wifi_nrf_fmac_init(struct nrf_wifi_data_config_params *data_config,
					      struct rx_buf_pool_params *rx_buf_pools,
					      struct wifi_nrf_fmac_callbk_fns *callbk_fns);

/**
 * @brief Issue a request to get stats from the RPU.
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 * @param stats_type The type of RPU statistics to get.
 * @param stats Pointer to memory where the stats are to be copied.
 *
 * @details This function is used to send a command to
 * 	    instruct the firmware to return the current RPU statistics. The RPU will
 *	    send the event with the current statistics.
 *
 * @return Command execution status
 */
enum wifi_nrf_status wifi_nrf_fmac_stats_get(struct wifi_nrf_fmac_dev_ctx *fmac_dev_ctx,
					     struct rpu_op_stats *stats);


/**
 * @brief Issue a scan request to the RPU.
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 * @param if_idx Index of the interface on which the scan is to be performed.
 * @param scan_info: The parameters needed by the RPU for scan operation.
 *
 * @details This function is used to send a command to
 *	    instruct the firmware to trigger a scan. The scan can be performed in two
 *	    modes:
 *
 *	    Auto Mode (%AUTO_SCAN):
 *     		In this mode the host does not need to specify any scan specific
 *     		rameters. The RPU will perform the scan on all the channels permitted
 *     		by and abiding by the regulations imposed by the
 *     		WORLD (common denominator of all regulatory domains) regulatory domain.
 *     		The scan will be performed using the wildcard SSID.
 *
 * 	    Channel Map Mode (%CHANNEL_MAPPING_SCAN):
 *      	In this mode the host can have fine grained control over the scan
 *      	specific parameters to be used (e.g. Passive/Active scan selection,
 *      	Number of probe requests per active scan, Channel list to scan,
 *      	Permanence on each channel, SSIDs to scan etc.). This mode expects
 *      	the regulatory restrictions to be taken care by the invoker of the
 *      	API.
 *
 * @return Command execution status
 */
enum wifi_nrf_status wifi_nrf_fmac_scan(void *fmac_dev_ctx,
					unsigned char if_idx,
					struct nrf_wifi_umac_scan_info *scan_info);


/**
 * @brief Issue a scan results request to the RPU.
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 * @param if_idx Index of the interface on which the scan results are to be fetched.
 * @param scan_ty: The scan type (i.e. DISPLAY or CONNECT scan).
 *
 * @details This function is used to send a command to
 *	    instruct the firmware to return the results of a scan.
 *
 * @return Command execution status
 */
enum wifi_nrf_status wifi_nrf_fmac_scan_res_get(void *fmac_dev_ctx,
						unsigned char if_idx,
						int scan_type);

/**
 * @brief Issue abort of an ongoing scan to the RPU.
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 * @param if_idx Index of the interface on which the scan results are to be fetched.
 *
 * @details This function is used to send a command to
 *	    instruct the firmware to abort an ongoing scan.
 *
 * @return Command execution status
 */
enum wifi_nrf_status wifi_nrf_fmac_abort_scan(void *dev_ctx,
						unsigned char if_idx);

#ifdef CONFIG_WPA_SUPP
/**
 * @brief Issue a authentication request to the RPU.
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 * @param if_idx Index of the interface on which the authentication is to be
 *	         performed.
 * @param auth_info The parameters needed by the RPU to generate the authentication
 *                  request.
 *
 * @details This function is used to send a command to
 *	    instruct the firmware to initiate a authentication request to an AP on the
 *	    interface identified with @if_idx.
 *
 * @return Command execution status
 */
enum wifi_nrf_status wifi_nrf_fmac_auth(void *fmac_dev_ctx,
					unsigned char if_idx,
					struct nrf_wifi_umac_auth_info *auth_info);


/**
 * @brief Issue a deauthentication request to the RPU.
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 * @param if_idx Index of the interface on which the deauthentication is to be
 *          	 performed.
 * @param deauth_info Deauthentication specific information required by the RPU.
 *
 * @details This function is used to send a command to
 *	    instruct the firmware to initiate a deauthentication notification to an AP
 *	    on the interface identified with @if_idx.
 *
 * @return Command execution status
 */
enum wifi_nrf_status wifi_nrf_fmac_deauth(void *fmac_dev_ctx,
					  unsigned char if_idx,
					  struct nrf_wifi_umac_disconn_info *deauth_info);


/**
 * @brief Issue a association request to the RPU.
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 * @param if_idx Index of the interface on which the association is to be
 *               performed.
 * @param assoc_info The parameters needed by the RPU to generate the association
 *           	     request.
 *
 * @details This function is used to send a command to
 * 	    instruct the firmware to initiate a association request to an AP on the
 * 	    interface identified with @if_idx.
 *
 * @return Command execution status
 */
enum wifi_nrf_status wifi_nrf_fmac_assoc(void *fmac_dev_ctx,
					 unsigned char if_idx,
					 struct nrf_wifi_umac_assoc_info *assoc_info);


/**
 * @brief Issue a disassociation request to the RPU.
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 * @param if_idx Index of the interface on which the disassociation is to be
 *	         performed.
 * @disassoc_info: Disassociation specific information required by the RPU.
 *
 * @details This function is used to send a command to
 * 	    instruct the firmware to initiate a disassociation notification to an AP
 *	    on the interface identified with @if_idx.
 *
 * @return Command execution status
 */
enum wifi_nrf_status wifi_nrf_fmac_disassoc(void *fmac_dev_ctx,
					    unsigned char if_idx,
					    struct nrf_wifi_umac_disconn_info *disassoc_info);


/**
 * @brief Add a key into the RPU security database.
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 * @param if_idx Index of the interface on which the key is to be added.
 * @param key_info Key specific information which needs to be passed to the RPU.
 * @param mac_addr MAC address of the peer with which the key is associated.
 *
 * @details This function is used to send a command to
 * 	    instruct the firmware to add a key to its security database.
 * 	    The key is for the peer identified by @mac_addr on the
 *	    interface identified with @if_idx.
 *
 * @return Command execution status
 */
enum wifi_nrf_status wifi_nrf_fmac_add_key(void *fmac_dev_ctx,
					   unsigned char if_idx,
					   struct nrf_wifi_umac_key_info *key_info,
					   const char *mac_addr);


/**
 * @brief Delete a key from the RPU security database.
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 * @param if_idx Index of the interface from which the key is to be deleted.
 * @param key_info Key specific information which needs to be passed to the RPU.
 * @param mac_addr MAC address of the peer with which the key is associated.
 *
 * @details This function is used to send a command to
 * 	    instruct the firmware to delete a key from its security database.
 * 	    The key is for the peer identified by @mac_addr  on the
 * 	    interface identified with @if_idx.
 *
 * @return Command execution status
 */
enum wifi_nrf_status wifi_nrf_fmac_del_key(void *fmac_dev_ctx,
					   unsigned char if_idx,
					   struct nrf_wifi_umac_key_info *key_info,
					   const char *mac_addr);


/**
 * @brief Set a key as a default for data or management
 *	  traffic in the RPU security database.
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 * @param if_idx Index of the interface on which the key is to be set.
 * @param key_info Key specific information which needs to be passed to the RPU.
 *
 * @details This function is used to send a command to
 *	    instruct the firmware to set a key as default in its security database.
 *	    The key is either for data or management traffic and is classified based on
 *	    the flags element set in @key_info parameter.
 *
 * @return Command execution status
 */
enum wifi_nrf_status wifi_nrf_fmac_set_key(void *fmac_dev_ctx,
					   unsigned char if_idx,
					   struct nrf_wifi_umac_key_info *key_info);


/**
 * @brief Set BSS parameters for an AP mode interface to the RPU.
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 * @param if_idx Index of the interface on which the BSS parameters are to be set.
 * @param bss_info BSS specific parameters which need to be passed to the RPU.
 *
 * @details This function is used to send a command to
 *	    instruct the firmware to set the BSS parameter for an AP mode interface.
 *
 * @return Command execution status
 */
enum wifi_nrf_status wifi_nrf_fmac_set_bss(void *fmac_dev_ctx,
					   unsigned char if_idx,
					   struct nrf_wifi_umac_bss_info *bss_info);


/**
 * @brief Update the Beacon Template.
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 * @param if_idx Index of the interface on which the Beacon Template is to be updated.
 * @param data Beacon Template which need to be passed to the RPU.
 *
 * @details This function is used to send a command to
 *	    instruct the firmware to update beacon template for an AP mode interface.
 *
 * @return Command execution status
 */
enum wifi_nrf_status wifi_nrf_fmac_chg_bcn(void *fmac_dev_ctx,
					   unsigned char if_idx,
					   struct nrf_wifi_umac_set_beacon_info *data);

/**
 * @brief Start a SoftAP.
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 * @param if_idx Index of the interface on which the SoftAP is to be started.
 * @param ap_info AP operation specific parameters which need to be passed to the RPU.
 *
 * @details This function is used to send a command to
 * 	    instruct the firmware to start a SoftAP on an interface identified with
 *	    @if_idx.
 *
 * @return Command execution status
 */
enum wifi_nrf_status wifi_nrf_fmac_start_ap(void *fmac_dev_ctx,
					    unsigned char if_idx,
					    struct nrf_wifi_umac_start_ap_info *ap_info);


/**
 * @brief Stop a SoftAP.
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 * @param if_idx Index of the interface on which the SoftAP is to be stopped.
 *
 * @details This function is used to send a command to
 * 	    instruct the firmware to stop a SoftAP on an interface identified with
 * 	    @if_idx.
 *
 * @return Command execution status
 */
enum wifi_nrf_status wifi_nrf_fmac_stop_ap(void *fmac_dev_ctx,
					   unsigned char if_idx);


/**
 * @brief Start P2P mode on an interface.
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 * @param if_idx Index of the interface on which the P2P mode is to be started.
 *
 * @details This function is used to send a command to
 * 	    instruct the firmware to start P2P mode on an interface identified with
 *          @if_idx.
 *
 * @return Command execution status
 */
enum wifi_nrf_status wifi_nrf_fmac_p2p_dev_start(void *fmac_dev_ctx,
						 unsigned char if_idx);


/**
 * @brief Start P2P mode on an interface.
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 * @param if_idx Index of the interface on which the P2P mode is to be started.
 *
 * @detais This function is used to send a command to
 *	   instruct the firmware to start P2P mode on an interface identified with
 *	   @if_idx.
 *
 * @return Command execution status
 */
enum wifi_nrf_status wifi_nrf_fmac_p2p_dev_stop(void *fmac_dev_ctx,
						unsigned char if_idx);

/**
 * @brief Start p2p remian on channel.
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 * @param if_idx Index of the interface to be kept on channel and stay there.
 * @param roc_info Contans channel and time in ms to stay on.
 *
 * @details This function is used to send a command
 * 	    to RPU to put p2p device in listen state for a duration.
 *
 * @return Command execution status
 */
enum wifi_nrf_status wifi_nrf_fmac_p2p_roc_start(void *fmac_dev_ctx,
						 unsigned char if_idx,
						 struct remain_on_channel_info *roc_info);

/**
 * @brief Stop p2p remain on channel.
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 * @param if_idx Index of the interface to be kept on channel and stay there.
 * @param cookie cancel p2p listen state of the matching cookie.
 *
 * @details This function is used to send a command to RPU to put p2p device out
 *	    of listen state.
 *
 * @return Command execution status
 */
enum wifi_nrf_status wifi_nrf_fmac_p2p_roc_stop(void *fmac_dev_ctx,
						unsigned char if_idx,
						unsigned long long cookie);

/**
 * @brief Transmit a management frame.
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 * @param if_idx Index of the interface on which the frame is to be
 *               transmitted.
 * @param mgmt_tx_info Information regarding the management frame to be
 *                     transmitted.
 *
 * @details This function is used to instruct the RPU to transmit a management frame.
 *
 * @return Command execution status
 */
enum wifi_nrf_status wifi_nrf_fmac_mgmt_tx(void *fmac_dev_ctx,
					   unsigned char if_idx,
					   struct nrf_wifi_umac_mgmt_tx_info *mgmt_tx_info);


/**
 * @brief Remove a station.
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 * @param if_idx Index of the interface on which the STA is connected.
 * @param del_sta_info Information regarding the station to be removed.
 *
 * @details This function is used to instruct the RPU to remove a station and send a
 *	    deauthentication/disassociation frame to the same.
 *
 * @return Command execution status
 */
enum wifi_nrf_status wifi_nrf_fmac_del_sta(void *fmac_dev_ctx,
					   unsigned char if_idx,
					   struct nrf_wifi_umac_del_sta_info *del_sta_info);


/**
 * @brief Indicate a new STA connection to the RPU.
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 * @param if_idx Index of the interface on which the STA is connected.
 * @param add_sta_info Information regarding the new station.
 *
 * @details This function is used to indicate to the RPU that a new STA has
 *	    successfully connected to the AP.
 *
 * @return Command execution status
 */
enum wifi_nrf_status wifi_nrf_fmac_add_sta(void *fmac_dev_ctx,
					   unsigned char if_idx,
					   struct nrf_wifi_umac_add_sta_info *add_sta_info);

/**
 * @brief Indicate changes to STA connection parameters to the RPU.
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 * @param if_idx Index of the interface on which the STA is connected.
 * @param chg_sta_info Information regarding updates to the station parameters.
 *
 * @details This function is used to indicate changes in the connected STA parameters
 *	    to the RPU.
 *
 * @return Command execution status
 */
enum wifi_nrf_status wifi_nrf_fmac_chg_sta(void *fmac_dev_ctx,
					   unsigned char if_idx,
					   struct nrf_wifi_umac_chg_sta_info *chg_sta_info);



/**
 * @brief Register the management frame type which needs to be sent up to the host by the RPU.
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 * @param if_idx Index of the interface from which the received frame is to be
 *               sent up.
 * @param frame_info Information regarding the management frame to be sent up.
 *
 * @details This function is used to send a command to
 * 	    instruct the firmware to pass frames matching that type/subtype to be
 *	    passed upto the host driver.
 *
 * @return Command execution status
 */
enum wifi_nrf_status wifi_nrf_fmac_mgmt_frame_reg(void *fmac_dev_ctx,
						  unsigned char if_idx,
						  struct nrf_wifi_umac_mgmt_frame_info *frame_info);

#endif /* CONFIG_WPA_SUPP */
/**
 * @brief Get unused MAC address from base mac address.
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 * @param addr Memory to copy the mac address to.
 *
 * @return Command execution status
 */
enum wifi_nrf_status wifi_nrf_fmac_mac_addr(struct wifi_nrf_fmac_dev_ctx *fmac_dev_ctx,
					    unsigned char *addr);

/**
 * @brief Assign a index for a new VIF.
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 *
 * @details This function searches for an unused VIF index and returns it.
 *
 * @return Index to be used for a new VIF
 *         In case of error MAX_NUM_VIFS will be returned.
 */
unsigned char wifi_nrf_fmac_vif_idx_get(struct wifi_nrf_fmac_dev_ctx *fmac_dev_ctx);

/**
 * @brief Add a new virtual interface.
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 * @param os_vif_ctx Pointer to VIF context that the user of the UMAC IF would like
 *                   to be passed during invocation of callback functions like
 *                   @rx_frm_callbk_fn etc.
 * @param vif_info Information regarding the interface to be added.
 *
 * @details This function is used to send a command to
 * 	    instruct the firmware to add a new interface with parameters specified by
 *          @vif_info.
 *
 * @return Index (maintained by the UMAC IF layer) of the VIF that was added.
 *         In case of error MAX_NUM_VIFS will be returned.
 */
unsigned char wifi_nrf_fmac_add_vif(void *fmac_dev_ctx,
				    void *os_vif_ctx,
				    struct nrf_wifi_umac_add_vif_info *vif_info);


/**
 * @brief Deletes a virtual interface.
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 * @param if_idx Index of the interface to be deleted.
 *
 * @details This function is used to send a command to
 * 	    instruct the firmware to delete an interface which was added using
 *	    @wifi_nrf_fmac_add_vif.
 *
 * @return Command execution status
 */
enum wifi_nrf_status wifi_nrf_fmac_del_vif(void *fmac_dev_ctx,
					   unsigned char if_idx);

/**
 * @brief Change the attributes of an interface.
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 * @param if_idx Index of the interface on which the functionality is to be
 *               bound.
 * @param vif_info Interface specific information which needs to be passed to the
 *                 RPU.
 *
 * @details This function is used to change the attributes of an interface identified
 * 	    with @if_idx.
 *
 * @return Command execution status
 */
enum wifi_nrf_status wifi_nrf_fmac_chg_vif(void *fmac_dev_ctx,
					   unsigned char if_idx,
					   struct nrf_wifi_umac_chg_vif_attr_info *vif_info);


/**
 * @brief Change the state of a virtual interface.
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 * @param if_idx Index of the interface whose state needs to be changed.
 * @param vif_info State information to be changed for the interface.
 *
 * @details This function is used to send a command to
 * 	    instruct the firmware to change the state of an interface with an index of
 * 	    @if_idx and parameters specified by @vif_info.
 *
 * @return Command execution status
 */
enum wifi_nrf_status wifi_nrf_fmac_chg_vif_state(void *fmac_dev_ctx,
						 unsigned char if_idx,
						 struct nrf_wifi_umac_chg_vif_state_info *vif_info);


/**
 * @brief Set MAC address on interface.
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 * @param if_idx Index of the interface whose MAC address is to be changed.
 * @param mac_addr MAC address to set.
 *
 * @details This function is used to change the MAC address of an interface identified
 * 	    with @if_idx.
 *
 * @return Command execution status
 */
enum wifi_nrf_status wifi_nrf_fmac_set_vif_macaddr(void *fmac_dev_ctx,
						   unsigned char if_idx,
						   unsigned char *mac_addr);

/**
 * @brief Trasmit a frame to the RPU.
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 * @param if_idx Index of the interface on which the frame is to be
 *               transmitted.
 * @param netbuf Pointer to the OS specific network buffer.
 *
 * @details This function takes care of transmitting a frame to the RPU. It does the
 *	    following:
 *
 *		- Queues the frames to a transmit queue.
 *		- Based on token availability sends one or more frames to the RPU using
 *		  the command for transmission.
 *		- The firmware sends an event once the command has
 *		  been processed send to indicate whether the frame(s) have been
 *		  transmited/aborted.
 *		- The diver can cleanup the frame buffers after receiving this event.
 *
 * @return Command execution status
 */
enum wifi_nrf_status wifi_nrf_fmac_start_xmit(void *fmac_dev_ctx,
					      unsigned char if_idx,
					      void *netbuf);

/**
 * @brief Inform the RPU that host is going to suspend state.
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 *
 * @details This function is used to send a command to
 * 	    inform the RPU that host is going to suspend state.
 *
 * @return Command execution status
 */
enum wifi_nrf_status wifi_nrf_fmac_suspend(void *fmac_dev_ctx);


/**
 * @brief Notify RPU that host has resumed from a suspended state.
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 *
 * @details This function is used to send a command
 *	    to inform the RPU that host has resumed from a suspended state.
 *
 * @return Command execution status
 */
enum wifi_nrf_status wifi_nrf_fmac_resume(void *fmac_dev_ctx);


/**
 * @brief Get tx power
 *
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 * @param if_idx VIF index.
 *
 * @details This function is used to send a command
 * 	    to get the transmit power on a particular interface.
 *
 * @return Command execution status
 */
enum wifi_nrf_status wifi_nrf_fmac_get_tx_power(void *fmac_dev_ctx,
						unsigned int if_idx);

/**
 * @brief Get channel definition.
 *
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 * @param if_idx VIF index.
 *
 * @details This function is used to send a command
 * 	    to get the channel configured on a particular interface.
 *
 * @return Command execution status
 */
enum wifi_nrf_status wifi_nrf_fmac_get_channel(void *fmac_dev_ctx,
					       unsigned int if_idx);

/**
 * @brief Get station statistics
 *
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 * @param if_idx: VIF index.
 * @param mac MAC address of the station
 *
 * @details This function is used to send a command
 * 	    to get station statistics using a mac address.
 *
 * @return Command execution status
 */
enum wifi_nrf_status wifi_nrf_fmac_get_station(void *fmac_dev_ctx,
					       unsigned int if_idx,
					       unsigned char *mac);


/* @brief Get interface statistics
 *
 * @param dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 * @param if_idx VIF index.
 *
 * @details This function is used to send a command
 * 	    to get interface statistics using interface index.
 *
 * @return Command execution status
 */
enum wifi_nrf_status wifi_nrf_fmac_get_interface(void *dev_ctx,
					       unsigned int if_idx);


/**
 * @brief Configure WLAN power management.
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 * @param if_idx Index of the interface on which power management is to be set.
 * @param state Enable/Disable of WLAN power management.
 *
 * @details This function is used to send a command
 *	    to RPU to Enable/Disable WLAN Power management.
 *
 * @return Command execution status
 */
enum wifi_nrf_status wifi_nrf_fmac_set_power_save(void *fmac_dev_ctx,
						  unsigned char if_idx,
						  bool state);

/**
 * @brief Configure WLAN uapsd queue.
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 * @param if_idx Index of the interface on which power management is to be set.
 * @param uapsd_queue Uapsd_queue to be used.
 *
 * @details This function is used to send a command (%NRF_WIFI_UMAC_CMD_CONFIG_UAPSD)
 *	    to RPU to set uapsd queue value.
 *
 * @return Command execution status
 */
enum wifi_nrf_status wifi_nrf_fmac_set_uapsd_queue(void *fmac_dev_ctx,
						   unsigned char if_idx,
						   unsigned int uapsd_queue);

/**
 * @brief Configure Power save timeout.
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 * @param if_idx Index of the interface on which power management is to be set.
 * @param ps_timeout Power save inactivity time.
 *
 * @details This function is used to send a command
 * 	    (%NRF_WIFI_UMAC_CMD_SET_POWER_SAVE_TIMEOUT) to RPU to set power save
 *	    inactivity time.
 *
 * @return Command execution status
 */
enum wifi_nrf_status wifi_nrf_fmac_set_power_save_timeout(void *dev_ctx,
							  unsigned char if_idx,
							  int ps_timeout);

/**
 * @brief Configure qos_map of for data
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 * @param if_idx Index of the interface on which the qos map be set.
 * @param qos_info qos_map information
 *
 * @details This function is used to send a command
 *	    to RPU to set qos map information.
 *
 * @return Command execution status
 */
enum wifi_nrf_status wifi_nrf_fmac_set_qos_map(void *fmac_dev_ctx,
					       unsigned char if_idx,
					       struct nrf_wifi_umac_qos_map_info *qos_info);

/**
 * @brief Configure WOWLAN.
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 * @param var Wakeup trigger condition.
 *
 * @details This function is used to send a command
 * 	    to RPU to configure Wakeup trigger condition in RPU.
 *
 * @return Command execution status
 */
enum wifi_nrf_status wifi_nrf_fmac_set_wowlan(void *fmac_dev_ctx,
					      unsigned int var);

/**
 * @brief Get PHY configuration.
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 * @param if_idx Index of the interface on which the CMD needs to be sent.
 *
 * @details This function is used to get PHY configuration from RPU.
 *
 * @return Command execution status
 */
enum wifi_nrf_status wifi_nrf_fmac_get_wiphy(void *fmac_dev_ctx, unsigned char if_idx);

/**
 * @brief Register to get MGMT frames.
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 * @param if_idx Index of the interface on which the CMD needs to be sent.
 * @param frame_info Information regarding the management frame.
 *
 * @details Register with RPU to receive MGMT frames.
 *
 * @return Command execution status
 */
enum wifi_nrf_status wifi_nrf_fmac_register_frame(void *dev_ctx, unsigned char if_idx,
						  struct nrf_wifi_umac_mgmt_frame_info *frame_info);

/**
 * @brief set wiphy parameters
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 * @param wiphy_info wiphy parameters
 *
 * @details This function is used to send a command
 *	    to RPU to configure parameters relted to interface.
 *
 * @return Command execution status
 */

enum wifi_nrf_status wifi_nrf_fmac_set_wiphy_params(void *fmac_dev_ctx,
						 unsigned char if_idx,
						 struct nrf_wifi_umac_set_wiphy_info *wiphy_info);

/**
 * @brief TWT setup command
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 * @param if_idx Index of the interface on which the TWT parameters be set.
 * @param twt_info TWT parameters
 *
 * @details This function is used to send a command
 *	    to RPU to configure parameters relted to TWT setup.
 *
 * @return Command execution status
 */
enum wifi_nrf_status wifi_nrf_fmac_twt_setup(void *fmac_dev_ctx,
					     unsigned char if_idx,
					     struct nrf_wifi_umac_config_twt_info *twt_info);

/**
 * @brief TWT teardown command
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 * @param if_idx Index of the interface on which the TWT parameters be set.
 * @param twt_info TWT parameters
 *
 * @details This function is used to send a command
 *	    to RPU to tear down an existing TWT session.
 *
 * @return Command execution status
 */
enum wifi_nrf_status wifi_nrf_fmac_twt_teardown(void *fmac_dev_ctx,
						unsigned char if_idx,
						struct nrf_wifi_umac_config_twt_info *twt_info);
#endif /* !CONFIG_NRF700X_RADIO_TEST */


/**
 * @brief De-initializes the UMAC IF layer.
 * @param fpriv Pointer to the context of the UMAC IF layer.
 *
 * @details This function de-initializes the UMAC IF layer of the RPU WLAN FullMAC
 *	    driver. It does the following:
 *
 *		- De-initializes the HAL layer.
 *		- Frees the context for the UMAC IF layer.
 *
 * @return None
 */
void wifi_nrf_fmac_deinit(struct wifi_nrf_fmac_priv *fpriv);


/**
 * @brief Adds a RPU instance.
 * @param fpriv Pointer to the context of the UMAC IF layer.
 *
 * @details This function adds an RPU instance. This function will return the
 *	    pointer to the context of the RPU instance. This pointer will need to be
 *	    supplied while invoking further device specific API's,
 *	    e.g. @wifi_nrf_fmac_scan etc.
 *
 * @return Pointer to the context of the RPU instance.
 */
struct wifi_nrf_fmac_dev_ctx *wifi_nrf_fmac_dev_add(struct wifi_nrf_fmac_priv *fpriv,
						    void *os_dev_ctx);


/**
 * @brief Removes a RPU instance.
 * @param fmac_dev_ctx Pointer to the context of the RPU instance to be removed.
 *
 * @details This function handles the removal of an RPU instance at the UMAC IF layer.
 *
 * @return None.
 */
void wifi_nrf_fmac_dev_rem(struct wifi_nrf_fmac_dev_ctx *fmac_dev_ctx);


/**
 * @brief Initializes a RPU instance.
 * @param fmac_dev_ctx Pointer to the context of the RPU instance to be removed.
 * @param rf_params_usr RF parameters (if any) to be passed to the RPU.
 * @param sleep_type Type of RPU sleep.
 * @param phy_calib PHY calibration flags to be passed to the RPU.
 * @param ant_gain_2g Antenna gain value for 2.4 GHz band.
 * @param ant_gain_5g_band1 Antenna gain value for 5 GHz band (5150 MHz - 5350 MHz).
 * @param ant_gain_5g_band2 Antenna gain value for 5 GHz band (5470 MHz - 5730 MHz).
 * @param ant_gain_5g_band3 Antenna gain value for 5 GHz band (5730 MHz - 5895 MHz).
 *
 * @details This function initializes the firmware of an RPU instance.
 *
 * @return Command execution status
 */
enum wifi_nrf_status wifi_nrf_fmac_dev_init(struct wifi_nrf_fmac_dev_ctx *fmac_dev_ctx,
#ifndef CONFIG_NRF700X_RADIO_TEST
					    unsigned char *rf_params_usr,
#endif /* !CONFIG_NRF700X_RADIO_TEST */
#ifdef CONFIG_NRF_WIFI_LOW_POWER
					    int sleep_type,
#endif /* CONFIG_NRF_WIFI_LOW_POWER */
					    unsigned int phy_calib,
					    unsigned char ant_gain_2g,
					    unsigned char ant_gain_5g_band1,
					    unsigned char ant_gain_5g_band2,
					    unsigned char ant_gain_5g_band3);


/**
 * @brief De-initializes a RPU instance.
 * @param fmac_dev_ctx Pointer to the context of the RPU instance to be removed.
 *
 * @details This function de-initializes the firmware of an RPU instance.
 *
 * @retun None.
 */
void wifi_nrf_fmac_dev_deinit(struct wifi_nrf_fmac_dev_ctx *fmac_dev_ctx);


/**
 * @brief Loads the Firmware(s) to the RPU WLAN device.
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device,
 * 			which was passed as @fmac_dev_ctx parameter via the
 * 			@add_dev_callbk_fn callback function.
 * @param fmac_fw Information about the FullMAC firmware(s) to be loaded.
 *
 * @details This function loads the FullMAC firmware(s) to the RPU WLAN device.
 *
 * @return Command execution status
 */
enum wifi_nrf_status wifi_nrf_fmac_fw_load(struct wifi_nrf_fmac_dev_ctx *fmac_dev_ctx,
					   struct wifi_nrf_fmac_fw_info *fmac_fw);


/**
 * @brief Get FW versions from the RPU.
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 * @param umac_ver Pointer to the address where the UMAC version needs to be copied.
 * @param lmac_ver Pointer to the address where the LMAC version needs to be copied.
 *
 * @details This function is used to get Firmware versions from the RPU.
 *
 * @return Command execution status
 */
enum wifi_nrf_status wifi_nrf_fmac_ver_get(struct wifi_nrf_fmac_dev_ctx *fmac_dev_ctx,
					  unsigned int *umac_ver,
					  unsigned int *lmac_ver);


/**
 * @brief Configure BT-Coex parameters in RPU.
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 * @param cmd BT-coex parameters which will be configured in RPU.
 * @param cmd_len Command length.
 *
 * @deatils This function is used to send a command to RPU to configure
 *	    BT-Coex parameters in RPU.
 *
 * @return Command execution status
 */
enum wifi_nrf_status wifi_nrf_fmac_conf_btcoex(struct wifi_nrf_fmac_dev_ctx *fmac_dev_ctx,
					       void *cmd, unsigned int cmd_len);

/**
 * @brief Configure HE LTF and GI parameters.
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 * @param he_ltf HE LTF parameter which will be configured in RPU.
 * @param he_gi HE GI parameter which will be configured in RPU
 * @param enabled enable/disable HE LTF and GI parameter configured
 *
 * @details This function is used to send a command to RPU
 *	    to configure HE ltf and gi parameters in RPU.
 *
 * @return Command execution status
 */
enum wifi_nrf_status wifi_nrf_fmac_conf_ltf_gi(struct wifi_nrf_fmac_dev_ctx *fmac_dev_ctx,
					       unsigned char he_ltf,
					       unsigned char he_gi,
					       unsigned char enabled);


/**
 * @brief set the Multicast filter address.
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 * @param if_idx Index of the interface whose state needs to be changed.
 * @param mcast_info Multicast information to be set
 *
 * @details This function is used to send a command (%NRF_WIFI_UMAC_CMD_MCAST_FILTER) to
 *	    instruct the firmware to set the multicast filter address to an interface
 *	    with index @if_idx and parameters specified by @mcast_info.
 *
 * @return Command execution status
 */
enum wifi_nrf_status wifi_nrf_fmac_set_mcast_addr(struct wifi_nrf_fmac_dev_ctx *fmac_dev_ctx,
						  unsigned char if_idx,
						  struct nrf_wifi_umac_mcast_cfg *mcast_info);


/**
 * @brief Fetch MAC address from OTP.
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 * @param vif_idx Interface index for which the MAC address is to be fetched.
 * @param mac_addr Pointer to the address where the MAC address needs to be copied.
 *
 * @details This function is used to fetch MAC address from the OTP.
 *
 * @return Command execution status
 */
enum wifi_nrf_status wifi_nrf_fmac_otp_mac_addr_get(struct wifi_nrf_fmac_dev_ctx *fmac_dev_ctx,
						    unsigned char vif_idx,
						    unsigned char *mac_addr);


/**
 * @brief Get the RF parameters to be programmed to the RPU.
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 * @param rf_params Pointer to the address where the RF params information needs to be copied.
 *
 * @details This function is used to fetch RF parameters information from the RPU and
 *	    update the default RF parameter with the OTP values. The updated RF
 *	    parameters are then returned in the @rf_params.
 *
 * @return Command execution status
 */
enum wifi_nrf_status wifi_nrf_fmac_rf_params_get(struct wifi_nrf_fmac_dev_ctx *fmac_dev_ctx,
						 unsigned char *rf_params);
/**@brief Regulatory parameter data. **/
struct wifi_nrf_fmac_reg_info {
	unsigned char alpha2[NRF_WIFI_COUNTRY_CODE_LEN]; /**< ISO IEC Country code */ 
	bool force; /**< Forcefully set regulatory **/ 
};

/**
 * @brief Set regulatory domain in RPU.
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 * @param reg_info Pointer to the address where the regulatory domain information
 *		   needs to be copied.
 * @details This function is used to set regulatory domain in the RPU.
 * 
 * @return Command execution status
 */
enum wifi_nrf_status wifi_nrf_fmac_set_reg(struct wifi_nrf_fmac_dev_ctx *fmac_dev_ctx,
					   struct wifi_nrf_fmac_reg_info *reg_info);

/**
 * @brief Get regulatory domain from RPU.
 * @param fmac_dev_ctx: Pointer to the UMAC IF context for a RPU WLAN device.
 * @param reg_info Pointer to the address where the regulatory domain information
 *		   needs to be copied.
 * @details This function is used to get regulatory domain from the RPU.
 *
 * @return Command execution status
 */
enum wifi_nrf_status wifi_nrf_fmac_get_reg(struct wifi_nrf_fmac_dev_ctx *fmac_dev_ctx,
					   struct wifi_nrf_fmac_reg_info *reg_info);

/**
 * @brief Get the current power save info.
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 * @param if_idx: Index of the interface on which power management is to be set.
 *
 * @details This function is used to send a command
 *	    to RPU to Enable/Disable WLAN Power management.
 *
 * @return Command execution status
 */
enum wifi_nrf_status wifi_nrf_fmac_get_power_save_info(void *fmac_dev_ctx,
						       unsigned char if_idx);

#ifdef CONFIG_NRF700X_UTIL
enum wifi_nrf_status wifi_nrf_fmac_set_tx_rate(struct wifi_nrf_fmac_dev_ctx *fmac_dev_ctx,
					       unsigned char rate_flag,
					       int data_rate);
#ifdef CONFIG_NRF_WIFI_LOW_POWER
/**
 * @brief Get the RPU power save status from host perspective.
 * @param fmac_dev_ctx Pointer to the UMAC IF context for a RPU WLAN device.
 * @param rpu_ps_ctrl_state Pointer to the address where the current rpu ps state
 *			    from host perspective needs to be copied.
 *
 * @details This function is used to fetch the RPU power save status
 *	    from host perspective.
 *
 * @return Command execution status
 */
enum wifi_nrf_status wifi_nrf_fmac_get_host_rpu_ps_ctrl_state(void *fmac_dev_ctx,
							      int *rpu_ps_ctrl_state);
#endif /* CONFIG_NRF_WIFI_LOW_POWER */
#endif
#endif /* __FMAC_API_H__ */
