extends GeradorCorredor2D

## Gerar caminhos entre as salas usando o Algoritmo de Primm
func criar_caminho(pontos: Array[Vector2i]) -> void:
	
	var visitado : Array[Vector2i] = []
	var restantes : Array[Vector2i] = pontos.duplicate()

	var vertice_atual : Vector2i = restantes.pop_front()
	visitado.append(vertice_atual)
	
	# Enquanto ainda tiver vertices (salas) para visitar
	while restantes.size() > 0:
	
		var distancia_minima = INF
		var arestas_distancia_minima = []
		
		for vertice_visitada in visitado:
			for vertices_restante in restantes:
				
				# Encontrar par de vertices com a menor distancia entre eles
				var distancia = vertice_visitada.distance_to(vertices_restante)
				if distancia < distancia_minima:
					distancia_minima = distancia
					arestas_distancia_minima = [vertice_visitada, vertices_restante]
					
		# Ao encontrar o par com menor distancia
		if not arestas_distancia_minima.is_empty():
			var ponto_inicial : Vector2i = arestas_distancia_minima[0]
			var ponto_final : Vector2i = arestas_distancia_minima[1]
			
			# Criar caminho entre os dois pontos
			_criar_caminho(ponto_inicial, ponto_final)
			
			# Adicionar ponto a lista de já visitados
			visitado.append(ponto_final)
			restantes.erase(ponto_final)

## Calcular a direcao de uma sala pra outra, para uso
## na abertura dos caminhos
func _calcular_step(a: Vector2i, b: Vector2i) -> Vector2i:
	return b - a
		
## Abrir porta entre duas salas
func _abrir_entre(a_pos: Vector2i, b_pos: Vector2i) -> void:
	var dir := _calcular_step(a_pos, b_pos)
	var a = gerador_dungeon.get_dungeon_em(a_pos)
	var b = gerador_dungeon.get_dungeon_em(b_pos)
	if a:
		a.remove_tile_from_door(dir)
	if b:
		b.remove_tile_from_door(-dir)

## Criar caminho e abrir as portas entre as salas
## e os corredores entre o ponto p1 e p2
func _criar_caminho(p1: Vector2i, p2: Vector2i) -> void:
	var x := p1.x
	var y := p1.y
	var x2 := p2.x
	var y2 := p2.y
	
	var caminho: Array[Vector2i] = []
	
	# Criar corredores e configurar todos os pontos do caminho
	while x != x2 or y != y2:
		if abs(x - x2) > abs(y - y2):
			x += 1 if x < x2 else -1
		elif y != y2:
			y += 1 if y < y2 else -1
		else:
			x += 1 if x < x2 else -1
			
		# Apenas criar novos corredores se a celula atual
		# for vazia
		var vetor : Vector2i = Vector2i(x,y)
		
		if gerador_dungeon.eh_espaco_vazio(vetor):
			gerador_dungeon.criar_corredor(vetor)
			
		# Independente do ponto que foi encontrado, colocar ele na lista
		# de pontos a ser aberto em um caminho
		caminho.append(vetor)

	# Abertura de todas as portas
	var anterior := p1
	for atual in caminho:
		_abrir_entre(anterior, atual)
		anterior = atual

	# Garantir que o ponto final e corredor final estejam abertos
	_abrir_entre(anterior, p2)
