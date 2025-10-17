#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024 // definovanie velkosti bufferu

int main(int argc, char *argv[]) {
    if (argc != 2) { // kontrola poctu argumentov
        fprintf(stderr, "pouzite: %s <port>\n", argv[0]); // vypis instrukcii pre pouzitie
        return 1;
    }

    int port = atoi(argv[1]); // konverzia portu na cislo
    int server_socket, client_socket; // premenne pre sockety servera a klienta
    struct sockaddr_in server_addr, client_addr; // struktury pre adresy servera a klienta
    socklen_t client_addr_len = sizeof(client_addr); // dlzka adresy klienta
    char buffer[BUFFER_SIZE]; // buffer pre prijate udaje
    ssize_t bytes_received; // pocet prijatych bajtov

    server_socket = socket(AF_INET, SOCK_STREAM, 0); // vytvorenie socketu
    if (server_socket < 0) { // kontrola ci sa socket vytvoril uspesne
        perror("chyba pri vytvarani socketu");
        return 1;
    }

    memset(&server_addr, 0, sizeof(server_addr)); // vynulovanie struktury adresy
    server_addr.sin_family = AF_INET; // nastavenie typu adresy na ipv4
    server_addr.sin_addr.s_addr = INADDR_ANY; // akceptovanie pripojeni z akejkolvek adresy
    server_addr.sin_port = htons(port); // konvertovanie cisla portu na sietovy format

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) { // pokus o priradenie socketu k portu
        perror("chyba pri priradovani socketu k portu");
        close(server_socket); // uzavretie socketu
        return 1;
    }

    if (listen(server_socket, 1) < 0) { // zacatie pocuvania na serverovom sockete
        perror("chyba pri spustani pocuvania");
        close(server_socket); // uzavretie socketu
        return 1;
    }

    fprintf(stderr, "cakanie na pripojenie na porte %d...\n", port); // vypis cakania na pripojenie

    client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len); // prijatie klienta
    if (client_socket < 0) { // kontrola ci bolo pripojenie uspesne
        perror("chyba pri prijimani pripojenia");
        close(server_socket); // uzavretie socketu
        return 1;
    }

    bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0); // prijatie dat od klienta
    if (bytes_received < 0) { // kontrola, ci prijatie bolo uspesne
        perror("chyba pri prijimani udajov");
        close(client_socket); // uzavretie klientskeho socketu
        close(server_socket); // uzavretie serveroveho socketu
        return 1;
    }

    buffer[bytes_received] = '\0'; // ukoncenie prijateho textu nulovym znakom
    printf("%s\n", buffer); // vypis prijatej spravy
    fprintf(stderr, "pocet prijatych bajtov: %ld\n", bytes_received); // vypis poctu prijatych bajtov

    close(client_socket); // uzavretie klientskeho socketu
    close(server_socket); // uzavretie serveroveho socketu

    return 0;
}