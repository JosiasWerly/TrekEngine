#ifndef _ProjectSystem
#define _ProjectSystem

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <sstream>  
#include <fstream>
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;


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
    virtual ~Project() {}

    virtual void attached() {}
    virtual void detached() {}

    virtual void beginPlay() {}
    virtual void endPlay() {}
};


class DllTarget {
    string fileTargetPath, localPath;
    fs::file_time_type fileModTime;
    DynamicLibrary dll;
public:
    void setTarget(string targetPath, string localPath) {
        fileTargetPath = targetPath;
        this->localPath = localPath;
    }
    void loadTarget() {
        if (dll.isLoaded())
            dll.unload();
        std::this_thread::sleep_for(std::chrono::seconds(2));
        fs::copy_file(fileTargetPath, localPath, fs::copy_options::overwrite_existing);

        if (dll.load(localPath))
            fileModTime = fs::last_write_time(fs::path(fileTargetPath.c_str()));
    } //should return a bool
    bool isLoaded() {
        return dll.isLoaded();
    }
    bool isDeprecated() {
        if (fs::exists(fileTargetPath.c_str())) {
            fs::path p(fileTargetPath.c_str());
            return fileModTime != fs::last_write_time(p);
        }
        return false;
    }

    DynamicLibrary &getTarget() { return dll; }
};
class ProjectSystem {
public:
    Project *attachedProject = nullptr;
    DllTarget dllTarget;

    ProjectSystem() {
        dllTarget.setTarget(
            "C:\\Users\\josia\\Desktop\\Bigmoxi\\Sandbox\\EngineTest\\Trek\\Build\\Debug\\x64\\ProjectSample\\ProjectSample.dll",
            "C:\\Users\\josia\\Desktop\\Bigmoxi\\Sandbox\\EngineTest\\Trek\\Build\\Debug\\x64\\EngineEditor\\ProjectSample.dll"
        );
    }
    void detachProject() {
        if (attachedProject) {
            attachedProject->detached();
            delete attachedProject;
        }
    }
    bool loadProject(class Engine *engineRef) {
        dllTarget.loadTarget();
        FInstProject pInst = dllTarget.getTarget().getFunc<FInstProject>("instProject");
        if (!pInst)
            return false;

        attachedProject = pInst(engineRef);
        if (!attachedProject)
            return false;

        attachedProject->attached();
        return true;
    }
    bool deprecatedProject() {
        return dllTarget.isDeprecated();
    }
};
#endif // !_ProjectSystem