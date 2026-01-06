extends GeradorSala2D

@export var raio: int = 2
@export var num_checagens_antes_de_rejeicao : int = 30

## Geração aleatória de pontos no mapa usando o Algoritmo do
## Fast Poisson disk sampling (https://www.cs.ubc.ca/~rbridson/docs/bridson-siggraph07-poissondisk.pdf)
func gerar_salas(tamanho_grid: Vector2i) -> Array[Vector2i]:
	# Pontos de fato gerados
	var pontos: Array[Vector2i] = [] 
	# Pontos que ainda precisam ser verificados
	var pontos_ativos: Array[Vector2i] = []
	
	# Comecar com um ponto aleatório no centro
	var ponto_do_meio = Vector2i(tamanho_grid.x/2, tamanho_grid.y/2)
	pontos_ativos.append(ponto_do_meio)
	
	# Colocar o ponto inicial como sala
	gerador_dungeon.criar_sala(ponto_do_meio)
	
	#_imprimir_dungeon_texto()
	
	# Enquanto não tiver como mais colocar pontos,
	# Tentar colocar eles na sala
	while not pontos_ativos.is_empty():
		
		# Escolha um ponto atual que ainda tem que ser explorado
		var ponto_atual : Vector2i = pontos_ativos.pick_random()
		var ponto_candidato_aceito : bool = false
		
		# Varias tentativas para encontrar um ponto aceitavel
		for i in range(num_checagens_antes_de_rejeicao):
			
			# Gerar um novo ponto aleatorio
			var angulo = randf() * PI * 2
			var direcao : Vector2 = Vector2(sin(angulo), cos(angulo))
			var posicao_candidato : Vector2i = \
			 Vector2i(Vector2(ponto_atual) + direcao * randf_range(raio, 2*raio))
		
			if _poisson_disk_sampling_eh_valido(posicao_candidato, tamanho_grid):
				pontos.append(posicao_candidato)
				pontos_ativos.append(posicao_candidato)
				
				gerador_dungeon.criar_sala(posicao_candidato)
				
				ponto_candidato_aceito = true
			
				break
				
		if not ponto_candidato_aceito:
			pontos_ativos.erase(ponto_atual)
	
	return pontos
	
## Valida um ponto candidato a ser inserido no mapa
func _poisson_disk_sampling_eh_valido(candidato: Vector2i, 
									tamanho_grid: Vector2i) -> bool:
	
	var eh_valido : bool = true
	
	# Verificar se o ponto está dentro do limiar do grid
	if candidato.x < 0 \
	 or candidato.x >= tamanho_grid.x \
	 or candidato.y < 0 \
	 or candidato.y >= tamanho_grid.y:
		return false
	
	var x_inicial : int = clamp(candidato.x - raio, 0, tamanho_grid.x)
	var x_final : int = clamp(candidato.x + raio, 0, tamanho_grid.x)
	var y_inicial : int = clamp(candidato.y - raio, 0, tamanho_grid.y)
	var y_final : int = clamp(candidato.y + raio, 0, tamanho_grid.y)
	
	# Percorrer dentro de um espaco ao redor do candidato com base no [raio]
	for x in range(x_inicial, x_final):
		for y in range(y_inicial, y_final):
			
			var ponto_teste : Vector2i = Vector2i(x,y)
			if gerador_dungeon.existe_sala_em(ponto_teste):
				# Calcular distancia de uma sala pra outra
				var distancia_pontos = candidato.distance_squared_to(ponto_teste)
				
				# Se a sala for muito proxima da outra
				eh_valido = distancia_pontos > raio * raio
				if not eh_valido:
					break
					
		if not eh_valido:
			break
	
	return eh_valido
