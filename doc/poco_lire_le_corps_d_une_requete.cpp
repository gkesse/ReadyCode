GString lContent;
if(_request.hasContentLength()) {
    std::istream& lInput = _request.stream();
    std::string lOutput;
    Poco::StreamCopier::copyToString(lInput, lOutput, _request.getContentLength());
    lContent = lOutput;
}
lContent.print();
