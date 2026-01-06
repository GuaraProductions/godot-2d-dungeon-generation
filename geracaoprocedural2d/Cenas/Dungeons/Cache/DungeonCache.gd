extends Resource
class_name DungeonCache

@export var dungeon : Array[Vector2i]

func _init(p_dungeon: Array[Vector2i] = []) -> void:
	dungeon = p_dungeon
