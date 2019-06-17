# VisuAlgo
Biblioteka w C++ do tworzenia prezentacji ilustrujących działanie algorytmów.

## Opis
Biblioteka udostępnia wygodne funkcje pozwalające dla dowolnych zmiennych/tablic/grafów stworzyć prezentację w PDFie, która obrazuje ich działanie w wybranym algorytmie.

## Wymagane narzędzia
- Kompilator C++ wspierający C++17
- LaTeX (wraz z biblioteką beamer)
- graphviz
- pdfunite

## Generowanie plików wykonywalnych
Aby zbudować samą bibliotekę, należy użyć komendy:
```sh
make visualgo.a
```

## Architektura
W katalogu `io_stuff/architecture/` znajdują się 2 diagramy logical view. Ze względu na czytelność, w szczegółowym diagramie umieściliśmy wszystkie klasy użyte w projekcie, a w ogólnym uproszczony diagram z uwzględnieniem kluczowych funkcji najważniejszych klas projektu.

## Przykłady
Przykłady użycia biblioteki znajdują się w katalogu `examples/` w plikach `*.cc`. Wypisują one kod LaTeXa na standardowe wyjście. Aby je skompilować, automatycznie uruchomić i z wygenerowanego kodu LaTeXa zrobić PDFy, należy użyć komendy:
```sh
make examples
```
Pojedyncze prezentacje odpowiadają przykładowym programom np. dla `arrays.cc` zostanie utworzona prezentacja `arrays.pdf`.

Aby zrobić z wszystkich przykładowych prezentacji jednego PDFa wystarczy użyć komendy:
```sh
make examples/examples.pdf
```
lub
```sh
make all
```
która dodatkowo zbuduje do pliku `presentation/presentation.pdf` prezentację krótko przedstawiającą naszą bibliotekę.

### Spis przykładów

| Nazwa | Opis |
|------|------|
| arrays | demonstruje przykłady tablic jedno- i dwuwymiarowych oraz kolorowanie pól |
| binsearch | demonstruje działanie algorytmu wyszukiwania binarnego |
| containers | prezentuje użycie wizualizacji kontenerów z biblioteki standardowej C++ |
| dijkstra | demonstruje wizualizację grafów na przykładzie algorytmu dijkstry |
| geometry | przykład rysowania obiektów geometrycznych 2D |
| graph | wizualizuje wybrane operacje na grafach ukorzenionych (w tym drzewa, drzewa binarne) |
| matrix | wizualizacja działania macierzy |
| pictures | przykład dodawania obrazków o zadanej wielkości i kącie obrotu na wybrane miejsce na slajdzie | 
| sieve | prezentuje działanie sita Eratostenesa |

## Testy
Aby uruchomić testy jednostkowe należy użyć komendy:
```
make test
```

