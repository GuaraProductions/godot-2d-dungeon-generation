#pragma once

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/variant/typed_array.hpp>
#include <godot_cpp/variant/vector2i.hpp>
#include <godot_cpp/variant/variant.hpp>

namespace godot {

class CorridorGenerator : public Node {
	GDCLASS(CorridorGenerator, Node)

private:

	Node* dungeon_generator;

protected:
	static void _bind_methods();

public:

	CorridorGenerator();
	~CorridorGenerator();

	void _ready() override;
	virtual void generate_corridor(TypedArray<Vector2i> points);
};

} // namespace godot