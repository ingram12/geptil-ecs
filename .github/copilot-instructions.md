# Geptil ECS - AI Agent Instructions

## Architecture Overview

This is a C17-based Entity Component System (ECS) with **archetype-based storage** and an **arena allocator** for memory management. The ECS uses bitmasked component queries to efficiently iterate over entities with specific component combinations.

### Core Concepts

- **Archetype**: A unique combination of components (e.g., Position+Rotation). Entities with the same components share an archetype and are stored contiguously for cache efficiency.
- **Component Mask**: 64-bit bitfield arrays (`ComponentMask.mask[COMPONENT_MASK_COUNT]`) where each bit represents presence of a component type.
- **Query System**: Matches archetypes to component requirements using bitwise AND operations. Queries cache matching archetype indices for fast iteration.
- **Arena Allocator**: All ECS allocations go through the arena (`Context.arena`). No individual frees - reset the entire arena to reclaim memory.

## Component Code Generation

**CRITICAL**: Components are **NOT** manually written. They are code-generated from [generator/components.json](../generator/components.json).

### Adding/Modifying Components

1. Edit [generator/components.json](../generator/components.json) with component definitions
2. Run: `python generator/gen_components.py`
3. Regenerates [src/include/ecs/component/components.gen.h](../src/include/ecs/component/components.gen.h) and [components.gen.c](../src/include/ecs/component/components.gen.c)

Generated code includes:
- Component structs (e.g., `Position`, `Rotation`)
- `ComponentIndex` enum (e.g., `COMP_POSITION`, `COMP_ROTATION`)
- `Archetype` struct with component arrays (pluralized: `positions`, `rotations`)
- `geptil_components_storage_init()` - allocates component arrays based on mask
- `geptil_archetype_grow_capacity()` - doubles archetype capacity via geptil_arena_realloc

**Never** manually edit `.gen.h` or `.gen.c` files - they will be overwritten.

## Development Workflow

### Build & Run
```bash
make DEBUG=1         # Debug build with ASAN/UBSAN sanitizers
make                 # Release build (-O2 -march=native)
make run             # Build and execute
make clean           # Remove build artifacts
```

VS Code tasks available: `build (debug)` (default), `build (release)`

### Project Structure
```
src/include/         # All header and implementation files
  ecs/               # ECS core (entity, archetype, component, query)
  memory/            # Arena allocator (arena.c/h)
  logger/            # Logging utilities
  context.h/c        # Global context (holds ECS + Arena)
src/systems/         # ECS systems (e.g., move.c)
generator/           # Component code generator
```

## Code Conventions

### Type Aliases (core_types.h)
Use project typedefs instead of stdint types:
- `u8`, `u16`, `u32`, `u64` (unsigned)
- `i8`, `i16`, `i32`, `i64` (signed)
- `f32`, `f64` (floating-point)

### Archetype-Based Data Access

Entities are **not** accessed individually. Systems iterate over archetypes:

```c
// CORRECT: Archetype-oriented iteration
void geptil_system_move(Context *ctx) {
    u32 query_id = 0;  // Query for Position component
    QueryArchetypeIndices *query = &ctx->ecs.query_archetype_indices[query_id];
    
    for (u32 i = 0; i < query->count; ++i) {
        Archetype *arch = &ctx->ecs.archetypes[query->indices[i]];
        Position *positions = arch->positions;  // Array of positions
        
        for (u32 j = 0; j < arch->entity_count; ++j) {
            positions[j].x += 1.0;  // Operate on components directly
        }
    }
}
```

**Key Pattern**: Always iterate `query->count` (archetypes), then `arch->entity_count` (entities in archetype).

### Memory Management

- **All allocations** go through `geptil_arena_alloc()` or `geptil_arena_realloc()`.
- No `malloc/free` - arena owns all memory.
- Reallocation pattern: `geptil_arena_realloc(arena, ptr, old_size, new_size)` - **must** provide old_size.
- Growing arrays: Double capacity, not incremental (see `geptil_grow_archetype()`, `geptil_grow_query()`).

### Component Mask Building

```c
const ComponentIndex components[] = {COMP_POSITION, COMP_ROTATION};
ComponentMask mask = geptil_build_component_mask(components, 2);
```

Pass array of `ComponentIndex` enums - never construct masks manually.

### Entity Creation

```c
u32 archetype_id = geptil_archetype_init(ctx, component_mask);  // Gets/creates archetype
EntityId entity = geptil_entity_init(ctx, archetype_id, 0);     // Spawns entity in archetype
```

Archetype initialization is **idempotent** - returns existing archetype if mask matches.

## Common Patterns

### System Implementation

1. Place system in `src/systems/` with `.h` and `.c`
2. System signature: `void geptil_system_name(Context *ctx)`
3. Use queries to filter entities (create query in main or system)
4. Access component arrays directly from archetypes

### Query Creation

```c
const ComponentIndex comps[] = {COMP_POSITION};
ComponentMask mask = geptil_build_component_mask(comps, 1);
u32 query_id = geptil_init_query(&ctx->arena, &ctx->ecs, mask);
```

Queries are created once and reused. They cache matching archetype indices.

## File Naming

- Headers: `.h` files in `src/include/`
- Implementations: `.c` files co-located with headers in `src/include/` subdirectories
- Systems: Both `.h` and `.c` in `src/systems/`
- Main entry: [src/main.c](../src/main.c)

## Build System Notes

- Makefile uses `find src -name '*.c'` to discover all source files
- Auto-generates dependency files (`.d`) for incremental builds
- Object files preserve directory structure in `build/`
- Includes sanitizers (ASAN/UBSAN) in debug mode - critical for catching memory errors
