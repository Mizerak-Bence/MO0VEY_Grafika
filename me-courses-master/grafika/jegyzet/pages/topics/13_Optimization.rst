Optimalizálás
=============

* Számítási idő vs. háttértár
* Renderelési idő vs. előrenderelés

Ütközésvizsgálat
----------------

Az ütközésvizsgálat (és ezzel általában együtt) a fizika számítása igen költséges művelet. Számos módszert kidolgoztak a probléma megoldásának hatékonyabbá tételéhez. Ezek alapvetően a térpartícionálási és keresési módszerek témakörébe tartoznak.

* Befoglaló testek (*bounding box*) alkalmazása.
* BSP: *Binary Space Partitioning*, https://en.wikipedia.org/wiki/Binary_space_partitioning
* Oktális fák alkalmazása, *Octree*, https://en.wikipedia.org/wiki/Octree

Level of Details
----------------

* Röviden *LoD*-nak szokták rövidíteni.
* Az a feltételezés mögötte, hogy a kisebb méretben megjelenített modelleket és textúráikat felesleges túlságosan jó minőségben megjeleníteni, mert úgy sem látszódnának.
* A célja egyaránt a számítási idő, és az (aktuális) tárigény csökkentése.
* https://en.wikipedia.org/wiki/Level_of_detail_(computer_graphics)

A módszer alkalmazásának fontosabb lépései a következők.

* Definiálni kell különböző részletességi szinteket.
* Távolság függvényében meg kell határozni, hogy éppen milyen részletességnek kell látszódnia.
* Az eredeti, nagy felbontású modelleket és textúrákat alacsonyabb poligonszámúvá és kisebb felbontásúvá kell alakítani.

.. note::

  A modellek és textúrák részletességi szintjének állításán kívül a fények, anyagjellemzők és a színtér, a megjelenítés további elemeire is vonatkozhatnak egyszerűsítések.

Environment mapping
-------------------

* Csillogó felületek megjelenítésére alkalmazható, a helyett, hogy tényleges tükröződéssel kellene számolni.
* Az egyik egyszerűbb implementációja az, hogy ha a környezetről készített képet, mint textúrát rakjuk rá a modellre.
* Az aktuálisan leképzett képrészek (mint ahogyan a tükröződés is) erősen függ a megjelenített alakzat, és a kamera pozíciójától is.
* https://en.wikipedia.org/wiki/Reflection_mapping

Bump mapping
------------

* Érdes felületek, felületi egyenetlenségek megjelenítésére használják.
* Az alapötlet az, hogy a felület fényhatásait többek között a normálvektorok határozzák meg, amelyeket textúraszerűen, háromszögeken belül is tudunk változtatni.
* A számítás hatékonyabb, mint hogy ha ténylegesen, nagyobb poligonszámú modellel dolgoznánk, a megjelenítés minősége viszont hasonló.
* A *bump mapping* nincs tekintettel a felület alakjára, úgy értve, hogy hiába jelenítünk meg vele egy érdes felületet, az alakzat szélein ez nem fog különbséget jelenteni.
* https://en.wikipedia.org/wiki/Bump_mapping

Displacement mapping
--------------------

* Megtehetjük, hogy a felület pontjait ténylegesen eltoljuk. Ennek a tárolására az eltolásokat hasonlóképpen kezelhetjük, mint a textúrákat.
* https://en.wikipedia.org/wiki/Displacement_mapping

On-demand betöltés
------------------

* A színterünk bizonyos részeit igény szerint tölthetjük be.
* Ezzel az erőforráskihasználás javul, mivel közelíthetjük azt, hogy ténylegesen mennyi elem kezelésére van egyidejűleg szükség.

