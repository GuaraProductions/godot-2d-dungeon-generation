/**
 * @file vector_marker_2d.h
 * @brief Marker node for indicating directional exits in dungeon rooms.
 */

#include <godot_cpp/classes/marker2d.hpp>
#include <godot_cpp/variant/vector2i.hpp>
#include <godot_cpp/variant/string_name.hpp>
#include <godot_cpp/variant/string.hpp>

#pragma once

namespace godot {

/**
 * @class VectorMarker2DCpp
 * @brief A 2D marker that indicates a directional exit or door in a dungeon room.
 * 
 * VectorMarker2DCpp extends Marker2D to represent directional markers for room exits.
 * It stores a direction vector and automatically adds itself to a group for easy identification.
 * These markers are used by dungeon rooms to identify where doors and connections should be placed.
 * 
 * @extends Marker2D
 */
class VectorMarker2DCpp : public Marker2D {
	GDCLASS(VectorMarker2DCpp, Marker2D)

private:
	/// Direction vector indicating the exit orientation (e.g., Vector2i(0,-1) for north).
    Vector2i direction;

protected:
	/**
	 * @brief Binds methods and properties to be accessible from GDScript.
	 */
	static void _bind_methods();

public:
	/**
	 * @brief Default constructor.
	 */
    VectorMarker2DCpp();
	
	/**
	 * @brief Destructor.
	 */
    ~VectorMarker2DCpp();

	/**
	 * @brief Called when the node is ready in the scene tree.
	 * 
	 * Initializes the marker and adds it to the VectorMarker2DCpp group.
	 */
	void _ready() override;
	
	/**
	 * @brief Returns a string representation of the marker.
	 * @return String describing the marker and its direction.
	 */
    godot::String _to_string();

	/**
	 * @brief Gets the direction vector of the marker.
	 * @return Vector2i representing the exit direction.
	 */
    Vector2i get_direction() const;
	
	/**
	 * @brief Sets the direction vector of the marker.
	 * @param p_direction New direction vector for the exit.
	 */
    void set_direction(Vector2i p_direction);

	/**
	 * @brief Gets the group name used by all VectorMarker2DCpp instances.
	 * 
	 * All VectorMarker2DCpp nodes are automatically added to this group,
	 * allowing the dungeon system to find and manage them easily.
	 * 
	 * @return StringName of the group ("VectorMarker2DCpp").
	 */
    static godot::StringName get_group_name() {
        return godot::StringName("VectorMarker2DCpp");
    }
};

} // namespace godot