extends CharacterBody2D

@export var fator_zoom : float = 1.1
@export var zoom_limite_inferior : float = 0.1
@export var zoom_limite_superior : float = 5

@export var SPEED = 300.0
@onready var camera = $Camera2D

func _physics_process(_delta: float) -> void:

	# Get the input direction and handle the movement/deceleration.
	# As good practice, you should replace UI actions with custom gameplay actions.
	var direction := Input.get_vector("ui_left", "ui_right", "ui_up", "ui_down")
	if direction:
		velocity.x = direction.x * SPEED
		velocity.y = direction.y * SPEED
	else:
		velocity.x = move_toward(velocity.x, 0, SPEED)
		velocity.y = move_toward(velocity.y, 0, SPEED)

	move_and_slide()

func _unhandled_input(event: InputEvent) -> void:
	
	if event is InputEventMouseButton:
		if event.button_index == MOUSE_BUTTON_WHEEL_UP:
			camera.zoom.x = clamp(camera.zoom.x * fator_zoom, zoom_limite_inferior, zoom_limite_superior)
			camera.zoom.y = clamp(camera.zoom.y * fator_zoom, zoom_limite_inferior, zoom_limite_superior)
		elif event.button_index == MOUSE_BUTTON_WHEEL_DOWN:
			camera.zoom.x = clamp(camera.zoom.x / fator_zoom, zoom_limite_inferior, zoom_limite_superior)
			camera.zoom.y = clamp(camera.zoom.y / fator_zoom, zoom_limite_inferior, zoom_limite_superior)
		
