/*******************************************************\
 *                    Roast DB
 * 
 *  src/include/roastdb/binder/statement/insert.h
 * 
 *  GPL-3.0 license
 * 
\*******************************************************/

#pragma once

#include <string>
#include <utility>
#include <memory>
#include <vector>

#include "roastdb/binder/BaseStatement.h"
#include "roastdb/binder/BaseTableRef.h"
#include "roastdb/binder/statement/select.h"

namespace roastdb {

class InsertStatement : public BaseStatement {
public:
    InsertStatement(std::unique_ptr<BaseTableRef> table,
                    std::unique_ptr<SelectStatement> target):
        BaseStatement(StatementType::INSERT_STATEMENT),
        table_(std::move(table)),
        target_(std::move(target)) {}

    std::string to_string() const override;

    std::unique_ptr<BaseTableRef> table_;
    std::unique_ptr<SelectStatement> target_;
}; 

}