#include"dungeon_generator_2d.h"
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/scene_tree.hpp>

#include <godot_cpp/classes/engine.hpp>

using namespace godot;

void DungeonGenerator2D::_bind_methods() {

	ClassDB::bind_method(D_METHOD("get_room_generator"), &DungeonGenerator2D::get_room_generator);
	ClassDB::bind_method(D_METHOD("set_room_generator", "p_room_generator"), &DungeonGenerator2D::set_room_generator);
	ADD_PROPERTY(
		PropertyInfo(
			Variant::OBJECT, 
			"room_generator",
			PROPERTY_HINT_NODE_TYPE,
			"RoomGenerator"), 
		"set_room_generator",
		"get_room_generator");

	ClassDB::bind_method(D_METHOD("get_corridor_generator"), &DungeonGenerator2D::get_corridor_generator);
	ClassDB::bind_method(D_METHOD("set_corridor_generator", "p_corridor_generator"), &DungeonGenerator2D::set_corridor_generator);
	ADD_PROPERTY(
		PropertyInfo(
			Variant::OBJECT, 
			"corridor_generator",
			PROPERTY_HINT_NODE_TYPE,
			"CorridorGenerator"), 
		"set_corridor_generator",
		"get_corridor_generator");

    ClassDB::bind_method(D_METHOD("get_room_collection"), &DungeonGenerator2D::get_room_collection);
    ClassDB::bind_method(D_METHOD("set_room_collection", "p_room_collection"), &DungeonGenerator2D::set_room_collection);
	ADD_PROPERTY(
        PropertyInfo(
            Variant::OBJECT, 
            "room_collection", 
            PROPERTY_HINT_RESOURCE_TYPE, 
            "DungeonCollectionCpp"
    ),
	"set_room_collection",
	"get_room_collection"
	);

    ClassDB::bind_method(D_METHOD("get_corridor_collection"), &DungeonGenerator2D::get_corridor_collection);
    ClassDB::bind_method(D_METHOD("set_corridor_collection", "p_corridor_collection"), &DungeonGenerator2D::set_corridor_collection);
	ADD_PROPERTY(
        PropertyInfo(
            Variant::OBJECT, 
            "corridor_collection", 
            PROPERTY_HINT_RESOURCE_TYPE, 
            "DungeonCollectionCpp"
    ),
	"set_corridor_collection",
	"get_corridor_collection"
	);

	ClassDB::bind_method(D_METHOD("get_on_ready"), &DungeonGenerator2D::get_on_ready);
	ClassDB::bind_method(D_METHOD("set_on_ready", "p_on_ready"), &DungeonGenerator2D::set_on_ready);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "on_ready"), 
	             "set_on_ready", "get_on_ready"); 

	ClassDB::bind_method(D_METHOD("get_use_cache"), &DungeonGenerator2D::get_use_cache);
	ClassDB::bind_method(D_METHOD("set_use_cache", "p_use_cache"), &DungeonGenerator2D::set_use_cache);
	
	// Cria a categoria dentro do inspetor
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
	room_generator = nullptr;
	corridor_generator = nullptr;
	on_ready = false;
	use_cache = false;
	print_in_terminal = false;
	dungeon_size = Vector2i(0, 0);
	room_size = Vector2i(0, 0);
	dungeon_grid = nullptr;
}

DungeonGenerator2D::~DungeonGenerator2D() {
}

void DungeonGenerator2D::_ready() {
	
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

void DungeonGenerator2D::set_room_generator(RoomGenerator* p_room_generator) {
	room_generator = p_room_generator;
}

RoomGenerator* DungeonGenerator2D::get_room_generator() const {
	return room_generator;
}

void DungeonGenerator2D::set_corridor_generator(CorridorGenerator* p_corridor_generator) {
	corridor_generator = p_corridor_generator;
}

CorridorGenerator* DungeonGenerator2D::get_corridor_generator() const {
	return corridor_generator;
}

void DungeonGenerator2D::set_room_collection(Ref<DungeonCollectionCpp> p_available_rooms) {
	available_rooms = p_available_rooms;
}

Ref<DungeonCollectionCpp> DungeonGenerator2D::get_room_collection() const {
	return available_rooms;
}

void DungeonGenerator2D::set_corridor_collection(Ref<DungeonCollectionCpp> p_available_corridors) {
	available_corridors = p_available_corridors;
}

Ref<DungeonCollectionCpp> DungeonGenerator2D::get_corridor_collection() const {
	return available_corridors;
}