m_host = _request.getHost();
m_method = _request.getMethod();
m_uri = _request.getURI();
m_version = _request.getVersion();
GFORMAT("%s %s %s", m_method.c_str(), m_uri.c_str(), m_version.c_str()).print();
