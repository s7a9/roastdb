/*******************************************************\
 *                    Roast DB
 * 
 *  src/include/roastdb/binder/table_ref/subquery_ref.h
 * 
 *  GPL-3.0 license
 * 
\*******************************************************/

#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "roastdb/binder/BaseExpression.h"
#include "roastdb/binder/BaseTableRef.h"
#include "roastdb/binder/statement/select.h"

namespace roastdb
{

class SubqueryRef : public BaseTableRef {
public:

    SubqueryRef(std::unique_ptr<SelectStatement> subquery,
                std::vector<std::string> column_names,
                std::string alias_): 
        BaseTableRef(TableRefType::SUBQUERY),
        subquery_(std::move(subquery)),
        column_names_(std::move(column_names)),
        alias_(std::move(alias_)) {}

    std::string to_string() const override;

    /// @brief Select Statemenent that composes of the subquery
    std::unique_ptr<SelectStatement> subquery_;

    /// @brief Names of each columns
    std::vector<std::string> column_names_;

    /// @brief alias of the subquery
    std::string alias_;
}; 

} // namespace roastdb