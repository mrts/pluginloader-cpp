#include <pluginloader/pluginloader.h>

#include <iostream>
#include <exception>
#include <string>

typedef int (*sqlite3_open_ptr)(const char*, void**);

using namespace std;

void testPluginLoader(const char* const what,
                      const char* const libraryName,
                      const char* const functionName)
{
    cout << "Testing " << what << endl;

    try {
        PluginLoader::PluginLoader plugin(libraryName);
        void* function = plugin.getFunction(functionName);
        sqlite3_open_ptr sqlite3_open = reinterpret_cast<sqlite3_open_ptr>(function);
        sqlite3_open("test.sqlite", &function);

        cout << "SUCESS" << endl;

    } catch (const std::exception& e) {
        cout << "FAIL: " << e.what() << endl;
    }

    cout << "---" << endl;
}

#ifdef _WIN32
const char* const SQLITE_DLL = "sqlite3.dll";
#else
const char* const SQLITE_DLL = "libsqlite3.so";
#endif

int main()
{
    testPluginLoader("invalid library (expecting FAIL)",
                     "library-that-does-not-exist", "");
    testPluginLoader("invalid function (expecting FAIL)",
                     SQLITE_DLL, "function-that-does-not-exist");
    testPluginLoader("valid library with valid function (expecting SUCCESS)",
                     SQLITE_DLL, "sqlite3_open");
    return 0;
}
