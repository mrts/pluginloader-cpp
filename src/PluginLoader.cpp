#include <pluginloader/pluginloader.h>

#ifdef _WIN32
#include "PluginLoaderImpl_windows.h"
#else
#include "PluginLoaderImpl_linux.h"
#endif

namespace PluginLoader
{

PluginLoader::PluginLoader(const char* const name) :
    pimpl(new PluginLoaderImpl(name))
{ }

PluginLoader::~PluginLoader()
{ }

function_ptr PluginLoader::getFunction(const char* const name)
{
    return pimpl->getFunction(name);
}

}
