# Genetic-Cars

Instalacja wymaganych bibliotek i narzędzi (system Linux)
1. Należy uruchomić skrypt install.sh (instaluje on pakiety niezbędne do zbudowania aplikacji, pobiera kod źródłowy biblioteki Box2D z repozytorium Github oraz pobiera i uruchamia instalator QT)
2. Zostanie uruchomiony instalator QT:
	- Należy z listy rozwinąć QT
	- Następnie należy roziwnąć QT 5.10.0
	- Wybieramy "Desktop gcc 64-bit" oraz "Qt Charts" i kontynuujemy instalację.
3. Po zakończeniu instalacji należy dodać do zmiennych środowiskowych zmienną QT5DIR i ścieżkę do zainstalowanego QT (na przykład):
Należy uruchomić terminal i wpisać (zastępując podaną ścieżkę własną ścieżką instalacji QT): 
export QT5DIR="/home/username/Qt/5.10.0/gcc_64"
4. Po tej operacji możliwe jest już zbudowanie projektu z poziomy katalogu z plikiem SConstruct. Aby zbudować należy wywołać "scons". Plik wykonywalny o nazwie "GeneticCars" zostanie umieszczony w katalogu "build".