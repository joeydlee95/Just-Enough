#include "request_handler.h"

#include "utils.h"
#include <string>
#include <sstream>
#include <iostream>
#include <vector>

using std::string;
using std::vector;
using Headers = vector<std::pair<string, string>>;

std::unique_ptr<Request> Request::Parse(const string& raw_request) {
    std::stringstream reqSS(raw_request);

    std::unique_ptr<Request> req(new Request());

    string head = getCRLFLine(reqSS);
    vector<string> headTokens = split(head, ' ');
    if (headTokens.size() != 3) { // VERB PATH HTTP/VERSION
        std::cerr << "received malformed request" << std::endl;
        return nullptr;
    }
    req->method_ = headTokens[0];
    // TODO: validate method_

    req->uri_ = headTokens[1];

    // HTTP/1.1
    if (headTokens[2].substr(0, 5) != "HTTP/") {
        std::cerr << "received malformed request" << std::endl;
        return nullptr;
    }
    req->version_ = headTokens[2];

    while (true) {
        string line = getCRLFLine(reqSS);
        if (line == "") break;

        size_t delimPos = line.find(':');
        if (delimPos == string::npos) {
            std::cerr << "received malformed request" << std::endl;
            return nullptr;
        }

        std::stringstream lineSS(line);
        string headerKey = line.substr(0, delimPos);
        size_t headerValueStart = delimPos+1; // after ':'
        while (headerValueStart < line.size() && line[headerValueStart] == ' ') {
            headerValueStart++;
        }
        string headerValue = line.substr(headerValueStart);

        // TODO: check if header is given twice?
        req->headers_.push_back(std::pair<string,string>(headerKey, headerValue));
    }

    req->raw_request_ = raw_request;

    return req;
}

string Request::raw_request() const {
    return raw_request_;
}
string Request::method() const {
    return method_;
}
string Request::uri() const {
    return uri_;
}
string Request::version() const {
    return body_;
}
Headers Request::headers() const {
    return headers_;
}
string Request::body() const {
    return body_;
}
