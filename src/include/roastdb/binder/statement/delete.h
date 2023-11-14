/*******************************************************\
 *                    Roast DB
 * 
 *  src/include/roastdb/binder/statement/delete.h
 * 
 *  GPL-3.0 license
 * 
\*******************************************************/

#pragma once

#include <vector>
#include <string>
#include <utility>
#include <memory>

#include "roastdb/binder/BaseStatement.h"
#include "roastdb/binder/BaseExpression.h"
#include "roastdb/binder/BaseTableRef.h"

namespace roastdb {

class DeleteStatement : public BaseStatement {
public:
    DeleteStatement(std::unique_ptr<BaseTableRef> table, std::unique_ptr<BaseExpression> expr):
        BaseStatement(StatementType::DELETE_STATEMENT), 
        table_(std::move(table)), 
        expr_(std::move(expr)) {}

    std::string to_string() const override;

    std::unique_ptr<BaseTableRef> table_;
    std::unique_ptr<BaseExpression> expr_;
}; 

}