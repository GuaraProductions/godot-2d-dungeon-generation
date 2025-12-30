#include"dungeon_generator_2d.h"
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/scene_tree.hpp>

#include <godot_cpp/classes/engine.hpp>

using namespace godot;

void DungeonGenerator2D::_bind_methods() {

	ClassDB::bind_method(D_METHOD("print_dungeon_in_text"), &DungeonGenerator2D::print_dungeon_in_text);	

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
	
	ADD_GROUP("Cache", "");

	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "use_cache", PROPERTY_HINT_NONE), 
	             "set_use_cache", "get_use_cache"); 

	ClassDB::bind_method(D_METHOD("get_print_in_terminal"), &DungeonGenerator2D::get_print_in_terminal);
	ClassDB::bind_method(D_METHOD("set_print_in_terminal","value"), &DungeonGenerator2D::set_print_in_terminal);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "print_in_terminal"), "set_print_in_terminal", "get_print_in_terminal");

	ClassDB::bind_method(D_METHOD("get_dungeon_size"), &DungeonGenerator2D::get_dungeon_size);
	ClassDB::bind_method(D_METHOD("set_dungeon_size","p_dungeon_size"), &DungeonGenerator2D::set_dungeon_size);
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR2I, "dungeon_size"), "set_dungeon_size", "get_dungeon_size");

	ClassDB::bind_method(D_METHOD("get_room_size"), &DungeonGenerator2D::get_room_size);
	ClassDB::bind_method(D_METHOD("set_room_size","p_room_size"), &DungeonGenerator2D::set_room_size);
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR2I, "room_size"), "set_room_size", "get_room_size");

	ClassDB::bind_method(D_METHOD("create_room", "position", "direction"), &DungeonGenerator2D::create_room);
	ClassDB::bind_method(D_METHOD("create_corridor", "position"), &DungeonGenerator2D::create_corridor);
	ClassDB::bind_method(D_METHOD("get_dungeon_in", "position"), &DungeonGenerator2D::get_dungeon_in);
	ClassDB::bind_method(D_METHOD("exists_dungeon_in", "position"), &DungeonGenerator2D::exists_dungeon_in);
	ClassDB::bind_method(D_METHOD("is_empty", "position"), &DungeonGenerator2D::is_empty);

	BIND_ENUM_CONSTANT(EMPTY);
	BIND_ENUM_CONSTANT(ROOM);
	BIND_ENUM_CONSTANT(CORRIDOR);
}

DungeonGenerator2D::DungeonGenerator2D() {
	room_generator = nullptr;
	corridor_generator = nullptr;
	on_ready = false;
	use_cache = false;
	grid_initialized = false;
	print_in_terminal = false;
	dungeon_size = Vector2i(0, 0);
	room_size = Vector2i(0, 0);
	dungeon_grid = nullptr;
}

DungeonGenerator2D::~DungeonGenerator2D() {
	free_dungeon_grid();
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

godot::Vector2i DungeonGenerator2D::get_room_size() const {
	return room_size;
}


void DungeonGenerator2D::set_dungeon_size(godot::Vector2i p_dungeon_size) {
	dungeon_size = p_dungeon_size;
}

void DungeonGenerator2D::set_room_size(godot::Vector2i p_room_size) {
	room_size = p_room_size;
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

void DungeonGenerator2D::_ready() {

	if (godot::Engine::get_singleton()->is_editor_hint()) return;

	if (on_ready) 
		generate_dungeon();
}

void DungeonGenerator2D::free_dungeon_grid() {
	if (dungeon_grid != nullptr && grid_initialized) {
		for (int i = 0; i < dungeon_size.x; i++) {
			delete[] dungeon_grid[i];
		}

		delete[] dungeon_grid;
		dungeon_grid = nullptr;
		grid_initialized = false;
	}
}

void DungeonGenerator2D::init_dungeon_grid() {
	free_dungeon_grid();

	if (dungeon_size.x < 0 || dungeon_size.y < 0) {
		UtilityFunctions::printerr("Não é possível criar uma dungeon com essas dimensões");
		return;
	}

	dungeon_grid = new int*[dungeon_size.x];
	for (int i = 0 ; i < dungeon_size.x; i++) {
		dungeon_grid[i] = new int[dungeon_size.y];
		for (int j = 0; j < dungeon_size.y; j++) {
			dungeon_grid[i][j] = CellType::EMPTY;
		}
	}
	grid_initialized = true;
}

void DungeonGenerator2D::generate_dungeon() {
	init_dungeon_grid();

	TypedArray<Vector2i> points;

	if (dungeon_size.x < 0 || dungeon_size.y < 0) {
		UtilityFunctions::printerr("Não é possível criar uma dungeon com essas dimensões");
		return;
	}

	if (room_generator) {
		points = room_generator->generate_rooms(dungeon_size);
	} else {
		UtilityFunctions::printerr("O node \"RoomGenerator\" não foi atribuido!");
		return;
	}

	if (corridor_generator) {
		corridor_generator->generate_corridor(points);
	} else {
		UtilityFunctions::printerr("O node \"CorridorGenerator\" não foi atribuido!");
		return;
	}

	if (print_in_terminal) {
		print_dungeon_in_text();
	}

}

Dungeon2DCpp* DungeonGenerator2D::create_room(Vector2i position, Vector2i direction) {

	if (!grid_initialized) return nullptr;

	if (position.x < 0 || position.y < 0 
	|| position.x >= dungeon_size.x || position.y >= dungeon_size.x) {
		UtilityFunctions::printerr("Não é possível criar uma dungeon nas coordenadas: ", position);
		return nullptr;
	}

	dungeon_grid[position.x][position.y] = CellType::ROOM;

	Dungeon2DCpp* dungeon_inst = available_rooms->get_random_dungeon();
	if (dungeon_inst == nullptr) {
		UtilityFunctions::printerr("Não foi possível instanciar essa sala");
		return nullptr;
	}

	dungeon_inst->set_name(vformat("%d-%d", position.x, position.y));
	add_child(dungeon_inst);

	dungeon_inst->remove_tile_from_door(direction);

	dungeon_inst->set_global_position(
		Vector2(
			position.x * room_size.x,
			position.y * room_size.y
		)
	);

	return dungeon_inst;
}

Dungeon2DCpp* DungeonGenerator2D::create_corridor(Vector2i position) {

	if (!grid_initialized) return nullptr;

	if (position.x < 0 || position.y < 0 
	|| position.x >= dungeon_size.x || position.y >= dungeon_size.x) {
		UtilityFunctions::printerr("Não é possível criar uma dungeon nas coordenadas: ", position);
		return nullptr;
	}

	dungeon_grid[position.x][position.y] = CellType::CORRIDOR;

	Dungeon2DCpp* dungeon_inst = available_corridors->get_random_dungeon();

	if (dungeon_inst == nullptr) {
		UtilityFunctions::printerr("Não foi possível instanciar essa sala");
		return nullptr;
	}

	dungeon_inst->set_name(vformat("%d-%d", position.x, position.y));
	add_child(dungeon_inst);

	dungeon_inst->set_global_position(
		Vector2(
			position.x * room_size.x,
			position.y * room_size.y
		)
	);

	return dungeon_inst;
}

Dungeon2DCpp* DungeonGenerator2D::get_dungeon_in(Vector2i position) {
	String dungeon_location = vformat("%d-%d", position.x, position.y);
	return Object::cast_to<Dungeon2DCpp>(get_node_or_null(NodePath(dungeon_location)));
}

bool DungeonGenerator2D::exists_dungeon_in(Vector2i position) {
	if (!grid_initialized) return false;
	if (position.x < 0 || position.y < 0 
	|| position.x >= dungeon_size.x || position.y >= dungeon_size.x) {
		UtilityFunctions::printerr("Não é possível criar uma dungeon nas coordenadas: ", position);
		return false;
	}

	return dungeon_grid[position.x][position.y] == CellType::ROOM;
}

bool DungeonGenerator2D::is_empty(Vector2i position) {
	if (!grid_initialized) return false;
	if (position.x < 0 || position.y < 0 
	|| position.x >= dungeon_size.x || position.y >= dungeon_size.x) {
		UtilityFunctions::printerr("Não é possível criar uma dungeon nas coordenadas: ", position);
		return false;
	}

	return dungeon_grid[position.x][position.y] == CellType::EMPTY;
}


void DungeonGenerator2D::print_dungeon_in_text() {
	if (!grid_initialized) return;

	int width = dungeon_size.x;
	int height = dungeon_size.y;

	int pad_x = (int)width/2;
	int pad_y = (int)height/2;

	String output = "";
	
	output += "y\\x\t\t";
	for (int x = 0; x < width; x++) {
		output += vformat("%*d ", pad_x, x);
	}
	output += "\n";

	for (int y = 0; y < height; y++) {

		output += vformat("%*d [", pad_y, y);
		output += " [";
		for (int x = 0; x < width; x++) {
			int value = dungeon_grid[x][y];
			String start_tag = "[color=white]";

			switch (value) {
				case CellType::EMPTY: start_tag = "[color=black]"; break;
				case CellType::ROOM: start_tag = "[color=red]"; break;
				case CellType::CORRIDOR: start_tag = "[color=green]"; break;
			}

			output += vformat("%s%*s[/color] ", start_tag, pad_x, String::num_int64(value));
		}
		output += "]\n";
	}

	UtilityFunctions::print_rich(output);
}