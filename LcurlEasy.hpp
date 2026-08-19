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
    response(){}
    ~response(){}
};

/*
    funçao que dita gerencia o registro de dados pra dentro do buffer
*/
size_t writefunc(void* buffer, size_t size, size_t NMemBytes, void* response){
    size_t total= size * NMemBytes;
    string* response_ = static_cast<string*>(response);
    response_->append(static_cast<char*>(buffer), total);
    return total;
}

response HTTP_req(Metodo metodo, const char* url, const char* infos = nullptr) {

    response resposta;
    
    CURL* curl = curl_easy_init(); //Inicializa o handle da curl 
    if (!curl) {cerr << "Erro ao inicializar o CURL" << endl; exit(1);}
    
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &(resposta.resposta));

    // Configuração dos métodos HTTP
    switch (metodo) {
        
        case GET:
            curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
            break;
            
        case POST:
            curl_easy_setopt(curl, CURLOPT_POST, 1L);
            if (infos) {
                curl_easy_setopt(curl, CURLOPT_POSTFIELDS, infos);
            }
            break;
            
        case PUT:
            curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
            if (infos) {
                curl_easy_setopt(curl, CURLOPT_POSTFIELDS, infos);
            }
            break;
            
        case DELETE:
            curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
            if (infos) {
                curl_easy_setopt(curl, CURLOPT_POSTFIELDS, infos);
            }
            break;
    }

    CURLcode res = curl_easy_perform(curl);
    
    // Salvando o código de resultado do CURL na classe response
    resposta.curlcode = res; 

    // Verificação básica de erro
    if (res != CURLE_OK) {cerr << "Falha na requisicao: " << curl_easy_strerror(res) << endl; exit(-1);}
    
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &resposta.status_code);

    // encerra o handle curl
    curl_easy_cleanup(curl);
    return resposta;
}