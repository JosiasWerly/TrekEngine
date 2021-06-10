#include "ProjectSystem.hpp"
//
//
//#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
//#include <experimental/filesystem>
//
//
//
//void DllTarget::setTarget(string targetPath, string localPath) {
//	fileTargetPath = targetPath;
//	this->localPath = localPath;
//}
//void DllTarget::loadTarget() {
//	if (dll.isLoaded())
//		dll.unload();
//	std::this_thread::sleep_for(std::chrono::seconds(2));
//	fs::copy_file(fileTargetPath, localPath, fs::copy_options::overwrite_existing);
//	std::this_thread::sleep_for(std::chrono::seconds(2));
//	if (dll.load(localPath))
//		fileModTime = fs::last_write_time(fs::path(fileTargetPath.c_str()));
//}
//bool DllTarget::isLoaded() {
//	return dll.isLoaded();
//}
//bool DllTarget::isDeprecated() {
//	if (fs::exists(fileTargetPath.c_str())) {
//		fs::path p(fileTargetPath.c_str());
//		return fileModTime != fs::last_write_time(p);
//	}
//	return false;
//}
//
//
//ProjectSystem::ProjectSystem() {
//	dllTarget.setTarget(
//		"C:\\Users\\josia\\Desktop\\Bigmoxi\\Sandbox\\EngineTest\\Trek\\Build\\Debug\\x64\\ProjectSample\\ProjectSample.dll",
//		"C:\\Users\\josia\\Desktop\\Bigmoxi\\Sandbox\\EngineTest\\Trek\\Build\\Debug\\x64\\EngineEditor\\ProjectSample.dll"
//	);
//}
//void ProjectSystem::detachProject() {
//	if (attachedProject) {
//		attachedProject->detached();
//		delete attachedProject;
//	}
//}
//bool ProjectSystem::loadProject(class Engine *engineRef) {
//	dllTarget.loadTarget();
//	FInstProject pInst = dllTarget.getTarget().getFunc<FInstProject>("instProject");
//	if (!pInst)
//		return false;
//
//	attachedProject = pInst(engineRef);
//	if (!attachedProject)
//		return false;
//
//	attachedProject->attached();
//	return true;
//}
//bool ProjectSystem::deprecatedProject() {
//	return dllTarget.isDeprecated();
//}