# Client-Server Komunikácia v jazyku C

Tento projekt demonštruje základný princíp **komunikácie klient-server** pomocou **socketov** v jazyku C.  
Server a klient medzi sebou nadväzujú spojenie cez TCP (Transmission Control Protocol).

## Popis programu

- **server.c** – vytvára socket, počúva na určenom porte a čaká na pripojenie klienta. Po prijatí správy ju môže spracovať a poslať odpoveď späť klientovi.  
- **client.c** – vytvára socket, pripája sa na server a odosiela mu správu (napr. textový reťazec). Následne čaká na odpoveď od servera.

Programy demonštrujú princípy:
- vytvárania a zatvárania socketov,
- použitia funkcií `bind()`, `listen()`, `accept()`, `connect()`, `send()` a `recv()`,
- základnej obojsmernej komunikácie po sieti.<br><br>

Autor: Denis Čumitta
