#include"corridor_generator.h"

#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/variant/typed_array.hpp>
#include <godot_cpp/variant/vector2i.hpp>
#include <godot_cpp/variant/variant.hpp>

using namespace godot;

void CorridorGenerator::_bind_methods() {
    ClassDB::bind_method(D_METHOD("generate_corridor", "points"),&CorridorGenerator::generate_corridor);
}

CorridorGenerator::CorridorGenerator() {

}

CorridorGenerator::~CorridorGenerator() {
	
}

void CorridorGenerator::_ready() {

	if (godot::Engine::get_singleton()->is_editor_hint()) return;
    
    Node* node_pai = get_parent();

    dungeon_generator = node_pai;

	godot::UtilityFunctions::print("DungeonGenerator: ", dungeon_generator);
}

void CorridorGenerator::generate_corridor(TypedArray<Vector2i> points) {

}