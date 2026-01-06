extends Marker2D
class_name VectorMarker2D

const GRUPO_NOME : String = "VectorMarker2D"

@export var vetor_direcao : Vector2i

func _ready() -> void:
	add_to_group(GRUPO_NOME)
