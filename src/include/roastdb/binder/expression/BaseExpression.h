/*******************************************************\
 *                    Roast DB
 * 
 *  src/include/roastdb/binder/expression/BaseExpression.h
 * 
 *  GPL-3.0 license
 * 
\*******************************************************/

# pragma once

#include "common/macros.h"
#include <string>
#include <memory>

namespace roastdb {
/**
 * Expression allows for specification of a computation which can be 
 * organized as child node of statements to perfrom various tasks
*/
enum class ExpressionType : uint8_t {
    INVALID = 0,
    CONSTANT = 1, 
    COLUMN_REF = 3,
    FUNC_CALL = 4,
    AGG_CALL = 5,
    STAR = 6,
    UNARY_OP = 7,
    BINARY_OP = 8,
    ALIAS = 9,
    WINDOW = 10,
};

class BaseExpression {
public:
    explicit BaseExpression(ExpressionType type=ExpressionType::INVALID) : type_(type) {}
    virtual ~BaseExpression() = default;

    inline bool 
    is_valid() const { return type_ != ExpressionType::INVALID; }

    inline auto
    get_expression_type() const { return type_; }

    virtual std::string
    to_string() const { return ""; }

    virtual inline bool 
    has_agg() const { UNIMPLEMENTED("hasAgg function must be implemented!"); }

    virtual inline bool 
    has_win() const { return false; }  

    ExpressionType type_;
};
}