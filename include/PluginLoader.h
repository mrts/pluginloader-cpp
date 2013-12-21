/*
 * Platform-independent interface for loading plugins.
 *
 * Created by Mart Somermaa in 2013.
 *
 * Distributed under the SQLite non-license :).
 *
 * The author disclaims copyright of this source code.
 * In place of a legal notice, here is a blessing:
 *
 *   May you do good and not evil.
 *   May you find forgiveness for yourself and forgive others.
 *   May you share freely, never taking more than you give.
 *
 */

#ifndef PLUGINLOADER_H__
#define PLUGINLOADER_H__

#include <memory>

namespace PluginLoader
{

#ifdef _WIN32
typedef TCHAR char_t;
typedef FARPROC function_handle;
#else
typedef char char_t;
typedef void* function_handle;
#endif

class PluginLoaderImpl;

class PluginLoader
{
public:
    PluginLoader(const char_t* const name);
    ~PluginLoader();

    function_handle getFunction(const char_t* const name);

private:
#if __cplusplus > 199711L
    std::unique_ptr<PluginLoaderImpl> pimpl;
#else
    // auto_ptr's should be avoided, but don't want to depend on Boost
    std::auto_ptr<PluginLoaderImpl> pimpl;
#endif
};

}

#endif /* PLUGINLOADER_H */
