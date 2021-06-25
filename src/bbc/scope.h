//
// Created by liangyulin on 2021/6/25.
//

#ifndef BBASIC_SCOPE_H
#define BBASIC_SCOPE_H

#include <string>
#include <unordered_map>

#include "symbol.h"

class Scope {
    std::unordered_map<std::string, Symbol*> members_;
    Scope *enclosing_scope_;
    int level_, variable_count_;
public:
    Scope(Scope *enclosing_scope)
            : enclosing_scope_(enclosing_scope)
            , level_(enclosing_scope ? enclosing_scope->level_ + 1 : 0)
            , variable_count_(0) {}

    ~Scope() {
        for (auto &pair : members_) {
            delete pair.second;
        }
    }

    void define(Symbol *sym) {
        auto result = members_.emplace(sym->get_name(), sym);
        if (!result.second) {
            //TODO 异常
            //throw CompileException("expect compare operand", current_token_);
        }
        if (sym->is_variable()) {
            variable_count_++;
        }
    }

    Symbol *resolve(const std::string &name) {
        auto iter = members_.find(name);
        if (iter == members_.end()) {
            return enclosing_scope_ ? enclosing_scope_->resolve(name) : nullptr;
        }
        return iter->second;
    }

    inline Scope *get_enclosing_scope() {
        return enclosing_scope_;
    }

    inline int get_level() const {
        return level_;
    }

    inline int get_variable_count() const {
        return variable_count_;
    }
};


#endif //BBASIC_SCOPE_H
