#pragma once
#include "request_handler.h"

class NotFoundHandler : public RequestHandler {
    public:
        virtual Status Init(const std::string& uri_prefix,
                const NginxConfig& config);

        virtual Status HandleRequest(const Request& request,
                Response* response);

        virtual ~NotFoundHandler() = default;

        virtual std::string type() const {
            return "NotFoundHandler";
        }
};

REGISTER_REQUEST_HANDLER(NotFoundHandler);
