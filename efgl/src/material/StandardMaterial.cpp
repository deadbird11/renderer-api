#include "efpch.h"

#include "StandardMaterial.h"

#include <../tracy/Tracy.hpp>
#include <../tracy/TracyOpenGL.hpp>

namespace efgl 
{

	void StandardMaterial::SetShaderUniforms(Shader& shader)
	{
		ZoneScopedC(tracy::Color::Orchid);
		TracyGpuZoneC("StandardMaterial::SetShaderUniforms", tracy::Color::Sienna);
		shader.Bind();

		shader.SetUniform("material.shininess", Shininess);

		for (int i = 0; i < Diffuses.size(); ++i) {
			shader.SetUniform("material.texture_diffuse" + std::to_string(i + 1), i);

			Diffuses[i]->Bind(i);
		}

		for (int i = 0; i < Speculars.size(); ++i) {
			int slot = i + Diffuses.size();
			shader.SetUniform("material.texture_specular" + std::to_string(i + 1), slot);

			Speculars[i]->Bind(slot);
		}
	}
}