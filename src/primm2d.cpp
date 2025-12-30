#include"primm2d.h"

#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/variant/typed_array.hpp>
#include <godot_cpp/variant/vector2i.hpp>
#include <godot_cpp/variant/variant.hpp>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/core/math.hpp>

#include <vector>
#include <utility>
#include <optional>
#include <iostream>

using namespace godot;

void Primm2D::_bind_methods() {
    ClassDB::bind_method(D_METHOD("generate_corridor", "points"),&Primm2D::generate_corridor);
}

void Primm2D::_ready() {

	if (godot::Engine::get_singleton()->is_editor_hint()) return;
    
    Node* node_pai = get_parent();

    dungeon_generator = node_pai;
}

void Primm2D::generate_corridor(TypedArray<Vector2i> points) {

    auto visitado = TypedArray<Vector2i>();
    auto restantes = points.duplicate();

    auto vertice_atual = restantes.pop_front();
    visitado.append(vertice_atual);

    while (restantes.size() > 0) {

        float distancia_minima = 99999;
        std::optional<std::pair<Vector2i, Vector2i>> arestas_distancia_minima;

        for (int i = 0; i < visitado.size(); i++) {
            Vector2i vertice_visitada = visitado[i];
            for (int j = 0; j < restantes.size(); j++) {
                Vector2i vertice_atual = restantes[j];
                
                float distancia = vertice_visitada.distance_to(vertice_atual);
                if (distancia < distancia_minima) {
                    
                    distancia_minima = distancia;
                    arestas_distancia_minima = std::make_pair(vertice_visitada, vertice_atual);
                }
            }     
        }

        if (arestas_distancia_minima.has_value()) {
            auto ponto_inicial = arestas_distancia_minima->first;
            auto ponto_final = arestas_distancia_minima->second;

            open_path_in_dungeon(ponto_inicial, ponto_final);

            visitado.append(ponto_final);
            restantes.erase(ponto_final);
        }
    }    

}

void Primm2D::open_path_in_dungeon(Vector2i initial, Vector2i end) {

    int x = initial.x;
    int y = initial.y;
    int x2 = end.x;
    int y2 = end.y;

    std::vector<Vector2i> path = {};

    while (x != x2 || y != y2) {

        if (godot::Math::abs(x - x2) > godot::Math::abs(y - y2))
            x += (x < x2 ? 1 : -1);
        else if (y != y2)
            y += (y < y2 ? 1 : -1);
        else
            x += (x < x2 ? 1 : -1);

        Vector2i posicao_atual = Vector2i(x, y);
        if ((bool)dungeon_generator->call("is_empty", posicao_atual)) 
            dungeon_generator->call("create_corridor", posicao_atual);
        
        path.push_back(posicao_atual);
    }

    auto anterior = initial;
    for (const auto& atual : path) {
        open_between(anterior, atual);
        anterior = atual;
    }

    open_between(anterior, end);
}

Vector2i Primm2D::calculate_step(Vector2i a, Vector2i b) {
    return b - a;
}

void Primm2D::open_between(Vector2i a, Vector2i b) {

    Vector2i direction = calculate_step(a, b);

    Node* dungeon_a = 
        Object::cast_to<Node>(dungeon_generator->call("get_dungeon_in", a)); 
    Node* dungeon_b = 
        Object::cast_to<Node>(dungeon_generator->call("get_dungeon_in", b)); 

    if (dungeon_a != NULL)
        dungeon_a->call("remove_tile_from_door", direction);
    if (dungeon_b != NULL)
        dungeon_b->call("remove_tile_from_door", -direction);
}