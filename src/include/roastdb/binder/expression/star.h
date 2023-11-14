/*******************************************************\
 *                    Roast DB
 * 
 *  src/include/roastdb/binder/expression/star.h
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

class StarExpression : public BaseExpression {
public:
    StarExpression(): BaseExpression(ExpressionType::STAR) {}

    bool has_agg() const override { return false; }

    std::string to_string() const override;
};

}