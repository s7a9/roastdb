/*******************************************************\
 *                    Roast DB
 * 
 *  src/include/roastdb/binder/binder.h
 * 
 *  GPL-3.0 license
 * 
\*******************************************************/

//===----------------------------------------------------------------------===//
// Copyright 2018-2022 Stichting DuckDB Foundation
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice (including the next paragraph)
// shall be included in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//===----------------------------------------------------------------------===//

#pragma once

#include <memory>
#include <unordered_map>
#include <vector>
#include <utility>

#include <string>

#include "roastdb/binder/all_binder_components.h"
#include "catalog/catalog.h"
#include "catalog/column_info.h"
#include "common/macros.h"
#include "nodes/parsenodes.hpp"
#include "nodes/pg_list.hpp"
#include "pg_definitions.hpp"
#include "postgres_parser.hpp"
#include "types/type_id.h"
#include "types/value.hpp"


namespace duckdb_libpgquery {
struct PGList;
struct PGSelectStmt;
struct PGAConst;
struct PGAStar;
struct PGFuncCall;
struct PGNode;
struct PGColumnRef;
struct PGResTarget;
struct PGAExpr;
struct PGJoinExpr;
}  // namespace duckdb_libpgquery

namespace roastdb {

class Catalog;
class ColumnInfo;
class BaseExpression;
class BaseTableRef;
class BaseBaseTableRef;
class BaseExpression;
class BoundExpressionListRef;
class OrderBy;
class SubqueryRef;
class CreateStatement;
class ExplainStatement;
class IndexStatement;
class DeleteStatement;
class UpdateStatement;

/**
 * Binder is responsible for transforming Postgres tree into binder trees which is 
 * understandable for planner
*/
class Binder {
public:
    explicit Binder(std::shared_ptr<Catalog> catalog): catalog_(std::move(catalog)) {}

    /// @brief Parser a query and save it in statements_list_
    /// @param query SQL query in form of std::string
    void parse_and_save(const std::string &query);

    /// @brief Bind a single Postgre statement node
    std::unique_ptr<BaseStatement>
    bind_statement(duckdb_libpgquery::PGNode *stmt);

    /// @brief Bind a single Postgre expression node
    std::unique_ptr<BaseExpression>
    bind_expression(duckdb_libpgquery::PGNode *node);


    // Each of the following function correspond to a node type in Posgres tree

    std::unique_ptr<CreateStatement> 
    bind_create(duckdb_libpgquery::PGNode *stmt);

    ColumnInfo
    bind_column_def(duckdb_libpgquery::PGColumnDef *cdef);

    std::unique_ptr<SelectStatement>
    bind_select(duckdb_libpgquery::PGNode *pg_stmt);

    std::unique_ptr<BaseTableRef>
    bind_range_subselect(duckdb_libpgquery::PGRangeSubselect *root);

    std::unique_ptr<SubqueryRef>
    bind_subquery(duckdb_libpgquery::PGSelectStmt *node, const std::string &alias);

    std::vector<std::unique_ptr<BaseExpression>>
    bind_select_list(duckdb_libpgquery::PGList *list);

    std::unique_ptr<BaseExpression>
    bind_where(duckdb_libpgquery::PGNode *root);

    std::vector<std::unique_ptr<BaseExpression>>
    bind_group_by(duckdb_libpgquery::PGList *list);

    std::unique_ptr<BaseExpression>
    bind_having(duckdb_libpgquery::PGNode *root);

    std::vector<std::unique_ptr<BaseExpression>>
    bind_expression_list(duckdb_libpgquery::PGList *list);

    std::unique_ptr<BaseExpression>
    bind_constant(duckdb_libpgquery::PGAConst *node);

    std::unique_ptr<BaseExpression>
    bind_column_ref(duckdb_libpgquery::PGColumnRef *node);

    std::unique_ptr<BaseExpression>
    bind_res_target(duckdb_libpgquery::PGResTarget *root);

    std::unique_ptr<BaseExpression>
    bind_star(duckdb_libpgquery::PGAStar *node);

    std::unique_ptr<BaseExpression>
    bind_func_call(duckdb_libpgquery::PGFuncCall *root);

    std::unique_ptr<BaseExpression>
    bind_a_expr(duckdb_libpgquery::PGAExpr *root);

    std::unique_ptr<BaseExpression>
    bind_bool_expr(duckdb_libpgquery::PGBoolExpr *root);

    std::unique_ptr<BaseTableRef>
    bind_from(duckdb_libpgquery::PGList *list);
    
    std::unique_ptr<BaseTableRef>
    bing_table_ref(duckdb_libpgquery::PGNode *node);

    std::unique_ptr<BaseTableRef>
    bind_vanilla_tabel(std::string table_name, std::optional<std::string> alias);

    std::unique_ptr<BaseTableRef>
    bind_join(duckdb_libpgquery::PGJoinExpr *root);

    std::unique_ptr<InsertStatement>
    bind_insert(duckdb_libpgquery::PGInsertStmt *pg_stmt);

    std::unique_ptr<ExpressionListRef>
    bind_value_lists(duckdb_libpgquery::PGList *list);

    std::unique_ptr<BaseExpression>
    bind_limit_count(duckdb_libpgquery::PGNode *root);

    std::unique_ptr<BaseExpression>
    bind_limit_offset(duckdb_libpgquery::PGNode *root);

    std::vector<std::unique_ptr<OrderBy>>
    bind_sort(duckdb_libpgquery::PGList *list);

    std::unique_ptr<IndexStatement>
    bind_index(duckdb_libpgquery::PGIndexStmt *stmt);

    std::unique_ptr<DeleteStatement>
    bind_delete(duckdb_libpgquery::PGDeleteStmt *stmt);

    std::unique_ptr<UpdateStatement>
    bind_update(duckdb_libpgquery::PGUpdateStmt *stmt);

private:

    /// @brief Catalog that the binder uses. Catealog should outlive the binder
    std::shared_ptr<Catalog> catalog_;

    /// @brief Root for the binder tree.
    std::unique_ptr<BaseStatement> binder_tree_;

    /// @brief Vector that contians all statements in parser tree.
    std::vector<duckdb_libpgquery::PGNode*> statements_list_;

    /// @brief Parser of libpg where the root for parse tree is stored.
    duckdb::PostgresParser parser_;

};
} // namespace roastdb