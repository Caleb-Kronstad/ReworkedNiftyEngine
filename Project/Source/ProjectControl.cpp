#include "Engine.h"

#include "TestNode.h"

class ProjectInstance : public Project
{
public:
	ProjectInstance() : Project()
	{
		PushNode(new TestNode());
	}

	~ProjectInstance()
	{
	}

private:

};

int main(int argc, char** argv)
{
	auto project = new ProjectInstance();
	project->Run();
	delete project;

	return 0;
}