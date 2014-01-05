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
    PluginLoaderImpl(const char* const name) :
        plugin(dlopen(name, RTLD_NOW))
    {
        if (!plugin)
            throw_error("load plugin", name);
    }

    ~PluginLoaderImpl()
    {
        // TODO: no way to check if dlclose() fails in destructor
        if (plugin)
            dlclose(plugin);
    }

    void* getFunction(const char* const name)
    {
        void* function_ptr = dlsym(plugin, name);
        if (!function_ptr)
            throw_error("find symbol", name);
        return function_ptr;
    }

private:
    void* plugin;
};

}
