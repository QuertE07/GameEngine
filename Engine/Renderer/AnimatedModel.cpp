#include "pch.h"
#include "AnimatedModel.h"


namespace gl
{
	void AnimatedModel::Update(float dt)
	{
		float frameTime = 1.0f / m_fps;

		m_timeSinceUpdate += dt;
		if (m_timeSinceUpdate >= frameTime)
		{
			m_timeSinceUpdate -= frameTime;
			m_index++;
		}

		if (m_index >= m_frames.size())
		{
			m_index = 0;
		}
	}

	void AnimatedModel::CalculateRadius()
	{
		float radiusAvg = 0.0f;
		for (const auto& frame : m_frames)
		{
			radiusAvg += frame.GetRadius();
		}
		radiusAvg /= m_frames.size();
		m_radius = radiusAvg;
	}
}