/*******************************************************\
 *                    Roast DB
 * 
 *  src/include/roastdb/binder/expression/unary_op.h
 * 
 *  GPL-3.0 license
 * 
\*******************************************************/

#pragma once

#include <string>
#include <memory>
#include <utility>
#include "binder/BaseExpression.h"

namespace roastdb {

class UnaryOperatorExpression : public BaseExpression {
public:
    UnaryOperatorExpression(std::string op_name, std::unique_ptr<BaseExpression> arg):
        BaseExpression(ExpressionType::UNARY_OP),
        op_name_(std::move(op_name)), arg_(std::move(arg)) {}

    std::string to_string() const override;

    inline bool
    has_agg() const override { return arg_->has_agg(); }


    std::string op_name_;
    // argument
    std::unique_ptr<BaseExpression> arg_;
};
}