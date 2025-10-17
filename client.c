#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024 // definovanie velkosti bufferu pre spravy

int main(int argc, char *argv[]) {
    if (argc != 3) { // kontrola poctu argumentov programu
        fprintf(stderr, "pouzite: %s <ip> <port>\n", argv[0]); // vypis instrukcii pre pouzitie programu
        return 1;
    }

    const char *ip = argv[1]; // nacitanie ip adresy zo vstupnych argumentov
    int port = atoi(argv[2]); // konverzia portu z textu na cislo
    int client_socket; // premenna pre socket klienta
    struct sockaddr_in server_addr; // struktura pre adresu servera
    char buffer[BUFFER_SIZE]; // buffer pre ukladanie spravy

    client_socket = socket(AF_INET, SOCK_STREAM, 0); // vytvorenie socketu
    if (client_socket < 0) { // kontrola ci sa socket vytvoril uspesne
        perror("chyba pri vytvarani socketu"); // vypis chyby ak sa socket nepodarilo vytvorit
        return 1;
    }

    memset(&server_addr, 0, sizeof(server_addr)); // vynulovanie struktury pre adresu
    server_addr.sin_family = AF_INET; // nastavenie typu adresy na ipv4
    server_addr.sin_port = htons(port); // konvertovanie cisla portu na sietovy format

    if (inet_pton(AF_INET, ip, &server_addr.sin_addr) <= 0) { // konverzia ip adresy zo stringu na binarny format
        perror("chyba pri konverzii ip adresy");
        close(client_socket); // uzavretie socketu
        return 1;
    }

    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) { // pokus o pripojenie k serveru
        perror("chyba pri pripojeni k serveru");
        close(client_socket); // uzavretie socketu
        return 1;
    }

    if (!fgets(buffer, BUFFER_SIZE, stdin)) { // nacitanie textu od uzivatela
        fprintf(stderr, "chyba pri citani vstupu\n");
        close(client_socket); // uzavretie socketu
        return 1;
    }

    buffer[strcspn(buffer, "\n")] = '\0'; // nahradenie noveho riadku koncom retazca

    if (send(client_socket, buffer, strlen(buffer), 0) < 0) { // odoslanie nacitanej spravy na server
        perror("chyba pri odosielani udajov");
        close(client_socket); // uzavretie socketu
        return 1;
    }

    close(client_socket); // uzavretie socketu po ukonceni komunikacie

    return 0;
}