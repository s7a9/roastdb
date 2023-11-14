/*******************************************************\
 *                    Roast DB
 * 
 *  src/include/roastdb/binder/order_by.h
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

namespace roastdb {

enum class OrderByType {
    INVALID = 0,
    DEFAULT = 1,
    ASC = 2,
    DESC = 3,
};

class OrderBy {
public:

    OrderBy(OrderByType type, std::unique_ptr<BaseExpression> expr):
        type_(type), expr_(std::move(expr)) {}
    ~OrderBy() = default;

    std::string to_string() const;

    OrderByType type_;
    std::unique_ptr<BaseExpression> expr_;
};

} // namespace roastdb