/**
 * @file dungeon_collection.h
 * @brief Resource class for managing collections of dungeon room scenes.
 */

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/variant/typed_array.hpp>
#include <godot_cpp/variant/vector2i.hpp>
#include <godot_cpp/variant/variant.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/resource.hpp>

#include "dungeon_2d.h"

#pragma once

namespace godot {

/**
 * @class DungeonCollectionCpp
 * @brief Resource that holds a collection of dungeon room PackedScenes.
 * 
 * DungeonCollectionCpp is a Resource-based class that manages a collection of
 * PackedScene objects representing different dungeon rooms or corridors. It provides
 * functionality to randomly select and instantiate rooms from the collection.
 * 
 * @extends Resource
 */
class DungeonCollectionCpp : public Resource {
	GDCLASS(DungeonCollectionCpp, Resource)

private:
	/// Array of PackedScene objects representing dungeon rooms or corridors.
	TypedArray<PackedScene> scenes;

protected:
	/**
	 * @brief Binds methods and properties to be accessible from GDScript.
	 */
	static void _bind_methods();

public:
	/**
	 * @brief Constructor with optional scenes parameter.
	 * @param p_scenes Initial array of PackedScene objects (default: empty array).
	 */
	DungeonCollectionCpp(TypedArray<PackedScene> p_scenes = {});
	
	/**
	 * @brief Destructor.
	 */
	~DungeonCollectionCpp();

	/**
	 * @brief Gets a random dungeon room from the collection.
	 * 
	 * Randomly selects a PackedScene from the collection and instantiates it
	 * as a Dungeon2DCpp node.
	 * 
	 * @return Pointer to the instantiated Dungeon2DCpp node, or nullptr if collection is empty.
	 */
	Dungeon2DCpp* get_random_dungeon();
	
	/**
	 * @brief Gets a copy of the scenes array.
	 * @return TypedArray containing copies of all PackedScene objects in the collection.
	 */
	TypedArray<PackedScene> get_scenes() const;
	
	/**
	 * @brief Sets the scenes array.
	 * @param p_scenes New array of PackedScene objects to store in the collection.
	 */
	void set_scenes(TypedArray<PackedScene> p_scenes);
};

} // namespace godot