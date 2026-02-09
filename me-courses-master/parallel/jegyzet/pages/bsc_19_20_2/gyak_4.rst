4. gyakorlat
============

Összefésülés
------------

* Vizsgáljuk meg, hogy milyen módon párhuzamosítható az összefésülés algoritmusa!
* Nézzük meg a `merge` nevű mintaprogram megoldását!


Termelő-fogyasztó probléma
--------------------------

.. code-block:: pascal

   VAR chan: CHANNEL OF INTEGER;


* Készítsünk egy programot, amelyben egy *Publisher* egész számokat tesz közzé, majd a *Subscriber* annyi műveletet végez el, amennyi a kapott számértékben szerepel. (Azért annyit, hogy változatosak legyenek a számítási idők.) Tegyük fel, hogy összesen 5 ilyen üzenet lesz!
* Módosítsuk a programot úgy, hogy két *Publisher* is van!
* Módosítsuk a programot úgy, hogy két *Subscriber* fut párhuzamosan!
* Kombináljuk az előző kettőt!


Pipeline párhuzamosítás
-----------------------

* Vizsgáljuk meg a Fibonacci sorozat elemeit számító programot!
* Készítsünk egy olyan programot, amelyik egy egész számnak kiszámítja a nála kisebb, legnagyobb osztóját, meghatározza annak a köbét, majd kiszámítja annak négyzetgyökét! Adjuk meg a programot szekvenciális és pipeline-al történő párhuzamosítás formájában! Írassuk ki az egyes részeredményeket futás közben!


Zárolási mechanizmusok
----------------------

* Készítsünk példát a *Lost update* problémára, majd javítsuk ki `SPINLOCK` segítségével!
* Készítsünk olyan példát, amelyben a lock használata feleslegesen rontja a számítási teljesítményt! (Például tömb elemeihez való hozzáférés kapcsán.)
* Nézzük meg a hisztogram és a közelítő integrál számításához tartozó párhuzamos algoritmusokat!

