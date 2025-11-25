extends Node

@onready var dungeon_generator_2d: DungeonGenerator2D = $DungeonGenerator2D

func _ready() -> void:
	print(dungeon_generator_2d.dungeon_size)
