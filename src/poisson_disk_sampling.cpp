#include"poisson_disk_sampling.h"

#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/variant/typed_array.hpp>
#include <godot_cpp/variant/vector2i.hpp>
#include <godot_cpp/variant/variant.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>
#include <godot_cpp/core/math.hpp>
#include<random>

const float PI = 3.14;

using namespace godot;

void PoissonDiskSampling::_bind_methods() {
    ClassDB::bind_method(D_METHOD("generate_rooms", "dimension"),&PoissonDiskSampling::generate_rooms);

	ClassDB::bind_method(
        D_METHOD("get_radius"), 
        &PoissonDiskSampling::get_radius);
	ClassDB::bind_method(
        D_METHOD("set_radius", "p_radius"), 
        &PoissonDiskSampling::set_radius);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "radius", PROPERTY_HINT_RANGE, "0,10,1"), 
				 "set_radius", "get_radius");

	ClassDB::bind_method(
        D_METHOD("get_num_checks_before_rejection"), 
        &PoissonDiskSampling::get_num_checks_before_rejection);

	ClassDB::bind_method(
        D_METHOD("set_num_checks_before_rejection", "p_num_checks_before_rejection"), 
        &PoissonDiskSampling::set_num_checks_before_rejection);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "num_checks_before_rejection", PROPERTY_HINT_RANGE, "20,40,1"), 
				 "set_num_checks_before_rejection", "get_num_checks_before_rejection");
}

void PoissonDiskSampling::_ready() {

	if (godot::Engine::get_singleton()->is_editor_hint()) return;
    
    Node* node_pai = get_parent();

    dungeon_generator = node_pai;
}

int PoissonDiskSampling::get_radius() const {
    return radius;
}

void PoissonDiskSampling::set_radius(int p_radius) {
    radius = p_radius;
}

int PoissonDiskSampling::get_num_checks_before_rejection() const {
    return num_checks_before_rejection;
}

void PoissonDiskSampling::set_num_checks_before_rejection(int p_num_checks_before_rejection) {
    num_checks_before_rejection = p_num_checks_before_rejection;
}

TypedArray<Vector2i> PoissonDiskSampling::generate_rooms(Vector2i dimension) {
    
    Ref<RandomNumberGenerator> rng;
    rng.instantiate();

    auto points = TypedArray<Vector2i>();

    auto active_points = TypedArray<Vector2i>();

    Vector2i middle_point = Vector2i(dimension.x/2, dimension.y/2);
    active_points.append(middle_point);
    godot::UtilityFunctions::print("dungeon generator == null? ", dungeon_generator == NULL);
    dungeon_generator->call("criar_sala", middle_point);

    while (!active_points.is_empty()) {
        //godot::UtilityFunctions::print("while (!active_points.is_empty()) ");
        Vector2i current_point = active_points.pick_random();
        bool candidate_point_accepted = false;

        for (int i = num_checks_before_rejection; i >= 0; i--) {

            //godot::UtilityFunctions::print("for (int i = num_checks_before_rejection; i >= 0; i--)");
            float angle = rng->randf() * PI * 2;
            auto direction = Vector2(sin(angle), cos(angle));

            auto candidate_position =
             Vector2i(Vector2(current_point) + direction * rng->randi_range(radius, radius*2));

            if (is_valid(candidate_position, dimension)) {

                points.append(candidate_position);
                active_points.append(candidate_position);

                dungeon_generator->call("criar_sala", candidate_position);

                candidate_point_accepted = true;

                break;
            }
        }

        if (!candidate_point_accepted) {
            active_points.erase(current_point);
        }
    }

    return points;
}

bool PoissonDiskSampling::is_valid(Vector2i candidate_point, Vector2i dimension) {

    bool is_valid = true;

    if (candidate_point.x < 0 || candidate_point.x >= dimension.x 
        || candidate_point.y < 0 || candidate_point.y >= dimension.y ) {

        return false;
    }

    int x_initial = godot::CLAMP(candidate_point.x - radius, 0, dimension.x);
    int x_final = godot::CLAMP(candidate_point.x + radius, 0, dimension.x);

    int y_initial = godot::CLAMP(candidate_point.y - radius, 0, dimension.y);
    int y_final = godot::CLAMP(candidate_point.y + radius, 0, dimension.y);

    for (int x = x_initial; x < x_final; x++) {
        for (int y = y_initial; y < y_final; y++) {
            
            auto test_point = Vector2i(x, y);

            if ((bool)dungeon_generator->call("existe_sala_em", test_point)) {
                
                float points_distance = candidate_point.distance_squared_to(test_point);

                is_valid = points_distance > radius * radius;
                if (!is_valid) 
                    break;
            }
        }

        if (!is_valid)
            break;
    }

    return is_valid;
}