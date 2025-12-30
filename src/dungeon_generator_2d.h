#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/array.hpp>
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/variant/typed_array.hpp>
#include <godot_cpp/variant/vector2i.hpp>
#include <godot_cpp/variant/variant.hpp>
#include "room_generator.h"
#include "corridor_generator.h"
#include "dungeon_2d.h"
#include "dungeon_collection.h"

#pragma once


namespace godot {

class DungeonGenerator2D : public Node2D {
	GDCLASS(DungeonGenerator2D, Node2D)

private:

	bool on_ready;
	bool use_cache;
	bool print_in_terminal;
	bool grid_initialized;

	Vector2i dungeon_size;
	Vector2i room_size;

	RoomGenerator* room_generator;
	CorridorGenerator* corridor_generator;

	Ref<DungeonCollectionCpp> available_rooms;
	Ref<DungeonCollectionCpp> available_corridors;

	int** dungeon_grid;

	void generate_dungeon();
    void init_dungeon_grid();
    void free_dungeon_grid();

protected:
	static void _bind_methods();

public:

	enum CellType {
		EMPTY,
		ROOM,
		CORRIDOR
	};

	DungeonGenerator2D();
	~DungeonGenerator2D();

	void _ready() override;

	void set_on_ready(bool p_on_ready);
	bool get_on_ready() const;

	void set_use_cache(bool p_use_cache);
	bool get_use_cache() const;

	void set_print_in_terminal(bool p_print_in_terminal);
	bool get_print_in_terminal() const;

	void set_room_generator(RoomGenerator* p_room_generator);
	RoomGenerator* get_room_generator() const;

	void set_corridor_generator(CorridorGenerator* p_corridor_generator);
	CorridorGenerator* get_corridor_generator() const;

	void set_room_collection(Ref<DungeonCollectionCpp> p_available_rooms);
	Ref<DungeonCollectionCpp> get_room_collection() const;

	void set_corridor_collection(Ref<DungeonCollectionCpp> p_corridor_collection);
	Ref<DungeonCollectionCpp> get_corridor_collection() const;

	void set_dungeon_size(Vector2i p_dungeon_size);
	Vector2i get_dungeon_size() const;

	void set_room_size(Vector2i p_dungeon_size);
	Vector2i get_room_size() const;

	void print_dungeon_in_text();

	Dungeon2DCpp* create_room(Vector2i position, Vector2i direction = Vector2i(0,0));
	Dungeon2DCpp* create_corridor(Vector2i position);
	Dungeon2DCpp* get_dungeon_in(Vector2i position);
	bool exists_dungeon_in(Vector2i position);
	bool is_empty(Vector2i position);
};

} // namespace godot

VARIANT_ENUM_CAST(DungeonGenerator2D::CellType);