#include <iostream>
#include <string>
#include "LcurlEasy.hpp"

using namespace std;

const char* url_httpbin= "https://httpbin.org/get";
const char* url_ipify= "https://api.ipify.org";
const char* url_colab= "https://colab.research.google.com/drive/1zQbCbEzNrlIEuPfc843nQoWMeoaljR_z?usp=sharing#scrollTo=5rufnSrqf0rx";



int main (int argc, char** argv) {
    
    response res= HTTP_req(GET, url_colab);

    cout << "curl code:" << res.curlcode << endl;
    cout << "status code:" << res.status_code << endl;
    cout << "response body:" << res.resposta << endl;
    
    return 0;
}


