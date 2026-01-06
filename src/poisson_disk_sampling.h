/**
 * @file poisson_disk_sampling.h
 * @brief Poisson disk sampling algorithm for room generation.
 */

#include "room_generator.h"
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/variant/typed_array.hpp>
#include <godot_cpp/variant/vector2i.hpp>
#include <godot_cpp/variant/variant.hpp>

#pragma once

namespace godot {

/**
 * @class PoissonDiskSampling
 * @brief Implements Poisson disk sampling for generating evenly-distributed room positions.
 * 
 * PoissonDiskSampling generates room positions using the Poisson disk sampling algorithm,
 * which ensures a minimum distance between rooms while maintaining good spatial distribution.
 * This creates more natural-looking dungeon layouts with rooms that are neither too clustered
 * nor too evenly spaced.
 * 
 * @extends RoomGenerator
 */
class PoissonDiskSampling : public RoomGenerator {
	GDCLASS(PoissonDiskSampling, RoomGenerator)

private:
	/// Minimum distance between room centers in grid cells.
	int radius = 3;
	
	/// Number of attempts to place a new room before rejecting a candidate point.
	int num_checks_before_rejection = 20;
	
	/// Reference to the parent dungeon generator node.
	Node* dungeon_generator;

	/**
	 * @brief Checks if a candidate point is valid for room placement.
	 * 
	 * Validates that the candidate point maintains the minimum distance from existing rooms
	 * and falls within the dungeon boundaries.
	 * 
	 * @param candidate_point The position to validate.
	 * @param dimension The dimensions of the dungeon area.
	 * @return True if the point is valid for placing a room.
	 */
	bool is_valid(Vector2i candidate_point, Vector2i dimension);

protected:
	/**
	 * @brief Binds methods and properties to be accessible from GDScript.
	 */
	static void _bind_methods();

public:
	/**
	 * @brief Called when the node is ready in the scene tree.
	 */
	void _ready() override;
	
	/**
	 * @brief Generates room positions using Poisson disk sampling.
	 * 
	 * Implements the Poisson disk sampling algorithm to distribute rooms evenly
	 * across the dungeon space while maintaining a minimum distance between them.
	 * 
	 * @param dimension Vector2i specifying the width and height of the dungeon area.
	 * @return TypedArray of Vector2i coordinates representing room positions.
	 */
	virtual TypedArray<Vector2i> generate_rooms(Vector2i dimension);
	
	/**
	 * @brief Sets the minimum radius between rooms.
	 * @param p_radius Minimum distance in grid cells between room centers.
	 */
	void set_radius(int p_radius);
	
	/**
	 * @brief Gets the minimum radius between rooms.
	 * @return Current radius value.
	 */
	int get_radius() const;
	
	/**
	 * @brief Sets the number of candidate checks before rejection.
	 * @param p_num_checks_before_rejection Number of placement attempts per active point.
	 */
	void set_num_checks_before_rejection(int p_num_checks_before_rejection);
	
	/**
	 * @brief Gets the number of candidate checks before rejection.
	 * @return Current number of checks.
	 */
	int get_num_checks_before_rejection() const;

};

} // namespace godot