# VisuAlgo
Biblioteka w C++ do tworzenia prezentacji wizualizujących działanie algorytmów.

## Opis
Biblioteka udostępnia wygodne funkcje pozwalające dla dowolnych zmiennych/tablic/grafów stworzyć prezentację w PDFie, która obrazuje ich działanie w wybranym algorytmie.

## Wymagane narzędzia
- LaTeX (wraz z biblioteką beamer)
- graphviz
- pdfunite

## Generowanie plików wykonywalnych
Aby zbudować bibliotekę, należy użyć komendy:
```sh
make
```

## Architektura
W katalogu `architecture/` znajdują się 2 diagramy logical view. Ze względu na czytleność, w szczegółowym diagramie umieściliśmy wszystkie klasy użyte w projekcie, a w ogólnym uproszczony diagram z uwzględnieniem kluczowych funkcji najważniejszych klas projektu.

## Przykłady 
W folderze `examples/` znajdują się przykłady ilustrujące sposoby użycia biblioteki. Aby je zbudować, należy użyć komendy:
```sh
make examples
```

### Prezentacje generowane przez przykładowe programy

Przykłady użycia biblioteki znajdują się w katalogu `examples/` w plikach `*.cc`. Wypisują one kod LaTeXa na standardowe wyjście.
Aby automatycznie uruchomić wszystkie programy i zrobić z wygenerowanego kodu LaTeXa PDFy należy użyć komendy:
```sh
make examples/examples.pdf
```
Stworzy ona wszystkie prezentacje oraz złączy je w jedną i zapisze do pliku `examples/examples.pdf`.
Pojedyncze prezentacje odpowiadają przykładowym programom np. dla `arrays.cc` zostanie utworzona prezentacja `arrays.pdf`.

#### Spis przykładów

| Nazwa | Opis |
|------|------|
| arrays | demonstruje przykłady tablic jedno- i dwuwymiarowych oraz kolorowanie pól |
| binsearch | demonstruje działanie algorytmu wyszukiwania binarnego |
| containers | prezenuje uzycie wizualizacji kontenerów z biblioteki standardowej C++ |
| dijkstra | demonstruje wizualizację grafów na przykładzie algorytmu dijkstry |
| graph | wizualizuje wybrane operacje na grafach ukorzenionych (w tym drzewa, drzewa binarne) |
| matrix | wizualizacja działania macierzy |
| pictures | przykład dodawania obrazków o zadanej wielkości i kącie obrotu na wybrane miejsce na slajdzie | 
| sieve | prezentuje działanie sita Eratostenesa |

