Poco::Net::HTTPServerRequest::ConstIterator it = _request.begin();
for(; it != _request.end(); it++) {
    GString lKey = it->first;
    GString lValue = it->second;
    GFORMAT("%s: %s", lKey.c_str(), lValue.c_str()).print();
}
