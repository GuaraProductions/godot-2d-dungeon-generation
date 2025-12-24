#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/variant/vector2i.hpp>
#include <godot_cpp/variant/dictionary.hpp>
#include <godot_cpp/variant/variant.hpp>

#pragma once

namespace godot {

class Dungeon2DCpp : public Node2D {
	GDCLASS(Dungeon2DCpp, Node2D)

private:

    Vector2 room_size;
    Dictionary exits_and_vectors;

protected:
	static void _bind_methods();

public:

    Dungeon2DCpp();
    ~Dungeon2DCpp();

	void _ready() override;
	void remove_tile_from_door(Vector2i direction);

    Vector2 get_room_size() const;
    void set_room_size();
};

} // namespace godot