#pragma once

#include "settings.h"
#include <gui/icon_i.h>
#include <toolbox/path.h>

#define PACKS_DIR EXT_PATH("dolphin_custom")

typedef struct {
    bool is_nsfw;
    const Icon* A_Levelup_128x64;
    const Icon* I_BLE_Pairing_128x64;
    const Icon* I_DolphinCommon_56x48;
    const Icon* I_DolphinMafia_115x62;
    const Icon* I_DolphinNice_96x59;
    const Icon* I_DolphinWait_61x59;
    const Icon* I_iButtonDolphinVerySuccess_108x52;
    const Icon* I_DolphinReadingSuccess_59x63;
    const Icon* I_NFC_dolphin_emulation_47x61;
    const Icon* I_passport_bad;
    const Icon* I_passport_DB;
    const Icon* I_passport_happy;
    const Icon* I_passport_okay;
    const Icon* I_RFIDDolphinReceive_97x61;
    const Icon* I_RFIDDolphinSend_97x61;
    const Icon* I_RFIDDolphinSuccess_108x57;
    const Icon* I_Cry_dolph_55x52;
    const Icon* I_Scanning_123x52;
    const Icon* I_Auth_62x31;
    const Icon* I_Connect_me_62x31;
    const Icon* I_Connected_62x31;
    const Icon* I_Error_62x31;
} DAssets;

void D_ASSETS_LOAD();

DAssets* D_ASSETS();