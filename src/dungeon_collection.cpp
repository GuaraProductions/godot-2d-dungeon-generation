#include"dungeon_collection.h"

#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/object.hpp>

using namespace godot;

void DungeonCollectionCpp::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_random_dungeon"), &DungeonCollectionCpp::get_random_dungeon);
    ClassDB::bind_method(D_METHOD("get_scenes"), &DungeonCollectionCpp::get_scenes);
    ClassDB::bind_method(D_METHOD("set_scenes", "p_scenes"), &DungeonCollectionCpp::set_scenes);
	ADD_PROPERTY(
        PropertyInfo(
            Variant::ARRAY, 
            "scenes", 
            PROPERTY_HINT_TYPE_STRING, 
            String::num(Variant::OBJECT) + "/" + String::num(PROPERTY_HINT_RESOURCE_TYPE) + ":PackedScene"
    ),"set_scenes", "get_scenes");
}

DungeonCollectionCpp::DungeonCollectionCpp(TypedArray<PackedScene> p_scenes) {
    scenes = p_scenes;
}

DungeonCollectionCpp::~DungeonCollectionCpp() {
	
}

Dungeon2DCpp* DungeonCollectionCpp::get_random_dungeon() {
    PackedScene* scene = Object::cast_to<PackedScene>(scenes.pick_random());

    if (scene == nullptr)
        return nullptr;

    return Object::cast_to<Dungeon2DCpp>(scene->instantiate());
}   

TypedArray<PackedScene> DungeonCollectionCpp::get_scenes() const{
    return scenes.duplicate();
}

void DungeonCollectionCpp::set_scenes(TypedArray<PackedScene> p_scenes) {
    scenes = p_scenes;
}