# Genetic-Cars

Instalacja wymaganych bibliotek i narzędzi (system Linux)
1. Należy uruchomić skrypt install.sh (instaluje on wszystkie pakiety niezbędne do zbudowania aplikacji oraz pobiera kod źródłowy biblioteki Box2D z repozytorium Github)



# Tworzenie obiektów

1. Stwórz Physics::Loop
2. loop.run(); <- tworzy wątek z petlą fizyki
                  loop powinien istnieć przez cały czas istnienia programu
3. Physics::ObjectsFactory.init(loop) <- musi zostać wywołane zanim zostanie
                                         stworzony jakikolwiek inny obiekt
4. Stwórz obiekt:
        Objects::Wheel circle(Vector2(0.0f, 0.0f), 1.0f) <- już dodany do symulacji


   Uwagi:
        obiektów nie da sie usuwac, nie żebyśmy musieli.
        stworzone obiekty powinny zyć przez cały czas programu
        zostaną same usunięte wraz z usunięciem loop