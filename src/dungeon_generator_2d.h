/**
 * @file dungeon_generator_2d.h
 * @brief Main controller for procedural 2D dungeon generation.
 */

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

/**
 * @class DungeonGenerator2D
 * @brief Main controller for generating procedural 2D dungeons.
 * 
 * DungeonGenerator2D orchestrates the complete dungeon generation process by managing
 * room and corridor generation, maintaining a grid-based dungeon layout, and instantiating
 * dungeon elements in the scene. It supports configurable room and corridor generators,
 * caching, and debug output.
 * 
 * @extends Node2D
 */
class DungeonGenerator2D : public Node2D {
	GDCLASS(DungeonGenerator2D, Node2D)

private:
	/// Whether to generate the dungeon automatically on _ready().
	bool on_ready;
	
	/// Whether to use cached dungeon data.
	bool use_cache;
	
	/// Whether to print debug information to the terminal.
	bool print_in_terminal;
	
	/// Whether the dungeon grid has been initialized.
	bool grid_initialized;

	/// Size of the entire dungeon in grid cells.
	Vector2i dungeon_size;
	
	/// Size of each room in pixels or units.
	Vector2i room_size;

	/// Pointer to the room generator node.
	RoomGenerator* room_generator;
	
	/// Pointer to the corridor generator node.
	CorridorGenerator* corridor_generator;

	/// Collection of available room scenes.
	Ref<DungeonCollectionCpp> available_rooms;
	
	/// Collection of available corridor scenes.
	Ref<DungeonCollectionCpp> available_corridors;

	/// 2D array representing the dungeon grid layout.
	int** dungeon_grid;

	/**
	 * @brief Main dungeon generation logic.
	 * 
	 * Coordinates the room and corridor generation process to create a complete dungeon.
	 */
	void generate_dungeon();
	
	/**
	 * @brief Initializes the dungeon grid array.
	 * 
	 * Allocates memory for the 2D grid based on dungeon_size.
	 */
    void init_dungeon_grid();
	
	/**
	 * @brief Frees the dungeon grid array memory.
	 */
    void free_dungeon_grid();

protected:
	/**
	 * @brief Binds methods, properties, and enums to be accessible from GDScript.
	 */
	static void _bind_methods();

public:
	/**
	 * @enum CellType
	 * @brief Represents the type of cell in the dungeon grid.
	 */
	enum CellType {
		EMPTY,    ///< Empty cell with no dungeon element
		ROOM,     ///< Cell containing a room
		CORRIDOR  ///< Cell containing a corridor
	};

	/**
	 * @brief Default constructor.
	 */
	DungeonGenerator2D();
	
	/**
	 * @brief Destructor - frees dungeon grid memory.
	 */
	~DungeonGenerator2D();

	/**
	 * @brief Called when the node is ready in the scene tree.
	 * 
	 * Triggers dungeon generation if on_ready is enabled.
	 */
	void _ready() override;

	/**
	 * @brief Sets whether to generate dungeon on ready.
	 * @param p_on_ready True to auto-generate on _ready().
	 */
	void set_on_ready(bool p_on_ready);
	
	/**
	 * @brief Gets the on_ready flag value.
	 * @return True if dungeon will generate on _ready().
	 */
	bool get_on_ready() const;

	/**
	 * @brief Sets whether to use cached dungeon data.
	 * @param p_use_cache True to enable caching.
	 */
	void set_use_cache(bool p_use_cache);
	
	/**
	 * @brief Gets the use_cache flag value.
	 * @return True if caching is enabled.
	 */
	bool get_use_cache() const;

	/**
	 * @brief Sets whether to print debug information.
	 * @param p_print_in_terminal True to enable terminal output.
	 */
	void set_print_in_terminal(bool p_print_in_terminal);
	
	/**
	 * @brief Gets the print_in_terminal flag value.
	 * @return True if terminal printing is enabled.
	 */
	bool get_print_in_terminal() const;

	/**
	 * @brief Sets the room generator node.
	 * @param p_room_generator Pointer to RoomGenerator instance.
	 */
	void set_room_generator(RoomGenerator* p_room_generator);
	
	/**
	 * @brief Gets the room generator node.
	 * @return Pointer to the current RoomGenerator.
	 */
	RoomGenerator* get_room_generator() const;

	/**
	 * @brief Sets the corridor generator node.
	 * @param p_corridor_generator Pointer to CorridorGenerator instance.
	 */
	void set_corridor_generator(CorridorGenerator* p_corridor_generator);
	
	/**
	 * @brief Gets the corridor generator node.
	 * @return Pointer to the current CorridorGenerator.
	 */
	CorridorGenerator* get_corridor_generator() const;

	/**
	 * @brief Sets the collection of available room scenes.
	 * @param p_available_rooms Reference to DungeonCollectionCpp resource.
	 */
	void set_room_collection(Ref<DungeonCollectionCpp> p_available_rooms);
	
	/**
	 * @brief Gets the room collection.
	 * @return Reference to the DungeonCollectionCpp containing room scenes.
	 */
	Ref<DungeonCollectionCpp> get_room_collection() const;

	/**
	 * @brief Sets the collection of available corridor scenes.
	 * @param p_corridor_collection Reference to DungeonCollectionCpp resource.
	 */
	void set_corridor_collection(Ref<DungeonCollectionCpp> p_corridor_collection);
	
	/**
	 * @brief Gets the corridor collection.
	 * @return Reference to the DungeonCollectionCpp containing corridor scenes.
	 */
	Ref<DungeonCollectionCpp> get_corridor_collection() const;

	/**
	 * @brief Sets the size of the dungeon grid.
	 * @param p_dungeon_size Vector2i specifying width and height in grid cells.
	 */
	void set_dungeon_size(Vector2i p_dungeon_size);
	
	/**
	 * @brief Gets the dungeon grid size.
	 * @return Vector2i containing the dungeon dimensions.
	 */
	Vector2i get_dungeon_size() const;

	/**
	 * @brief Sets the size of individual rooms.
	 * @param p_dungeon_size Vector2i specifying room width and height.
	 */
	void set_room_size(Vector2i p_dungeon_size);
	
	/**
	 * @brief Gets the room size.
	 * @return Vector2i containing the room dimensions.
	 */
	Vector2i get_room_size() const;

	/**
	 * @brief Prints a text representation of the dungeon grid to the terminal.
	 */
	void print_dungeon_in_text();

	/**
	 * @brief Creates and instantiates a room at the specified position.
	 * @param position Grid position where the room should be placed.
	 * @param direction Optional direction vector for room orientation (default: Vector2i(0,0)).
	 * @return Pointer to the created Dungeon2DCpp room instance.
	 */
	Dungeon2DCpp* create_room(Vector2i position, Vector2i direction = Vector2i(0,0));
	
	/**
	 * @brief Creates and instantiates a corridor at the specified position.
	 * @param position Grid position where the corridor should be placed.
	 * @return Pointer to the created Dungeon2DCpp corridor instance.
	 */
	Dungeon2DCpp* create_corridor(Vector2i position);
	
	/**
	 * @brief Gets the dungeon element at the specified grid position.
	 * @param position Grid coordinates to query.
	 * @return Pointer to the Dungeon2DCpp at that position, or nullptr if none exists.
	 */
	Dungeon2DCpp* get_dungeon_in(Vector2i position);
	
	/**
	 * @brief Checks if a dungeon element exists at the specified position.
	 * @param position Grid coordinates to check.
	 * @return True if a dungeon element exists at the position.
	 */
	bool exists_dungeon_in(Vector2i position);
	
	/**
	 * @brief Checks if the specified grid position is empty.
	 * @param position Grid coordinates to check.
	 * @return True if the position is empty (no room or corridor).
	 */
	bool is_empty(Vector2i position);
};

} // namespace godot

VARIANT_ENUM_CAST(DungeonGenerator2D::CellType);