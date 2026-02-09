5. Osztályozás
==============

* A jellegvektorok kinyerését (*feature extraction*) követően képfeldolgozástól függetleníthető probléma.
* Az osztályozó jellemzően egy :math:`f: \mathbb{R}^n \rightarrow \mathbb{N}` függvénykapcsolatot valósít meg.
* Az osztályozás megbízhatóságát a helyes, helytelen, fals pozitív és fals negatív esetek aránya jellemzi.

.. note::

   Az osztályozást akkor egyszerűbb elvégezni, hogy ha jellegvektorok terének a dimenziója alacsony, de a jellegkinyerés során nem veszett el sok információ.


Átlagos esettől való távolság
-----------------------------

* Amennyiben feltételezhetjük, hogy az átlagos esetek jól jellemzik az osztályokat (egyfajta osztály középpontoknak tekinthetjük őket), egy adott jellegvektorhoz megkereshetjük a legközelebbi osztályt.
* Az osztálytól vett távolságot normalizálva osztályhoz való hozzátartozási mértékként kezelhetjük.

.. todo::

   Készítsünk egy osztályozót, amelyik zebrák és lovak képeit tudja elkülöníteni!

