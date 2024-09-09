#pragma once

#include "Core/Node.h"

namespace Nifty
{
	class Renderer : public Node
	{
	public:
		Renderer();
		~Renderer();

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;
		void OnInput(Input& input) override;

	private:

	};
}