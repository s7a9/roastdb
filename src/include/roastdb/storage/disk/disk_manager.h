/************************************************\
 *                    Roast DB
 * 
 *  src/include/roastdb/storage/disk/disk_manager.h
 * 
 *  GPL-3.0 license
 * 
\*************************************************/

#pragma once

#include <mutex>
#include <cassert>
#include <thread>
#include <condition_variable>

#include "roastdb/common/db_config.h"

#ifdef _WIN32
#include "roastdb/storage/disk/disk_nameger_win.h"
#endif

/* ====== NOTE ======
This DiskManager cannot simply be built upon the c++ standard library.

1. DiskManager must be able to instantly know the size of the file,
which must rely on system api.

2. System apis are more natural and have higher performance.
For example, windows has a `ReadFileEX` api, which supports
asynchronous file reads. 
*/