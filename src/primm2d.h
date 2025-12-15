#include "corridor_generator.h"
#include <godot_cpp/variant/typed_array.hpp>
#include <godot_cpp/variant/vector2i.hpp>
#include <godot_cpp/variant/variant.hpp>

namespace godot {

class Primm2D : public CorridorGenerator {
	GDCLASS(Primm2D, CorridorGenerator)

private:

	Node* dungeon_generator;

	
	Vector2i calculate_step(Vector2i a, Vector2i b);
	void open_between(Vector2i a, Vector2i b);

protected:
	static void _bind_methods();

public:

	void _ready() override;
	void generate_corridor(TypedArray<Vector2i> points) override;
	void open_path_in_dungeon(Vector2i initial, Vector2i end);
};

} // namespace godot