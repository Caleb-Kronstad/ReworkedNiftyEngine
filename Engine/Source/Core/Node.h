#pragma once

#include "Input/Input.h"
#include "Input/InputCodes.h"
#include "Input/InputTypes.h"

namespace Nifty
{
	class Node
	{
	protected:
		std::string m_DebugName;

	public:
		Node(const std::string& name = "Node");
		virtual ~Node() = default;

		virtual void OnAttach();
		virtual void OnDetach();
		virtual void OnUpdate();
		virtual void OnInput(Input& input);

		std::string GetName() const { return m_DebugName; }
	};
}