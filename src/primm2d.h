/**
 * @file primm2d.h
 * @brief Prim's algorithm implementation for generating minimum spanning tree corridors.
 */

#include "corridor_generator.h"
#include <godot_cpp/variant/typed_array.hpp>
#include <godot_cpp/variant/vector2i.hpp>
#include <godot_cpp/variant/variant.hpp>

namespace godot {

/**
 * @class Primm2D
 * @brief Implements Prim's algorithm for connecting rooms with corridors.
 * 
 * Primm2D uses Prim's minimum spanning tree algorithm to generate corridors that
 * connect all rooms in the dungeon. This ensures all rooms are reachable while
 * minimizing the total corridor length and creating a tree-like structure without cycles.
 * 
 * @extends CorridorGenerator
 */
class Primm2D : public CorridorGenerator {
	GDCLASS(Primm2D, CorridorGenerator)

private:
	/// Reference to the parent dungeon generator node.
	Node* dungeon_generator;

	/**
	 * @brief Calculates the step direction from point a to point b.
	 * 
	 * Determines the unit direction vector needed to move from one point toward another,
	 * moving one grid cell at a time either horizontally or vertically.
	 * 
	 * @param a Starting point.
	 * @param b Target point.
	 * @return Vector2i unit direction vector (one of: up, down, left, right).
	 */
	Vector2i calculate_step(Vector2i a, Vector2i b);
	
	/**
	 * @brief Opens corridor connections between two adjacent points.
	 * 
	 * Creates the physical corridor connection between two neighboring grid positions
	 * by removing doors/walls and placing corridor tiles.
	 * 
	 * @param a First point.
	 * @param b Second point (must be adjacent to a).
	 */
	void open_between(Vector2i a, Vector2i b);

protected:
	/**
	 * @brief Binds methods to be accessible from GDScript.
	 */
	static void _bind_methods();

public:
	/**
	 * @brief Called when the node is ready in the scene tree.
	 */
	void _ready() override;
	
	/**
	 * @brief Generates corridors using Prim's algorithm.
	 * 
	 * Overrides the base method to implement Prim's minimum spanning tree algorithm,
	 * which connects all room points with corridors while minimizing total path length.
	 * 
	 * @param points Array of Vector2i coordinates representing room positions to be connected.
	 */
	void generate_corridor(TypedArray<Vector2i> points) override;
	
	/**
	 * @brief Opens a corridor path between two points in the dungeon.
	 * 
	 * Creates a Manhattan-distance path (horizontal then vertical, or vice versa)
	 * from the initial point to the end point, placing corridor tiles along the way.
	 * 
	 * @param initial Starting position for the corridor path.
	 * @param end Ending position for the corridor path.
	 */
	void open_path_in_dungeon(Vector2i initial, Vector2i end);
};

} // namespace godot