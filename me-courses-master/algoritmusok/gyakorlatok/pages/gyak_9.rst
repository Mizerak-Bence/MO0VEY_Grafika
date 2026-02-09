9. Rendező algoritmusok I.
==========================

Beszúró rendezés
----------------

Rendezzük a következő sorozatot!

.. math::

    A = [24, 14, 57, 34, 81, 11, 28]

* Mi a legrosszabb esete a beszúró rendezésnek?
* Hogyan változna az algoritmus, hogy ha a beszúrást mindig a sorozat elejétől kezdenénk?

Minimum kiválasztásos rendezés
------------------------------

Rendezzük a következő sorozatot!

.. math::

    A = [53, 27, 16, 44, 8, 37, 12]

* Hogyan tudnánk röviden megfogalmazni, hogy mi a lényegi különbség a beszúró rendezés és a minimumkiválasztásos rendezés között?

.. A beszúró rendezésnél azt tudjuk, hogy mit szúrunk be, és azt keressük, hogy hova, a minimumkiválasztásos rendezésnél pedig azt tudjuk, hogy hova, és azt keressük, hogy mit.

* Mi a legrosszabb esete a minimumkiválasztásos rendezésnek?
* Hogyan változna az algoritmus, hogy ha ugyancsak növekvő sorrendet szeretnénk elérni, viszont maximum keresést szeretnénk használni hozzá?

Buborékrendezés
---------------

Rendezzük buborékrendezéssel a következő sorozatot!

.. math::

    A = [51, 80, 15, 64, 31, 19]

* Mennyi csere volt a rendezés végrehajtása során?
* Mi a legrosszabb esete a buborék rendezésnek?
* Milyen változatai lehetnek a buborékrendezés algoritmusának?

Shell rendezés
--------------

*Fogyó növekménnyel*

Legyenek a növekményeink :math:`h = 4, 2, 1`. Rendezzük a következő sorozatot!

.. math::

    A = [73, 25, 38, 29, 14, 41, 26]

* Mennyi csere volt a művelet végrehajtása során?
* Hasonlítsuk össze az eredményt a buborékrendezéssel!

Összefésülő rendezés
--------------------

Fésüljük össze az alábbi sorozatokat!

.. math::

    A = [12, 30, 34, 51, 70, 80], \quad
    B = [8, 14, 17, 32, 75]

* Mennyi összehasonlítás volt szükséges a művelet elvégzéséhez?
* Mit feltételeztünk az összefésüléskor az összefésülendő sorozatokra nézve?

Vizsgáljuk meg az összefésülés algoritmusát az :math:`\text{ÖSSZEFÉSÜL}(A, p, q, r)` esetében!

* Mit jelentenek benne a paraméterek?
* Milyen az algoritmus időbonyolultsága?

Összefésülő rendezéssel rendezzük a következő sorozatot!

.. math::

    A = [55, 17, 10, 84, 39, 62, 8, 47]

* Az összefésülés menetét ábrázoljuk gráfon!

Batcher-féle páros-páratlan összefésülés
----------------------------------------

* Nézzük meg a Batcher-féle páros-páratlan összefésülést az előbbi, összefésüléses példára!
* Mennyiben változott az összehasonlítások száma?
