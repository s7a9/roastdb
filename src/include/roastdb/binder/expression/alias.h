/*******************************************************\
 *                    Roast DB
 * 
 *  src/include/roastdb/binder/expression/alias.h
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

class AliasExpression : public BaseExpression {
public:
    AliasExpression(std::string alias, std::unique_ptr<BaseExpression> target):
        BaseExpression(ExpressionType::ALIAS), 
        alias_(std::move(alias)),
        target_(std::move(target)) {}

    std::string to_string() const override;

    inline bool has_agg() const override { return target_->has_agg(); }

    inline bool has_win() const override { return target_->has_win(); }

    // the alias
    std::string alias_;

    // the actual expression
    std::unique_ptr<BaseExpression> target_;
};

}