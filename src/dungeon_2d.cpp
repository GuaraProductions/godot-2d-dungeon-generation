#include"dungeon_2d.h"

#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/variant/typed_array.hpp>
#include <vector_marker_2d.h>

using namespace godot;

void Dungeon2DCpp::_bind_methods() {
    ClassDB::bind_method(D_METHOD("remove_tile_from_door"), &Dungeon2DCpp::remove_tile_from_door);
}

Dungeon2DCpp::Dungeon2DCpp() {
    room_size = Vector2(0,0);
}

Dungeon2DCpp::~Dungeon2DCpp() {
	
}

void Dungeon2DCpp::_ready() {

	if (godot::Engine::get_singleton()->is_editor_hint()) return;
    
    SceneTree* scene_tree = get_tree();

    TypedArray<Node> markers = scene_tree->get_nodes_in_group(VectorMarker2DCpp::get_group_name());

    for (int i = 0; i < markers.size(); i++) {
        VectorMarker2DCpp* marker = Object::cast_to<VectorMarker2DCpp>(markers[i]);

        exits_and_vectors[marker->get_direction()] = marker;
    }

    godot::UtilityFunctions::print("dictionary: ", exits_and_vectors);
}

void Dungeon2DCpp::remove_tile_from_door(Vector2i direction) {

    if (exits_and_vectors.has(direction)) {

        VectorMarker2DCpp* direction = Object::cast_to<VectorMarker2DCpp>(exits_and_vectors[direction]);

        for (int i = 0; i < get_child_count(); i++) {
            VectorMarker2DCpp* child = Object::cast_to<VectorMarker2DCpp>(get_child(i));
            if (child) {
                child->queue_free();
                child = nullptr;
            }
        }
    }
}