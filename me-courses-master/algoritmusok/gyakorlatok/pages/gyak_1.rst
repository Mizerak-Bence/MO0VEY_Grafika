1. Számrendszerek, számábrázolás
================================

Elemi műveletek
---------------

Alsó- és felsőegészrész függvények:

.. math::

   \lfloor x \rfloor = \max_{k \leq x, k \in \mathbb{Z}} k,
   \quad
   \lceil x \rceil = \min_{k \geq x, k \in \mathbb{Z}} k,


Kerekítés és törtrész függvények:

.. math::

   \text{Round}(x) = \left\lfloor x + \dfrac{1}{2} \right\rfloor,
   \quad
   \{x\} = x - \lfloor x \rfloor

Egész hányados képzése (``div``):

.. math::

   a \text{ div } b =
   \left\lfloor \dfrac{a}{b} \right\rfloor,
   \quad b \neq 0,

Egész maradék képzése (``mod``):

.. math::

   a \text{ mod } b =
   \begin{cases}
       a, & b = 0 \\
       a - \left\lfloor \dfrac{a}{b} \right\rfloor \cdot b, & b \neq 0. \\
   \end{cases},
   \quad
   a \text{ mod } 1 = \{a\}

.. note::

   Mi ezen függvényeknek az értelmezési tartománya és az értékkészlete?


Számítsuk ki a következő értékeket!

* :math:`\lceil 4.4 \rceil`, :math:`\lfloor -10.3 \rfloor`, :math:`\left\lfloor \dfrac{7}{6} \right\rfloor`, :math:`\left\lceil -\dfrac{51}{4} \right\rceil`,
* :math:`\text{Round}\left(-4.8\right)`, :math:`\text{Round}\left(11\right)`, :math:`\text{Round}\left(\dfrac{23}{2}\right)`, :math:`\text{Round}\left(3.2\right)`, :math:`\text{Round}\left(-8.5\right)`
* :math:`\left\{ \dfrac{30}{7} \right\}`, :math:`\{0.95\}`, :math:`\{-7.18\}`, :math:`\{\pi\}`, :math:`\{-\pi\}`
* :math:`41 \text{ div } 3`, :math:`41 \text{ div } 22`, :math:`972 \text{ mod } -17`, :math:`-593 \text{ mod } 61`
* :math:`50 \text{ div } 9`, :math:`-50 \text{ div } 9`, :math:`50 \text{ div } (-9)`, :math:`-50 \text{ div } (-9)`
* :math:`50 \text{ mod } 9`, :math:`-50 \text{ mod } 9`, :math:`50 \text{ mod } (-9)`, :math:`-50 \text{ mod } (-9)`

Ábrázoljuk a következő függvényeket!

* :math:`f(x) = \{\sqrt{x}\}`
* :math:`f(x) = \text{Round}(\sin(x))`
* :math:`f(x, y) = \{(x, y) \in \mathbb{R}^2 \;|\; \{x\} + \{y\} = 0.5\}`
* :math:`f(x, y) = \{(x, y) \in \mathbb{R}^2 \;|\; \lfloor x \rfloor > \lceil y \rceil\}`


Egész számok ábrázolása
-----------------------

* Váltsuk át a 139-et kettes számrendszerbe!
* Ellenőrízzük a számítást helyiértékes formában és Horner sémával!
* Írjuk fel a 3825-öt 2, 3, 4, 7, 9, 13, 16-os számrendszerekben!


Számjegyek számáról szóló tétel
-------------------------------

.. math::

   n + 1 = \left\lfloor \log_b x \right\rfloor + 1

* A tétel segítségével ellenőrízzük, hogy a 3825 mennyi számjegyből fog állni a különböző számrendszerekben!
* Mennyi számjegyből fog állni a 8182331 szám 7-es számrendszerben?


Orosz paraszt módszer
---------------------

Orosz paraszt módszerrel szorozzuk össze a 65 és 61 számokat!

.. csv-table::
   :header-rows: 1

   szorzandó,szorzó,páratlan?,szorzat
   65,51,igen,0+65=65
   130,25,igen,65+130=195
   260,12,nem,195
   520,6,nem,195
   1040,3,igen,195+1040=1235
   2080,1,igen,1235+2080=3315

* Hogyan működik az algoritmus?
* Hogyan érdemes implementálni a szorzást számítógépen?


Kettes komplemens
-----------------

* Ábrázoljuk a -50, -1896, -1, 127, -128 számokat kettes komplemens ábrázolási móddal!
* A -1896 értékhez adjunk hozzá 3825-öt, úgy hogy kettes számrendszerben számítjuk ki az összeget!


Törtek átírása
--------------

* Írjuk át a 0.73438, -0.10546875, 0.953125 törteket kettes számrendszerbe!
* Írjuk át a 0.7, 0.175, 9.11 törteket kettes számrendszerbe!


Egyszeres lebegőpontos ábrázolás
--------------------------------

* Ábrázoljuk a 4440.46875 számot az egyszeres lebegőpontos szabvány szerint!
* Ábrázoljuk a -0.3 értéket!
* Milyen értéket ábrázolnak egyszeres pontosság esetén az ``12340000`` illetve az ``FE820000`` bájtok?
* Ábrázoljuk a :math:`\pm 0` értékeket egyszeres lebegőpontos ábrázolással!
* Adjunk példát denormalizált számra, és nem számra!
* Összesen mennyi féle értéket tudunk ábrázolni egyszeres, és kétszeres pontosság esetén?

