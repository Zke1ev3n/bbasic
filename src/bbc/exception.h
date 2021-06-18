//
// Created by 梁玉林 on 2021/6/8.
//

#ifndef BBC_EXCEPTION_H
#define BBC_EXCEPTION_H

#include <sstream>
#include <string>

#include "token.h"


class Exception {
public:
    Exception() { stream_ = new std::ostringstream(); }
    ~Exception() {
        if (stream_) {
            delete (stream_);
        }
        stream_ = NULL;
    }
    const std::string message() const { return stream_->str(); }

protected:
    std::ostringstream& stream() { return *stream_; }

private:
    std::ostringstream* stream_;
};

class CompileException : public Exception {
public:
    std::string trim(const std::string& s) {
        std::string result = s;
        if (result.empty()) {
            return result;
        }

        result.erase(0, result.find_first_not_of(" "));
        result.erase(result.find_last_not_of(" ") + 1);
        return result;
    }

    CompileException(const char* msg, const Token& token) {
        stream() << "(line:" << token.line_ << ", column:" << token.column_
                 << "):" << msg << ", get " << token.lexeme_;
    }

//    CompileException(const char* key, const char* msg, const Token& token,
//                     std::string str_line_) {
//        stream() << "(line:" << token.line_ << ", column:" << token.column_
//                 << "):" << key << msg << " around \"" << trim(str_line_) << "\"";
//    }
};


#endif //BBC_EXCEPTION_H
