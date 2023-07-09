//===============================================
#include "GHttp.h"
//===============================================
#define GHTTP_STATUS(code, name) {code, name}
//===============================================
GHttp::sGStatus GHTTP_STATUS_MAP[] {
    GHTTP_STATUS(GHttp::eGStatus::Continue, "Continue")
    , GHTTP_STATUS(GHttp::eGStatus::SwitchingProtocol, "SwitchingProtocol")
    , GHTTP_STATUS(GHttp::eGStatus::Processing, "Processing")
    , GHTTP_STATUS(GHttp::eGStatus::EarlyHints, "EarlyHints")

    , GHTTP_STATUS(GHttp::eGStatus::Ok, "Ok")
    , GHTTP_STATUS(GHttp::eGStatus::Created, "Created")
    , GHTTP_STATUS(GHttp::eGStatus::Accepted, "Accepted")
    , GHTTP_STATUS(GHttp::eGStatus::NonAuthoritativeInformation, "NonAuthoritativeInformation")
    , GHTTP_STATUS(GHttp::eGStatus::NoContent, "NoContent")
    , GHTTP_STATUS(GHttp::eGStatus::ResetContent, "ResetContent")
    , GHTTP_STATUS(GHttp::eGStatus::PartialContent, "PartialContent")
    , GHTTP_STATUS(GHttp::eGStatus::MultiStatus, "MultiStatus")
    , GHTTP_STATUS(GHttp::eGStatus::AlreadyReported, "AlreadyReported")
    , GHTTP_STATUS(GHttp::eGStatus::ImUsed, "ImUsed")

    , GHTTP_STATUS(GHttp::eGStatus::MultipleChoice, "MultipleChoice")
    , GHTTP_STATUS(GHttp::eGStatus::MovedPermanently, "MovedPermanently")
    , GHTTP_STATUS(GHttp::eGStatus::Found, "Found")
    , GHTTP_STATUS(GHttp::eGStatus::SeeOther, "SeeOther")
    , GHTTP_STATUS(GHttp::eGStatus::NotModified, "NotModified")
    , GHTTP_STATUS(GHttp::eGStatus::UseProxy, "UseProxy")
    , GHTTP_STATUS(GHttp::eGStatus::TemporaryRedirect, "TemporaryRedirect")
    , GHTTP_STATUS(GHttp::eGStatus::PermanentRedirect, "PermanentRedirect")

    , GHTTP_STATUS(GHttp::eGStatus::BadRequest, "BadRequest")
    , GHTTP_STATUS(GHttp::eGStatus::Unauthorized, "Unauthorized")
    , GHTTP_STATUS(GHttp::eGStatus::PaymentRequired, "PaymentRequired")
    , GHTTP_STATUS(GHttp::eGStatus::Forbidden, "Forbidden")
    , GHTTP_STATUS(GHttp::eGStatus::NotFound, "NotFound")
    , GHTTP_STATUS(GHttp::eGStatus::MethodNotAllowed, "MethodNotAllowed")
    , GHTTP_STATUS(GHttp::eGStatus::NotAcceptable, "NotAcceptable")
    , GHTTP_STATUS(GHttp::eGStatus::ProxyAuthenticationRequired, "ProxyAuthenticationRequired")
    , GHTTP_STATUS(GHttp::eGStatus::RequestTimeout, "RequestTimeout")
    , GHTTP_STATUS(GHttp::eGStatus::Conflict, "Conflict")
    , GHTTP_STATUS(GHttp::eGStatus::Gone, "Gone")
    , GHTTP_STATUS(GHttp::eGStatus::LengthRequired, "LengthRequired")
    , GHTTP_STATUS(GHttp::eGStatus::PreconditionFailed, "PreconditionFailed")
    , GHTTP_STATUS(GHttp::eGStatus::PayloadTooLarge, "PayloadTooLarge")
    , GHTTP_STATUS(GHttp::eGStatus::UriTooLong, "UriTooLong")
    , GHTTP_STATUS(GHttp::eGStatus::UnsupportedMediaType, "UnsupportedMediaType")
    , GHTTP_STATUS(GHttp::eGStatus::RangeNotSatisfiable, "RangeNotSatisfiable")
    , GHTTP_STATUS(GHttp::eGStatus::ExpectationFailed, "ExpectationFailed")
    , GHTTP_STATUS(GHttp::eGStatus::MisdirectedRequest, "MisdirectedRequest")
    , GHTTP_STATUS(GHttp::eGStatus::UnprocessableEntity, "UnprocessableEntity")
    , GHTTP_STATUS(GHttp::eGStatus::Locked, "Locked")
    , GHTTP_STATUS(GHttp::eGStatus::FailedDependency, "FailedDependency")
    , GHTTP_STATUS(GHttp::eGStatus::TooEarly, "TooEarly")
    , GHTTP_STATUS(GHttp::eGStatus::UpgradeRequired, "UpgradeRequired")
    , GHTTP_STATUS(GHttp::eGStatus::PreconditionRequired, "PreconditionRequired")
    , GHTTP_STATUS(GHttp::eGStatus::TooManyRequests, "TooManyRequests")
    , GHTTP_STATUS(GHttp::eGStatus::RequestHeaderFieldsTooLarge, "RequestHeaderFieldsTooLarge")
    , GHTTP_STATUS(GHttp::eGStatus::UnavailableForLegalReasons, "UnavailableForLegalReasons")

    , GHTTP_STATUS(GHttp::eGStatus::InternalServerError, "InternalServerError")
    , GHTTP_STATUS(GHttp::eGStatus::NotImplemented, "NotImplemented")
    , GHTTP_STATUS(GHttp::eGStatus::BadGateway, "BadGateway")
    , GHTTP_STATUS(GHttp::eGStatus::ServiceUnavailable, "ServiceUnavailable")
    , GHTTP_STATUS(GHttp::eGStatus::GatewayTimeout, "GatewayTimeout")
    , GHTTP_STATUS(GHttp::eGStatus::HttpVersionNotSupported, "HttpVersionNotSupported")
    , GHTTP_STATUS(GHttp::eGStatus::VariantAlsoNegotiates, "VariantAlsoNegotiates")
    , GHTTP_STATUS(GHttp::eGStatus::InsufficientStorage, "InsufficientStorage")
    , GHTTP_STATUS(GHttp::eGStatus::LoopDetected, "LoopDetected")
    , GHTTP_STATUS(GHttp::eGStatus::NotExtended, "NotExtended")
    , GHTTP_STATUS(GHttp::eGStatus::NetworkAuthenticationRequired, "NetworkAuthenticationRequired")

    , GHTTP_STATUS(GHttp::eGStatus::eLast, "")
};
//===============================================
GHttp::GHttp()
: GObject() {
    m_status = eGStatus::BadRequest;
}
//===============================================
GHttp::~GHttp() {

}
//===============================================
void GHttp::setStatus(const eGStatus& _status) {
    m_status = _status;
}
//===============================================
void GHttp::setData(const GString& _data) {
    m_data = _data;
}
//===============================================
GString GHttp::toReason(eGStatus _status) {
    int i = 0;
    while(1) {
        sGStatus lStatus = GHTTP_STATUS_MAP[i++];
        if(lStatus.code == eGStatus::eLast) break;
        if(lStatus.code == _status) return lStatus.name;
    }
    m_logs.addError("Le code du status n'a pas été trouvé.");
    return "Unknown";
}
//===============================================
GString GHttp::toResponse() {
    GString lData = "";
    lData += sformat("HTTP/1.1 %d %s\r\n", m_status, toReason(m_status).c_str());
    lData += sformat("Content-Length: %d\r\n", m_data.size());
    lData += sformat("\r\n");
    lData += sformat("%s", m_data.c_str());
    return lData;
}
//===============================================
