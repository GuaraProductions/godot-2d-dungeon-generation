#pragma once

#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/array.hpp>
#include <godot_cpp/variant/vector2i.hpp>

/*
## Quantidade de salas presentes em uma cena
@export var executar_no_ready : bool = false
@export var tamanho_dungeon : Vector2i
@export var gerador_de_salas : GeradorSala2D
@export var gerador_de_corredores : GeradorCorredor2D
## Cenas que serão usadas como salas (Precisam ser do tipo DungeonRoom)
@export_category("Cenas")
@export var dungeons : DungeonCollection2D
## Cenas que serão usadas como corredores (Precisam ser do tipo DungeonRoom)
@export var corredores : DungeonCollection2D
## Indica o tamanho de cada sala (dungeon e corredor)
@export var tamanho_sala : Vector2i
## Matrix 2D representando a dungeon
@export_category("Cache")
@export var usar_cache : bool
@export var dungeon_cache : DungeonCache
@export_category("Debug")
@export var executar_no_editor : bool = false
@export var imprimir_dungeon_no_terminal : bool = false

*/

namespace godot {

class DungeonGenerator2D : public Node2D {
	GDCLASS(DungeonGenerator2D, Node2D)

private:

	bool on_ready;
	bool use_cache;
	bool print_in_terminal;
	godot::Vector2i dungeon_size;
	godot::Vector2i room_size;
	//RoomGenerator2D
	//CorridorGenerator2D
	//DungeonCollection2D (Rooms)
	//DungeonCollection2D (Corridors)
	godot::Array dungeon_grid ;
	//DungeonCache2D

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

	void set_on_ready(bool p_on_ready);
	bool get_on_ready() const;

	void set_use_cache(bool p_use_cache);
	bool get_use_cache() const;

	void set_print_in_terminal(bool p_print_in_terminal);
	bool get_print_in_terminal() const;

	void set_dungeon_size(godot::Vector2i p_dungeon_size);
	godot::Vector2i get_dungeon_size() const;
};

} // namespace godot

VARIANT_ENUM_CAST(DungeonGenerator2D::CellType);