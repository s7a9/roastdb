/*******************************************************\
 *                    Roast DB
 * 
 *  src/include/roastdb/binder/expression/func_call.h
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

class FuncCallExpression : public BaseExpression {
    FuncCallExpression(std::string func_name,
                       std::vector<std::unique_ptr<BaseExpression>> args_):
        BaseExpression(ExpressionType::FUNC_CALL),
        func_name_(std::move(func_name)),
        args_(std::move(args_)) {}

    std::string to_string() const override;

    inline bool has_agg() const override { return false; }
        
    // Name of function
    std::string func_name_;
    // List of args of the function
    std::vector<std::unique_ptr<BaseExpression>> args_;

};

}