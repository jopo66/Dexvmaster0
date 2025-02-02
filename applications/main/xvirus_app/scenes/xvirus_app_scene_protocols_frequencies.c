#include "../xvirus_app.h"

enum VarItemListIndex {
    VarItemListIndexUseDefaults,
    VarItemListIndexStaticFrequencies,
    VarItemListIndexHopperFrequencies,
};

void xvirus_app_scene_protocols_frequencies_var_item_list_callback(void* context, uint32_t index) {
    XvirusApp* app = context;
    view_dispatcher_send_custom_event(app->view_dispatcher, index);
}

static void xvirus_app_scene_protocols_frequencies_use_defaults_changed(VariableItem* item) {
    XvirusApp* app = variable_item_get_context(item);
    bool value = variable_item_get_current_value_index(item);
    variable_item_set_current_value_text(item, value ? "ON" : "OFF");
    app->subghz_use_defaults = value;
    app->save_subghz_frequencies = true;
}

void xvirus_app_scene_protocols_frequencies_on_enter(void* context) {
    XvirusApp* app = context;
    VariableItemList* var_item_list = app->var_item_list;
    VariableItem* item;

    item = variable_item_list_add(
        var_item_list,
        "Use Defaults",
        2,
        xvirus_app_scene_protocols_frequencies_use_defaults_changed,
        app);
    variable_item_set_current_value_index(item, app->subghz_use_defaults);
    variable_item_set_current_value_text(item, app->subghz_use_defaults ? "ON" : "OFF");

    variable_item_list_add(var_item_list, "Static Frequencies", 0, NULL, app);

    variable_item_list_add(var_item_list, "Hopper Frequencies", 0, NULL, app);

    variable_item_list_set_enter_callback(
        var_item_list, xvirus_app_scene_protocols_frequencies_var_item_list_callback, app);

    variable_item_list_set_selected_item(
        var_item_list,
        scene_manager_get_scene_state(app->scene_manager, XvirusAppSceneProtocolsFrequencies));

    view_dispatcher_switch_to_view(app->view_dispatcher, XvirusAppViewVarItemList);
}

bool xvirus_app_scene_protocols_frequencies_on_event(void* context, SceneManagerEvent event) {
    XvirusApp* app = context;
    bool consumed = false;

    if(event.type == SceneManagerEventTypeCustom) {
        scene_manager_set_scene_state(
            app->scene_manager, XvirusAppSceneProtocolsFrequencies, event.event);
        consumed = true;
        switch(event.event) {
        case VarItemListIndexStaticFrequencies:
            scene_manager_next_scene(app->scene_manager, XvirusAppSceneProtocolsFrequenciesStatic);
            break;
        case VarItemListIndexHopperFrequencies:
            scene_manager_next_scene(app->scene_manager, XvirusAppSceneProtocolsFrequenciesHopper);
            break;
        default:
            break;
        }
    }

    return consumed;
}

void xvirus_app_scene_protocols_frequencies_on_exit(void* context) {
    XvirusApp* app = context;
    variable_item_list_reset(app->var_item_list);
}
