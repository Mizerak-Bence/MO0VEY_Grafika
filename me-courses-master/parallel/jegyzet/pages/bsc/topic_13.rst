13. Előadás - Osztályozás
=========================

Az osztályozandó elemeket pontokként (valós vektorokként) tekinthetjük. Az osztályozás célja, hogy egy adott pontról eldöntsük, hogy milyen osztályba tartozik.

Precedens alapú osztályozó
~~~~~~~~~~~~~~~~~~~~~~~~~~

Rendelkezésre állnak olyan pontok, amelyekről tudjuk, hogy milyen osztályba tartoznak.

Feltételezzük, hogy a térben van egy adott metrika (például euklideszi távolság).

A KNN (*K Nearest Neighbour*) osztályozó megkeresi a :math:`K` számú legközelebbi szomszédot, majd a kérdéses pont osztályának a leggyakrabban előforduló osztályt választja.

Klaszterezés
------------

Adott egy ponthalmaz, rajta egy metrika. A ponthalmaz alapján meg szeretnénk határozni, hogy milyen csoportok, klaszterek (*clusters*) alkotják a halmazt.

K-Means algoritmus
~~~~~~~~~~~~~~~~~~

Tudjuk, hogy a pontokat :math:`K` klaszterbe lehet besorolni.

* Minden pontot besorolunk a :math:`K` számú klaszter valamelyikébe.
* Definiálunk egy hiba metrikát, amelyik az aktuális klaszterezés jóságát mutatja.
* Feltételezzük, hogy a klaszterek a metrika szerint térben közel helyezkednek el egymáshoz (közel gömb alakúak).
* Kiszámítjuk a klaszterek aktuális középpontját.
* Meghatározzuk, hogy az alapján mely pontok melyik klaszterbe esnének.
* Módosítjuk a klaszter azonosítókat.

Kérdések
--------

* Mi a különbség az osztályozás és a klaszterezés között?

Feladatok
---------

* Implementáljuk az előzőekben említett algoritmusokat!
* Készítsen hozzájuk konkrét példákat!
