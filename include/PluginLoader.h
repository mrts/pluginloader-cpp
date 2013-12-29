/*
 * Platform-independent interface for loading plug-ins.
 *
 * Created by Mart Somermaa in 2013.
 *
 * Distributed under the SQLite non-license:
 *
 * The author disclaims copyright of this source code.
 * In place of a legal notice, here is a blessing:
 *
 *   May you do good and not evil.
 *   May you find forgiveness for yourself and forgive others.
 *   May you share freely, not taking more than you give.
 *
 */

#ifndef PLUGINLOADER_H__
#define PLUGINLOADER_H__

#include <memory>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#include <Windows.h>
#undef VC_EXTRALEAN
#undef WIN32_LEAN_AND_MEAN
#endif

namespace PluginLoader
{

#ifdef _WIN32
typedef FARPROC function_ptr;
#else
typedef void* function_ptr;
#endif

class PluginLoaderImpl;

class PluginLoader
{
public:
    PluginLoader(const char* const name);
    ~PluginLoader();

    function_ptr getFunction(const char* const name);

private:
#if __cplusplus > 199711L
    std::unique_ptr<PluginLoaderImpl> pimpl;
#else
    // auto_ptrs should be avoided, but don't want to depend on Boost
    std::auto_ptr<PluginLoaderImpl> pimpl;
#endif
};

}

#endif /* PLUGINLOADER_H */
