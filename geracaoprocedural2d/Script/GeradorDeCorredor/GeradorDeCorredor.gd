extends Node
class_name GeradorCorredor2D

var gerador_dungeon : GeradorDungeon2D

func _ready() -> void:
	
	var pai : Node = get_parent()
	if pai is not GeradorDungeon2D:
		printerr("Erro! Node mal configurado")
		return
		
	gerador_dungeon = pai

func criar_caminho(_pontos: Array[Vector2i]) -> void:
	pass
