#include <iostream>
#include <string>
#include "LcurlEasy.hpp"
const char* url_httpbin= "https://httpbin.org/get";
const char* url_ipify= "https://api.ipify.org";




int main (int argc, char** argv) {
    
    LcurlEasy::HTTP_req(LcurlEasy::GET, url_ipify);
    
    return 0;
}


