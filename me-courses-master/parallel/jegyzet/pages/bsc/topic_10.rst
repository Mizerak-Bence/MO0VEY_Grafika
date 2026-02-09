10. Előadás - Gráfalgoritmusok
==============================

Egy gráfot egy :math:`G = (V, E)` párnak tekintünk, ahol :math:`V` a csúcspontok (*vertices*), :math:`E` az élek (*edges*) halmaza.

* Irányítatlan gráf esetében: :math:`E = \{\{x, y\} \mid x, y \in V\}`
* Irányított gráf esetében: :math:`E \subseteq V \times V`

Összefüggő komponensek keresése
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Legyen adott egy :math:`G` irányítatlan gráf. A gráf komponenseinek tekintjük azon részgráfokat, melyek bármely két pontja között vezet út.

A problémát kezelhetjük úgy is, hogy minden :math:`v \in V` csúcshoz szeretnénk rendelni egy komponens azonosítót (label, címke, szín), amely mutatja, hogy melyek érhetők el egymásból.

Az összefüggő komponensek keresésénél az a célunk, hogy

* meghatározzuk, hogy melyek az összefüggő (maximális elemszámú) részgráfok,
* mennyi részgráfból áll a :math:`G` gráf.

A probléma megoldható például:

* mélységi vagy szélességi bejárással,
* gráf kontrakcióval.

Minimális feszítőfa számítása
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Tegyük fel, hogy van egy :math:`G = (V, E)` súlyozott gráfunk. A súlyozást megadhatjuk egy :math:`w: E \rightarrow \mathbb{R}` függvény formájában.

Feltételezhetjük, hogy a gráfunk összefüggő.

A feladat az, hogy meghatározzunk egy olyan :math:`T = (V, E')` részgráfot, ahol

* :math:`E' \subseteq E`,
* :math:`T` egy fa gráf,
* :math:`\displaystyle w(T) = \sum_{e \in E'} w(e) \rightarrow \min!`

Tranzitív lezárt
~~~~~~~~~~~~~~~~

Tegyük fel, hogy :math:`G` egy irányított gráf. Az éleket ábrázolhatjuk egy

.. math::

  A \in \{0, 1\}^{|V| \times |V|}

(*adjacencia*) mátrix formájában.

A feladat az, hogy az eredeti gráfhoz tartozó :math:`A` mátrix alapján meghatározzuk a gráf tranzitív lezártjának adjacencia mátrixát.

A problémát egy speciális, mátrix szorzáshoz hasonló művelet elvégzésével oldhatjuk meg.

A párhuzamosításra ugyanúgy adódik a lehetőség, mint mátrix szorzás esetében is.

Legrövidebb utak keresése
~~~~~~~~~~~~~~~~~~~~~~~~~

Tegyük fel, hogy adott egy :math:`G` súlyozott gráf. A feladat az, hogy tetszőleges :math:`a, b \in V` pontok esetében meghatározzuk az őket összekötő, minimális súlyú útvonalat.

**Dijkstra algoritmus**

Az algoritmus egy adott pontból (*source*) kiindulva képes meghatározni az összes pontra vonaktozóan az abba vezető legrövidebb utakat.

Kérdések
--------

* Írja le a mélységi keresés algoritmusát!
* Írja le a szélességi keresés algoritmusát!

Feladatok
---------

* Implementáljuk az előzőekben bemutatott algoritmusokat!
* Készítsen hozzájuk konkrét példákat!
