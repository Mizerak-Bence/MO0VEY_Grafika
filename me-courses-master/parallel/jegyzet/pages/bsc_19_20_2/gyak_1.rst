1. gyakorlat
============

Komplexitás
-----------

Feladatok
~~~~~~~~~

* Milyen jellegzetes növekedési rendeket ismerünk?
* Az első előadás anyagában mit jelölnek a :math:`A, \mathcal{A}, E, B, D, m, N, n, W, \mathcal{P}` betűk?
* Mit nevezünk munkának és gyorsításnak (*speedup*)?
* A *speedup* milyen intervallumon változhat?
* Egy probléma megoldására 2 algoritmus áll rendelkezésre. Az egyik :math:`T_A(n) = n^2 + 10` futási időket ad, a másik pedig :math:`T_B(n) = 4n + 200` időket. Az :math:`n` a bemenet méretét jelöli, alsó indexben pedig az algoritmus neve szerepel. Melyiket érdemes használni? Mit tudunk mondani ordó szimbólumok segítségével a két algoritmus bonyolultságáról?
* Melyik algoritmust érdemes használni, hogy ha az egyik :math:`T_A(n) = \left(\dfrac{n}{16}\right)^4 + 8` futási időt ad, a másik pedig :math:`T_B(n) = \sqrt{8n}` időt? Mit tudunk mondani ordó szimbólumok segítségével a két algoritmus bonyolultságáról?

DosBox
------

Gyökérkönyvtár felcsatolása:

.. code-block:: shell

   mount c ..


Jegyzékben lévő állományok újraolvastatása:

.. code-block:: shell

   RESCAN


``Ctrl-F4``-el szintén megoldható.


Pascal
------

A programokat nem kell külön fordítani. A ``multi.exe``-t paraméter nélkül lehet indítani, majd ott helyben kell megadni a futtatandó állomány nevét. A programot ezt követően a ``run`` paranccsal lehet elindítani.

Feladatok
~~~~~~~~~

* Tekintsük át a példakódokat!
* Készítsünk egy tipikus *Hello, World!* alkalmazást és futtassuk le!
* Definiáljunk változókat, majd kéressük be az értéküket! Legyen közöttük egész, valós és szöveges típusú is! Írassuk ki az értékeket! Nézzük meg mi történik érvénytelen formátumú bemenet esetén!
* Írassuk ki egy ``FOR`` ciklusban szövegeket, úgy hogy a kiírt szövegben szerepel, hogy éppen hanyadik iterációnál jár a program!
* Készítsük el ennek párhuzamosított változatát a ``FORALL`` vezérlési szerkezet segítségével!
* Készítsünk példákat a ``/list``, ``/input`` és ``/output`` argumentumok használatára!
* Írjunk egy programot, amely egy fájlból beolvassa a benne lévő számokat, majd kiírja azok összegét!
* Készítsünk egy programot, amely 7-től 50-ig lépteti egy változó értékét 11-essével! Töréspont segítségével állítgassuk meg a programot abban az esetben, ha a változó értéke páros!

