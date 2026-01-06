/**
 * @file dungeon_2d.h
 * @brief Represents a 2D dungeon room or section in the dungeon generation system.
 */

#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/variant/vector2i.hpp>
#include <godot_cpp/variant/dictionary.hpp>
#include <godot_cpp/variant/variant.hpp>

#pragma once

namespace godot {

/**
 * @class Dungeon2DCpp
 * @brief Represents a single dungeon room with exits and connections.
 * 
 * Dungeon2DCpp is a Node2D-based class that manages a single dungeon room,
 * including its size, exits, and door management. It tracks vector markers
 * that indicate where doors and exits are located.
 * 
 * @extends Node2D
 */
class Dungeon2DCpp : public Node2D {
	GDCLASS(Dungeon2DCpp, Node2D)

private:
	/// Size of the room in 2D space.
    Vector2 room_size;
	
	/// Dictionary mapping exit directions to their corresponding vector markers.
    Dictionary exits_and_vectors;

protected:
	/**
	 * @brief Binds methods to be accessible from GDScript.
	 */
	static void _bind_methods();

public:
	/**
	 * @brief Default constructor.
	 */
    Dungeon2DCpp();
	
	/**
	 * @brief Destructor.
	 */
    ~Dungeon2DCpp();

	/**
	 * @brief Called when the node is ready in the scene tree.
	 * 
	 * Initializes the dungeon room by finding all VectorMarker2D nodes
	 * and mapping them to their respective directions.
	 */
	void _ready() override;
	
	/**
	 * @brief Removes tiles from a door in the specified direction.
	 * 
	 * This method removes all child nodes from the vector marker corresponding
	 * to the given direction, effectively removing the door tiles.
	 * 
	 * @param direction The direction of the door to remove tiles from.
	 */
	void remove_tile_from_door(Vector2i direction);

	/**
	 * @brief Gets the size of the room.
	 * @return Vector2 containing the room dimensions.
	 */
    Vector2 get_room_size() const;
	
	/**
	 * @brief Sets the room size (currently not implemented).
	 */
    void set_room_size();
};

} // namespace godot