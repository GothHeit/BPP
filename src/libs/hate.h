#ifndef HATE_H
#define HATE_H

#include <vector>
#include <string>

namespace hate {

    /// @brief Converte a string para minúsculas.
    /// @param orig A string original.
    /// @return Uma string com todos os caracteres em minúsculo.
    std::string to_lower(std::string orig);

    /// @brief Divide a string de entrada em substrings com base nos delimitadores fornecidos.
    /// @param input A string a ser dividida.
    /// @param delimiters Caracteres usados para divisão (padrão: espaço e tabulação).
    /// @param remove_empty Se deve remover strings vazias do resultado (padrão: true).
    /// @return Um vetor de strings resultante da divisão.
    std::vector<std::string> split(const std::string& input, const std::string& delimiters = " \t", bool remove_empty = true);

    /// @brief Remove delimitadores do início da string.
    /// @param input A string a ser tratada.
    /// @param delimiters Caracteres a serem removidos (padrão: espaço e tabulação).
    /// @return A string sem os delimitadores à esquerda.
    std::string ltrim(const std::string& input, const std::string& delimiters = " \t");

    /// @brief Remove delimitadores do fim da string.
    /// @param input A string a ser tratada.
    /// @param delimiters Caracteres a serem removidos (padrão: espaço e tabulação).
    /// @return A string sem os delimitadores à direita.
    std::string rtrim(const std::string& input, const std::string& delimiters = " \t");

    /// @brief Gera uma progressão aritmética entre dois valores.
    /// @param first Primeiro termo da progressão.
    /// @param last Último termo da progressão.
    /// @param middle_terms Quantidade de termos intermediários.
    /// @return Vetor contendo a progressão aritmética completa.
    std::vector<int> interpolate_arithmetic(int first, int last, int middle_terms);

    /// @brief Conta quantos dígitos possui um número inteiro.
    /// @param value O número a ser contado.
    /// @return Número de dígitos.
    int count_digits(int value);

    /// @brief Verifica se um valor está presente em um vetor até uma certa posição.
    /// @param target O valor a ser procurado.
    /// @param values Vetor onde será feita a busca.
    /// @param limit Índice limite até onde buscar.
    /// @return true se encontrado antes do limite; false caso contrário.
    bool exists_before(const std::vector<int>& values, int target, unsigned int limit);

} // namespace hate

#endif // HATE_H
