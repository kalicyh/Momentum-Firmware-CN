#include "../storage_settings.h"

enum StorageSettingsStartSubmenuIndex {
    StorageSettingsStartSubmenuIndexInternalInfo,
    StorageSettingsStartSubmenuIndexSDInfo,
    StorageSettingsStartSubmenuIndexUnmount,
    StorageSettingsStartSubmenuIndexFormat,
    StorageSettingsStartSubmenuIndexBenchy,
    StorageSettingsStartSubmenuIndexFactoryReset,
    StorageSettingsStartSubmenuIndexWipeDevice,
};

static void storage_settings_scene_start_submenu_callback(void* context, uint32_t index) {
    StorageSettings* app = context;

    view_dispatcher_send_custom_event(app->view_dispatcher, index);
}

void storage_settings_scene_start_on_enter(void* context) {
    StorageSettings* app = context;
    Submenu* submenu = app->submenu;

    submenu_add_item(
        submenu,
        "关于内部存储",
        StorageSettingsStartSubmenuIndexInternalInfo,
        storage_settings_scene_start_submenu_callback,
        app);
    submenu_add_item(
        submenu,
        "关于 SD 卡",
        StorageSettingsStartSubmenuIndexSDInfo,
        storage_settings_scene_start_submenu_callback,
        app);

    FS_Error sd_status = storage_sd_status(app->fs_api);
    if(sd_status != FSE_OK) {
        submenu_add_item(
            submenu,
            "挂载 SD 卡",
            StorageSettingsStartSubmenuIndexUnmount,
            storage_settings_scene_start_submenu_callback,
            app);
    } else {
        submenu_add_item(
            submenu,
            "卸载 SD 卡",
            StorageSettingsStartSubmenuIndexUnmount,
            storage_settings_scene_start_submenu_callback,
            app);
    }

    submenu_add_item(
        submenu,
        "格式化 SD 卡",
        StorageSettingsStartSubmenuIndexFormat,
        storage_settings_scene_start_submenu_callback,
        app);
    submenu_add_item(
        submenu,
        "基准测试 SD 卡",
        StorageSettingsStartSubmenuIndexBenchy,
        storage_settings_scene_start_submenu_callback,
        app);
    submenu_add_item(
        submenu,
        "恢复出厂设置",
        StorageSettingsStartSubmenuIndexFactoryReset,
        storage_settings_scene_start_submenu_callback,
        app);
    submenu_add_item(
        submenu,
        "清除设备",
        StorageSettingsStartSubmenuIndexWipeDevice,
        storage_settings_scene_start_submenu_callback,
        app);

    submenu_set_selected_item(
        submenu, scene_manager_get_scene_state(app->scene_manager, StorageSettingsStart));

    view_dispatcher_switch_to_view(app->view_dispatcher, StorageSettingsViewSubmenu);
}

bool storage_settings_scene_start_on_event(void* context, SceneManagerEvent event) {
    StorageSettings* app = context;
    bool consumed = false;

    if(event.type == SceneManagerEventTypeCustom) {
        switch(event.event) {
        case StorageSettingsStartSubmenuIndexSDInfo:
            scene_manager_set_scene_state(
                app->scene_manager, StorageSettingsStart, StorageSettingsStartSubmenuIndexSDInfo);
            scene_manager_next_scene(app->scene_manager, StorageSettingsSDInfo);
            consumed = true;
            break;
        case StorageSettingsStartSubmenuIndexInternalInfo:
            scene_manager_set_scene_state(
                app->scene_manager,
                StorageSettingsStart,
                StorageSettingsStartSubmenuIndexInternalInfo);
            scene_manager_next_scene(app->scene_manager, StorageSettingsInternalInfo);
            consumed = true;
            break;
        case StorageSettingsStartSubmenuIndexUnmount:
            scene_manager_set_scene_state(
                app->scene_manager, StorageSettingsStart, StorageSettingsStartSubmenuIndexUnmount);
            scene_manager_next_scene(app->scene_manager, StorageSettingsUnmountConfirm);
            consumed = true;
            break;
        case StorageSettingsStartSubmenuIndexFormat:
            scene_manager_set_scene_state(
                app->scene_manager, StorageSettingsStart, StorageSettingsStartSubmenuIndexFormat);
            scene_manager_next_scene(app->scene_manager, StorageSettingsFormatConfirm);
            consumed = true;
            break;
        case StorageSettingsStartSubmenuIndexBenchy:
            scene_manager_set_scene_state(
                app->scene_manager, StorageSettingsStart, StorageSettingsStartSubmenuIndexBenchy);
            scene_manager_next_scene(app->scene_manager, StorageSettingsBenchmarkConfirm);
            consumed = true;
            break;
        case StorageSettingsStartSubmenuIndexFactoryReset:
            scene_manager_set_scene_state(
                app->scene_manager,
                StorageSettingsStart,
                StorageSettingsStartSubmenuIndexFactoryReset);
            scene_manager_next_scene(app->scene_manager, StorageSettingsFactoryReset);
            consumed = true;
            break;
        case StorageSettingsStartSubmenuIndexWipeDevice:
            scene_manager_set_scene_state(
                app->scene_manager,
                StorageSettingsStart,
                StorageSettingsStartSubmenuIndexWipeDevice);
            scene_manager_next_scene(app->scene_manager, StorageSettingsWipeDevice);
            consumed = true;
            break;
        }
    }
    return consumed;
}

void storage_settings_scene_start_on_exit(void* context) {
    StorageSettings* app = context;
    submenu_reset(app->submenu);
}
