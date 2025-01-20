#include "../momentum_app.h"

enum VarItemListIndex {
    VarItemListIndexFlipperName, // TODO: Split into name, mac, serial
    VarItemListIndexShellColor,
};

const char* const shell_color_names[FuriHalVersionColorCount] = {
    "真实",
    "黑色",
    "白色",
    "透明",
};
static void momentum_app_scene_misc_spoof_shell_color_changed(VariableItem* item) {
    MomentumApp* app = variable_item_get_context(item);
    uint8_t index = variable_item_get_current_value_index(item);
    variable_item_set_current_value_text(item, shell_color_names[index]);
    momentum_settings.spoof_color = index;
    app->save_settings = true;
    app->require_reboot = true;
}

// 设备状态变更回调
static void momentum_app_scene_misc_device_status_changed(VariableItem* item) {
    MomentumApp* app = variable_item_get_context(item);
    bool value = variable_item_get_current_value_index(item);
    variable_item_set_current_value_text(item, value ? "复刻版" : "正版");
    momentum_settings.spoof_status = value;
    app->save_settings = true;
    app->require_reboot = true;
}

void momentum_app_scene_misc_spoof_var_item_list_callback(void* context, uint32_t index) {
    MomentumApp* app = context;
    view_dispatcher_send_custom_event(app->view_dispatcher, index);
}

void momentum_app_scene_misc_spoof_on_enter(void* context) {
    MomentumApp* app = context;
    VariableItemList* var_item_list = app->var_item_list;
    VariableItem* item;

    item = variable_item_list_add(var_item_list, "Flipper 名称", 0, NULL, app);
    variable_item_set_current_value_text(item, app->device_name);

    item = variable_item_list_add(
        var_item_list,
        "外壳颜色",
        FuriHalVersionColorCount,
        momentum_app_scene_misc_spoof_shell_color_changed,
        app);
    variable_item_set_current_value_index(item, momentum_settings.spoof_color);
    variable_item_set_current_value_text(item, shell_color_names[momentum_settings.spoof_color]);

    item = variable_item_list_add(
        var_item_list,
        "设备状态",
        2,
        momentum_app_scene_misc_device_status_changed,
        app);
    variable_item_set_current_value_index(item, momentum_settings.spoof_status);
    variable_item_set_current_value_text(item, momentum_settings.spoof_status ? "复刻版" : "正版");

    variable_item_list_set_enter_callback(
        var_item_list, momentum_app_scene_misc_spoof_var_item_list_callback, app);

    variable_item_list_set_selected_item(
        var_item_list,
        scene_manager_get_scene_state(app->scene_manager, MomentumAppSceneMiscSpoof));

    view_dispatcher_switch_to_view(app->view_dispatcher, MomentumAppViewVarItemList);
}

bool momentum_app_scene_misc_spoof_on_event(void* context, SceneManagerEvent event) {
    MomentumApp* app = context;
    bool consumed = false;

    if(event.type == SceneManagerEventTypeCustom) {
        scene_manager_set_scene_state(app->scene_manager, MomentumAppSceneMiscSpoof, event.event);
        consumed = true;
        switch(event.event) {
        case VarItemListIndexFlipperName:
            scene_manager_next_scene(app->scene_manager, MomentumAppSceneMiscSpoofName);
            break;
        default:
            break;
        }
    }

    return consumed;
}

void momentum_app_scene_misc_spoof_on_exit(void* context) {
    MomentumApp* app = context;
    variable_item_list_reset(app->var_item_list);
}
