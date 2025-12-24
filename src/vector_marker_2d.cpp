#include "vector_marker_2d.h"

#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/node.hpp>

using namespace godot;

void VectorMarker2DCpp::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_direction"), &VectorMarker2DCpp::get_direction);
	ClassDB::bind_method(D_METHOD("set_direction", "p_direction"), &VectorMarker2DCpp::set_direction);
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR2I, "direction", PROPERTY_HINT_NONE), 
				 "set_direction", "get_direction");

    ClassDB::bind_static_method("VectorMarker2DCpp", D_METHOD("get_group_name"), &VectorMarker2DCpp::get_group_name);
}

VectorMarker2DCpp::VectorMarker2DCpp() {
    direction = Vector2(0,0);
}

VectorMarker2DCpp::~VectorMarker2DCpp() {
	
}

void VectorMarker2DCpp::_ready() {

	if (godot::Engine::get_singleton()->is_editor_hint()) return;

    add_to_group(get_group_name());
}

Vector2i VectorMarker2DCpp::get_direction() const {
    return direction;
}

void VectorMarker2DCpp::set_direction(Vector2i p_direction) {
    direction = p_direction;
}

godot::String VectorMarker2DCpp::_to_string() {
    return godot::String("VectorMarker2DCpp");
}