#include "room_generator.h"
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/variant/typed_array.hpp>
#include <godot_cpp/variant/vector2i.hpp>
#include <godot_cpp/variant/variant.hpp>

#pragma once

namespace godot {

class PoissonDiskSampling : public RoomGenerator {
	GDCLASS(PoissonDiskSampling, RoomGenerator)

private:

	int radius = 3;
	int num_checks_before_rejection = 20;
	Node* dungeon_generator;

	bool is_valid(Vector2i candidate_point, Vector2i dimension);

protected:
	static void _bind_methods();

public:

	void _ready() override;
	virtual TypedArray<Vector2i> generate_rooms(Vector2i dimension);
	void set_radius(int p_radius);
	int get_radius() const;
	void set_num_checks_before_rejection(int p_num_checks_before_rejection);
	int get_num_checks_before_rejection() const;

};

} // namespace godot