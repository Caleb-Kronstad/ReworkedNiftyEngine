#pragma once

#include "Core/Node.h"

namespace Nifty
{
	class EngineUI : public Node
	{
	public:
		EngineUI();
		~EngineUI();

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;
		void OnInput(Input& input) override;

	private:

	};
}
