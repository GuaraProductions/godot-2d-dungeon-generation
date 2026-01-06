extends Resource
class_name DungeonCollection2D

@export var cenas : Array[PackedScene]

func _init(p_cenas: Array[PackedScene] = []) -> void:
	cenas = p_cenas
	
func get_dungeon_aleatoria() -> Dungeon2D:
	var cena : PackedScene = cenas.pick_random()
	
	if cena == null:
		return null
	
	return cena.instantiate()
