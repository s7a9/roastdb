/*******************************************************\
 *                    Roast DB
 * 
 *  src/include/roastdb/binder/table_ref/cross_product_ref.h
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

class CrossProductRef : public BaseTableRef {
public:

    CrossProductRef(std::unique_ptr<BaseTableRef> left,
                    std::unique_ptr<BaseTableRef> right):
        BaseTableRef(TableRefType::CROSS_PRODUCT),
        left_(std::move(left)),
        right_(std::move(right)){}

    std::string to_string() const override;

    std::unique_ptr<BaseTableRef> left_;
    std::unique_ptr<BaseTableRef> right_;
}; 

} // namespace roastdb