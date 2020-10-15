#version 450 core

in vec3 VertexNormal;
in vec3 FragmentPosition;

out vec3 FragmentColor;

uniform vec3 ObjectColor;
uniform vec3 CameraPosition;
uniform vec3 LightDirection;

void main() {
    float AmbientLightIntensity = 0.1;

    float DiffuseLightIntensity = max(dot(VertexNormal, normalize(-LightDirection)), 0.0);

    FragmentColor = (AmbientLightIntensity + DiffuseLightIntensity) * ObjectColor;

    if (DiffuseLightIntensity > 0.0)
    {
        vec3 CameraDirection = normalize(CameraPosition - FragmentPosition);
        vec3 ReflectionDirection = reflect(normalize(LightDirection), VertexNormal);
        float SpecularLightIntensity = pow(max(dot(CameraDirection, ReflectionDirection), 0.0), 4);
        FragmentColor += SpecularLightIntensity * vec3(1.0, 1.0, 1.0);
    }
}