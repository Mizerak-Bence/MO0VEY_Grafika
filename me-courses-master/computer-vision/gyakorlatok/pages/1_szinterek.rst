1. Színterek
============

Képek betöltése
---------------

.. todo::

   Töltsünk be egy képet, majd jelenítsük meg!

.. todo::

   Vágjuk ki a kép egyes részeit slice operátorral!


RGB
---

* A leginkább elterjedt változat.
* A csatornák intenzitástartománya változhat. Nem feltétlenül :math:`[0, 255]` minden esetben.
* OpenCV esetén BGR vagy egyéb változat is előfordulhat.

.. todo::

   Szedjünk szét egy képet csatornákra, majd jelenítsük azokat meg, mint külön képeket!

.. todo::

   Készítsünk 3 szürkeárnyalatos képet, majd rakjunk össze belőle egy színes, RGB változatot!


HSV
---

* https://en.wikipedia.org/wiki/HSL_and_HSV


Színtér transzformáció
----------------------

* https://docs.opencv.org/master/df/d9d/tutorial_py_colorspaces.html

.. todo::

   Készítsünk példát RGB :math:`\rightarrow` HSV transzformációra!


Szín műveletek
--------------

* A színek átlagolhatók, negálhatók.
* A színek között távolságok számíthatók.

.. todo::

   Készítsünk egy programot, amelyik :math:`10 \times 10` méretű blokkonként átlagolja a képet!


Képek simítása
--------------

* Mérőeszközzel készített képek esetén gyakorlatilag mindig csak zajos képekről beszélhetünk.
* A pontszerű zajokat valamilyen szűrővel, simítással tudjuk eltávolítani.
* Jellemzően valamilyen kernelt használhatunk arra, hogy konvolúcióval végig menjünk az összes képponton.

https://docs.opencv.org/master/d4/d13/tutorial_py_filtering.html

.. todo::

   Egy aránylag zaj mentes képhez adjunk mesterségesen hozzá pontszerű zajokat, majd próbáljuk meg azokat medián szűrővel eltávolítani!

