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
#include "roastdb/binder/order_by.h"
#include "roastdb/binder/expression/column_ref.h"

namespace roastdb {


class SelectStatement : public BaseStatement {
public:

    SelectStatement(std::unique_ptr<BaseTableRef> from,
                    std::vector<std::unique_ptr<BaseExpression>> target,
                    std::unique_ptr<BaseExpression> where,
                    std::vector<std::unique_ptr<BaseExpression>> group_by,
                    std::unique_ptr<BaseExpression> having,
                    std::vector<std::unique_ptr<OrderBy>> order_by,
                    std::unique_ptr<BaseExpression> limit_count,
                    std::unique_ptr<BaseExpression> limit_offset,
                    bool is_distinct):
        BaseStatement(StatementType::SELECT_STATEMENT),
        from_(std::move(from)),
        target_(std::move(target)),
        where_(std::move(where)),
        group_by_(std::move(group_by)),
        having_(std::move(having)),
        order_by_(std::move(order_by)),
        limit_count_(std::move(limit_count)),
        limit_offset_(std::move(limit_offset)),
        is_distinct_(is_distinct) {} 

    std::string to_string() const override;

    /// @brief From Clause
    std::unique_ptr<BaseTableRef> from_;

    /// @brief Select target
    std::vector<std::unique_ptr<BaseExpression>> target_;

    /// @brief Where Clause
    std::unique_ptr<BaseExpression> where_;

    /// @brief Group By Clause
    std::vector<std::unique_ptr<BaseExpression>> group_by_;

    /// @brief Having Clase
    std::unique_ptr<BaseExpression> having_;

    /// @brief Order By Clause
    std::vector<std::unique_ptr<OrderBy>> order_by_;

    /// @brief limit Clause
    std::unique_ptr<BaseExpression> limit_count_;
    std::unique_ptr<BaseExpression> limit_offset_;

    /// @brief Select distinct
    bool is_distinct_;
};

} // namespace roastdb