#include "../storage_settings.h"
#include <furi_hal_version.h>
#include <furi_hal_flash.h>

static void
    storage_settings_scene_internal_info_dialog_callback(DialogExResult result, void* context) {
    StorageSettings* app = context;

    view_dispatcher_send_custom_event(app->view_dispatcher, result);
}

void storage_settings_scene_internal_info_on_enter(void* context) {
    StorageSettings* app = context;
    uint64_t total_space;
    uint64_t free_space;
    FS_Error error =
        storage_common_fs_info(app->fs_api, STORAGE_INT_PATH_PREFIX, &total_space, &free_space);
    DialogEx* dialog_ex = app->dialog_ex;

    dialog_ex_set_context(dialog_ex, app);
    dialog_ex_set_result_callback(dialog_ex, storage_settings_scene_internal_info_dialog_callback);

    if(error != FSE_OK) {
        dialog_ex_set_header(
            dialog_ex, "内部存储错误", 64, 10, AlignCenter, AlignCenter);
        dialog_ex_set_text(
            dialog_ex, storage_error_get_desc(error), 64, 32, AlignCenter, AlignCenter);
    } else {
        furi_string_printf(
            app->text_string,
            "名称: %s\n类型: 虚拟 (/.int 在 SD 卡上)\n总计: %lu KiB\n剩余: %lu KiB\n",
            furi_hal_version_get_name_ptr() ? furi_hal_version_get_name_ptr() : "未知",
            (uint32_t)(total_space / 1024),
            (uint32_t)(free_space / 1024));

        uint32_t free_flash =
            furi_hal_flash_get_free_end_address() - furi_hal_flash_get_free_start_address();
        if(free_flash < 1024) {
            furi_string_cat_printf(app->text_string, "闪存: %lu B 剩余", free_flash);
        } else {
            furi_string_cat_printf(
                app->text_string, "闪存: %.2f KiB 剩余", (double)free_flash / 1024);
        }

        dialog_ex_set_text(
            dialog_ex, furi_string_get_cstr(app->text_string), 4, 4, AlignLeft, AlignTop);
    }

    view_dispatcher_switch_to_view(app->view_dispatcher, StorageSettingsViewDialogEx);
}

bool storage_settings_scene_internal_info_on_event(void* context, SceneManagerEvent event) {
    StorageSettings* app = context;
    bool consumed = false;

    if(event.type == SceneManagerEventTypeCustom) {
        switch(event.event) {
        case DialogExResultLeft:
            consumed = scene_manager_previous_scene(app->scene_manager);
            break;
        }
    }
    return consumed;
}

void storage_settings_scene_internal_info_on_exit(void* context) {
    StorageSettings* app = context;
    DialogEx* dialog_ex = app->dialog_ex;

    dialog_ex_reset(dialog_ex);

    furi_string_reset(app->text_string);
}
