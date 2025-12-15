#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/variant/typed_array.hpp>
#include <godot_cpp/variant/vector2i.hpp>
#include <godot_cpp/variant/variant.hpp>

#pragma once

namespace godot {

class RoomGenerator : public Node {
	GDCLASS(RoomGenerator, Node)

private:

	Node* dungeon_generator;

protected:
	static void _bind_methods();

public:

	RoomGenerator();
	~RoomGenerator();

	void _ready() override;
	virtual TypedArray<Vector2i> generate_rooms(Vector2i dimension);
};

} // namespace godot