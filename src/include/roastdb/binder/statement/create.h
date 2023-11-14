/*******************************************************\
 *                    Roast DB
 * 
 *  src/include/roastdb/binder/statement/create.h
 * 
 *  GPL-3.0 license
 * 
\*******************************************************/

#pragma once
#include <vector>
#include <string>
#include <utility>

#include "roastdb/binder/BaseStatement.h"
#include "roastdb/catalog/column_info.h"

namespace roastdb {

/// @brief create table t1 (int a1, int a2, PRIMARY KEY (a1))
class CreatStatement : public BaseStatement {
public:
    CreatStatement(std::string table_name, 
                   std::vector<ColumnInfo> columns, 
                   std::vector<std::string> primary_key):
        BaseStatement(StatementType::CREATE_STATEMENT),
        table_name_(std::move(table_name)),
        columns_(std::move(columns)),
        primary_key_(std::move(primary_key)) {}

    std::string to_string() const override;

    std::string table_name_;
    std::vector<ColumnInfo> columns_;
    std::vector<std::string> primary_key_;

};

}