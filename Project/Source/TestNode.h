#pragma once

#include "Engine.h"

using namespace Nifty;

class TestNode : public Node
{
public:
	TestNode();
	~TestNode();

	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate() override;
	void OnInput(Nifty::Input& input) override;

private:

};