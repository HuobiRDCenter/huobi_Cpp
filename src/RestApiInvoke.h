#ifndef RESTAPIINVOKE_H
#define RESTAPIINVOKE_H
#include <memory>
#include <curl/curl.h>
#include "RestApi.h"
#include "Utils/JsonDocument.h"
#include "EtfResult.h"
#include "Huobi/HuobiApiException.h"
#include "Utils/Singleton.h"

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/error.hpp>
#include <boost/asio/ssl/stream.hpp>



namespace Huobi {

    class RestApiInvoke : public Singleton<RestApiInvoke> {
    private:
        boost::asio::ssl::context ctx_;
    protected:
        friend class Singleton<RestApiInvoke>;
        
        RestApiInvoke() : ctx_(boost::asio::ssl::context::sslv23_client)
        {
            ctx_.set_verify_mode(boost::asio::ssl::verify_peer);
            ctx_.load_verify_file("/etc/huobi_cert/cert.pem");
        }
        
    private:
        template <typename T>
        T callSync_Boost(RestApi<T>* request) {
            static boost::beast::flat_buffer buffer;
            
            std::unique_ptr<RestApi < T >> ptr(request);
            // The io_context is required for all I/O
            boost::asio::io_context ioc;
            boost::asio::ip::tcp::resolver resolver(ioc);
            boost::beast::ssl_stream<boost::beast::tcp_stream> stream(ioc, ctx_);
            
            // Set SNI Hostname (many hosts need this to handshake successfully)
            if(! SSL_set_tlsext_host_name(stream.native_handle(), ptr->host.c_str()))
            {
                boost::beast::error_code ec{static_cast<int>(::ERR_get_error()), boost::asio::error::get_ssl_category()};
                throw boost::beast::system_error{ec};
            }
            auto const results = resolver.resolve(ptr->tagret.c_str(), 443);
            
            auto tcp = boost::beast::get_lowest_layer(stream);
            tcp.expires_after(std::chrono::seconds(20));
            tcp.connect(results);
            //tcp.expires_after();
            stream.handshake(boost::asio::ssl::stream_base::client);
           
            if (ptr->method == "POST") {
                 boost::beast::http::request<boost::beast::http::string_body> req{boost::beast::http::verb::post, ptr->tagret.c_str(), 11};
                 req.set(boost::beast::http::field::host, ptr->host.c_str());
                 req.set(boost::beast::http::field::content_type, "application/json;charset=UTF-8");
                 req.set(boost::beast::http::field::body, ptr->postbody);
                 boost::beast::http::write(stream, req);
            } else {
                 boost::beast::http::request<boost::beast::http::string_body> req{boost::beast::http::verb::get, ptr->tagret.c_str(), 11};
                 req.set(boost::beast::http::field::host, ptr->host.c_str());
                 req.set(boost::beast::http::field::content_type, "application/x-www-form-urlencoded");
                 boost::beast::http::write(stream, req);
            }
            std::cout<< "-- Send request Done" <<std::endl;
            boost::beast::http::response<boost::beast::http::string_body> res;
            buffer.clear();
            // Receive the HTTP response
            boost::beast::http::read(stream, buffer, res);
            std::cout<< "-- Get response" <<std::endl;
            // Write the message to standard out
            std::cout << res.body().c_str() << std::endl;
            
            try {
                stream.shutdown();
            }
            catch(std::exception const& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
            
            JsonDocument djson;
            JsonWrapper json = djson.parseFromString(res.body().c_str());
            RestApiInvoke::checkResponse(json);

            T val = (ptr->jsonParser)(json);

            return val;
        }
    public:
        static void checkResponse(const JsonWrapper& json) {
            try {
                if (json.containKey("status")) {
                    std::string status = json.getString("status");
                    if ("error" == status) {
                        std::string err_code = json.getString("err-code");
                        std::string err_msg = json.getString("err-msg");
                        throw HuobiApiException(HuobiApiException::EXEC_ERROR,
                                "[Executing] " + err_code + ": " + err_msg);
                    } else if ("ok" != status) {
                        throw HuobiApiException(
                                HuobiApiException::RUNTIME_ERROR, "[Invoking] Response is not expected: " + status);
                    }
                } else if (json.containKey("success")) {
                    bool success = json.getBool("success");
                    if (!success) {
                        std::string err_code = EtfResult::checkResult(json.getInt("code"));
                        std::string err_msg = json.getString("message");
                        if (err_code.empty()) {
                            throw HuobiApiException(HuobiApiException::EXEC_ERROR, "[Executing] " + err_msg);
                        } else {
                            throw HuobiApiException(HuobiApiException::EXEC_ERROR,
                                    "[Executing] " + err_code + ": " + err_msg);
                        }
                    }
                } else {
                    throw HuobiApiException(
                            HuobiApiException::RUNTIME_ERROR, "[Invoking] Status cannot be found in response.");
                }
            } catch (std::exception e) {
                std::string msg;
                msg = "[Invoking] Unexpected error: ";
                throw HuobiApiException(
                        HuobiApiException::RUNTIME_ERROR, msg + e.what());
            }
        }

        static size_t writeFun(void *input, size_t uSize, size_t uCount, void *avg) {
            size_t uLen = uSize*uCount;
            std::string &sBuffer = *reinterpret_cast<std::string *> (avg);
            sBuffer.append(reinterpret_cast<const char *> (input), uLen);
            return uLen;
        }

        template <typename T>
        static T callSync(RestApi<T>* request) {
                    // The io_context is required for all I/O
            
            std::unique_ptr<RestApi < T >> ptr(request);
            CURLcode code = curl_global_init(CURL_GLOBAL_DEFAULT);
            if (code != CURLE_OK) {
                std::cout << "curl_global_init() Err" << std::endl;
                throw HuobiApiException("", "curl_global_init() Err");
            }
            CURL* pCurl = curl_easy_init();
            if (pCurl == NULL) {
                std::cout << "curl_easy_init() Err" << std::endl;
                throw HuobiApiException("", "curl_easy_init() Err");
            }
            std::string sBuffer;
            printf("\n");
            printf("------request------\n");
            printf(ptr->tagret.c_str());
            printf("\n");
            curl_easy_setopt(pCurl, CURLOPT_SSLKEYTYPE, "PEM");
            curl_easy_setopt(pCurl, CURLOPT_SSL_VERIFYPEER, 1L);
            curl_easy_setopt(pCurl, CURLOPT_SSL_VERIFYHOST, 1L);
            curl_easy_setopt(pCurl, CURLOPT_URL, request->tagret.c_str()); // 访问的URL
            curl_easy_setopt(pCurl, CURLOPT_CAINFO, "/etc/huobi_cert/cert.pem");
            if (ptr->method == "POST") {
                curl_easy_setopt(pCurl, CURLOPT_POST, 1);
                curl_slist *plist = curl_slist_append(NULL, "Content-Type:application/json;charset=UTF-8");
                curl_easy_setopt(pCurl, CURLOPT_HTTPHEADER, plist);
            } else {
                curl_slist *plist = curl_slist_append(NULL, "Content-Type:application/x-www-form-urlencoded");
                curl_easy_setopt(pCurl, CURLOPT_HTTPHEADER, plist);
            }
            curl_easy_setopt(pCurl, CURLOPT_TIMEOUT, 20); // 超时(单位S)
            curl_easy_setopt(pCurl, CURLOPT_WRITEFUNCTION, &writeFun); // !数据回调函数
            curl_easy_setopt(pCurl, CURLOPT_WRITEDATA, &sBuffer); // !数据回调函数的参，一般为Buffer或文件fd
            if (request->method == "POST") {
                //TODO: body需要转成utf-8
                curl_easy_setopt(pCurl, CURLOPT_POSTFIELDS, request->postbody.c_str());
            }
            curl_easy_perform(pCurl);
            if (code != CURLE_OK) {
                std::cout << "curl_easy_perform() Err" << std::endl;
                throw HuobiApiException("", "curl_easy_perform() Err");
            }
            printf("------response------\n");
            printf(sBuffer.c_str());
            printf("\n");
            JsonDocument djson;
            JsonWrapper json = djson.parseFromString(sBuffer.c_str());

            curl_easy_cleanup(pCurl);
            curl_global_cleanup();

            RestApiInvoke::checkResponse(json);

            T val = (ptr->jsonParser)(json);

            return val;
        }
    };
}

#endif /* RESTAPIINVOKE_H */

