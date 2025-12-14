import json
import os

ROOT = os.path.dirname(os.path.dirname(__file__))

JSON_PATH = os.path.join(ROOT, "generator", "components.json")
GEN_H_PATH = os.path.join(ROOT, "src", "include", "ecs", "component", "components.gen.h")
GEN_C_PATH = os.path.join(ROOT, "src", "include", "ecs", "component", "components.gen.c")

def pluralize(name: str) -> str:
    if name.endswith(("ch", "sh")):
        return name + "es"
    if name.endswith(("s", "x", "z")):
        return name + "es"
    if name.endswith("y") and len(name) > 1 and name[-2] not in "aeiou":
        return name[:-1] + "ies"
    return name + "s"

def generate_header(data):
    out = []
    out.append("// AUTO-GENERATED FILE BY gen_components.py\n")
    out.append("#pragma once\n\n")

    out.append("#include <stdint.h>\n")
    out.append('#include "../../memory/arena.h"\n')
    out.append('#include "../../core_types.h"\n\n')

    out.append(f"#define COMPONENT_COUNT {len(data['components'])}\n")
    out.append(f"#define COMPONENT_MASK_COUNT {(len(data['components']) + 63) // 64}\n\n")

    out.append("typedef struct Geptil_ComponentMask {\n")
    out.append("    uint64_t mask[COMPONENT_MASK_COUNT];\n")
    out.append("} Geptil_ComponentMask;\n\n")

    # enum for component index
    out.append("typedef enum {\n")
    for comp in data["components"]:
        out.append(f"    COMP_{comp['name'].upper()} = {data['components'].index(comp)},\n")
    out.append("} ComponentIndex;\n\n")

    # Component structs
    for comp in data["components"]:
        out.append(f"typedef struct Geptil_{comp['name']} {{\n")
        for field in comp["fields"]:
            out.append(f"    {field['type']} {field['name']};\n")
        out.append(f"}} Geptil_{comp['name']};\n\n")

    out.append("typedef struct Geptil_Archetype {\n")
    out.append("    uint32_t entity_count;\n")
    out.append("    uint32_t entity_capacity;\n\n")

    out.append("    uint32_t *entities;\n")
    for comp in data["components"]:
        var_name = pluralize(comp['name'].lower())
        out.append(f"    Geptil_{comp['name']} *{var_name};\n")
    out.append("} Geptil_Archetype;\n\n")


    out.append("void geptil_components_storage_init(Geptil_Arena *arena, Geptil_Archetype *arch, Geptil_ComponentMask component_mask, u32 capacity);\n")
    out.append("void geptil_archetype_grow_capacity(Geptil_Arena *arena, Geptil_Archetype *arch);\n")

    return "".join(out)

def generate_source(data):
    out = []
    out.append("// AUTO-GENERATED FILE BY gen_components.py\n\n")
    out.append('#include "components.gen.h"\n\n')
    out.append("void geptil_components_storage_init(Geptil_Arena *arena, Geptil_Archetype *arch, Geptil_ComponentMask component_mask, u32 capacity)\n{\n")
    for comp in data["components"]:
        var_name = pluralize(comp['name'].lower())
        mask_index = data['components'].index(comp) // 64
        out.append(f"    arch->{var_name} = (component_mask.mask[{mask_index}] & (1ULL << (COMP_{comp['name'].upper()} % 64))) ? (Geptil_{comp['name']} *)geptil_arena_alloc(arena, sizeof(Geptil_{comp['name']}) * capacity) : NULL;\n")
    out.append("}\n\n")

    out.append("void geptil_archetype_grow_capacity(Geptil_Arena *arena, Geptil_Archetype *arch)\n{\n")
    out.append("    arch->entities = (u32 *)geptil_arena_realloc(\n")
    out.append("        arena,\n")
    out.append("        arch->entities,")
    out.append("        sizeof(u32) * arch->entity_capacity,\n")
    out.append("        sizeof(u32) * arch->entity_capacity * 2\n")
    out.append("    );\n\n")

    out.append("    // Reallocate component arrays\n")

    for comp in data["components"]:
        var_name = pluralize(comp['name'].lower())
        out.append(f"    if (arch->{var_name}) {{\n")
        out.append(f"        arch->{var_name} = (Geptil_{comp['name']} *)geptil_arena_realloc(\n")
        out.append("            arena,\n")
        out.append(f"            arch->{var_name},\n")
        out.append(f"            sizeof(Geptil_{comp['name']}) * arch->entity_capacity,\n")
        out.append(f"            sizeof(Geptil_{comp['name']}) * arch->entity_capacity * 2\n")
        out.append("        );\n")
        out.append("    }\n")

    out.append("    arch->entity_capacity *= 2;\n")
    out.append("}\n\n")

    return "".join(out)


def main():
    with open(JSON_PATH, "r") as f:
        data = json.load(f)

    # Ensure directory exists
    os.makedirs(os.path.dirname(GEN_H_PATH), exist_ok=True)

    with open(GEN_H_PATH, "w") as f:
        f.write(generate_header(data))

    with open(GEN_C_PATH, "w") as f:
        f.write(generate_source(data))

    print("Generated:")
    print(" -", GEN_H_PATH)
    print(" -", GEN_C_PATH)


if __name__ == "__main__":
    main()
