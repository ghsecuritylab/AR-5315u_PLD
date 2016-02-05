/*
    Copyright 2000-2010 Broadcom Corporation

    <:label-BRCM:2011:DUAL/GPL:standard
    
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License, version 2, as published by
    the Free Software Foundation (the "GPL").
    
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    
    A copy of the GPL is available at http://www.broadcom.com/licenses/GPLv2.php, or by
    writing to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
    Boston, MA 02111-1307, USA.
    
    :>
*/

/**************************************************************************
* File Name  : boardparms.c
*
* Description: This file contains the implementation for the BCM63xx board
*              parameter access functions.
*
* Updates    : 07/14/2003  Created.
***************************************************************************/

/* Includes. */
#include "boardparms.h"
#include "bcmSpiRes.h"

/* Typedefs */

/*
You can add a new enum entry anywhere in the enum list below.
Then, you can use the enums in the board parm arrays, with the following restrictions:
-An API must be created for accessing any data from the array except for bp_elemTemplate.
-bp_cpBoardId  must be the first element of the array.
-bp_elemTemplate if used should be the last or second to last (just before bp_last) element
 of the array
-Most enums that are used only once in the array can be placed anywhere after bp_cpBoardId .
-These enums are read with the BpGetUc/BpGetUs/BpGetUl private functions.
-If there is a board parm array that is very similar to one you are adding, then you
 can use the bp_elemTemplate to point to that the board parm array BUT the restriction
 below still applies - that is do not split up the "groups"
 (see g_bcm96362advngr and g_bcm96362advngr2 or g_bcm963168vx and g_bcm963168vx_p300)
-Certain enums can appear multiple times in the board parm arrays
-These enums have special APIs that understand how to loop through each occurence
 They are:
 *packet switch related parameters (from bp_ucPhyAddress to bp_ulPhyId7) which can
  appear once per packet switch (bp_ucPhyType0 and bp_ucPhyType1)
 *led info related parameters (bp_usDuplexLed, bp_usSpeedLed100 and bp_usSpeedLed1000) which can
  appear once per internal led (bp_ulPhyId0 and bp_ulPhyId1)
 *voip dsp related parameters (from bp_ucDspAddress to bp_usGpioDectLed) which can
  appear once per dsp (bp_ucDspType0 and bp_ucDspType1)
*/

#define bp_usGpioOverlay     bp_ulGpioOverlay

enum bp_id {
  bp_cpBoardId,
  bp_cpComment,
  bp_ulGpioOverlay,
  bp_usGpioLedAdsl,
  bp_usGpioLedAdslFail,
  bp_usGpioSecLedAdsl,
  bp_usGpioSecLedAdslFail,
  bp_usGpioLedSesWireless,
  bp_usGpioLedWanData,
  bp_usGpioLedWanError,
  bp_usGpioLedBlPowerOn,
  bp_usGpioLedBlStop,
  bp_usGpioFpgaReset,
  bp_usGpioLedGpon,
  bp_usGpioLedGponFail,
  bp_usGpioLedMoCA,
  bp_usGpioLedMoCAFail,
  bp_usExtIntrResetToDefault,
  bp_usExtIntrSesBtnWireless,
  bp_usAntInUseWireless,
  bp_usWirelessFlags,
  bp_usGpioWirelessPowerDown,
  bp_ucPhyType0,
  bp_ucPhyType1,
  bp_ucPhyAddress,
  bp_usConfigType,
  bp_ulPortMap,
  bp_ulPhyId0,
  bp_ulPhyId1,
  bp_ulPhyId2,
  bp_ulPhyId3,
  bp_ulPhyId4,
  bp_ulPhyId5,
  bp_ulPhyId6,
  bp_ulPhyId7,
  bp_usDuplexLed,
  bp_usSpeedLed100,
  bp_usSpeedLed1000,
  bp_usPhyConnType,
  bp_ucPhyDevName,
  bp_ucDspType0,
  bp_ucDspType1,
  bp_ucDspAddress,
  bp_usGpioLedVoip,
  bp_usGpioVoip1Led,
  bp_usGpioVoip1LedFail,
  bp_usGpioVoip2Led,
  bp_usGpioVoip2LedFail,
  bp_usGpioPotsLed,
  bp_usGpioDectLed,
  bp_usGpioPassDyingGasp,
  bp_ulAfeId0,
  bp_ulAfeId1,
  bp_usGpioExtAFEReset,
  bp_usGpioExtAFELDPwr,
  bp_usGpioExtAFELDMode,
  bp_usGpioIntAFELDPwr,
  bp_usGpioIntAFELDMode,
  bp_usGpioAFELDRelay,
  bp_usGpioUart2Sdin,
  bp_usGpioUart2Sdout,
  bp_usGpioLaserDis,
  bp_usGpioLaserTxPwrEn,
  bp_usVregSel1P2,
  bp_ucVreg1P8,
  bp_usGponOpticsType,
  bp_usGpioFemtoReset,
  bp_cpDefaultOpticalParams,
  bp_usEphyBaseAddress,
  bp_ulNonPeriphGpioCtrlMap,
  bp_usGpioSpiSlaveReset,  
  bp_usSpiSlaveBusNum,  
  bp_usSpiSlaveSelectNum,
  bp_usSpiSlaveMode,
  bp_ulSpiSlaveCtrlState,
  bp_ulSpiSlaveMaxFreq,
  bp_usSpiSlaveProtoRev,
  bp_usGpioExtAFELDData,
  bp_usGpioExtAFELDClk,
  bp_ulNumFePorts,
  bp_ulNumGePorts,
  bp_ulNumVoipPorts,
  bp_usGpioI2cScl,
  bp_usGpioI2cSda,
  bp_elemTemplate,
  bp_usSerialLEDMuxSel,
  bp_ulDeviceOptions,
//<< [CTFN-WIFI-001] kewei lai : Support two Wireless en/disable buttons and Wireless/WPS in one button
  bp_usGpioCtWirelessBtn,
  bp_usGpioCtWirelessBtn2,
  bp_usExtIntrCtWifiBtn,
  bp_usExtIntrCtWifiBtn2,
//>> [CTFN-WIFI-001] End
//<< [CTFN-DRV-001] Antony.Wu : Support 1. Phyid to Ethx mapping and 2. IP101_1001 of ICPLUS, 20111205
  bp_ucpEthPhyMap,
//>> [CTFN-DRV-001] End
//<< [CTFN-DRV-001-2] Support to configure the first index of Ethernet interface in board parameters
  bp_usEthIndex,
//>> [CTFN-DRV-001-2] End
//<< [CTFN-SYS-016] Jimmy Wu : Support Internet LED (implemented by Comtrend)
  bp_usGpioCtInternetLed,
  bp_usGpioCtInternetFailLed,
//>> [CTFN-SYS-016] End
//>> [CTFN-SYS-032-6] kewei lai : Support the second USB LED
  bp_usGpioCtUsbSingleLed1,
  bp_usGpioCtUsbSingleLed2,
//<< [CTFN-SYS-032-6] End
//<< [CTFN-SYS-032] Lucien Huang : Support USB LED for USB host (implemented by Comtrend), 2012/03/12
  bp_usGpioCtUSBLed,
  bp_usGpioCtUSBFailLed,
//>> [CTFN-SYS-032] End
  bp_pPhyInit,
  bp_usGpioLaserReset,
  bp_usGpio_Intr,
  bp_ulExtIntrMocaHostIntr,
  bp_usGphyBaseAddress,
  bp_cpPersonalityName,
//<< [CTFN-WIFI-014] Support two Wireless Interfaces with band defined in board parameter and modify SSID according to band info
  bp_usCtWirelessBand1,
  bp_usCtWirelessBand2,
//>> [CTFN-WIFI-014] End
//<< [CTFN-WIFI-017] kewei lai: Support the second WPS LED
  bp_usGpioCtLedSesWireless2,
//>> [CTFN-WIFI-017] End
// << kewei lai for add new boardid 963169R-1861AC to WAP-5892u 
  bp_usGpioCtWifiBtnAll,
//>> kewei lai for add new boardid 963169R-1861AC to WAP-5892u 

  bp_last
};

/* Include all the led id in this list. The cfe/setup initilization code
 * use this list to perform any necessary setup such pinmux selection on these
 * LED gpio pins
 */
static enum bp_id bpLedList[] = {
  bp_usGpioLedAdsl,
  bp_usGpioLedAdslFail,
  bp_usGpioSecLedAdsl,
  bp_usGpioSecLedAdslFail,
  bp_usGpioLedSesWireless,
  bp_usGpioLedWanData,
  bp_usGpioLedWanError,
  bp_usGpioLedBlPowerOn,
  bp_usGpioLedBlStop,
  bp_usGpioFpgaReset,
  bp_usGpioLedGpon,
  bp_usGpioLedGponFail,
  bp_usGpioLedMoCA,
  bp_usGpioLedMoCAFail,
#if defined(_BCM96318_) || defined(CONFIG_BCM96318)
  bp_usGpioCtUSBLed,
  bp_usGpioCtUSBFailLed,
#endif
  bp_usDuplexLed,
  bp_usSpeedLed100,
  bp_usSpeedLed1000,
  bp_usGpioLedVoip,
  bp_usGpioVoip1Led,
  bp_usGpioVoip1LedFail,
  bp_usGpioVoip2Led,
  bp_usGpioVoip2LedFail,
  bp_usGpioPotsLed,
  bp_usGpioDectLed
};

/* Include all the gpio id in this list. The cfe/setup initilization code
 * use this list to perform any necessary setup such pinmux selection on these
 * gpio pins
 */
static enum bp_id bpGpioList[] = {
  bp_usGpioWirelessPowerDown,
  bp_usGpioPassDyingGasp,
  bp_usGpioExtAFEReset,
  bp_usGpioExtAFELDPwr,
  bp_usGpioExtAFELDMode,
  bp_usGpioIntAFELDPwr,
  bp_usGpioIntAFELDMode,
  bp_usGpioAFELDRelay,
  bp_usGpioUart2Sdin,
  bp_usGpioUart2Sdout,
  bp_usGpioLaserDis,
  bp_usGpioLaserTxPwrEn,
  bp_usGpioSpiSlaveReset,
  bp_usGpioI2cScl,
  bp_usGpioI2cSda,
  bp_usGpioLaserReset,
  bp_usGpio_Intr
};

typedef struct bp_elem {
  enum bp_id id;
  union {
    char * cp;
    unsigned char * ucp;
    unsigned char uc;
    unsigned short us;
    unsigned long ul;
    bp_mdio_init_t * phyinitp;
    struct bp_elem * bp_elemp;
  } u;
} bp_elem_t;

/* Variables */
#if 0
/* Sample structure with all elements present in a valid order */
/* Indentation is used to illustrate the groupings where parameters can be repeated */
/* use bp_elemTemplate to use another structure but do not split the groups */   
static bp_elem_t g_sample[] = {
  {bp_cpBoardId,               .u.cp = "SAMPLE"},
  {bp_ulGpioOverlay,           .u.ul = 0;
  {bp_usGpioLedAdsl,           .u.us = 0},
  {bp_usGpioLedAdslFail,       .u.us = 0},
  {bp_usGpioSecLedAdsl,        .u.us = 0},
  {bp_usGpioSecLedAdslFail,    .u.us = 0},
  {bp_usGpioLedSesWireless,    .u.us = 0},
  {bp_usGpioLedWanData,        .u.us = 0},
  {bp_usGpioLedWanError,       .u.us = 0},
  {bp_usGpioLedBlPowerOn,      .u.us = 0},
  {bp_usGpioLedBlStop,         .u.us = 0},
  {bp_usGpioFpgaReset,         .u.us = 0},
  {bp_usGpioLedGpon,           .u.us = 0},
  {bp_usGpioLedGponFail,       .u.us = 0},
  {bp_usGpioLedMoCA,           .u.us = 0},
  {bp_usGpioLedMoCAFail,       .u.us = 0},
  {bp_usExtIntrResetToDefault, .u.us = 0},
  {bp_usExtIntrSesBtnWireless, .u.us = 0},
  {bp_usAntInUseWireless,      .u.us = 0},
  {bp_usWirelessFlags,         .u.us = 0},
  {bp_usGpioWirelessPowerDown, .u.us = 0},
  {bp_ucPhyType0,              .u.uc = 0}, // First switch
    {bp_ucPhyAddress,          .u.uc = 0},
    {bp_usConfigType,          .u.us = 0},
    {bp_ulPortMap,             .u.ul = 0},
    {bp_ulPhyId0,              .u.ul = 0},
      {bp_usDuplexLed,         .u.us = 0},
      {bp_usSpeedLed100,       .u.us = 0},
      {bp_usSpeedLed1000,      .u.us = 0},
      {bp_pPhyInit             .u.phyinitp = g_phyinit},
    {bp_ulPhyId1,              .u.ul = 0},
      {bp_usDuplexLed,         .u.us = 0},
      {bp_usSpeedLed100,       .u.us = 0},
      {bp_usSpeedLed1000,      .u.us = 0},
      {bp_pPhyInit             .u.phyinitp = g_phyinit},
    {bp_ulPhyId2,              .u.ul = 0},
    {bp_ulPhyId3,              .u.ul = 0},
    {bp_ulPhyId4,              .u.ul = 0},
    {bp_ulPhyId5,              .u.ul = 0},
      {bp_usPhyConnType        .u.us = 0},
      {bp_pPhyInit             .u.phyinitp = g_phyinit},
    {bp_ulPhyId6,              .u.ul = 0},
    {bp_ulPhyId7,              .u.ul = 0},
  {bp_ucPhyType1,              .u.uc = 0}, // Second switch
    {bp_ucPhyAddress,          .u.uc = 0},
    {bp_usConfigType,          .u.us = 0},
    {bp_ulPortMap,             .u.ul = 0},
    {bp_ulPhyId0,              .u.ul = 0},
      {bp_usDuplexLed,         .u.us = 0},
      {bp_usSpeedLed100,       .u.us = 0},
      {bp_usSpeedLed1000,      .u.us = 0},
    {bp_ulPhyId1,              .u.ul = 0},
      {bp_usDuplexLed,         .u.us = 0},
      {bp_usSpeedLed100,       .u.us = 0},
      {bp_usSpeedLed1000,      .u.us = 0},
    {bp_ulPhyId2,              .u.ul = 0},
    {bp_ulPhyId3,              .u.ul = 0},
    {bp_ulPhyId4,              .u.ul = 0},
    {bp_ulPhyId5,              .u.ul = 0},
    {bp_ulPhyId6,              .u.ul = 0},
    {bp_ulPhyId7,              .u.ul = 0},
  {bp_ucDspType0,              .u.uc = 0}, // First VOIP DSP
    {bp_ucDspAddress,          .u.uc = 0},
    {bp_usGpioLedVoip,         .u.us = 0},
    {bp_usGpioVoip1Led,        .u.us = 0},
    {bp_usGpioVoip1LedFail,    .u.us = 0},
    {bp_usGpioVoip2Led,        .u.us = 0},
    {bp_usGpioVoip2LedFail,    .u.us = 0},
    {bp_usGpioPotsLed,         .u.us = 0},
    {bp_usGpioDectLed,         .u.us = 0},
  {bp_ucDspType1,              .u.uc = 0}, // Second VOIP DSP
    {bp_ucDspAddress,          .u.uc = 0},
    {bp_usGpioLedVoip,         .u.us = 0},
    {bp_usGpioVoip1Led,        .u.us = 0},
    {bp_usGpioVoip1LedFail,    .u.us = 0},
    {bp_usGpioVoip2Led,        .u.us = 0},
    {bp_usGpioVoip2LedFail,    .u.us = 0},
    {bp_usGpioPotsLed,         .u.us = 0},
    {bp_usGpioDectLed,         .u.us = 0},
  {bp_ulAfeId0,                .u.ul = 0},
  {bp_ulAfeId1,                .u.ul = 0},
  {bp_usGpioExtAFEReset,       .u.us = 0},
  {bp_usGpioExtAFELDPwr,       .u.us = 0},
  {bp_usGpioExtAFELDMode,      .u.us = 0},
  {bp_usGpioLaserDis,          .u.us = 0},
  {bp_usGpioLaserTxPwrEn,      .u.us = 0},
  {bp_usVregSel1P2,            .u.us = 0},
  {bp_ucVreg1P8                .u.uc = 0},
  {bp_usGpioFemtoReset,        .u.us = 0},
  {bp_usSerialLEDMuxSel        .u.us = 0},
  {bp_elemTemplate             .u.bp_elemp = g_sample2},
  {bp_last}
};

#endif

#if defined(_BCM96362_) || defined(CONFIG_BCM96362)

static bp_elem_t g_bcm96362advnx[] = {
  {bp_cpBoardId,               .u.cp = "96362ADVNX"},
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_USB_LED |
                                       BP_OVERLAY_EPHY_LED_0 |
                                       BP_OVERLAY_EPHY_LED_1 |
                                       BP_OVERLAY_EPHY_LED_2 |
                                       BP_OVERLAY_EPHY_LED_3 |
                                       BP_OVERLAY_SERIAL_LEDS |
                                       BP_OVERLAY_USB_DEVICE)},
  {bp_usGpioLedAdsl,           .u.us = BP_SERIAL_GPIO_14_AL},
  {bp_usGpioLedSesWireless,    .u.us = BP_SERIAL_GPIO_15_AL},
  {bp_usGpioLedWanData,        .u.us = BP_GPIO_1_AL},
  {bp_usGpioLedWanError,       .u.us = BP_SERIAL_GPIO_10_AL},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_SERIAL_GPIO_12_AL},
  {bp_usGpioLedBlStop,         .u.us = BP_SERIAL_GPIO_13_AL},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_0},
  {bp_usExtIntrSesBtnWireless, .u.us = BP_EXT_INTR_1},
  {bp_usWirelessFlags,         .u.us = BP_WLAN_EXCLUDE_ONBOARD},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x1f},
  {bp_ulPhyId0,                .u.ul = 0x01},
  {bp_ulPhyId1,                .u.ul = 0x02},
  {bp_ulPhyId2,                .u.ul = 0x03},
  {bp_ulPhyId3,                .u.ul = 0x04},
  {bp_ulPhyId4,                .u.ul = 0x18},
  {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
  {bp_ucDspAddress,            .u.uc = 0},
  {bp_usGpioVoip1Led,          .u.us = BP_SERIAL_GPIO_8_AL},
  {bp_usGpioVoip2Led,          .u.us = BP_SERIAL_GPIO_9_AL},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6301 | BP_AFE_FE_ANNEXA | BP_AFE_FE_AVMODE_ADSL | BP_AFE_FE_REV_6301_REV_5_1_1},
  {bp_last}
};

static bp_elem_t g_bcm96362advngr[] = {
  {bp_cpBoardId,               .u.cp = "96362ADVNgr"},
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_USB_LED |
                                       BP_OVERLAY_SPI_SSB3_EXT_CS |
                                       BP_OVERLAY_EPHY_LED_0 |
                                       BP_OVERLAY_EPHY_LED_1 |
                                       BP_OVERLAY_EPHY_LED_2 |
                                       BP_OVERLAY_EPHY_LED_3 |
                                       BP_OVERLAY_SERIAL_LEDS |
                                       BP_OVERLAY_USB_DEVICE)},
  {bp_usGpioLedAdsl,           .u.us = BP_SERIAL_GPIO_14_AL},
  {bp_usGpioLedSesWireless,    .u.us = BP_SERIAL_GPIO_15_AL},
  {bp_usGpioLedWanData,        .u.us = BP_GPIO_1_AL},
  {bp_usGpioLedWanError,       .u.us = BP_SERIAL_GPIO_10_AL},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_SERIAL_GPIO_12_AL},
  {bp_usGpioLedBlStop,         .u.us = BP_SERIAL_GPIO_13_AL},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_0},
  {bp_usExtIntrSesBtnWireless, .u.us = BP_EXT_INTR_1},
  {bp_usWirelessFlags,         .u.us = BP_WLAN_EXCLUDE_ONBOARD},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x3f},
  {bp_ulPhyId0,                .u.ul = 0x01},
  {bp_ulPhyId1,                .u.ul = 0x02},
  {bp_ulPhyId2,                .u.ul = 0x03},
  {bp_ulPhyId3,                .u.ul = 0x04},
  {bp_ulPhyId4,                .u.ul = 0x18},
  {bp_ulPhyId5,                .u.ul = 0x19},
  {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
  {bp_ucDspAddress,            .u.uc = 0},
  {bp_usGpioVoip1Led,          .u.us = BP_SERIAL_GPIO_8_AL},
  {bp_usGpioVoip2Led,          .u.us = BP_SERIAL_GPIO_9_AL},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6301 | BP_AFE_FE_ANNEXA | BP_AFE_FE_AVMODE_ADSL | BP_AFE_FE_REV_6301_REV_5_1_1},
  {bp_last}
};

static bp_elem_t g_bcm96362advngr2[] = {
  {bp_cpBoardId,               .u.cp = "96362ADVNgr2"},
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_USB_LED |
                                       BP_OVERLAY_SPI_SSB3_EXT_CS |
                                       BP_OVERLAY_EPHY_LED_0 |
                                       BP_OVERLAY_EPHY_LED_1 |
                                       BP_OVERLAY_EPHY_LED_2 |
                                       BP_OVERLAY_EPHY_LED_3 |
                                       BP_OVERLAY_SERIAL_LEDS |
                                       BP_OVERLAY_USB_DEVICE)},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x1f},
  {bp_ulPhyId0,                .u.ul = 0x01},
  {bp_ulPhyId1,                .u.ul = 0x02},
  {bp_ulPhyId2,                .u.ul = 0x03},
  {bp_ulPhyId3,                .u.ul = 0x04},
  {bp_ulPhyId4,                .u.ul = 0x18},
  {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
  {bp_ucDspAddress,            .u.uc = 0},
  {bp_usGpioVoip1Led,          .u.us = BP_SERIAL_GPIO_8_AL},
  {bp_usGpioVoip2Led,          .u.us = BP_SERIAL_GPIO_9_AL},
  {bp_usGpioPotsLed,           .u.us = BP_SERIAL_GPIO_11_AL},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6302 | BP_AFE_FE_ANNEXA | BP_AFE_FE_AVMODE_ADSL | BP_AFE_FE_REV_6302_REV_5_2_2},
  {bp_elemTemplate,            .u.bp_elemp = g_bcm96362advngr},
  {bp_last}
};

static bp_elem_t g_bcm963629epon[] = {
  {bp_cpBoardId,               .u.cp = "963629epon"},
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_USB_LED |
                                       BP_OVERLAY_EPHY_LED_0 |
                                       BP_OVERLAY_EPHY_LED_1 |
                                       BP_OVERLAY_EPHY_LED_2 |
                                       BP_OVERLAY_EPHY_LED_3 |
                                       BP_OVERLAY_SERIAL_LEDS |
                                       BP_OVERLAY_USB_DEVICE)},
  {bp_usGpioLedSesWireless,    .u.us = BP_SERIAL_GPIO_15_AL},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_SERIAL_GPIO_12_AL},
  {bp_usGpioLedBlStop,         .u.us = BP_SERIAL_GPIO_13_AL},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_0},
  {bp_usExtIntrSesBtnWireless, .u.us = BP_EXT_INTR_1},
  {bp_usWirelessFlags,         .u.us = BP_WLAN_EXCLUDE_ONBOARD},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x1f},
  {bp_ulPhyId0,                .u.ul = 0x01},
  {bp_ulPhyId1,                .u.ul = 0x02},
  {bp_ulPhyId2,                .u.ul = 0x03},
  {bp_ulPhyId3,                .u.ul = 0x04},
  {bp_ulPhyId4,                .u.ul = 0x18 | BCM_WAN_PORT | CONNECTED_TO_EPON_MAC},
  {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
  {bp_ucDspAddress,            .u.uc = 0},
  {bp_usGpioVoip1Led,          .u.us = BP_SERIAL_GPIO_8_AL},
  {bp_usGpioVoip2Led,          .u.us = BP_SERIAL_GPIO_9_AL},
  {bp_last}
};

static bp_elem_t g_bcm96362advn2xh[] = {
  {bp_cpBoardId,               .u.cp = "96362ADVN2xh"},
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_USB_LED |
                                       BP_OVERLAY_SPI_SSB2_EXT_CS |
                                       BP_OVERLAY_EPHY_LED_0 |
                                       BP_OVERLAY_EPHY_LED_1 |
                                       BP_OVERLAY_EPHY_LED_2 |
                                       BP_OVERLAY_EPHY_LED_3 |
                                       BP_OVERLAY_SERIAL_LEDS |
                                       BP_OVERLAY_USB_DEVICE)},
  {bp_usGpioLedAdsl,           .u.us = BP_SERIAL_GPIO_14_AL},
  {bp_usGpioLedSesWireless,    .u.us = BP_SERIAL_GPIO_15_AL},
  {bp_usGpioLedWanData,        .u.us = BP_GPIO_1_AL},
  {bp_usGpioLedWanError,       .u.us = BP_SERIAL_GPIO_10_AL},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_SERIAL_GPIO_12_AL},
  {bp_usGpioLedBlStop,         .u.us = BP_SERIAL_GPIO_13_AL},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_0},
  {bp_usExtIntrSesBtnWireless, .u.us = BP_EXT_INTR_1},
  {bp_usWirelessFlags,         .u.us = BP_WLAN_EXCLUDE_ONBOARD},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x10},
  {bp_ulPhyId4,                .u.ul = RGMII_DIRECT},
  {bp_ucPhyType1,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_SPI_SSB_2},
  {bp_ulPortMap,               .u.ul = 0x1f},
  {bp_ulPhyId0,                .u.ul = 0x00},
  {bp_ulPhyId1,                .u.ul = 0x01},
  {bp_ulPhyId2,                .u.ul = 0x02},
  {bp_ulPhyId3,                .u.ul = 0x03},
  {bp_ulPhyId4,                .u.ul = 0x04},
  {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
  {bp_ucDspAddress,            .u.uc = 0},
  {bp_usGpioVoip1Led,          .u.us = BP_SERIAL_GPIO_8_AL},
  {bp_usGpioVoip2Led,          .u.us = BP_SERIAL_GPIO_9_AL},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6301 | BP_AFE_FE_ANNEXA | BP_AFE_FE_AVMODE_ADSL | BP_AFE_FE_REV_6301_REV_5_1_1},
  {bp_last}
};

static bp_elem_t g_bcm96362advn2xm[] = {
  {bp_cpBoardId,               .u.cp = "96362ADVN2XM"},
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_USB_LED |
                                       BP_OVERLAY_SPI_SSB2_EXT_CS |
                                       BP_OVERLAY_EPHY_LED_0 |
                                       BP_OVERLAY_EPHY_LED_1 |
                                       BP_OVERLAY_EPHY_LED_2 |
                                       BP_OVERLAY_EPHY_LED_3 |
                                       BP_OVERLAY_SERIAL_LEDS |
                                       BP_OVERLAY_USB_DEVICE)},
  {bp_usGpioLedAdsl,           .u.us = BP_SERIAL_GPIO_14_AL},
  {bp_usGpioLedSesWireless,    .u.us = BP_SERIAL_GPIO_15_AL},
  {bp_usGpioLedWanData,        .u.us = BP_GPIO_1_AL},
  {bp_usGpioLedWanError,       .u.us = BP_SERIAL_GPIO_10_AL},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_SERIAL_GPIO_12_AL},
  {bp_usGpioLedBlStop,         .u.us = BP_SERIAL_GPIO_13_AL},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_0},
  {bp_usExtIntrSesBtnWireless, .u.us = BP_EXT_INTR_1},
  {bp_usWirelessFlags,         .u.us = BP_WLAN_EXCLUDE_ONBOARD},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x10},
  {bp_ulPhyId4,                .u.ul = RGMII_DIRECT},
  {bp_ucPhyType1,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_SPI_SSB_2},
  {bp_ulPortMap,               .u.ul = 0x1f},
  {bp_ulPhyId0,                .u.ul = 0x00},
  {bp_ulPhyId1,                .u.ul = 0x01},
  {bp_ulPhyId2,                .u.ul = 0x02},
  {bp_ulPhyId3,                .u.ul = 0x03},
  {bp_ulPhyId4,                .u.ul = 0x04},
  {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
  {bp_ucDspAddress,            .u.uc = 0},
  {bp_usGpioVoip1Led,          .u.us = BP_SERIAL_GPIO_8_AL},
  {bp_usGpioVoip2Led,          .u.us = BP_SERIAL_GPIO_9_AL},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6301 | BP_AFE_FE_ANNEXA | BP_AFE_FE_AVMODE_ADSL | BP_AFE_FE_REV_6301_REV_5_1_1},
  {bp_last}
};


static bp_elem_t g_bcm96361XF[] = {
  {bp_cpBoardId,               .u.cp = "96361XF"},
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_USB_LED |
                                       BP_OVERLAY_EPHY_LED_0 |
                                       BP_OVERLAY_EPHY_LED_1 |
                                       BP_OVERLAY_EPHY_LED_2 |
                                       BP_OVERLAY_EPHY_LED_3 |
                                       BP_OVERLAY_SERIAL_LEDS |
                                       BP_OVERLAY_USB_DEVICE)},
  {bp_usGpioLedAdsl,           .u.us = BP_SERIAL_GPIO_14_AL},
  {bp_usGpioLedSesWireless,    .u.us = BP_SERIAL_GPIO_15_AL},
  {bp_usGpioLedWanData,        .u.us = BP_GPIO_1_AL},
  {bp_usGpioLedWanError,       .u.us = BP_SERIAL_GPIO_10_AL},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_SERIAL_GPIO_12_AL},
  {bp_usGpioLedBlStop,         .u.us = BP_SERIAL_GPIO_13_AL},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_0},
  {bp_usExtIntrSesBtnWireless, .u.us = BP_EXT_INTR_1},
  {bp_usWirelessFlags,         .u.us = BP_WLAN_EXCLUDE_ONBOARD},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x1f},
  {bp_ulPhyId0,                .u.ul = 0x01},
  {bp_ulPhyId1,                .u.ul = 0x02},
  {bp_ulPhyId2,                .u.ul = 0x03},
  {bp_ulPhyId3,                .u.ul = 0x04},
  {bp_ulPhyId4,                .u.ul = MII_DIRECT},
  {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
  {bp_ucDspAddress,            .u.uc = 0},
  {bp_usGpioVoip1Led,          .u.us = BP_SERIAL_GPIO_8_AL},
  {bp_usGpioVoip2Led,          .u.us = BP_SERIAL_GPIO_9_AL},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6302 | BP_AFE_FE_ANNEXA | BP_AFE_FE_AVMODE_ADSL | BP_AFE_FE_REV_6302_REV_5_2_2},
  {bp_usVregSel1P2,            .u.us = 0x13},
  {bp_usGpioFemtoReset,        .u.us = BP_GPIO_35_AH},
  {bp_last}
};

static bp_elem_t g_bcm96361I2[] = {
  {bp_cpBoardId ,              .u.cp = "96361I2"},
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_USB_LED |
                                       BP_OVERLAY_EPHY_LED_0 |
                                       BP_OVERLAY_EPHY_LED_1 |
                                       BP_OVERLAY_EPHY_LED_2 |
                                       BP_OVERLAY_EPHY_LED_3 |
                                       BP_OVERLAY_SERIAL_LEDS |
                                       BP_OVERLAY_USB_DEVICE)},
  {bp_usGpioLedAdsl,           .u.us = BP_SERIAL_GPIO_14_AL},
  {bp_usGpioLedSesWireless,    .u.us = BP_SERIAL_GPIO_15_AL},
  {bp_usGpioLedWanData,        .u.us = BP_GPIO_1_AL},
  {bp_usGpioLedWanError,       .u.us = BP_SERIAL_GPIO_10_AL},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_SERIAL_GPIO_12_AL},
  {bp_usGpioLedBlStop,         .u.us = BP_SERIAL_GPIO_13_AL},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_0},
  {bp_usExtIntrSesBtnWireless, .u.us = BP_EXT_INTR_1},
  {bp_usWirelessFlags,         .u.us = BP_WLAN_EXCLUDE_ONBOARD},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x3f},
  {bp_ulPhyId0,                .u.ul = 0x01},
  {bp_ulPhyId1,                .u.ul = 0x02},
  {bp_ulPhyId2,                .u.ul = 0x03},
  {bp_ulPhyId3,                .u.ul = 0x04},
  {bp_ulPhyId4,                .u.ul = BP_PHY_ID_24 | MAC_IFACE_VALID | MAC_IF_RGMII},
  {bp_ulPhyId5,                .u.ul = BP_PHY_ID_25 | MAC_IFACE_VALID | MAC_IF_RGMII},
  {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
  {bp_ucDspAddress,            .u.uc = 0},
  {bp_usGpioVoip1Led,          .u.us = BP_SERIAL_GPIO_8_AL},
  {bp_usGpioVoip2Led,          .u.us = BP_SERIAL_GPIO_9_AL},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6301 | BP_AFE_FE_ANNEXA | BP_AFE_FE_AVMODE_ADSL | BP_AFE_FE_REV_6301_REV_5_1_1},
  {bp_last}
};

static bp_elem_t g_bcm96362rpvt[] = {
  {bp_cpBoardId ,              .u.cp = "96362RPVT"},
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_USB_LED |
                                       BP_OVERLAY_EPHY_LED_0 |
                                       BP_OVERLAY_EPHY_LED_1 |
                                       BP_OVERLAY_EPHY_LED_2 |
                                       BP_OVERLAY_EPHY_LED_3 |
                                       BP_OVERLAY_SERIAL_LEDS |
                                       BP_OVERLAY_USB_DEVICE)},
  {bp_usGpioLedAdsl,           .u.us = BP_SERIAL_GPIO_14_AL},
  {bp_usGpioLedSesWireless,    .u.us = BP_SERIAL_GPIO_15_AL},
  {bp_usGpioLedWanData,        .u.us = BP_GPIO_1_AL},
  {bp_usGpioLedWanError,       .u.us = BP_SERIAL_GPIO_10_AL},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_SERIAL_GPIO_12_AL},
  {bp_usGpioLedBlStop,         .u.us = BP_SERIAL_GPIO_13_AL},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_0},
  {bp_usExtIntrSesBtnWireless, .u.us = BP_EXT_INTR_1},
  {bp_usWirelessFlags,         .u.us = BP_WLAN_EXCLUDE_ONBOARD},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x3f},
  {bp_ulPhyId0,                .u.ul = 0x01},
  {bp_ulPhyId1,                .u.ul = 0x02},
  {bp_ulPhyId2,                .u.ul = 0x03},
  {bp_ulPhyId3,                .u.ul = 0x04},
  {bp_ulPhyId4,                .u.ul = 0x18 | MAC_IFACE_VALID | MAC_IF_RGMII},
  {bp_ulPhyId5,                .u.ul = 0x19 | MAC_IFACE_VALID | MAC_IF_RGMII},
  {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
  {bp_ucDspAddress,            .u.uc = 0},
  {bp_usGpioVoip1Led,          .u.us = BP_SERIAL_GPIO_8_AL},
  {bp_usGpioVoip2Led,          .u.us = BP_SERIAL_GPIO_9_AL},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6302 | BP_AFE_FE_ANNEXA | BP_AFE_FE_AVMODE_ADSL | BP_AFE_FE_REV_6302_REV_5_2_2}, 
  {bp_last}
};

static bp_elem_t g_bcm96362rpvt_2u[] = {
  {bp_cpBoardId ,              .u.cp = "96362RPVT_2U"},
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_EPHY_LED_0 |
                                       BP_OVERLAY_EPHY_LED_1 |
                                       BP_OVERLAY_EPHY_LED_2 |
                                       BP_OVERLAY_EPHY_LED_3 |
                                       BP_OVERLAY_SERIAL_LEDS)},
  {bp_usGpioLedAdsl,           .u.us = BP_SERIAL_GPIO_14_AL},
  {bp_usGpioLedSesWireless,    .u.us = BP_SERIAL_GPIO_15_AL},
  {bp_usGpioLedWanData,        .u.us = BP_GPIO_1_AL},
  {bp_usGpioLedWanError,       .u.us = BP_SERIAL_GPIO_10_AL},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_SERIAL_GPIO_12_AL},
  {bp_usGpioLedBlStop,         .u.us = BP_SERIAL_GPIO_13_AL},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_0},
  {bp_usExtIntrSesBtnWireless, .u.us = BP_EXT_INTR_1},
  {bp_usWirelessFlags,         .u.us = BP_WLAN_EXCLUDE_ONBOARD},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x3f},
  {bp_ulPhyId0,                .u.ul = 0x01},
  {bp_ulPhyId1,                .u.ul = 0x02},
  {bp_ulPhyId2,                .u.ul = 0x03},
  {bp_ulPhyId3,                .u.ul = 0x04},
  {bp_ulPhyId4,                .u.ul = 0x18 | MAC_IFACE_VALID | MAC_IF_RGMII},
  {bp_ulPhyId5,                .u.ul = 0x19 | MAC_IFACE_VALID | MAC_IF_RGMII},
  {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
  {bp_ucDspAddress,            .u.uc = 0},
  {bp_usGpioVoip1Led,          .u.us = BP_SERIAL_GPIO_8_AL},
  {bp_usGpioVoip2Led,          .u.us = BP_SERIAL_GPIO_9_AL},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6302 | BP_AFE_FE_ANNEXA | BP_AFE_FE_AVMODE_ADSL | BP_AFE_FE_REV_6302_REV_5_2_2}, 
  {bp_last}
};

static bp_elem_t g_bcm96362ravngr2[] = {
  {bp_cpBoardId,               .u.cp = "96362RAVNGR2"},
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_USB_LED |
                                       BP_OVERLAY_EPHY_LED_0 |
                                       BP_OVERLAY_EPHY_LED_1 |
                                       BP_OVERLAY_EPHY_LED_2 |
                                       BP_OVERLAY_EPHY_LED_3 |
                                       BP_OVERLAY_SERIAL_LEDS |
                                       BP_OVERLAY_USB_DEVICE)},
  {bp_usGpioLedAdsl,           .u.us = BP_SERIAL_GPIO_14_AL},
  {bp_usGpioLedSesWireless,    .u.us = BP_SERIAL_GPIO_15_AL},
  {bp_usGpioLedWanData,        .u.us = BP_GPIO_1_AL},
  {bp_usGpioLedWanError,       .u.us = BP_SERIAL_GPIO_10_AL},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_SERIAL_GPIO_12_AL},
  {bp_usGpioLedBlStop,         .u.us = BP_SERIAL_GPIO_13_AL},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_0},
  {bp_usExtIntrSesBtnWireless, .u.us = BP_EXT_INTR_1},
  {bp_usWirelessFlags,         .u.us = BP_WLAN_EXCLUDE_ONBOARD},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x1f},
  {bp_ulPhyId0,                .u.ul = 0x01},
  {bp_ulPhyId1,                .u.ul = 0x02},
  {bp_ulPhyId2,                .u.ul = 0x03},
  {bp_ulPhyId3,                .u.ul = 0x04},
  {bp_ulPhyId4,                .u.ul = 0x18},
  {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
  {bp_ucDspAddress,            .u.uc = 0},
  {bp_usGpioVoip1Led,          .u.us = BP_SERIAL_GPIO_8_AL},
  {bp_usGpioVoip2Led,          .u.us = BP_SERIAL_GPIO_9_AL},
  {bp_usGpioPotsLed,           .u.us = BP_SERIAL_GPIO_11_AL},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6302 | BP_AFE_FE_ANNEXA | BP_AFE_FE_AVMODE_ADSL | BP_AFE_FE_REV_6302_REV_5_2_2},
  {bp_last}
};

static bp_elem_t g_bcm96362radvnxh5[] = {
  {bp_cpBoardId,               .u.cp = "96362RADVNXH5"},
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_USB_LED |
                                       BP_OVERLAY_SPI_SSB2_EXT_CS |
                                       BP_OVERLAY_SERIAL_LEDS |
                                       BP_OVERLAY_USB_DEVICE)},
  {bp_usGpioPotsLed,           .u.us = BP_SERIAL_GPIO_11_AL},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6302 | BP_AFE_FE_ANNEXA | BP_AFE_FE_AVMODE_ADSL | BP_AFE_FE_REV_6302_REV_5_2_2},
  {bp_elemTemplate,            .u.bp_elemp = g_bcm96362advn2xh},
  {bp_last}
};

static bp_elem_t g_bcm96362radvn2xh[] = {
  {bp_cpBoardId,               .u.cp = "96362RADVN2XH"},
  {bp_elemTemplate,            .u.bp_elemp = g_bcm96362radvnxh5},
  {bp_last}
};

static bp_elem_t * g_BoardParms[] = {g_bcm96362advnx, g_bcm96362advngr, g_bcm96362advngr2, g_bcm963629epon, g_bcm96362advn2xh, g_bcm96361XF, g_bcm96361I2, g_bcm96362rpvt, g_bcm96362rpvt_2u, g_bcm96362ravngr2, g_bcm96362advn2xm, g_bcm96362radvnxh5, g_bcm96362radvn2xh, 0};
#endif

#if defined(_BCM96368_) || defined(CONFIG_BCM96368)

static bp_elem_t g_bcm96368vvw[] = {
  {bp_cpBoardId,               .u.cp = "96368VVW"},
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_PCI |
                                       BP_OVERLAY_EPHY_LED_0 |
                                       BP_OVERLAY_EPHY_LED_1 |
                                       BP_OVERLAY_EPHY_LED_2 |
                                       BP_OVERLAY_EPHY_LED_3 |
                                       BP_OVERLAY_INET_LED |
                                       BP_OVERLAY_USB_DEVICE |
                                       BP_OVERLAY_USB_LED)},
  {bp_usGpioLedAdsl,           .u.us = BP_GPIO_2_AL},
  {bp_usGpioLedSesWireless,    .u.us = BP_GPIO_24_AL},
  {bp_usGpioLedWanData,        .u.us = BP_GPIO_5_AH},
  {bp_usGpioLedWanError,       .u.us = BP_GPIO_33_AH},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_GPIO_0_AH},
  {bp_usGpioLedBlStop,         .u.us = BP_GPIO_1_AH},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_0},
  {bp_usExtIntrSesBtnWireless, .u.us = BP_EXT_INTR_1},
  {bp_usAntInUseWireless,      .u.us = BP_WLAN_ANT_MAIN},
  {bp_usWirelessFlags,         .u.us = 0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x0f},
  {bp_ulPhyId0,                .u.ul = 0x01},
  {bp_ulPhyId1,                .u.ul = 0x02},
  {bp_ulPhyId2,                .u.ul = 0x03},
  {bp_ulPhyId3,                .u.ul = 0x04},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_ISIL1556 | BP_AFE_FE_ANNEXA | BP_AFE_FE_REV_ISIL_REV1},
  {bp_last}
};

static bp_elem_t g_bcm96368vvwb[] = {
  {bp_cpBoardId,               .u.cp = "96368VVWB"},
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_PCI |
                                       BP_OVERLAY_EPHY_LED_0 |
                                       BP_OVERLAY_EPHY_LED_1 |
                                       BP_OVERLAY_EPHY_LED_2 |
                                       BP_OVERLAY_EPHY_LED_3 |
                                       BP_OVERLAY_INET_LED |
                                       BP_OVERLAY_USB_DEVICE |
                                       BP_OVERLAY_USB_LED)},
  {bp_usGpioLedAdsl,           .u.us = BP_GPIO_2_AL},
  {bp_usGpioLedSesWireless,    .u.us = BP_GPIO_24_AL},
  {bp_usGpioLedWanData,        .u.us = BP_GPIO_5_AH},
  {bp_usGpioLedWanError,       .u.us = BP_GPIO_33_AH},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_GPIO_0_AH},
  {bp_usGpioLedBlStop,         .u.us = BP_GPIO_1_AH},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_0},
  {bp_usExtIntrSesBtnWireless, .u.us = BP_EXT_INTR_1},
  {bp_usAntInUseWireless,      .u.us = BP_WLAN_ANT_MAIN},
  {bp_usWirelessFlags,         .u.us = 0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x0f},
  {bp_ulPhyId0,                .u.ul = 0x01},
  {bp_ulPhyId1,                .u.ul = 0x02},
  {bp_ulPhyId2,                .u.ul = 0x03},
  {bp_ulPhyId3,                .u.ul = 0x04},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_ISIL1556 | BP_AFE_FE_ANNEXB | BP_AFE_FE_REV_ISIL_REV1},
  {bp_last}
};

static bp_elem_t g_bcm96368ntr[] = {
  {bp_cpBoardId,               .u.cp = "96368NTR"},
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_PCI |
                                       BP_OVERLAY_EPHY_LED_0 |
                                       BP_OVERLAY_EPHY_LED_1 |
                                       BP_OVERLAY_EPHY_LED_2 |
                                       BP_OVERLAY_EPHY_LED_3 |
                                       BP_OVERLAY_INET_LED |
                                       BP_OVERLAY_USB_DEVICE)},
  {bp_usGpioLedAdsl,           .u.us = BP_GPIO_2_AL},
  {bp_usGpioLedWanData,        .u.us = BP_GPIO_5_AH},
  {bp_usGpioLedWanError,       .u.us = BP_GPIO_33_AH},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_GPIO_0_AH},
  {bp_usGpioLedBlStop,         .u.us = BP_GPIO_1_AH},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_0},
  {bp_usExtIntrSesBtnWireless, .u.us = BP_EXT_INTR_1},
  {bp_usAntInUseWireless,      .u.us = BP_WLAN_ANT_MAIN},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x0f},
  {bp_ulPhyId0,                .u.ul = 0x01},
  {bp_ulPhyId1,                .u.ul = 0x02},
  {bp_ulPhyId2,                .u.ul = 0x03},
  {bp_ulPhyId3,                .u.ul = 0x04},
  {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
  {bp_ucDspAddress,            .u.uc = 0},
  {bp_usGpioVoip1Led,          .u.us = BP_GPIO_25_AL},
  {bp_usGpioVoip2Led,          .u.us = BP_GPIO_26_AL},
  {bp_usGpioPotsLed,           .u.us = BP_GPIO_27_AL},
  {bp_last}
};

static bp_elem_t g_bcm96368sv2[] = {
  {bp_cpBoardId,               .u.cp = "96368SV2"},
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_PCI |
                                       BP_OVERLAY_PHY |
                                       BP_OVERLAY_EPHY_LED_0 |
                                       BP_OVERLAY_EPHY_LED_1 |
                                       BP_OVERLAY_EPHY_LED_2 |
                                       BP_OVERLAY_EPHY_LED_3 |
                                       BP_OVERLAY_INET_LED |
                                       BP_OVERLAY_USB_DEVICE |
                                       BP_OVERLAY_USB_LED)},
  {bp_usGpioLedAdsl,           .u.us = BP_GPIO_2_AL},
  {bp_usGpioLedWanData,        .u.us = BP_GPIO_5_AH},
  {bp_usGpioLedWanError,       .u.us = BP_GPIO_33_AH},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_GPIO_30_AH},
  {bp_usGpioLedBlStop,         .u.us = BP_GPIO_31_AH},
  {bp_usAntInUseWireless,      .u.us = BP_WLAN_ANT_MAIN},
  {bp_usWirelessFlags,         .u.us = 0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x3f},
  {bp_ulPhyId0,                .u.ul = 0x01},
  {bp_ulPhyId1,                .u.ul = 0x02},
  {bp_ulPhyId2,                .u.ul = 0x03},
  {bp_ulPhyId3,                .u.ul = 0x04},
  {bp_ulPhyId4,                .u.ul = 0x12},
  {bp_ulPhyId5,                .u.ul = 0x11},
  {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
  {bp_ucDspAddress,            .u.uc = 0},
  {bp_usGpioVoip1Led,          .u.us = BP_GPIO_25_AL},
  {bp_usGpioVoip2Led,          .u.us = BP_GPIO_26_AL},
  {bp_usGpioPotsLed,           .u.us = BP_GPIO_27_AL},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_ISIL1556 | BP_AFE_FE_ANNEXA | BP_AFE_FE_REV_ISIL_REV1},
  {bp_last}
};

static bp_elem_t g_bcm96368mvwg[] = {
  {bp_cpBoardId,               .u.cp = "96368MVWG"},
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_PCI |
                                       BP_OVERLAY_PHY |
                                       BP_OVERLAY_EPHY_LED_0 |
                                       BP_OVERLAY_EPHY_LED_1 |
                                       BP_OVERLAY_EPHY_LED_2 |
                                       BP_OVERLAY_EPHY_LED_3 |
                                       BP_OVERLAY_INET_LED |
                                       BP_OVERLAY_USB_DEVICE |
                                       BP_OVERLAY_USB_LED)},
  {bp_usGpioLedAdsl,           .u.us = BP_GPIO_2_AL},
  {bp_usGpioLedSesWireless,    .u.us = BP_GPIO_22_AL},
  {bp_usGpioLedWanData,        .u.us = BP_GPIO_5_AH},
  {bp_usGpioLedWanError,       .u.us = BP_GPIO_31_AH},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_GPIO_22_AH},
  {bp_usGpioLedBlStop,         .u.us = BP_GPIO_24_AH},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_0},
  {bp_usExtIntrSesBtnWireless, .u.us = BP_EXT_INTR_1},
  {bp_usAntInUseWireless,      .u.us = BP_WLAN_ANT_MAIN},
  {bp_usWirelessFlags,         .u.us = 0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x36},
  {bp_ulPhyId1,                .u.ul = 0x02},
  {bp_ulPhyId2,                .u.ul = 0x03},
  {bp_ulPhyId4,                .u.ul = 0x12},
  {bp_ulPhyId5,                .u.ul = 0x11},
  {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
  {bp_ucDspAddress,            .u.uc = 0},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6302 | BP_AFE_FE_ANNEXA | BP_AFE_FE_REV_6302_REV1},
  {bp_last}
};

static bp_elem_t g_bcm96368mvwgb[] = {
  {bp_cpBoardId,               .u.cp = "96368MVWGB"},
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_PCI |
                                       BP_OVERLAY_PHY |
                                       BP_OVERLAY_EPHY_LED_0 |
                                       BP_OVERLAY_EPHY_LED_1 |
                                       BP_OVERLAY_EPHY_LED_2 |
                                       BP_OVERLAY_EPHY_LED_3 |
                                       BP_OVERLAY_INET_LED |
                                       BP_OVERLAY_USB_DEVICE |
                                       BP_OVERLAY_USB_LED)},
  {bp_usGpioLedAdsl,           .u.us = BP_GPIO_2_AL},
  {bp_usGpioLedSesWireless,    .u.us = BP_GPIO_22_AL},
  {bp_usGpioLedWanData,        .u.us = BP_GPIO_5_AH},
  {bp_usGpioLedWanError,       .u.us = BP_GPIO_31_AH},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_GPIO_22_AH},
  {bp_usGpioLedBlStop,         .u.us = BP_GPIO_24_AH},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_0},
  {bp_usExtIntrSesBtnWireless, .u.us = BP_EXT_INTR_1},
  {bp_usAntInUseWireless,      .u.us = BP_WLAN_ANT_MAIN},
  {bp_usWirelessFlags,         .u.us = 0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x36},
  {bp_ulPhyId1,                .u.ul = 0x02},
  {bp_ulPhyId2,                .u.ul = 0x03},
  {bp_ulPhyId4,                .u.ul = 0x12},
  {bp_ulPhyId5,                .u.ul = 0x11},
  {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
  {bp_ucDspAddress,            .u.uc = 0},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6302 | BP_AFE_FE_ANNEXB | BP_AFE_FE_REV_6302_REV1},
  {bp_last}
};

static bp_elem_t g_bcm96368mvwgj[] = {
  {bp_cpBoardId,               .u.cp = "96368MVWGJ"},
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_PCI |
                                       BP_OVERLAY_PHY |
                                       BP_OVERLAY_EPHY_LED_0 |
                                       BP_OVERLAY_EPHY_LED_1 |
                                       BP_OVERLAY_EPHY_LED_2 |
                                       BP_OVERLAY_EPHY_LED_3 |
                                       BP_OVERLAY_INET_LED |
                                       BP_OVERLAY_USB_DEVICE |
                                       BP_OVERLAY_USB_LED)},
  {bp_usGpioLedAdsl,           .u.us = BP_GPIO_2_AL},
  {bp_usGpioLedSesWireless,    .u.us = BP_GPIO_22_AL},
  {bp_usGpioLedWanData,        .u.us = BP_GPIO_5_AH},
  {bp_usGpioLedWanError,       .u.us = BP_GPIO_31_AH},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_GPIO_22_AH},
  {bp_usGpioLedBlStop,         .u.us = BP_GPIO_24_AH},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_0},
  {bp_usExtIntrSesBtnWireless, .u.us = BP_EXT_INTR_1},
  {bp_usAntInUseWireless,      .u.us = BP_WLAN_ANT_MAIN},
  {bp_usWirelessFlags,         .u.us = 0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x36},
  {bp_ulPhyId0,                .u.ul = 0x00},
  {bp_ulPhyId1,                .u.ul = 0x02},
  {bp_ulPhyId2,                .u.ul = 0x03},
  {bp_ulPhyId3,                .u.ul = 0x00},
  {bp_ulPhyId4,                .u.ul = 0x12},
  {bp_ulPhyId5,                .u.ul = 0x11},
  {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
  {bp_ucDspAddress,            .u.uc = 0},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6302 | BP_AFE_FE_ANNEXJ | BP_AFE_FE_REV_6302_REV1},
  {bp_last}
};

static bp_elem_t g_bcm96368mb2g[] = {
  {bp_cpBoardId,               .u.cp = "96368MB2G"},
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_PCI |
                                       BP_OVERLAY_PHY |
                                       BP_OVERLAY_EPHY_LED_0 |
                                       BP_OVERLAY_EPHY_LED_1 |
                                       BP_OVERLAY_EPHY_LED_2 |
                                       BP_OVERLAY_EPHY_LED_3 |
                                       BP_OVERLAY_INET_LED |
                                       BP_OVERLAY_USB_DEVICE)},
  {bp_usGpioLedAdsl,           .u.us = BP_GPIO_2_AL},
  {bp_usGpioSecLedAdsl,        .u.us = BP_GPIO_27_AL},
  {bp_usGpioLedWanData,        .u.us = BP_GPIO_5_AH},
  {bp_usGpioLedWanError,       .u.us = BP_GPIO_31_AH},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_GPIO_22_AH},
  {bp_usGpioLedBlStop,         .u.us = BP_GPIO_24_AH},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x0f},
  {bp_ulPhyId0,                .u.ul = 0x01},
  {bp_ulPhyId1,                .u.ul = 0x02},
  {bp_ulPhyId2,                .u.ul = 0x03},
  {bp_ulPhyId3,                .u.ul = 0x04},
  {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
  {bp_ucDspAddress,            .u.uc = 0},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6302 | BP_AFE_FE_ANNEXA | BP_AFE_FE_REV_6302_REV1},
  {bp_ulAfeId1,                .u.ul = BP_AFE_CHIP_6306 | BP_AFE_LD_ISIL1556 | BP_AFE_FE_ANNEXA | BP_AFE_FE_REV_ISIL_REV1},
  {bp_usGpioExtAFEReset,       .u.us = BP_GPIO_35_AL},
  {bp_last}
};

static bp_elem_t g_bcm96368mbg6b[] = {
  {bp_cpBoardId,               .u.cp = "96368MBG6b"},
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_PCI |
                                       BP_OVERLAY_PHY |
                                       BP_OVERLAY_EPHY_LED_0 |
                                       BP_OVERLAY_EPHY_LED_1 |
                                       BP_OVERLAY_EPHY_LED_2 |
                                       BP_OVERLAY_EPHY_LED_3 |
                                       BP_OVERLAY_INET_LED |
                                       BP_OVERLAY_USB_DEVICE)},
  {bp_usGpioLedAdsl,           .u.us = BP_GPIO_2_AL},
  {bp_usGpioSecLedAdsl,        .u.us = BP_GPIO_27_AL},
  {bp_usGpioLedWanData,        .u.us = BP_GPIO_5_AH},
  {bp_usGpioLedWanError,       .u.us = BP_GPIO_31_AH},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_GPIO_22_AH},
  {bp_usGpioLedBlStop,         .u.us = BP_GPIO_24_AH},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x0f},
  {bp_ulPhyId0,                .u.ul = 0x01},
  {bp_ulPhyId1,                .u.ul = 0x02},
  {bp_ulPhyId2,                .u.ul = 0x03},
  {bp_ulPhyId3,                .u.ul = 0x04},
  {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
  {bp_ucDspAddress,            .u.uc = 0},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_6306 | BP_AFE_LD_ISIL1556 | BP_AFE_FE_ANNEXA | BP_AFE_FE_REV_ISIL_REV1},
  {bp_usGpioExtAFEReset,       .u.us = BP_GPIO_35_AL},
  {bp_last}
};

static bp_elem_t g_bcm96368mbg6302[] = {
  {bp_cpBoardId,               .u.cp = "96368MBG6302"},
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_PCI |
                                       BP_OVERLAY_PHY |
                                       BP_OVERLAY_EPHY_LED_0 |
                                       BP_OVERLAY_EPHY_LED_1 |
                                       BP_OVERLAY_EPHY_LED_2 |
                                       BP_OVERLAY_EPHY_LED_3 |
                                       BP_OVERLAY_INET_LED |
                                       BP_OVERLAY_USB_DEVICE)},
  {bp_usGpioLedAdsl,           .u.us = BP_GPIO_2_AL},
  {bp_usGpioSecLedAdsl,        .u.us = BP_GPIO_27_AL},
  {bp_usGpioLedWanData,        .u.us = BP_GPIO_5_AH},
  {bp_usGpioLedWanError,       .u.us = BP_GPIO_31_AH},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_GPIO_22_AH},
  {bp_usGpioLedBlStop,         .u.us = BP_GPIO_24_AH},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x0f},
  {bp_ulPhyId0,                .u.ul = 0x01},
  {bp_ulPhyId1,                .u.ul = 0x02},
  {bp_ulPhyId2,                .u.ul = 0x03},
  {bp_ulPhyId3,                .u.ul = 0x04},
  {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
  {bp_ucDspAddress,            .u.uc = 0},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6302 | BP_AFE_FE_ANNEXA | BP_AFE_FE_REV_6302_REV1},
  {bp_ulAfeId1,                .u.ul = BP_AFE_CHIP_6306 | BP_AFE_LD_6302 | BP_AFE_FE_ANNEXA | BP_AFE_FE_REV_6302_REV1},
  {bp_usGpioExtAFEReset,       .u.us = BP_GPIO_35_AL},
  {bp_usGpioExtAFELDPwr,       .u.us = BP_GPIO_37_AH},
  {bp_usGpioExtAFELDMode,      .u.us = BP_GPIO_36_AH},
  {bp_last}
};

static bp_elem_t g_bcm96368mng[] = {
  {bp_cpBoardId,               .u.cp = "96368MNG"},
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_PCI |
                                       BP_OVERLAY_PHY |
                                       BP_OVERLAY_EPHY_LED_0 |
                                       BP_OVERLAY_EPHY_LED_1 |
                                       BP_OVERLAY_EPHY_LED_2 |
                                       BP_OVERLAY_EPHY_LED_3 |
                                       BP_OVERLAY_INET_LED)},
  {bp_usGpioLedAdsl,           .u.us = BP_GPIO_2_AL},
  {bp_usGpioLedWanData,        .u.us = BP_GPIO_5_AH},
  {bp_usGpioLedWanError,       .u.us = BP_GPIO_31_AH},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_GPIO_22_AH},
  {bp_usGpioLedBlStop,         .u.us = BP_GPIO_24_AH},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x20},
  {bp_ulPhyId5,                .u.ul = 0xff},
  {bp_ucPhyType1,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_SPI_SSB_1},
  {bp_ulPortMap,               .u.ul = 0x0f},
  {bp_ulPhyId0,                .u.ul = 0x00},
  {bp_ulPhyId1,                .u.ul = 0x01},
  {bp_ulPhyId2,                .u.ul = 0x02},
  {bp_ulPhyId3,                .u.ul = 0x03},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_6306 | BP_AFE_LD_ISIL1556 | BP_AFE_FE_ANNEXA | BP_AFE_FE_REV_ISIL_REV1},
  {bp_usGpioExtAFEReset,       .u.us = BP_GPIO_37_AL},
  {bp_last}
};

static bp_elem_t g_bcm96367avng[] = {
  {bp_cpBoardId,               .u.cp = "96367AVNG"},
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_PCI |
                                       BP_OVERLAY_PHY |
                                       BP_OVERLAY_EPHY_LED_0 |
                                       BP_OVERLAY_EPHY_LED_1 |
                                       BP_OVERLAY_EPHY_LED_2 |
                                       BP_OVERLAY_EPHY_LED_3 |
                                       BP_OVERLAY_INET_LED |
                                       BP_OVERLAY_USB_DEVICE |
                                       BP_OVERLAY_USB_LED)},
  {bp_usGpioLedAdsl,           .u.us = BP_GPIO_2_AL},
  {bp_usGpioLedSesWireless,    .u.us = BP_GPIO_23_AL},
  {bp_usGpioLedWanError,       .u.us = BP_GPIO_31_AH},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_GPIO_22_AH},
  {bp_usGpioLedBlStop,         .u.us = BP_GPIO_24_AH},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_0},
  {bp_usExtIntrSesBtnWireless, .u.us = BP_EXT_INTR_1},
  {bp_usAntInUseWireless,      .u.us = BP_WLAN_ANT_MAIN},
  {bp_usWirelessFlags,         .u.us = 0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x2f},
  {bp_ulPhyId0,                .u.ul = 0x01},
  {bp_ulPhyId1,                .u.ul = 0x02},
  {bp_ulPhyId2,                .u.ul = 0x03},
  {bp_ulPhyId3,                .u.ul = 0x04},
  {bp_ulPhyId5,                .u.ul = 0x11},
  {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
  {bp_ucDspAddress,            .u.uc = 0},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6302 | BP_AFE_FE_ANNEXA | BP_AFE_FE_REV_6302_REV1},
  {bp_last}
};

static bp_elem_t g_bcm96368mvngr[] = {
  {bp_cpBoardId,               .u.cp = "96368MVNgr"},
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_PCI |
                                       BP_OVERLAY_SPI_EXT_CS |
                                       BP_OVERLAY_PHY |
                                       BP_OVERLAY_EPHY_LED_0 |
                                       BP_OVERLAY_EPHY_LED_1 |
                                       BP_OVERLAY_EPHY_LED_2 |
                                       BP_OVERLAY_EPHY_LED_3 |
                                       BP_OVERLAY_INET_LED |
                                       BP_OVERLAY_USB_DEVICE |
                                       BP_OVERLAY_USB_LED)},
  {bp_usGpioLedAdsl,           .u.us = BP_GPIO_2_AL},
  {bp_usGpioLedSesWireless,    .u.us = BP_GPIO_23_AL},
  {bp_usGpioLedWanData,        .u.us = BP_GPIO_5_AH},
  {bp_usGpioLedWanError,       .u.us = BP_GPIO_3_AH},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_GPIO_22_AH},
  {bp_usGpioLedBlStop,         .u.us = BP_GPIO_24_AH},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_0},
  {bp_usExtIntrSesBtnWireless, .u.us = BP_EXT_INTR_1},
  {bp_usAntInUseWireless,      .u.us = BP_WLAN_ANT_MAIN},
  {bp_usWirelessFlags,         .u.us = 0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x0f},
  {bp_ulPhyId0,                .u.ul = 0x01},
  {bp_ulPhyId1,                .u.ul = 0x02},
  {bp_ulPhyId2,                .u.ul = 0x03},
  {bp_ulPhyId3,                .u.ul = 0x04},
  {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
  {bp_ucDspAddress,            .u.uc = 0},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6302 | BP_AFE_FE_ANNEXA | BP_AFE_FE_REV_6302_REV1},
  {bp_last}
};

static bp_elem_t g_bcm96368rmvng_nand[] = {
  {bp_cpBoardId,               .u.cp = "96368RMVNg NAND"},
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_PCI |
                                       BP_OVERLAY_SPI_EXT_CS |
                                       BP_OVERLAY_PHY |
                                       BP_OVERLAY_EPHY_LED_0 |
                                       BP_OVERLAY_EPHY_LED_1 |
                                       BP_OVERLAY_INET_LED |
                                       BP_OVERLAY_USB_DEVICE |
                                       BP_OVERLAY_USB_LED)},
  {bp_usGpioLedAdsl,           .u.us = BP_GPIO_2_AL},
  {bp_usGpioLedSesWireless,    .u.us = BP_GPIO_23_AL},
  {bp_usGpioLedWanData,        .u.us = BP_GPIO_5_AH},
  {bp_usGpioLedWanError,       .u.us = BP_GPIO_3_AH},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_GPIO_22_AH},
  {bp_usGpioLedBlStop,         .u.us = BP_GPIO_24_AH},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_0},
  {bp_usExtIntrSesBtnWireless, .u.us = BP_EXT_INTR_1},
  {bp_usAntInUseWireless,      .u.us = BP_WLAN_ANT_MAIN},
  {bp_usWirelessFlags,         .u.us = 0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x03},
  {bp_ulPhyId0,                .u.ul = 0x01},
  {bp_ulPhyId1,                .u.ul = 0x02},
  {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
  {bp_ucDspAddress,            .u.uc = 0},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6302 | BP_AFE_FE_ANNEXA | BP_AFE_FE_REV_6302_REV1},
  {bp_last}
};

static bp_elem_t g_bcm96368rmvng_nor[] = {
  {bp_cpBoardId,               .u.cp = "96368RMVNg NOR"},
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_PCI |
                                       BP_OVERLAY_SPI_EXT_CS |
                                       BP_OVERLAY_PHY |
                                       BP_OVERLAY_EPHY_LED_0 |
                                       BP_OVERLAY_EPHY_LED_1 |
                                       BP_OVERLAY_INET_LED |
                                       BP_OVERLAY_USB_DEVICE |
                                       BP_OVERLAY_USB_LED)},
  {bp_usGpioLedAdsl,           .u.us = BP_GPIO_2_AL},
  {bp_usGpioLedSesWireless,    .u.us = BP_GPIO_23_AL},
  {bp_usGpioLedWanData,        .u.us = BP_GPIO_5_AH},
  {bp_usGpioLedWanError,       .u.us = BP_GPIO_3_AH},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_GPIO_22_AH},
  {bp_usGpioLedBlStop,         .u.us = BP_GPIO_24_AH},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_0},
  {bp_usExtIntrSesBtnWireless, .u.us = BP_EXT_INTR_1},
  {bp_usAntInUseWireless,      .u.us = BP_WLAN_ANT_MAIN},
  {bp_usWirelessFlags,         .u.us = 0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x13},
  {bp_ulPhyId0,                .u.ul = 0x01},
  {bp_ulPhyId1,                .u.ul = 0x02},
  {bp_ulPhyId4,                .u.ul = 0x18},
  {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
  {bp_ucDspAddress,            .u.uc = 0},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6302 | BP_AFE_FE_ANNEXA | BP_AFE_FE_REV_6302_REV1},
  {bp_last}
};

static bp_elem_t g_bcm96368mvngrP2[] = {
  {bp_cpBoardId,               .u.cp = "96368MVNgrP2"},
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_PCI |
                                       BP_OVERLAY_PHY |
                                       BP_OVERLAY_EPHY_LED_0 |
                                       BP_OVERLAY_EPHY_LED_1 |
                                       BP_OVERLAY_EPHY_LED_2 |
                                       BP_OVERLAY_EPHY_LED_3 |
                                       BP_OVERLAY_INET_LED |
                                       BP_OVERLAY_USB_DEVICE |
                                       BP_OVERLAY_USB_LED)},
  {bp_usGpioLedAdsl,           .u.us = BP_GPIO_2_AL},
  {bp_usGpioLedSesWireless,    .u.us = BP_GPIO_23_AL},
  {bp_usGpioLedWanData,        .u.us = BP_GPIO_5_AL},
  {bp_usGpioLedWanError,       .u.us = BP_GPIO_3_AL},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_GPIO_22_AL},
  {bp_usGpioLedBlStop,         .u.us = BP_GPIO_24_AL},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_0},
  {bp_usExtIntrSesBtnWireless, .u.us = BP_EXT_INTR_1},
  {bp_usAntInUseWireless,      .u.us = BP_WLAN_ANT_MAIN},
  {bp_usWirelessFlags,         .u.us = 0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x0f},
  {bp_ulPhyId0,                .u.ul = 0x01},
  {bp_ulPhyId1,                .u.ul = 0x02},
  {bp_ulPhyId2,                .u.ul = 0x03},
  {bp_ulPhyId3,                .u.ul = 0x04},
  {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
  {bp_ucDspAddress,            .u.uc = 0},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6302 | BP_AFE_FE_ANNEXA | BP_AFE_FE_REV_6302_REV1},
  {bp_last}
};

static bp_elem_t g_bcm96368Ext[] = {
  {bp_cpBoardId,               .u.cp = "96368EXT"},
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_PCI |
                                       BP_OVERLAY_PHY |
                                       BP_OVERLAY_EPHY_LED_0 |
                                       BP_OVERLAY_EPHY_LED_1 |
                                       BP_OVERLAY_EPHY_LED_2 |
                                       BP_OVERLAY_EPHY_LED_3 |
                                       BP_OVERLAY_INET_LED |
                                       BP_OVERLAY_USB_DEVICE |
                                       BP_OVERLAY_USB_LED)},
  {bp_usGpioLedAdsl,           .u.us = BP_GPIO_2_AL},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x03},
  {bp_ulPhyId0,                .u.ul = 0x01},
  {bp_ulPhyId1,                .u.ul = 0x02},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6302 | BP_AFE_FE_ANNEXA | BP_AFE_FE_REV_6302_REV1},
  {bp_last}
};

static bp_elem_t * g_BoardParms[] =
{g_bcm96368vvw, g_bcm96368mvwg, g_bcm96368sv2, g_bcm96368mb2g,
g_bcm96368ntr, g_bcm96368Ext, g_bcm96368vvwb, g_bcm96368mvwgb,
g_bcm96368mng, g_bcm96368mbg6302, g_bcm96368mvwgj, g_bcm96367avng,
g_bcm96368mvngr, g_bcm96368rmvng_nand, g_bcm96368rmvng_nor, g_bcm96368mvngrP2, g_bcm96368mbg6b, 0};
#endif

#if defined(_BCM96816_) || defined(CONFIG_BCM96816)

static bp_elem_t g_bcm96816sv[] = {
  {bp_cpBoardId,               .u.cp = "96816SV"},
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_PCI |
                                       BP_OVERLAY_GPHY_LED_0 |
                                       BP_OVERLAY_GPHY_LED_1 |
                                       BP_OVERLAY_MOCA_LED)},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_GPIO_3_AH},
  {bp_usGpioLedBlStop,         .u.us = BP_GPIO_4_AH},
  {bp_usGpioLedGpon,           .u.us = BP_GPIO_8_AH},
  {bp_usGpioLedGponFail,       .u.us = BP_GPIO_16_AH},
  {bp_usGpioLedWanData,        .u.us = BP_GPIO_15_AH},
  {bp_usGpioLedWanError,       .u.us = BP_GPIO_17_AH},
  {bp_usGpioLedMoCA,           .u.us = BP_GPIO_5_AH},
  {bp_usWirelessFlags,         .u.us = 0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0xbf},
  {bp_ulPhyId0,                .u.ul = 0x00},
  {bp_ulPhyId1,                .u.ul = 0x01},
  {bp_ulPhyId2,                .u.ul = 0x14},
  {bp_ulPhyId3,                .u.ul = 0x12},
  {bp_ulPhyId4,                .u.ul = 0x18},
  {bp_ulPhyId5,                .u.ul = 0xff},
  {bp_ulPhyId7,                .u.ul = 0xff},
  {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
  {bp_ucDspAddress,            .u.uc = 0},
  {bp_usGponOpticsType,        .u.ul = BP_GPON_OPTICS_TYPE_LEGACY},
  {bp_last}
};

static bp_elem_t g_bcm96816pvwm[] = {
  {bp_cpBoardId,               .u.cp = "96816PVWM"},
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_GPHY_LED_0 |
                                       BP_OVERLAY_GPHY_LED_1 |
                                       BP_OVERLAY_MOCA_LED)},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_GPIO_3_AH},
  {bp_usGpioLedBlStop,         .u.us = BP_GPIO_4_AH},
  {bp_usGpioLedGpon,           .u.us = BP_GPIO_8_AH},
  {bp_usGpioLedGponFail,       .u.us = BP_GPIO_2_AH},
  {bp_usGpioLedWanData,        .u.us = BP_GPIO_19_AH},
  {bp_usGpioLedWanError,       .u.us = BP_GPIO_20_AH},
  {bp_usGpioLedMoCA,           .u.us = BP_GPIO_5_AH},
  {bp_usGpioLedMoCAFail,       .u.us = BP_GPIO_37_AH},
  {bp_usWirelessFlags,         .u.us = 0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0xbf},
  {bp_ulPhyId0,                .u.ul = 0x00},
  {bp_ulPhyId1,                .u.ul = 0x01},
  {bp_ulPhyId2,                .u.ul = 0x11},
  {bp_ulPhyId3,                .u.ul = 0x12},
  {bp_ulPhyId4,                .u.ul = 0xff | PHYCFG_VALID}, /* WAN interface */
  {bp_ulPhyId5,                .u.ul = 0xff},
  {bp_ulPhyId7,                .u.ul = 0xff},
  {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
  {bp_ucDspAddress,            .u.uc = 0},
  {bp_usGponOpticsType,        .u.us = BP_GPON_OPTICS_TYPE_LEGACY},
  {bp_last}
};

#if !defined(_CFE_)
unsigned char _6818RgParams[BP_OPTICAL_PARAMS_LEN] = {0x28,0x03,0x02,0x0B,0x00,0xD8,0x00,0x77,
                                                      0x01,0xB8,0x7F,0x02,0x02,0x32,0x00,0x00,
                                                      0x00,0x34,0xFA,0x00,0x00,0x09,0x00,0x00,
                                                      0x08,0x6F,0xFF,0xFF,0xEF,0xFF,0xFF,0xFF,
                                                      0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,
                                                      0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x01};
#endif

static bp_elem_t g_bcm96818rg[] = {
  {bp_cpBoardId,               .u.cp = "96818RG"},
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_GPHY_LED_0 |
                                       BP_OVERLAY_GPHY_LED_1 |
                                       BP_OVERLAY_SERIAL_LEDS)},
  {bp_usGpioLedSesWireless,    .u.us = BP_SERIAL_GPIO_11_AL},
  {bp_usGpioLedWanData,        .u.us = BP_GPIO_19_AH},
  {bp_usGpioLedWanError,       .u.us = BP_SERIAL_GPIO_12_AH},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_SERIAL_GPIO_0_AH},
  {bp_usGpioLedBlStop,         .u.us = BP_SERIAL_GPIO_1_AH},
  {bp_usGpioLedGpon,           .u.us = BP_GPIO_8_AH},
  {bp_usGpioLedGponFail,       .u.us = BP_SERIAL_GPIO_6_AH},
  {bp_usWirelessFlags,         .u.us = 0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x8f},
  {bp_ulPhyId0,                .u.ul = BP_PHY_ID_0},
  {bp_usSpeedLed100,           .u.us = BP_SERIAL_GPIO_2_AL},
  {bp_usSpeedLed1000,          .u.us = BP_SERIAL_GPIO_3_AL},
  {bp_ulPhyId1,                .u.ul = BP_PHY_ID_1},
  {bp_usSpeedLed100,           .u.us = BP_SERIAL_GPIO_4_AL},
  {bp_usSpeedLed1000,          .u.us = BP_SERIAL_GPIO_5_AL},
  {bp_ulPhyId2,                .u.ul  = PHY_INTEGRATED_VALID | PHY_EXTERNAL | MAC_IF_RGMII | BP_PHY_ID_24},
  {bp_ulPhyId3,                .u.ul  = PHY_INTEGRATED_VALID | PHY_EXTERNAL | MAC_IF_RGMII | BP_PHY_ID_25},
  {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
  {bp_ucDspAddress,            .u.uc = 0},
  {bp_usGpioVoip1Led,          .u.us = BP_SERIAL_GPIO_7_AL},
  {bp_usGpioVoip2Led,          .u.us = BP_SERIAL_GPIO_8_AL},  
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_0},
  {bp_usGpioLaserDis,          .u.us = BP_GPIO_0_AL},
  {bp_usGpioLaserTxPwrEn,      .u.us = BP_GPIO_5_AL},
  {bp_usGponOpticsType,        .u.us = BP_GPON_OPTICS_TYPE_LEGACY},  
  {bp_last}
};

static bp_elem_t g_bcm96818rg_bosa[] = {
  {bp_cpBoardId,               .u.cp = "96818RG_BOSA"},
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_GPHY_LED_0 |
                                       BP_OVERLAY_GPHY_LED_1 |
                                       BP_OVERLAY_SERIAL_LEDS)},
  {bp_usGpioLedSesWireless,    .u.us = BP_SERIAL_GPIO_11_AL},
  {bp_usGpioLedWanData,        .u.us = BP_GPIO_19_AH},
  {bp_usGpioLedWanError,       .u.us = BP_SERIAL_GPIO_12_AH},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_SERIAL_GPIO_0_AH},
  {bp_usGpioLedBlStop,         .u.us = BP_SERIAL_GPIO_1_AH},
  {bp_usGpioLedGpon,           .u.us = BP_GPIO_8_AH},
  {bp_usGpioLedGponFail,       .u.us = BP_SERIAL_GPIO_6_AH},
  {bp_usWirelessFlags,         .u.us = 0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x8f},
  {bp_ulPhyId0,                .u.ul = BP_PHY_ID_0},
  {bp_usSpeedLed100,           .u.us = BP_SERIAL_GPIO_2_AL},
  {bp_usSpeedLed1000,          .u.us = BP_SERIAL_GPIO_3_AL},
  {bp_ulPhyId1,                .u.ul = BP_PHY_ID_1},
  {bp_usSpeedLed100,           .u.us = BP_SERIAL_GPIO_4_AL},
  {bp_usSpeedLed1000,          .u.us = BP_SERIAL_GPIO_5_AL},
  {bp_ulPhyId2,                .u.ul  = PHY_INTEGRATED_VALID | PHY_EXTERNAL | MAC_IF_RGMII | BP_PHY_ID_24},
  {bp_ulPhyId3,                .u.ul  = PHY_INTEGRATED_VALID | PHY_EXTERNAL | MAC_IF_RGMII | BP_PHY_ID_25},
  {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
  {bp_ucDspAddress,            .u.uc = 0},
  {bp_usGpioVoip1Led,          .u.us = BP_SERIAL_GPIO_7_AL},
  {bp_usGpioVoip2Led,          .u.us = BP_SERIAL_GPIO_8_AL},  
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_0},
  {bp_usGpioLaserDis,          .u.us = BP_GPIO_0_AL},
  {bp_usGpioLaserTxPwrEn,      .u.us = BP_GPIO_5_AL},
  {bp_usGponOpticsType,        .u.us = BP_GPON_OPTICS_TYPE_BOSA},
#if !defined(_CFE_)
  {bp_cpDefaultOpticalParams,  .u.ucp = _6818RgParams},    
#endif
  {bp_last}
};

static bp_elem_t g_bcm96818rg_fe[] = {
  {bp_cpBoardId,               .u.cp = "96818RG_FE"},
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_GPHY_LED_0 |
                                       BP_OVERLAY_GPHY_LED_1 |
                                       BP_OVERLAY_SERIAL_LEDS)},
  {bp_usGpioLedSesWireless,    .u.us = BP_SERIAL_GPIO_11_AL},
  {bp_usGpioLedWanData,        .u.us = BP_GPIO_19_AH},
  {bp_usGpioLedWanError,       .u.us = BP_SERIAL_GPIO_12_AH},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_SERIAL_GPIO_0_AH},
  {bp_usGpioLedBlStop,         .u.us = BP_SERIAL_GPIO_1_AH},
  {bp_usGpioLedGpon,           .u.us = BP_GPIO_8_AH},
  {bp_usGpioLedGponFail,       .u.us = BP_SERIAL_GPIO_6_AH},
  {bp_usWirelessFlags,         .u.us = 0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x9f},
  {bp_ulPhyId0,                .u.ul = BP_PHY_ID_0},
  {bp_usSpeedLed100,           .u.us = BP_SERIAL_GPIO_2_AL},
  {bp_usSpeedLed1000,          .u.us = BP_SERIAL_GPIO_3_AL},
  {bp_ulPhyId1,                .u.ul = BP_PHY_ID_1},
  {bp_usSpeedLed100,           .u.us = BP_SERIAL_GPIO_4_AL},
  {bp_usSpeedLed1000,          .u.us = BP_SERIAL_GPIO_5_AL},
  {bp_ulPhyId2,                .u.ul  = PHY_INTEGRATED_VALID | PHY_EXTERNAL | MAC_IF_RGMII| BP_PHY_ID_24},
  {bp_ulPhyId3,                .u.ul  = PHY_INTEGRATED_VALID | PHY_EXTERNAL | MAC_IF_RGMII| BP_PHY_ID_25},
  {bp_ulPhyId4,                .u.ul = PHYCFG_VALID | MII_OVER_GPIO_VALID | PHY_INTEGRATED_VALID | PHY_EXTERNAL | BP_PHY_ID_16},
  {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
  {bp_ucDspAddress,            .u.uc = 0},
  {bp_usGpioVoip1Led,          .u.us = BP_SERIAL_GPIO_7_AL},
  {bp_usGpioVoip2Led,          .u.us = BP_SERIAL_GPIO_8_AL},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_0},  
  {bp_usGpioLaserDis,          .u.us = BP_GPIO_0_AL},
  {bp_usGpioLaserTxPwrEn,      .u.us = BP_GPIO_5_AL},
  {bp_usGponOpticsType,        .u.us = BP_GPON_OPTICS_TYPE_BOSA},
#if !defined(_CFE_)
  {bp_cpDefaultOpticalParams,  .u.ucp = _6818RgParams},    
#endif
  {bp_last}
};

#if !defined(_CFE_)
unsigned char _68128RgParams[BP_OPTICAL_PARAMS_LEN] = {0x28,0x03,0x02,0x0B,0x00,0xD8,0x00,0x77,
                                                       0x01,0xC5,0x26,0x02,0x02,0x32,0x00,0x00,
                                                       0x00,0x34,0xFA,0x00,0x00,0x09,0x00,0x00,
                                                       0x08,0x6F,0xFF,0xFF,0xEF,0xFF,0xFF,0xFF,
                                                       0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,
                                                       0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x01};
#endif

static bp_elem_t g_bcm968128rg[] = {
  {bp_cpBoardId,               .u.cp = "968128RG"},
  {bp_ulGpioOverlay,           .u.ul = BP_OVERLAY_GPHY_LED_0},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_GPIO_18_AH},
  {bp_usGpioLedBlStop,         .u.us = BP_GPIO_19_AH},
  {bp_usGpioLedGpon,           .u.us = BP_GPIO_8_AL},
  {bp_usWirelessFlags,         .u.us = 0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x81},
  {bp_ulPhyId0,                .u.ul = BP_PHY_ID_0},
  {bp_usSpeedLed100,           .u.us = BP_GPIO_29_AL},
  {bp_usSpeedLed1000,          .u.us = BP_GPIO_26_AL},
  {bp_ulPhyId7,                .u.ul = BP_PHY_ID_NOT_SPECIFIED},
  {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
  {bp_ucDspAddress,            .u.uc = 0},
  {bp_usGpioLaserDis,          .u.us = BP_GPIO_11_AL},
  {bp_usGpioLaserTxPwrEn,      .u.us = BP_GPIO_39_AH},
  {bp_usGponOpticsType,        .u.us = BP_GPON_OPTICS_TYPE_BOSA},
#if !defined(_CFE_)
  {bp_cpDefaultOpticalParams,  .u.ucp = _68128RgParams},  
#endif
  {bp_last}
};

static bp_elem_t g_bcm96829rg[] = {
  {bp_cpBoardId,               .u.cp = "96829RG"},
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_GPHY_LED_0 |
                                       BP_OVERLAY_GPHY_LED_1 |
                                       BP_OVERLAY_MOCA_LED)},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_GPIO_3_AH},
  {bp_usGpioLedBlStop,         .u.us = BP_GPIO_4_AH},
  {bp_usGpioLedMoCA,           .u.us = BP_GPIO_5_AL},
  {bp_usGpioLedMoCAFail,       .u.us = BP_GPIO_37_AH},
  {bp_usWirelessFlags,         .u.us = 0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0xa3},
  {bp_ulPhyId0,                .u.ul = 0x00},
  {bp_ulPhyId1,                .u.ul = 0x01},
  {bp_ulPhyId2,                .u.ul = 0xff},
  {bp_ulPhyId3,                .u.ul = 0xff},
  {bp_ulPhyId4,                .u.ul = 0x00},
  {bp_ulPhyId5,                .u.ul = 0xff},
  {bp_ulPhyId6,                .u.ul = 0x00},
  {bp_ulPhyId7,                .u.ul = 0xff},
  {bp_usGponOpticsType,        .u.us = BP_GPON_OPTICS_TYPE_LEGACY},
  {bp_last}
};

static bp_elem_t g_bcm96816p2og[] = {
  {bp_cpBoardId,               .u.cp = "96816P2OG"},
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_GPHY_LED_0 |
                                       BP_OVERLAY_GPHY_LED_1 |
                                       BP_OVERLAY_PCI |
                                       BP_OVERLAY_MOCA_LED)},
  {bp_usGpioFpgaReset,         .u.us = BP_GPIO_2_AH},
  {bp_usGpioLedGpon,           .u.us = BP_GPIO_8_AH},
  {bp_usGpioLedGponFail,       .u.us = BP_GPIO_16_AH},
  {bp_usWirelessFlags,         .u.us = 0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0xaf},
  {bp_ulPhyId0,                .u.ul = 0x00},
  {bp_ulPhyId1,                .u.ul = 0x01},
  {bp_ulPhyId2,                .u.ul = 0x11},
  {bp_ulPhyId3,                .u.ul = 0xff},
  {bp_ulPhyId5,                .u.ul = 0xff},
  {bp_ulPhyId7,                .u.ul = 0xff},    
  {bp_usGponOpticsType,        .u.us = BP_GPON_OPTICS_TYPE_LEGACY},
  {bp_last}
};

static bp_elem_t g_bcm96812pg[] = {
  {bp_cpBoardId,               .u.cp = "96812PG"},
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_GPHY_LED_0 |
                                       BP_OVERLAY_GPHY_LED_1)},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_GPIO_3_AH},
  {bp_usGpioLedBlStop,         .u.us = BP_GPIO_4_AH},
  {bp_usGpioLedGpon,           .u.us = BP_GPIO_8_AH},
  {bp_usGpioLedGponFail,       .u.us = BP_GPIO_2_AH},
  {bp_usGpioLedWanData,        .u.us = BP_GPIO_5_AH},
  {bp_usGpioLedWanError,       .u.us = BP_GPIO_15_AH},
  {bp_usWirelessFlags,         .u.us = 0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0xaf},
  {bp_ulPhyId0,                .u.ul = 0x00},
  {bp_ulPhyId1,                .u.ul = 0x01},
  {bp_ulPhyId2,                .u.ul = 0x11},
  {bp_ulPhyId3,                .u.ul = 0x12},
  {bp_ulPhyId5,                .u.ul = 0xff},
  {bp_ulPhyId7,                .u.ul = 0xff},
  {bp_usGponOpticsType,        .u.us = BP_GPON_OPTICS_TYPE_LEGACY},
  {bp_last}
};

static bp_elem_t g_bcm96819bhr[] = {
  {bp_cpBoardId,               .u.cp = "96819BHR"},
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_GPHY_LED_0 |
                                       BP_OVERLAY_GPHY_LED_1 |
                                       BP_OVERLAY_MOCA_LED)},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_GPIO_3_AH},
  {bp_usGpioLedBlStop,         .u.us = BP_GPIO_4_AH},
  {bp_usGpioLedMoCA,           .u.us = BP_GPIO_5_AL},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_3},
  {bp_usWirelessFlags,         .u.us = 0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x3f},
  {bp_ulPhyId0,                .u.ul = 0x00},
  {bp_usSpeedLed100,           .u.us = BP_GPIO_13_AL},
  {bp_usSpeedLed1000,          .u.us = BP_GPIO_38_AL},
  {bp_ulPhyId1,                .u.ul = 0x01},
  {bp_usSpeedLed100,           .u.us = BP_GPIO_30_AL},
  {bp_usSpeedLed1000,          .u.us = BP_GPIO_31_AL},
  {bp_ulPhyId2,                .u.ul = 0x14},
  {bp_ulPhyId3,                .u.ul = 0x12},
  {bp_ulPhyId4,                .u.ul = 0xa1},
  {bp_ulPhyId5,                .u.ul = 0xff},    
  {bp_usGponOpticsType,        .u.us = BP_GPON_OPTICS_TYPE_LEGACY},
  {bp_last}
};

static bp_elem_t g_bcm968121pg[] = {
  {bp_cpBoardId,               .u.cp = "968121PG"},
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_GPHY_LED_0)},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_GPIO_3_AH},
  {bp_usGpioLedBlStop,         .u.us = BP_GPIO_24_AH},
  {bp_usGpioLedGpon,           .u.us = BP_GPIO_8_AL},
  {bp_usWirelessFlags,         .u.us = 0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x95},
  {bp_ulPhyId0,                .u.ul = 0x00},
  {bp_ulPhyId1,                .u.ul = 0x00},
  {bp_ulPhyId2,                .u.ul = 0x18},
  {bp_ulPhyId3,                .u.ul = 0x00},
  {bp_ulPhyId4,                .u.ul = 0xff | PHYCFG_VALID}, /* WAN Interface */
  {bp_ulPhyId5,                .u.ul = 0x00},
  {bp_ulPhyId6,                .u.ul = 0x00},
  {bp_ulPhyId7,                .u.ul = 0xff},    
  {bp_usGponOpticsType,        .u.us = BP_GPON_OPTICS_TYPE_LEGACY},
  {bp_last}
};

static bp_elem_t g_bcm968121p[] = {
  {bp_cpBoardId,               .u.cp = "968121P"},
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_GPHY_LED_0)},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_GPIO_3_AH},
  {bp_usGpioLedBlStop,         .u.us = BP_GPIO_24_AH},
  {bp_usGpioLedGpon,           .u.us = BP_GPIO_8_AL},
  {bp_usWirelessFlags,         .u.us = 0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x91},
  {bp_ulPhyId0,                .u.ul = 0x00},
  {bp_ulPhyId4,                .u.ul = 0xff | PHYCFG_VALID}, /* WAN Interface */
  {bp_ulPhyId7,                .u.ul = 0xff},    
  {bp_usGponOpticsType,        .u.us = BP_GPON_OPTICS_TYPE_LEGACY},
  {bp_last}
};

static bp_elem_t g_bcm96819bhrgr[] = {
  {bp_cpBoardId,               .u.cp = "96819BHRGR"},
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_GPHY_LED_0 |
                                       BP_OVERLAY_GPHY_LED_1 |
                                       BP_OVERLAY_MOCA_LED)},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_GPIO_3_AH},
  {bp_usGpioLedBlStop,         .u.us = BP_GPIO_4_AH},
  {bp_usGpioLedMoCA,           .u.us = BP_GPIO_5_AL},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_3},
  {bp_usWirelessFlags,         .u.us = 0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x3f},
  {bp_ulPhyId0,                .u.ul = 0x00},
  {bp_usSpeedLed100,           .u.us = BP_GPIO_13_AL},
  {bp_usSpeedLed1000,          .u.us = BP_GPIO_38_AL},
  {bp_ulPhyId1,                .u.ul = 0x01},
  {bp_usSpeedLed100,           .u.us = BP_GPIO_2_AL},
  {bp_usSpeedLed1000,          .u.us = BP_GPIO_31_AL},
  {bp_ulPhyId2,                .u.ul = 0x18},
  {bp_ulPhyId3,                .u.ul = 0x19},
  {bp_ulPhyId4,                .u.ul = 0xa1},
  {bp_ulPhyId5,                .u.ul = 0xff},    
  {bp_usGponOpticsType,        .u.us = BP_GPON_OPTICS_TYPE_LEGACY},
  {bp_last}
};

static bp_elem_t * g_BoardParms[] = {g_bcm96816sv, g_bcm96816pvwm,
  g_bcm96829rg, g_bcm96816p2og, g_bcm96812pg, g_bcm96819bhr,
  g_bcm968121pg, g_bcm968121p, g_bcm96819bhrgr, g_bcm96818rg, g_bcm96818rg_bosa, g_bcm96818rg_fe, g_bcm968128rg, 0};
#endif

#if defined(_BCM96328_) || defined(CONFIG_BCM96328)

static bp_elem_t g_bcm96328avng[] = {
  {bp_cpBoardId,               .u.cp = "96328avng"},
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_EPHY_LED_0 |
                                       BP_OVERLAY_EPHY_LED_1 |
                                       BP_OVERLAY_EPHY_LED_2 |
                                       BP_OVERLAY_EPHY_LED_3 |
                                       BP_OVERLAY_PCIE_CLKREQ)},
  {bp_usGpioLedAdsl,           .u.us = BP_GPIO_3_AL},
  {bp_usGpioLedSesWireless,    .u.us = BP_GPIO_9_AL},
  {bp_usGpioLedWanData,        .u.us = BP_GPIO_0_AL},
  {bp_usGpioLedWanError,       .u.us = BP_GPIO_2_AL},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_GPIO_4_AL},
  {bp_usGpioLedBlStop,         .u.us = BP_GPIO_8_AL},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_0},
  {bp_usExtIntrSesBtnWireless, .u.us = BP_EXT_INTR_1},
  {bp_usAntInUseWireless,      .u.us = BP_WLAN_ANT_MAIN},
  {bp_usWirelessFlags,         .u.us = 0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x1f},
  {bp_ulPhyId0,                .u.ul = 0x01},
  {bp_ulPhyId1,                .u.ul = 0x02},
  {bp_ulPhyId2,                .u.ul = 0x03},
  {bp_ulPhyId3,                .u.ul = 0x04},
  {bp_ulPhyId4,                .u.ul = 0x18},
  {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
  {bp_ucDspAddress,            .u.uc = 0},
  {bp_usGpioVoip1Led,          .u.us = BP_GPIO_6_AL},
  {bp_usGpioVoip2Led,          .u.us = BP_GPIO_7_AL},
  {bp_usGpioPotsLed,           .u.us = BP_GPIO_5_AL},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6301 | BP_AFE_FE_ANNEXA | BP_AFE_FE_AVMODE_ADSL | BP_AFE_FE_REV_6301_REV_5_1_1},
  {bp_last}
};

static bp_elem_t g_bcm96328avngrP1[] = {
  {bp_cpBoardId,               .u.cp = "96328avngrP1"},
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_SPI_EXT_CS |
                                       BP_OVERLAY_EPHY_LED_0 |
                                       BP_OVERLAY_EPHY_LED_1 |
                                       BP_OVERLAY_EPHY_LED_2 |
                                       BP_OVERLAY_EPHY_LED_3 |
                                       BP_OVERLAY_SERIAL_LEDS |
                                       BP_OVERLAY_PCIE_CLKREQ)},
  {bp_usGpioLedAdsl,           .u.us = BP_SERIAL_GPIO_10_AL},
  {bp_usGpioLedSesWireless,    .u.us = BP_SERIAL_GPIO_11_AL},
  {bp_usGpioLedWanData,        .u.us = BP_SERIAL_GPIO_1_AL},
  {bp_usGpioLedWanError,       .u.us = BP_SERIAL_GPIO_13_AL},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_SERIAL_GPIO_8_AL},
  {bp_usGpioLedBlStop,         .u.us = BP_SERIAL_GPIO_15_AL},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_0},
  {bp_usExtIntrSesBtnWireless, .u.us = BP_EXT_INTR_1},
  {bp_usAntInUseWireless,      .u.us = BP_WLAN_ANT_MAIN},
  {bp_usWirelessFlags,         .u.us = 0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x1f},
  {bp_ulPhyId0,                .u.ul = 0x01},
  {bp_ulPhyId1,                .u.ul = 0x02},
  {bp_ulPhyId2,                .u.ul = 0x03},
  {bp_ulPhyId3,                .u.ul = 0x04},
  {bp_ulPhyId4,                .u.ul = 0x18},
  {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
  {bp_ucDspAddress,            .u.uc = 0},
  {bp_usGpioVoip1Led,          .u.us = BP_SERIAL_GPIO_14_AL},
  {bp_usGpioVoip2Led,          .u.us = BP_SERIAL_GPIO_12_AL},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6301 | BP_AFE_FE_ANNEXA | BP_AFE_FE_AVMODE_ADSL | BP_AFE_FE_REV_6301_REV_5_1_1},
  {bp_last}
};

static bp_elem_t g_bcm96328avngr[] = {
  {bp_cpBoardId,               .u.cp = "96328avngr"},
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_SPI_EXT_CS |
                                       BP_OVERLAY_EPHY_LED_0 |
                                       BP_OVERLAY_EPHY_LED_1 |
                                       BP_OVERLAY_EPHY_LED_2 |
                                       BP_OVERLAY_EPHY_LED_3 |
                                       BP_OVERLAY_SERIAL_LEDS |
                                       BP_OVERLAY_PCIE_CLKREQ)},
  {bp_usGpioLedAdsl,           .u.us = BP_SERIAL_GPIO_10_AL},
  {bp_usGpioLedSesWireless,    .u.us = BP_SERIAL_GPIO_11_AL},
  {bp_usGpioLedWanData,        .u.us = BP_GPIO_1_AL},
  {bp_usGpioLedWanError,       .u.us = BP_SERIAL_GPIO_13_AL},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_SERIAL_GPIO_8_AL},
  {bp_usGpioLedBlStop,         .u.us = BP_SERIAL_GPIO_15_AL},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_0},
  {bp_usExtIntrSesBtnWireless, .u.us = BP_EXT_INTR_1},
  {bp_usAntInUseWireless,      .u.us = BP_WLAN_ANT_MAIN},
  {bp_usWirelessFlags,         .u.us = 0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x1f},
  {bp_ulPhyId0,                .u.ul = 0x01},
  {bp_ulPhyId1,                .u.ul = 0x02},
  {bp_ulPhyId2,                .u.ul = 0x03},
  {bp_ulPhyId3,                .u.ul = 0x04},
  {bp_ulPhyId4,                .u.ul = 0x18},
  {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
  {bp_ucDspAddress,            .u.uc = 0},
  {bp_usGpioVoip1Led,          .u.us = BP_SERIAL_GPIO_14_AL},
  {bp_usGpioVoip2Led,          .u.us = BP_SERIAL_GPIO_12_AL},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6301 | BP_AFE_FE_ANNEXA | BP_AFE_FE_AVMODE_ADSL | BP_AFE_FE_REV_6301_REV_5_1_1},
  {bp_last}
};

static bp_elem_t g_bcm963281TAN[] = {
  {bp_cpBoardId,               .u.cp = "963281TAN"},
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_EPHY_LED_0 |
                                       BP_OVERLAY_EPHY_LED_1 |
                                       BP_OVERLAY_EPHY_LED_2 |
                                       BP_OVERLAY_EPHY_LED_3 |
                                       BP_OVERLAY_PCIE_CLKREQ)},
  {bp_usGpioLedAdsl,           .u.us = BP_GPIO_11_AL},
  {bp_usGpioLedSesWireless,    .u.us = BP_GPIO_9_AL},
  {bp_usGpioLedWanData,        .u.us = BP_GPIO_1_AL},
  {bp_usGpioLedWanError,       .u.us = BP_GPIO_7_AL},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_GPIO_4_AL},
  {bp_usGpioLedBlStop,         .u.us = BP_GPIO_8_AL},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_0},
  {bp_usExtIntrSesBtnWireless, .u.us = BP_EXT_INTR_1},
  {bp_usAntInUseWireless,      .u.us = BP_WLAN_ANT_MAIN},
  {bp_usWirelessFlags,         .u.us = 0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x0f},
  {bp_ulPhyId0,                .u.ul = 0x01},
  {bp_ulPhyId1,                .u.ul = 0x02},
  {bp_ulPhyId2,                .u.ul = 0x03},
  {bp_ulPhyId3,                .u.ul = 0x04},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6301 | BP_AFE_FE_ANNEXA | BP_AFE_FE_AVMODE_ADSL | BP_AFE_FE_REV_6301_REV_5_1_1},
  {bp_last}
};

static bp_elem_t g_bcm963281TAN2[] = {
  {bp_cpBoardId,               .u.cp = "963281TAN2"},
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_EPHY_LED_0 |
                                       BP_OVERLAY_EPHY_LED_1 |
                                       BP_OVERLAY_EPHY_LED_2 |
                                       BP_OVERLAY_EPHY_LED_3 |
                                       BP_OVERLAY_PCIE_CLKREQ)},
  {bp_usGpioLedAdsl,           .u.us = BP_GPIO_11_AL},
  {bp_usGpioLedSesWireless,    .u.us = BP_GPIO_9_AL},
  {bp_usGpioLedWanData,        .u.us = BP_GPIO_1_AL},
  {bp_usGpioLedWanError,       .u.us = BP_GPIO_7_AL},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_GPIO_4_AL},
  {bp_usGpioLedBlStop,         .u.us = BP_GPIO_8_AL},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_0},
  {bp_usExtIntrSesBtnWireless, .u.us = BP_EXT_INTR_1},
  {bp_usAntInUseWireless,      .u.us = BP_WLAN_ANT_MAIN},
  {bp_usWirelessFlags,         .u.us = 0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x0f},
  {bp_ulPhyId0,                .u.ul = 0x01},
  {bp_ulPhyId1,                .u.ul = 0x02},
  {bp_ulPhyId2,                .u.ul = 0x03},
  {bp_ulPhyId3,                .u.ul = 0x04},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6301 | BP_AFE_FE_ANNEXA | BP_AFE_FE_AVMODE_ADSL | BP_AFE_FE_REV_6301_REV_5_1_2},
  {bp_last}
};

static bp_elem_t g_bcm963281TAN3[] = {
  {bp_cpBoardId,               .u.cp = "963281TAN3"},
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_EPHY_LED_0 |
                                       BP_OVERLAY_EPHY_LED_1 |
                                       BP_OVERLAY_EPHY_LED_2 |
                                       BP_OVERLAY_EPHY_LED_3 |
                                       BP_OVERLAY_PCIE_CLKREQ)},
  {bp_usGpioLedAdsl,           .u.us = BP_GPIO_11_AL},
  {bp_usGpioLedSesWireless,    .u.us = BP_GPIO_9_AL},
  {bp_usGpioLedWanData,        .u.us = BP_GPIO_1_AL},
  {bp_usGpioLedWanError,       .u.us = BP_GPIO_7_AL},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_GPIO_4_AL},
  {bp_usGpioLedBlStop,         .u.us = BP_GPIO_8_AL},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_0},
  {bp_usExtIntrSesBtnWireless, .u.us = BP_EXT_INTR_1},
  {bp_usAntInUseWireless,      .u.us = BP_WLAN_ANT_MAIN},
  {bp_usWirelessFlags,         .u.us = 0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x0f},
  {bp_ulPhyId0,                .u.ul = 0x01},
  {bp_ulPhyId1,                .u.ul = 0x02},
  {bp_ulPhyId2,                .u.ul = 0x03},
  {bp_ulPhyId3,                .u.ul = 0x04},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6302| BP_AFE_FE_ANNEXA | BP_AFE_FE_AVMODE_ADSL | BP_AFE_FE_REV_6302_REV_5_2_2},
  {bp_last}
};

static bp_elem_t g_bcm963281TAN4[] = {
  {bp_cpBoardId,               .u.cp = "963281TAN4"},
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_EPHY_LED_0 |
                                       BP_OVERLAY_EPHY_LED_1 |
                                       BP_OVERLAY_EPHY_LED_2 |
                                       BP_OVERLAY_EPHY_LED_3 |
                                       BP_OVERLAY_PCIE_CLKREQ)},
  {bp_usGpioLedAdsl,           .u.us = BP_GPIO_11_AL},
  {bp_usGpioLedSesWireless,    .u.us = BP_GPIO_9_AL},
  {bp_usGpioLedWanData,        .u.us = BP_GPIO_1_AL},
  {bp_usGpioLedWanError,       .u.us = BP_GPIO_7_AL},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_GPIO_4_AL},
  {bp_usGpioLedBlStop,         .u.us = BP_GPIO_8_AL},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_0},
  {bp_usExtIntrSesBtnWireless, .u.us = BP_EXT_INTR_1},
  {bp_usAntInUseWireless,      .u.us = BP_WLAN_ANT_MAIN},
  {bp_usWirelessFlags,         .u.us = 0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x0f},
  {bp_ulPhyId0,                .u.ul = 0x01},
  {bp_ulPhyId1,                .u.ul = 0x02},
  {bp_ulPhyId2,                .u.ul = 0x03},
  {bp_ulPhyId3,                .u.ul = 0x04},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6301 | BP_AFE_FE_ANNEXA | BP_AFE_FE_AVMODE_ADSL | BP_AFE_FE_REV_6301_REV_5_1_2},
  {bp_last}
};

static bp_elem_t g_bcm963293epon[] = {
  {bp_cpBoardId,               .u.cp = "963293epon"},
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_SPI_EXT_CS |
                                       BP_OVERLAY_EPHY_LED_0 |
                                       BP_OVERLAY_EPHY_LED_1 |
                                       BP_OVERLAY_EPHY_LED_2 |
                                       BP_OVERLAY_EPHY_LED_3 |
                                       BP_OVERLAY_SERIAL_LEDS |
                                       BP_OVERLAY_PCIE_CLKREQ)},
  {bp_usGpioLedSesWireless,    .u.us = BP_SERIAL_GPIO_11_AL},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_SERIAL_GPIO_8_AL},
  {bp_usGpioLedBlStop,         .u.us = BP_SERIAL_GPIO_15_AL},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_0},
  {bp_usExtIntrSesBtnWireless, .u.us = BP_EXT_INTR_1},
  {bp_usAntInUseWireless,      .u.us = BP_WLAN_ANT_MAIN},
  {bp_usWirelessFlags,         .u.us = 0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x1f},
  {bp_ulPhyId0,                .u.ul = 0x01},
  {bp_ulPhyId1,                .u.ul = 0x02},
  {bp_ulPhyId2,                .u.ul = 0x03},
  {bp_ulPhyId3,                .u.ul = 0x04},
  {bp_ulPhyId4,                .u.ul = MII_DIRECT  | CONNECTED_TO_EPON_MAC},
  {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
  {bp_ucDspAddress,            .u.uc = 0},
  {bp_usGpioVoip1Led,          .u.us = BP_SERIAL_GPIO_14_AL},
  {bp_usGpioVoip2Led,          .u.us = BP_SERIAL_GPIO_12_AL},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6301 | BP_AFE_FE_ANNEXA | BP_AFE_FE_AVMODE_ADSL | BP_AFE_FE_REV_6301_REV_5_1_1},
  {bp_last}
};

static bp_elem_t g_bcm963293epon_gphy[] = {
  {bp_cpBoardId,               .u.cp = "963293epon_gphy"},
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_SPI_EXT_CS |
                                       BP_OVERLAY_EPHY_LED_0 |
                                       BP_OVERLAY_EPHY_LED_1 |
                                       BP_OVERLAY_EPHY_LED_2 |
                                       BP_OVERLAY_EPHY_LED_3 |
                                       BP_OVERLAY_SERIAL_LEDS |
                                       BP_OVERLAY_PCIE_CLKREQ)},
  {bp_usGpioLedSesWireless,    .u.us = BP_SERIAL_GPIO_11_AL},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_SERIAL_GPIO_8_AL},
  {bp_usGpioLedBlStop,         .u.us = BP_SERIAL_GPIO_15_AL},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_0},
  {bp_usExtIntrSesBtnWireless, .u.us = BP_EXT_INTR_1},
  {bp_usAntInUseWireless,      .u.us = BP_WLAN_ANT_MAIN},
  {bp_usWirelessFlags,         .u.us = 0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x1f},
  {bp_ulPhyId0,                .u.ul = 0x01},
  {bp_ulPhyId1,                .u.ul = 0x02},
  {bp_ulPhyId2,                .u.ul = 0x03},
  {bp_ulPhyId3,                .u.ul = 0x04},
  {bp_ulPhyId4,                .u.ul = 0x18 | CONNECTED_TO_EPON_MAC},
  {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
  {bp_ucDspAddress,            .u.uc = 0},
  {bp_usGpioVoip1Led,          .u.us = BP_SERIAL_GPIO_14_AL},
  {bp_usGpioVoip2Led,          .u.us = BP_SERIAL_GPIO_12_AL},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6301 | BP_AFE_FE_ANNEXA | BP_AFE_FE_AVMODE_ADSL | BP_AFE_FE_REV_6301_REV_5_1_1},
  {bp_last}
};

static bp_elem_t g_bcm963283_24tstbrd[] = {
  {bp_cpBoardId,               .u.cp = "963283_24tstbrd"},
  {bp_ulGpioOverlay,           .u.ul =( BP_OVERLAY_PCIE_CLKREQ)},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_GPIO_29_AL},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x1f},
  {bp_ulPhyId0,                .u.ul = 0x01},
  {bp_ulPhyId1,                .u.ul = 0x02},
  {bp_ulPhyId2,                .u.ul = 0x03},
  {bp_ulPhyId3,                .u.ul = 0x04},
  {bp_ulPhyId4,                .u.ul = 0x18},
  {bp_last}
};

static bp_elem_t g_bcm93715rv[] = {
  {bp_cpBoardId,                 .u.cp = "93715rv"},
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_SPI_EXT_CS)},

  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x01},
  {bp_ulPhyId0,                .u.ul = 0x01 | CONNECTED_TO_EPON_MAC},

  {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
  {bp_ucDspAddress,            .u.uc = 0},
  {bp_usGpioVoip1Led,          .u.us = BP_SERIAL_GPIO_14_AL},
  {bp_usGpioVoip2Led,          .u.us = BP_SERIAL_GPIO_12_AL},
  
  {bp_usGpioPassDyingGasp,     .u.us = BP_SERIAL_GPIO_1_AL},
  
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6301 | BP_AFE_FE_ANNEXA | BP_AFE_FE_AVMODE_ADSL | BP_AFE_FE_REV_6301_REV_5_1_1},

  {bp_last}
 };
// << Jimmy.Lin : For AR-5381u
static bp_elem_t g_96328at_1341n2[] = {
  {bp_cpBoardId ,              .u.cp = "96328AT-1341N2"},
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_EPHY_LED_0 |
                                       BP_OVERLAY_EPHY_LED_1 |
                                       BP_OVERLAY_EPHY_LED_2 |
                                       BP_OVERLAY_EPHY_LED_3 )},
  {bp_usGpioLedAdsl,           .u.us = BP_GPIO_3_AL},
  {bp_usGpioLedSesWireless,    .u.us = BP_GPIO_9_AL},
  {bp_usGpioLedWanData,        .u.us = BP_GPIO_11_AL},
  {bp_usGpioLedWanError,       .u.us = BP_GPIO_2_AL},
  {bp_usGpioCtInternetLed,     .u.us = BP_GPIO_11_AL},
  {bp_usGpioCtInternetFailLed, .u.us = BP_GPIO_2_AL},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_GPIO_4_AL},
  {bp_usGpioLedBlStop,         .u.us = BP_GPIO_8_AL},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_0},
  {bp_usExtIntrSesBtnWireless, .u.us = BP_EXT_INTR_1},
  {bp_usAntInUseWireless,      .u.us = BP_WLAN_ANT_MAIN},
  {bp_usWirelessFlags,         .u.us = 0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x0f},
  {bp_ulPhyId0,                .u.ul = 0x01},
  {bp_ulPhyId1,                .u.ul = 0x02},
  {bp_ulPhyId2,                .u.ul = 0x03},
  {bp_ulPhyId3,                .u.ul = 0x04},
//  {bp_ulPhyId4,                .u.ul = 0x11 | MAC_IFACE_VALID | MAC_IF_MII},
#ifdef ADSL_ANNEXB
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6301 | BP_AFE_FE_ANNEXB | BP_AFE_FE_AVMODE_ADSL | BP_AFE_FE_REV_6301_REV_5_1_1},
#else
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6301 | BP_AFE_FE_ANNEXA | BP_AFE_FE_AVMODE_ADSL | BP_AFE_FE_REV_6301_REV_5_1_2},
#endif
  {bp_usGpioCtWirelessBtn,     .u.us = BP_GPIO_31_AL},
  {bp_last}
};
// >> Jimmy.Lin : For AR-5381u
//<< David Rodriguez: Add AR-5381u "JAZ" board, 2014-03-13
static bp_elem_t g_96328a_1241n[] = {
  {bp_cpBoardId ,              .u.cp = "96328A-1241N"},
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_EPHY_LED_0 |
                                       BP_OVERLAY_EPHY_LED_1 |
                                       BP_OVERLAY_EPHY_LED_2 |
                                       BP_OVERLAY_EPHY_LED_3 )},
  {bp_usGpioLedAdsl,           .u.us = BP_GPIO_3_AL},
  {bp_usGpioLedSesWireless,    .u.us = BP_GPIO_9_AL},
  {bp_usGpioLedWanData,        .u.us = BP_NOT_DEFINED},
  {bp_usGpioLedWanError,       .u.us = BP_GPIO_2_AL},
  {bp_usGpioCtInternetLed,     .u.us = BP_NOT_DEFINED},
  {bp_usGpioCtInternetFailLed, .u.us = BP_GPIO_2_AL},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_GPIO_4_AL},
  {bp_usGpioLedBlStop,         .u.us = BP_GPIO_29_AL},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_0},
  {bp_usExtIntrSesBtnWireless, .u.us = BP_EXT_INTR_1},
  {bp_usAntInUseWireless,      .u.us = BP_WLAN_ANT_MAIN},
  {bp_usWirelessFlags,         .u.us = 0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x0f},
  {bp_ulPhyId0,                .u.ul = 0x01},
  {bp_ulPhyId1,                .u.ul = 0x02},
  {bp_ulPhyId2,                .u.ul = 0x03},
  {bp_ulPhyId3,                .u.ul = 0x04},
//  {bp_ulPhyId4,                .u.ul = 0x11 | MAC_IFACE_VALID | MAC_IF_MII},
#ifdef ADSL_ANNEXB
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6301 | BP_AFE_FE_ANNEXB | BP_AFE_FE_AVMODE_ADSL | BP_AFE_FE_REV_6301_REV_5_1_1},
#else
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6301 | BP_AFE_FE_ANNEXA | BP_AFE_FE_AVMODE_ADSL | BP_AFE_FE_REV_6301_REV_5_1_2},
#endif
  {bp_usGpioCtWirelessBtn,     .u.us = BP_NOT_DEFINED},
  {bp_last}
};
//>> End: Add AR-5381u "JAZ" board
//<< Add AR-5387un profile
static bp_elem_t g_96328AT_1341N3[] = {
  {bp_cpBoardId,               .u.cp = "96328AT-1341N3"},
  {bp_usGpioOverlay,           .u.ul =(BP_OVERLAY_EPHY_LED_0 |
                                       BP_OVERLAY_EPHY_LED_1 |
                                       BP_OVERLAY_EPHY_LED_2 |
                                       BP_OVERLAY_EPHY_LED_3 )},
  {bp_usGpioLedAdsl,           .u.us = BP_GPIO_11_AL},
  {bp_usGpioLedSesWireless,    .u.us = BP_GPIO_9_AL},
  {bp_usGpioLedWanData,        .u.us = BP_NOT_DEFINED},
  {bp_usGpioLedWanError,       .u.us = BP_NOT_DEFINED},
  {bp_usGpioCtInternetLed,     .u.us = BP_GPIO_1_AL},
  {bp_usGpioCtInternetFailLed, .u.us = BP_GPIO_7_AL},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_GPIO_4_AL},
  {bp_usGpioLedBlStop,         .u.us = BP_GPIO_8_AL},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_0},
  {bp_usExtIntrSesBtnWireless, .u.us = BP_EXT_INTR_1},
  {bp_usAntInUseWireless,      .u.us = BP_WLAN_ANT_AUX},
  {bp_usWirelessFlags,         .u.us = 0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x0f},
  {bp_ulPhyId0,                .u.ul = 0x01},
  {bp_ulPhyId1,                .u.ul = 0x02},
  {bp_ulPhyId2,                .u.ul = 0x03},
  {bp_ulPhyId3,                .u.ul = 0x04},
  {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
  {bp_ucDspAddress,            .u.uc = -1},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6301 | BP_AFE_FE_ANNEXA | BP_AFE_FE_AVMODE_ADSL | BP_AFE_FE_REV_6301_REV_5_1_1},
  {bp_usGpioCtWirelessBtn,         .u.us = BP_GPIO_12_AL},
  {bp_last}
};
//>> End, Add AR-5387un profile
//<< Kewei Lai : For add boardid AR-5223u
static bp_elem_t g_96328at_1341[] = {
  {bp_cpBoardId ,              .u.cp = "96328AT-1341"},
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_EPHY_LED_0 |
                                       BP_OVERLAY_EPHY_LED_1 |
                                       BP_OVERLAY_EPHY_LED_2 |
                                       BP_OVERLAY_EPHY_LED_3 )},
  {bp_usGpioLedAdsl,           .u.us = BP_GPIO_3_AL},
  {bp_usGpioLedSesWireless,    .u.us = BP_GPIO_9_AL},
  {bp_usGpioLedWanData,        .u.us = BP_GPIO_11_AL},
  {bp_usGpioLedWanError,       .u.us = BP_GPIO_2_AL},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_GPIO_4_AL},
  {bp_usGpioLedBlStop,         .u.us = BP_GPIO_8_AL},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x0f},
  {bp_ulPhyId0,                .u.ul = 0x01},
  {bp_ulPhyId1,                .u.ul = 0x02},
  {bp_ulPhyId2,                .u.ul = 0x03},
  {bp_ulPhyId3,                .u.ul = 0x04},
#ifdef ADSL_ANNEXB
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6301 | BP_AFE_FE_ANNEXB | BP_AFE_FE_AVMODE_ADSL | BP_AFE_FE_REV_6301_REV_5_1_1},
#else
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6301 | BP_AFE_FE_ANNEXA | BP_AFE_FE_AVMODE_ADSL | BP_AFE_FE_REV_6301_REV_5_1_2},
#endif
  {bp_usGpioCtInternetLed,        .u.us = BP_GPIO_11_AL},
  {bp_usGpioCtInternetFailLed,       .u.us = BP_GPIO_2_AL},
  {bp_last}
};
//>> End, For add boardid AR-5223u

static bp_elem_t * g_BoardParms[] = {
g_96328AT_1341N3, //AR-5387
// << Jimmy.Lin : For AR-5381u
g_96328at_1341n2,
// >> Jimmy.Lin : For AR-5381u
//<< David Rodriguez: Add AR-5381u "JAZ" board, 2014-03-13
g_96328a_1241n,
//>> End: Add AR-5381u "JAZ" board
//<< Kewei Lai : For add boardid AR-5223u
g_96328at_1341,
//>> End,  For add boardid AR-5223u
g_bcm96328avng, g_bcm96328avngrP1, g_bcm96328avngr, g_bcm963281TAN, g_bcm963281TAN2, g_bcm963281TAN3, g_bcm963281TAN4, g_bcm963293epon, g_bcm963293epon_gphy, g_bcm963283_24tstbrd, g_bcm93715rv, 0};
#endif

#if defined(_BCM963268_) || defined(CONFIG_BCM963268)

static char g_obsoleteStr[] = "(obsolete)";

static bp_elem_t g_bcm963268sv1[] = {
  {bp_cpBoardId,               .u.cp = "963268SV1"},
  {bp_ulDeviceOptions,         .u.ul = BP_DEVICE_OPTION_ENABLE_GMAC },
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_PHY |
                                       BP_OVERLAY_SERIAL_LEDS |
                                       BP_OVERLAY_USB_LED |
                                       BP_OVERLAY_USB_DEVICE)},
  {bp_usAntInUseWireless,      .u.us = BP_WLAN_ANT_MAIN},
  {bp_usWirelessFlags,         .u.us = 0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x0f},
  {bp_ulPhyId0,                .u.ul = 0x01},
  {bp_ulPhyId1,                .u.ul = 0x02},
  {bp_ulPhyId2,                .u.ul = 0x03},
  {bp_ulPhyId3,                .u.ul = 0x04},
  {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
  {bp_ucDspAddress,            .u.uc = 0},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6302 | BP_AFE_FE_ANNEXA | BP_AFE_FE_REV_6302_REV1},
  {bp_usGpioExtAFEReset,       .u.us = BP_GPIO_17_AL},
  {bp_last}
};

static bp_elem_t g_bcm963168mbv_17a[] = {
  {bp_cpBoardId,               .u.cp = "963168MBV_17A"},
  {bp_ulDeviceOptions,         .u.ul = BP_DEVICE_OPTION_ENABLE_GMAC },
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_PHY |
                                       BP_OVERLAY_SERIAL_LEDS |
                                       BP_OVERLAY_USB_LED |
                                       BP_OVERLAY_USB_DEVICE)},
  {bp_usGpioLedAdsl,           .u.us = BP_SERIAL_GPIO_3_AL},
  {bp_usGpioSecLedAdsl,        .u.us = BP_GPIO_9_AL},
  {bp_usGpioLedSesWireless,    .u.us = BP_SERIAL_GPIO_7_AL},
  {bp_usGpioLedWanData,        .u.us = BP_SERIAL_GPIO_8_AL},
  {bp_usGpioLedWanError,       .u.us = BP_SERIAL_GPIO_2_AL},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_GPIO_20_AL},
  {bp_usGpioLedBlStop,         .u.us = BP_GPIO_21_AL},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_0}, 
  {bp_usExtIntrSesBtnWireless, .u.us = BP_EXT_INTR_1},  
  {bp_usAntInUseWireless,      .u.us = BP_WLAN_ANT_MAIN},
  {bp_usWirelessFlags,         .u.us = 0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x5f},
  {bp_ulPhyId0,                .u.ul = 0x01},
  {bp_ulPhyId1,                .u.ul = 0x02},
  {bp_ulPhyId2,                .u.ul = 0x03},
  {bp_ulPhyId3,                .u.ul = 0x04},
  {bp_ulPhyId4,                .u.ul = 0x18 | MAC_IFACE_VALID | MAC_IF_RGMII},
  {bp_ulPhyId6,                .u.ul = 0x19 | MAC_IFACE_VALID | MAC_IF_RGMII},
  {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
  {bp_ucDspAddress,            .u.uc = 0},
  {bp_usGpioVoip1Led,          .u.us = BP_SERIAL_GPIO_4_AL},
  {bp_usGpioVoip2Led,          .u.us = BP_SERIAL_GPIO_5_AL},
  {bp_usGpioPotsLed,           .u.us = BP_SERIAL_GPIO_6_AL},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6302 | BP_AFE_FE_ANNEXA | BP_AFE_FE_REV_6302_REV_7_2_30},
  {bp_ulAfeId1,                .u.ul = BP_AFE_CHIP_6306| BP_AFE_LD_6302 | BP_AFE_FE_ANNEXA | BP_AFE_FE_REV_6302_REV_7_2_21},
  {bp_usGpioExtAFEReset,       .u.us = BP_GPIO_17_AL},
  {bp_usGpioAFELDRelay,      .u.us = BP_GPIO_39_AH},
  {bp_last}
};

//<< [CTFN-DRV-001] Antony.Wu : Support 1. Phyid to Ethx mapping and 2. IP101_1001 of ICPLUS, 20111205
#if 0
//<< Antony.Wu : Example
// @@ eth0 = 0x04, eth1 = 0x14, eth2 = 0x01, eth3 = 0x02 and eth4 = 0x03
unsigned char _963168m_abc_phymap[BP_MAX_SWITCH_PORTS] = {0x04, 0x14, 0x01, 0x02, 0x03}; 
static bp_elem_t g_963168m_1441n1abc[] = {
  {bp_cpBoardId ,              .u.cp = "963168M-abc"},
  {bp_cpComment,               .u.cp = g_obsoleteStr},
  {bp_usGpioOverlay,           .u.ul =(BP_OVERLAY_PHY |
                                       BP_OVERLAY_SERIAL_LEDS |
                                       BP_OVERLAY_USB_DEVICE)},
  {bp_usGpioLedAdsl,           .u.us = BP_SERIAL_GPIO_3_AL},
  {bp_usGpioLedSesWireless,    .u.us = BP_SERIAL_GPIO_7_AL},
  {bp_usGpioLedWanData,        .u.us = BP_SERIAL_GPIO_8_AL},
  {bp_usGpioLedWanError,       .u.us = BP_SERIAL_GPIO_2_AL},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_GPIO_20_AL},
  {bp_usGpioLedBlStop,         .u.us = BP_GPIO_21_AL},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_0},
  {bp_usExtIntrSesBtnWireless, .u.us = BP_EXT_INTR_1},
  {bp_usAntInUseWireless,      .u.us = BP_WLAN_ANT_MAIN},
  {bp_usWirelessFlags,         .u.us = 0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x4f},
  {bp_ulPhyId0,                .u.ul = 0x01},
  {bp_ulPhyId1,                .u.ul = 0x02},
  {bp_ulPhyId2,                .u.ul = 0x03},
  {bp_ulPhyId3,                .u.ul = 0x04},
  {bp_ulPhyId6,                .u.ul = 0x14 | MAC_IFACE_VALID | MAC_IF_MII},
  {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
  {bp_ucDspAddress,            .u.uc = 0},
  {bp_usGpioVoip1Led,          .u.us = BP_SERIAL_GPIO_4_AL},
  {bp_usGpioVoip2Led,          .u.us = BP_SERIAL_GPIO_5_AL},
  {bp_usGpioPotsLed,           .u.us = BP_SERIAL_GPIO_6_AL},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6302 | BP_AFE_FE_ANNEXA | BP_AFE_FE_REV_6302_REV_7_2_30},
  {bp_usGpioExtAFEReset,       .u.us = BP_GPIO_17_AL},
  {bp_ucpEthPhyMap,            .u.ucp= _963168m_abc_phymap},
  {bp_last}
};
//>> Antony.Wu : Example
#endif
//>> [CTFN-DRV-001] End

// << Antony.Wu : For VR-3031u
unsigned char _963168m_1341n1_phymap[BP_MAX_SWITCH_PORTS] = {0x04, 0x01, 0x02, 0x03, 0x00}; 
static bp_elem_t g_963168m_1341n1[] = {
  {bp_cpBoardId ,              .u.cp = "963168M-1341N1"},
  {bp_usGpioOverlay,           .u.ul =(BP_OVERLAY_PHY |
                                       BP_OVERLAY_SERIAL_LEDS)},
  {bp_usGpioLedAdsl,           .u.us = BP_SERIAL_GPIO_3_AL},
  {bp_usGpioLedSesWireless,    .u.us = BP_SERIAL_GPIO_7_AL},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_GPIO_20_AL},
  {bp_usGpioLedBlStop,         .u.us = BP_GPIO_21_AL},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_0}, // reset button uses interrupt 0
  {bp_usExtIntrSesBtnWireless, .u.us = BP_EXT_INTR_1},
  {bp_usAntInUseWireless,      .u.us = BP_WLAN_ANT_MAIN},
  {bp_usWirelessFlags,         .u.us = 0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x0f},
  {bp_ulPhyId0,                .u.ul = 0x01},
  {bp_ulPhyId1,                .u.ul = 0x02},
  {bp_ulPhyId2,                .u.ul = 0x03},
//<< Joba Yang Change Wireless PA and Advertise no 1000BASE-T full-duplex/half-duplex capability for VR-3031u_CTL
  {bp_ulPhyId3,                .u.ul = ADVERTISE_ALL_MII | PHY_ADV_CFG_VALID | 0x04},
//>> Joba Yang End
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6302 | BP_AFE_FE_ANNEXA | BP_AFE_FE_REV_6302_REV_7_2_30},
  {bp_usGpioExtAFEReset,       .u.us = BP_GPIO_17_AL},
  {bp_usGpioCtInternetLed,     .u.us = BP_SERIAL_GPIO_8_AL},
  {bp_usGpioCtInternetFailLed, .u.us = BP_SERIAL_GPIO_2_AL},
  {bp_usGpioCtUSBLed,          .u.us = BP_SERIAL_GPIO_4_AL},
  {bp_usGpioCtUSBFailLed,      .u.us = BP_SERIAL_GPIO_5_AL},
  {bp_ucpEthPhyMap, 		   .u.ucp= _963168m_1341n1_phymap},
  {bp_last}
};
// >> Antony.Wu : For VR-3031u
// << jimmylin : For VR-3036u
static bp_elem_t g_963168M_1441N3[] = {
  {bp_cpBoardId ,              .u.cp = "963168M-1441N3"},
  {bp_usGpioOverlay,           .u.ul =(BP_OVERLAY_PHY |
                                       BP_OVERLAY_SERIAL_LEDS)},
  {bp_usGpioLedAdsl,           .u.us = BP_SERIAL_GPIO_3_AL},
  {bp_usGpioLedSesWireless,    .u.us = BP_SERIAL_GPIO_7_AL},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_GPIO_20_AL},
  {bp_usGpioLedBlStop,         .u.us = BP_GPIO_21_AL},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_0}, // reset button uses interrupt 0
  {bp_usExtIntrSesBtnWireless, .u.us = BP_EXT_INTR_1},
  {bp_usAntInUseWireless,      .u.us = BP_WLAN_ANT_MAIN},
  {bp_usWirelessFlags,         .u.us = 0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x0f},
  {bp_ulPhyId0,                .u.ul = 0x01},
  {bp_ulPhyId1,                .u.ul = 0x02},
  {bp_ulPhyId2,                .u.ul = 0x03},
//<< Joba Yang Change Wireless PA and Advertise no 1000BASE-T full-duplex/half-duplex capability for VR-3031u_CTL
  {bp_ulPhyId3,                .u.ul = ADVERTISE_ALL_MII | PHY_ADV_CFG_VALID | 0x04},
//>> Joba Yang End
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6302 | BP_AFE_FE_ANNEXA | BP_AFE_FE_REV_6302_REV_7_2_30},
  {bp_usGpioExtAFEReset,       .u.us = BP_GPIO_17_AL},
  {bp_usGpioCtInternetLed,     .u.us = BP_SERIAL_GPIO_8_AL},
  {bp_usGpioCtInternetFailLed, .u.us = BP_SERIAL_GPIO_2_AL},
  {bp_usGpioCtUSBLed,          .u.us = BP_SERIAL_GPIO_4_AL},
//  {bp_usGpioCtUSBFailLed,      .u.us = BP_SERIAL_GPIO_5_AL},
  {bp_ucpEthPhyMap, 		   .u.ucp= _963168m_1341n1_phymap},
  {bp_last}
};
// >> jimmylin : For VR-3036u
// << Jimmy.Wu : For VR-3031eu
unsigned char _963168M_1441N2_phymap[BP_MAX_SWITCH_PORTS] = {0x04, 0x01, 0x02, 0x03, 0x00}; 
static bp_elem_t g_963168M_1441N2[] = {
  {bp_cpBoardId ,              .u.cp = "963168M-1441N2"},
  {bp_usGpioOverlay,           .u.ul =(BP_OVERLAY_PHY |
                                       BP_OVERLAY_SERIAL_LEDS)},
  {bp_usGpioLedAdsl,           .u.us = BP_SERIAL_GPIO_3_AL},
  {bp_usGpioLedSesWireless,    .u.us = BP_SERIAL_GPIO_7_AL},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_GPIO_20_AL},
  {bp_usGpioLedBlStop,         .u.us = BP_GPIO_21_AL},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_0},
  {bp_usExtIntrSesBtnWireless, .u.us = BP_EXT_INTR_1},
  {bp_usAntInUseWireless,      .u.us = BP_WLAN_ANT_MAIN},
  {bp_usWirelessFlags,         .u.us = 0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x0f},
  {bp_ulPhyId0,                .u.ul = 0x01},
  {bp_ulPhyId1,                .u.ul = 0x02},
  {bp_ulPhyId2,                .u.ul = 0x03},
  {bp_ulPhyId3,                .u.ul = ADVERTISE_ALL_MII | PHY_ADV_CFG_VALID | 0x04},  
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6302 | BP_AFE_FE_ANNEXB | BP_AFE_FE_REV_6302_REV_7_2_30},
  {bp_usGpioExtAFEReset,       .u.us = BP_GPIO_17_AL},
  {bp_usGpioCtInternetLed,     .u.us = BP_SERIAL_GPIO_8_AL},
  {bp_usGpioCtInternetFailLed, .u.us = BP_SERIAL_GPIO_2_AL},
  {bp_usGpioCtUSBLed,          .u.us = BP_SERIAL_GPIO_4_AL},
  {bp_ucpEthPhyMap,            .u.ucp= _963168M_1441N2_phymap},
  {bp_usEthIndex,              .u.us = 0x0},
  {bp_last}
};
// >> Jimmy.Wu : For VR-3031eu
// << Camille.Wu : for NL-3110
static bp_elem_t g_963168VB_1441N[] = {
  {bp_cpBoardId ,              .u.cp = "963168VB-1441N"},
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_SERIAL_LEDS |
                                       BP_OVERLAY_PHY)},
  {bp_usGpioLedAdsl,           .u.us = BP_SERIAL_GPIO_3_AL},
  {bp_usGpioLedSesWireless,    .u.us = BP_SERIAL_GPIO_7_AL},
//  {bp_usGpioLedWanData,        .u.us = BP_SERIAL_GPIO_8_AL},
//  {bp_usGpioLedWanError,       .u.us = BP_SERIAL_GPIO_2_AL},  
  {bp_usGpioSecLedAdsl,        .u.us = BP_GPIO_9_AL},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_GPIO_20_AL},
  {bp_usGpioLedBlStop,         .u.us = BP_GPIO_21_AL},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_usExtIntrSesBtnWireless, .u.us = BP_EXT_INTR_1},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x0f},
  {bp_ulPhyId0,                .u.ul = 0x01},
  {bp_ulPhyId1,                .u.ul = 0x02},
  {bp_ulPhyId2,                .u.ul = 0x03},
  {bp_ulPhyId3,                .u.ul = 0x04},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6302 | BP_AFE_FE_ANNEXA | BP_AFE_FE_REV_6302_REV_7_2_30},
  {bp_ulAfeId1,                .u.ul = BP_AFE_CHIP_6306 | BP_AFE_LD_6302 | BP_AFE_FE_ANNEXA | BP_AFE_FE_REV_6302_REV_7_2_21},
  {bp_usGpioExtAFEReset,       .u.us = BP_GPIO_17_AL},
  {bp_usGpioCtWirelessBtn,     .u.us = BP_GPIO_34_AL},
  {bp_usGpioCtInternetLed,		   .u.us = BP_SERIAL_GPIO_8_AL},
  {bp_usGpioCtInternetFailLed,    .u.us = BP_SERIAL_GPIO_2_AL},
  {bp_ucpEthPhyMap, 		   .u.ucp= _963168m_1341n1_phymap},
  {bp_last}
};
// >> Camille.Wu : for NL-3110
// << Camille.Wu : for NL-3111
static bp_elem_t g_963168MB_1461N[] = {
  {bp_cpBoardId ,              .u.cp = "963168MB-1461N"},
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_SERIAL_LEDS |
                                       BP_OVERLAY_PHY)},
  {bp_usGpioLedAdsl,           .u.us = BP_SERIAL_GPIO_3_AL},
  {bp_usGpioLedSesWireless,    .u.us = BP_SERIAL_GPIO_7_AL},
//  {bp_usGpioLedWanData,        .u.us = BP_SERIAL_GPIO_8_AL},
//  {bp_usGpioLedWanError,       .u.us = BP_SERIAL_GPIO_2_AL},  
  {bp_usGpioSecLedAdsl,        .u.us = BP_GPIO_9_AL},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_GPIO_20_AL},
  {bp_usGpioLedBlStop,         .u.us = BP_GPIO_21_AL},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_usExtIntrSesBtnWireless, .u.us = BP_EXT_INTR_1},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x0f},
  {bp_ulPhyId0,                .u.ul = 0x01},
  {bp_ulPhyId1,                .u.ul = 0x02},
  {bp_ulPhyId2,                .u.ul = 0x03},
  {bp_ulPhyId3,                .u.ul = 0x04},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6302 | BP_AFE_FE_ANNEXA | BP_AFE_FE_REV_6302_REV_7_2_30},
  {bp_ulAfeId1,                .u.ul = BP_AFE_CHIP_6306 | BP_AFE_LD_6302 | BP_AFE_FE_ANNEXA | BP_AFE_FE_REV_6302_REV_7_2_21},
  {bp_usGpioExtAFEReset,       .u.us = BP_GPIO_17_AL},
  {bp_usGpioCtWirelessBtn,     .u.us = BP_GPIO_34_AL},
  {bp_usGpioCtInternetLed,		   .u.us = BP_SERIAL_GPIO_8_AL},
  {bp_usGpioCtInternetFailLed,    .u.us = BP_SERIAL_GPIO_2_AL},
  {bp_ucpEthPhyMap, 		   .u.ucp= _963168m_1341n1_phymap},
  {bp_last}
};
// >> Camille.Wu : for NL-3111
// << Antony.Wu : For VR-3034
unsigned char _963168m_1341_phymap[BP_MAX_SWITCH_PORTS] = {0x01, 0x01, 0x00, 0x00, 0x00}; 
static bp_elem_t g_963168m_1341[] = {
  {bp_cpBoardId ,              .u.cp = "963168M-1341"},
  {bp_usGpioOverlay,           .u.ul =(BP_OVERLAY_PHY |
                                       BP_OVERLAY_SERIAL_LEDS)},
  {bp_usGpioLedAdsl,           .u.us = BP_SERIAL_GPIO_3_AL},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_GPIO_20_AL},
  {bp_usGpioLedBlStop,         .u.us = BP_GPIO_21_AL},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_0}, // reset button uses interrupt 0
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x01},
  {bp_ulPhyId0,                .u.ul = 0x01},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6302 | BP_AFE_FE_ANNEXA | BP_AFE_FE_REV_6302_REV_7_2_30},
  {bp_usGpioExtAFEReset,       .u.us = BP_GPIO_17_AL},
  {bp_usGpioCtInternetLed,     .u.us = BP_SERIAL_GPIO_8_AL},
  {bp_usGpioCtInternetFailLed, .u.us = BP_SERIAL_GPIO_2_AL},
  {bp_ucpEthPhyMap, 		   .u.ucp= _963168m_1341_phymap},
  {bp_last}
};
// >> Antony.Wu : For VR-3034
static bp_elem_t g_bcm963168mbv_30a[] = {
  {bp_cpBoardId ,              .u.cp = "963168MBV_30A"},
  {bp_ulDeviceOptions,         .u.ul = BP_DEVICE_OPTION_ENABLE_GMAC },
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_PHY |
                                       BP_OVERLAY_SERIAL_LEDS |
                                       BP_OVERLAY_USB_LED |
                                       BP_OVERLAY_USB_DEVICE)},
  {bp_usGpioLedAdsl,           .u.us = BP_SERIAL_GPIO_3_AL},
  {bp_usGpioSecLedAdsl,        .u.us = BP_GPIO_9_AL},
  {bp_usGpioLedSesWireless,    .u.us = BP_SERIAL_GPIO_7_AL},
  {bp_usGpioLedWanData,        .u.us = BP_SERIAL_GPIO_8_AL},
  {bp_usGpioLedWanError,       .u.us = BP_SERIAL_GPIO_2_AL},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_GPIO_20_AL},
  {bp_usGpioLedBlStop,         .u.us = BP_GPIO_21_AL},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_0}, 
  {bp_usExtIntrSesBtnWireless, .u.us = BP_EXT_INTR_1},  
  {bp_usAntInUseWireless,      .u.us = BP_WLAN_ANT_MAIN},
  {bp_usWirelessFlags,         .u.us = 0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x5f},
  {bp_ulPhyId0,                .u.ul = 0x01},
  {bp_ulPhyId1,                .u.ul = 0x02},
  {bp_ulPhyId2,                .u.ul = 0x03},
  {bp_ulPhyId3,                .u.ul = 0x04},
  {bp_ulPhyId4,                .u.ul = 0x18 | MAC_IFACE_VALID | MAC_IF_RGMII},
  {bp_ulPhyId6,                .u.ul = 0x19 | MAC_IFACE_VALID | MAC_IF_RGMII},
  {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
  {bp_ucDspAddress,            .u.uc = 0},
  {bp_usGpioVoip1Led,          .u.us = BP_SERIAL_GPIO_4_AL},
  {bp_usGpioVoip2Led,          .u.us = BP_SERIAL_GPIO_5_AL},
  {bp_usGpioPotsLed,           .u.us = BP_SERIAL_GPIO_6_AL},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_6306 | BP_AFE_LD_ISIL1556 | BP_AFE_FE_AVMODE_VDSL | BP_AFE_FE_REV_12_21 | BP_AFE_FE_ANNEXA },
  {bp_usGpioExtAFEReset,       .u.us = BP_GPIO_17_AL},
  {bp_usGpioAFELDRelay,      .u.us = BP_GPIO_39_AH},
  {bp_last}
};

static bp_elem_t g_bcm963168mbv17a302[] = {
  {bp_cpBoardId,               .u.cp = "963168MBV17A302"},
  {bp_usGpioSecLedAdsl,        .u.us = BP_GPIO_17_AL},
  {bp_usGpioIntAFELDMode,      .u.us = BP_PIN_DSL_CTRL_5},
  {bp_usGpioIntAFELDPwr,       .u.us = BP_PIN_DSL_CTRL_4},
  {bp_usGpioExtAFELDMode,      .u.us = BP_GPIO_13_AH},
  {bp_usGpioExtAFELDPwr,       .u.us = BP_GPIO_12_AH},
  {bp_usGpioExtAFEReset,       .u.us = BP_GPIO_11_AL},
  {bp_usGpioAFELDRelay,        .u.us = BP_GPIO_NONE},
  {bp_elemTemplate,            .u.bp_elemp = g_bcm963168mbv_17a},
  {bp_last}
};

static bp_elem_t g_bcm963168mbv30a302[] = {
  {bp_cpBoardId,               .u.cp = "963168MBV30A302"},
  {bp_usGpioSecLedAdsl,        .u.us = BP_GPIO_17_AL},
  {bp_usGpioIntAFELDMode,      .u.us = BP_PIN_DSL_CTRL_5},
  {bp_usGpioIntAFELDPwr,       .u.us = BP_PIN_DSL_CTRL_4},
  {bp_usGpioExtAFELDMode,      .u.us = BP_GPIO_13_AH},
  {bp_usGpioExtAFELDPwr,       .u.us = BP_GPIO_12_AH},
  {bp_usGpioExtAFEReset,       .u.us = BP_GPIO_11_AL},
  {bp_usGpioAFELDRelay,        .u.us = BP_GPIO_NONE},
  {bp_elemTemplate,            .u.bp_elemp = g_bcm963168mbv_30a},
  {bp_last}
};

static bp_elem_t g_bcm963268mbv[] = {
  {bp_cpBoardId,                 .u.cp = "963268MBV"},
  {bp_cpComment,               .u.cp = g_obsoleteStr},
  {bp_ulDeviceOptions,         .u.ul = BP_DEVICE_OPTION_ENABLE_GMAC },
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_PHY |
                                       BP_OVERLAY_SERIAL_LEDS |
                                       BP_OVERLAY_USB_DEVICE)},
  {bp_usGpioLedAdsl,           .u.us = BP_SERIAL_GPIO_3_AL},
  {bp_usGpioSecLedAdsl,        .u.us = BP_GPIO_9_AL},
  {bp_usGpioLedSesWireless,    .u.us = BP_SERIAL_GPIO_7_AL},
  {bp_usGpioLedWanData,        .u.us = BP_SERIAL_GPIO_8_AL},
  {bp_usGpioLedWanError,       .u.us = BP_SERIAL_GPIO_2_AL},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_GPIO_20_AL},
  {bp_usGpioLedBlStop,         .u.us = BP_GPIO_21_AL},
  {bp_usAntInUseWireless,      .u.us = BP_WLAN_ANT_MAIN},
  {bp_usWirelessFlags,         .u.us = 0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x5f},
  {bp_ulPhyId0,                .u.ul = 0x01},
  {bp_ulPhyId1,                .u.ul = 0x02},
  {bp_ulPhyId2,                .u.ul = 0x03},
  {bp_ulPhyId3,                .u.ul = 0x04},
  {bp_ulPhyId4,                .u.ul = 0x18 | MAC_IFACE_VALID | MAC_IF_RGMII},
  {bp_ulPhyId6,                .u.ul = 0x19 | MAC_IFACE_VALID | MAC_IF_RGMII},
  {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
  {bp_ucDspAddress,            .u.uc = 0},
  {bp_usGpioVoip1Led,          .u.us = BP_SERIAL_GPIO_4_AL},
  {bp_usGpioVoip2Led,          .u.us = BP_SERIAL_GPIO_5_AL},
  {bp_usGpioPotsLed,           .u.us = BP_SERIAL_GPIO_6_AL},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6302 | BP_AFE_FE_ANNEXA | BP_AFE_FE_REV_6302_REV_7_2_30},
  {bp_usGpioExtAFEReset,       .u.us = BP_GPIO_17_AL},
  {bp_usGpioAFELDRelay,      .u.us = BP_GPIO_39_AH},
  {bp_last}
};

static bp_elem_t g_bcm963168mbv3[] = {
  {bp_cpBoardId ,              .u.cp = "963168MBV3"},
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_PHY |
                                       BP_OVERLAY_SERIAL_LEDS |
                                       BP_OVERLAY_USB_LED |
                                       BP_OVERLAY_USB_DEVICE)},
  {bp_usGpioSecLedAdsl,        .u.us = BP_GPIO_17_AL},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6303 | BP_AFE_FE_ANNEXA | BP_AFE_FE_REV_6303_REV_12_3_30 }, 
  {bp_ulAfeId1,                .u.ul = BP_AFE_CHIP_6306 | BP_AFE_LD_6303 | BP_AFE_FE_ANNEXA | BP_AFE_FE_REV_6303_REV_12_3_20 }, 
  // LDMode is set to NONE in case the board we are inheriting from set them
  {bp_usGpioIntAFELDMode,      .u.us = BP_GPIO_NONE},  
  {bp_usGpioIntAFELDPwr,       .u.us = BP_GPIO_10_AH},
  // IntAFELDClk uses dedicated pin
  // IntAFELDData uses dedicated pin
  {bp_usGpioExtAFELDMode,      .u.us = BP_GPIO_NONE},
  {bp_usGpioExtAFELDPwr,       .u.us = BP_GPIO_9_AH},
  {bp_usGpioExtAFELDClk,       .u.us = BP_GPIO_8_AL},
  {bp_usGpioExtAFELDData,      .u.us = BP_GPIO_11_AH},
  {bp_usGpioExtAFEReset,       .u.us = BP_GPIO_13_AL},
  {bp_usGpioAFELDRelay,        .u.us = BP_GPIO_NONE},
  {bp_elemTemplate,            .u.bp_elemp = g_bcm963168mbv_30a},
  {bp_last}
};

#if 0
/* Uncomment "#define BP_GET_INT_AFE_DEFINED" in Boardparams.h when these bp_ids are in used:
* bp_usGpioIntAFELDPwr
* bp_usGpioIntAFELDMode
* bp_usGpioAFELDRelay
*/

static bp_elem_t g_bcm963268mbv6b[] = {
  {bp_cpBoardId,               .u.cp = "963168MBV6b"},
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_PHY |
                                       BP_OVERLAY_SERIAL_LEDS |
                                       BP_OVERLAY_USB_DEVICE)},
  {bp_usGpioLedAdsl,           .u.us = BP_SERIAL_GPIO_3_AL},
  {bp_usGpioLedSesWireless,    .u.us = BP_SERIAL_GPIO_7_AL},
  {bp_usGpioLedWanData,        .u.us = BP_SERIAL_GPIO_8_AL},
  {bp_usGpioLedWanError,       .u.us = BP_SERIAL_GPIO_2_AL},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_GPIO_20_AL},
  {bp_usGpioLedBlStop,         .u.us = BP_GPIO_21_AL},
  {bp_usAntInUseWireless,      .u.us = BP_WLAN_ANT_MAIN},
  {bp_usWirelessFlags,         .u.us = 0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x5f},
  {bp_ulPhyId0,                .u.ul = 0x01},
  {bp_ulPhyId1,                .u.ul = 0x02},
  {bp_ulPhyId2,                .u.ul = 0x03},
  {bp_ulPhyId3,                .u.ul = 0x04},
  {bp_ulPhyId4,                .u.ul = 0x18},
  {bp_ulPhyId6,                .u.ul = 0x19},
  {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
  {bp_ucDspAddress,            .u.uc = 0},
  {bp_usGpioVoip1Led,          .u.us = BP_SERIAL_GPIO_4_AL},
  {bp_usGpioVoip2Led,          .u.us = BP_SERIAL_GPIO_5_AL},
  {bp_usGpioPotsLed,           .u.us = BP_SERIAL_GPIO_6_AL},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_6306 | BP_AFE_LD_ISIL1556 | BP_AFE_FE_ANNEXA | BP_AFE_FE_REV_12_21},
  {bp_usGpioExtAFEReset,       .u.us = BP_GPIO_17_AL},
  {bp_usGpioExtAFELDPwr,       .u.us = BP_GPIO_13_AH},
  {bp_usGpioExtAFELDMode,      .u.us = BP_GPIO_12_AH},
  {bp_usGpioIntAFELDPwr,       .u.us = BP_GPIO_11_AH},
  {bp_usGpioIntAFELDMode,      .u.us = BP_GPIO_10_AH},
  {bp_usGpioAFELDRelay,      .u.us = BP_GPIO_39_AH},
  {bp_last}
};
#endif

static bp_elem_t g_bcm963168vx[] = {
  {bp_cpBoardId,               .u.cp = "963168VX"},
  {bp_ulDeviceOptions,         .u.ul = BP_DEVICE_OPTION_ENABLE_GMAC },
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_PHY |
                                       BP_OVERLAY_SERIAL_LEDS |
                                       BP_OVERLAY_USB_DEVICE |
                                       BP_OVERLAY_USB_LED |
                                       BP_OVERLAY_PCIE_CLKREQ)},
  {bp_usGpioLedAdsl,           .u.us = BP_SERIAL_GPIO_3_AL},
  {bp_usGpioLedSesWireless,    .u.us = BP_SERIAL_GPIO_7_AL},
  {bp_usGpioLedWanData,        .u.us = BP_SERIAL_GPIO_8_AL},
  {bp_usGpioLedWanError,       .u.us = BP_SERIAL_GPIO_2_AL},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_GPIO_20_AL},
  {bp_usGpioLedBlStop,         .u.us = BP_GPIO_21_AL},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_0},
  {bp_usExtIntrSesBtnWireless, .u.us = BP_EXT_INTR_1},
  {bp_usAntInUseWireless,      .u.us = BP_WLAN_ANT_MAIN},
  {bp_usWirelessFlags,         .u.us = 0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x0f},
  {bp_ulPhyId0,                .u.ul = 0x01},
  {bp_ulPhyId1,                .u.ul = 0x02},
  {bp_ulPhyId2,                .u.ul = 0x03},
  {bp_ulPhyId3,                .u.ul = 0x04},
  {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
  {bp_ucDspAddress,            .u.uc = 0},
  {bp_usGpioVoip1Led,          .u.us = BP_SERIAL_GPIO_4_AL},
  {bp_usGpioVoip2Led,          .u.us = BP_SERIAL_GPIO_5_AL},
  {bp_usGpioPotsLed,           .u.us = BP_SERIAL_GPIO_6_AL},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6302 | BP_AFE_FE_ANNEXA | BP_AFE_FE_REV_6302_REV1},
  {bp_usGpioExtAFEReset,       .u.us = BP_GPIO_17_AL},
  {bp_last}
};

static bp_elem_t g_bcm963168vx_p300[] = {
  {bp_cpBoardId,               .u.cp = "963168VX_P300"},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6302 | BP_AFE_FE_ANNEXA | BP_AFE_FE_REV_6302_REV_7_2_30},
  {bp_elemTemplate,            .u.bp_elemp = g_bcm963168vx}, 
  {bp_last}
};

static bp_elem_t g_bcm963168xf[] = {
  {bp_cpBoardId,               .u.cp = "963168XF"},
  {bp_ulDeviceOptions,         .u.ul = BP_DEVICE_OPTION_ENABLE_GMAC },
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_PHY |
                                       BP_OVERLAY_SERIAL_LEDS |
                                       BP_OVERLAY_USB_DEVICE |
                                       BP_OVERLAY_USB_LED |
                                       BP_OVERLAY_PCIE_CLKREQ)},
  {bp_usGpioLedAdsl,           .u.us = BP_SERIAL_GPIO_3_AL},
  {bp_usGpioLedSesWireless,    .u.us = BP_SERIAL_GPIO_7_AL},
  {bp_usGpioLedWanData,        .u.us = BP_SERIAL_GPIO_8_AL},
  {bp_usGpioLedWanError,       .u.us = BP_SERIAL_GPIO_2_AL},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_GPIO_20_AL},
  {bp_usGpioLedBlStop,         .u.us = BP_GPIO_21_AL},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_0},
  {bp_usExtIntrSesBtnWireless, .u.us = BP_EXT_INTR_1},
  {bp_usAntInUseWireless,      .u.us = BP_WLAN_ANT_MAIN},
  {bp_usWirelessFlags,         .u.us = 0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x1f},
  {bp_ulPhyId0,                .u.ul = 0x01},
  {bp_ulPhyId1,                .u.ul = 0x02},
  {bp_ulPhyId2,                .u.ul = 0x03},
  {bp_ulPhyId3,                .u.ul = 0x04},
  {bp_ulPhyId4,                .u.ul =  (PHY_LNK_CFG_VALID | FORCE_LINK_100FD | MAC_CONN_VALID | MAC_MAC_IF | MAC_IFACE_VALID | MAC_IF_RvMII) },  
  {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
  {bp_ucDspAddress,            .u.uc = 0},
  {bp_usGpioVoip1Led,          .u.us = BP_GPIO_14_AL},
  {bp_usGpioVoip2Led,          .u.us = BP_GPIO_15_AL},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6302 | BP_AFE_FE_ANNEXA | BP_AFE_FE_REV_6302_REV1},
  {bp_usGpioFemtoReset,        .u.us = BP_GPIO_8_AH},  
  {bp_last}
};

static bp_elem_t g_bcm963268sv2_extswitch[] = {
  {bp_cpBoardId,               .u.cp = "963268SV2_EXTSW"},
  {bp_ulDeviceOptions,         .u.ul = BP_DEVICE_OPTION_ENABLE_GMAC },
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_PHY |
                                       BP_OVERLAY_SERIAL_LEDS |
                                       BP_OVERLAY_USB_LED |
                                       BP_OVERLAY_USB_DEVICE |
                                       BP_OVERLAY_HS_SPI_SSB7_EXT_CS)},
  {bp_usGpioLedAdsl,           .u.us = BP_SERIAL_GPIO_3_AL},
  {bp_usGpioLedSesWireless,    .u.us = BP_SERIAL_GPIO_7_AL},
  {bp_usGpioLedWanData,        .u.us = BP_SERIAL_GPIO_8_AL},
  {bp_usGpioLedWanError,       .u.us = BP_SERIAL_GPIO_2_AL},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_GPIO_20_AL},
  {bp_usGpioLedBlStop,         .u.us = BP_GPIO_21_AL},
  {bp_usAntInUseWireless,      .u.us = BP_WLAN_ANT_MAIN},
  {bp_usWirelessFlags,         .u.us = 0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0xbf},
  {bp_ulPhyId0,                .u.ul = BP_PHY_ID_1},
  {bp_ulPhyId1,                .u.ul = BP_PHY_ID_2},
  {bp_ulPhyId2,                .u.ul = BP_PHY_ID_3},
  {bp_ulPhyId3,                .u.ul = BP_PHY_ID_4},
  {bp_ulPhyId4,                .u.ul = RGMII_DIRECT | EXTSW_CONNECTED},
  {bp_ulPhyId5,                .u.ul = 0x18 | MAC_IFACE_VALID | MAC_IF_RGMII},
  {bp_ulPhyId7,                .u.ul = 0x19 | MAC_IFACE_VALID | MAC_IF_RGMII},  
  {bp_ucPhyType1,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MDIO},
  {bp_ulPortMap,               .u.ul = 0x03},
  {bp_ulPhyId0,                .u.ul = BP_PHY_ID_0},
  {bp_ulPhyId1,                .u.ul = BP_PHY_ID_1},
  {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
  {bp_ucDspAddress,            .u.uc = 0},
  {bp_usGpioVoip1Led,          .u.us = BP_SERIAL_GPIO_4_AL},
  {bp_usGpioVoip2Led,          .u.us = BP_SERIAL_GPIO_5_AL},
  {bp_usGpioPotsLed,           .u.us = BP_SERIAL_GPIO_6_AL},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6302 | BP_AFE_FE_ANNEXA | BP_AFE_FE_REV_6302_REV1},
  {bp_usGpioSpiSlaveReset,     .u.us = BP_GPIO_22_AH},
  {bp_usSpiSlaveBusNum,        .u.us = HS_SPI_BUS_NUM},
  {bp_usSpiSlaveSelectNum,     .u.us = 7},
  {bp_usSpiSlaveMode,          .u.us = SPI_MODE_3},
  {bp_ulSpiSlaveCtrlState,     .u.ul = SPI_CONTROLLER_STATE_GATE_CLK_SSOFF},
  {bp_ulSpiSlaveMaxFreq,       .u.ul = 781000},
  {bp_usSpiSlaveProtoRev,      .u.us = 0},   
  {bp_last}
};

static bp_elem_t g_bcm963268bu[] = {
  {bp_cpBoardId,               .u.cp = "963268BU"},
  {bp_ulDeviceOptions,         .u.ul = BP_DEVICE_OPTION_ENABLE_GMAC },
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_SERIAL_LEDS |
                                       BP_OVERLAY_PHY |
                                       BP_OVERLAY_INET_LED |
                                       BP_OVERLAY_GPHY_LED_0 |
                                       BP_OVERLAY_USB_LED |
                                       BP_OVERLAY_USB_DEVICE)},
  {bp_usGpioLedAdsl,           .u.us = BP_SERIAL_GPIO_3_AL},
  {bp_usGpioLedSesWireless,    .u.us = BP_SERIAL_GPIO_7_AL},
  {bp_usGpioLedWanData,        .u.us = BP_GPIO_8_AL},
  {bp_usGpioLedWanError,       .u.us = BP_SERIAL_GPIO_2_AL},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_GPIO_20_AL},
  {bp_usGpioLedBlStop,         .u.us = BP_GPIO_21_AL},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_0},
  {bp_usExtIntrSesBtnWireless, .u.us = BP_EXT_INTR_1},
  {bp_usAntInUseWireless,      .u.us = BP_WLAN_ANT_MAIN},
  {bp_usWirelessFlags,         .u.us = 0},
  // {bp_usEphyBaseAddress,       .u.us = 0x10},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0xFC},
  {bp_ulPhyId2,                .u.ul = BP_PHY_ID_3 | PHY_INTERNAL | PHY_INTEGRATED_VALID },
  {bp_ulPhyId3,                .u.ul = BP_PHY_ID_4 },
  {bp_ulPhyId4,                .u.ul = BP_PHY_ID_0 | MAC_IFACE_VALID | MAC_IF_RGMII | PHY_INTEGRATED_VALID | PHY_EXTERNAL},
  {bp_ulPhyId5,                .u.ul = BP_PHY_ID_1 | MAC_IFACE_VALID | MAC_IF_RGMII | PHY_INTEGRATED_VALID | PHY_EXTERNAL },
  {bp_ulPhyId6,                .u.ul = BP_PHY_ID_24 | MAC_IFACE_VALID | MAC_IF_RGMII},
  {bp_ulPhyId7,                .u.ul = BP_PHY_ID_25 | MAC_IFACE_VALID | MAC_IF_RGMII},
  {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
  {bp_ucDspAddress,            .u.uc = 0},
  {bp_usGpioVoip1Led,          .u.us = BP_SERIAL_GPIO_4_AL},
  {bp_usGpioVoip2Led,          .u.us = BP_SERIAL_GPIO_5_AL},
  {bp_usGpioPotsLed,           .u.us = BP_SERIAL_GPIO_6_AL},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6302 | BP_AFE_FE_ANNEXA | BP_AFE_FE_REV_6302_REV1},
  {bp_usGpioIntAFELDMode,      .u.us = BP_GPIO_10_AH},
  {bp_usGpioIntAFELDPwr,       .u.us = BP_GPIO_11_AH},
  {bp_last}
};

static bp_elem_t g_bcm963268bu_p300[] = {
  {bp_cpBoardId,               .u.cp = "963268BU_P300"},
  {bp_ulDeviceOptions,         .u.ul = BP_DEVICE_OPTION_ENABLE_GMAC },
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_SERIAL_LEDS |
                                       BP_OVERLAY_PHY |
                                       BP_OVERLAY_INET_LED |
                                       BP_OVERLAY_EPHY_LED_0 |
                                       BP_OVERLAY_GPHY_LED_0 |
                                       BP_OVERLAY_USB_LED |
                                       BP_OVERLAY_USB_DEVICE)},
  {bp_usGpioLedAdsl,           .u.us = BP_SERIAL_GPIO_3_AL},
  {bp_usGpioLedSesWireless,    .u.us = BP_SERIAL_GPIO_7_AL},
  {bp_usGpioLedWanData,        .u.us = BP_GPIO_8_AL},
  {bp_usGpioLedWanError,       .u.us = BP_SERIAL_GPIO_2_AL},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_GPIO_20_AL},
  {bp_usGpioLedBlStop,         .u.us = BP_GPIO_21_AL},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_0},
  {bp_usExtIntrSesBtnWireless, .u.us = BP_EXT_INTR_1},
  {bp_usAntInUseWireless,      .u.us = BP_WLAN_ANT_MAIN},
  {bp_usWirelessFlags,         .u.us = 0},
  {bp_usEphyBaseAddress,       .u.us = 0x10},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0xF9},
  {bp_ulPhyId0,                .u.ul = BP_PHY_ID_17 | PHY_INTERNAL | PHY_INTEGRATED_VALID },
  {bp_ulPhyId3,                .u.ul = BP_PHY_ID_4 | PHY_INTERNAL | PHY_INTEGRATED_VALID },
  {bp_ulPhyId4,                .u.ul = BP_PHY_ID_0 | MAC_IFACE_VALID | MAC_IF_RGMII | PHY_INTEGRATED_VALID | PHY_EXTERNAL},
  {bp_ulPhyId5,                .u.ul = BP_PHY_ID_1 | MAC_IFACE_VALID | MAC_IF_RGMII | PHY_INTEGRATED_VALID | PHY_EXTERNAL },
  {bp_ulPhyId6,                .u.ul = BP_PHY_ID_24 | MAC_IFACE_VALID | MAC_IF_RGMII},
  {bp_ulPhyId7,                .u.ul = BP_PHY_ID_25 | MAC_IFACE_VALID | MAC_IF_RGMII},
  {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
  {bp_ucDspAddress,            .u.uc = 0},
  {bp_usGpioVoip1Led,          .u.us = BP_SERIAL_GPIO_4_AL},
  {bp_usGpioVoip2Led,          .u.us = BP_SERIAL_GPIO_5_AL},
  {bp_usGpioPotsLed,           .u.us = BP_SERIAL_GPIO_6_AL},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6302 | BP_AFE_FE_ANNEXA | BP_AFE_FE_REV_6302_REV1},
  {bp_usGpioIntAFELDMode,      .u.us = BP_GPIO_10_AH},
  {bp_usGpioIntAFELDPwr,       .u.us = BP_GPIO_11_AH},
  {bp_last}
};

static bp_elem_t g_bcm963168xh[] = {
  {bp_cpBoardId,               .u.cp = "963168XH"},
  {bp_ulDeviceOptions,         .u.ul = BP_DEVICE_OPTION_ENABLE_GMAC },
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_SERIAL_LEDS |
                                       BP_OVERLAY_USB_DEVICE|
                                       BP_OVERLAY_USB_LED|
                                       BP_OVERLAY_PCIE_CLKREQ |
                                       BP_OVERLAY_HS_SPI_SSB5_EXT_CS)},
  {bp_usGpioLedAdsl,           .u.us = BP_GPIO_13_AH},
  {bp_usGpioLedSesWireless,    .u.us = BP_SERIAL_GPIO_7_AL},
  {bp_usGpioLedWanData,        .u.us = BP_GPIO_8_AL},
  {bp_usGpioLedWanError,       .u.us = BP_SERIAL_GPIO_2_AL},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_GPIO_10_AL},
  {bp_usGpioLedBlStop,         .u.us = BP_SERIAL_GPIO_3_AL},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_0},
  {bp_usExtIntrSesBtnWireless, .u.us = BP_EXT_INTR_1},  
  {bp_usAntInUseWireless,      .u.us = BP_WLAN_ANT_MAIN},
  {bp_usWirelessFlags,         .u.us = 0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x58},
  {bp_ulPhyId3,                .u.ul = BP_PHY_ID_4},
  {bp_ulPhyId4,                .u.ul = RGMII_DIRECT | EXTSW_CONNECTED},
  {bp_ulPhyId6,                .u.ul = BP_PHY_ID_25 | MAC_IFACE_VALID | MAC_IF_RGMII},
  {bp_ucPhyType1,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_HS_SPI_SSB_5},// Remember to make MDIO HW changes(install resistors R540, R541 and R553) BP_ENET_CONFIG_HS_SPI_SSB_5},
  {bp_ulPortMap,               .u.ul = 0x0f},
  {bp_ulPhyId0,                .u.ul = BP_PHY_ID_0},
  {bp_ulPhyId1,                .u.ul = BP_PHY_ID_1},
  {bp_ulPhyId2,                .u.ul = BP_PHY_ID_2},
  {bp_ulPhyId3,                .u.ul = BP_PHY_ID_3},
  {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
  {bp_ucDspAddress,            .u.uc = 0},
  {bp_usGpioVoip1Led,          .u.us = BP_SERIAL_GPIO_4_AL},
  {bp_usGpioVoip2Led,          .u.us = BP_SERIAL_GPIO_5_AL},
  {bp_usGpioPotsLed,           .u.us = BP_SERIAL_GPIO_6_AL},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_6306 | BP_AFE_LD_ISIL1556 | BP_AFE_FE_AVMODE_VDSL | BP_AFE_FE_REV_12_21 | BP_AFE_FE_ANNEXA },
  {bp_usGpioExtAFEReset,       .u.us = BP_GPIO_11_AL},  
  {bp_last}
};

static bp_elem_t g_bcm963168xh5[] = {
    {bp_cpBoardId,               .u.cp = "963168XH5"},
    {bp_ulDeviceOptions,         .u.ul = BP_DEVICE_OPTION_ENABLE_GMAC },
    {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_SERIAL_LEDS |
                                      BP_OVERLAY_USB_DEVICE|
                                      BP_OVERLAY_USB_LED|
                                      BP_OVERLAY_PCIE_CLKREQ |
                                      BP_OVERLAY_HS_SPI_SSB5_EXT_CS)},
    {bp_usGpioLedAdsl,           .u.us = BP_GPIO_13_AH},
    {bp_usGpioLedSesWireless,    .u.us = BP_SERIAL_GPIO_7_AL},
    {bp_usGpioLedWanData,        .u.us = BP_GPIO_8_AL},
    {bp_usGpioLedWanError,       .u.us = BP_SERIAL_GPIO_2_AL},
    {bp_usGpioLedBlPowerOn,      .u.us = BP_GPIO_10_AL},
    {bp_usGpioLedBlStop,         .u.us = BP_SERIAL_GPIO_3_AL},
    {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_0},
    {bp_usExtIntrSesBtnWireless, .u.us = BP_EXT_INTR_1},  
    {bp_usAntInUseWireless,      .u.us = BP_WLAN_ANT_MAIN},
    {bp_usWirelessFlags,         .u.us = 0},
    {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
    {bp_ucPhyAddress,            .u.uc = 0x0},
    {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
    {bp_ulPortMap,               .u.ul = 0x58},
    {bp_ulPhyId3,                .u.ul = BP_PHY_ID_4},
    {bp_ulPhyId4,                .u.ul = RGMII_DIRECT | EXTSW_CONNECTED},
    {bp_ulPhyId6,                .u.ul = BP_PHY_ID_25 | MAC_IFACE_VALID | MAC_IF_RGMII},
    {bp_ucPhyType1,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
    {bp_ucPhyAddress,            .u.uc = 0x0},
    {bp_usConfigType,            .u.us = BP_ENET_CONFIG_HS_SPI_SSB_5},// Remember to make MDIO HW changes(install resistors R540, R541 and R553) BP_ENET_CONFIG_HS_SPI_SSB_5},
    {bp_ulPortMap,               .u.ul = 0x0f},
    {bp_ulPhyId0,                .u.ul = BP_PHY_ID_0},
    {bp_ulPhyId1,                .u.ul = BP_PHY_ID_1},
    {bp_ulPhyId2,                .u.ul = BP_PHY_ID_2},
    {bp_ulPhyId3,                .u.ul = BP_PHY_ID_3},
    {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
    {bp_ucDspAddress,            .u.uc = 0},
    {bp_usGpioVoip1Led,          .u.us = BP_SERIAL_GPIO_4_AL},
    {bp_usGpioVoip2Led,          .u.us = BP_SERIAL_GPIO_5_AL},
    {bp_usGpioPotsLed,           .u.us = BP_SERIAL_GPIO_6_AL},
    {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_6306 | BP_AFE_LD_ISIL1556 | BP_AFE_FE_AVMODE_VDSL | BP_AFE_FE_REV_12_21 | BP_AFE_FE_ANNEXA },
    {bp_usGpioExtAFEReset,       .u.us = BP_GPIO_11_AL},  
    {bp_last}
};

  static bp_elem_t g_bcm963168xm[] = {
    {bp_cpBoardId,               .u.cp = "963168XM"},
    {bp_ulDeviceOptions,         .u.ul = BP_DEVICE_OPTION_ENABLE_GMAC },
    {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_SERIAL_LEDS |
                                       BP_OVERLAY_USB_DEVICE|
                                       BP_OVERLAY_PCIE_CLKREQ |
                                       BP_OVERLAY_HS_SPI_SSB5_EXT_CS)},
  {bp_usGpioLedAdsl,           .u.us = BP_GPIO_13_AH},
  {bp_usGpioLedSesWireless,    .u.us = BP_SERIAL_GPIO_7_AL},
  {bp_usGpioLedWanData,        .u.us = BP_GPIO_8_AL},
  {bp_usGpioLedWanError,       .u.us = BP_SERIAL_GPIO_2_AL},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_GPIO_10_AL},
  {bp_usGpioLedBlStop,         .u.us = BP_SERIAL_GPIO_3_AL},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_0},
  {bp_usExtIntrSesBtnWireless, .u.us = BP_EXT_INTR_1},  
  {bp_usAntInUseWireless,      .u.us = BP_WLAN_ANT_MAIN},
  {bp_usWirelessFlags,         .u.us = 0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x58},
  {bp_ulPhyId3,                .u.ul = BP_PHY_ID_4},
  {bp_ulPhyId4,                .u.ul = RGMII_DIRECT | EXTSW_CONNECTED},
  {bp_ulPhyId6,                .u.ul = BP_PHY_ID_25},
  {bp_ucPhyType1,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_HS_SPI_SSB_5},// Remember to make MDIO HW changes(install resistors R540, R541 and R553) BP_ENET_CONFIG_HS_SPI_SSB_5},
  {bp_ulPortMap,               .u.ul = 0x0f},
  {bp_ulPhyId0,                .u.ul = BP_PHY_ID_0},
  {bp_ulPhyId1,                .u.ul = BP_PHY_ID_1},
  {bp_ulPhyId2,                .u.ul = BP_PHY_ID_2},
  {bp_ulPhyId3,                .u.ul = BP_PHY_ID_3},
  {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
  {bp_ucDspAddress,            .u.uc = 0},
  {bp_usGpioVoip1Led,          .u.us = BP_SERIAL_GPIO_4_AL},
  {bp_usGpioVoip2Led,          .u.us = BP_SERIAL_GPIO_5_AL},
  {bp_usGpioPotsLed,           .u.us = BP_SERIAL_GPIO_6_AL},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_6306 | BP_AFE_LD_ISIL1556 | BP_AFE_FE_AVMODE_VDSL | BP_AFE_FE_REV_12_21 | BP_AFE_FE_ANNEXA },
  {bp_usGpioExtAFEReset,       .u.us = BP_GPIO_11_AL},  
  {bp_last}
};


  static bp_elem_t g_bcm963168mp[] = {
  {bp_cpBoardId,               .u.cp = "963168MP"},
  {bp_ulDeviceOptions,         .u.ul = BP_DEVICE_OPTION_ENABLE_GMAC },
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_PHY |
                                       BP_OVERLAY_SERIAL_LEDS)},
  {bp_usGpioLedAdsl,           .u.us = BP_SERIAL_GPIO_3_AL},
  {bp_usGpioLedSesWireless,    .u.us = BP_SERIAL_GPIO_7_AL},
  {bp_usGpioLedWanData,        .u.us = BP_SERIAL_GPIO_8_AL},
  {bp_usGpioLedWanError,       .u.us = BP_SERIAL_GPIO_2_AL},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_GPIO_20_AL},
  {bp_usGpioLedBlStop,         .u.us = BP_GPIO_21_AL},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_0},
  {bp_usExtIntrSesBtnWireless, .u.us = BP_EXT_INTR_1},  
  {bp_usAntInUseWireless,      .u.us = BP_WLAN_ANT_MAIN},
  {bp_usWirelessFlags,         .u.us = 0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x1F},
  {bp_ulPhyId0,                .u.ul = 0x01},
  {bp_ulPhyId1,                .u.ul = 0x02},
  {bp_ulPhyId2,                .u.ul = 0x03},
  {bp_ulPhyId3,                .u.ul = 0x04},
  {bp_ulPhyId4,                .u.ul = MII_DIRECT},
  {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
  {bp_ucDspAddress,            .u.uc = 0},
  {bp_usGpioVoip1Led,          .u.us = BP_SERIAL_GPIO_4_AL},
  {bp_usGpioVoip2Led,          .u.us = BP_SERIAL_GPIO_5_AL},
  {bp_usGpioPotsLed,           .u.us = BP_SERIAL_GPIO_6_AL},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6302 | BP_AFE_FE_ANNEXA | BP_AFE_FE_REV_6302_REV_7_2_30},
  {bp_last}
};

  static bp_elem_t g_bcm963268v30a[] = {
  {bp_cpBoardId,               .u.cp = "963268V30A"},
  {bp_ulDeviceOptions,         .u.ul = BP_DEVICE_OPTION_ENABLE_GMAC },
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_PCIE_CLKREQ |
                                       BP_OVERLAY_PHY |
                                       BP_OVERLAY_GPHY_LED_0 |
                                       BP_OVERLAY_SERIAL_LEDS )},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_0},
  {bp_usExtIntrSesBtnWireless, .u.us = BP_EXT_INTR_1},
  {bp_usGpioLedAdsl,           .u.us = BP_SERIAL_GPIO_3_AL},
  {bp_usGpioLedSesWireless,    .u.us = BP_SERIAL_GPIO_7_AL},
  {bp_usGpioLedWanData,        .u.us = BP_GPIO_8_AL},
  {bp_usGpioLedWanError,       .u.us = BP_SERIAL_GPIO_2_AL},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_GPIO_20_AL},
  {bp_usGpioLedBlStop,         .u.us = BP_GPIO_21_AL},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_0},
  {bp_usExtIntrSesBtnWireless, .u.us = BP_EXT_INTR_1},
  {bp_usAntInUseWireless,      .u.us = BP_WLAN_ANT_MAIN}, // FIXME
  {bp_usWirelessFlags,         .u.us = 0}, // FIXME
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0xD8},
  {bp_ulPhyId3,                .u.ul = 0x04},
  {bp_ulPhyId4,                .u.ul = 0x00 | MAC_IFACE_VALID | MAC_IF_RGMII | PHY_INTEGRATED_VALID | PHY_EXTERNAL},
  {bp_ulPhyId6,                .u.ul = 0x18 | MAC_IFACE_VALID | MAC_IF_RGMII},
  {bp_ulPhyId7,                .u.ul = 0x19 | MAC_IFACE_VALID | MAC_IF_RGMII},
  {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
  {bp_ucDspAddress,            .u.uc = 0},
  {bp_usGpioVoip1Led,          .u.us = BP_SERIAL_GPIO_4_AL},
  {bp_usGpioVoip2Led,          .u.us = BP_SERIAL_GPIO_5_AL},
  {bp_usGpioPotsLed,           .u.us = BP_SERIAL_GPIO_6_AL},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_6306 | BP_AFE_LD_6302 | BP_AFE_FE_ANNEXA | BP_AFE_6302_6306_REV_A_12_40},
  {bp_usGpioExtAFEReset,       .u.us = BP_GPIO_9_AL},  
  {bp_usGpioExtAFELDMode,      .u.us = BP_GPIO_10_AH},
  {bp_usGpioExtAFELDPwr,       .u.us = BP_GPIO_11_AH},
  {bp_last}
};

  static bp_elem_t g_bcm963168media[] = {
  {bp_cpBoardId,               .u.cp = "963168MEDIA"},
  {bp_ulDeviceOptions,         .u.ul = BP_DEVICE_OPTION_ENABLE_GMAC },
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_PCIE_CLKREQ |
                                       BP_OVERLAY_PHY |                                       
                                       BP_OVERLAY_SERIAL_LEDS )},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_0},
  {bp_usExtIntrSesBtnWireless, .u.us = BP_EXT_INTR_1},
  {bp_usGpioLedAdsl,           .u.us = BP_SERIAL_GPIO_3_AL},
  {bp_usGpioLedSesWireless,    .u.us = BP_SERIAL_GPIO_7_AL},
  {bp_usGpioLedWanData,        .u.us = BP_GPIO_8_AL},
  {bp_usGpioLedWanError,       .u.us = BP_SERIAL_GPIO_2_AL},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_SERIAL_GPIO_1_AL},
  {bp_usGpioLedBlStop,         .u.us = BP_SERIAL_GPIO_6_AL},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_0},
  {bp_usExtIntrSesBtnWireless, .u.us = BP_EXT_INTR_1},
  {bp_usAntInUseWireless,      .u.us = BP_WLAN_ANT_MAIN}, // FIXME
  {bp_usWirelessFlags,         .u.us = 0}, // FIXME
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x5F},
  {bp_ulPhyId0,                .u.ul = 0x01},
  {bp_ulPhyId1,                .u.ul = 0x02},
  {bp_ulPhyId2,                .u.ul = 0x03},
  {bp_ulPhyId3,                .u.ul = 0x04},
  {bp_ulPhyId4,                .u.ul = 0x18 | MAC_IFACE_VALID | MAC_IF_RGMII | PHY_INTEGRATED_VALID | PHY_EXTERNAL},
  {bp_ulPhyId6,                .u.ul = RGMII_DIRECT},
  {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
  {bp_ucDspAddress,            .u.uc = 0},
  {bp_usGpioVoip1Led,          .u.us = BP_SERIAL_GPIO_4_AL},
  {bp_usGpioVoip2Led,          .u.us = BP_SERIAL_GPIO_5_AL}, 
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6302 | BP_AFE_FE_ANNEXA | BP_AFE_FE_REV_6302_REV_7_2_30},
  {bp_usGpioExtAFELDMode,      .u.us = BP_GPIO_10_AH},
  {bp_usGpioExtAFELDPwr,       .u.us = BP_GPIO_11_AH},
  {bp_usGpioUart2Sdin,         .u.us = BP_GPIO_12_AH},
  {bp_usGpioUart2Sdout,        .u.us = BP_GPIO_13_AH},        
  {bp_last}
};


static bp_elem_t g_bcm963268sv2[] = {
  {bp_cpBoardId,               .u.cp = "963268SV2"},
  {bp_ulDeviceOptions,         .u.ul = BP_DEVICE_OPTION_ENABLE_GMAC },
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_PHY |
                                       BP_OVERLAY_SERIAL_LEDS |
                                       BP_OVERLAY_USB_LED |
                                       BP_OVERLAY_USB_DEVICE)},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_GPIO_20_AL},
  {bp_usGpioLedBlStop,         .u.us = BP_GPIO_21_AL},
  {bp_usAntInUseWireless,      .u.us = BP_WLAN_ANT_MAIN},
  {bp_usWirelessFlags,         .u.us = 0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x0f},
  {bp_ulPhyId0,                .u.ul = BP_PHY_ID_1},
  {bp_ulPhyId1,                .u.ul = BP_PHY_ID_2},
  {bp_ulPhyId2,                .u.ul = BP_PHY_ID_3},
  {bp_ulPhyId3,                .u.ul = BP_PHY_ID_4},
  {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
  {bp_ucDspAddress,            .u.uc = 0},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6302 | BP_AFE_FE_ANNEXA | BP_AFE_FE_REV_6302_REV1},
  {bp_usGpioExtAFEReset,       .u.us = BP_GPIO_17_AL},
  {bp_last}
};

static bp_elem_t g_bcm963168xfg3[] = {
  {bp_cpBoardId,               .u.cp = "963168XFG3"},
  {bp_ulDeviceOptions,         .u.ul = BP_DEVICE_OPTION_ENABLE_GMAC },
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_SERIAL_LEDS |
                                       BP_OVERLAY_USB_DEVICE  |
                                       BP_OVERLAY_PHY         |
                                       BP_OVERLAY_PCIE_CLKREQ)},
  {bp_usGpioLedAdsl,           .u.us = BP_SERIAL_GPIO_3_AL},
  {bp_usGpioLedSesWireless,    .u.us = BP_SERIAL_GPIO_7_AL},
  {bp_usGpioLedWanData,        .u.us = BP_SERIAL_GPIO_8_AL},
  {bp_usGpioLedWanError,       .u.us = BP_SERIAL_GPIO_2_AL},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_GPIO_20_AL},
  {bp_usGpioLedBlStop,         .u.us = BP_GPIO_21_AL},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_0},
  {bp_usExtIntrSesBtnWireless, .u.us = BP_EXT_INTR_1},  
  {bp_usAntInUseWireless,      .u.us = BP_WLAN_ANT_MAIN},
  {bp_usWirelessFlags,         .u.us = 0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x1F},
  {bp_ulPhyId0,                .u.ul = BP_PHY_ID_1}, 
  {bp_ulPhyId1,                .u.ul = BP_PHY_ID_2},  
  {bp_ulPhyId2,                .u.ul = BP_PHY_ID_3},         
  {bp_ulPhyId3,                .u.ul = BP_PHY_ID_4},
  {bp_ulPhyId4,                .u.ul = MII_DIRECT},  
  {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
  {bp_ucDspAddress,            .u.uc = 0},
  {bp_usGpioVoip1Led,          .u.us = BP_SERIAL_GPIO_4_AL},
  {bp_usGpioVoip2Led,          .u.us = BP_SERIAL_GPIO_5_AL},
  {bp_usGpioExtAFELDMode,      .u.us = BP_GPIO_10_AH},
  {bp_usGpioExtAFELDPwr,       .u.us = BP_GPIO_11_AH},  
  {bp_usGpioFemtoReset,        .u.us = BP_GPIO_8_AH},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6302 | BP_AFE_FE_ANNEXA | BP_AFE_FE_AVMODE_ADSL | BP_AFE_FE_REV_6302_REV_7_2_30}, 
  {bp_last}
};

// << kewei lai for add new boardid 963169R-1861AC to WAP-5892u 
unsigned char _963169r1861ac_phymap[BP_MAX_SWITCH_PORTS] = {0x0c, 0x01, 0x02, 0x03, 0x04}; 

static bp_elem_t g_bcm963169r1861ac[] = {
  {bp_cpBoardId,               .u.cp = "963169R-1861AC"},
  {bp_ulDeviceOptions,         .u.ul = BP_DEVICE_OPTION_ENABLE_GMAC },
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_PCIE_CLKREQ)},
  {bp_usGpioLedSesWireless,    .u.us = BP_GPIO_1_AL},
  {bp_usGpioCtInternetLed,     .u.us = BP_GPIO_8_AL},
  {bp_usGpioCtUsbSingleLed1,	   	   .u.us = BP_GPIO_9_AL},
  {bp_usGpioCtInternetFailLed, .u.us = BP_GPIO_15_AL},
  {bp_usGpioCtUsbSingleLed2,	   	   .u.us = BP_GPIO_16_AL},
  {bp_usGpioCtWifiBtnAll,        .u.us = BP_GPIO_18_AL},
  {bp_usGpioCtLedSesWireless2,        .u.us = BP_GPIO_22_AL},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_GPIO_20_AL},
  {bp_usGpioLedBlStop,         .u.us = BP_GPIO_21_AL},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_0},
  {bp_usExtIntrCtWifiBtn,    .u.us = BP_EXT_INTR_1},
  {bp_usExtIntrSesBtnWireless, .u.us = BP_EXT_INTR_2},
  {bp_usExtIntrCtWifiBtn2,    .u.us = BP_EXT_INTR_3},
  {bp_usAntInUseWireless,      .u.us = BP_WLAN_ANT_MAIN},
  {bp_usWirelessFlags,         .u.us = 0},
  {bp_usGphyBaseAddress,       .u.us = 0x08}, // 5bit phy address for Gphy is b'01xxx now
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x18},
  {bp_ulPhyId3, 			   .u.ul = BP_PHY_ID_12}, // Gphy address is changed form 4 to 12
  {bp_ulPhyId4,                .u.ul = RGMII_DIRECT | EXTSW_CONNECTED},
  {bp_ucPhyType1,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MDIO},
  {bp_ulPortMap,               .u.ul = 0x1e},
  {bp_ulPhyId1,                .u.ul = BP_PHY_ID_1 | CONNECTED_TO_EXTERN_SW},
  {bp_ulPhyId2,                .u.ul = BP_PHY_ID_2 | CONNECTED_TO_EXTERN_SW},
  {bp_ulPhyId3,                .u.ul = BP_PHY_ID_3 | CONNECTED_TO_EXTERN_SW},
  {bp_ulPhyId4,                .u.ul = BP_PHY_ID_4 | CONNECTED_TO_EXTERN_SW},
  {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
  {bp_ucDspAddress,            .u.uc = 0},
  {bp_usCtWirelessBand1,         .u.us = 2},
  {bp_usCtWirelessBand2,         .u.us = 1},
  {bp_ucpEthPhyMap, 		   .u.ucp= _963169r1861ac_phymap},
  {bp_last}
};

// >> kewei lai for add new boardid 963169R-1861AC to WAP-5892u 


static bp_elem_t * g_BoardParms[] = {
g_963168m_1341n1, // for VR-3031u
g_963168M_1441N2, // for VR-3031eu
g_963168VB_1441N, // for NL-3110u
g_963168MB_1461N, // for NL-3111u
g_963168M_1441N3, // for VR-3036u
g_963168m_1341, // for VR-3034
// << kewei lai for add new boardid 963169R-1861AC to WAP-5892u 
g_bcm963169r1861ac,
// >> kewei lai for add new boardid 963169R-1861AC to WAP-5892u 
g_bcm963268sv1, g_bcm963268mbv, g_bcm963168vx, g_bcm963168vx_p300, g_bcm963268bu, g_bcm963268bu_p300, g_bcm963268sv2_extswitch, g_bcm963168mbv_17a, g_bcm963168mbv_30a, g_bcm963168xh, g_bcm963168xh5, g_bcm963168mp, g_bcm963268v30a, g_bcm963168media, g_bcm963268sv2, g_bcm963168xfg3, g_bcm963168xf, g_bcm963168xm, g_bcm963168mbv3, g_bcm963168mbv17a302, g_bcm963168mbv30a302, 0};

#endif

#if defined(_BCM96828_) || defined(CONFIG_BCM96828)

static bp_elem_t g_bcm96828epon[] = {
  {bp_cpBoardId,               .u.cp = "96828MBV"},
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_PHY |
                                       BP_OVERLAY_SERIAL_LEDS |
                                       BP_OVERLAY_USB_DEVICE)},
  {bp_usGpioLedAdsl,           .u.us = BP_SERIAL_GPIO_3_AL},
  {bp_usGpioLedSesWireless,    .u.us = BP_SERIAL_GPIO_7_AL},
  {bp_usGpioLedWanData,        .u.us = BP_SERIAL_GPIO_8_AL},
  {bp_usGpioLedWanError,       .u.us = BP_SERIAL_GPIO_2_AL},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_GPIO_20_AL},
  {bp_usGpioLedBlStop,         .u.us = BP_GPIO_21_AL},
  {bp_usAntInUseWireless,      .u.us = BP_WLAN_ANT_MAIN},
  {bp_usWirelessFlags,         .u.us = 0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x5f},
  {bp_ulPhyId0,                .u.ul = 0x01},
  {bp_ulPhyId1,                .u.ul = 0x02},
  {bp_ulPhyId2,                .u.ul = 0x03},
  {bp_ulPhyId3,                .u.ul = 0x04},
  {bp_ulPhyId4,                .u.ul = 0x18},
  {bp_ulPhyId6,                .u.ul = 0x19},
  {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
  {bp_ucDspAddress,            .u.uc = 0},
  {bp_usGpioVoip1Led,          .u.us = BP_SERIAL_GPIO_4_AL},
  {bp_usGpioVoip2Led,          .u.us = BP_SERIAL_GPIO_5_AL},
  {bp_usGpioPotsLed,           .u.us = BP_SERIAL_GPIO_6_AL},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6302 | BP_AFE_FE_ANNEXA | BP_AFE_FE_REV_6302_REV_7_2_30},
  {bp_usGpioExtAFEReset,       .u.us = BP_GPIO_17_AL},
  {bp_last}
};

static bp_elem_t * g_BoardParms[] = {g_bcm96828epon, 0};

#endif

#if defined(_BCM96318_) || defined(CONFIG_BCM96318)

static bp_elem_t g_bcm96318sv[] = {
  {bp_cpBoardId,               .u.cp = "96318SV"},
  {bp_usGpioOverlay,           .u.ul =(BP_OVERLAY_EPHY_LED_0 |
                                       BP_OVERLAY_EPHY_LED_1 |
                                       BP_OVERLAY_EPHY_LED_2 |
                                       BP_OVERLAY_EPHY_LED_3 )},
  {bp_usGpioLedAdsl,           .u.us = BP_GPIO_10_AL},
 // {bp_usGpioLedSesWireless,    .u.us = BP_GPIO_12_AL},
  {bp_usGpioLedWanData,        .u.us = BP_GPIO_8_AL},
  {bp_usGpioLedWanError,       .u.us = BP_GPIO_9_AL},
  {bp_usGpioLedBlStop,         .u.us = BP_GPIO_11_AL},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_1},
  {bp_usAntInUseWireless,      .u.us = BP_WLAN_ANT_MAIN},
  {bp_usWirelessFlags,         .u.us = 0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x1f},
  {bp_ulPhyId0,                .u.ul = 0x01},
  {bp_ulPhyId1,                .u.ul = 0x02},
  {bp_ulPhyId2,                .u.ul = 0x03},
  {bp_ulPhyId3,                .u.ul = 0x04},
  {bp_ulPhyId4,                .u.ul = 0x18 | MAC_IFACE_VALID | MAC_IF_RGMII | PHY_INTEGRATED_VALID | PHY_EXTERNAL},
  {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
  {bp_ucDspAddress,            .u.uc = 0},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6301 | BP_AFE_FE_ANNEXA | BP_AFE_FE_AVMODE_ADSL | BP_AFE_FE_REV_6301_REV_5_1_3},
  {bp_last}
};

static bp_elem_t g_bcm96318sv_sersw[] = {
  {bp_cpBoardId,               .u.cp = "96318SV_SERSW"},
  {bp_ulGpioOverlay,           .u.ul = (BP_OVERLAY_SERIAL_LEDS)},
  {bp_usSerialLEDMuxSel,       .u.us = (BP_SERIAL_MUX_SEL_GROUP0|BP_SERIAL_MUX_SEL_GROUP2)},
  {bp_usGpioLedAdsl,           .u.us = BP_GPIO_10_AL},
 // {bp_usGpioLedSesWireless,    .u.us = BP_GPIO_12_AL},
  {bp_usGpioLedWanData,        .u.us = BP_GPIO_8_AL},
  {bp_usGpioLedWanError,       .u.us = BP_GPIO_9_AL},
  {bp_usGpioLedBlStop,         .u.us = BP_GPIO_11_AL},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_1},
  {bp_usAntInUseWireless,      .u.us = BP_WLAN_ANT_MAIN},
  {bp_usWirelessFlags,         .u.us = 0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x1f},
  {bp_ulPhyId0,                .u.ul = 0x01},
  {bp_ulPhyId1,                .u.ul = 0x02},
  {bp_ulPhyId2,                .u.ul = 0x03},
  {bp_ulPhyId3,                .u.ul = 0x04},
  {bp_ulPhyId4,                .u.ul = 0x18 | MAC_IFACE_VALID | MAC_IF_RGMII | PHY_INTEGRATED_VALID | PHY_EXTERNAL},
  {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
  {bp_ucDspAddress,            .u.uc = 0},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6301 | BP_AFE_FE_ANNEXA | BP_AFE_FE_AVMODE_ADSL | BP_AFE_FE_REV_6301_REV_5_1_3},
  {bp_last}
};

static bp_elem_t g_bcm96318sv_serled[] = {
  {bp_cpBoardId,               .u.cp = "96318SV_SERLED"},
  {bp_ulGpioOverlay,           .u.ul =(BP_OVERLAY_EPHY_LED_0 |
                                       BP_OVERLAY_EPHY_LED_1 |
                                       BP_OVERLAY_EPHY_LED_2 |
                                       BP_OVERLAY_EPHY_LED_3 |
                                       BP_OVERLAY_SERIAL_LEDS)},
  {bp_usGpioLedAdsl,           .u.us = BP_SERIAL_GPIO_10_AL},
 // {bp_usGpioLedSesWireless,    .u.us = BP_GPIO_12_AL},
  {bp_usGpioLedWanData,        .u.us = BP_SERIAL_GPIO_8_AL},
  {bp_usGpioLedWanError,       .u.us = BP_SERIAL_GPIO_9_AL},
  {bp_usGpioLedBlStop,         .u.us = BP_SERIAL_GPIO_11_AL},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_1},
  {bp_usAntInUseWireless,      .u.us = BP_WLAN_ANT_MAIN},
  {bp_usWirelessFlags,         .u.us = 0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x1f},
  {bp_ulPhyId0,                .u.ul = 0x01},
  {bp_ulPhyId1,                .u.ul = 0x02},
  {bp_ulPhyId2,                .u.ul = 0x03},
  {bp_ulPhyId3,                .u.ul = 0x04},
  {bp_ulPhyId4,                .u.ul = 0x18 | MAC_IFACE_VALID | MAC_IF_RGMII | PHY_INTEGRATED_VALID | PHY_EXTERNAL},  
  {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
  {bp_ucDspAddress,            .u.uc = 0},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6301 | BP_AFE_FE_ANNEXA | BP_AFE_FE_AVMODE_ADSL | BP_AFE_FE_REV_6301_REV_5_1_3},
  {bp_last}
};

static bp_elem_t g_bcm96318ref[] = {
  {bp_cpBoardId,               .u.cp = "96318REF"},
  {bp_usGpioOverlay,           .u.ul =(BP_OVERLAY_EPHY_LED_0 |
                                       BP_OVERLAY_EPHY_LED_1 |
                                       BP_OVERLAY_EPHY_LED_2 |
                                       BP_OVERLAY_EPHY_LED_3 )},
  {bp_usGpioLedAdsl,           .u.us = BP_GPIO_10_AL},
 // {bp_usGpioLedSesWireless,    .u.us = BP_GPIO_12_AL},
  {bp_usGpioLedWanData,        .u.us = BP_GPIO_8_AL},
  {bp_usGpioLedWanError,       .u.us = BP_GPIO_9_AL},
  {bp_usGpioLedBlStop,         .u.us = BP_GPIO_11_AL},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_1},
  {bp_usExtIntrSesBtnWireless, .u.us = BP_EXT_INTR_0},
  {bp_usAntInUseWireless,      .u.us = BP_WLAN_ANT_MAIN},
  {bp_usWirelessFlags,         .u.us = 0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x0f},
  {bp_ulPhyId0,                .u.ul = 0x01},
  {bp_ulPhyId1,                .u.ul = 0x02},
  {bp_ulPhyId2,                .u.ul = 0x03},
  {bp_ulPhyId3,                .u.ul = 0x04},
  {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
  {bp_ucDspAddress,            .u.uc = 0},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6301 | BP_AFE_FE_ANNEXA | BP_AFE_FE_AVMODE_ADSL | BP_AFE_FE_REV_6301_REV_5_1_3},
  {bp_last}
};

static bp_elem_t g_bcm96318A_1441N1[] = {
  {bp_cpBoardId,               .u.cp = "96318A-1441N1"},
  {bp_usGpioOverlay,           .u.ul =(BP_OVERLAY_EPHY_LED_0 |
                                       BP_OVERLAY_EPHY_LED_1 |
                                       BP_OVERLAY_EPHY_LED_2 |
                                       BP_OVERLAY_EPHY_LED_3 )},
  {bp_usGpioLedAdsl,           .u.us = BP_GPIO_10_AL},
  {bp_usGpioLedSesWireless,    .u.us = BP_GPIO_0_AL},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_GPIO_1_AL},
  {bp_usGpioLedBlStop,         .u.us = BP_GPIO_11_AL},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_0},
  {bp_usExtIntrSesBtnWireless, .u.us = BP_EXT_INTR_NONE},
  //{bp_usExtIntrSesBtnWireless, .u.us = BP_GPIO_3_AL},
  {bp_usGpio_Intr,             .u.us = BP_GPIO_3_AL},
//  {bp_usExtIntrSesBtnWireless, .u.us = BP_GPIO_3_AL},
  {bp_usAntInUseWireless,      .u.us = BP_WLAN_ANT_MAIN},
  {bp_usWirelessFlags,         .u.us = 0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x0f},
  {bp_ulPhyId0,                .u.ul = 0x01},
  {bp_ulPhyId1,                .u.ul = 0x02},
  {bp_ulPhyId2,                .u.ul = 0x03},
  {bp_ulPhyId3,                .u.ul = 0x04},
  {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
  {bp_ucDspAddress,            .u.uc = 0},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6301 | BP_AFE_FE_ANNEXA | BP_AFE_FE_AVMODE_ADSL | BP_AFE_FE_REV_6301_REV_5_1_3},
  {bp_usGpioCtInternetLed,	   .u.us = BP_GPIO_8_AL},
  {bp_usGpioCtInternetFailLed, .u.us = BP_GPIO_9_AL},  
  {bp_usGpioCtUSBLed,		   .u.us = BP_GPIO_2_AL},
  {bp_last}
};
//<< Camille Wu: Add AR-5310
unsigned char _5310_phymap[BP_MAX_SWITCH_PORTS] = {0x04, 0x03, 0x02, 0x01, 0x00}; 

static bp_elem_t g_bcm96318AT_1341N1[] = {
  {bp_cpBoardId,               .u.cp = "96318AT-1341N1"},
  {bp_usGpioOverlay,           .u.ul =(BP_OVERLAY_EPHY_LED_0 |
                                       BP_OVERLAY_EPHY_LED_1 |
                                       BP_OVERLAY_EPHY_LED_2 |
                                       BP_OVERLAY_EPHY_LED_3 )},
  {bp_usGpioLedAdsl,           .u.us = BP_GPIO_17_AL},
  {bp_usGpioLedBlStop,         .u.us = BP_GPIO_11_AL},
  {bp_usGpioLedSesWireless,    .u.us = BP_GPIO_16_AL},
  {bp_usExtIntrSesBtnWireless, .u.us = BP_EXT_INTR_0},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_1},
  {bp_usAntInUseWireless,      .u.us = BP_WLAN_ANT_MAIN},
  {bp_usWirelessFlags,         .u.us = 0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x0f},
  {bp_ulPhyId0,                .u.ul = 0x01},
  {bp_ulPhyId1,                .u.ul = 0x02},
  {bp_ulPhyId2,                .u.ul = 0x03},
  {bp_ulPhyId3,                .u.ul = 0x04},
  {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
  {bp_ucDspAddress,            .u.uc = 0},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6301 | BP_AFE_FE_ANNEXA | BP_AFE_FE_AVMODE_ADSL | BP_AFE_FE_REV_6301_REV_5_1_3},
  {bp_usGpioCtInternetLed,	   .u.us = BP_GPIO_8_AL},
  {bp_usGpioCtInternetFailLed, .u.us = BP_GPIO_9_AL},  
  {bp_usGpioCtUSBLed,		   .u.us = BP_GPIO_18_AL},
  {bp_ucpEthPhyMap, 		   .u.ucp= _5310_phymap},
  {bp_last}
};
//>> Add AR-5310 End
//<< Camille Wu: Add AR-5310u
static bp_elem_t g_bcm96318AT_1341N3[] = {
  {bp_cpBoardId,               .u.cp = "96318AT-1341N3"},
  {bp_usGpioOverlay,           .u.ul =(BP_OVERLAY_EPHY_LED_0 |
                                       BP_OVERLAY_EPHY_LED_1 |
                                       BP_OVERLAY_EPHY_LED_2 |
                                       BP_OVERLAY_EPHY_LED_3 )},
  {bp_usGpioLedAdsl,           .u.us = BP_GPIO_17_AL},
  {bp_usGpioLedBlStop,         .u.us = BP_GPIO_11_AL},
  {bp_usGpioLedSesWireless,    .u.us = BP_GPIO_16_AL},
  {bp_usExtIntrSesBtnWireless, .u.us = BP_EXT_INTR_0},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_1},
  {bp_usAntInUseWireless,      .u.us = BP_WLAN_ANT_MAIN},
  {bp_usWirelessFlags,         .u.us = 0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x0f},
  {bp_ulPhyId0,                .u.ul = 0x01},
  {bp_ulPhyId1,                .u.ul = 0x02},
  {bp_ulPhyId2,                .u.ul = 0x03},
  {bp_ulPhyId3,                .u.ul = 0x04},
  {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
  {bp_ucDspAddress,            .u.uc = 0},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6301 | BP_AFE_FE_ANNEXA | BP_AFE_FE_AVMODE_ADSL | BP_AFE_FE_REV_6301_REV_5_1_3},
  {bp_usGpioCtInternetLed,	   .u.us = BP_GPIO_8_AL},
  {bp_usGpioCtInternetFailLed, .u.us = BP_GPIO_9_AL},  
  {bp_usGpioCtUSBLed,		   .u.us = BP_GPIO_18_AL},
  {bp_ucpEthPhyMap, 		   .u.ucp= _5310_phymap},
  {bp_last}
};
//>> Add AR-5310u End
//<< Joba Yang Add AR-5311
static bp_elem_t g_bcm96318AT_1341N2[] = {
  {bp_cpBoardId,               .u.cp = "96318AT-1341N2"},
  {bp_usGpioOverlay,           .u.ul =(BP_OVERLAY_EPHY_LED_0 |
                                       BP_OVERLAY_EPHY_LED_1 |
                                       BP_OVERLAY_EPHY_LED_2 |
                                       BP_OVERLAY_EPHY_LED_3 )},
  {bp_usGpioLedAdsl,           .u.us = BP_GPIO_17_AL},
  {bp_usGpioLedBlPowerOn,      .u.us = BP_GPIO_11_AL},
  {bp_usGpioLedSesWireless,    .u.us = BP_GPIO_16_AL},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_0},
  {bp_usAntInUseWireless,      .u.us = BP_WLAN_ANT_MAIN},
  {bp_usWirelessFlags,         .u.us = 0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x0f},
  {bp_ulPhyId0,                .u.ul = 0x01},
  {bp_ulPhyId1,                .u.ul = 0x02},
  {bp_ulPhyId2,                .u.ul = 0x03},
  {bp_ulPhyId3,                .u.ul = 0x04},
  {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
  {bp_ucDspAddress,            .u.uc = 0},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6301 | BP_AFE_FE_ANNEXA | BP_AFE_FE_AVMODE_ADSL | BP_AFE_FE_REV_6301_REV_5_1_3},
  {bp_usGpioCtInternetLed,	   .u.us = BP_GPIO_8_AL},
  {bp_usGpioCtInternetFailLed, .u.us = BP_GPIO_9_AL},  
  {bp_usGpioCtUSBLed,		   .u.us = BP_GPIO_2_AL},
  {bp_last}
};
//>> Joba Yang
//<< jimmylin: Add AR-5312
static bp_elem_t g_bcm96318AT_1341N4[] = {
  {bp_cpBoardId,               .u.cp = "96318AT-1341N4"},
  {bp_usGpioOverlay,           .u.ul =(BP_OVERLAY_EPHY_LED_0 |
                                       BP_OVERLAY_EPHY_LED_1 |
                                       BP_OVERLAY_EPHY_LED_2 |
                                       BP_OVERLAY_EPHY_LED_3 )},
  {bp_usGpioLedAdsl,           .u.us = BP_GPIO_17_AL},
  {bp_usGpioLedBlStop,         .u.us = BP_GPIO_11_AL},
  {bp_usGpioLedSesWireless,    .u.us = BP_GPIO_16_AL},
  {bp_usExtIntrSesBtnWireless, .u.us = BP_EXT_INTR_0},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_1},
  {bp_usAntInUseWireless,      .u.us = BP_WLAN_ANT_MAIN},
  {bp_usWirelessFlags,         .u.us = 0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x0f},
  {bp_ulPhyId0,                .u.ul = 0x01},
  {bp_ulPhyId1,                .u.ul = 0x02},
  {bp_ulPhyId2,                .u.ul = 0x03},
  {bp_ulPhyId3,                .u.ul = 0x04},
  {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
  {bp_ucDspAddress,            .u.uc = 0},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6301 | BP_AFE_FE_ANNEXA | BP_AFE_FE_AVMODE_ADSL | BP_AFE_FE_REV_6301_REV_5_1_3},
  {bp_usGpioCtInternetLed,	   .u.us = BP_GPIO_8_AL},
  {bp_usGpioCtInternetFailLed, .u.us = BP_GPIO_9_AL},
  {bp_usGpioCtUSBLed,		   .u.us = BP_GPIO_18_AL},
  {bp_ucpEthPhyMap, 		   .u.ucp= _5310_phymap},
  {bp_last}
};
//>> Add AR-5312 End
//<< camille: Add AR-5312u
static bp_elem_t g_bcm96318AT_1341N5[] = {
  {bp_cpBoardId,               .u.cp = "96318AT-1341N5"},
  {bp_usGpioOverlay,           .u.ul =(BP_OVERLAY_EPHY_LED_0 |
                                       BP_OVERLAY_EPHY_LED_1 |
                                       BP_OVERLAY_EPHY_LED_2 |
                                       BP_OVERLAY_EPHY_LED_3 )},
  {bp_usGpioLedAdsl,           .u.us = BP_GPIO_17_AL},
  {bp_usGpioLedBlStop,         .u.us = BP_GPIO_11_AL},
  {bp_usGpioLedSesWireless,    .u.us = BP_GPIO_16_AL},
  {bp_usExtIntrSesBtnWireless, .u.us = BP_EXT_INTR_0},
  {bp_usExtIntrResetToDefault, .u.us = BP_EXT_INTR_1},
  {bp_usAntInUseWireless,      .u.us = BP_WLAN_ANT_MAIN},
  {bp_usWirelessFlags,         .u.us = 0},
  {bp_ucPhyType0,              .u.uc = BP_ENET_EXTERNAL_SWITCH},
  {bp_ucPhyAddress,            .u.uc = 0x0},
  {bp_usConfigType,            .u.us = BP_ENET_CONFIG_MMAP},
  {bp_ulPortMap,               .u.ul = 0x0f},
  {bp_ulPhyId0,                .u.ul = 0x01},
  {bp_ulPhyId1,                .u.ul = 0x02},
  {bp_ulPhyId2,                .u.ul = 0x03},
  {bp_ulPhyId3,                .u.ul = 0x04},
  {bp_ucDspType0,              .u.uc = BP_VOIP_MIPS},
  {bp_ucDspAddress,            .u.uc = 0},
  {bp_ulAfeId0,                .u.ul = BP_AFE_CHIP_INT | BP_AFE_LD_6301 | BP_AFE_FE_ANNEXA | BP_AFE_FE_AVMODE_ADSL | BP_AFE_FE_REV_6301_REV_5_1_3},
  {bp_usGpioCtInternetLed,	   .u.us = BP_GPIO_8_AL},
  {bp_usGpioCtInternetFailLed, .u.us = BP_GPIO_9_AL},
  {bp_usGpioCtUSBLed,		   .u.us = BP_GPIO_18_AL},
  {bp_ucpEthPhyMap, 		   .u.ucp= _5310_phymap},
  {bp_last}
};
//>> Add AR-5312u End

static bp_elem_t g_bcm96318ref_p300[] = {
  {bp_cpBoardId,               .u.cp = "96318REF_P300"},
  {bp_usGpioLedSesWireless,    .u.us = BP_GPIO_16_AL},
  {bp_elemTemplate,            .u.bp_elemp = g_bcm96318ref},
  {bp_last}
};

static bp_elem_t * g_BoardParms[] = {g_bcm96318AT_1341N5, g_bcm96318AT_1341N4, g_bcm96318AT_1341N1,g_bcm96318AT_1341N3,g_bcm96318A_1441N1, g_bcm96318AT_1341N2, g_bcm96318sv, g_bcm96318ref, g_bcm96318ref_p300, g_bcm96318sv_serled, g_bcm96318sv_sersw, 0};

#endif

static bp_elem_t * g_pCurrentBp = 0;

/* Private function prototypes */
bp_elem_t * BpGetElem(enum bp_id id, bp_elem_t **pstartElem, enum bp_id stopAtId);
char *BpGetSubCp(enum bp_id id, bp_elem_t *pstartElem, enum bp_id stopAtId );
unsigned char BpGetSubUc(enum bp_id id, bp_elem_t *pstartElem, enum bp_id stopAtId );
unsigned short BpGetSubUs(enum bp_id id, bp_elem_t *pstartElem, enum bp_id stopAtId );
unsigned long BpGetSubUl(enum bp_id id, bp_elem_t *pstartElem, enum bp_id stopAtId );
int BpGetCp(enum bp_id id, char **pcpValue );
int BpGetUc(enum bp_id id, unsigned char *pucValue );
int BpGetUs(enum bp_id id, unsigned short *pusValue );
int BpGetUl(enum bp_id id, unsigned long *pulValue );
int BpGetGpio(enum bp_id id, unsigned short *pusValue );
int BpGetExtIntrGpio(enum bp_id id, unsigned short *pusValue);

/**************************************************************************
* Name       : bpstrcmp
*
* Description: String compare for this file so it does not depend on an OS.
*              (Linux kernel and CFE share this source file.)
*
* Parameters : [IN] dest - destination string
*              [IN] src - source string
*
* Returns    : -1 - dest < src, 1 - dest > src, 0 dest == src
***************************************************************************/
int bpstrcmp(const char *dest,const char *src)
{
    while (*src && *dest) {
        if (*dest < *src) return -1;
        if (*dest > *src) return 1;
        dest++;
        src++;
    }

    if (*dest && !*src) return 1;
    if (!*dest && *src) return -1;
    return 0;
} /* bpstrcmp */


/**************************************************************************
* Name       : BpGetElem
*
* Description: Private function to walk through the profile
*              and find the desired entry
*
* Parameters : [IN] id         - id to search for
*              [IN/OUT] pstartElem - where to start and where it was found
*              [IN] stopAtId   - id to stop at if the searched id is not found
*                                (allows grouping and repeated ids)
*
* Returns    : ptr to entry found or to last entry otherwise
***************************************************************************/
bp_elem_t * BpGetElem(enum bp_id id, bp_elem_t **pstartElem, enum bp_id stopAtId)
{
    bp_elem_t * pelem;

    // when compiling CFE, it does not like 'NULL' hence using 0
    if ( 0 == *pstartElem )
        *pstartElem = g_pCurrentBp;

    for (pelem = *pstartElem; 
         pelem->id != bp_last && pelem->id != id && pelem->id != stopAtId; 
         pelem++, (*pstartElem)++) 
    {
        // found template so jump to it
        // any entries after bp_elemTemplate will be ignored
        if ( bp_elemTemplate == pelem->id ) {
            *pstartElem = pelem->u.bp_elemp;
            pelem = *pstartElem;
            // ignoring the first element of this new array
            // because it is always bp_cpBoardId
        }
    }

    return pelem;    
}

/**************************************************************************
* Name       : BpGetSubCp
*
* Description: Private function to get an char * entry from the profile
*              can be used to search an id within a group by specifying stop id
*
* Parameters : [IN] id       - id to search for
*              [IN] pstartElem - where to start from
*              [IN] stopAtId - id to stop at if the searched id is not found
*                                (allows grouping and repeated ids)
*
* Returns    : the unsigned char * from the entry
***************************************************************************/
char *BpGetSubCp(enum bp_id id, bp_elem_t *pstartElem, enum bp_id stopAtId )
{
    bp_elem_t *pelem;

    pelem = BpGetElem(id, &pstartElem, stopAtId);
    if (id == pelem->id) { 
        return pelem->u.cp;
    } else { 
        return (char *)BP_NOT_DEFINED;
    }
}

/**************************************************************************
* Name       : BpGetSubUc
*
* Description: Private function to get an unsigned char entry from the profile
*              can be used to search an id within a group by specifying stop id
*
* Parameters : [IN] id       - id to search for
*              [IN] pstartElem - where to start from
*              [IN] stopAtId - id to stop at if the searched id is not found
*                                (allows grouping and repeated ids)
*
* Returns    : the unsigned char from the entry
***************************************************************************/
unsigned char BpGetSubUc(enum bp_id id, bp_elem_t *pstartElem, enum bp_id stopAtId )
{
    bp_elem_t *pelem;

    pelem = BpGetElem(id, &pstartElem, stopAtId);
    if (id == pelem->id) {
        return pelem->u.uc;
    } else {
        return (unsigned char)BP_NOT_DEFINED;
    }
}

/**************************************************************************
* Name       : BpGetSubUs
*
* Description: Private function to get an unsigned short entry from the profile
*              can be used to search an id within a group by specifying stop id
*
* Parameters : [IN] id       - id to search for
*              [IN] pstartElem - where to start from
*              [IN] stopAtId - id to stop at if the searched id is not found
*                                (allows grouping and repeated ids)
*
* Returns    : the unsigned short from the entry
***************************************************************************/
unsigned short BpGetSubUs(enum bp_id id, bp_elem_t *pstartElem, enum bp_id stopAtId )
{
    bp_elem_t *pelem;

    pelem = BpGetElem(id, &pstartElem, stopAtId);
    if (id == pelem->id) {
        return pelem->u.us;
    } else {
        return BP_NOT_DEFINED;
    }
}

/**************************************************************************
* Name       : BpGetSubUl
*
* Description: Private function to get an unsigned long entry from the profile
*              can be used to search an id within a group by specifying stop id
*
* Parameters : [IN] id       - id to search for
*              [IN] pstartElem - where to start from
*              [IN] stopAtId - id to stop at if the searched id is not found
*                                (allows grouping and repeated ids)
*
* Returns    : the unsigned long from the entry
***************************************************************************/
unsigned long BpGetSubUl(enum bp_id id, bp_elem_t *pstartElem, enum bp_id stopAtId )
{
    bp_elem_t *pelem;

    pelem = BpGetElem(id, &pstartElem, stopAtId);
    if (id == pelem->id)
        return pelem->u.ul;
    else
        return BP_NOT_DEFINED;
}

/**************************************************************************
* Name       : BpGetCp
*
* Description: Private function to get an char * entry from the profile
*              can only be used to search an id which appears once in the profile
*
* Parameters : [IN] id       - id to search for
*              [IN] pulValue - char ** found
*
* Returns    : BP_SUCCESS or appropriate error
***************************************************************************/
int BpGetCp(enum bp_id id, char **pcpValue )
{
    int nRet;

    if( g_pCurrentBp ) {
        *pcpValue = BpGetSubCp(id, 0, bp_last);
        nRet = ((char *)BP_NOT_DEFINED != *pcpValue ? BP_SUCCESS : BP_VALUE_NOT_DEFINED);
    } else {     
        *pcpValue = (char *)BP_NOT_DEFINED;
        nRet = BP_BOARD_ID_NOT_SET;
    }

    return( nRet );
}

/**************************************************************************
* Name       : BpGetUc
*
* Description: Private function to get an unsigned char entry from the profile
*              can only be used to search an id which appears once in the profile
*
* Parameters : [IN] id       - id to search for
*              [IN] pucValue - unsigned char found
*
* Returns    : BP_SUCCESS or appropriate error
***************************************************************************/
int BpGetUc(enum bp_id id, unsigned char *pucValue )
{
    int nRet;

    if( g_pCurrentBp ) {
        *pucValue = BpGetSubUc(id, 0, bp_last);
        nRet = ((unsigned char)BP_NOT_DEFINED != *pucValue ? BP_SUCCESS : BP_VALUE_NOT_DEFINED);
    } else {
        *pucValue = (unsigned char)BP_NOT_DEFINED;
        nRet = BP_BOARD_ID_NOT_SET;
    }

    return( nRet );
}

/**************************************************************************
* Name       : BpGetUs
*
* Description: Private function to get an unsigned short entry from the profile
*              can only be used to search an id which appears once in the profile
*
* Parameters : [IN] id       - id to search for
*              [IN] pusValue - unsigned short found
*
* Returns    : BP_SUCCESS or appropriate error
***************************************************************************/
int BpGetUs(enum bp_id id, unsigned short *pusValue )
{
    int nRet;

    if( g_pCurrentBp ) {
        *pusValue = BpGetSubUs(id, 0, bp_last);
        nRet = (BP_NOT_DEFINED != *pusValue ? BP_SUCCESS : BP_VALUE_NOT_DEFINED);
    } else {
        *pusValue = BP_NOT_DEFINED;
        nRet = BP_BOARD_ID_NOT_SET;
    }

    return( nRet );
}

/**************************************************************************
* Name       : BpGetUl
*
* Description: Private function to get an unsigned long entry from the profile
*              can only be used to search an id which appears once in the profile
*
* Parameters : [IN] id       - id to search for
*              [IN] pulValue - unsigned long found
*
* Returns    : BP_SUCCESS or appropriate error
***************************************************************************/
int BpGetUl(enum bp_id id, unsigned long *pulValue )
{
    int nRet;

    if( g_pCurrentBp ) {
        *pulValue = BpGetSubUl(id, 0, bp_last);
        nRet = (BP_NOT_DEFINED != *pulValue ? BP_SUCCESS : BP_VALUE_NOT_DEFINED);
    } else {
        *pulValue = BP_NOT_DEFINED;
        nRet = BP_BOARD_ID_NOT_SET;
    }

    return( nRet );
}

/**************************************************************************
* Name       : BpEnumUs
*
* Description: Enumerate the board parameters for all the instance of Us boardparms id 
*
* Parameters : [IN] id - boardparm id to enumerate.
*              [IN] token - transparent to caller. Set a pointer to NULL when first time call
*              [OUT] pusValue - value of the id
*
* Returns    : BP_SUCCESS - Success, value is returned in pusValue
*              BP_SUCCESS_LAST - Last entry reached, no value is returened in pusValue
*              BP_VALUE_NOT_DEFINED - this Led id is not defined in the boardparm
***************************************************************************/
int BpEnumUs(enum bp_id id, int* token, unsigned short *pusValue)
{
    bp_elem_t *pelem, *pnext;
    int rc;

    pelem = (bp_elem_t*)(*token);
    pnext = BpGetElem(id, &pelem, bp_last);
    if (id == pnext->id) 
    {
        *pusValue =  pnext->u.us;
        pnext++;
        *token = (int)pnext;
        rc = BP_SUCCESS;
    }
    else 
    {
        if( *token == 0 )
        {
	    /* no such bp item at all */   
	    *pusValue = BP_NOT_DEFINED;
            rc = BP_VALUE_NOT_DEFINED;
	}
        else
        {
            /* previous instant exists but we reach to the end... */   
	    *pusValue = BP_NOT_DEFINED;
            rc = BP_SUCCESS_LAST;
	}
    }

    return rc;
}

/**************************************************************************
* Name       : BpGetVoipDspConfig
*
* Description: Gets the DSP configuration from the board parameter
*              structure for a given DSP index.
*
* Parameters : [IN] dspNum - DSP index (number)
*
***************************************************************************/
VOIP_DSP_INFO g_VoIPDspInfo[BP_MAX_VOIP_DSP] = {{0}};
VOIP_DSP_INFO *BpGetVoipDspConfig( unsigned char dspNum )
{
    VOIP_DSP_INFO *pDspConfig = 0;
    int i;
    bp_elem_t *pelem;
    bp_elem_t *pDspType;
    enum bp_id bp_aucDspType[BP_MAX_VOIP_DSP+1] = {bp_ucDspType0, bp_ucDspType1, bp_last};
    enum bp_id bp_current, bp_next;

    if( g_pCurrentBp ) {
        /* First initialize the structure to known values */
        for( i = 0 ; i < BP_MAX_VOIP_DSP ; i++ ) {
            g_VoIPDspInfo[i].ucDspType = BP_VOIP_NO_DSP;
        }

        /* Now populate it with what we have in the element array */
        for( i = 0 ; i < BP_MAX_VOIP_DSP ; i++ ) {
            pDspType = 0;
            bp_current = bp_aucDspType[i];
            bp_next    = bp_aucDspType[i+1];
            pelem = BpGetElem(bp_current, &pDspType, bp_next);
            if (bp_current != pelem->id) {
                continue;
            }
            g_VoIPDspInfo[i].ucDspType = pelem->u.uc;

            ++pDspType;
            g_VoIPDspInfo[i].ucDspAddress       = BpGetSubUc(bp_ucDspAddress, pDspType, bp_next);
            g_VoIPDspInfo[i].usGpioLedVoip      = BpGetSubUs(bp_usGpioLedVoip, pDspType, bp_next);
            g_VoIPDspInfo[i].usGpioVoip1Led     = BpGetSubUs(bp_usGpioVoip1Led, pDspType, bp_next);
            g_VoIPDspInfo[i].usGpioVoip1LedFail = BpGetSubUs(bp_usGpioVoip1LedFail, pDspType, bp_next);
            g_VoIPDspInfo[i].usGpioVoip2Led     = BpGetSubUs(bp_usGpioVoip2Led, pDspType, bp_next);
            g_VoIPDspInfo[i].usGpioVoip2LedFail = BpGetSubUs(bp_usGpioVoip2LedFail, pDspType, bp_next);
            g_VoIPDspInfo[i].usGpioPotsLed      = BpGetSubUs(bp_usGpioPotsLed, pDspType, bp_next);
            g_VoIPDspInfo[i].usGpioDectLed      = BpGetSubUs(bp_usGpioDectLed, pDspType, bp_next);
        }

        /* Transfer the requested results */
        for( i = 0 ; i < BP_MAX_VOIP_DSP ; i++ ) {
            if( g_VoIPDspInfo[i].ucDspType != BP_VOIP_NO_DSP &&
                g_VoIPDspInfo[i].ucDspAddress == dspNum ) {
                pDspConfig = &g_VoIPDspInfo[i];
                break;
            }
        }
    }

    return pDspConfig;
} /* BpGetVoipDspConfig */

/**************************************************************************
* Name       : BpSetBoardId
*
* Description: This function find the BOARD_PARAMETERS structure for the
*              specified board id string and assigns it to a global, static
*              variable.
*
* Parameters : [IN] pszBoardId - Board id string that is saved into NVRAM.
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_FOUND - Error, board id input string does not
*                  have a board parameters configuration record.
***************************************************************************/
int BpSetBoardId( char *pszBoardId )
{
    int nRet = BP_BOARD_ID_NOT_FOUND;
    bp_elem_t **ppcBp;

    for( ppcBp = g_BoardParms; *ppcBp; ppcBp++ ) {
        if( !bpstrcmp((*ppcBp)[0].u.cp, pszBoardId) ) {
            g_pCurrentBp = *ppcBp;
            nRet = BP_SUCCESS;
            break;
        }
    }

    return( nRet );
} /* BpSetBoardId */

/**************************************************************************
* Name       : BpGetBoardId
*
* Description: This function returns the current board id strings.
*
* Parameters : [OUT] pszBoardIds - Address of a buffer that the board id
*                  string is returned in.
*
* Returns    : BP_SUCCESS - Success, value is returned.
***************************************************************************/
int BpGetBoardId( char *pszBoardId )
{
    int i;

    if (g_pCurrentBp == 0) {
        return -1;
    }

    for (i = 0; i < BP_BOARD_ID_LEN; i++) {
        pszBoardId[i] = g_pCurrentBp[0].u.cp[i];
    }

    return 0;
}

/**************************************************************************
* Name       : BpGetBoardIdNameByIndex
*
* Description: This function returns the pointer to the board id name indexed by i. 
*
* Parameters : [OUT] Address of a buffer that the board id
*                    string is returned in.
*              [IN]  Index of the board in the g_BoardParms array.            
*
* Returns    : BP_SUCCESS - Success, value is returned.
***************************************************************************/
char * BpGetBoardIdNameByIndex( int i )
{
    return g_BoardParms[i][0].u.cp;
}


/**************************************************************************
* Name       : BpGetBoardIds
*
* Description: This function returns all of the supported board id strings.
*
* Parameters : [OUT] pszBoardIds - Address of a buffer that the board id
*                  strings are returned in.  Each id starts at BP_BOARD_ID_LEN
*                  boundary.
*              [IN] nBoardIdsSize - Number of BP_BOARD_ID_LEN elements that
*                  were allocated in pszBoardIds.
*
* Returns    : Number of board id strings returned.
***************************************************************************/
int BpGetBoardIds( char *pszBoardIds, int nBoardIdsSize )
{
    int i;
    char *src;
    char *dest;
    bp_elem_t **ppcBp;

    for( i = 0, ppcBp = g_BoardParms; *ppcBp && nBoardIdsSize;
        i++, ppcBp++, nBoardIdsSize--, pszBoardIds += BP_BOARD_ID_LEN ) {
        dest = pszBoardIds;
        src = (*ppcBp)[0].u.cp;
        while( *src ) {
            *dest++ = *src++;
        }
        *dest = '\0';
    }

    return( i );
} /* BpGetBoardIds */

int BPGetNumBoardIds(void)
{
    int numElements = sizeof(g_BoardParms) / sizeof(bp_elem_t *);
    return ( numElements - 1);
}


/**************************************************************************
* Name       : BpGetComment
*
* Description: This function returns is used to get a comment for a board.
*
* Parameters : [OUT] pcpValue - comment string.
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - At least one return value is not defined
*                  for the board.
***************************************************************************/
int BpGetComment( char **pcpValue )
{
    return( BpGetCp(bp_cpComment, pcpValue ) );
} /* BpGetComment */

/**************************************************************************
* Name       : BpGetGPIOverlays
*
* Description: This function GPIO overlay configuration
*
* Parameters : [OUT] pusValue - Address of short word that interfaces in use.
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - At least one return value is not defined
*                  for the board.
***************************************************************************/
int BpGetGPIOverlays( unsigned long *pulValue )
{
    return( BpGetUl(bp_ulGpioOverlay, pulValue ) );
} /* BpGetGPIOverlays */


/**************************************************************************
* Name       : BpGetEthernetMacInfo
*
* Description: This function returns all of the supported board id strings.
*
* Parameters : [OUT] pEnetInfos - Address of an array of ETHERNET_MAC_INFO
*                  buffers.
*              [IN] nNumEnetInfos - Number of ETHERNET_MAC_INFO elements that
*                  are pointed to by pEnetInfos.
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
***************************************************************************/
int BpGetEthernetMacInfo( PETHERNET_MAC_INFO pEnetInfos, int nNumEnetInfos )
{
    int i, j;
    bp_elem_t *pelem;
    bp_elem_t *pPhyType;
    bp_elem_t *pPhyId;
    int nRet = BP_BOARD_ID_NOT_SET;
    PETHERNET_MAC_INFO pE;
    enum bp_id bp_aucPhyType[BP_MAX_ENET_MACS+1] = {bp_ucPhyType0, bp_ucPhyType1, bp_last};
    enum bp_id bp_current, bp_next;
    enum bp_id bp_aulPhyId[BP_MAX_SWITCH_PORTS+1] = {bp_ulPhyId0, bp_ulPhyId1, bp_ulPhyId2,
                bp_ulPhyId3, bp_ulPhyId4, bp_ulPhyId5, bp_ulPhyId6, bp_ulPhyId7, bp_last};
    enum bp_id bp_current_phyid;

    /* First initialize the structure to known values */
    for( i = 0, pE = pEnetInfos; i < nNumEnetInfos; i++, pE++ ) {
        pE->ucPhyType = BP_ENET_NO_PHY;
        /* The old code only initialized the first set, let's tdo the same so the 2 compare without error */
        if (0 == i) {
            for( j = 0; j < BP_MAX_ENET_INTERNAL; j++ ) {
                pE->sw.ledInfo[j].duplexLed = BP_NOT_DEFINED;
                pE->sw.ledInfo[j].speedLed100 = BP_NOT_DEFINED;
                pE->sw.ledInfo[j].speedLed1000 = BP_NOT_DEFINED;
            }
        }
    }

    if( g_pCurrentBp ) {
        /* Populate it with what we have in the element array */
        for( i = 0, pE = pEnetInfos; i < BP_MAX_ENET_MACS; i++, pE++ ) {
            pPhyType = 0;
            bp_current = bp_aucPhyType[i];
            bp_next    = bp_aucPhyType[i+1];
            pelem = BpGetElem(bp_current, &pPhyType, bp_next);
            if (bp_current != pelem->id)
                continue;
            pE->ucPhyType = pelem->u.uc;

            ++pPhyType;
            pE->ucPhyAddress  = BpGetSubUc(bp_ucPhyAddress, pPhyType, bp_next);
            pE->usConfigType  = BpGetSubUs(bp_usConfigType, pPhyType, bp_next);
            pE->sw.port_map   = BpGetSubUl(bp_ulPortMap, pPhyType, bp_next);

            for( j = 0; j < BP_MAX_SWITCH_PORTS; j++ ) {
                pPhyId = pPhyType;
                bp_current_phyid = bp_aulPhyId[j];
                pelem = BpGetElem(bp_current_phyid, &pPhyId, bp_next);
                pE->sw.phyconn[j] = PHY_CONN_TYPE_NOT_DEFINED;
                pE->sw.phy_devName[j] = PHY_DEVNAME_NOT_DEFINED;
                pE->sw.phyinit[j] = (bp_mdio_init_t* )0;
                if (bp_current_phyid == pelem->id) {
                    pE->sw.phy_id[j] = pelem->u.ul & ~MII_OVER_GPIO_VALID;
                    ++pPhyId;
                        while (pPhyId) {
                            switch (pPhyId->id) {
                            case bp_usDuplexLed:
                                pE->sw.ledInfo[j].duplexLed = pPhyId->u.us;
                                ++pPhyId;
                                break;
                            case bp_usSpeedLed100:
                                pE->sw.ledInfo[j].speedLed100 = pPhyId->u.us;
                                ++pPhyId;
                                break;
                            case bp_usSpeedLed1000:
                                pE->sw.ledInfo[j].speedLed1000 = pPhyId->u.us;
                                ++pPhyId;
                                break;
                        case bp_usPhyConnType:
                            pE->sw.phyconn[j] = pPhyId->u.us;
                            ++pPhyId;
                            break;
                        case bp_ucPhyDevName:
                            pE->sw.phy_devName[j] = pPhyId->u.cp;
                            ++pPhyId;
                            break;                            
                        case bp_pPhyInit:
                             pE->sw.phyinit[j] = pPhyId->u.phyinitp;
                             ++pPhyId;
                            break;
                            default:
                                pPhyId = 0;
                                break;
                            }
                        }
                } else {
                    pE->sw.phy_id[j] = 0;
                }
            }
        }
        nRet = BP_SUCCESS;
    }
    return( nRet );

} /* BpGetEthernetMacInfo */

#if defined(CONFIG_BCM963268) && defined(CONFIG_BCM_EXT_SWITCH)
int BpGetPortConnectedToExtSwitch(void)
{
    unsigned long phy_id, port_map;
    int i, extSwConnPort = -1;

    BpGetUl(bp_ulPortMap, &port_map);

    for (i = 0; i < BP_MAX_SWITCH_PORTS; i++) {
        if ( port_map &  (1 << i)) {
            BpGetUl(bp_ulPhyId0 + i, &phy_id);
            if (phy_id & EXTSW_CONNECTED)
            {
                extSwConnPort = i;
            }
        }
    }
    return extSwConnPort;
}
#endif

/**************************************************************************
* Name       : BpGetMiiOverGpioFlag
*
* Description: This function returns logical disjunction of MII over GPIO
*              flag over all PHY IDs.
*
* Parameters : [OUT] pMiiOverGpioFlag - MII over GPIO flag
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
***************************************************************************/
int BpGetMiiOverGpioFlag( unsigned long* pMiiOverGpioFlag )
{
    int i, j;
    bp_elem_t *pelem;
    bp_elem_t *pPhyType;
    bp_elem_t *pPhyId;
    int nRet;
    enum bp_id bp_aucPhyType[BP_MAX_ENET_MACS+1] = {bp_ucPhyType0, bp_ucPhyType1, bp_last};
    enum bp_id bp_current, bp_next;
    enum bp_id bp_aulPhyId[BP_MAX_SWITCH_PORTS+1] = {bp_ulPhyId0, bp_ulPhyId1, bp_ulPhyId2,
                bp_ulPhyId3, bp_ulPhyId4, bp_ulPhyId5, bp_ulPhyId6, bp_ulPhyId7, bp_last};
    enum bp_id bp_current_phyid;

    *pMiiOverGpioFlag = 0;

    if( g_pCurrentBp ) {
        for( i = 0; i < BP_MAX_ENET_MACS; i++ ) {
            pPhyType = 0;
            bp_current = bp_aucPhyType[i];
            bp_next    = bp_aucPhyType[i+1];
            pelem = BpGetElem(bp_current, &pPhyType, bp_next);
            if (bp_current != pelem->id)
                continue;

            ++pPhyType;
            for( j = 0; j < BP_MAX_SWITCH_PORTS; j++ ) {
                pPhyId = pPhyType;
                bp_current_phyid = bp_aulPhyId[j];
                pelem = BpGetElem(bp_current_phyid, &pPhyId, bp_next);
                if (bp_current_phyid == pelem->id) {
                    *pMiiOverGpioFlag |= pelem->u.ul & MII_OVER_GPIO_VALID;                
                    ++pPhyId;
                }
            }
        }
        // Normalize flag value by positioning in lsb position        
        *pMiiOverGpioFlag >>= MII_OVER_GPIO_S;
        nRet = BP_SUCCESS;
    }
    else
    {
        nRet = BP_BOARD_ID_NOT_SET;
    }

    return( nRet );

} /* BpGetMiiOverGpioFlag */


/**************************************************************************
* Name       : BpGetGpio
*
* Description: Wrapper function to get the Gpio pin number
*
* Parameters : [IN] id       - id to search for
*              [IN] pusValue - unsigned short found
*
* Returns    : BP_SUCCESS or appropriate error
***************************************************************************/
int BpGetGpio(enum bp_id id, unsigned short *pusValue )
{
    int nRet;

    nRet = BpGetUs(id, pusValue );
    if(nRet == BP_SUCCESS && *pusValue == BP_GPIO_NONE)
    {
    	*pusValue = BP_NOT_DEFINED;
    	nRet = BP_VALUE_NOT_DEFINED;
    }

    return( nRet );
}

/**************************************************************************
* Name       : BpGetExtIntrGpio
*
* Description: Wrapper function to get the Gpio pin number for shared external
*              interrupt
*
* Parameters : [IN] id       - id for the external interrupt. The bp_usGpio_Intr
*                              id must follow this id
*              [IN] pusValue - unsigned short found
*
* Returns    : BP_SUCCESS or appropriate error
***************************************************************************/
int  BpGetExtIntrGpio(enum bp_id id, unsigned short *pusValue)
{
    bp_elem_t *pelem;
    int ret;
    bp_elem_t *start_elem = 0;

    /* First go to elem with interrupt id */
    pelem = BpGetElem(id,  &start_elem, bp_last);
    if (id != pelem->id)
    {
        *pusValue = BP_NOT_DEFINED;
        ret = BP_VALUE_NOT_DEFINED;
    }
    else
    {
        pelem++;
        /* We should expect the id bp_usGpio_Intr in the next element */
        if (bp_usGpio_Intr != pelem->id)
        {
            *pusValue = BP_NOT_DEFINED;
            ret = BP_VALUE_NOT_DEFINED;
        }
        else
        {
            *pusValue = pelem->u.us;
            ret = BP_SUCCESS;
        }
    }

    return ret;
}

/**************************************************************************
* Name       : BpGetRj11InnerOuterPairGpios
*
* Description: This function returns the GPIO pin assignments for changing
*              between the RJ11 inner pair and RJ11 outer pair.
*
* Parameters : [OUT] pusInner - Address of short word that the RJ11 inner pair
*                  GPIO pin is returned in.
*              [OUT] pusOuter - Address of short word that the RJ11 outer pair
*                  GPIO pin is returned in.
*
* Returns    : BP_SUCCESS - Success, values are returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - At least one return value is not defined
*                  for the board.
***************************************************************************/
int BpGetRj11InnerOuterPairGpios( unsigned short *pusInner,
                                 unsigned short *pusOuter )
{
    *pusInner = BP_NOT_DEFINED;
    *pusOuter = BP_NOT_DEFINED;

    return( BP_VALUE_NOT_DEFINED );
} /* BpGetRj11InnerOuterPairGpios */

/**************************************************************************
* Name       : BpGetUartRtsCtsGpios
*
* Description: This function returns the GPIO pin assignments for RTS and CTS
*              UART signals.
*
* Parameters : [OUT] pusRts - Address of short word that the UART RTS GPIO
*                  pin is returned in.
*              [OUT] pusCts - Address of short word that the UART CTS GPIO
*                  pin is returned in.
*
* Returns    : BP_SUCCESS - Success, values are returned.
*              BP_BOARD_ID_NOT_SET - Error, board id input string does not
*              BP_VALUE_NOT_DEFINED - At least one return value is not defined
*                  for the board.
***************************************************************************/
int BpGetRtsCtsUartGpios( unsigned short *pusRts, unsigned short *pusCts )
{
    *pusRts = BP_NOT_DEFINED;
    *pusCts = BP_NOT_DEFINED;

    return( BP_VALUE_NOT_DEFINED );
} /* BpGetUartRtsCtsGpios */

/**************************************************************************
* Name       : BpGetAdslLedGpio
*
* Description: This function returns the GPIO pin assignment for the ADSL
*              LED.
*
* Parameters : [OUT] pusValue - Address of short word that the ADSL LED
*                  GPIO pin is returned in.
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - At least one return value is not defined
*                  for the board.
***************************************************************************/
int BpGetAdslLedGpio( unsigned short *pusValue )
{
    return( BpGetGpio(bp_usGpioLedAdsl, pusValue ) );
} /* BpGetAdslLedGpio */

/**************************************************************************
* Name       : BpGetAdslFailLedGpio
*
* Description: This function returns the GPIO pin assignment for the ADSL
*              LED that is used when there is a DSL connection failure.
*
* Parameters : [OUT] pusValue - Address of short word that the ADSL LED
*                  GPIO pin is returned in.
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - At least one return value is not defined
*                  for the board.
***************************************************************************/
int BpGetAdslFailLedGpio( unsigned short *pusValue )
{
    return( BpGetGpio(bp_usGpioLedAdslFail, pusValue ) );
} /* BpGetAdslFailLedGpio */

/**************************************************************************
* Name       : BpGetSecAdslLedGpio
*
* Description: This function returns the GPIO pin assignment for the ADSL
*              LED of the Secondary line, applicable more for bonding.
*
* Parameters : [OUT] pusValue - Address of short word that the ADSL LED
*                  GPIO pin is returned in.
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - At least one return value is not defined
*                  for the board.
***************************************************************************/
int BpGetSecAdslLedGpio( unsigned short *pusValue )
{
    return( BpGetGpio(bp_usGpioSecLedAdsl, pusValue ) );
} /* BpGetSecAdslLedGpio */

/**************************************************************************
* Name       : BpGetSecAdslFailLedGpio
*
* Description: This function returns the GPIO pin assignment for the ADSL
*              LED of the Secondary ADSL line, that is used when there is
*              a DSL connection failure.
*
* Parameters : [OUT] pusValue - Address of short word that the ADSL LED
*                  GPIO pin is returned in.
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - At least one return value is not defined
*                  for the board.
***************************************************************************/
int BpGetSecAdslFailLedGpio( unsigned short *pusValue )
{
    return( BpGetGpio(bp_usGpioSecLedAdslFail, pusValue ) );
} /* BpGetSecAdslFailLedGpio */

/**************************************************************************
* Name       : BpGetWirelessAntInUse
*
* Description: This function returns the antennas in use for wireless
*
* Parameters : [OUT] pusValue - Address of short word that the Wireless Antenna
*                  is in use.
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - At least one return value is not defined
*                  for the board.
***************************************************************************/
int BpGetWirelessAntInUse( unsigned short *pusValue )
{
    return( BpGetUs(bp_usAntInUseWireless, pusValue ) );
} /* BpGetWirelessAntInUse */

/**************************************************************************
* Name       : BpGetWirelessFlags
*
* Description: This function returns optional control flags for wireless
*
* Parameters : [OUT] pusValue - Address of short word control flags
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - At least one return value is not defined
*                  for the board.
***************************************************************************/
int BpGetWirelessFlags( unsigned short *pusValue )
{
    return( BpGetUs(bp_usWirelessFlags, pusValue ) );
} /* BpGetWirelessAntInUse */

/**************************************************************************
* Name       : BpGetWirelessSesExtIntr
*
* Description: This function returns the external interrupt number for the
*              Wireless Ses Button.
*
* Parameters : [OUT] pusValue - Address of short word that the Wireless Ses
*                  external interrup is returned in.
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - At least one return value is not defined
*                  for the board.
***************************************************************************/
int BpGetWirelessSesExtIntr( unsigned short *pusValue )
{
    return( BpGetUs(bp_usExtIntrSesBtnWireless, pusValue ) );
} /* BpGetWirelessSesExtIntr */

/**************************************************************************
* Name       : BpGetWirelessSesExtIntrGpio
*
* Description: This function returns the external interrupt number for the
*              Wireless Ses Button.
*
* Parameters : [OUT] pusValue - Address of short word that the Wireless Ses
*                  external interrup is returned in.
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - At least one return value is not defined
*                  for the board.
***************************************************************************/
int BpGetWirelessSesExtIntrGpio( unsigned short *pusValue )
{
    int ret;

    if( !g_pCurrentBp ) 
    {
        *pusValue = BP_NOT_DEFINED;
        ret       = BP_BOARD_ID_NOT_SET;
        return ret;
    }
    
    ret = BpGetExtIntrGpio(bp_usExtIntrSesBtnWireless, pusValue);
    
    return( ret );  
} /* BpGetWirelessSesExtIntrGpio */


/**************************************************************************
* Name       : BpGetWirelessSesLedGpio
*
* Description: This function returns the GPIO pin assignment for the Wireless
*              Ses Led.
*
* Parameters : [OUT] pusValue - Address of short word that the Wireless Ses
*                  Led GPIO pin is returned in.
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - At least one return value is not defined
*                  for the board.
***************************************************************************/
int BpGetWirelessSesLedGpio( unsigned short *pusValue )
{
    return( BpGetGpio(bp_usGpioLedSesWireless, pusValue ) );
} /* BpGetWirelessSesLedGpio */


/**************************************************************************
* Name       : BpGetMocaHostIntr
*
* Description: This function returns the external interrupt line for 
*              the moca host interrupt.
*
* Parameters : [OUT] pulValue - Address of the return value.
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - At least one return value is not defined
*                  for the board.
***************************************************************************/
int BpGetMocaHostIntr( unsigned long *pulValue )
{
    return( BpGetUl(bp_ulExtIntrMocaHostIntr, pulValue ) );
} /* BpGetMocaHostIntr */


#if defined(_BCM96362_) || defined(CONFIG_BCM96362)
/* The unique part contains the subSytemId (boardId) and the BoardRev number */
static WLAN_SROM_ENTRY wlan_patch_unique_96362ADVNX[] = {
    {2,  0x536},
    {65, 0x1100},
    {0, 0}
};

static WLAN_SROM_ENTRY wlan_patch_unique_96362ADVNgr2[] = {
    {2,  0x580},
    {65, 0x1500},
    {0, 0}
};

static WLAN_SROM_ENTRY wlan_patch_unique_963629epon[] = {
    {2,  0x5a5},
    {65, 0x1500},
    {0, 0}
};

static WLAN_SROM_ENTRY wlan_patch_unique_96362ADVN2xh[] = {
    {2,  0x5a6},
    {65, 0x1200},
    {0, 0}
};

static WLAN_SROM_ENTRY wlan_patch_unique_96361XF[] = {
    {2,  0x5b8},
    {65, 0x1100},
    {0, 0}
};

static WLAN_SROM_ENTRY wlan_patch_unique_96362RAVNGR2[] = {
    {2,  0x60d},
    {65, 0x1500},
    {0, 0}
};

static WLAN_SROM_ENTRY wlan_patch_unique_96362ADVN2XM[] = {
    {2,  0x60d},
    {65, 0x1500},
    {0, 0}
};

static WLAN_SROM_ENTRY wlan_patch_unique_96362RADVNXH5[] = {
    {2,  0x63F},
    {65, 0x1100},
    {0, 0}
};

static WLAN_SROM_ENTRY wlan_patch_unique_96362RADVN2XH[] = {
    {2,  0x63E},
    {65, 0x1100},
    {0, 0}
};

/* The common part contains the entries that are valid for multiple boards */
static WLAN_SROM_ENTRY wlan_patch_common_96362ADVNX[] = {
    { 87, 0x0319},
    { 96, 0x2058},
    { 97, 0xfe6f},
    { 98, 0x1785},
    { 99, 0xfa21},
    {112, 0x2058},
    {113, 0xfe77},
    {114, 0x17e0},
    {115, 0xfa16},
    {161, 0x5555},
    {162, 0x5555},
    {169, 0x5555},
    {170, 0x5555},
    {171, 0x5555},
    {172, 0x5555},
    {173, 0x3333},
    {174, 0x3333},
    {175, 0x3333},
    {176, 0x3333},
    {0, 0}
};

static WLAN_SROM_ENTRY wlan_patch_common_96362ADVNgr2[] = {
    { 96, 0x2046},
    {100, 0x3c46},
    {101, 0x4040},    
    {102, 0xFF3C},
    {103, 0x1381},
    {104, 0xFBF1},
    {108, 0xFF09},
    {109, 0x1310},
    {110, 0xFBD6},
    {112, 0x2046},
    {116, 0x3c46},  
    {117, 0x4040},
    {118, 0xFFE9},
    {119, 0x1383},
    {120, 0xFCBC},
    {124, 0xFF3F},
    {125, 0x13C9},
    {126, 0xFBEC},
    {160, 0x3333},
    {161, 0x0000},
    {162, 0x3333},
    {163, 0x0000},
    {164, 0x5555},
    {165, 0x0000},
    {166, 0x2222},
    {167, 0x0000},
    {168, 0x4444},
    {169, 0x3000},
    {170, 0x3333},
    {171, 0x3000},
    {172, 0x3333},
    {177, 0x5000},
    {178, 0x5555},
    {179, 0x5000},
    {180, 0x5555},
    {185, 0x2000},
    {186, 0x2222},
    {187, 0x2000},
    {188, 0x2222},
    {193, 0x4000},
    {194, 0x4444},
    {195, 0x4000},
    {196, 0x4444},
    {201, 0x1111},
    {202, 0x2222},
    {203, 0x6775},  
    {0, 0}
};

static WLAN_SROM_ENTRY wlan_patch_common_96361XF[] = {
    { 66, 0x0200},
    { 67, 0x0000},
    { 78, 0x0003},
    { 79, 0x0000},
    { 80, 0x0000},
    { 87, 0x0313},
    { 88, 0x0313},
    { 93, 0xffff},
    { 96, 0x2054},
    { 97, 0xfe80},
    { 98, 0x1fa2},
    { 99, 0xf897},
    {112, 0x2054},
    {113, 0xfe8c},
    {114, 0x1f13},
    {115, 0xf8c4},
    {161, 0x4444},
    {162, 0x4444},
    {169, 0x4444},
    {170, 0x4444},
    {171, 0x4444},
    {172, 0x4444},
    {203, 0x2222},  
    {0, 0}
};

static WLAN_SROM_ENTRY wlan_patch_common_96362ADVN2xh[] = {
    { 66, 0x3200},
    { 67, 0x8000},
    { 78, 0x0003},
    { 79, 0x0000},
    { 80, 0x0000},
    { 87, 0x031f},
    { 88, 0x031f},
    { 93, 0x0202},
    { 96, 0x2064},
    { 97, 0xfe80},
    { 98, 0x1fa2},
    { 99, 0xf897},
    {112, 0x2064},
    {113, 0xfe8c},
    {114, 0x1f13},
    {115, 0xf8c4},
    {203, 0x2222},
    {0, 0}
};

static WLAN_SROM_ENTRY wlan_patch_common_96362ADVN2XM[] = {
    /* PA params not updated yet */
    { 65, 0x1200},                
    { 66, 0x3200},
    { 67, 0x8000},
    { 78, 0x0003},
    { 79, 0x0000},
    { 80, 0x0000},
    { 87, 0x031f},
    { 88, 0x031f},
    { 93, 0x0202},
    { 96, 0x205c},
    { 97, 0xfe80},
    { 98, 0x1fa2},
    { 99, 0xf897},
    {112, 0x205c},
    {113, 0xfe8c},
    {114, 0x1f13},
    {115, 0xf8c4},
    {203, 0x2222},
    {0, 0}
};

static WLAN_SROM_ENTRY wlan_patch_common_96362RADVNXH5[] = {
    /* PA params not updated yet */
    { 66,  0x3200},
    { 67,  0x8000},
    { 78,  0x0300},
    { 87,  0x031f},
    { 88,  0x033f},
    { 93,  0x0202},
    { 100, 0x4060},
    { 101, 0x6060},
    { 102, 0xFE87},
    { 103, 0x1F06},
    { 104, 0xF8B0},
    { 108, 0xFE88},
    { 109, 0x1EC8},
    { 110, 0xF8C0},
    { 116, 0x4060},
    { 117, 0x6060},
    { 118, 0xFE87},
    { 119, 0x1F06},
    { 120, 0xF8B0},
    { 124, 0xFE8E},
    { 125, 0x1F0B},
    { 126, 0xF8BB},
    { 161, 0x0000},
    { 162, 0x0000},
    { 169, 0x0000},
    { 170, 0x0000},
    { 171, 0x0000},
    { 172, 0x0000},
    {203, 0x2222},  
    {0, 0}
};
#endif

#if defined(_BCM963268_) || defined(CONFIG_BCM963268)
/* The unique part contains the subSytemId (boardId) and the BoardRev number */
static WLAN_SROM_ENTRY wlan_patch_unique_963268MBV[] = {
    {2,  0x5BB},
    { 65,  0x1204},
    {0, 0}
};

static WLAN_SROM_ENTRY wlan_patch_unique_963268V30A[] = {
    {2,  0x5E7},
    { 65,  0x1101},
    {0, 0}
};

static WLAN_SROM_ENTRY wlan_patch_unique_963268BU[] = {
    {2,  0x5A7},
    { 65,  0x1201},
    {0, 0}
};

static WLAN_SROM_ENTRY wlan_patch_unique_963168XH[] = {
    {2,  0x5E2},
    {65, 0x1100},
    {0, 0}
};

static WLAN_SROM_ENTRY wlan_patch_unique_963168XM[] = {
    {2,  0x61F},
    {65, 0x1100},
    {0, 0}
};

static WLAN_SROM_ENTRY wlan_patch_unique_963168XH5[] = {
    {2,  0x640},
    {65, 0x1100},
    {0, 0}
};
// << kewei lai for add new boardid 963169R-1861AC to WAP-5892u 
/*for wifi srom table*/

static WLAN_SROM_ENTRY wlan_patch_common_1861AC_4360[] = {
    {0, 0}
};

static WLAN_SROM_ENTRY wlan_patch_unique_1861AC[] = { 
    { 97,  0xff0e},
    { 98,  0x16e0},
    { 99,  0xfa77},
    { 113, 0xff15},
    { 114, 0x1732},
    { 115, 0xfa8e},
    {   0,      0}      
};

static WLAN_SROM_ENTRY wlan_patch_unique_1861AC_4360[] = { 
    { 116,  0xffa6},
    { 117,  0x1600},
    { 118,  0xfd8c},
    { 119,  0xff80},
    { 120,  0x1603},
    { 121,  0xfd66},
    { 122,  0xff84},
    { 123,  0x167d},
    { 124,  0xfd58},
    { 125,  0xff85},
    { 126,  0x1704},
    { 127,  0xfd4f},
    { 136,  0xff89},
    { 137,  0x151e},
    { 138,  0xfd7b},
    { 139,  0xff86},
    { 140,  0x1597},
    { 141,  0xfd6f},
    { 142,  0xff71},
    { 143,  0x15a1},
    { 144,  0xfd62},
    { 145,  0xff77},
    { 146,  0x165d},
    { 147,  0xfd64},
    { 156,  0xffa1},
    { 157,  0x15ce},
    { 158,  0xfd83},
    { 159,  0xff97},
    { 160,  0x1676},
    { 161,  0xfd68},
    { 162,  0xff82},
    { 163,  0x1627},
    { 164,  0xfd5f},
    { 165,  0xff7d},
    { 166,  0x1730},
    { 167,  0xfd4b},
    {   0,      0}      
};
// >> kewei lai for add new boardid 963169R-1861AC to WAP-5892u 

//<< for PROFILE=NL-3110u_CTL
static WLAN_SROM_ENTRY wlan_patch_unique_963268VB[] = {
    { 2,  0x05BB},
    { 65,  0x1204},
    { 97,  0xFF8E}, 
    { 98,  0x18FB},
    { 99,  0xFA6C},
    { 113, 0xFF75},
    { 114, 0x1868},
    { 115, 0xFA80},
    {0, 0}
};
static WLAN_SROM_ENTRY wlan_patch_common_963268M_CT[] = {
    { 2,  0x05BB},
    { 65,  0x1204},
    { 78,  0x0303}, 
    { 79,  0x0202}, 
    { 80,  0xff02},
    { 87,  0x0315}, 
    { 88,  0x0315},
    { 96,  0x2048}, 
    { 100, 0x3E3C},
    { 101, 0x4038},
    { 102, 0xFE7F},
    { 103, 0x1279},
    { 112, 0x2048},
    { 116, 0x3E3C},
    { 117, 0x4038},
    { 118, 0xFE87},
    { 119, 0x1233},
    { 203, 0x2226},
    {0, 0}
};
//<< for PROFILE=NL-3110u_CTL

/* The common part contains the entries that are valid for multiple boards */
static WLAN_SROM_ENTRY wlan_patch_common_963268MBV[] = {
    { 78,  0x0303},
    { 79,  0x0202},
    { 80,  0xff02},
    { 87,  0x0315},
    { 88,  0x0315},
    { 96,  0x2048},
    { 97,  0xFFB5},
    { 98,  0x175F},
    { 99,  0xFB29},
    { 100, 0x3E40},
    { 101, 0x403C},
    { 102, 0xFF15},
    { 103, 0x1455},
    { 104, 0xFB95},
    { 108, 0xFF28},
    { 109, 0x1315},
    { 110, 0xFBF0},
    { 112, 0x2048}, 
    { 113, 0xFFD7},
    { 114, 0x17D6},
    { 115, 0xFB67},
    { 116, 0x3E40},
    { 117, 0x403C},
    { 118, 0xFE87},
    { 119, 0x110F},
    { 120, 0xFB4B},
    { 124, 0xFF8D},
    { 125, 0x1146},
    { 126, 0xFCD6},
    { 161, 0x0000},
    { 162, 0x4444},
    { 163, 0x0000},
    { 164, 0x2222},
    { 165, 0x0000},
    { 166, 0x2222},
    { 167, 0x0000},
    { 168, 0x2222},
    { 169, 0x4000},
    { 170, 0x4444},
    { 171, 0x4000},
    { 172, 0x4444},
    { 177, 0x2000},
    { 178, 0x2222},
    { 179, 0x2000},
    { 180, 0x2222},
    { 185, 0x2000},
    { 186, 0x2222},
    { 187, 0x2000},
    { 188, 0x2222},
    { 193, 0x2000},
    { 194, 0x2222},
    { 195, 0x2000},
    { 196, 0x2222},
    { 201, 0x1111},
    { 202, 0x2222},
    { 203, 0x4446},
    {0, 0}
};

static WLAN_SROM_ENTRY wlan_patch_common_963168XH[] = {
    { 66,  0x3200},
    { 67,  0x8000},
    { 87,  0x031f},
    { 88,  0x031f},
    { 93,  0x0202},
    { 96,  0x2064},
    { 97,  0xfe59},
    { 98,  0x1c81},
    { 99,  0xf911},
    { 112, 0x2064},
    { 113, 0xfe55},
    { 114, 0x1c00},
    { 115, 0xf92c},
    { 161, 0x0000},
    { 162, 0x0000},
    { 169, 0x0000},
    { 170, 0x0000},
    { 171, 0x0000},
    { 172, 0x0000},
    { 203, 0x2222},
    {0, 0}
};
//<< Charles Wei: Correction for wrong SROM patch which caused poor wireless performance for VR-3031u
//<< Joba Yang Change Wireless PA and Advertise no 1000BASE-T full-duplex/half-duplex capability for VR-3031u_CTL
static WLAN_SROM_ENTRY wlan_patch_unique_1341N1[] = { 
    { 2,  0x05BB},
    { 65,  0x1204},
    { 97,  0xFF81},
    { 98,  0x1860},
    { 99,  0xFA98},
    { 113, 0xFF58},
    { 114, 0x17CA},
    { 115, 0xFAA3},
    {   0,      0}      
};
//>> Joba Yang End
//>> Charles Wei: End, Correction for wrong SROM patch which caused poor wireless performance for VR-3031u
static WLAN_SROM_ENTRY wlan_patch_common_963168XM[] = {
    { 66,  0x3200},
    { 67,  0x8000},
    { 87,  0x031f},
    { 88,  0x031f},
    { 93,  0x0202},
    { 96,  0x205c},
    { 97,  0xfe94},
    { 98,  0x1c92},
    { 99,  0xf948},
    { 112, 0x205c},
    { 113, 0xfe81},
    { 114, 0x1be6},
    { 115, 0xf947},
    { 161, 0x0000},
    { 162, 0x0000},
    { 169, 0x0000},
    { 170, 0x0000},
    { 171, 0x0000},
    { 172, 0x0000},
    { 203, 0x2222},
    {0, 0}
};

static WLAN_SROM_ENTRY wlan_patch_common_963168XH5[] = {
    { 66,  0x3200},
    { 67,  0x8000},
    { 78,  0x0300},
    { 87,  0x031f},
    { 88,  0x033f},
    { 93,  0x0202},
    { 100, 0x4060},
    { 101, 0x6060},
    { 102, 0xFE87},
    { 103, 0x1E80},
    { 104, 0xF8C9},
    { 108, 0xFE88},
    { 109, 0x1E56},
    { 110, 0xF8D5},
    { 116, 0x4060},
    { 117, 0x6060},
    { 118, 0xFE88},
    { 119, 0x1E56},
    { 120, 0xF8D5},
    { 124, 0xFE9B},
    { 125, 0x1A62},
    { 126, 0xFA58},
    { 161, 0x0000},
    { 162, 0x0000},
    { 169, 0x0000},
    { 170, 0x0000},
    { 171, 0x0000},
    { 172, 0x0000},
    { 203, 0x2222},
    {0, 0}
};

#endif

#if defined(_BCM96828_) || defined(CONFIG_BCM96828)
/* The unique part contains the subSytemId (boardId) and the BoardRev number */
static WLAN_SROM_ENTRY wlan_patch_unique_96828MBV[] = {
    {65, 0x1230},
    {0, 0}
};

static WLAN_SROM_ENTRY wlan_patch_unique_96828BU[] = {
    {65, 0x1230},
    {0, 0}
};

/* The common part contains the entries that are valid for multiple boards */
static WLAN_SROM_ENTRY wlan_patch_common_96828MBV[] = {
    { 78,  0x0303}, 
    { 79,  0x0202}, 
    { 80,  0xff02},
    { 87,  0x0315}, 
    { 88,  0x0315},
    { 96,  0x2040}, 
    { 97,  0xFFB5}, 
    { 98,  0x175F},
    { 99,  0xFB29},
    { 112, 0x2040},
    { 113, 0xFFD7},
    { 114, 0x17D6},
    { 115, 0xFB67},
    {0, 0}
};

#endif
//<< Add AR-5387un profile
#if defined(_BCM96328_) || defined(CONFIG_BCM96328)
static WLAN_SROM_ENTRY wlan_patch_unique_96328A1441N1[] = {
	{ 2,  0x05BB},
	{ 65,  0x1204},
    {0, 0}
};
// << Jimmy.Lin : For AR-5381u
static WLAN_SROM_ENTRY wlan_patch_unique_96328AT_1341N2[] = {
    { 97,  0xfea2},
    { 98, 0x16ef},
    { 99,  0xfa77},
    { 113, 0xfecc},
    { 114, 0x1752},
    { 115, 0xfa9a},
    {0, 0}
};
// >> Jimmy.Lin : For AR-5381u
//<< David Rodriguez: Add AR-5381u "JAZ" board, 2014-03-13
static WLAN_SROM_ENTRY wlan_patch_unique_96328A_1241N[] = {
    {97,  0xfed6},
    {98,  0x172e},
    {99,  0xfaab},
    {113, 0xfecc},
    {114, 0x1665},
    {115, 0xfaac},
    {0, 0}
};
//>> End: Add AR-5381u "JAZ" board
static WLAN_SROM_ENTRY wlan_patch_common_96328A1441N1[] = {
    { 78,  0x0303}, 
    { 79,  0x0202}, 
    { 80,  0xff02},
    { 87,  0x0315}, 
    { 88,  0x0315},
    { 96,  0x2048}, 
    { 97,  0xFF11}, 
    { 98,  0x1567},
    { 99,  0xFB24},
    { 100, 0x3E3C},
    { 101, 0x4038},
    { 102, 0xFE7F},
    { 103, 0x1279},
    { 112, 0x2048},
    { 113, 0xFF03},
    { 114, 0x154C},
    { 115, 0xFB27},
    { 116, 0x3E3C},
    { 117, 0x4038},
    { 118, 0xFE87},
    { 119, 0x1233},
    { 203, 0x2226},
	{	0,		0}
};
// << Jimmy.Lin : For AR-5381u
static WLAN_SROM_ENTRY wlan_patch_common_96328CT[] = {
    {0, 0}
};
// >> Jimmy.Lin : For AR-5381u
//<< David Rodriguez: Add AR-5381u "JAZ" board, 2014-03-13
static WLAN_SROM_ENTRY wlan_patch_common_96328A_1241N[] = {
    {0, 0}
};
//>> End: Add AR-5381u "JAZ" board
#endif
//>> End, Add AR-5387un Profile 
//<< Add AR-5310 profile
#if defined(_BCM96318_) || defined(CONFIG_BCM96318)
static WLAN_SROM_ENTRY wlan_patch_unique_96318AT1341N1[] = {
    { 97,  0xFE7C}, 
    { 98,  0x18A7},
    { 99,  0xFA15},
    { 113, 0xFE7C},
    { 114, 0x18DF},
    { 115, 0xFA19},
    {0, 0}
};
static WLAN_SROM_ENTRY wlan_patch_common_96318AT1341N1[] = {
	{	0,		0}
};
static WLAN_SROM_ENTRY wlan_patch_unique_96318AT1341N4[] = {
    { 2,   0x062b},
    { 65,  0x1204}, 
    { 66,  0x1200}, 
    { 67,  0x8000}, 
    { 68,  0x1800}, 
//    { 76,  0x83ff},
    { 87,  0x041f}, 
    { 93,  0x0002}, 
    { 96,  0x2068}, 
    { 97,  0xFeb9},
    { 98,  0x1c66},
    { 99,  0xFa0b},
    { 112, 0x2068}, 
    { 113, 0xfe78},
    { 114, 0x1bea},
    { 115, 0xF9c3},
    { 162, 0x4444},
    { 170, 0x4444},
    { 172, 0x4444},
    {0, 0}
};
static WLAN_SROM_ENTRY wlan_patch_common_96318AT1341N4[] = {
	{	0,		0}
};

//<< jojopo : Wireless PA for 6318 , 2013/11/07
static WLAN_SROM_ENTRY wlan_patch_unique_96318A1441N1[] = {
   {   0,      0}
};
static WLAN_SROM_ENTRY wlan_patch_common_96318A[] = {
    { 97,  0xFE55},
    { 98,  0x171D},
    { 99,  0xFA42},
    { 113, 0xFEB7},
    { 114, 0x18CD},
    { 115, 0xFA4F},
    {   0,      0}
};
//>> jojopo : end
#endif
//>> End, Add AR-5310 Profile 
static WLAN_SROM_ENTRY wlan_patch_LAST[] = {
    {0, 0}
};

/* this data structure could be moved to boardparams structure in the future */
/* does not require to rebuild cfe here if more srom entries are needed */
static WLAN_SROM_PATCH_INFO wlanPaInfo[]={
#if defined(_BCM96362_) || defined(CONFIG_BCM96362)
    {"96362ADVNX",    0x6362, 220, wlan_patch_unique_96362ADVNX,    wlan_patch_common_96362ADVNX},
    {"96362ADVNgr2",  0x6362, 220, wlan_patch_unique_96362ADVNgr2,  wlan_patch_common_96362ADVNgr2},
    {"963629epon",    0x6362, 220, wlan_patch_unique_963629epon,    wlan_patch_common_96362ADVNgr2},
    {"96361XF",       0x6362, 220, wlan_patch_unique_96361XF,       wlan_patch_common_96361XF},
    {"96362RAVNGR2",  0x6362, 220, wlan_patch_unique_96362RAVNGR2,  wlan_patch_common_96362ADVNgr2},
    {"96362ADVN2xh",  0x6362, 220, wlan_patch_unique_96362ADVN2xh,  wlan_patch_common_96362ADVN2xh},
    {"96362ADVN2XM",  0x6362, 220, wlan_patch_unique_96362ADVN2XM,  wlan_patch_common_96362ADVN2XM},
    {"96362RADVN2XH", 0x6362, 220, wlan_patch_unique_96362RADVN2XH, wlan_patch_common_96362ADVN2xh},
    {"96362RADVNXH5", 0x6362, 220, wlan_patch_unique_96362RADVNXH5, wlan_patch_common_96362RADVNXH5},
#endif
// << Jimmy.Lin : For AR-5381u
#if defined(_BCM96328_) || defined(CONFIG_BCM96328)
    {"96328AT-1341N2",   43225, 220,wlan_patch_unique_96328AT_1341N2,wlan_patch_common_96328CT},
#endif
// >> Jimmy.Lin : For AR-5381u
//<< David Rodriguez: Add AR-5381u "JAZ" board, 2014-03-13
#if defined(_BCM96328_) || defined(CONFIG_BCM96328)
    {"96328A-1241N", 43225, 115, wlan_patch_unique_96328A_1241N, wlan_patch_common_96328A_1241N},
#endif
//>> End: Add AR-5381u "JAZ" board
#if defined(_BCM963268_) || defined(CONFIG_BCM963268)
    {"963168VB-1441N",0x6362, 220, wlan_patch_unique_963268VB,     wlan_patch_common_963268MBV}, //for NL-3110u
    {"963168MB-1461N",0x6362, 220, wlan_patch_unique_963268VB,     wlan_patch_common_963268MBV}, //for NL-3110u
    {"963268MBV",     0x6362, 220, wlan_patch_unique_963268MBV,     wlan_patch_common_963268MBV},
    {"963168MBV_17A", 0x6362, 220, wlan_patch_unique_963268MBV,     wlan_patch_common_963268MBV},
    {"963168MBV_30A", 0x6362, 220, wlan_patch_unique_963268MBV,     wlan_patch_common_963268MBV},
    {"963168MBV3",    0x6362, 220, wlan_patch_unique_963268MBV,     wlan_patch_common_963268MBV},
    {"963168MBV17A302",0x6362, 220, wlan_patch_unique_963268MBV,     wlan_patch_common_963268MBV},
    {"963168MBV30A302",0x6362, 220, wlan_patch_unique_963268MBV,     wlan_patch_common_963268MBV},
    {"963268V30A",    0x6362, 220, wlan_patch_unique_963268V30A,    wlan_patch_common_963268MBV},
    {"963268BU",      0x6362, 220, wlan_patch_unique_963268BU,      wlan_patch_common_963268MBV},
    {"963268BU_P300", 0x6362, 220, wlan_patch_unique_963268BU,      wlan_patch_common_963268MBV},
    {"963168XH",      0x6362, 220, wlan_patch_unique_963168XH,      wlan_patch_common_963168XH},
    {"963168XM",      0x6362, 220, wlan_patch_unique_963168XM,      wlan_patch_common_963168XM},
    {"963168XH5",     0x6362, 220, wlan_patch_unique_963168XH5,     wlan_patch_common_963168XH5},
//<< Charles Wei: Correction for wrong SROM patch which caused poor wireless performance for VR-3031u
    {"963168M-1341N1",     0x6362, 220, wlan_patch_unique_1341N1,     wlan_patch_common_963268MBV}, //for VR-3031u
//>> Charles Wei: End, Correction for wrong SROM patch which caused poor wireless performance for VR-3031u
    {"963168M-1441N3",     0x6362, 220, wlan_patch_unique_1341N1,     wlan_patch_common_963268MBV}, //for VR-3036u
    {"963168M-1441N2",     0x6362, 220, wlan_patch_unique_1341N1,     wlan_patch_common_963268MBV}, //for VR-3031eu
// << kewei lai for add new boardid 963169R-1861AC to WAP-5892u  
	/*for wifi srom table*/
    {"963169R-1861AC",	 0x6362, 220, wlan_patch_unique_1861AC, wlan_patch_common_963268MBV}, 
    {"963169R-1861AC",	 0x4360, 220, wlan_patch_unique_1861AC_4360, wlan_patch_common_1861AC_4360}, 
// >> kewei lai for add new boardid 963169R-1861AC to WAP-5892u  
#endif

#if defined(_BCM96828_) || defined(CONFIG_BCM96828)
    {"96828MBV",     0x6362, 220, wlan_patch_unique_96828MBV,       wlan_patch_common_96828MBV},
    {"96828BU",      0x6362, 220, wlan_patch_unique_96828BU,        wlan_patch_common_96828MBV},
#endif
//<< Add AR-5387un profile
#if defined(_BCM96328_) || defined(CONFIG_BCM96328)
    {"96328A-1441N1",   43225, 115, wlan_patch_unique_96328A1441N1, wlan_patch_common_96328A1441N1}, //for AR-5387
#endif
//>> End, Add AR-5387un Profile 
//<< Add AR-5310 profile
#if defined(_BCM96318_) || defined(CONFIG_BCM96318)
    {"96318AT-1341N1",   43217, 220, wlan_patch_unique_96318AT1341N1, wlan_patch_common_96318AT1341N1}, //for AR-5310
    {"96318AT-1341N3",   43217, 220, wlan_patch_unique_96318AT1341N1, wlan_patch_common_96318AT1341N1}, //for AR-5310
    {"96318AT-1341N4",   43217, 220, wlan_patch_unique_96318AT1341N4, wlan_patch_common_96318AT1341N4}, //for AR-5310u
    {"96318AT-1341N5",   43217, 220, wlan_patch_unique_96318AT1341N4, wlan_patch_common_96318AT1341N4}, //for AR-5310u
//<< jojopo : Wireless PA for 6318 , 2013/11/07
    {"96318A-1441N1",   43217, 115, wlan_patch_unique_96318A1441N1, wlan_patch_common_96318A},
//>> jojopo : end

#endif
//>> End, Add AR-5310 Profile 
    {"", 0, 0, wlan_patch_LAST, wlan_patch_LAST}, /* last entry*/
      
};

/**************************************************************************
* Name       : BpUpdateWirelessSromMap
*
* Description: This function patch wireless PA values
*
* Parameters : [IN] unsigned short chipID
*              [IN/OUT] unsigned short* pBase - base of srom map
*              [IN/OUT] int size - size of srom map
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_VALUE_NOT_DEFINED - At least one return value is not defined
*                  for the board.
***************************************************************************/
int BpUpdateWirelessSromMap(unsigned short chipID, unsigned short* pBase, int sizeInWords)
{
    int nRet = BP_BOARD_ID_NOT_FOUND;
    int i = 0;
    int j = 0;

    if(chipID == 0 || pBase == 0 || sizeInWords <= 0 )
        return nRet;

    i = 0;
    while ( wlanPaInfo[i].szboardId[0] != 0 ) {
        /* check boardId */
        if ( !bpstrcmp(g_pCurrentBp[0].u.cp, wlanPaInfo[i].szboardId) ) {
            /* check chipId */
            if ( (wlanPaInfo[i].usWirelessChipId == chipID) && (wlanPaInfo[i].usNeededSize <= sizeInWords) ){

                /* valid , patch common to multiple boards entry */
                while ( wlanPaInfo[i].commonEntries[j].wordOffset != 0) {
                    pBase[wlanPaInfo[i].commonEntries[j].wordOffset] = wlanPaInfo[i].commonEntries[j].value;
                    j++;
                }

                j = 0;
                /* valid , patch board specific entry */
                while ( wlanPaInfo[i].uniqueEntries[j].wordOffset != 0) {
                    pBase[wlanPaInfo[i].uniqueEntries[j].wordOffset] = wlanPaInfo[i].uniqueEntries[j].value;
                    j++;
                }

                nRet = BP_SUCCESS;
                goto srom_update_done;
            }
        }
        i++;
    }

srom_update_done:

    return( nRet );

} /* BpUpdateWirelessSromMap */


static WLAN_PCI_PATCH_INFO wlanPciInfo[]={
#if defined(_BCM96362_) || defined(CONFIG_BCM96362)
    /* this is the patch to boardtype(boardid) for internal PA */
    {"96362ADVNX", 0x435f14e4, 64,
    {{"subpciids", 11, 0x53614e4},
    {"",       0,      0}}},
    /* this is the patch to boardtype(boardid) for 96362ADVNgr2 */
    {"96362ADVNgr2", 0x435f14e4, 64,
    {{"subpciids", 11, 0x58014e4},
    {"",       0,      0}}},
    /* this is the patch to boardtype(boardid) for 96362ADVN2xh */
    {"96362ADVN2xh", 0x435f14e4, 64,
    {{"subpciids", 11, 0x5a614e4},
    {"",       0,      0}}},
    /* this is the patch to boardtype(boardid) for 96361XF */
    {"96361XF", 0x435f14e4, 64,
    {{"subpciids", 11, 0x5b814e4},
    {"",       0,      0}}},
    /* this is the patch to boardtype(boardid) for 96361I2 */
    {"96361I2", 0x435f14e4, 64,
    {{"subpciids", 11, 0x5e514e4},
    {"",       0,      0}}},
    /* this is the patch to boardtype(boardid) for 96362RAVNGR2 */
    {"96362RAVNGR2", 0x435f14e4, 64,
    {{"subpciids", 11, 0x60d14e4},
    {"",       0,      0}}},
    /* this is the patch to boardtype(boardid) for 96362ADVN2XM */
    {"96362ADVN2XM", 0x435f14e4, 64,
    {{"subpciids", 11, 0x5d414e4},
    {"",       0,      0}}},
    /* this is the patch to boardtype(boardid) for 96362RADVNXH5 */
    {"96362RADVNXH5", 0x435f14e4, 64,
    {{"subpciids", 11, 0x63F14e4},
    {"",       0,      0}}},
    /* this is the patch to boardtype(boardid) for 96362RADVN2XH */
    {"96362RADVN2XH", 0x435f14e4, 64,
    {{"subpciids", 11, 0x63E14e4},
    {"",       0,      0}}},
#endif
#if defined(_BCM963268_) || defined(CONFIG_BCM963268)
    /* this is the patch to boardtype(boardid) for 63268MBV */
    {"963268MBV", 0x435f14e4, 64,
    {{"subpciids", 11, 0x5BB14e4},
    {"",       0,      0}}},
    /* this is the patch to boardtype(boardid) for 963168MBV_17A */
    {"963168MBV_17A", 0x435f14e4, 64,
    {{"subpciids", 11, 0x5BB14e4},
    {"",       0,      0}}},
    /* this is the patch to boardtype(boardid) for 963168MBV_30A */
    {"963168MBV_30A", 0x435f14e4, 64,
    {{"subpciids", 11, 0x5BB14e4},
    {"",       0,      0}}},
    /* this is the patch to boardtype(boardid) for 963168MBV3 */
    {"963168MBV3", 0x435f14e4, 64,
    {{"subpciids", 11, 0x5BB14e4},
    {"",       0,      0}}},
    /* this is the patch to boardtype(boardid) for 963168MBV17A302 */
    {"963168MBV17A302", 0x435f14e4, 64,
    {{"subpciids", 11, 0x5BB14e4},
    {"",       0,      0}}},
    /* this is the patch to boardtype(boardid) for 963168MBV30A302 */
    {"963168MBV30A302", 0x435f14e4, 64,
    {{"subpciids", 11, 0x5BB14e4},
    {"",       0,      0}}},
    /* this is the patch to boardtype(boardid) for 963268V30A */
    {"963268V30A", 0x435f14e4, 64,
    {{"subpciids", 11, 0x5E714e4},
    {"",       0,      0}}},
    /* this is the patch to boardtype(boardid) for 63268BU */
    {"63268BU", 0x435f14e4, 64,
    {{"subpciids", 11, 0x5A714e4},
    {"",       0,      0}}},
    /* this is the patch to boardtype(boardid) for 963168VX */
    {"963168VX", 0x435f14e4, 64,
    {{"subpciids", 11, 0x5A814e4},
    {"",       0,      0}}},
    /* this is the patch to boardtype(boardid) for 963168VX_P300 */
    {"963168VX_P300", 0x435f14e4, 64,
    {{"subpciids", 11, 0x5A814e4},
    {"",       0,      0}}},    
    /* this is the patch to boardtype(boardid) for 963168VX_P400 */
    {"963168VX_P400", 0x435f14e4, 64,
    {{"subpciids", 11, 0x5A814e4},
    {"",       0,      0}}},    
    /* this is the patch to boardtype(boardid) for 63168XH */
    {"963168XH", 0x435f14e4, 64,
    {{"subpciids", 11, 0x5E214e4},
    {"",       0,      0}}},
    /* this is the patch to boardtype(boardid) for 63168XM */
    {"963168XM", 0x435f14e4, 64,
    {{"subpciids", 11, 0x61f14e4},
    {"",       0,      0}}},
    /* this is the patch to boardtype(boardid) for 963168XH5 */
    {"963168XH5", 0x435f14e4, 64,
    {{"subpciids", 11, 0x64014e4},
    {"",       0,      0}}},
//<< Charles Wei: Correction for wrong SROM patch which caused poor wireless performance for VR-3031u
    /* this is the patch to boardtype(boardid) for 963168M-1341N1 */
    {"963168M-1341N1", 0x435f14e4, 64,
    {{"subpciids", 11, 0x5BB14e4},
    {"",       0,      0}}},
//>> Charles Wei: End, Correction for wrong SROM patch which caused poor wireless performance for VR-3031u
//>> Charles Wei, end
#endif
    {"",                 0, 0, {{"",       0,      0}}}, /* last entry*/
};

/**************************************************************************
* Name       : BpUpdateWirelessPciConfig
*
* Description: This function patch wireless PCI Config Header
*              This is not functional critial/necessary but for dvt database maintenance
*
* Parameters : [IN] unsigned int pciID
*              [IN/OUT] unsigned int* pBase - base of pci config header
*              [IN/OUT] int sizeInDWords - size of pci config header
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_VALUE_NOT_DEFINED - At least one return value is not defined
*                  for the board.
***************************************************************************/
int BpUpdateWirelessPciConfig (unsigned long pciID, unsigned long* pBase, int sizeInDWords)
{
    int nRet = BP_BOARD_ID_NOT_FOUND;
    int i = 0;
    int j = 0;

    if(pciID == 0 || pBase == 0 || sizeInDWords <= 0 )
        return nRet;

    i = 0;
    while ( wlanPciInfo[i].szboardId[0] != 0 ) {
        /* check boardId */
        if ( !bpstrcmp(g_pCurrentBp[0].u.cp, wlanPciInfo[i].szboardId) ) {
            /* check pciId */
            if ( (wlanPciInfo[i].usWirelessPciId == pciID) && (wlanPciInfo[i].usNeededSize <= sizeInDWords) ){
                /* valid , patch entry */
                while ( wlanPciInfo[i].entries[j].name[0] ) {
                    pBase[wlanPciInfo[i].entries[j].dwordOffset] = wlanPciInfo[i].entries[j].value;
                    j++;
                }
                nRet = BP_SUCCESS;
                goto pciconfig_update_done;
            }
        }
        i++;
    }

pciconfig_update_done:

    return( nRet );

}

/**************************************************************************
* Name       : BpGetWanDataLedGpio
*
* Description: This function returns the GPIO pin assignment for the WAN Data
*              LED.
*
* Parameters : [OUT] pusValue - Address of short word that the WAN Data LED
*                  GPIO pin is returned in.
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - At least one return value is not defined
*                  for the board.
***************************************************************************/
int BpGetWanDataLedGpio( unsigned short *pusValue )
{
    return( BpGetGpio(bp_usGpioLedWanData, pusValue ) );
} /* BpGetWanDataLedGpio */

/**************************************************************************
* Name       : BpGetWanErrorLedGpio
*
* Description: This function returns the GPIO pin assignment for the WAN
*              LED that is used when there is a WAN connection failure.
*
* Parameters : [OUT] pusValue - Address of short word that the WAN LED
*                  GPIO pin is returned in.
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - At least one return value is not defined
*                  for the board.
***************************************************************************/
int BpGetWanErrorLedGpio( unsigned short *pusValue )
{
    return( BpGetGpio(bp_usGpioLedWanError, pusValue ) );
} /* BpGetWanErrorLedGpio */

/**************************************************************************
* Name       : BpGetBootloaderPowerOnLedGpio
*
* Description: This function returns the GPIO pin assignment for the power
*              on LED that is set by the bootloader.
*
* Parameters : [OUT] pusValue - Address of short word that the alarm LED
*                  GPIO pin is returned in.
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - At least one return value is not defined
*                  for the board.
***************************************************************************/
int BpGetBootloaderPowerOnLedGpio( unsigned short *pusValue )
{
    return( BpGetGpio(bp_usGpioLedBlPowerOn, pusValue ) );
} /* BpGetBootloaderPowerOn */

/**************************************************************************
* Name       : BpGetBootloaderStopLedGpio
*
* Description: This function returns the GPIO pin assignment for the break
*              into bootloader LED that is set by the bootloader.
*
* Parameters : [OUT] pusValue - Address of short word that the break into
*                  bootloader LED GPIO pin is returned in.
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - At least one return value is not defined
*                  for the board.
***************************************************************************/
int BpGetBootloaderStopLedGpio( unsigned short *pusValue )
{
    return( BpGetGpio(bp_usGpioLedBlStop, pusValue ) );
} /* BpGetBootloaderStopLedGpio */

/**************************************************************************
* Name       : BpGetVoipLedGpio
*
* Description: This function returns the GPIO pin assignment for the VOIP
*              LED.
*
* Parameters : [OUT] pusValue - Address of short word that the VOIP LED
*                  GPIO pin is returned in.
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - At least one return value is not defined
*                  for the board.
*
* Note       : The VoIP structure would allow for having one LED per DSP
*              however, the board initialization function assumes only one
*              LED per functionality (ie one LED for VoIP).  Therefore in
*              order to keep this tidy and simple we do not make usage of the
*              one-LED-per-DSP function.  Instead, we assume that the LED for
*              VoIP is unique and associated with DSP 0 (always present on
*              any VoIP platform).  If changing this to a LED-per-DSP function
*              then one need to update the board initialization driver in
*              bcmdrivers\opensource\char\board\bcm963xx\impl1
***************************************************************************/
int BpGetVoipLedGpio( unsigned short *pusValue )
{
    return( BpGetGpio(bp_usGpioLedVoip, pusValue ) );
} /* BpGetVoipLedGpio */

/**************************************************************************
* Name       : BpGetVoip1LedGpio
*
* Description: This function returns the GPIO pin assignment for the VoIP1.
*              LED which is used when FXS0 is active
* Parameters : [OUT] pusValue - Address of short word that the VoIP1
*                  GPIO pin is returned in.
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - At least one return value is not defined
*                  for the board.
***************************************************************************/
int BpGetVoip1LedGpio( unsigned short *pusValue )
{
    return( BpGetGpio(bp_usGpioVoip1Led, pusValue ) );
} /* BpGetVoip1LedGpio */

/**************************************************************************
* Name       : BpGetVoip1FailLedGpio
*
* Description: This function returns the GPIO pin assignment for the VoIP1
*              Fail LED which is used when there's an error with FXS0
* Parameters : [OUT] pusValue - Address of short word that the VoIP1
*                  GPIO pin is returned in.
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - At least one return value is not defined
*                  for the board.
***************************************************************************/
int BpGetVoip1FailLedGpio( unsigned short *pusValue )
{
    return( BpGetGpio(bp_usGpioVoip1LedFail, pusValue ) );
} /* BpGetVoip1FailLedGpio */

/**************************************************************************
* Name       : BpGetVoip2LedGpio
*
* Description: This function returns the GPIO pin assignment for the VoIP2.
*              LED which is used when FXS1 is active
* Parameters : [OUT] pusValue - Address of short word that the VoIP2
*                  GPIO pin is returned in.
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - At least one return value is not defined
*                  for the board.
***************************************************************************/
int BpGetVoip2LedGpio( unsigned short *pusValue )
{
    return( BpGetGpio(bp_usGpioVoip2Led, pusValue ) );
} /* BpGetVoip2LedGpio */

/**************************************************************************
* Name       : BpGetVoip2FailLedGpio
*
* Description: This function returns the GPIO pin assignment for the VoIP2
*              Fail LED which is used when there's an error with FXS1
* Parameters : [OUT] pusValue - Address of short word that the VoIP2
*                  GPIO pin is returned in.
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - At least one return value is not defined
*                  for the board.
***************************************************************************/
int BpGetVoip2FailLedGpio( unsigned short *pusValue )
{
    return( BpGetGpio(bp_usGpioVoip2LedFail, pusValue ) );
} /* BpGetVoip2FailLedGpio */

/**************************************************************************
* Name       : BpGetPotsLedGpio
*
* Description: This function returns the GPIO pin assignment for the POTS1.
*              LED which is used when DAA is active
* Parameters : [OUT] pusValue - Address of short word that the POTS11
*                  GPIO pin is returned in.
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - At least one return value is not defined
*                  for the board.
***************************************************************************/
int BpGetPotsLedGpio( unsigned short *pusValue )
{
    return( BpGetGpio(bp_usGpioPotsLed, pusValue ) );
} /* BpGetPotsLedGpio */

/**************************************************************************
* Name       : BpGetDectLedGpio
*
* Description: This function returns the GPIO pin assignment for the DECT.
*              LED which is used when DECT is active
* Parameters : [OUT] pusValue - Address of short word that the DECT
*                  GPIO pin is returned in.
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - At least one return value is not defined
*                  for the board.
***************************************************************************/
int BpGetDectLedGpio( unsigned short *pusValue )
{
    return( BpGetGpio(bp_usGpioDectLed, pusValue ) );
} /* BpGetDectLedGpio */


/**************************************************************************
* Name       : BpGetPassDyingGaspGpio
*
* Description: This function returns the GPIO pin assignment used to pass
*                  a dying gasp interrupt to an external processor.
* Parameters : [OUT] pusValue - Address of short word that the DECT
*                  GPIO pin is returned in.
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - At least one return value is not defined
*                  for the board.
***************************************************************************/
int BpGetPassDyingGaspGpio( unsigned short *pusValue )
{
    return( BpGetGpio(bp_usGpioPassDyingGasp, pusValue ) );
} /* BpGetPassDyingGaspGpio */


/**************************************************************************
* Name       : BpGetFpgaResetGpio
*
* Description: This function returns the GPIO pin assignment for the FPGA
*              Reset signal.
*
* Parameters : [OUT] pusValue - Address of short word that the FPGA Reset
*                  signal GPIO pin is returned in.
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - At least one return value is not defined
*                  for the board.
***************************************************************************/
int BpGetFpgaResetGpio( unsigned short *pusValue ) {
    return( BpGetGpio(bp_usGpioFpgaReset, pusValue ) );
} /*BpGetFpgaResetGpio*/

/**************************************************************************
* Name       : BpGetGponLedGpio
*
* Description: This function returns the GPIO pin assignment for the GPON
*              LED.
*
* Parameters : [OUT] pusValue - Address of short word that the GPON LED
*                  GPIO pin is returned in.
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - At least one return value is not defined
*                  for the board.
***************************************************************************/
int BpGetGponLedGpio( unsigned short *pusValue )
{
    return( BpGetGpio(bp_usGpioLedGpon, pusValue ) );
} /* BpGetGponLedGpio */

/**************************************************************************
* Name       : BpGetGponFailLedGpio
*
* Description: This function returns the GPIO pin assignment for the GPON
*              LED that is used when there is a GPON connection failure.
*
* Parameters : [OUT] pusValue - Address of short word that the GPON LED
*                  GPIO pin is returned in.
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - At least one return value is not defined
*                  for the board.
***************************************************************************/
int BpGetGponFailLedGpio( unsigned short *pusValue )
{
    return( BpGetGpio(bp_usGpioLedGponFail, pusValue ) );
} /* BpGetGponFailLedGpio */

/**************************************************************************
* Name       : BpGetMoCALedGpio
*
* Description: This function returns the GPIO pin assignment for the MoCA
*              LED.
*
* Parameters : [OUT] pusValue - Address of short word that the MoCA LED
*                  GPIO pin is returned in.
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - At least one return value is not defined
*                  for the board.
***************************************************************************/
int BpGetMoCALedGpio( unsigned short *pusValue )
{
    return( BpGetGpio(bp_usGpioLedMoCA, pusValue ) );
} /* BpGetMoCALedGpio */

/**************************************************************************
* Name       : BpGetMoCAFailLedGpio
*
* Description: This function returns the GPIO pin assignment for the MoCA
*              LED that is used when there is a MoCA connection failure.
*
* Parameters : [OUT] pusValue - Address of short word that the MoCA LED
*                  GPIO pin is returned in.
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - At least one return value is not defined
*                  for the board.
***************************************************************************/
int BpGetMoCAFailLedGpio( unsigned short *pusValue )
{
    return( BpGetGpio(bp_usGpioLedMoCAFail, pusValue ) );
} /* BpGetMoCAFailLedGpio */

/**************************************************************************
* Name       : BpGetResetToDefaultExtIntr
*
* Description: This function returns the external interrupt number for the
*              reset to default button.
*
* Parameters : [OUT] pusValue - Address of short word that reset to default
*                  external interrupt is returned in.
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - At least one return value is not defined
*                  for the board.
***************************************************************************/
int BpGetResetToDefaultExtIntr( unsigned short *pusValue )
{
    return( BpGetUs(bp_usExtIntrResetToDefault, pusValue ) );
} /* BpGetResetToDefaultExtIntr */

/**************************************************************************
* Name       : BpGetResetToDefaultExtIntrGpio
*
* Description: This function returns the external interrupt number for the
*              reset to default button.
*
* Parameters : [OUT] pusValue - Address of short word that reset to default
*                  external interrupt is returned in.
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - At least one return value is not defined
*                  for the board.
***************************************************************************/
int BpGetResetToDefaultExtIntrGpio( unsigned short *pusValue )
{
    bp_elem_t *pelem;
    int ret;
    bp_elem_t *start_elem = 0;

    if( !g_pCurrentBp ) 
    {
        *pusValue = BP_NOT_DEFINED;
        ret       = BP_VALUE_NOT_DEFINED;
        return ret;
    }
    
    /* First go to elem with id bp_usExtIntrSesBtnWireless */
    pelem = BpGetElem(bp_usExtIntrResetToDefault, &start_elem, bp_last);
    if (bp_usExtIntrResetToDefault != pelem->id) 
    {
       *pusValue = BP_NOT_DEFINED;
        ret      = BP_VALUE_NOT_DEFINED;
    }
    else
    {
        pelem++;
        /* We should expect the id bp_usGpio_Intr in the next element */
        if (bp_usGpio_Intr != pelem->id)
        {
            *pusValue = BP_NOT_DEFINED;
            ret       = BP_VALUE_NOT_DEFINED;
        }
        else
        {
            *pusValue = pelem->u.us;
            ret       = BP_SUCCESS;            
        }
    }
    
    return( ret );  

} /* BpGetResetToDefaultExtIntrGpio */


/**************************************************************************
* Name       : BpGetWirelessPowerDownGpio
*
* Description: This function returns the GPIO pin assignment for WLAN_PD
*
*
* Parameters : [OUT] pusValue - Address of short word that the WLAN_PD
*                  GPIO pin is returned in.
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - At least one return value is not defined
*                  for the board.
***************************************************************************/
int BpGetWirelessPowerDownGpio( unsigned short *pusValue )
{
    return( BpGetGpio(bp_usGpioWirelessPowerDown, pusValue ) );
} /* usGpioWirelessPowerDown */

/**************************************************************************
* Name       : BpGetDslPhyAfeIds
*
* Description: This function returns the DSL PHY AFE ids for primary and
*              secondary PHYs.
*
* Parameters : [OUT] pulValues-Address of an array of two long words where
*              AFE Id for the primary and secondary PHYs are returned.
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET-Error, BpSetBoardId hasn't been called.
*              BP_VALUE_NOT_DEFINED - No defined AFE Ids.
**************************************************************************/
int BpGetDslPhyAfeIds( unsigned long *pulValues )
{
    int nRet;

    if( g_pCurrentBp )
    {
        if (BpGetUl(bp_ulAfeId0, &pulValues[0]) != BP_SUCCESS) {
          pulValues[0] = BP_AFE_DEFAULT;
        }
        if (BpGetUl(bp_ulAfeId1, &pulValues[1]) != BP_SUCCESS) {
          pulValues[1] = BP_AFE_DEFAULT;
        }
        nRet = BP_SUCCESS;
    }
    else
    {
        pulValues[0] = BP_AFE_DEFAULT;
        pulValues[1] = BP_AFE_DEFAULT;
        nRet = BP_BOARD_ID_NOT_SET;
    }

    return( nRet );
} /* BpGetDslPhyAfeIds */

/**************************************************************************
* Name       : BpGetUart2SdoutGpio
*
* Description: This function returns the GPIO pin assignment for UART2 SDOUT
*
*
* Parameters : [OUT] pusValue - Address of short word that the bp_usGpioUart2Sdout
*                  GPIO pin is returned in.
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - Not defined
***************************************************************************/
int BpGetUart2SdoutGpio( unsigned short *pusValue )
{
    return( BpGetGpio(bp_usGpioUart2Sdout, pusValue ) );
} /* BpGetUart2SdoutGpio */

/**************************************************************************
* Name       : BpGetUart2SdinGpio
*
* Description: This function returns the GPIO pin assignment for UART2 SDIN
*
*
* Parameters : [OUT] pusValue - Address of short word that the bp_usGpioUart2Sdin
*                  GPIO pin is returned in.
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - Not defined
***************************************************************************/
int BpGetUart2SdinGpio( unsigned short *pusValue )
{
    return( BpGetGpio(bp_usGpioUart2Sdin, pusValue ) );
} /* BpGetUart2SdinGpio */

/**************************************************************************
* Name       : BpGetExtAFEResetGpio
*
* Description: This function returns the GPIO pin assignment for resetting the external AFE chip
*
*
* Parameters : [OUT] pusValue - Address of short word that the ExtAFEReset
*                  GPIO pin is returned in.
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - Not defined
***************************************************************************/
int BpGetExtAFEResetGpio( unsigned short *pusValue )
{
    return( BpGetGpio(bp_usGpioExtAFEReset, pusValue ) );
} /* BpGetExtAFEResetGpio */

/**************************************************************************
* Name       : BpGetAFELDRelayGpio
*
* Description: This function returns the GPIO pin assignment for switching LD relay
*
*
* Parameters : [OUT] pusValue - Address of short word that the bp_usGpioAFELDRelay
*                  GPIO pin is returned in.
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - Not defined
***************************************************************************/
int BpGetAFELDRelayGpio( unsigned short *pusValue )
{
    return( BpGetGpio(bp_usGpioAFELDRelay, pusValue ) );
} /* BpGetAFELDRelayGpio */

/**************************************************************************
* Name       : BpGetIntAFELDModeGpio
*
* Description: This function returns the GPIO pin assignment for setting LD Mode to ADSL/VDSL
*                  for the internal path.
*
* Parameters : [OUT] pusValue - Address of short word that the bp_usGpioIntAFELDMode
*                  GPIO pin is returned in.
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - Not defined
***************************************************************************/
int BpGetIntAFELDModeGpio( unsigned short *pusValue )
{
    return( BpGetGpio(bp_usGpioIntAFELDMode, pusValue ) );
} /* BpGetIntAFELDModeGpio */

/**************************************************************************
* Name       : BpGetIntAFELDPwrGpio
*
* Description: This function returns the GPIO pin assignment for turning on/off the internal AFE LD
*
*
* Parameters : [OUT] pusValue - Address of short word that the usGpioExtAFELDPwr
*                  GPIO pin is returned in.
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - Not defined
***************************************************************************/
int BpGetIntAFELDPwrGpio( unsigned short *pusValue )
{
    return( BpGetGpio(bp_usGpioIntAFELDPwr, pusValue ) );
} /* BpGetIntAFELDPwrGpio */

/**************************************************************************
* Name       : BpGetExtAFELDModeGpio
*
* Description: This function returns the GPIO pin assignment for setting LD Mode to ADSL/VDSL
*                  for the external path.
*
* Parameters : [OUT] pusValue - Address of short word that the usGpioExtAFELDMode
*                  GPIO pin is returned in.
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - Not defined
***************************************************************************/
int BpGetExtAFELDModeGpio( unsigned short *pusValue )
{
    return( BpGetGpio(bp_usGpioExtAFELDMode, pusValue ) );
} /* BpGetExtAFELDModeGpio */

/**************************************************************************
* Name       : BpGetExtAFELDPwrGpio
*
* Description: This function returns the GPIO pin assignment for turning on/off the external AFE LD
*
*
* Parameters : [OUT] pusValue - Address of short word that the usGpioExtAFELDPwr
*                  GPIO pin is returned in.
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - Not defined
***************************************************************************/
int BpGetExtAFELDPwrGpio( unsigned short *pusValue )
{
    return( BpGetGpio(bp_usGpioExtAFELDPwr, pusValue ) );
} /* BpGetExtAFELDPwrGpio */

/**************************************************************************
* Name       : BpGetExtAFELDDataGpio
*
* Description: This function returns the GPIO pin assignment for sending config data to the external AFE LD
*
*
* Parameters : [OUT] pusValue - Address of short word that the bp_usGpioExtAFELDData
*                  GPIO pin is returned in.
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - Not defined
***************************************************************************/
int BpGetExtAFELDDataGpio( unsigned short *pusValue )
{
    return( BpGetGpio(bp_usGpioExtAFELDData, pusValue ) );
} /* BpGetExtAFELDDataGpio */

/**************************************************************************
* Name       : BpGetExtAFELDClkGpio
*
* Description: This function returns the GPIO pin assignment for sending the clk to the external AFE LD
*
*
* Parameters : [OUT] pusValue - Address of short word that the bp_usGpioExtAFELDClk
*                  GPIO pin is returned in.
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - Not defined
***************************************************************************/

int BpGetExtAFELDClkGpio( unsigned short *pusValue )
{
    return( BpGetGpio(bp_usGpioExtAFELDClk, pusValue ) );
} /* BpGetExtAFELDClkGpio */

/**************************************************************************
* Name       : BpGet6829PortInfo
*
* Description: This function checks the ENET MAC info to see if a 6829
*              is connected
*
* Parameters : [OUT] portInfo6829 - 0 if 6829 is not present
*                                 - 6829 port information otherwise
*
* Returns    : BP_SUCCESS           - Success, value is returned.
*              BP_BOARD_ID_NOT_SET  - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - Not defined
***************************************************************************/
int BpGet6829PortInfo( unsigned char *portInfo6829 )
{
   ETHERNET_MAC_INFO enetMacInfo;
   ETHERNET_SW_INFO *pSwInfo;
   int               retVal;
   int               i;

   *portInfo6829 = 0;
   retVal = BpGetEthernetMacInfo( &enetMacInfo, 1 );
   if ( BP_SUCCESS == retVal ) {
      pSwInfo = &enetMacInfo.sw;
      for (i = 0; i < BP_MAX_SWITCH_PORTS; i++) {
         if ( ((pSwInfo->phy_id[i] & PHYID_LSBYTE_M) != 0xFF) &&
              ((pSwInfo->phy_id[i] & PHYID_LSBYTE_M) &  0x80) ) {
            *portInfo6829 = pSwInfo->phy_id[i] & PHYID_LSBYTE_M;
            retVal        = BP_SUCCESS;
            break;
         }
      }
   }

   return retVal;

}

/**************************************************************************
* Name       : BpGetEthSpdLedGpio
*
* Description: This function returns the GPIO pin assignment for the
*              specified port and link speed 
*
* Parameters : [IN] port - Internal phy number
*              [IN] enetIdx - index for Ethernet MAC info
*              [IN] ledIdx - 0 -> duplex GPIO
*                          - 1 -> spd 100 GPIO
*                          - 2 -> spd 1000 GPIO
*              [OUT] pusValue - Address of a short word to store the GPIO
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - At least one return value is not defined
*                  for the board.
***************************************************************************/
int BpGetEthSpdLedGpio( unsigned short port, unsigned short enetIdx,
                        unsigned short ledIdx, unsigned short *pusValue )
{
    ETHERNET_MAC_INFO enetMacInfos[BP_MAX_ENET_MACS];
    unsigned short *pShort;
    int nRet;

    if( g_pCurrentBp ) {
        nRet = BpGetEthernetMacInfo( enetMacInfos, BP_MAX_ENET_MACS );

        if ((enetIdx >= BP_MAX_ENET_MACS) ||
            (port >= BP_MAX_ENET_INTERNAL) ||
            (enetMacInfos[enetIdx].ucPhyType == BP_ENET_NO_PHY)) {
           *pusValue = BP_NOT_DEFINED;
           nRet = BP_VALUE_NOT_DEFINED;
        } else {
           pShort   = &enetMacInfos[enetIdx].sw.ledInfo[port].duplexLed;
           pShort   += ledIdx;
           *pusValue = *pShort;
           if( *pShort == BP_NOT_DEFINED ) {
               nRet = BP_VALUE_NOT_DEFINED;
           } else {
               nRet = BP_SUCCESS;
           }
        }
    } else {
        *pusValue = BP_NOT_DEFINED;
        nRet = BP_BOARD_ID_NOT_SET;
    }

    return( nRet );
} /* BpGetEthSpdLedGpio */


/**************************************************************************
* Name       : BpGetLaserDisGpio
*
* Description: This function returns the GPIO pin assignment for disabling
*              the laser
*
* Parameters : [OUT] pusValue - Address of short word that the usGpioLaserDis
*                  GPIO pin is returned in.
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - Not defined
***************************************************************************/
int BpGetLaserDisGpio( unsigned short *pusValue )
{
    return( BpGetGpio(bp_usGpioLaserDis, pusValue ) );
} /* BpGetLaserDisGpio */


/**************************************************************************
* Name       : BpGetLaserTxPwrEnGpio
*
* Description: This function returns the GPIO pin assignment for enabling
*              the transmit power of the laser
*
* Parameters : [OUT] pusValue - Address of short word that the usGpioLaserTxPwrEn
*                  GPIO pin is returned in.
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - Not defined
***************************************************************************/
int BpGetLaserTxPwrEnGpio( unsigned short *pusValue )
{
    return( BpGetGpio(bp_usGpioLaserTxPwrEn, pusValue ) );
} /* BpGetLaserTxPwrEnGpio */

/**************************************************************************
* Name       : BpGetLaserResetGpio
*
* Description: This function returns the GPIO pin assignment for resetting
* the optical module
*
* Parameters : [OUT] pusValue - Address of short word that the bp_usGpioLaserReset
*                  GPIO pin is returned in.
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - Not defined
***************************************************************************/
int BpGetLaserResetGpio( unsigned short *pusValue )
{
    return( BpGetUs(bp_usGpioLaserReset, pusValue ) );
} /* BpGetLaserResetGpio */

/**************************************************************************
* Name       : BpGetVregSel1P2
*
* Description: This function returns the desired voltage level for 1V2
*
* Parameters : [OUT] pusValue - Address of short word that the 1V2 level
*                  is returned in.
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - Not defined
***************************************************************************/
int BpGetVregSel1P2( unsigned short *pusValue )
{
    return( BpGetUs(bp_usVregSel1P2, pusValue ) );
} /* BpGetVregSel1P2 */

/**************************************************************************
* Name       : BpGetVreg1P8
*
* Description: This function returns the desired state for 1P8 regulator
*
* Parameters : [OUT] pucValue - Address of unsigned char where to return
*                               whether 1P8 regulator is external or not
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - Not defined
***************************************************************************/
int BpGetVreg1P8( unsigned char *pucValue )
{
    return( BpGetUc(bp_ucVreg1P8, pucValue ) );
} /* BpGetVreg1P8 */

/**************************************************************************
* Name       : BpGetGponOpticsType
*
* Description: This function returns an indication of whether the current 
*              board type supports GPON legacy or BOSA optics.
*
* Parameters : [Out] pusValue
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_VALUE_NOT_DEFINED - Not defined
***************************************************************************/
int BpGetGponOpticsType( unsigned short *pusValue )
{
    return ( BpGetUs (bp_usGponOpticsType, pusValue));
} /* BpGetGponOpticsType */


#if !defined(_CFE_)
/**************************************************************************
* Name       : BpGetDefaultOpticalParams
*
* Description: This function returns the optical params for BOSA optics if
*              they exist.  These are only used if they do not exist in NVRAM.
*
* Parameters : [OUT] pOpticalParams - Address of a buffer that the optical
*              params are returned in.
*
* Returns    : BP_SUCCESS - Success, value is returned.
***************************************************************************/
int BpGetDefaultOpticalParams( unsigned char *pOpticalParams )
{
    int Index, Ret;    
    unsigned char * pBpOpticalParams = (unsigned char *)0;


    if (BP_SUCCESS == (Ret = BpGetCp (bp_cpDefaultOpticalParams, (char**)&pBpOpticalParams)))
    {
        for (Index = 0; Index < BP_OPTICAL_PARAMS_LEN; Index++)
        {
            pOpticalParams[Index] = pBpOpticalParams[Index];
        }
    }

    return (Ret);

} /* BpGetDefaultOpticalParams */


/**************************************************************************
* Name       : BpGetI2cGpios
*
* Description: This function returns the GPIO pin assignments for the I2C
*              clock (SCL) and data (SDA).
*
* Parameters : [OUT] pusScl - Address of short word that the SCL GPIO pin
*                  is returned in.
*              [OUT] pusSda - Address of short word that the SDA GPIO pin
*                  pin is returned in.
*
* Returns    : BP_SUCCESS - Success, values are returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - At least one return value is not defined
*                  for the board.
***************************************************************************/
int BpGetI2cGpios( unsigned short *pusScl, unsigned short *pusSda )
{
    int ret;

    *pusScl = *pusSda = BP_NOT_DEFINED;
    if( (ret = BpGetGpio (bp_usGpioI2cScl, pusScl)) == BP_SUCCESS )
        ret = BpGetGpio (bp_usGpioI2cSda, pusSda);
    
    return(ret);
} /* BpGetRj11InnerOuterPairGpios */
#endif


/**************************************************************************
* Name       : BpGetFemtoResetGpio
*
* Description: This function returns the GPIO that needs to be toggled high
*              for 2 msec at least to reset the FEMTO chip
*
* Parameters : [OUT] pusValue - Address of short word that the GPIO for
*                  resetting FEMTO chip is returned in.
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - Not defined
***************************************************************************/
int BpGetFemtoResetGpio( unsigned short *pusValue )
{
    return( BpGetGpio(bp_usGpioFemtoReset, pusValue ) );
} /*  BpGetFemtoResetGpio */



/**************************************************************************
* Name       : BpGetEphyBaseAddress
*
* Description: This function returns the base address requested for
*              the internal EPHYs
*
* Parameters : [OUT] pusValue - Address of short word for returned value.
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - Not defined
***************************************************************************/
int BpGetEphyBaseAddress( unsigned short *pusValue )
{
    return( BpGetUs(bp_usEphyBaseAddress, pusValue ) );
} /*  BpGetEphyBaseAddress */


/**************************************************************************
* Name       : BpGetGphyBaseAddress
*
* Description: This function returns the base address requested for
*              the internal GPHYs
*
* Parameters : [OUT] pusValue - Address of short word for returned value.
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - Not defined
***************************************************************************/
int BpGetGphyBaseAddress( unsigned short *pusValue )
{
    return( BpGetUs(bp_usGphyBaseAddress, pusValue ) );
} /*  BpGetGphyBaseAddress */

/**************************************************************************
* Name       : BpGetSpiSlaveResetGpio
*
* Description: This function returns the GPIO pin assignment for the resetting the 
*              the SPI slave.
*
* Parameters : [OUT] pusValue - Address of short word that the spi slave reset
*                  GPIO pin is returned in.
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - At least one return value is not defined
*                  for the board.
***************************************************************************/
int BpGetSpiSlaveResetGpio( unsigned short *pusValue )
{
    return( BpGetGpio(bp_usGpioSpiSlaveReset, pusValue ) );
} /* BpGetSpiSlaveResetGpio */

/**************************************************************************
* Name       : BpGetSpiSlaveBusNum
*
* Description: This function returns the bus number of the SPI slave device.
*
* Parameters : [OUT] pusValue - Address of short word that the spi slave select number
*                    is returned in.
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - At least one return value is not defined
*                  for the board.
***************************************************************************/
int BpGetSpiSlaveBusNum( unsigned short *pusValue )
{
    return( BpGetUs(bp_usSpiSlaveBusNum, pusValue ) );
} /* BpGetSpiSlaveBusNum */

/**************************************************************************
* Name       : BpGetSpiSlaveSelectNum
*
* Description: This function returns the SPI slave select number connected  
*              to the slave device.
*
* Parameters : [OUT] pusValue - Address of short word that the spi slave select number
*                    is returned in.
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - At least one return value is not defined
*                  for the board.
***************************************************************************/
int BpGetSpiSlaveSelectNum( unsigned short *pusValue )
{
    return( BpGetUs(bp_usSpiSlaveSelectNum, pusValue ) );
} /* BpGetSpiSlaveSelectNum */

/**************************************************************************
* Name       : BpGetSpiSlaveMode
*
* Description: This function returns the SPI slave select number connected  
*              to the slave device.
*
* Parameters : [OUT] pusValue - Address of short word that the spi slave mode is returned in.
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - At least one return value is not defined
*                  for the board.
***************************************************************************/
int BpGetSpiSlaveMode( unsigned short *pusValue )
{
    return( BpGetUs(bp_usSpiSlaveMode, pusValue ) );
} /* BpGetSpiSlaveMode */

/**************************************************************************
* Name       : BpGetSpiSlaveCtrlState
*
* Description: This function returns the spi controller state that is needed to talk
*              to the spi slave device.
*
* Parameters : [OUT] pusValue - Address of long word that the spi controller state is returned in.
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - At least one return value is not defined
*                  for the board.
***************************************************************************/
int BpGetSpiSlaveCtrlState( unsigned long *pulValue )
{
    return( BpGetUl(bp_ulSpiSlaveCtrlState, pulValue ) );
} /* BpGetSpiSlaveCtrlState */

/**************************************************************************
* Name       : BpGetSpiSlaveMaxFreq
*
* Description: This function returns the SPI slaves max frequency for communication.
*
* Parameters : [OUT] pusValue - Address of long word that the max freq is returned in.
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - At least one return value is not defined
*                  for the board.
***************************************************************************/
int BpGetSpiSlaveMaxFreq( unsigned long *pulValue )
{
    return( BpGetUl(bp_ulSpiSlaveMaxFreq, pulValue ) );
} /* BpGetSpiSlaveMaxFreq */

/**************************************************************************
* Name       : BpGetSpiSlaveProtoRev
*
* Description: This function returns the protocol revision that the slave device uses.
*
* Parameters : [OUT] pusValue - Address of short word that the spi slave protocol revision
                                is returned in.
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - At least one return value is not defined
*                  for the board.
***************************************************************************/
int BpGetSpiSlaveProtoRev( unsigned short *pusValue )
{
    return( BpGetUs(bp_usSpiSlaveProtoRev, pusValue ) );
} /* BpGetSpiSlaveProtoRev */

/**************************************************************************
* Name       : BpGetSerialLEDMuxSel
*
* Description: This function returns the serial LED Mux selection.
*
* Parameters : [OUT] pusValue - Address of short word that the serial LED MUX Selection
                                is returned in.
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - At least one return value is not defined
*                  for the board.
***************************************************************************/
int BpGetSerialLEDMuxSel( unsigned short *pusValue )
{
    return( BpGetUs(bp_usSerialLEDMuxSel, pusValue ) );
} /* BpGetSerialLEDMuxSel */

/**************************************************************************
* Name       : BpGetSwitchPortMap
*
* Description: This function returns the switch port map.
*
* Parameters : [OUT] pulValue - Bitmap of switch ports enabled.
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_VALUE_NOT_DEFINED - bp_ulPortMap is not defined
*                  for the board.
***************************************************************************/
int BpGetSwitchPortMap (unsigned long *pulValue)
{
    *pulValue = BpGetSubUl(bp_ulPortMap, 0, bp_last);
    if (*pulValue == BP_NOT_DEFINED ){
        *pulValue = 0;
        return BP_VALUE_NOT_DEFINED;
    } else {
        return BP_SUCCESS;
    }
}

/**************************************************************************
* Name       : BpGetDeviceOptions
*
* Description: This function returns the serial LED Mux selection.
*
* Parameters : [OUT] pulValue - Address of word that device options bitmap
                                is returned in.
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - At least one return value is not defined
*                  for the board.
***************************************************************************/
int BpGetDeviceOptions( unsigned long *pulValue )
{
    return( BpGetUl(bp_ulDeviceOptions, pulValue ) );
} /* BpGetDeviceOptions */

#if defined(CONFIG_EPON_SDK)
/**************************************************************************
* Name       : BpGetEponNumFePorts
*
* Description: This function returns the number of FE ports
*
* Parameters : [OUT] pulValue - number of FE UNI ports in this board design
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - At least one return value is not defined
*                  for the board.
***************************************************************************/
int BpGetNumFePorts( unsigned long *pulValue )
{
    return( BpGetUl(bp_ulNumFePorts, pulValue ) );
} /* BpGetEponNumFePorts */

/**************************************************************************
* Name       : BpGetEponNumGePorts
*
* Description: This function returns the number of GE ports
*
* Parameters : [OUT] pulValue - number of GE UNI ports in this board design
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - At least one return value is not defined
*                  for the board.
***************************************************************************/
int BpGetNumGePorts( unsigned long *pulValue )
{
    return( BpGetUl(bp_ulNumGePorts, pulValue ) );
} /* BpGetEponNumGePorts */

/**************************************************************************
* Name       : BpGetEponNumVoipPorts
*
* Description: This function returns the number of VOIP ports
*
* Parameters : [OUT] pulValue - number of VOIP ports in this board design
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - At least one return value is not defined
*                  for the board.
***************************************************************************/
int BpGetNumVoipPorts( unsigned long *pulValue )
{
    return( BpGetUl(bp_ulNumVoipPorts, pulValue ) );
} /* BpGetEponNumVoipPorts */


/**************************************************************************
* Name       : BpGetPersonalityName
*
* Description: This function returns is used to get the personality name 
*              for a board.
*
* Parameters : [OUT] pcpValue - personality file name .
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - At least one return value is not defined
*                  for the board.
***************************************************************************/
int BpGetPersonalityName( char **pcpValue )
{
    return( BpGetCp( bp_cpPersonalityName, pcpValue ) );
} /* BpGetPersonalityName */

#if defined(CONFIG_BCM96828)
/**************************************************************************
* Name       : BpGetNonPeriphGpioMap
*
* Description: This function returns the bit map of GPIOs controlled by other blocks like by EPON and APM
*
* Parameters : [OUT] pulValue - bit map of GPIOs (starting from GPIO32) controlled by EPON block.
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - At least one return value is not defined
*                  for the board.
***************************************************************************/
int BpGetNonPeriphGpioMap( unsigned long *pulValue )
{
    return( BpGetUl(bp_ulNonPeriphGpioCtrlMap, pulValue ) );
} /* BpGetNonPeriphGpioMap */
#endif

#endif //CONFIG_EPON_SDK

/**************************************************************************
* Name       : BpGetLedGpio
*
* Description: Get the gpio pin assignment for a LED boardparm id in the bpLedList
*
* Parameters : [IN] idx - LED boardparm id index to the bpLedList array.
*              [OUT] pusValue - the GPIO number for the LED or BP_VALUE_NOT_DEFINED
*              if that LED is not defined in the board parameter
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - this Led id is not defined in the boardparm
*              BP_MAX_ITEM_EXCEEDED - idx exceed the maximum led id in the list
***************************************************************************/
int BpGetLedGpio(int idx, unsigned short *pusValue)
{
    int total = sizeof(bpLedList)/sizeof(enum bp_id);

    if(idx >= total)
        return BP_MAX_ITEM_EXCEEDED;
    else
        return BpGetGpio(bpLedList[idx], pusValue);
}

/**************************************************************************
* Name       : BpGetGpioGpio
*
* Description: Get the gpio pin assignment for a GPIO boardparm id in the bpGpioList
*
* Parameters : [IN] idx - GPIO boardparm id idx to the bpGpioList array.
*              [OUT] pusValue - the GPIO number for the Gpio or BP_VALUE_NOT_DEFINED
*              if that LED is not defined in the board parameter
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_SET - Error, BpSetBoardId has not been called.
*              BP_VALUE_NOT_DEFINED - this GPIO id is not defined in the boardparm
*              BP_MAX_ITEM_EXCEEDED - idx exceed the maximum led id in the list
***************************************************************************/
int BpGetGpioGpio(int idx, unsigned short *pusValue)
{
    int total = sizeof(bpGpioList)/sizeof(enum bp_id);

    if(idx >= total)
        return BP_MAX_ITEM_EXCEEDED;
    else
        return BpGetGpio(bpGpioList[idx], pusValue);
}

//<< [CTFN-SYS-015] Jimmy Wu : Support to flash LED when CPE is upgrading the software
int BpGetPowerLedGpio( unsigned short *pusValue )
{
    return( BpGetUs(bp_usGpioLedBlPowerOn, pusValue ) );
} /* BpGetPowerLedGpio */


int BpGetPowerFailLedGpio( unsigned short *pusValue )
{
    return( BpGetUs(bp_usGpioLedBlStop, pusValue ) );
} /* BpGetPowerFailLedGpio */
//>> [CTFN-SYS-015] End


//<< [CTFN-WIFI-001] kewei lai : Support two Wireless en/disable buttons and Wireless/WPS in one button
int BpGetCtWirelessBtnGpio( unsigned short *pusValue )
{
    return( BpGetUs(bp_usGpioCtWirelessBtn, pusValue ) );
} /* BpGetCtWirelessBtnGpio */

int BpGetCtWirelessBtn2Gpio( unsigned short *pusValue )
{
    return( BpGetUs(bp_usGpioCtWirelessBtn2, pusValue ) );
} /* BpGetCtWirelessBtn2Gpio */


int BpGetCtWifiBtnExtIntr( unsigned short *pusValue )
{
    return( BpGetUs(bp_usExtIntrCtWifiBtn, pusValue ) );
} /* BpGetCtWifiBtnExtIntr */

int BpGetCtWifiBtnExtIntr2( unsigned short *pusValue )
{
    return( BpGetUs(bp_usExtIntrCtWifiBtn2, pusValue ) );
} /* BpGetCtWifiBtnExtIntr2 */

//>> [CTFN-WIFI-001] End

//<< [CTFN-DRV-001] Antony.Wu : Support 1. Phyid to Ethx mapping and 2. IP101_1001 of ICPLUS, 20111205
/*
 * return integer nGet: number of phy id stored in the table.
 * input value pucValue: pointer to an array which preset 
 *     which phyid should be eth0 and which phyid should be eth1...
 *     eg. 0x14, 0x3, 0x2, 0x1 
 *         => phyid 0x14 should be eth0, phyid 0x3 should be eth1
 *         => phyid 0x2 sohould be eth2, phyid 0x1 sould be eth3
 */
int BpGetCtEthPhyMap( unsigned char *pucValue )
{
    int nGet = 0;
    unsigned char *ptr = 0;
    if(BP_SUCCESS == BpGetCp(bp_ucpEthPhyMap, (char**)&ptr)){
        while(ptr && ptr[nGet]){
            pucValue[nGet] = ptr[nGet];
            nGet++;
        }
    }
    return nGet;
}
//>> [CTFN-DRV-001] End
//<< [CTFN-DRV-001-2] Support to configure the first index of Ethernet interface in board parameters
int BpGetCtEthIndex( unsigned short *pusValue )
{
	return (BpGetUs(bp_usEthIndex, pusValue));
}
//>> [CTFN-DRV-001-2] End

//<< [CTFN-SYS-016] Jimmy Wu : Support Internet LED (implemented by Comtrend)
int BpGetCtInternetLedGpio( unsigned short *pusValue )
{
    return( BpGetUs(bp_usGpioCtInternetLed, pusValue ) );
} /* BpGetCtInternetLedGpio */

int BpGetCtInternetFailLedGpio( unsigned short *pusValue )
{
    return( BpGetUs(bp_usGpioCtInternetFailLed, pusValue ) );
} /* BpGetGpioCtInternetFailLed */
//>> [CTFN-SYS-016] End
//<< [CTFN-WIFI-014] Support two Wireless Interfaces with band defined in board parameter and modify SSID according to band info
int BpGetWirelessBand1( unsigned short *pusValue )
{
    return( BpGetUs(bp_usCtWirelessBand1, pusValue ) );
} /* BpGetWirelessBand1 */

int BpGetWirelessBand2( unsigned short *pusValue )
{
    return( BpGetUs(bp_usCtWirelessBand2, pusValue ) );
} /* BpGetWirelessBand2 */
//>> [CTFN-WIFI-014] End

//<< [CTFN-SYS-032] Lucien Huang : Support USB LED for USB host (implemented by Comtrend), 2012/03/12
int BpGetCtUSBLedGpio( unsigned short *pusValue )
{
    return( BpGetUs(bp_usGpioCtUSBLed, pusValue ) );
} /* BpGetCtUSBLedGpio */

int BpGetCtUSBFailLedGpio( unsigned short *pusValue )
{
    return( BpGetUs(bp_usGpioCtUSBFailLed, pusValue ) );
} /* BpGetCtUSBFailLedGpio */
//>> [CTFN-SYS-032] End
//>> [CTFN-SYS-032-6] kewei lai : Support the second USB LED

int BpGetCtUsbSingleLed1Gpio( unsigned short *pusValue )
{
    return( BpGetUs(bp_usGpioCtUsbSingleLed1, pusValue ) );
} /* BpGetCtUsbSingleLed1Gpio */

int BpGetCtUsbSingleLed2Gpio( unsigned short *pusValue )
{
    return( BpGetUs(bp_usGpioCtUsbSingleLed2, pusValue ) );
} /* BpGetCtUsbSingleLed2Gpio */
//<< [CTFN-SYS-032-6] End

//<< [CTFN-WIFI-017] kewei lai: Support the second WPS LED
int BpGetCtLedSesWireless2( unsigned short *pusValue )
{
    return( BpGetGpio(bp_usGpioCtLedSesWireless2, pusValue ) );
} /* BpGetCtLedSesWireless2 */
//>> [CTFN-WIFI-017] End

//<< kewei lai for add new boardid 963169R-1861AC to WAP-5892u  

int BpGetCtWifiBtnAllGpio( unsigned short *pusValue )
{
    return( BpGetUs(bp_usGpioCtWifiBtnAll, pusValue ) );
} /* BpGetCtWifiBtnAllGpio */

//>> kewei lai for add new boardid 963169R-1861AC to WAP-5892u  


