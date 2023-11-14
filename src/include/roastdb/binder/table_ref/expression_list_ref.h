/*******************************************************\
 *                    Roast DB
 * 
 *  src/include/roastdb/binder/table_ref/expression_list_ref.h
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
#include "roastdb/types/value.hpp"

namespace roastdb
{
    
class ExpressionListRef : public BaseTableRef {
public:
    ExpressionListRef(std::vector<std::unique_ptr<BaseExpression>> values,
                      std::string list_name):
        BaseTableRef(TableRefType::EXPRESSION_LIST),
        values_(std::move(values)),
        list_name_(std::move(list_name)) {}

    std::string to_string() const override;

    std::vector<std::unique_ptr<BaseExpression>> values_;
    std::string list_name_;
};

} // namespace roastdb
