#pragma once

#include "request_handler.h"
#include "request_handler.h"
#include "sync_client.h"

#include <mutex>

class ProxyHandler : public RequestHandler {
    public:
        ProxyHandler()
        {
            client_ = std::unique_ptr<SyncClient>(new SyncClient());
            redirect_ = false;
        }

        virtual Status Init(const std::string& uri_prefix,
                const NginxConfig& config);

        virtual Status HandleRequest(const Request& request,
                Response* response);

        virtual std::string type() const {
            return "ProxyHandler";
        }

        Response ParseRawResponse(const std::string& response);
    private:

        std::unique_ptr<SyncClient> client_;

        std::string uri_prefix_;

        // leave remote port as a string b/c boost needs it in that form anyway
        std::string remote_host_, remote_port_;

        std::string redirect_host_, redirect_host_header_, redirect_uri_;

        bool redirect_;

        std::mutex mtx_;
};

REGISTER_REQUEST_HANDLER(ProxyHandler);
