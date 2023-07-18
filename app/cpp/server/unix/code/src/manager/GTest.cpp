//===============================================
#include "GTest.h"
#include "GString.h"
#include "GLog.h"
#include "GXml.h"
#include "GCode.h"
#include "GSocket.h"
#include "GMySQL.h"
#include "GDateTime.h"
#include "GCurl.h"
#include "GEmail.h"
//===============================================
GTest::GTest()
: GObject() {

}
//===============================================
GTest::~GTest() {

}
//===============================================
void GTest::run(int _argc, char** _argv) {
    GString lMethod = "";
    if(_argc > 2) lMethod = _argv[2];

    if(lMethod == "") {
        m_logs.addError("La méthode est obligatoire.");
    }
    else if(lMethod == "string") {
        runString(_argc, _argv);
    }
    else if(lMethod == "log") {
        runLog(_argc, _argv);
    }
    else if(lMethod == "xml") {
        runXml(_argc, _argv);
    }
    else if(lMethod == "code") {
        runCode(_argc, _argv);
    }
    else if(lMethod == "socket_client") {
        runSocket(_argc, _argv);
    }
    else if(lMethod == "mysql") {
        runMySQL(_argc, _argv);
    }
    else if(lMethod == "datetime") {
        runDatetime(_argc, _argv);
    }
    else if(lMethod == "curl") {
        runCurl(_argc, _argv);
    }
    else if(lMethod == "email") {
        runEmail(_argc, _argv);
    }
    else {
        m_logs.addError("La méthode est inconnue.");
    }
}
//===============================================
void GTest::runString(int _argc, char** _argv) {
    printf("%s...\n", __FUNCTION__);

    // copie - affectation
    GString lData = "Bonjour tout le monde.";
    lData.print();
    lData = "Bonjour tout le monde (2).";
    lData.print();
}
//===============================================
void GTest::runLog(int _argc, char** _argv) {
    printf("%s...\n", __FUNCTION__);
    GLog lLog;
    GLog lLogC;

    // addError - addData - addLog - addLogs - serialize
    lLog.addError("Le serveur n'est pas disponible.");
    lLog.addData("La résolution de l'écran est :  1200 x 970.");
    lLog.addLog("Le chargement du module est terminé.");
    lLog.loadFromMap(2);
    lLog.serialize().print();
    m_logs.addLogs(lLog);

    // deserialize
    lLogC.deserialize(lLog.serialize());
    lLogC.serialize().print();
}
//===============================================
void GTest::runXml(int _argc, char** _argv) {
    printf("%s...\n", __FUNCTION__);
    GXml lDom;
    GXml lDomC;

    // createDoc - setNode - addObj - addData - toString
    lDom.createDoc();
    lDomC.setNode(lDom.addObj("datas"));
    lDomC.setNode(lDomC.addObj("data"));
    lDomC.addData("code", "logs");
    lDomC.addData("type", "error");
    lDomC.addData("side", "server_cpp");
    lDomC.addData("msg", "Le serveur n'est pas disponible.");
    lDom.toString().print();

    // getNode - toNode
    lDomC.setNode(lDom.getNode(lDom, sformat("/rdv/datas/data")));
    lDomC.toNode(lDom).print();

    // createNode
    lDom.createDoc();
    lDom.createNode(lDom, sformat("/rdv/datas/data"));
    lDomC.setNode(lDom.createNode(lDom, sformat("/rdv/datas/data")));
    lDomC.createNode(lDom, sformat("rdv/datas/data"));
    lDomC.createNode(lDom, sformat("rdv/datas/data"));
    lDom.toString().print();
}
//===============================================
void GTest::runCode(int _argc, char** _argv) {
    printf("%s...\n", __FUNCTION__);
    GCode lDom;

    // createDatas - createCode - addData
    lDom.createDoc();
    lDom.createDatas();
    lDom.createDatas();
    lDom.createCode("logs");
    lDom.createCode("logs");
    lDom.addData("logs", "type", "error");
    lDom.toString().print();
    lDom.addData("logs", "type", "log");
    lDom.toString().print();

    // createDatas - createCode - addData
    lDom.createDoc();
    lDom.addData("manager", "module", "logs");
    lDom.toString().print();
}
//===============================================
void GTest::runSocket(int _argc, char** _argv) {
    printf("%s...\n", __FUNCTION__);
    GSocket lClient;
    GLog lLog;

    // callFacade
    lLog.addError("Le serveur n'est pas disponible.");
    lLog.addData("La résolution de l'écran est :  1200 x 970.");
    lLog.addLog("Le chargement du module est terminé.");
    lLog.loadFromMap(2);
    GString lData = lClient.callFacade("logs", "save_logs", lLog.serialize());
    lData.print();
}
//===============================================
void GTest::runMySQL(int _argc, char** _argv) {
    printf("%s...\n", __FUNCTION__);
    GMySQL dbSQL;
    GString lData = dbSQL.readData(sformat(""
            " SELECT table_name "
            " FROM information_schema.tables "
            " WHERE table_schema = '%s' "
            "", dbSQL.toDatabase().c_str()
    ));
    m_logs.addLogs(dbSQL.getLogs());
    lData.print();
}
//===============================================
void GTest::runDatetime(int _argc, char** _argv) {
    printf("%s...\n", __FUNCTION__);

    // date courante
    {
        jed_utils::datetime dtTest = jed_utils::datetime();
        printf("date courante : %s\n", dtTest.to_shortdate_string().c_str());
        printf("date courante : %s\n", dtTest.to_string().c_str());
    }

    // constructeur
    printf("constructeur : %s\n", jed_utils::datetime(2016, 11, 25).to_string().c_str());
    printf("constructeur : %s\n", jed_utils::datetime(2016, 11, 25, 20, 12, 44).to_string().c_str());

    // PM
    {
        jed_utils::datetime dtTest = jed_utils::datetime(2016, 11, 25, 4, 12, 44, jed_utils::period::PM);
        printf("PM : %s\n", dtTest.to_string().c_str());
    }

    // ajouter 1 semaine (7 jours)
    {
        jed_utils::datetime dtTest(2016, 11, 25, 20, 12, 44);
        dtTest.add_days(7);
        printf("ajouter 1 semaine (7 jours) : %s\n", dtTest.to_string().c_str());
    }

    // soustraire 1 semaine (7 jours)
    {
        jed_utils::datetime dtTest(2016, 11, 25, 20, 12, 44);
        dtTest.add_days(-7);
        printf("soustraire 1 semaine (7 jours) : %s\n", dtTest.to_string().c_str());
    }

    // jour de la semaine
    {
        jed_utils::datetime dtTest(2016, 11, 25, 20, 12, 44);
        printf("jour de la semaine : %d\n", dtTest.get_weekday());
    }

    // formater
    {
        jed_utils::datetime dtTest(2016, 11, 25, 20, 12, 44);
        printf("formater : %s\n", dtTest.to_string("yyyy-MM-dd hh:mm:ss tt").c_str());
    }

    // parser
    {
        jed_utils::datetime dtTest = jed_utils::datetime::parse(std::string("yyyy/MM/dd HH:mm:ss"), std::string("2016-08-18 23:14:42"));
        printf("parse : %s\n", dtTest.to_string().c_str());
    }

    // temps écoulé
    {
        jed_utils::timespan ts(0, 1, 3, 15);
        printf("temps écoulé : %d\n", ts.get_total_minutes());
    }

    // temps écoulé
    {
        jed_utils::datetime date1(2016, 11, 25);
        jed_utils::datetime date2(2016, 12, 5);
        jed_utils::timespan ts1 = date2 - date1;
        printf("temps écoulé : %d\n", ts1.get_total_seconds());
    }

    // empty
    {
        jed_utils::datetime dtTest = jed_utils::datetime::parse(std::string("yyyy/MM/dd HH:mm:ss"), std::string("2016-08-18 23:14:42"));
        printf("parse : %s\n", dtTest.to_string().c_str());
    }

    // GDateTime
    {
        GDateTime dtTest;
        printf("GDateTime : %s\n", dtTest.toString().c_str());
    }

    // GDateTime
    {
        GDateTime dtTest;
        printf("GDateTime : %s\n", dtTest.to_string().c_str());
    }

    // GDateTime
    {
        GDateTime dtTest;
        dtTest.toParse("2016-08-18 23:14:42");
        printf("GDateTime : %s\n", dtTest.toString().c_str());
    }

    // GDateTime
    {
        GDateTime dtTest;
        dtTest.toParse("0000-00-00 00:00:00");
        printf("GDateTime : %s\n", dtTest.toString().c_str());
        GDateTime dtTest2 = dtTest;
        printf("GDateTime : %s\n", dtTest2.toString().c_str());
    }
}
//===============================================
void GTest::runCurl(int _argc, char** _argv) {
    printf("%s...\n", __FUNCTION__);
    GCurl lCurl;
    GString lData = lCurl.postHttpsFormFacade("calculator", "run_calculator");
    m_logs.addLogs(lCurl.getLogs());
    if(!m_logs.hasErrors()) {
        m_logs.addData(lData);
    }
}
//===============================================
void GTest::runEmail(int _argc, char** _argv) {
    printf("%s...\n", __FUNCTION__);
    GString lAction = "no_reply";

    if(lAction == "") {
        m_logs.addError("L'action est obligatoire.");
    }
    else if(lAction == "reply") {
        GEmail lEmail;
        lEmail.setSubject("Salutations (Cpp)");
        lEmail.setBody("Voici mon premier email (Cpp).");
        lEmail.getTo().addAddr("kernelly.blavatsky@outlook.fr", "Kernelly BLAVASKY");
        lEmail.sendEmail();
        m_logs.addLogs(lEmail.getLogs());
        if(!m_logs.hasErrors()) {
            m_logs.addData(lEmail.serialize());
        }
    }
    else if(lAction == "no_reply") {
        GEmail lEmail;
        lEmail.setSubject("Salutations (Cpp-No-Reply)");
        lEmail.setBody("Voici mon premier email (Cpp-No-Reply).");
        lEmail.getTo().addAddr("kernelly.blavatsky@outlook.fr", "Kernelly BLAVASKY");
        lEmail.setNoReply();
        lEmail.getCC().addAddr("adyoboue@outlook.fr", "Deborah YOUBOUE");
        lEmail.getBCC().addAddr("tiakagerard@hotmail.com", "Gérard KESSE");
        lEmail.sendEmail();
        m_logs.addLogs(lEmail.getLogs());
        if(!m_logs.hasErrors()) {
            m_logs.addData(lEmail.serialize());
        }
    }
    else {
        m_logs.addError("L'action est inconnue.");
    }
}
//===============================================
