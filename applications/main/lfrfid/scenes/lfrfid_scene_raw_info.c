#include "../lfrfid_i.h"

void lfrfid_scene_raw_info_on_enter(void* context) {
    LfRfid* app = context;
    Widget* widget = app->widget;

    if(storage_sd_status(app->storage) != FSE_OK) {
        widget_add_icon_element(widget, 83, 22, &I_WarningDolphinFlip_45x42);
        widget_add_string_element(
            widget, 64, 0, AlignCenter, AlignTop, FontPrimary, "没有 SD 卡！");
        widget_add_string_multiline_element(
            widget,
            0,
            13,
            AlignLeft,
            AlignTop,
            FontSecondary,
            "插入 SD 卡\n"
            "以使用此功能");

    } else {
        widget_add_text_box_element(
            widget,
            0,
            0,
            128,
            64,
            AlignLeft,
            AlignTop,
            "\e#RAW RFID 数据读取器\e#\n"
            "1. 将卡靠近 Flipper\n"
            "2. 按 OK\n"
            "3. 等待数据读取完成",
            false);

        widget_add_button_element(widget, GuiButtonTypeCenter, "OK", lfrfid_widget_callback, app);
    }

    view_dispatcher_switch_to_view(app->view_dispatcher, LfRfidViewWidget);
}

bool lfrfid_scene_raw_info_on_event(void* context, SceneManagerEvent event) {
    LfRfid* app = context;
    SceneManager* scene_manager = app->scene_manager;
    bool consumed = false;

    if(event.type == SceneManagerEventTypeBack) {
        consumed = true;
        scene_manager_search_and_switch_to_previous_scene(scene_manager, LfRfidSceneExtraActions);
    } else if(event.type == SceneManagerEventTypeCustom) {
        consumed = true;
        if(event.event == GuiButtonTypeCenter) {
            scene_manager_next_scene(scene_manager, LfRfidSceneRawRead);
        } else if(event.event == GuiButtonTypeLeft) {
            scene_manager_search_and_switch_to_previous_scene(
                scene_manager, LfRfidSceneExtraActions);
        }
    }

    return consumed;
}

void lfrfid_scene_raw_info_on_exit(void* context) {
    LfRfid* app = context;
    widget_reset(app->widget);
}
