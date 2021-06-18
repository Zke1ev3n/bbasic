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

class symbol {
    std::string name_;
public:
    symbol(const std::string &name) : name_(name) {}

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


class variable : public symbol {
    int level_;
    int index_;
public:
    variable(const std::string &name, int level, int index)
            : symbol(name), level_(level), index_(index) {}

    int get_level() const {
        return level_;
    }

    int get_index() const {
        return index_;
    }

    virtual bool is_variable() const {
        return true;
    }

};


class constant : public symbol {
    int value_;
public:
    constant(const std::string &name, int value)
            : symbol(name), value_(value) {}

    int get_value() const {
        return value_;
    }

    virtual bool is_constant() const {
        return true;
    }
};


class function : public symbol {
    int level_;
    int entry_address_;
public:
    enum { invalid_address = -1 };

    function(const std::string &name, int level)
            : symbol(name), level_(level), entry_address_(invalid_address) {}

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
