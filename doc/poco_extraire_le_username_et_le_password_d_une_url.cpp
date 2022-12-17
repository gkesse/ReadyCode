bool GPoco::extractCredentials(const GString& _url) {
    Poco::URI lUri(_url.c_str());
    std::string lUsername;
    std::string lPassword;
    Poco::Net::HTTPCredentials::extractCredentials(lUri, lUsername, lPassword);
    return true;
}
