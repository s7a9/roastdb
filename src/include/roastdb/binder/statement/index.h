/*******************************************************\
 *                    Roast DB
 * 
 *  src/include/roastdb/binder/statement/index.h
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
#include "roastdb/binder/BaseExpression.h"
#include "roastdb/binder/BaseTableRef.h"
#include "roastdb/binder/expression/column_ref.h"

namespace roastdb {

class IndexStatement : public BaseStatement {
public:
    IndexStatement(std::unique_ptr<BaseTableRef> table,
                   std::string index_name,
                   std::vector<std::unique_ptr<ColumnRefExpression>> cols):
        BaseStatement(StatementType::INDEX_STATEMENT),
        table_(std::move(table)),
        index_name_(std::move(index_name)),
        cols_(std::move(cols)) {}

    std::string to_string() const override;

    std::unique_ptr<BaseTableRef> table_;
    std::string index_name_;
    std::vector<std::unique_ptr<ColumnRefExpression>> cols_;
}; 

}