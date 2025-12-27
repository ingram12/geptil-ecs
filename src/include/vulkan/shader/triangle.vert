#version 450

layout(location = 0) in vec3 inPosition;
layout(location = 0) out vec3 fragColor;

void main() {
    vec3 pos = inPosition;
    // смещаем по X на 0.3 * номер инстанса
    pos.x += float(gl_InstanceIndex) * 0.14;

    gl_Position = vec4(pos, 1.0);
    fragColor = vec3(1.0, 1.0, 0.0);
}
