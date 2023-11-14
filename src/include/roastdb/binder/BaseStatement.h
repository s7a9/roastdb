/*******************************************************\
 *                    Roast DB
 * 
 *  src/include/roastdb/binder/BaseStatement.h
 * 
 *  GPL-3.0 license
 * 
\*******************************************************/

#pragma once

#include <string>

#include "common/db_config.h"
#include "common/macros.h"

namespace roastdb {

enum class StatementType : uint8_t {
    INVALID_STATEMENT,        // invalid statement type
    SELECT_STATEMENT,         // select statement type
    INSERT_STATEMENT,         // insert statement type
    UPDATE_STATEMENT,         // update statement type
    CREATE_STATEMENT,         // create statement type
    DELETE_STATEMENT,         // delete statement type
    EXPLAIN_STATEMENT,        // explain statement type
    DROP_STATEMENT,           // drop statement type
    INDEX_STATEMENT,          // index statement type
    VARIABLE_SET_STATEMENT,   // set variable statement type
    VARIABLE_SHOW_STATEMENT,  // show variable statement type
};

class BaseStatement {
public:
    BaseStatement(StatementType type): type_(type) {}
    virtual ~BaseStatement() = default;
    virtual std::string to_string() const {
        UNIMPLEMENTED("This type of statement does not support to string function!");
    }

    StatementType type_;
};


}