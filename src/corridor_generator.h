/**
 * @file corridor_generator.h
 * @brief Base class for corridor generation algorithms in dungeon generation.
 */

#pragma once

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/variant/typed_array.hpp>
#include <godot_cpp/variant/vector2i.hpp>
#include <godot_cpp/variant/variant.hpp>

namespace godot {

/**
 * @class CorridorGenerator
 * @brief Base class for implementing corridor generation algorithms.
 * 
 * CorridorGenerator is an abstract base class that defines the interface for generating
 * corridors in a procedurally generated dungeon. Derived classes should implement specific
 * algorithms for connecting rooms with corridors.
 * 
 * @extends Node
 */
class CorridorGenerator : public Node {
	GDCLASS(CorridorGenerator, Node)

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
	CorridorGenerator();
	
	/**
	 * @brief Destructor.
	 */
	~CorridorGenerator();

	/**
	 * @brief Called when the node is ready in the scene tree.
	 * 
	 * Initializes the corridor generator and gets a reference to the parent dungeon generator.
	 */
	void _ready() override;
	
	/**
	 * @brief Generates corridors connecting the given points.
	 * 
	 * This is a virtual method that should be overridden in derived classes to implement
	 * specific corridor generation algorithms.
	 * 
	 * @param points Array of Vector2i coordinates representing room positions to be connected.
	 */
	virtual void generate_corridor(TypedArray<Vector2i> points);
};

} // namespace godot