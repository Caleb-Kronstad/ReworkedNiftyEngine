#include "nfpch.h"
#include "Engine.h"

class ProjectInstance : public Nifty::Project
{
public:
	ProjectInstance() : Nifty::Project()
	{

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