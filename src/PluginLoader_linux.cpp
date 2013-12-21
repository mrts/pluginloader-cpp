#include <PluginLoader.h>

#include <sstream>
#include <stdexcept>

#include <dlfcn.h>

using namespace std;

namespace
{

inline void throw_error(const char* const what, const char* const name)
{
    ostringstream error;
    error << "Failed to " << what << " '" << name << "': " << dlerror();
    throw runtime_error(error.str());
}

}

namespace PluginLoader
{

class PluginLoaderImpl
{
public:
    PluginLoaderImpl(const char_t* const name) :
        plugin(dlopen(name, RTLD_NOW))
    {
        if (!plugin)
            throw_error("load plugin", name);
    }

    ~PluginLoaderImpl()
    {
        // TODO: no way to check if dlclose() fails in destructor
        dlclose(plugin);
    }

    void* getFunction(const char_t* const name)
    {
        void* function_ptr = dlsym(plugin, name);
        if (!function_ptr)
            throw_error("find symbol", name);
        return function_ptr;
    }

private:
    void* plugin;
};


PluginLoader::PluginLoader(const char_t* const name) :
    pimpl(new PluginLoaderImpl(name))
{ }

PluginLoader::~PluginLoader()
{ }

function_handle PluginLoader::getFunction(const char_t* const name)
{
    return pimpl->getFunction(name);
}

}

