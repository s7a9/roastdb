/*******************************************************\
 *                    Roast DB
 * 
 *  src/include/roastdb/binder/expression/constant.h
 * 
 *  GPL-3.0 license
 * 
\*******************************************************/

# pragma once

#include <string>
#include <memory>
#include "binder/BaseExpression.h"
#include "types/value.hpp"

namespace roastdb{

class ConstantExpression : BaseExpression {
public:
    ConstantExpression(const Value &val): 
    BaseExpression(ExpressionType::CONSTANT), val_(val) {}

    // Does value need function toString?

    inline bool has_agg() const override { return false; }

    std::string to_string() const override;

    Value val_;
};

}