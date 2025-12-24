#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/variant/typed_array.hpp>
#include <godot_cpp/variant/vector2i.hpp>
#include <godot_cpp/variant/variant.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/resource.hpp>

#include "dungeon_2d.h"

#pragma once

namespace godot {

class DungeonCollectionCpp : public Resource {
	GDCLASS(DungeonCollectionCpp, Resource)

private:

	TypedArray<PackedScene> scenes;

protected:
	static void _bind_methods();

public:

	DungeonCollectionCpp(TypedArray<PackedScene> p_scenes = {});
	~DungeonCollectionCpp();

	Dungeon2DCpp* get_random_dungeon();
	TypedArray<PackedScene> get_scenes() const;
	void set_scenes(TypedArray<PackedScene> p_scenes);
};

} // namespace godot