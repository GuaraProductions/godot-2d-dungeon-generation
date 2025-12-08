#include"primm2d.h"

#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/variant/typed_array.hpp>
#include <godot_cpp/variant/vector2i.hpp>
#include <godot_cpp/variant/variant.hpp>

#include <godot_cpp/core/math.hpp>
#include <vector>
#include <utility>
#include <optional>

using namespace godot;

void Primm2D::_bind_methods() {
    ClassDB::bind_method(D_METHOD("generate_corridor", "points"),&Primm2D::generate_corridor);
}

Primm2D::Primm2D() {

}

Primm2D::~Primm2D() {
	
}

void Primm2D::generate_corridor(TypedArray<Vector2i> points) {

    auto visitado = TypedArray<Vector2i>();
    auto restantes = points.duplicate();

    auto vertice_atual = restantes.pop_front();

    while (restantes.size() > 0) {
        
        double distancia_minima = INT_FAST32_MAX;
        std::optional<std::pair<Vector2i, Vector2i>> arestas_distancia_minima;

        for (int i = 0; i < visitado.size(); i++) {
            Vector2i vertice_visitada = visitado[i];
            for (int i = 0; i < restantes.size(); i++) {
                Vector2i vertice_atual = restantes[i];
                
                double distancia = vertice_visitada.distance_to(vertice_atual);
                if (distancia < distancia_minima) {
                    arestas_distancia_minima = std::make_pair(vertice_visitada, vertice_atual);
                }
            }     
        }

        if (!arestas_distancia_minima) {
            auto ponto_inicial = arestas_distancia_minima->first;
            auto ponto_final = arestas_distancia_minima->second;

            open_path_in_dungeon(ponto_inicial, ponto_final);

            visitado.append(ponto_final);
            restantes.erase(ponto_final);
        }
    }    

}

void Primm2D::open_path_in_dungeon(Vector2i initial, Vector2i end) {

}