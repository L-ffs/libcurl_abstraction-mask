#!/bin/bash
echo 'rodando setup de teste de compilaçao e execuçao para linux'   


g++ main.cpp -o binfile
echo compilado
chmod +x binfile
echo 'permissao de execuçao concedida'

echo 'tentado rodar:'
./binfile
echo 
echo 'rodou com sucesso'
rm binfile
