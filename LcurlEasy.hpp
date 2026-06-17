#include <string>
#include <iostream>
#include <curl/curl.h>

using namespace std;



enum Metodo {GET, POST, PUT, DELETE};

class response {
private:
public:
    long status_code;
    CURLcode curlcode;
    string resposta;
    response(/* args */){}
    ~response(){}
};

size_t writefunc(void* buffer, size_t size, size_t NMemBytes, void* response){
    size_t total= size * NMemBytes;
    string* response_ = static_cast<string*>(response);
    response_->append(static_cast<char*>(buffer), total);
    return total;
}


response HTTP_req(Metodo metodo, const char* url, const char* infos= {}) {


    if (metodo != GET) {cout << "metodo ainda nao implementado."; exit (-1);}
    response resposta;
    
    CURL* curl = curl_easy_init(); //Inicializa o handle da curl 
    if (!curl) {cerr << "Erro ao inicializar o CURL" << endl; exit(1);}
    
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &(resposta.resposta));

    CURLcode res = curl_easy_perform(curl);

    // 7. Verificação básica de erro
    if (res != CURLE_OK) {cerr << "Falha na requisicao: " << curl_easy_strerror(res) << endl; exit(-1);}
    
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &resposta.status_code);



    curl_easy_cleanup(curl);
    return resposta;
}
