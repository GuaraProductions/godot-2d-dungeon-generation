extends Node
class_name GeradorSala2D

var gerador_dungeon : GeradorDungeon2D

func _ready() -> void:
	
	var pai : Node = get_parent()
	if pai is not GeradorDungeon2D:
		printerr("Erro! Node mal configurado")
		return
		
	gerador_dungeon = pai

func gerar_salas(_tamanho_grid: Vector2i) -> Array[Vector2i]:
	return []
	
