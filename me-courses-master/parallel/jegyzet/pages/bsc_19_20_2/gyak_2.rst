2. gyakorlat
============

A ``FORALL`` utasítás
---------------------

Gyökszámítás
~~~~~~~~~~~~

Olvassunk be 100 valós értéket egy fájlból, majd számítsuk ki mindegyik négyzetgyökét!

.. code-block:: pascal

   PROGRAM sqroot;
   VAR A: ARRAY [1..100] OF REAL;
       i: INTEGER;
   BEGIN
       FOR i := 1 TO 100 DO
           Readln(A[i]);
       FOR i := 1 TO 100 DO
           A[i] := SQRT(A[i]);
       FOR i := 1 TO 100 DO
           Writeln(A[i]);
   END.


* Vizsgáljuk meg a futási időt az elemszám függvényében! Próbáljuk megbecsülni ez alapján az időbonyolultságot!
* A középső, számításokat végző ``FOR`` ciklust cseréljük ki ``FORALL`` ciklusra, és nézzük meg, hogy mennyi a párhuzamos futási idő és a *speed-up*!
* Csoportosítsuk a számítási lépéseket a ``GROUPING`` kulcsszó segítségével, és vizsgáljuk meg, hogy a csoportméret függvényében hogyan változik a futási idő!

Optimális csoportméret számítása
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Vezessük be az alábbi jelöléseket!

* :math:`c`: egy processz létrehozási ideje [:math:`ms`]
* :math:`G`: a csoportok mérete (az egy processz által végrehajtandó maximális lépésszám)
* :math:`n`: a feladat elvégzéséhez szükséges lépések száma
* :math:`d`: egy számítási lépés végrehatjási ideje [:math:`ms`]
* :math:`T`: a számítás végrehajtásához szükséges futási idő.

Feltételezzük, hogy a futtatókörnyezet a processzeket egyidejűleg hozza létre és egyszerre indítja el a számítást.

* Hogyan határozhatjuk meg a processzek számát? (Jelöljünk :math:`p`-vel!)
* Ábrázoljuk Gannt diagramon, hogy hogyan adódik a teljes futási idő!
* Írjuk fel a futási idő számítását!
* Ismert :math:`c, d, G` értékek esetén határozzuk meg az optimális processz számot!
* Hogyan tudnánk megbecsülni a :math:`c` és :math:`d` értékeket? Próbáljuk ezt megtenni!
* Ábrázoljuk Gannt diagramon azt az esetet, hogy ha a processzek rögtön elindulnak, amint a futtatókörnyezet létrehozta őket!


Egymásba ágyazott ``FORALL`` ciklusok
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

* Készítsünk egy programot, amelyik 10000 beolvasott valós érték összegét számítja ki!
* Vizsgáljuk meg a ``FOR`` és ``FORALL`` ciklusos változatok futási idejét!
* Hogyan lehetne több szinten ``FOR`` és ``FORALL`` ciklusok használatával megoldani a problémát?


További feladatok
~~~~~~~~~~~~~~~~~

* Tekintsük át a ``ranksort`` nevű programot!
* Implementáljuk a mátrix szorzás műveletet soros és párhuzamosított program formájában!
* Vizsgáljuk meg a változók hatóköréből adódó problémákat!

