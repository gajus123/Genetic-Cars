# Genetic-Cars

Instalacja wymaganych bibliotek i narzędzi (system Linux)
1. Należy uruchomić skrypt install.sh (instaluje on pakiety niezbędne do zbudowania aplikacji, pobiera kod źródłowy biblioteki Box2D z repozytorium Github oraz pobiera i uruchamia instalator QT)
2. Zostanie uruchomiony instalator QT. Należy z listy wersji rozwinąć 5.10.0, a następnie wybrać do instalacji elementy "gcc 64" oraz "QtCharts"
3. Po zakończeniu instalacji należy dodać do zmiennych środowiskowych zmienną QT5DIR i ścieżkę do zainstalowanego QT (na przykład):
QT5DIR="/home/username/QT/5.10.0/gcc_64"
export QT5DIR
4. Po tej operacji możliwe jest już zbudowanie projektu z poziomy katalogu z plikiem SConstruct. Aby zbudować należy wywołać "scons". Plik wykonywalny o nazwie "GeneticCars" zostanie umieszczony w katalogu "build".