/*******************************************************\
 *                    Roast DB
 * 
 *  src/include/roastdb/binder/statement/update.h
 * 
 *  GPL-3.0 license
 * 
\*******************************************************/

#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "roastdb/binder/BaseStatement.h"
#include "roastdb/binder/BaseExpression.h"
#include "roastdb/binder/BaseTableRef.h"
#include "roastdb/binder/expression/column_ref.h"

namespace roastdb {

typedef std::pair<std::unique_ptr<ColumnRefExpression>, 
                  std::unique_ptr<BaseExpression>> col_expr_tuple;

class UpdateStatement : public BaseStatement {
public:
    UpdateStatement(std::unique_ptr<BaseTableRef> table, 
                    std::unique_ptr<BaseExpression> cond,
                    std::vector<col_expr_tuple> target):
        BaseStatement(StatementType::UPDATE_STATEMENT),
        table_(std::move(table)),
        cond_(std::move(cond)),
        target_(std::move(target)) {}

    std::string to_string() const override;

    std::unique_ptr<BaseTableRef> table_;
    std::unique_ptr<BaseExpression> cond_;
    std::vector<col_expr_tuple> target_;

};

} // namespace roastdb
