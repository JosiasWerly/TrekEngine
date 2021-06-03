#pragma once
#define TProject

#include <EngineLibrary/Trekkier.hpp>

using namespace std;
class SampleProject : 
	public Project {
public:
    ~SampleProject() {
    }
    void attached();
    void detached();
    void beginPlay();
    void endPlay();
};

extern "C" TApi Project * instProject(class Engine *engineRef) {
    engine = engineRef;
    return new SampleProject;
}
