#include "../infrared_app_i.h"

enum SubmenuIndex {
    SubmenuIndexUniversalRemotes,
    SubmenuIndexLearnNewRemote,
    SubmenuIndexSavedRemotes,
    SubmenuIndexGpioSettings,
    SubmenuIndexLearnNewRemoteRaw,
    SubmenuIndexDebug
};

static void infrared_scene_start_submenu_callback(void* context, uint32_t index) {
    InfraredApp* infrared = context;
    view_dispatcher_send_custom_event(infrared->view_dispatcher, index);
}

void infrared_scene_start_on_enter(void* context) {
    InfraredApp* infrared = context;
    Submenu* submenu = infrared->submenu;
    SceneManager* scene_manager = infrared->scene_manager;

    submenu_add_item(
        submenu,
        "万能遥控器",
        SubmenuIndexUniversalRemotes,
        infrared_scene_start_submenu_callback,
        infrared);
    submenu_add_item(
        submenu,
        "学习新遥控器",
        SubmenuIndexLearnNewRemote,
        infrared_scene_start_submenu_callback,
        infrared);
    submenu_add_item(
        submenu,
        "已保存的遥控器",
        SubmenuIndexSavedRemotes,
        infrared_scene_start_submenu_callback,
        infrared);
    submenu_add_item(
        submenu,
        "GPIO 设置",
        SubmenuIndexGpioSettings,
        infrared_scene_start_submenu_callback,
        infrared);

    submenu_add_lockable_item(
        submenu,
        "学习新遥控器 RAW",
        SubmenuIndexLearnNewRemoteRaw,
        infrared_scene_start_submenu_callback,
        infrared,
        !infrared->app_state.is_debug_enabled,
        "启用\n"
        "设置 >\n"
        "系统 >\n"
        "调试");
    submenu_add_lockable_item(
        submenu,
        "调试 RX",
        SubmenuIndexDebug,
        infrared_scene_start_submenu_callback,
        infrared,
        !infrared->app_state.is_debug_enabled,
        "启用\n"
        "设置 >\n"
        "系统 >\n"
        "调试");

    const uint32_t submenu_index =
        scene_manager_get_scene_state(scene_manager, InfraredSceneStart);
    submenu_set_selected_item(submenu, submenu_index);
    scene_manager_set_scene_state(scene_manager, InfraredSceneStart, SubmenuIndexUniversalRemotes);

    view_dispatcher_switch_to_view(infrared->view_dispatcher, InfraredViewSubmenu);
}

bool infrared_scene_start_on_event(void* context, SceneManagerEvent event) {
    InfraredApp* infrared = context;
    SceneManager* scene_manager = infrared->scene_manager;

    bool consumed = false;

    if(event.type == SceneManagerEventTypeCustom) {
        const uint32_t submenu_index = event.event;
        scene_manager_set_scene_state(scene_manager, InfraredSceneStart, submenu_index);
        if(submenu_index == SubmenuIndexUniversalRemotes) {
            // Set file_path only once here so repeated usages of
            // "Load from Library File" have file browser focused on
            // last selected file, feels more intuitive
            furi_string_set(infrared->file_path, INFRARED_APP_FOLDER);
            scene_manager_next_scene(scene_manager, InfraredSceneUniversal);
        } else if(
            submenu_index == SubmenuIndexLearnNewRemote ||
            submenu_index == SubmenuIndexLearnNewRemoteRaw) {
            // enable automatic signal decoding if "Learn New Remote"
            // disable automatic signal decoding if "Learn New Remote (RAW)"
            infrared_worker_rx_enable_signal_decoding(
                infrared->worker, submenu_index == SubmenuIndexLearnNewRemote);
            infrared->app_state.is_learning_new_remote = true;
            scene_manager_next_scene(scene_manager, InfraredSceneLearn);
        } else if(submenu_index == SubmenuIndexSavedRemotes) {
            furi_string_set(infrared->file_path, INFRARED_APP_FOLDER);
            scene_manager_next_scene(scene_manager, InfraredSceneRemoteList);
        } else if(submenu_index == SubmenuIndexGpioSettings) {
            scene_manager_next_scene(scene_manager, InfraredSceneGpioSettings);
        } else if(submenu_index == SubmenuIndexDebug) {
            scene_manager_next_scene(scene_manager, InfraredSceneDebug);
        }

        consumed = true;
    }

    return consumed;
}

void infrared_scene_start_on_exit(void* context) {
    InfraredApp* infrared = context;
    submenu_reset(infrared->submenu);
}
