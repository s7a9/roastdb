/*******************************************************\
 *                    Roast DB
 * 
 *  src/include/roastdb/binder/expression/binary_op.h
 * 
 *  GPL-3.0 license
 * 
\*******************************************************/

#pragma once

#include <string>
#include <memory>
#include <utility>
#include "BaseExpression.h"

namespace roastdb {

class BinaryOperatorExpression : public BaseExpression {
public:
    BinaryOperatorExpression(std::string op_name, std::unique_ptr<BaseExpression> larg,
                             std::unique_ptr<BaseExpression> rarg):
        BaseExpression(ExpressionType::BINARY_OP),
        op_name_(std::move(op_name)), larg_(std::move(larg)), rarg_(std::move(rarg)) {}

    std::string to_string() const override;

    inline bool
    has_agg() const override { return larg_->has_agg() || rarg_->has_agg(); }


    std::string op_name_;
    // left argument
    std::unique_ptr<BaseExpression> larg_;
    //right argument
    std::unique_ptr<BaseExpression> rarg_;

};
}