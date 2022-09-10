//===============================================
#include "GTest.h"
//===============================================
GTest::GTest()
: GObject()
{

}
//===============================================
GTest::~GTest()
{

}
//===============================================
void GTest::run(int _argc, char** _argv)
{
    std::string lKey = "default";
    if(_argc > 2) lKey = _argv[2];

    if(lKey == "default")
    {
        runDefault(_argc, _argv);
    }
    else if(lKey == "curl")
    {
        runCurl(_argc, _argv);
    }
    else
    {
        runDefault(_argc, _argv);
    }
}
//===============================================
void GTest::runDefault(int _argc, char** _argv)
{
    printf("Aucun process n'a été sélectionné.\n");
}
//===============================================
void GTest::runCurl(int _argc, char** _argv)
{
    printf("Test du module CURL.\n");
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if(curl) {
      curl_easy_setopt(curl, CURLOPT_URL, "https://www.example.com/");
      res = curl_easy_perform(curl);

      if(CURLE_OK == res) {
        char *ct;
        /* ask for the content-type */
        res = curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &ct);

        if((CURLE_OK == res) && ct)
          printf("We received Content-Type: %s\n", ct);
      }

      /* always cleanup */
      curl_easy_cleanup(curl);
    }
}
//===============================================
