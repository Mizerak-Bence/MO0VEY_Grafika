****************************
Alternatív modellezési módok
****************************

Modellezési módok
=================

Drótváz vagy huzalvázmodell
---------------------------

* A határoló éleket, jellegzetes vonalakat adjuk meg egyenesek, ívek és görbék formájában.
* A megjelenítésénél a szemléltetés nem egyértelmű. Egyazon drótvázhoz lényegesen különböző testek is tartozhatnak.
* Mivel az ilyen modellek esetében csak az éleket ismerjük, így nem használhatóak ütközésvizsgálathoz, térfogatszámításhoz.
* Manapság a szerkesztés egy közbülső lépéseként használatos.

Felületmodell
-------------

* A modellezett objektumot a határoló felületekkel írjuk le. Felület foltokat illesztünk egymáshoz.
* A modellezési mód a topológiai információkat nem kezeli. Külön vizsgálatokat igényel, hogy összefüggő, folytonos, továbbá, hogy zárt felületről van-e szó.
* A megjelenítési módja már jobban közelíti a valóságot. Használhatunk árnyalást, árnyékokat, textúrákat.

Palástmodell
------------

* Angol neve: *Boundary Representation*, vagy röviden *B-rep*.
* Az objektumokat véges, zárt burok formájában (mint palástot) írja le (többségében) poliéderes közelítéssel.
* Feltételezi, hogy a fizikai modellnek véges, zárt felülete van.
* A modellt topológia szempontjából is teljeskörűen jellemzi.
* Alkalmas például szimulációkhoz, végeselemes háló készítéséhez.

Fajtái:
* *poliéderes palástmodell*: sík lapokkal (például háromszögmodell) írja le,
* *valósághű palástmodell*: tetszőleges felületek használhatóak a pontosabb közelítés érdekében.

Testmodell
----------

* Nevezik még térfogat-modellezésnek vagy CSG-modellezésnek.
* A modellt véges, zárt ponthalmazként írja le.
* Absztrakció szintjén lényegesen egyszerűbb, mint az előzőekben felsorolt módszerek.

.. seealso::

  * http://old.bgk.uni-obuda.hu/ggyt/targyak/seged/bagca15nlc/

CSG modellezés
==============

*Constructive Solid Geometry*

Tegyük fel, hogy testeket modellezünk, és azokat implicit függvények alakjában ismerjük, méghozzá úgy, hogy a függvény megadja, hogy egy adott pont a testhez tartozik-e vagy nem.

* Mivel a függvény értéke egy logikai érték, ezért azon értelmezhetjük a logikai műveleteket.
* A testeket, mint ponthalmazokat tekintve a szokásos halmazműveleteket alkalmazhatjuk.

Ilyen jellegzetes műveletek az unió (:math:`\cup`), a metszet (:math:`\cap`) és a különbség (:math:`\setminus`).

Több műveletet halmazműveletekből alkotott kifejezésként fogalmazhatunk meg. A kifejezéseket faként is reprezentálhatjuk, amely így mutatja a modell elkészítésének a folyamatát.

* Ezt a fát nevezzük CSG fának.
* Mivel kétváltozós műveletekre hagyatkozunk, ezért ez egy bináris fa lesz.

Ahhoz, hogy ilyen módon modellezni tudjunk, szükségünk van geometriai alapelemekre (primitívekre). Ezek jellemzően például a következők:

* téglatest,
* sokszög alapú hasáb,
* gúla,
* henger,
* gömb,
* kúp.

A modellezéshez geometriai transzformációkat is használhatunk.

* A modellezési mód sugárkövető algoritmusokkal hatékonyan használható.
* A megjelenítéshez általánosan háromszöghálóvá (mesh) kell konvertálni a létrejött modellt.
* A megközelítés előnyös, hogy ha a modellezett objektumot megmunkálással szeretnénk elkészíteni.

.. seealso::

  * https://en.wikipedia.org/wiki/Constructive_solid_geometry

Metaball modellezés
===================

* https://en.wikipedia.org/wiki/Metaballs

Volumetrikus modellezés
=======================

Raszteres felbontásra épülő modellezést síkbeli és térbeli objektumok modellezése kapcsán is egyaránt használhatunk.

Háromdimenziós esetben, hogy ha egy rácsfelbontáson belül a cellák bizonyos tulajdonságainak a megadásával modellezzük az objektumokat, azt általában volumetrikus modellezésnek vagy voxel grafikának szokták nevezni.

.. seealso::

  * https://en.wikipedia.org/wiki/Voxel


Modellező szoftverek
====================

* Blender: https://www.blender.org/
* FreeCAD: https://www.freecad.org/
* Wings 3D: https://www.wings3d.com/

További feladatok
=================

* Készítsünk egy programot, amely egyszerű sugárkövetéses módszerrel képes CSG színterek renderelésére!
* Próbáljunk meg közelítést adni felületekre metaball modellezés segítségével!

