8. Sztring műveletek
====================

Minimumkeresés
--------------

* Mennyi a minimumkeresés időbonyolultsága?
* Ha nem feltételezünk rendezettséget, akkor hogyan lehet javítani az algoritmus számítási idején?

Tegyük fel, hogy adott egy páros elemszámú tömbünk. Számítsuk ki ennek a minimumát és a maximumát!

* Vizsgáljuk meg a külön-külön történő számításból adódó algoritmust és annak futási idejét!
* Írjuk fel az előadásban javasolt algoritmus pszeudó kódját, és nézzük meg a működését az alábbi példát!

.. math::

	X = [8, 4, 3, 6, 5, 2, 3, 9, 1, 7, 2, 4]

Feloszt eljárás
---------------

Osszuk fel az alábbi tömb elemeit az 50-es érték körül!

.. math::

	A = [11, 82, 20, 70, 65, 30, 12, 53]

* Mennyi cserére volt szükség az algoritmus végrehajtása során?
* Mi a kapott :math:`q` érték?
* Mennyi volt a cserék során az :math:`i` és :math:`j` indexek különbségének maximuma?

Sztring műveletek
-----------------

Konkatenálás
~~~~~~~~~~~~

* Írjuk fel a sztringek konkatenálásának egy lehetséges procedúrájának pszeudó kódját!
* Adjunk egy példát, amin megnézhetjük az algoritmus működését!
* Milyen a számítási ideje az algoritmusnak?

Részsztring törlése
~~~~~~~~~~~~~~~~~~~

Készítsünk egy procedúrát, amelyik szövegből egy adott részt képes törölni (kivágni)!

* Vizsgáljuk meg a részsztring megadásának lehetséges módjait!
* Írjuk fel a procedúra pszeudókódját!
* Egészítsük ki hibaellenőrzéssel!

Részsztring keresése
--------------------

Keressük meg a "``kllm``" szöveget a "``ktlkkllzkllmzt``" szövegben!

* Egyeztessük a jelöléseket!
* Használjuk hozzá a *Brute force* algoritmust!

Prefix és postfix
-----------------

Készítsünk egy algoritmust, amelyik egy adott :math:`A` alapsztringről meg tudja állapítani, hogy annak egy :math:`P` sztring valódi prefixe/szuffixe-e!

Maximális border meghatározása
------------------------------

* Készítsünk egy algoritmust, amely képes megkeresni egy szövegben a maximális border értékét! (:math:`b = ?`)
* Becsüljük meg az algoritmus számítási idejét!
* Vizsgáljuk meg az algoritmus működését a "``cabcxabbxacab``" szöveg példáján keresztül!
* Mennyi a maximális border értéke?
* Mennyi karakterösszehasonlításra volt szükség az algoritmus végrehajtása során?

A :math:`KÖV` tömb számítása
----------------------------

Számítsuk ki a :math:`KÖV` tömb értékét a "``cdecdecd``" sztring esetében!

.. csv-table::

	:math:`i`,0,1,2,3,4,5,6,7,8
	:math:`p[i]`,,c,d,e,c,d,e,c,d
	:math:`KÖV[i]`,,,,,,,,

* Hasonlóképpen vizsgáljuk meg az "``xyxzxxy``" szöveget is!

Knuth-Morris-Pratt algoritmus (KMP)
-----------------------------------

* A KMP algoritmus segítségével keressük meg a "``cdecd``" szöveget az "``edecdcdecdee``" szövegben!
* Hasonlítsuk össze a szükséges számítási lépések számát a *Brute force* algoritmuséval!

.. csv-table::

	:math:`i`,0,1,2,3,4,5,6,7,8,9,10,11,12
	:math:`A[i]`,,e,d,e,c,d,c,d,e,c,d,e,e

Nézzük meg a további példákat is!

.. csv-table::
	:header-rows: 1
	
	alapsztring,minta
	``stuuttustuttuttst``,``uttutt``
	``zttzztttztzztz``,``tztz``
	``ijmmjmimjjmiimm``,``jmii``
