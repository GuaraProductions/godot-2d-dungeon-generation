#include "corridor_generator.h"
#include <godot_cpp/variant/typed_array.hpp>
#include <godot_cpp/variant/vector2i.hpp>
#include <godot_cpp/variant/variant.hpp>

namespace godot {

class Primm2D : public CorridorGenerator {
	GDCLASS(Primm2D, CorridorGenerator)

private:

	Node* dungeon_generator;

protected:
	static void _bind_methods();

public:

	Primm2D();
	~Primm2D();

	void generate_corridor(TypedArray<Vector2i> points) override;
	void open_path_in_dungeon(Vector2i initial, Vector2i end);
};

} // namespace godot