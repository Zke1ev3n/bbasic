#pragma once

#include <string>
#include <vector>
#include <map>

using namespace std;

enum{
    ES_VARINT=0x10,
    ES_VARFLOAT=0x11,
    ES_VARSTRING=0x12,
};

class Symbol {
    std::string name_;
public:
    Symbol(const std::string &name) : name_(name) {}

    const std::string &get_name() const {
        return name_;
    }

    virtual bool is_variable() const {
        return false;
    }

    virtual bool is_constant() const {
        return false;
    }

    virtual bool is_function() const {
        return false;
    }
};


class Variable : public Symbol {
    int level_;
    int index_;
    bool is_global_;
public:
    Variable(const std::string &name, int level, int index, bool is_global)
            : Symbol(name), level_(level), index_(index), is_global_(is_global) {}

    int get_level() const {
        return level_;
    }

    int get_index() const {
        return index_;
    }

    bool is_global() {
        return is_global_;
    }

    virtual bool is_variable() const {
        return true;
    }

};


class Constant : public Symbol {
    int value_;
public:
    Constant(const std::string &name, int value)
            : Symbol(name), value_(value) {}

    int get_value() const {
        return value_;
    }

    virtual bool is_constant() const {
        return true;
    }
};


class Function : public Symbol {
    int level_;
    int entry_address_;
public:
    enum { invalid_address = -1 };

    Function(const std::string &name, int level)
            : Symbol(name), level_(level), entry_address_(invalid_address) {}

    int get_level() const {
        return level_;
    }

    void set_entry_address(int ea) {
        entry_address_ = ea;
    }

    int get_entry_address() const {
        return entry_address_;
    }

    virtual bool is_function() const {
        return true;
    }
};
