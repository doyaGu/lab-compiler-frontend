#include "GrammarProductionTable.h"

#include "Storage.h"

namespace grammar {
    using namespace inter;

    GrammarProductionTable::GrammarProductionTable() {
        SemanticAction expr_term_fact = [](GrammarSymbolPtr head, std::vector<GrammarSymbolPtr> &body) {
            head->setValue(body.front()->getInt());
        };

        SemanticAction expr_op_expr = [](GrammarSymbolPtr head, std::vector<GrammarSymbolPtr> &body) {
            head->setValue(Storage::instance().newTemp());
            Storage::instance().gen(
                body.at(1)->getType(),
                body.front()->getInt(),
                body.back()->getInt(),
                head->getInt()
            );
        };

        SemanticAction lp_expr_rp = [](GrammarSymbolPtr head, std::vector<GrammarSymbolPtr> &body) {
            head->setValue(body.at(1)->getInt());
        };

        SemanticAction expr_id = [](GrammarSymbolPtr head, std::vector<GrammarSymbolPtr> &body) {
            head->setValue(Storage::instance().entry(body.front()));
        };

        table_ = {
            // 0. E→E
            GrammarProduction(SymbolType::EXPR, {SymbolType::EXPR},
                              expr_term_fact,
                              "Expr -> Expr"),
            // 1. E→E+T
            GrammarProduction(SymbolType::EXPR, {SymbolType::EXPR, SymbolType::PL, SymbolType::TERM},
                              expr_op_expr,
                              "Expr -> Expr + Term"),
            // 2. E→E-T
            GrammarProduction(SymbolType::EXPR, {SymbolType::TERM, SymbolType::MI, SymbolType::TERM},
                              expr_op_expr,
                              "Expr -> Expr - Term"),
            // 3. E→T
            GrammarProduction(SymbolType::EXPR, {SymbolType::TERM},
                              expr_term_fact,
                              "Expr -> Term"),
            // 4. T→T*F
            GrammarProduction(SymbolType::TERM, {SymbolType::TERM, SymbolType::MU, SymbolType::FACTOR},
                              expr_op_expr,
                              "Term -> Term * Factor"),
            // 5. T→T/F
            GrammarProduction(SymbolType::TERM, {SymbolType::TERM, SymbolType::DI, SymbolType::FACTOR},
                              expr_op_expr,
                              "Term -> Term / Factor"),
            // 6. T→F
            GrammarProduction(SymbolType::TERM, {SymbolType::FACTOR},
                              expr_term_fact,
                              "Term -> Factor"),
            // 7. F→(E)
            GrammarProduction(SymbolType::FACTOR, {SymbolType::LPAREN, SymbolType::EXPR, SymbolType::RPAREN},
                              lp_expr_rp,
                              "Factor -> ( Expr )"),
            // 8. F→i
            GrammarProduction(SymbolType::FACTOR, {SymbolType::OPERAND},
                              expr_id,
                              "Factor -> Identifier")
        };
    }

    const GrammarProduction &GrammarProductionTable::lookup(const int index) const {
        return table_.at(index);
    }
}
