#pragma once
#include "Model.h"

namespace gl
{
	class AnimatedModel
	{
	public:
		AnimatedModel() = default;
		AnimatedModel(const std::vector<Mesh>& model) : m_frames{ model }
		{
			CalculateRadius();
		}
		AnimatedModel(float fps, std::vector<Model> frames) : m_fps{ fps }, m_frames{ frames }
		{
			CalculateRadius();
		}

		void Update(float dt);

		float GetFPS() const { return m_fps; }
		void SetFPS(float fps) { m_fps = fps; }
		const std::vector<Mesh>& GetFrame() const { return m_frames.at(m_index).GetMeshes(); }
		const std::vector<Mesh>& GetFrame(unsigned int index) const { if (index < m_frames.size()) return m_frames.at(index).GetMeshes(); }
		void SetFrame(const Model model) { m_frames.at(m_index) = model; }
		void SetFrame(const Model model, unsigned int index) { if (index < m_frames.size()) m_frames.at(index) = model; }

		float GetRadius() const { return m_radius; }
		void CalculateRadius();

	private:
		float m_radius = 0.0f;
		float m_fps = 0.0f;
		float m_timeSinceUpdate = 0.0f;
		unsigned int m_index = 0;
		std::vector<Model> m_frames;
	};
}