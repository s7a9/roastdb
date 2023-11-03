/************************************************\
 *                    Roast DB
 * 
 *  src/include/roastdb/common/macros.hpp
 * 
 *  GPL-3.0 license
 * 
\*************************************************/

#pragma once

#include <cassert>
#include <stdexcept>

namespace roastdb {

#define ROASTDB_ASSERT(expr, msg) assert((expr) && (msg))

#define UNIMPLEMENTED(msg) throw std::logic_error(msg)

#define DISALLOW_COPY(cname)                 \
    cname(const cname&) = delete;            \
    cname& operator=(const cname&) = delete; \

#define DISALLOW_MOVE(cname)            \
    cname(cname&&) = delete;            \
    cname& operator=(cname&&) = delete; \

} 