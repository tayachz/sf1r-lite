#ifndef _LOG_SERVER_CONNECTION_H_
#define _LOG_SERVER_CONNECTION_H_

#include "LogServerRequest.h"
#include "LogManagerSingleton.h"

#include <3rdparty/msgpack/rpc/client.h>

namespace sf1r
{

class LogServerConnection : public LogManagerSingleton<LogServerConnection>
{
public:
    LogServerConnection();

    ~LogServerConnection();

    bool init(const std::string& host, uint16_t port);

    template <typename RequestDataT>
    void asynRequest(const LogServerRequest::method_t& method, const RequestDataT& reqData);

    template <typename RequestT>
    void asynRequest(const RequestT& req);

    void flushRequests();

private:
    bool bInited_;
    std::string host_;
    uint16_t port_;
    boost::shared_ptr<msgpack::rpc::client> client_;
};

template <typename RequestDataT>
void LogServerConnection::asynRequest(const LogServerRequest::method_t& method, const RequestDataT& reqData)
{
    static unsigned int count = 0;
    //client_->call(method, reqData);
    client_->notify(method, reqData);
    if (++count == 1000)
    {
        flushRequests();
        count = 0;
    }
}

template <typename RequestT>
void LogServerConnection::asynRequest(const RequestT& req)
{
    asynRequest(req.method_names[req.method_], req.param_);
}

}

#endif /* _LOG_SERVER_CONNECTION_H_ */
