#pragma once
#include "Json.h"

#include <string>

namespace gl
{
	class Object
	{
	public:
		Object() = default;
		virtual ~Object() = default;

		const std::string& GetName() const { return m_name; }
		bool IsActive() const { return m_active; }
		void SetName(const std::string name) { m_name = name; }
		void SetActive(bool active = true) { m_active = active; }

		virtual void Read(const json::value_t& value)
		{
			JSON_READ_NAME(value, "name", m_name);
			JSON_READ_NAME(value, "active", m_active);
		}

	protected:
		std::string m_name;
		bool m_active = true;
	};
}