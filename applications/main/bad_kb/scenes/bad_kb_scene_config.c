#include "../bad_kb_app_i.h"

enum VarItemListIndex {
    VarItemListIndexKeyboardLayout,
    VarItemListIndexConnection,
};

enum VarItemListIndexBt {
    VarItemListIndexBtRemember = VarItemListIndexConnection + 1,
    VarItemListIndexBtPairing,
    VarItemListIndexBtDeviceName,
    VarItemListIndexBtMacAddress,
    VarItemListIndexBtRandomizeMac,
};

enum VarItemListIndexUsb {
    VarItemListIndexUsbManufacturer = VarItemListIndexConnection + 1,
    VarItemListIndexUsbProductName,
    VarItemListIndexUsbVidPid,
    VarItemListIndexUsbRandomizeVidPid,
};

void bad_kb_scene_config_connection_callback(VariableItem* item) {
    BadKbApp* bad_kb = variable_item_get_context(item);
    bad_kb->is_bt = variable_item_get_current_value_index(item);
    variable_item_set_current_value_text(item, bad_kb->is_bt ? "蓝牙" : "USB");
    view_dispatcher_send_custom_event(bad_kb->view_dispatcher, VarItemListIndexConnection);
}

void bad_kb_scene_config_bt_remember_callback(VariableItem* item) {
    BadKbApp* bad_kb = variable_item_get_context(item);
    bool value = variable_item_get_current_value_index(item);
    // Set user config and remember
    bad_kb->config.ble.bonding = value;
    // Apply to ID config so its temporarily overridden (currently can't set bonding with BT_ID anyway)
    if(bad_kb->set_bt_id) {
        bad_kb->id_config.ble.bonding = value;
    }
    variable_item_set_current_value_text(item, value ? "开" : "关");
    view_dispatcher_send_custom_event(bad_kb->view_dispatcher, VarItemListIndexBtRemember);
}

const char* const bt_pairing_names[GapPairingCount] = {
    "是/否",
    "PIN类型",
    "PIN 是/否",
};
void bad_kb_scene_config_bt_pairing_callback(VariableItem* item) {
    BadKbApp* bad_kb = variable_item_get_context(item);
    uint8_t index = variable_item_get_current_value_index(item);
    // Set user config and remember
    bad_kb->config.ble.pairing = index;
    // Apply to ID config so its temporarily overridden (currently can't set pairing with BT_ID anyway)
    if(bad_kb->set_bt_id) {
        bad_kb->id_config.ble.pairing = index;
    }
    variable_item_set_current_value_text(item, bt_pairing_names[index]);
    view_dispatcher_send_custom_event(bad_kb->view_dispatcher, VarItemListIndexBtPairing);
}

void bad_kb_scene_config_var_item_list_callback(void* context, uint32_t index) {
    BadKbApp* bad_kb = context;
    view_dispatcher_send_custom_event(bad_kb->view_dispatcher, index);
}

void bad_kb_scene_config_on_enter(void* context) {
    BadKbApp* bad_kb = context;
    VariableItemList* var_item_list = bad_kb->var_item_list;
    VariableItem* item;

    item = variable_item_list_add(var_item_list, "键盘布局", 0, NULL, bad_kb);

    item = variable_item_list_add(
        var_item_list, "连接方式", 2, bad_kb_scene_config_connection_callback, bad_kb);
    variable_item_set_current_value_index(item, bad_kb->is_bt);
    variable_item_set_current_value_text(item, bad_kb->is_bt ? "蓝牙" : "USB");

    if(bad_kb->is_bt) {
        BadKbConfig* cfg = bad_kb->set_bt_id ? &bad_kb->id_config : &bad_kb->config;

        item = variable_item_list_add(
            var_item_list, "记住蓝牙", 2, bad_kb_scene_config_bt_remember_callback, bad_kb);
        variable_item_set_current_value_index(item, cfg->ble.bonding);
        variable_item_set_current_value_text(item, cfg->ble.bonding ? "开" : "关");

        item = variable_item_list_add(
            var_item_list,
            "蓝牙配对",
            GapPairingCount,
            bad_kb_scene_config_bt_pairing_callback,
            bad_kb);
        variable_item_set_current_value_index(item, cfg->ble.pairing);
        variable_item_set_current_value_text(item, bt_pairing_names[cfg->ble.pairing]);

        item = variable_item_list_add(var_item_list, "蓝牙设备名称", 0, NULL, bad_kb);

        item = variable_item_list_add(var_item_list, "蓝牙 MAC 地址", 0, NULL, bad_kb);
        if(cfg->ble.bonding) {
            variable_item_set_locked(item, true, "记住\n必须关闭！");
        }

        item = variable_item_list_add(var_item_list, "随机化蓝牙 MAC", 0, NULL, bad_kb);
        if(cfg->ble.bonding) {
            variable_item_set_locked(item, true, "记住\n必须关闭！");
        }
    } else {
        item = variable_item_list_add(var_item_list, "USB 制造商", 0, NULL, bad_kb);

        item = variable_item_list_add(var_item_list, "USB 产品名称", 0, NULL, bad_kb);

        item = variable_item_list_add(var_item_list, "USB VID 和 PID", 0, NULL, bad_kb);

        item = variable_item_list_add(var_item_list, "随机化 USB VID:PID", 0, NULL, bad_kb);
    }

    variable_item_list_set_enter_callback(
        var_item_list, bad_kb_scene_config_var_item_list_callback, bad_kb);

    variable_item_list_set_selected_item(
        var_item_list, scene_manager_get_scene_state(bad_kb->scene_manager, BadKbSceneConfig));

    view_dispatcher_switch_to_view(bad_kb->view_dispatcher, BadKbAppViewVarItemList);
}

bool bad_kb_scene_config_on_event(void* context, SceneManagerEvent event) {
    BadKbApp* bad_kb = context;
    bool consumed = false;

    if(event.type == SceneManagerEventTypeCustom) {
        scene_manager_set_scene_state(bad_kb->scene_manager, BadKbSceneConfig, event.event);
        consumed = true;
        switch(event.event) {
        case VarItemListIndexKeyboardLayout:
            scene_manager_next_scene(bad_kb->scene_manager, BadKbSceneConfigLayout);
            break;
        case VarItemListIndexConnection:
            bad_kb_config_refresh(bad_kb);
            break;
        default:
            break;
        }
        if(bad_kb->is_bt) {
            switch(event.event) {
            case VarItemListIndexBtRemember:
                bad_kb_config_refresh(bad_kb);
                break;
            case VarItemListIndexBtPairing:
                bad_kb_config_refresh(bad_kb);
                break;
            case VarItemListIndexBtDeviceName:
                scene_manager_next_scene(bad_kb->scene_manager, BadKbSceneConfigBtName);
                break;
            case VarItemListIndexBtMacAddress:
                scene_manager_next_scene(bad_kb->scene_manager, BadKbSceneConfigBtMac);
                break;
            case VarItemListIndexBtRandomizeMac:
                // Set user config and remember
                furi_hal_random_fill_buf(bad_kb->config.ble.mac, sizeof(bad_kb->config.ble.mac));
                // Apply to ID config so its temporarily overridden
                if(bad_kb->set_bt_id) {
                    memcpy(
                        bad_kb->id_config.ble.mac,
                        bad_kb->config.ble.mac,
                        sizeof(bad_kb->id_config.ble.mac));
                }
                bad_kb_config_refresh(bad_kb);
                break;
            default:
                break;
            }
        } else {
            switch(event.event) {
            case VarItemListIndexUsbManufacturer:
                scene_manager_set_scene_state(
                    bad_kb->scene_manager, BadKbSceneConfigUsbName, true);
                scene_manager_next_scene(bad_kb->scene_manager, BadKbSceneConfigUsbName);
                break;
            case VarItemListIndexUsbProductName:
                scene_manager_set_scene_state(
                    bad_kb->scene_manager, BadKbSceneConfigUsbName, false);
                scene_manager_next_scene(bad_kb->scene_manager, BadKbSceneConfigUsbName);
                break;
            case VarItemListIndexUsbVidPid:
                scene_manager_next_scene(bad_kb->scene_manager, BadKbSceneConfigUsbVidPid);
                break;
            case VarItemListIndexUsbRandomizeVidPid:
                furi_hal_random_fill_buf(
                    (void*)bad_kb->usb_vidpid_buf, sizeof(bad_kb->usb_vidpid_buf));
                // Set user config and remember
                bad_kb->config.usb.vid = bad_kb->usb_vidpid_buf[0];
                bad_kb->config.usb.pid = bad_kb->usb_vidpid_buf[1];
                // Apply to ID config so its temporarily overridden
                if(bad_kb->set_usb_id) {
                    bad_kb->id_config.usb.vid = bad_kb->config.usb.vid;
                    bad_kb->id_config.usb.pid = bad_kb->config.usb.pid;
                }
                bad_kb_config_refresh(bad_kb);
                break;
            default:
                break;
            }
        }
    }

    return consumed;
}

void bad_kb_scene_config_on_exit(void* context) {
    BadKbApp* bad_kb = context;
    VariableItemList* var_item_list = bad_kb->var_item_list;

    variable_item_list_reset(var_item_list);
}
