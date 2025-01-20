#include "../momentum_app.h"

enum VarItemListIndex {
    VarItemListIndexSortDirsFirst,
    VarItemListIndexShowHiddenFiles,
    VarItemListIndexShowInternalTab,
    VarItemListIndexFavoriteTimeout,
};

const char* const browser_path_names[BrowserPathModeCount] = {
    "OFF",
    "Current",
    "Brief",
    "Full",
};

void momentum_app_scene_interface_filebrowser_var_item_list_callback(void* context, uint32_t index) {
    MomentumApp* app = context;
    view_dispatcher_send_custom_event(app->view_dispatcher, index);
}

static void momentum_app_scene_interface_filebrowser_sort_dirs_first_changed(VariableItem* item) {
    MomentumApp* app = variable_item_get_context(item);
    bool value = variable_item_get_current_value_index(item);
    variable_item_set_current_value_text(item, value ? "开启" : "关闭");
    momentum_settings.sort_dirs_first = value;
    app->save_settings = true;
}

static void
    momentum_app_scene_interface_filebrowser_show_hidden_files_changed(VariableItem* item) {
    MomentumApp* app = variable_item_get_context(item);
    bool value = variable_item_get_current_value_index(item);
    variable_item_set_current_value_text(item, value ? "开启" : "关闭");
    momentum_settings.show_hidden_files = value;
    app->save_settings = true;
}

static void
    momentum_app_scene_interface_filebrowser_show_internal_tab_changed(VariableItem* item) {
    MomentumApp* app = variable_item_get_context(item);
    bool value = variable_item_get_current_value_index(item);
    variable_item_set_current_value_text(item, value ? "开启" : "关闭");
    momentum_settings.show_internal_tab = value;
    app->save_settings = true;
}

static void
    momentum_app_scene_interface_filebrowser_browser_path_mode_changed(VariableItem* item) {
    MomentumApp* app = variable_item_get_context(item);
    uint8_t index = variable_item_get_current_value_index(item);
    variable_item_set_current_value_text(item, browser_path_names[index]);
    momentum_settings.browser_path_mode = index;
    app->save_settings = true;
}

static void momentum_app_scene_interface_filebrowser_favorite_timeout_changed(VariableItem* item) {
    MomentumApp* app = variable_item_get_context(item);
    uint32_t value = variable_item_get_current_value_index(item);
    char text[6];
    snprintf(text, sizeof(text), "%lu S", value);
    variable_item_set_current_value_text(item, value ? text : "关闭");
    momentum_settings.favorite_timeout = value;
    app->save_settings = true;
}

void momentum_app_scene_interface_filebrowser_on_enter(void* context) {
    MomentumApp* app = context;
    VariableItemList* var_item_list = app->var_item_list;
    VariableItem* item;

    item = variable_item_list_add(
        var_item_list,
        "文件夹在前",
        2,
        momentum_app_scene_interface_filebrowser_sort_dirs_first_changed,
        app);
    variable_item_set_current_value_index(item, momentum_settings.sort_dirs_first);
    variable_item_set_current_value_text(
        item, momentum_settings.sort_dirs_first ? "开启" : "关闭");

    item = variable_item_list_add(
        var_item_list,
        "显示隐藏文件",
        2,
        momentum_app_scene_interface_filebrowser_show_hidden_files_changed,
        app);
    variable_item_set_current_value_index(item, momentum_settings.show_hidden_files);
    variable_item_set_current_value_text(
        item, momentum_settings.show_hidden_files ? "开启" : "关闭");

    item = variable_item_list_add(
        var_item_list,
        "显示内部标签",
        2,
        momentum_app_scene_interface_filebrowser_show_internal_tab_changed,
        app);
    variable_item_set_current_value_index(item, momentum_settings.show_internal_tab);
    variable_item_set_current_value_text(
        item, momentum_settings.show_internal_tab ? "开启" : "关闭");

    item = variable_item_list_add(
        var_item_list,
        "显示路径",
        BrowserPathModeCount,
        momentum_app_scene_interface_filebrowser_browser_path_mode_changed,
        app);
    variable_item_set_current_value_index(item, momentum_settings.browser_path_mode);
    variable_item_set_current_value_text(
        item, browser_path_names[momentum_settings.browser_path_mode]);

    item = variable_item_list_add(
        var_item_list,
        "收藏超时",
        61,
        momentum_app_scene_interface_filebrowser_favorite_timeout_changed,
        app);
    variable_item_set_current_value_index(item, momentum_settings.favorite_timeout);
    char text[4];
    snprintf(text, sizeof(text), "%lu S", momentum_settings.favorite_timeout);
    variable_item_set_current_value_text(item, momentum_settings.favorite_timeout ? text : "关闭");

    variable_item_list_set_enter_callback(
        var_item_list, momentum_app_scene_interface_filebrowser_var_item_list_callback, app);

    variable_item_list_set_selected_item(
        var_item_list,
        scene_manager_get_scene_state(app->scene_manager, MomentumAppSceneInterfaceFilebrowser));

    view_dispatcher_switch_to_view(app->view_dispatcher, MomentumAppViewVarItemList);
}

bool momentum_app_scene_interface_filebrowser_on_event(void* context, SceneManagerEvent event) {
    MomentumApp* app = context;
    bool consumed = false;

    if(event.type == SceneManagerEventTypeCustom) {
        scene_manager_set_scene_state(
            app->scene_manager, MomentumAppSceneInterfaceFilebrowser, event.event);
        consumed = true;
        switch(event.event) {
        default:
            break;
        }
    }

    return consumed;
}

void momentum_app_scene_interface_filebrowser_on_exit(void* context) {
    MomentumApp* app = context;
    variable_item_list_reset(app->var_item_list);
}
