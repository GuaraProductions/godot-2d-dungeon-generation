#include "gdexample.h"
#include <godot_cpp/classes/engine.hpp>

using namespace godot;

void GDExample::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_amplitude"), &GDExample::get_amplitude);
	ClassDB::bind_method(D_METHOD("teste_um"), &GDExample::teste_um);
	ClassDB::bind_method(D_METHOD("somar_dois_numeros", "numero1", "numero2"), &GDExample::somar_dois_numeros);
	ClassDB::bind_method(D_METHOD("set_amplitude", "p_amplitude"), &GDExample::set_amplitude);

	ADD_SIGNAL(MethodInfo("position_changed", PropertyInfo(Variant::OBJECT, "node"), 
	           PropertyInfo(Variant::VECTOR2, "new_pos")));

	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "amplitude", PROPERTY_HINT_RANGE, "0,100,0.1"), 
	             "set_amplitude", "get_amplitude");
}

GDExample::GDExample() {
	time_passed = 0.0;
	amplitude = 10.0;
}

GDExample::~GDExample() {
}

void GDExample::_process(double delta) {

	if (godot::Engine::get_singleton()->is_editor_hint()) return;

	time_passed += delta;

	Vector2 new_position = Vector2(
		amplitude + (amplitude * sin(time_passed * 2.0)),
		amplitude + (amplitude * cos(time_passed * 1.5))
	);

	set_position(new_position);

	time_emit += delta;
	if (time_emit > 1.0) {
		emit_signal("position_changed", this, new_position);

		time_emit = 0.0;
	}
}

void GDExample::set_amplitude(const double p_amplitude) {
	amplitude = p_amplitude;
}

double GDExample::get_amplitude() {
	return amplitude;
}

int GDExample::somar_dois_numeros(int a, float b) {
	return a + b;
}

void GDExample::teste_um() {
	godot::UtilityFunctions::print("Ola ALLANOSAN");
	godot::Sprite2D* variavel = get_node<godot::Sprite2D>("Sprite2D");
	
	godot::UtilityFunctions::print("Sprite2D: ", variavel);

	Array nodes = get_tree()->get_nodes_in_group("MyGroup");

	godot::UtilityFunctions::print("Meu array: ", nodes);
}
