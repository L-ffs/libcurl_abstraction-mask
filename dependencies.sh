#!/bin/bash

echo "--- Verificando Dependências de Compilação ---"

# 1. Verifica g++
if ! command -v g++ &> /dev/null; then
    echo "g++ não encontrado. Instalando..."
    sudo apt update && sudo apt install -y build-essential
else
    echo "[OK] g++ já está instalado."
fi

# 2. Verifica libcurl de forma inteligente usando pkg-config
# Se o pkg-config retornar erro, significa que os arquivos de desenvolvimento (.h) não estão visíveis
if ! pkg-config --exists libcurl; then
    echo "Arquivos de desenvolvimento da libcurl não detectados pelo pkg-config."
    
    # Verifica se o pkg-config está instalado (necessário para a verificação)
    if ! command -v pkg-config &> /dev/null; then
        sudo apt update && sudo apt install -y pkg-config
    fi

    echo "Tentando instalar libcurl4-openssl-dev..."
    sudo apt update && sudo apt install -y libcurl4-openssl-dev
else
    echo "[OK] libcurl-dev detectada com sucesso."
    # Mostra onde os arquivos estão, só por curiosidade
    echo "Caminho dos Headers: $(pkg-config --cflags libcurl)"
fi

echo "--- Ambiente Pronto ---"