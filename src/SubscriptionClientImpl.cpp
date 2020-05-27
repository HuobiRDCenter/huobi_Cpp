#include <sstream>
#include "SubscriptionClientImpl.h"
#include "WebSocketConnection.h"
#include "InputChecker.h"

namespace Huobi {

    static int event_cb(
            struct lws* wsi,
            enum lws_callback_reasons reason,
            void* user,
            void* in,
            size_t len) {
        static int i = 10;
        WebSocketConnection* connection = reinterpret_cast<WebSocketConnection*> (user);

        switch (reason) {

            case LWS_CALLBACK_CLIENT_ESTABLISHED:
                connection->onOpen(wsi);
                break;
            case LWS_CALLBACK_CLIENT_WRITEABLE:
            {
                bool flag = connection->flushSendBuffer(wsi);
                if (!flag) {
                    //lws_cancel_service_pt(wsi);
                    return 1;
                }
                break;
            }
            case LWS_CALLBACK_CLIENT_RECEIVE:
            {
                // lwsl_user("receive");
                //                char buf[4096 * 100] = {0};
                //                unsigned int l = 4096 * 100;
                //                l = gzDecompress((char*) in, len, buf, l);
                //lwsl_user("RX %d: %s\n", l, (const char *) buf);
                // connection->onMessage(buf);
                connection->onMessage((char*) in, len);
                break;
            }
            case LWS_CALLBACK_CLIENT_CLOSED:

                //connection->close();
                lwsl_user("afer canceled.....\n");
                connection->disconnect();

                return -1;
                //case LWS_CALLBACK_WSI_DESTROY:
            case LWS_CALLBACK_CLIENT_CONNECTION_ERROR:
                connection->disconnect();
                lwsl_user("closed... \n");
                return 1;
            default:
                lwsl_notice("notice %d\n", reason);
                break;
        }

        return 0;
    }

    static const struct lws_protocols protocols[] = {
        {
            "example-protocol",
            event_cb,
            0,
            4096 * 100
        },
        { NULL, NULL, 0, 0}
    };

    void SubscriptionClientImpl::init_context() {
        if (context == nullptr) {

            int logs = LLL_ERR | LLL_WARN ;

            lws_set_log_level(logs, NULL);
            struct lws_context_creation_info info;
            memset(&info, 0, sizeof (info));
            info.port = CONTEXT_PORT_NO_LISTEN;
            info.protocols = protocols;
            info.gid = -1;
            info.uid = -1;
            info.options |= LWS_SERVER_OPTION_DO_SSL_GLOBAL_INIT;
            info.client_ssl_ca_filepath = "/etc/huobi_cert/cert.pem";
            context = lws_create_context(&info);
        }
    }

    void SubscriptionClientImpl::startService() {

        std::list<WebSocketConnection*>::iterator it = connectionList.begin();
        for (; it != connectionList.end(); ++it) {
            (*it)->connect(context);
        }
        lwsl_user("enter_event_loop\n");
        while (1) {
            try {
                lws_service(context, 100);
            } catch (...) {
                break;
            }
        }

        lwsl_user("enter_event_loop END\n");
        lws_context_destroy(context);
    }

    void SubscriptionClientImpl::startReq(WebSocketRequest* request) {

        std::list<WebSocketConnection*>::iterator it = connectionList.begin();
        for (; it != connectionList.end(); ++it) {
            (*it)->connect(context);
        }
        lwsl_user("enter_event_loop\n");

        while (!request->autoClose || request->time) {
            try {
                lws_service(context, 100);

            } catch (...) {
                break;
            }
        }
        lwsl_user("enter_event_loop END\n");
        lws_context_destroy(context);

    }

    void SubscriptionClientImpl::createConnection(WebSocketRequest* request) {
        if (dog == nullptr) {

            dog = new WebSocketWatchDog(op);
        }
        init_context();
        WebSocketConnection* connection = new WebSocketConnection(
                this->apiKey, this->secretKey, request, dog, host);
        connectionList.push_back(connection);
    }

    std::list<std::string> SubscriptionClientImpl::parseSymbols(const char* symbols) {

        std::string input(symbols);
        std::list<std::string> res;
        std::stringstream ss(input);
        std::string temp;
        while (std::getline(ss, temp, ',')) {
            InputChecker::checker()->checkSymbol(temp);
            res.push_back(temp);
        }
        return res;
    }

    void SubscriptionClientImpl::subscribeCandlestickEvent(
            const char* symbols,
            CandlestickInterval interval,
            const std::function<void(const CandlestickEvent&) >& callback,
            const std::function<void(HuobiApiException&)>& errorHandler) {
        createConnection(impl->subscribeCandlestickEvent(parseSymbols(symbols), interval, callback, errorHandler));
    }

    void SubscriptionClientImpl::subscribeTradeEvent(
            const char* symbols,
            const std::function<void(const TradeEvent&) >& callback,
            const std::function<void(HuobiApiException&)>& errorHandler) {
        createConnection(impl->subscribeTradeEvent(parseSymbols(symbols), callback, errorHandler));
    }

    void SubscriptionClientImpl::subscribePriceDepthEvent(
            const char* symbols,
            const std::function<void(const PriceDepthEvent&) >& callback,
            const std::function<void(HuobiApiException&)>& errorHandler) {
        //        createConnection(impl->subscribePriceDepthEvent(parseSymbols(symbols), callback, errorHandler));
        subscribePriceDepthEvent(symbols, DepthStep::step0, callback, errorHandler);
    }

    void SubscriptionClientImpl::subscribe24HTradeStatisticsEvent(
            const char* symbols,
            const std::function<void(const TradeStatisticsEvent&) >& callback,
            const std::function<void(HuobiApiException&)>& errorHandler) {
        createConnection(impl->subscribe24HTradeStatisticsEvent(parseSymbols(symbols), callback, errorHandler));
    }

    void SubscriptionClientImpl::subscribeOrderUpdateEvent(
            const char* symbols,
            const std::function<void(const OrderUpdateEvent&) >& callback,
            const std::function<void(HuobiApiException&)>& errorHandler) {
        createConnection(impl->subscribeOrderUpdateEvent(parseSymbols(symbols), callback, errorHandler));
    }

    void SubscriptionClientImpl::subscribeAccountEvent(
            const BalanceMode& mode,
            const std::function<void(const AccountEvent&) >& callback,
            const std::function<void(HuobiApiException&)>& errorHandler) {
        createConnection(impl->subscribeAccountEvent(mode, callback, errorHandler));
    }

    void SubscriptionClientImpl::subscribeOrderUpdateNewEvent(
            const char* symbols,
            const std::function<void(const OrderUpdateEvent&) >& callback,
            const std::function<void(HuobiApiException&)>& errorHandler) {
        createConnection(impl->subscribeOrderUpdateNewEvent(parseSymbols(symbols), callback, errorHandler));
    }

    void SubscriptionClientImpl::subscribePriceDepthEvent(
            const char* symbols,
            DepthStep step,
            const std::function<void(const PriceDepthEvent&) >& callback,
            const std::function<void(HuobiApiException&)>& errorHandler) {
        createConnection(impl->subscribePriceDepthEvent(parseSymbols(symbols), step, callback, errorHandler));
    }

    void SubscriptionClientImpl::subscribeMarketBBOEvent(
            const char* symbols,
            const std::function<void(const MarketBBOEvent&) >& callback,
            const std::function<void(HuobiApiException&)>& errorHandler) {
        createConnection(impl->subscribeMarketBBOEvent(parseSymbols(symbols), callback, errorHandler));

    }

    void SubscriptionClientImpl::subscribeMarketDepthMBP(
            const char* symbols,
            MBPLevel level,
            const std::function<void(const MarketDepthMBPEvent&) >& callback,
            const std::function<void(HuobiApiException&)>& errorHandler) {
        createConnection(impl->subscribeMarketDepthMBP(parseSymbols(symbols), level, callback, errorHandler));
    }

    void SubscriptionClientImpl::subscribeTradeClearingEvent(
            const char* symbols,
            const std::function<void(const TradeClearingEvent&) >& callback,
            const std::function<void(HuobiApiException&)>& errorHandler) {
        createConnection(impl->subscribeTradeClearingEvent(parseSymbols(symbols), callback, errorHandler));
    }

    void SubscriptionClientImpl::subscribeAccountUpdateEvent(
            const AccountsUpdateMode& mode,
            const std::function<void(const AccountUpdateEvent&) >& callback,
            const std::function<void(HuobiApiException&)>& errorHandler) {
        createConnection(impl->subscribeAccountUpdateEvent(mode, callback, errorHandler));
    }

    void SubscriptionClientImpl::subscribeMarketDepthMBPrefresh(
            const char* symbols,
            MBPLevel level,
            const std::function<void(const MarketDepthMBPEvent&) >& callback,
            const std::function<void(HuobiApiException&)>& errorHandler) {
        createConnection(impl->subscribeMarketDepthMBPrefresh(parseSymbols(symbols), level, callback, errorHandler));
    }

    void SubscriptionClientImpl::subscribeOrderUpdateV2(
            const char* symbol,
            const std::function<void(const OrderUpdateV2Event&) >& callback,
            const std::function<void(HuobiApiException&)>& errorHandler) {
        createConnection(impl->subscribeOrderUpdateV2(parseSymbols(symbol), callback, errorHandler));
    }

    WebSocketRequest* SubscriptionClientImpl::requestCandlestickEvent(
            bool autoClose,
            const char* symbols,
            CandlestickInterval interval,
            long startTime,
            long endTime,
            const std::function<void(const std::vector<CandlestickEvent>&) >& callback,
            const std::function<void(HuobiApiException&)>& errorHandler) {
        WebSocketRequest* req = impl->requestCandlestickEvent(autoClose, parseSymbols(symbols), interval, startTime, endTime, callback, errorHandler);
        createConnection(req);
        return req;

    }

    WebSocketRequest* SubscriptionClientImpl::requestPriceDepthEvent(
            bool autoClose,
            const char* symbols,
            DepthStep step,
            const std::function<void(const PriceDepthEvent&) >& callback,
            const std::function<void(HuobiApiException&)>& errorHandler) {
        WebSocketRequest* req = impl->requestPriceDepthEvent(autoClose, parseSymbols(symbols), step, callback, errorHandler);
        createConnection(req);
        return req;

    }

    WebSocketRequest* SubscriptionClientImpl::requestTradeEvent(
            bool autoClose,
            const char* symbols,
            const std::function<void(const TradeEvent&) >& callback,
            const std::function<void(HuobiApiException&)>& errorHandler) {
        WebSocketRequest* req = impl->requestTradeEvent(autoClose, parseSymbols(symbols), callback, errorHandler);
        createConnection(req);
        return req;
    }

    WebSocketRequest* SubscriptionClientImpl::request24HTradeStatisticsEvent(
            bool autoClose,
            const char* symbols,
            const std::function<void(const TradeStatisticsEvent&) >& callback,
            const std::function<void(HuobiApiException&)>& errorHandler) {
        WebSocketRequest* req = impl->request24HTradeStatistics(autoClose, parseSymbols(symbols), callback, errorHandler);
        createConnection(req);
        return req;
    }

    WebSocketRequest* SubscriptionClientImpl::requestAccountList(
            bool autoClose,
            const std::function<void(const AccountListEvent&) >& callback,
            const std::function<void(HuobiApiException&)>& errorHandler) {
        WebSocketRequest* req = impl->requestAccountList(autoClose, callback, errorHandler);
        createConnection(req);
        return req;
    }

    WebSocketRequest* SubscriptionClientImpl::requestOrdertListEvent(
            bool autoClose,
            OrderListEventRequest req,
            const std::function<void(const OrderListEvent&) >& callback,
            const std::function<void(HuobiApiException&)>& errorHandler) {
        WebSocketRequest* request = impl->requestOrdertListEvent(
                autoClose,
                req.accountId,
                parseSymbols(req.symbols),
                req.types,
                req.states,
                req.startTime,
                req.endTime,
                req.fromId,
                req.direction,
                req.size,
                callback,
                errorHandler);
        createConnection(request);
        return request;

    }

    WebSocketRequest* SubscriptionClientImpl::requestOrdertDetailEvent(
            bool autoClose,
            long orderId,
            const std::function<void(const OrderDetailEvent&) >& callback,
            const std::function<void(HuobiApiException&)>& errorHandler) {
        WebSocketRequest* req = impl->requestOrdertDetailEvent(autoClose, orderId, callback, errorHandler);
        createConnection(req);
        return req;
    }

    WebSocketRequest * SubscriptionClientImpl::requestMarketDepthMBPEvent(
            bool autoClose,
            const char* symbols,
            MBPLevel level,
            const std::function<void(const MarketDepthMBPEvent&) >& callback,
            const std::function<void(HuobiApiException&)>& errorHandler) {
        WebSocketRequest* req = impl->requestMarketDepthMBPEvent(autoClose, parseSymbols(symbols), level, callback, errorHandler);
        createConnection(req);
        return req;
    }


}


