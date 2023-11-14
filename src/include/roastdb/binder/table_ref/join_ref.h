/*******************************************************\
 *                    Roast DB
 * 
 *  src/include/roastdb/binder/table_ref/join_ref.h
 * 
 *  GPL-3.0 license
 * 
\*******************************************************/

#pragma once

#include <memory>
#include <string>
#include <utility>

#include "roastdb/binder/BaseExpression.h"
#include "roastdb/binder/BaseTableRef.h"

namespace roastdb
{

/// @brief Four types of joins
enum class JOINTYPE {
    INVALID,
    INNER,
    OUTER,
    LEFT,
    RIGHT,
};

class JoinRef : public BaseTableRef {
public:

    JoinRef(std::unique_ptr<BaseTableRef> left,
            std::unique_ptr<BaseTableRef> right,
            JOINTYPE type,
            std::unique_ptr<BaseExpression> on):
        BaseTableRef(TableRefType::JOIN),
        left_(std::move(left)),
        right_(std::move(right)),
        type_(type),
        on_(std::move(on)) {}

    std::string to_string() const override;

    std::unique_ptr<BaseTableRef> left_;
    std::unique_ptr<BaseTableRef> right_;
    JOINTYPE type_;
    std::unique_ptr<BaseExpression> on_;
}; 

} // namespace roastdb
