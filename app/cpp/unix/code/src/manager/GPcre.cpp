//===============================================
#include "GPcre.h"
//===============================================
GPcre::GPcre()
: GObject() {

}
//===============================================
GPcre::~GPcre() {

}
//===============================================
GObject* GPcre::clone() const {
    GObject* lObj = new GPcre;
    return lObj;
}
//===============================================
void GPcre::setObj(const GObject& _obj) {
    const GPcre& lObj = dynamic_cast<const GPcre&>(_obj);
    setObj(lObj);
}
//===============================================
void GPcre::setObj(const GPcre& _obj) {
    m_dataOut = _obj.m_dataOut;
}
//===============================================
void GPcre::setDataIn(const GString& _dataIn) {
    m_dataIn = _dataIn;
}
//===============================================
void GPcre::setPattern(const GString& _pattern) {
    m_pattern = _pattern;
}
//===============================================
GString GPcre::serialize(const GString& _code) {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "data_out", m_dataOut, true);
    lDom.addData(_code, m_map);
    return lDom.toString();

}
//===============================================
void GPcre::deserialize(const GString& _data, const GString& _code) {
    GCode lDom;
    lDom.loadXml(_data);
    m_dataOut = lDom.getData(_code, "data_out");
    lDom.getData(_code, m_map, *this);
}
//===============================================
bool GPcre::run() {
    pcre* lPcre;
    const char* lPattern;
    const char* lErrorMsg;
    int lErrorOffset;
    int lBuffers[PCRE_BUFFER_SIZE];

    lPcre = pcre_compile(
            m_pattern.c_str()   /* the pattern */
            , PCRE_MULTILINE    /* default options */
            , &lErrorMsg        /* for error message */
            , &lErrorOffset     /* for error offset */
            , NULL              /* use default character tables */
    );

    if(!lPcre) {
        m_logs.addError("L'expression n'a pas été initialisé.");
        return false;
    }

    int lOffset = 0;

    while(1) {
        if(lOffset >= m_dataIn.size()) break;
        int lReturn = pcre_exec(
                lPcre               /* the compiled pattern */
                , 0                 /* no extra data - we didn't study the pattern */
                , m_dataIn.c_str()  /* the subject string */
                , m_dataIn.size()   /* the length of the subject */
                , lOffset           /* start at offset 0 in the subject */
                , 0                 /* default options */
                , lBuffers          /* output vector for substring information */
                , PCRE_BUFFER_SIZE  /* number of elements in the output vector */
        );

        if(lReturn < 0)
        {
            if(lReturn != PCRE_ERROR_NOMATCH) {
                m_logs.addError("L'exécution de l'expression a échoué.");
            }
            break;
        }

        for(int i = 0; i < lReturn; ++i) {
            m_dataOut = GFORMAT("%.*s", lBuffers[2*i+1] - lBuffers[2*i], m_dataIn.data() + lBuffers[2*i]);
            addToMap(*this);
        }

        lOffset = lBuffers[1];
    }

    pcre_free(lPcre);
    return !m_logs.hasErrors();
}
//===============================================
