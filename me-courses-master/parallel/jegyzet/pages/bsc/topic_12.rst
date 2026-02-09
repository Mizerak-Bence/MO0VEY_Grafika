12. Előadás - Optimalizálás
===========================

Adott egy :math:`f: \mathbb{R}^n \rightarrow \mathbb{R}` függvény.

A feladat az, hogy meghatározzuk azt az :math:`x \in \mathbb{R}^n` pontot, amelyre az :math:`f(x)` értéke minimális (vagy maximális).

Particle Swarm Optimization
~~~~~~~~~~~~~~~~~~~~~~~~~~~

Az optimalizálási problémát úgy próbálja megoldani, hogy adott számú pontot elhelyez a térben, majd külön iterációkban módosítja azok helyét (és a további állapotát). Ehhez felír egy szabályrendszert.

* A madár és hal rajok mintáját követi az algoritmus.
* Különféle változatai vannak.
* Nagyon jól párhuzamosítható, mivel minden részecskének időben egyszerre számolható a következő állapota.

Genetikus Algoritmus
~~~~~~~~~~~~~~~~~~~~

Az optimalizálási probléma megoldásához létrehoz egy populációt.

* Feltételezi, hogy a problématér egy vektor (*gének*) formájában leírható.
* Operátorokat definiál a gének módosítására, keresztezésére.
* Ad egy heurisztikát arra vonatkozóan, hogy a populációból a következő iterációban mely egyedeket kell megtartani.

A mutációs és keresztező operátor, illetve a jósági (*fitness*) függvény kiértékelése egyaránt lehetőséget ad a párhuzamosításra.

Kérdések
--------

* Milyen adatok tartozhatnak például részecskeraj optimalizáció (*PSO*) esetében egy részecskéhez?
* Milyen esetben használható a genetikus algoritmus?

Feladatok
---------

* Implementáljuk az előzőekben említett algoritmusokat!
* Készítsen hozzájuk konkrét példákat!
