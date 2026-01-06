/**
 * @file room_generator.h
 * @brief Base class for room generation algorithms in dungeon generation.
 */

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/variant/typed_array.hpp>
#include <godot_cpp/variant/vector2i.hpp>
#include <godot_cpp/variant/variant.hpp>

#pragma once

namespace godot {

/**
 * @class RoomGenerator
 * @brief Base class for implementing room generation algorithms.
 * 
 * RoomGenerator is an abstract base class that defines the interface for generating
 * room positions in a procedurally generated dungeon. Derived classes should implement
 * specific algorithms for distributing rooms across the dungeon space.
 * 
 * @extends Node
 */
class RoomGenerator : public Node {
	GDCLASS(RoomGenerator, Node)

private:
	/// Reference to the parent dungeon generator node.
	Node* dungeon_generator;

protected:
	/**
	 * @brief Binds methods to be accessible from GDScript.
	 */
	static void _bind_methods();

public:
	/**
	 * @brief Default constructor.
	 */
	RoomGenerator();
	
	/**
	 * @brief Destructor.
	 */
	~RoomGenerator();

	/**
	 * @brief Called when the node is ready in the scene tree.
	 * 
	 * Initializes the room generator and gets a reference to the parent dungeon generator.
	 */
	void _ready() override;
	
	/**
	 * @brief Generates room positions within the given dimensions.
	 * 
	 * This is a virtual method that should be overridden in derived classes to implement
	 * specific room generation algorithms (e.g., Poisson disk sampling, grid-based, random).
	 * 
	 * @param dimension Vector2i specifying the width and height of the dungeon area.
	 * @return TypedArray of Vector2i coordinates representing room positions.
	 */
	virtual TypedArray<Vector2i> generate_rooms(Vector2i dimension);
};

} // namespace godot