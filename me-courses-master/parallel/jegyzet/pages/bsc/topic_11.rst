11. Előadás - Grafikai algoritmusok
===================================

Konvex burok számítása
~~~~~~~~~~~~~~~~~~~~~~

Tegyük fel, hogy adott :math:`n` számú pont egy vektortérben!

A feladat az, hogy meghatározzuk a ponthalmaz adott részhalmazát, amelyek kifeszítik a teljes ponthalmaz konvex burkát.

A problémát megfogalmazhatjuk úgy is, hogy meg szeretnénk határozni azon minimális elemszámú részhalmazt, amelynek a konvex burka megegyezik az eredeti ponthalmazéval.

**QuickHull algoritmus**

Feltételezzük, hogy síkbeli pontokról van szó. Az algoritmus működése az alábbi formában foglalható össze.

* Kiválasztunk 2 pontot, amely biztosan a konvex burkon van.
* Húzunk egy ezeken áthaladó egyenest. A problémát ezzel 2 részre bontottuk.
* Meghatározzuk az egyenestől legtávolabb eső pontot (a felosztás során kapott ponthalmazon belül). Ez így szükségszerűen a konvex burkon lesz.
* Ezt a pontot tekintjük a felosztáshoz használt új pontnak.
* Az új ponttal, és az első lépésben kiválasztott pontokkal rekurzív módon elvégezhetjük a felosztást.
* A leállási feltételt az adja, hogy a halmazokból a pontok elfogynak.

.. warning::

  A pontok megadási sorrendje számít a felosztásnál, mivel az alapján lehet eldönteni, hogy az egyenes melyik oldalára esnek a pontok!

A munka bonyolultsága hasonló a Gyorsrendezéséhez:

* legrosszabb esetben: :math:`\mathcal{O}(n^2)`,
* átlagos esetben: :math:`\mathcal{O}(n \cdot \log n)`.

:math:`\rhd` Hogyan oldható meg a ponthalmaz ábrázolása a hatékony implementációhoz?

Kérdések
--------

* Definiálja a konvex burok fogalmát!

Feladatok
---------

* Implementáljuk a QuickHull algoritmust!
* Készítsen hozzájuk konkrét példákat!
