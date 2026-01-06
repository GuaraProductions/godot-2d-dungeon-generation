extends Node2D

@onready var dungeon_1: Dungeon2D = $Dungeon1

func _ready() -> void:
	
	dungeon_1.remover_tile_de_porta(Vector2i.UP)
	dungeon_1.remover_tile_de_porta(Vector2i.DOWN)
