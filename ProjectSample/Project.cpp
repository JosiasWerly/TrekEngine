#include "Project.hpp"

extern "C" TApi Project *instProject(class Engine *engineRef) {
	engine = engineRef;
	return new SampleProject;
}