#include "../xvirus_app.h"

enum VarItemListIndex {
    VarItemListIndexSortDirsFirst,
    VarItemListIndexRgbBacklight,
    VarItemListIndexChangeDeviceName,
    VarItemListIndexExperimentalOptions,
    VarItemListIndexDarkMode,
    VarItemListIndexLeftHanded,
};

void xvirus_app_scene_misc_var_item_list_callback(void* context, uint32_t index) {
    XvirusApp* app = context;
    view_dispatcher_send_custom_event(app->view_dispatcher, index);
}

static void xvirus_app_scene_misc_lcd_color_changed(VariableItem* item) {
    XvirusApp* app = variable_item_get_context(item);
    uint8_t index = variable_item_get_current_value_index(item);
    variable_item_set_current_value_text(item, rgb_backlight_get_color_text(index));
    rgb_backlight_set_color(index);
    notification_message(app->notification, &sequence_display_backlight_on);
}

static void xvirus_app_scene_misc_rgb_backlight_changed(VariableItem* item) {
    XvirusApp* app = variable_item_get_context(item);
    bool value = variable_item_get_current_value_index(item);
    variable_item_set_current_value_text(item, value ? "ON" : "OFF");
    XVIRUS_SETTINGS()->rgb_backlight = value;
    app->save_settings = true;
    notification_message(app->notification, &sequence_display_backlight_on);
}

static void xvirus_app_scene_misc_sort_dirs_first_changed(VariableItem* item) {
    XvirusApp* app = variable_item_get_context(item);
    bool value = variable_item_get_current_value_index(item);
    variable_item_set_current_value_text(item, value ? "ON" : "OFF");
    XVIRUS_SETTINGS()->sort_dirs_first = value;
    app->save_settings = true;
}

static void xvirus_app_scene_misc_dark_mode_changed(VariableItem* item) {
    XvirusApp* app = variable_item_get_context(item);
    bool value = variable_item_get_current_value_index(item);
    variable_item_set_current_value_text(item, value ? "ON" : "OFF");
    XVIRUS_SETTINGS()->dark_mode = value;
    app->save_settings = true;
}

static void xvirus_app_scene_misc_left_handed_changed(VariableItem* item) {
    XvirusApp* app = variable_item_get_context(item);
    bool value = variable_item_get_current_value_index(item);
    variable_item_set_current_value_text(item, value ? "ON" : "OFF");
    XVIRUS_SETTINGS()->left_handed = value;
    app->save_settings = true;
}

void xvirus_app_scene_misc_on_enter(void* context) {
    XvirusApp* app = context;
    XvirusSettings* xvirus_settings = XVIRUS_SETTINGS();
    VariableItemList* var_item_list = app->var_item_list;
    VariableItem* item;

    item = variable_item_list_add(
        var_item_list, "Sort Dirs First", 2, xvirus_app_scene_misc_sort_dirs_first_changed, app);
    variable_item_set_current_value_index(item, xvirus_settings->sort_dirs_first);
    variable_item_set_current_value_text(item, xvirus_settings->sort_dirs_first ? "ON" : "OFF");

    variable_item_list_add(var_item_list, "Change Device Name", 0, NULL, app);

       item = variable_item_list_add(
        var_item_list, "RGB Backlight", 2, xvirus_app_scene_misc_rgb_backlight_changed, app);
    variable_item_set_current_value_index(item, xvirus_settings->rgb_backlight);
    variable_item_set_current_value_text(item, xvirus_settings->rgb_backlight ? "ON" : "OFF");

    item = variable_item_list_add(
        var_item_list, "LCD Color", rgb_backlight_get_color_count(), xvirus_app_scene_misc_lcd_color_changed, app);
    value_index = rgb_backlight_get_settings()->display_color_index;
    variable_item_set_current_value_index(item, value_index);
    variable_item_set_current_value_text(item, rgb_backlight_get_color_text(value_index));
    variable_item_set_locked(item, !xvirus_settings->rgb_backlight, "Needs RGB\nBacklight!");


    variable_item_list_add(var_item_list, "      Experimental Options:", 0, NULL, app);

    item = variable_item_list_add(
        var_item_list, "Dark Mode", 2, xvirus_app_scene_misc_dark_mode_changed, app);
    variable_item_set_current_value_index(item, xvirus_settings->dark_mode);
    variable_item_set_current_value_text(item, xvirus_settings->dark_mode ? "ON" : "OFF");

    item = variable_item_list_add(
        var_item_list, "Left Handed", 2, xvirus_app_scene_misc_left_handed_changed, app);
    variable_item_set_current_value_index(item, xvirus_settings->left_handed);
    variable_item_set_current_value_text(item, xvirus_settings->left_handed ? "ON" : "OFF");

    variable_item_list_set_enter_callback(
        var_item_list, xvirus_app_scene_misc_var_item_list_callback, app);

    variable_item_list_set_selected_item(
        var_item_list, scene_manager_get_scene_state(app->scene_manager, XvirusAppSceneMisc));

    view_dispatcher_switch_to_view(app->view_dispatcher, XvirusAppViewVarItemList);
}

bool xvirus_app_scene_misc_on_event(void* context, SceneManagerEvent event) {
    XvirusApp* app = context;
    bool consumed = false;

    if(event.type == SceneManagerEventTypeCustom) {
        scene_manager_set_scene_state(app->scene_manager, XvirusAppSceneMisc, event.event);
        consumed = true;
        switch(event.event) {
        case VarItemListIndexChangeDeviceName:
            scene_manager_next_scene(app->scene_manager, XvirusAppSceneMiscRename);
            break;
        default:
            break;
        }
    }

    return consumed;
}

void xvirus_app_scene_misc_on_exit(void* context) {
    XvirusApp* app = context;
    variable_item_list_reset(app->var_item_list);
}
