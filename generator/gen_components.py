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
    out.append('#include "../../memory/arena.h"\n\n')

    out.append(f"#define COMPONENT_COUNT {len(data['components'])}\n\n")

    # enum for component masks
    out.append("typedef enum {\n")
    for comp in data["components"]:
        out.append(f"    COMP_{comp['name'].upper()} = 1u << {data['components'].index(comp)},\n")
    out.append("} ComponentMask;\n\n")

    # Component structs
    for comp in data["components"]:
        out.append(f"typedef struct {comp['name']} {{\n")
        for field in comp["fields"]:
            out.append(f"    {field['type']} {field['name']};\n")
        out.append(f"}} {comp['name']};\n\n")

    out.append("typedef struct {\n")
    for comp in data["components"]:
        var_name = pluralize(comp['name'].lower())
        out.append(f"    {comp['name']} *{var_name};\n")
    out.append("} ComponentStorage;\n\n")
    out.append("void components_storage_init(Arena *arena, ComponentStorage *storage, uint32_t mask, uint32_t capacity);\n")

    return "".join(out)

def generate_source(data):
    out = []
    out.append("// AUTO-GENERATED FILE BY gen_components.py\n\n")
    out.append('#include "components.gen.h"\n\n')
    out.append("void components_storage_init(Arena *arena, ComponentStorage *storage, uint32_t mask, uint32_t capacity)\n{\n")
    for comp in data["components"]:
        var_name = pluralize(comp['name'].lower())
        out.append(f"    storage->{var_name} = (mask & COMP_{comp['name'].upper()}) ? ({comp['name']} *)arena_alloc(arena, sizeof({comp['name']}) * capacity) : NULL;\n")
    out.append("}\n")
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
