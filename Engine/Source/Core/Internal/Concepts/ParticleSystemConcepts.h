#pragma once

#include <concepts>
#include <vector>

namespace TGL
{
	// Forward declarations
	struct ParticleDataInfo;

	template <typename T>
	concept ValidCpuParticleData =
		std::is_class_v<T> &&
		std::default_initializable<T>;

	template <typename T>
	concept ValidGpuParticleData =
		std::is_class_v<T> &&
		std::default_initializable<T> &&
		requires {
			{
				T::GetParticleStructure()
			} -> std::same_as<std::vector<ParticleDataInfo>>;
		};
}
