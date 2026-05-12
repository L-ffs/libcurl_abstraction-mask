#include <iostream>
#include <string>
#include <curl/curl.h>

using namespace std;


string url_httpbin= "https://httpbin.org/get";
string url_ipify= "https://api.ipify.org";

size_t callback(void* buffer, size_t size, size_t NMemBytes, void* response){
            size_t total= size * NMemBytes;
            string* response_ = static_cast<string*>(response);
            response_->append(*static_cast<string*>(buffer));
            return total;
        }

int main (int argc, char** argv) {

    CURL* handle= curl_easy_init();
    // 1. O "vessel" que vai guardar a resposta da internet
    std::string resposta_bruta;

    // 2. Inicializa o handle da curl (abre a aba do navegador)
    CURL* curl = curl_easy_init();

    if (curl) {
        // 3. Define o alvo (HTTPS nativo)
        curl_easy_setopt(curl, CURLOPT_URL, url_ipify);

        // 4. O Callback:Ela recebe os bytes do servidor e "empurra" para nossa string
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);

        // 5. Dizemos para o callback o endereço da nossa string
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &resposta_bruta);

        // 6. O Gatilho: Aqui o programa para e faz a mágica do HTTPS
        CURLcode res = curl_easy_perform(curl);

        // 7. Verificação básica de erro
        if (res == CURLE_OK) {
            long status_code;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &status_code);

            // Exibe os resultados na tela
            std::cout << "Sucesso! Status HTTP: " << status_code << std::endl;
            std::cout << "Seu IP Publico eh: " << resposta_bruta << std::endl;
        } else {
            std::cerr << "Falha na requisicao: " << curl_easy_strerror(res) << std::endl;
        }

        // 8. Limpa a memoria e fecha a conexao
        curl_easy_cleanup(curl);
    }

    return 0;
}