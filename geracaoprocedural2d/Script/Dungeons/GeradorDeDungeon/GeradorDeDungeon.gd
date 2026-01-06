extends Node2D
class_name GeradorDungeon2D

enum TipoCelula {
	VAZIO,
	SALA,
	CORREDOR
}

## Quantidade de salas presentes em uma cena
@export var executar_no_ready : bool = false
@export var tamanho_dungeon : Vector2i
@export var gerador_de_salas : GeradorSala2D
@export var gerador_de_corredores : GeradorCorredor2D
#@export var tipo_geracao_salas : TipoGeracaoDeSalas
## Cenas que serão usadas como salas (Precisam ser do tipo DungeonRoom)
@export_category("Cenas")
@export var dungeons : DungeonCollection2D
## Cenas que serão usadas como corredores (Precisam ser do tipo DungeonRoom)
@export var corredores : DungeonCollection2D
## Indica o tamanho de cada sala (dungeon e corredor)
@export var tamanho_sala : Vector2i
## Matrix 2D representando a dungeon
@export_category("Cache")
@export var usar_cache : bool
@export var dungeon_cache : DungeonCache
@export_category("Debug")
@export var executar_no_editor : bool = false
@export var imprimir_dungeon_no_terminal : bool = false

## Estrutura auxiliar para guardar coordenadas de determinadas salas
var dungeon_grid : Array = []
	
func _ready() -> void:
	if executar_no_ready:
		gerar_dungeon()
	
func gerar_dungeon() -> void:
	
	_iniciar_dungeon_grid()
	
	# Geração dos pontos
	var pontos: Array[Vector2i] = []
	if usar_cache and dungeon_cache:
		pontos = dungeon_cache.dungeon
		_criar_todas_as_salas(pontos)
	else:
		pontos = gerador_de_salas.gerar_salas(tamanho_dungeon)
	
	# Geração dos caminhos
	gerador_de_corredores.criar_caminho(pontos)
	
	if imprimir_dungeon_no_terminal:
		_imprimir_dungeon_texto()


## Iniciar estrutura auxiliar da geração de dungeons
func _iniciar_dungeon_grid() -> void:
	
	dungeon_grid.clear()
	
	for i in range(tamanho_dungeon.y):
		var coluna : Array = []
		for j in range(tamanho_dungeon.x):
			coluna.append(TipoCelula.VAZIO)
		dungeon_grid.append(coluna)
			
			
## Instancia todas as salas com base na matrix de [pontos]
## Apenas utilizada quando a sala é carregada usando a cache
func _criar_todas_as_salas(pontos: Array) -> void:
	
	for ponto in pontos:
		dungeon_grid[ponto.x][ponto.y] = TipoCelula.SALA
		criar_sala(ponto)
			
## Spawnar sala em uma posicao do mapa. Todas as salas são configuradas
## De acordo com a coordenada que elas tem dentro do Grid
func criar_sala(posicao: Vector2, direcao: Vector2i = Vector2i.ZERO) -> Dungeon2D:
	
	dungeon_grid[posicao.x][posicao.y] = TipoCelula.SALA
	
	var dungeon_sala_instancia : Dungeon2D = dungeons.get_dungeon_aleatoria()
	dungeon_sala_instancia.name = "%d-%d" % [posicao.x, posicao.y]
	add_child(dungeon_sala_instancia)
	
	if direcao != Vector2i.ZERO:
		dungeon_sala_instancia.remover_tile_de_porta(direcao)
	
	dungeon_sala_instancia.global_position.x = \
	 posicao.x * tamanho_sala.x
	dungeon_sala_instancia.global_position.y = \
	 posicao.y * tamanho_sala.y
	
	return dungeon_sala_instancia
	
## Spawnar corredor em uma posicao do mapa. Todas as salas são configuradas
## De acordo com a coordenada que elas tem dentro do Grid
func criar_corredor(posicao: Vector2) -> Dungeon2D:
	
	dungeon_grid[posicao.x][posicao.y] = TipoCelula.CORREDOR
	
	var corredor_sala_instancia : Dungeon2D = corredores.get_dungeon_aleatoria()
	
	corredor_sala_instancia.name = "%d-%d" % [posicao.x, posicao.y]
	add_child(corredor_sala_instancia)
	
	corredor_sala_instancia.global_position.x = \
	 posicao.x * tamanho_sala.x
	corredor_sala_instancia.global_position.y = \
	 posicao.y * tamanho_sala.y
	
	return corredor_sala_instancia
	
## Acessar dungeon em especifico de acordo com a coordenada
func get_dungeon_em(p: Vector2i) -> Dungeon2D:
	var nome : String =  "%d-%d" % [p.x, p.y]
	return get_node_or_null(nome)
		
func existe_sala_em(ponto: Vector2i) -> bool:
	return dungeon_grid[ponto.x][ponto.y] == TipoCelula.SALA
	
func eh_espaco_vazio(ponto: Vector2i) -> bool:
	return dungeon_grid[ponto.x][ponto.y] == TipoCelula.VAZIO
		
func _imprimir_dungeon_texto() -> void:
	var w := dungeon_grid.size()            
	var h = dungeon_grid[0].size() if (w > 0) else 0 

	var pad_x := str(max(0, w-1)).length()
	var pad_y := str(max(0, h-1)).length()

	var out := ""

	out += "y\\x   " 
	for x in range(w):
		out += "%0*d " % [pad_x, x]  
	out += "\n"

	for y in range(h):
		out += "%0*d [" % [pad_y, y]
		out += " ["
		for x in range(w):
			var valor = dungeon_grid[x][y]

			var start_tag := "[color=white]"
			match valor:
				0: start_tag = "[color=black]"
				1: start_tag = "[color=red]"
				2: start_tag = "[color=green]"

			# usa mesmo padding de X pras células
			out += "%s%0*s[/color] " % [start_tag, pad_x, str(valor)]
		out += "]\n"

	print_rich(out)
