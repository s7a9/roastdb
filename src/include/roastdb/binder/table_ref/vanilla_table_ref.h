/*******************************************************\
 *                    Roast DB
 * 
 *  src/include/roastdb/binder/table_ref/vanilla_table_ref.h
 * 
 *  GPL-3.0 license
 * 
\*******************************************************/

#pragma once

#include <memory>
#include <string>
#include <utility>

#include "roastdb/storage/table/table.h"
#include "roastdb/binder/BaseTableRef.h"

namespace roastdb
{
    
class VanillaTableRef : public BaseTableRef {
public:
    explicit VanillaTableRef(std::shared_ptr<Table> table, std::string alias): 
        BaseTableRef(TableRefType::VANILLA_TABLE),
        table_(std::move(table)),
        alias_(std::move(alias)) {}

    std::string to_string() const override;

    std::string get_table_name() const;

    std::shared_ptr<Table> table_;
    std::string alias_;
};

} // namespace roastdb
