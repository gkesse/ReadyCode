//===============================================
#include "GPoco.h"
#include "GLog.h"
#include "GFormat.h"
//===============================================
GPoco::GPoco() : GObject() {

}
//===============================================
GPoco::~GPoco() {

}
//===============================================
void GPoco::configMail() {
    GSSLInitializer sslInitializer;

    std::string mailhost;
    std::string sender;
    std::string recipient;
    std::string username;
    std::string password;

    try
    {
        Poco::SharedPtr<Poco::Net::InvalidCertificateHandler> pCert = new Poco::Net::ConsoleCertificateHandler(false); // ask the user via console
        Poco::Net::Context::Ptr pContext = new Poco::Net::Context(Poco::Net::Context::CLIENT_USE, "", "", "", Poco::Net::Context::VERIFY_RELAXED, 9, true, "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH");
        Poco::Net::SSLManager::instance().initializeClient(0, pCert, pContext);

        Poco::Net::MailMessage lMailMessage;
        lMailMessage.setSender(sender);
        lMailMessage.addRecipient(Poco::Net::MailRecipient(Poco::Net::MailRecipient::PRIMARY_RECIPIENT, recipient));
        lMailMessage.setSubject("Hello from the POCO C++ Libraries");
        std::string content;
        content += "Hello ";
        content += recipient;
        content += ",\r\n\r\n";
        content += "This is a greeting from the POCO C++ Libraries.\r\n\r\n";
        std::string logo;
        lMailMessage.addContent(new Poco::Net::StringPartSource(content));
        lMailMessage.addAttachment("logo", new Poco::Net::StringPartSource(logo, "image/gif"));

        Poco::Net::SecureSMTPClientSession lSession(mailhost);
        lSession.login();
        lSession.startTLS(pContext);
        if (!username.empty()) {
            lSession.login(Poco::Net::SMTPClientSession::AUTH_LOGIN, username, password);
        }
        lSession.sendMessage(lMailMessage);
        lSession.close();
    }
    catch (Poco::Exception& e) {
        GERROR_ADD(eGERR, "Erreur lors de l'envoi de l'email.\n"
                "error........: (%s)\n"
                "", e.displayText().c_str()
        );
    }
}
//===============================================
