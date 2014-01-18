#include <sstream>
#include <stdexcept>

using namespace std;

// Using the non-Unicode API calls as GetProcAddress() is non-Unicode anyway

namespace
{

inline void throw_error(const char* const what,
                        const char* const name)
{
    DWORD errorCode = ::GetLastError();
    LPSTR errorText = NULL;
    DWORD resultLength = ::FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM |
            FORMAT_MESSAGE_ALLOCATE_BUFFER,
            NULL, errorCode, 0,
            reinterpret_cast<LPSTR>(&errorText),
            MAX_PATH, 0);

	stringstream error;
    error << "Failed to " << what << " '" << name;
    if (resultLength > 0)
        error << "': " << errorText;
    else
        error << "': error code 0x" << std::hex << errorCode;

    // we leak if stringstream throws...
    ::LocalFree(errorText);

    throw runtime_error(error.str());
}

}

namespace PluginLoader
{

class PluginLoaderImpl
{
public:
    PluginLoaderImpl(const char* const name) :
        plugin(::LoadLibraryA(name))
    {
        if (!plugin)
            throw_error("load plug-in", name);
    }

    ~PluginLoaderImpl()
    {
        // TODO: no way to check if FreeLibrary() fails in destructor
        if (plugin)
            ::FreeLibrary(plugin);
    }

	FARPROC getFunction(const char* const name)
    {
        FARPROC function_ptr = ::GetProcAddress(plugin, name);
        if (!function_ptr)
            throw_error("find symbol", name);
        return function_ptr;
    }

private:
    HMODULE plugin;
};

}
