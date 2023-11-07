/*******************************************************\
 *                    Roast DB
 * 
 *  src/include/roastdb/binder/expression/agg_call.h
 * 
 *  GPL-3.0 license
 * 
\*******************************************************/

#pragma once

#include <string>
#include <memory>
#include <vector>
#include <utility>
#include "BaseExpression.h"

namespace roastdb {

class AggCallExpression : public BaseExpression {
    AggCallExpression(std::string agg_name, bool is_distinct, 
                      std::vector<std::unique_ptr<BaseExpression>> args_):
        BaseExpression(ExpressionType::AGG_CALL),
        agg_name_(std::move(agg_name)),
        is_distinct_(std::move(is_distinct_)),
        args_(std::move(args_)) {}

    std::string to_string() const override;

    inline bool has_agg() const override { return true; }
        
    // Name of agg function
    std::string agg_name_;
    // Is the argument distinct
    bool is_distinct_;
    // List of args of the function
    std::vector<std::unique_ptr<BaseExpression>> args_;

};

}