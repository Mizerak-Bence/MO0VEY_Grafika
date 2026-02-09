14. Előadás - Klasszikus mesterséges intelligencia algoritmusok
===============================================================

A problémateret egy gráfként reprezentálhatjuk.

* A játék állapota a gráf egy pontja.
* Minden lehetséges lépés egy-egy élt ad egy szomszédos pontba.
* Minden játékállapothoz hozzá rendelhetünk egy jósági értéket (a játék értékét az adott játékos szemszögéből).

Zéró összegű játékról beszélünk, hogy ha a két játékos összpontszáma nullát kell, hogy kiadjon.

Sudoku
~~~~~~

Az egyszerűbb implementáció esetében a megoldást úgy keressük, hogy végig próbálgatjuk az üres helyeken mind a 9 számértéket.

* A rekurzív implementáció a kézenfekvő.
* Szekvenciális esetben igyekszünk kerülni a tábla másolását.
* A rekurzív hívások párhuzamosan kiértékelhetők, hogy ha van saját másolatuk a tábláról.

Amőba
~~~~~

Naiv implementáció:

* Minden mező esetében a jósági értéket az alapján kapjuk, hogy oda egy szimbólumot helyezve mennyi lehetőségünk lesz a későbbiekben 5-öt kirakni.
* Az algoritmusban vannak súlyparaméterek, amelyek azt mutatják, hogy mennyi az értéke az 1-től 5-ig a kirakott részeknek.

Fában való keresés:

* Minden játékállapotból minden játékállapotba a lépések mentén élek vezetnek. Mivel nincs a játékban visszafelé lépés, ezért ez egy fát eredményez.
* A fa leveleiben vannak a nyert, vesztett és a döntetlen játszmák.
* Meg szeretnénk becsülni, hogy az adott részfában ezek száma mennyi.
* A sok lépési lehetőség miatt a fa terebélyes, nem praktikus minden ágon ténylegesen végig haladni.

Párhuzamosítási lehetőségek:

* A naiv implementáció esetén a paraméterek becslése szimulációval végezhető. Egy-egy paraméter kiértékelése párhuzamosan elvégezhető.
* A szóbajöhető mezőkre a jósági érték kiértékelése párhuzamosan elvégezhető. (Egyidejűleg a maximum kiválasztására is van lehetőség.)

Kérdések
--------

* Mit jelent az, hogy egy játék zéró összegű?

Feladatok
---------

* Adjunk hatékonyabb számítást a Sudoku tábla érvényességének ellenörzéséhez!
* Becsüljük meg az Amőba játék optimális paramétereit!
