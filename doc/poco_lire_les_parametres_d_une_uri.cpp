const Poco::URI lUri(m_uri.c_str());
const Poco::URI::QueryParameters lParams = lUri.getQueryParameters();
for(int i = 0; i < (int)lParams.size(); i++) {
    GString lKey = lParams.at(i).first;
    GString lValue = lParams.at(i).second;
    GFORMAT("%s : %s", lKey.c_str(), lValue.c_str()).print();
}
