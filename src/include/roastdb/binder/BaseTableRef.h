/*******************************************************\
 *                    Roast DB
 * 
 *  src/include/roastdb/binder/BaseTableRef.h
 * 
 *  GPL-3.0 license
 * 
\*******************************************************/

#pragma once

#include <string>

#include "common/db_config.h"

namespace roastdb {

enum class TableRefType : uint8_t {
    INVALID = 0,         /**< Invalid table reference type. */
    VANILLA_TABLE = 1,      /**< Vanilla table reference. */
    JOIN = 3,            /**< Output of join. */
    CROSS_PRODUCT = 4,   /**< Output of cartesian product. */
    EXPRESSION_LIST = 5, /**< Values clause. */
    SUBQUERY = 6,        /**< Subquery. */
    CTE = 7,             /**< CTE. Not supported*/
    EMPTY = 8            /**< Placeholder for empty FROM. */
};

class BaseTableRef {
public:
    explicit BaseTableRef(TableRefType type): type_(type) {}
    virtual ~BaseTableRef() = default;

    virtual std::string to_string() const {
        switch (type_) {
        case TableRefType::INVALID:
            return "Invalid";
            break;
        case TableRefType::EMPTY:
            return "<empty>";
        }
    } 
    TableRefType type_;

};


} // namespace roastdb
