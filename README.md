# Geração de Dungeons 2D no Godot com C++

<img width="438" height="318" alt="image" src="https://github.com/user-attachments/assets/0141c4c1-79ed-42cd-a1e3-eb9f70611d02" />

Uma extensão GDExtension para Godot Engine 4.5+ que fornece geração procedural de dungeons 2D utilizando algoritmos de geração de salas e corredores.

## 📋 Sobre o Projeto

Este projeto implementa um sistema completo de geração procedural de dungeons 2D em C++ através de GDExtension, proporcionando alto desempenho e flexibilidade para criar dungeons únicas e jogáveis.

### Características Principais

- 🎲 **Geração Procedural de Salas**: Algoritmo de Poisson Disk Sampling para distribuição natural de salas
- 🔗 **Conexão de Corredores**: Algoritmo de Prim (MST) para conectar todas as salas com corredores otimizados
- 🎨 **Sistema Modular**: Classes base extensíveis para criar seus próprios algoritmos de geração
- 📦 **Coleções de Salas**: Sistema de recursos para gerenciar múltiplas variações de salas e corredores

## 🎯 Classes Principais

### DungeonGenerator2D
Controlador principal que orquestra todo o processo de geração de dungeons.

**Propriedades:**
- `dungeon_size`: Tamanho da grade do dungeon
- `room_size`: Tamanho de cada sala
- `on_ready`: Gerar dungeon automaticamente ao iniciar
- `room_generator`: Gerador de posições de salas
- `corridor_generator`: Gerador de corredores
- `room_collection`: Coleção de cenas de salas
- `corridor_collection`: Coleção de cenas de corredores

### RoomGenerator (Base)
Classe base para implementar algoritmos de geração de salas.

**Implementações:**
- `PoissonDiskSampling`: Distribui salas uniformemente com distância mínima configurável

### CorridorGenerator (Base)
Classe base para implementar algoritmos de geração de corredores.

**Implementações:**
- `Primm2D`: Usa algoritmo de Prim para criar árvore geradora mínima conectando todas as salas

### Dungeon2DCpp
Representa uma sala ou corredor individual no dungeon.

### DungeonCollectionCpp
Recurso que armazena coleções de PackedScenes de salas/corredores.

### VectorMarker2DCpp
Marcadores direcionais para indicar portas e saídas em salas.

## 🛠️ Requisitos

- **Godot Engine**: 4.5 ou superior
- **Sistema Operacional**: Linux, Windows, macOS
- **Compilador**: GCC/Clang (Linux/macOS) ou MSVC (Windows)
- **Python**: 3.6+ (para SCons)
- **SCons**: Sistema de build

## 📥 Instalação

### 1. Clone o Repositório

```bash
git clone https://github.com/seu-usuario/godot-2d-dungeon-generation.git
cd godot-2d-dungeon-generation
```

### 2. Inicialize Submódulos

```bash
git submodule update --init --recursive
```

Isso baixará a biblioteca `godot-cpp` necessária.

## 🔨 Compilação

### Build para Editor (com documentação)

```bash
scons target=editor
```

Este comando compila a extensão para uso no Godot Editor e **embute toda a documentação XML** nos binários, permitindo que o editor mostre tooltips e ajuda contextual.

### Build para Debug (exportação de jogos)

```bash
scons target=template_debug
```

### Build para Release (exportação de jogos)

```bash
scons target=template_release
```

### Build para Plataformas Específicas

```bash
# Windows 64-bit
scons platform=windows target=editor

# macOS
scons platform=macos target=editor

# Linux ARM64
scons platform=linux arch=arm64 target=editor
```

## 📚 Documentação

### Visualizando a Documentação no Editor

Após compilar com `target=editor`, a documentação estará disponível no Godot Editor:

1. Abra o projeto no Godot Editor
2. Pressione **F1** ou clique em "Pesquisar Ajuda"
3. Procure por qualquer classe: `DungeonGenerator2D`, `PoissonDiskSampling`, etc.
4. Veja descrições completas, propriedades e métodos com exemplos

### Arquivos de Documentação

Os arquivos XML em `doc_classes/` contêm toda a documentação das classes. Estes arquivos são processados durante a compilação e embedidos no binário da extensão.

**Arquivos incluídos:**
- `DungeonGenerator2D.xml`
- `RoomGenerator.xml`
- `CorridorGenerator.xml`
- `PoissonDiskSampling.xml`
- `Primm2D.xml`
- `Dungeon2DCpp.xml`
- `DungeonCollectionCpp.xml`
- `VectorMarker2DCpp.xml`

## 🎮 Como Usar

### 1. Configuração Básica

Crie uma cena com a seguinte estrutura:

```
DungeonGenerator2D (DungeonGenerator2D)
├── RoomGenerator (PoissonDiskSampling)
└── CorridorGenerator (Primm2D)
```

### 2. Configure as Propriedades

No Inspetor do `DungeonGenerator2D`:

```gdscript
# Tamanho do dungeon
dungeon_size = Vector2i(20, 20)

# Tamanho de cada sala
room_size = Vector2i(32, 32)

# Gerar ao iniciar
on_ready = true

# Atribuir geradores
room_generator = $RoomGenerator
corridor_generator = $CorridorGenerator
```

### 3. Crie Coleções de Salas

Crie um recurso `DungeonCollectionCpp` e adicione suas cenas de salas:

```gdscript
# No Editor:
# 1. Crie Resource -> DungeonCollectionCpp
# 2. Adicione PackedScenes de salas no array "scenes"
# 3. Atribua ao room_collection do DungeonGenerator2D
```

### 4. Configurando Salas

Cada sala deve ser uma cena com:
- Um nó `Dungeon2DCpp` como raiz
- Nós `VectorMarker2DCpp` filhos indicando direções de portas:
  - `direction = Vector2i(0, -1)` para norte
  - `direction = Vector2i(0, 1)` para sul
  - `direction = Vector2i(-1, 0)` para oeste
  - `direction = Vector2i(1, 0)` para leste

## 🔄 Hot-Reload (Desenvolvimento)

O GDExtension suporta hot-reload durante o desenvolvimento, permitindo recompilar e recarregar sem fechar o editor:

1. O arquivo `godot2d-generation.gdextension` tem `reloadable=true`
2. Compile suas alterações: `scons target=editor`
3. Suas alterações serão aplicadas sem perder o estado do editor

## 📁 Estrutura do Projeto

```
godot-2d-dungeon-generation/
├── src/                          # Código fonte C++
│   ├── dungeon_generator_2d.h/cpp
│   ├── room_generator.h/cpp
│   ├── corridor_generator.h/cpp
│   ├── poisson_disk_sampling.h/cpp
│   ├── primm2d.h/cpp
│   ├── dungeon_2d.h/cpp
│   ├── dungeon_collection.h/cpp
│   ├── vector_marker_2d.h/cpp
│   ├── register_types.h/cpp
│   └── gen/                      # Arquivos gerados (não commitar)
│       └── doc_data.gen.cpp
├── doc_classes/                  # Documentação XML (commitar)
│   ├── DungeonGenerator2D.xml
│   ├── RoomGenerator.xml
│   └── ...
├── godot-cpp/                    # Submódulo godot-cpp
├── geracaoprocedural2d/          # Projeto Godot de exemplo
│   └── bin/                      # Binários compilados
│       ├── godot2d-generation.gdextension
│       └── linux/
│           └── libGodot2D-DungeonGenerationCpp.linux.editor.x86_64.so
├── SConstruct                    # Script de build
└── README.md
```

## 🔧 Desenvolvimento

### Adicionando Nova Classe

1. Crie os arquivos `.h` e `.cpp` em `src/`
2. Adicione comentários Doxygen no header:
```cpp
/**
 * @class MinhaClasse
 * @brief Descrição breve.
 * 
 * Descrição detalhada da classe.
 */
```

3. Crie arquivo XML em `doc_classes/MinhaClasse.xml`
4. Registre a classe em `register_types.cpp`
5. Recompile: `scons target=editor`

### Atualizando Documentação

1. Edite os arquivos XML em `doc_classes/`
2. Recompile para embedir as mudanças
3. Reinicie o Godot Editor

## 🐛 Troubleshooting

### Documentação não aparece no Editor

1. Verifique se compilou com `target=editor`
2. Confirme que o arquivo `.gdextension` aponta para o build correto:
   ```ini
   linux.x86_64.editor = "./linux/libGodot2D-DungeonGenerationCpp.linux.editor.x86_64.so"
   ```
3. Reinicie completamente o Godot Editor

### Erro ao compilar

```bash
# Limpar cache de build
scons --clean
rm -rf .scons_cache/

# Verificar submódulos
git submodule update --init --recursive

# Recompilar
scons target=editor
```

### Extension não carrega

1. Verifique o console do Godot para erros
2. Confirme que o `entry_symbol` está correto: `example_library_init`
3. Verifique que os arquivos `.so`/`.dll` existem nos diretórios corretos

## 🤝 Contribuindo

Contribuições são bem-vindas! Por favor:

1. Fork o projeto
2. Crie uma branch para sua feature (`git checkout -b feature/MinhaFeature`)
3. Commit suas mudanças (`git commit -m 'Adiciona MinhaFeature'`)
4. Push para a branch (`git push origin feature/MinhaFeature`)
5. Abra um Pull Request

## 📝 Licença

MIT
