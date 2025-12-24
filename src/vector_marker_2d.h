#include <godot_cpp/classes/marker2d.hpp>
#include <godot_cpp/variant/vector2i.hpp>
#include <godot_cpp/variant/string_name.hpp>
#include <godot_cpp/variant/string.hpp>

#pragma once

namespace godot {

class VectorMarker2DCpp : public Marker2D {
	GDCLASS(VectorMarker2DCpp, Marker2D)

private:

    Vector2i direction;

protected:
	static void _bind_methods();

public:

    VectorMarker2DCpp();
    ~VectorMarker2DCpp();

	void _ready() override;
    godot::String _to_string();

    Vector2i get_direction() const;
    void set_direction(Vector2i p_direction);

    static godot::StringName get_group_name() {
        return godot::StringName("VectorMarker2DCpp");
    }
};

} // namespace godot