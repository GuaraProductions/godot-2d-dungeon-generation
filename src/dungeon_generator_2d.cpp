#include"dungeon_generator_2d.h"
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/scene_tree.hpp>

#include <godot_cpp/classes/engine.hpp>

using namespace godot;

void DungeonGenerator2D::_bind_methods() {



	ClassDB::bind_method(D_METHOD("get_on_ready"), &DungeonGenerator2D::get_on_ready);
	ClassDB::bind_method(D_METHOD("set_on_ready", "p_on_ready"), &DungeonGenerator2D::set_on_ready);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "on_ready"), 
	             "set_on_ready", "get_on_ready"); 

	ClassDB::bind_method(D_METHOD("get_use_cache"), &DungeonGenerator2D::get_use_cache);
	ClassDB::bind_method(D_METHOD("set_use_cache", "p_use_cache"), &DungeonGenerator2D::set_use_cache);
	ADD_PROPERTY(PropertyInfo(Variant::NIL, "Cache", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_CATEGORY, ""), 
	             "set_use_cache", "get_use_cache"); 
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "use_cache", PROPERTY_HINT_NONE), 
	             "set_use_cache", "get_use_cache"); 

	ClassDB::bind_method(D_METHOD("get_print_in_terminal"), &DungeonGenerator2D::get_print_in_terminal);
	ClassDB::bind_method(D_METHOD("set_print_in_terminal","value"), &DungeonGenerator2D::set_print_in_terminal);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "print_in_terminal"), "set_print_in_terminal", "get_print_in_terminal");

	ClassDB::bind_method(D_METHOD("get_dungeon_size"), &DungeonGenerator2D::get_dungeon_size);
	ClassDB::bind_method(D_METHOD("set_dungeon_size","p_dungeon_size"), &DungeonGenerator2D::set_dungeon_size);
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR2I, "dungeon_size"), "set_dungeon_size", "get_dungeon_size");

	BIND_ENUM_CONSTANT(EMPTY);
	BIND_ENUM_CONSTANT(ROOM);
	BIND_ENUM_CONSTANT(CORRIDOR);
}

DungeonGenerator2D::DungeonGenerator2D() {

}

DungeonGenerator2D::~DungeonGenerator2D() {
	
}

void DungeonGenerator2D::set_on_ready(bool p_on_ready) {
	on_ready = p_on_ready;
}

bool DungeonGenerator2D::get_on_ready() const {
	return on_ready;
}

void DungeonGenerator2D::set_use_cache(bool p_use_cache) {
	use_cache = p_use_cache;
}

bool DungeonGenerator2D::get_use_cache() const {
	return use_cache;
}

bool DungeonGenerator2D::get_print_in_terminal() const{
	return print_in_terminal;
}

void DungeonGenerator2D::set_print_in_terminal(bool p_print_in_terminal) {
	print_in_terminal= p_print_in_terminal;
}

godot::Vector2i DungeonGenerator2D::get_dungeon_size() const {
	return dungeon_size;
}

void DungeonGenerator2D::set_dungeon_size(godot::Vector2i p_dungeon_size) {
	dungeon_size = p_dungeon_size;
}