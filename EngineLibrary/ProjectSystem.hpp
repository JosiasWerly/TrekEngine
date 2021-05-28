#ifndef _ProjectSystem
#define _ProjectSystem

#include <string>
#include <sstream>
#include <fstream>
#include "DllSystem.hpp"

namespace fs = std::experimental::filesystem;
using namespace std;


#ifdef TProject
#define TApi __declspec(dllexport)
#else
#define TApi __declspec(dllimport)
#endif

typedef TApi class Project *(*FInstProject)(class Engine *engineRef);
extern "C" TApi Project *instProject(class Engine *engineRef);

class TApi Project {
public:
    Project() {}
    virtual ~Project();

    virtual void attached();
    virtual void detached();

    virtual void beginPlay();
    virtual void endPlay();
};


class DllTarget {
    string fileTargetPath, localPath;
    chrono::system_clock::time_point fileModTime;
    DynamicLibrary dll;
public:
    void setTarget(string targetPath, string localPath);
    void loadTarget();
    bool isLoaded();
    bool isDeprecated();

    DynamicLibrary &getTarget() { return dll; }
};
class ProjectSystem {
public:
    Project *attachedProject = nullptr;
    DllTarget dllTarget;

    ProjectSystem();
    void detachProject();
    bool loadProject(class Engine *engineRef);
    bool deprecatedProject();
};
#endif // !_ProjectSystem