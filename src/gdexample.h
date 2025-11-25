#pragma once

#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/scene_tree.hpp>

namespace godot {

class GDExample : public Sprite2D {
	GDCLASS(GDExample, Sprite2D)

private:

	double time_passed;
	double time_emit;
	double amplitude;

protected:
	static void _bind_methods();

public:
	GDExample();
	~GDExample();
	void set_amplitude(const double p_amplitude);
	double get_amplitude();
	void teste_um();
	int somar_dois_numeros(int a, float b);


	void _process(double delta) override;
};

} // namespace godot
