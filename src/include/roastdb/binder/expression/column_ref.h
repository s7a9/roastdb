/*******************************************************\
 *                    Roast DB
 * 
 *  src/include/roastdb/binder/expression/column_ref.h
 * 
 *  GPL-3.0 license
 * 
\*******************************************************/

#pragma once

#include <string>
#include <memory>
#include <vector>
#include <utility>
#include "binder/BaseExpression.h"

namespace roastdb {

/** 
 * A list of column name to be refed
*/
class ColumnRefExpression : public BaseExpression {
public:

    explicit ColumnRefExpression(std::vector<std::string> column_names):
        BaseExpression(ExpressionType::COLUMN_REF),
        column_names_(std::move(column_names)) {}
    explicit ColumnRefExpression(std::vector<std::string> column_names, 
                                 std::string tabel_name):
        BaseExpression(ExpressionType::COLUMN_REF),
        column_names_(std::move(column_names)),
        table_name_(std::move(tabel_name)) {}
    
    inline bool has_agg() const override { return false; }

    std::string to_string() const override;

    std::string table_name_;
    std::vector<std::string> column_names_;
};
}
