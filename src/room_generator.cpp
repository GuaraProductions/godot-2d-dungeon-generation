#include"room_generator.h"

#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/variant/typed_array.hpp>
#include <godot_cpp/variant/vector2i.hpp>
#include <godot_cpp/variant/variant.hpp>

using namespace godot;

void RoomGenerator::_bind_methods() {
    ClassDB::bind_method(D_METHOD("generate_rooms", "dimension"),&RoomGenerator::generate_rooms);
}

RoomGenerator::RoomGenerator() {

}

RoomGenerator::~RoomGenerator() {
	
}

void RoomGenerator::_ready() {

	if (godot::Engine::get_singleton()->is_editor_hint()) return;
    
    Node* node_pai = get_parent();

    dungeon_generator = node_pai;
}
	

TypedArray<Vector2i> RoomGenerator::generate_rooms(Vector2i dimension) {
    return TypedArray<Vector2i>();
}