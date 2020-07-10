#include <string>
#include <utility>
#include "xml/Lexer.h"
#include <iostream>

std::string stringTrim(const std::string &str) {
        int i = 0, j = str.size()-1;
        while (str[i] == ' ' || str[i] == '\t') ++i;
        while (str[j] == ' ' || str[j] == '\t') --j;
        return str.substr(i, j - i + 1);
}


Lexer::Lexer(std::string str)
: mStr(std::move(str)), mData({mStr.begin(), State::PARSE_BODY, QuoteType::SINGLE})

{}

Token blockQuoteMatcher(std::string::iterator &itr, const std::string::iterator &end) {
    static const std::regex reBeginProlog("<\\?xml");
    static const std::regex reBeginCloseBlock("</");
    if(std::distance(itr, end) >= 5) {
        auto endBegin = itr+5;
        if(std::regex_match(itr, endBegin, reBeginProlog)) {
            itr = endBegin;
            return {"<?xml", Token::BEGIN_PROLOG};
        }
    }
    if(std::distance(itr, end) >= 2) {
        auto beginCloseBlock = itr + 2;
        if(std::regex_match(itr, beginCloseBlock, reBeginCloseBlock)) {
            itr = beginCloseBlock;
            return {"</", Token::OPEN_QUOTE_END_BLOCK};
        }
    }
    if(*itr == '<') {
        ++itr;
        return {"<", Token::OPEN_QUOTE_BLOCK};
    }
    return {std::string(itr, ++itr), Token::ERROR};
}

Token Lexer::endProlog() {
    auto end = mStr.end();
    if(std::distance(mData.mItr, end) >= 2) {
        if(*mData.mItr == '?' && *(++mData.mItr) == '>') {
            Token tok = {"?>", Token::END_PROLOG};
            ++mData.mItr;
            return tok;
        }
    }
    auto beginErrorString = mData.mItr;
    ++mData.mItr;
    --beginErrorString;
    return {std::string(beginErrorString, mData.mItr), Token::ERROR};
}

//Token Lexer::variableNode() {
//    static const std::regex reVariable("[a-zA-Z][a-zA-Z0-9]*");
//    static const std::regex reSpace("[\\s>]");
//    auto end = mStr.end();
//    auto endVariable = mItr;
//    std::string::iterator tmp = endVariable;
//    while(endVariable != end &&  !std::regex_match(endVariable, ++tmp, reSpace)  && *endVariable != '=') {
//        tmp = ++endVariable;
//    }
//    if(std::regex_match(mItr, endVariable, reVariable)) {
//        Token tok = {std::string(mItr, endVariable), Token::VARIABLE};
//        mItr = endVariable;
//        return tok;
//    }
//    Token tok = {std::string(mItr, endVariable), Token::ERROR};
//    mItr = endVariable;
//    return tok;
//}

Token Lexer::parseString(){
    std::regex reString;//("[^'\"<>]+");
    std::regex reStringEnd;//("[\\s'\"]");
    Token::Type returnTokenType;
    if(mData.mState == State::PARSE_BODY) {
        reString = std::regex("[^<>]+");
        reStringEnd = std::regex("<");
        returnTokenType = Token::STRING;
    } else if(mData.mState == State::PARSE_PROPERTY_NAME) {
        reString = std::regex("[a-zA-Z][a-zA-Z0-9]*");
        reStringEnd = std::regex("[\\s=>]");
        returnTokenType = Token::VARIABLE;
    } else if(mData.mState == State::PARSE_PROPERTY_VALUE) {
        char quote = static_cast<char>(mData.mQuoteType);
        reString = std::regex(".+");
        reStringEnd = std::regex(std::string(&quote, 1));
        mData.mState = State::PARSE_PROPERTY_NAME;
        returnTokenType = Token::STRING;
    }
    auto endVariable = mData.mItr;
    auto end = mStr.end();
    std::string::iterator tmp = endVariable;
    while(endVariable != end && !std::regex_match(endVariable, ++tmp, reStringEnd) ) {
        tmp = ++endVariable;
    }
    if(std::regex_match(mData.mItr, endVariable, reString)) {
        Token tok = {stringTrim(std::string(mData.mItr, endVariable)), returnTokenType};
        mData.mItr = endVariable;
        return tok;
    }
    Token tok = {std::string(mData.mItr, endVariable), Token::ERROR};
    mData.mItr = ++endVariable;
    return tok;
}


Token Lexer::next() {
    static const std::regex reSpace("\\s");
    mBeforeState = mData;
    while(true) {
        if (mData.mItr == mStr.end()) {
            return {"", Token::END};
        }
        auto tmp = mData.mItr;
        if (std::regex_match(mData.mItr, ++tmp, reSpace)) {
            ++mData.mItr;
            continue;
        }
        break;
    }
        Token tok;
        switch(*mData.mItr) {
            case '<': {
                tok = blockQuoteMatcher(mData.mItr, mStr.end());
                if(tok.type != Token::ERROR) {
                    mData.mState = State::PARSE_PROPERTY_NAME;
                }
                break;
            }
            case '>': {
                mData.mState = State::PARSE_BODY;
                ++mData.mItr;
                tok = {">", Token::CLOSE_QUOTE_BLOCK};
                break;
            }
            case '?': {
                tok =  endProlog();
                if(tok.type != Token::ERROR) {
                    mData.mState = State::PARSE_BODY;
                }
                break;
            }
            case '\'': {
                mData.mQuoteType = QuoteType::SINGLE;
                ++mData.mItr;
                tok =  {"'", Token::QUOTE};
                break;
            }
            case '"': {
                mData.mQuoteType = QuoteType::DOUBLE;
                ++mData.mItr;
                tok =  {"\"", Token::DQUOTE};
                break;
            }
            case '=': {
                ++mData.mItr;
                mData.mState = State::PARSE_PROPERTY_VALUE;
                tok =  {"=", Token::EQ};
                break;
            }
            default: {
                tok = parseString();
            }
        }
    return  tok;
}


void Lexer::back() {
    mData = mBeforeState;
}