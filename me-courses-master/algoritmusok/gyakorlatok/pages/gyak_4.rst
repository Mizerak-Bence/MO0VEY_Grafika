4. Számelméleti algoritmusok
============================

Legnagyobb közös osztó
----------------------

* Definiáljuk a legnagyobb közös osztót, és az ahhoz szükséges fogalmakat!
* Határozzuk meg a 90 és a 24 legnagyobb közös osztóját!

*Prímtényezős felbontás*

.. math::

    90 = 2 \cdot 3^2 \cdot 5, \quad
    24 = 2^3 \cdot 3
    \quad \Rightarrow \quad
    \text{lnko}(90, 24) = 6


*Redukciós tétel*

.. math::

    \text{lnko}(a, b) = \begin{cases}
    a, & \text{ ha } b = 0, \\
    \text{lnko}(a - b, b), & \text{ ha } b \neq 0,
    \end{cases}
    \quad a \geq b.

.. math::

    \text{lnko}(90, 24) =
    \text{lnko}(66, 24) =
    \text{lnko}(42, 24) =
    \text{lnko}(18, 24) =
    \text{lnko}(24, 18) =

.. math::

    \text{lnko}(6, 18) =
    \text{lnko}(18, 6) =
    \text{lnko}(12, 6) =
    \text{lnko}(6, 6) =
    \text{lnko}(0, 6) =
    \text{lnko}(6, 0) =
    6

* Mennyi lépésből fog állni lnko(1000000, 1) kiszámítása?
* Milyen esetben adja a leggyorsabb, és a leglassabb megoldást?


Bináris LNKO
------------

* Definiáljuk a Bináris Legnagyobb Közös Osztó algoritmusát!
* Számítsuk ki a 90 és 24 legnagyobb közös osztóját 10-es és 2-es számrendszeri felírással!


Euklideszi algoritmus
---------------------

.. math::

    \text{lnko}(a, b) = \begin{cases}
        a, & \text{ ha } b = 0, \\
        \text{lnko}(a, a \text{ mod } b), & \text{ ha } b \neq 0
    \end{cases}


.. csv-table::
   :header-rows: 1

   a, b, a div b, a mod b
   90,24,3,18
   24,18,1,6
   18,6,3,0
   6,0,-,6


* Az Euklideszi algoritmusnak mi a legrosszabb esete?


Lamé tétele
-----------

Ha :math:`a > b \neq 0`, és :math:`b < F_{k+1}`, akkor az Euklideszi algoritmus rekurzív hívásainak száma kevesebb, mint `k`.

* Legfeljebb mennyi rekurzív hívás szükséges az lnko(283799, 76511) kiszámításához?

.. math::

   b = 76511 < F_{k+1}, \quad
   F_n = \text{Round}\left( \dfrac{1}{\sqrt{5}} \Phi^n \right), \quad
   76511 = \dfrac{1}{\sqrt{5}} \Phi^n

.. math::

   \Rightarrow \quad
   n = \log_{\Phi} \sqrt{5} \cdot 76511 \approx 25.04076

.. math::

   F_{25} = 75025, \quad F_{26} = 121393

.. math::

   b < F_{25+1} \quad \Rightarrow \quad k = 25


Legfeljebb 24 rekurzív hívás szükséges!


A legnagyobb közös osztó reprezentációs tétele
----------------------------------------------

.. math::

   d^{*} = \text{lnko}(a, b) = \min_{s \in L(a, b), s > 0} s = a \cdot x^{*} + b \cdot y^{*} = s^{*}

.. csv-table::
   :header-rows: 1

   :math:`a`,:math:`b`,:math:`a \text{ div } b`,:math:`a \text{ mod } b`,:math:`d^{*}`,:math:`x^{*}`,:math:`y^{*}`
   133,157,0,133,1,-72,:math:`61 - (-72) \cdot 0 = 61`
   157,133,1,24,1,61,:math:`-11 - 61 \cdot 1 = -72`
   133,24,5,13,1,-11,:math:`6 - (-11) \cdot 5 = 61`
   24,13,1,11,1,6,:math:`-5 - 6 \cdot 1 = -11`
   13,11,1,2,1,-5,:math:`1 - (-5) \cdot 1 = 6`
   11,2,5,1,1,1,:math:`0 - 1 \cdot 5 = -5`
   2,1,2,0,1,0,:math:`1 - 0 \cdot 2 = 1`
   1,0,-,1,1,1,0


.. math::

   133 \cdot (-72) + 157 \cdot 61 = 1

Lineáris kongruencia egyenlet
-----------------------------

**Kongruencia**: :math:`a \equiv b \mod n`

:math:`a` kongruens :math:`b`-vel az :math:`n` modulusra nézve, ha :math:`n`-nel osztva :math:`a` és :math:`b` azonos maradékot ad.

Például: :math:`11 \equiv 7 \mod 4, \quad 712 \equiv 312 \mod 10`

.. math::

   a \equiv b \mod n \quad \Leftrightarrow \quad n | a - b

**Lineáris kongruencia egyenlet**:

.. math::

   a \cdot x \equiv b \mod n, \quad x = ?

Két eset:

* Nincs megoldás, ha :math:`\text{lnko}(a, n) \nmid b`
* Végtelen sok megoldás van, ha :math:`\text{lnko}(a, n) | b`

alaprendszer:

.. math::

   x_0 = x^{*} \cdot \dfrac{b}{d^{*}} \mod n, \quad
   x_i = i \cdot \dfrac{n}{d^{*}} \mod n, (i = 1, \ldots, d^{*} - 1), \quad
   0 \leq x_i < n


* Oldjuk meg a :math:`84x \equiv 16 \mod 44` egyenletet!
* Ellenőrízzük a megoldást!


Multiplikatív inverz
--------------------

Jelölése: :math:`a^{-1} \mod n` (Az :math:`a` multiplikatív inverze az :math:`n` modulusra nézve.)

:math:`x = a^{-1} \mod n`, ha :math:`a \cdot x \equiv 1 \mod n`.

* Ha :math:`\text{lnko}(a, n) \neq 1`, akkor nincs megoldás.
* Ha :math:`\text{lnko}(a, n) = 1`, (tehát :math:`a`, :math:`n` relatív prímek), akkor végtelen sok megoldás van, melynek alaprendszere: :math:`x_0 = x^{*} \mod n`

Feladat:

* Határozzuk meg 21 multiplikatív inverzét a 32-es modulusra nézve! :math:`21^{-1} \mod 32 = ?`

.. csv-table::
   :header-rows: 1

   :math:`a`,:math:`b`,:math:`a \text{ div } b`,:math:`a \text{ mod } b`,:math:`d^{*}`,:math:`x^{*}`,:math:`y^{*}`
   21,32,0,21,1,-3,:math:`2 - (-3) \cdot 0 = 2`
   32,21,1,11,1,2,:math:`-1 - 1 \cdot 1 = -3`
   21,11,1,10,1,-1,1 - (-1) \cdot 1 = 2`
   11,10,1,1,1,1,:math:`0 - 1 \cdot 1 = -1`
   10,1,10,0,1,0,:math:`1 - 0 \cdot 10 = 1`
   1,0,-,1,1,1,0

.. math::

   21^{-1} \mod 32 = 29

Moduláris hatványozás
---------------------

.. math::

   a^b \mod n = ?

Határozzuk meg a :math:`98^{3114} \mod 150` értékét!

.. math::

   3114_{10} = 110000101010_{2}

.. csv-table::
   :header-rows: 1

   :math:`k`,:math:`b_k`,:math:`c^2 \mod n`,:math:`(c \cdot a) \mod n`
   11,1,:math:`1^2 = 1 \equiv 1`,:math:`1 \cdot 98 = 98 \equiv 98`
   10,1,:math:`98^2 = 9604 \equiv 4`,:math:`4 \cdot 98 = 392 \equiv 92`
   9,0,:math:`92^2 = 8464 \equiv 64`,-
   8,0,:math:`64^2 = 4096 \equiv 46`,-
   7,0,:math:`46^2 = 2116 \equiv 16`,-
   6,0,:math:`16^2 = 256 \equiv 106`,-
   5,1,:math:`106^2 = 11236 \equiv 136`,:math:`136 \cdot 98 = 13328 \equiv 128`
   4,0,:math:`128^2 = 16384 \equiv 34`,-
   3,1,:math:`34^2 = 1156 \equiv 106`,:math:`106 \cdot 98 = 10388 \equiv 38`
   2,0,:math:`38^2 = 1444 \equiv 94`,-
   1,1,:math:`94^2 = 8836 \equiv 136`,:math:`136 \cdot 98 = 13328 \equiv 128`
   0,0,:math:`128^2 =16384 \equiv 34`,-

.. math::

   98^{3114} \mod 150 = 34

Fermat-féle álprímteszt
-----------------------

Ha :math:`2^{p-1} \mod p = 1` akkor :math:`p` lehet prím. Ha :math:`2^{p-1} \mod p \neq 1`, akkor :math:`p` biztosan nem prím.

Vizsgáljuk meg, hogy a 41 prímszám-e!

.. math::

   40_{10} = 101000_{2}

.. csv-table::
   :header-rows: 1

   :math:`b_i`,:math:`c^2 \mod 41`,:math:`2 \cdot c \mod 41`
   1,:math:`1^2 \mod 41 = 1`,:math:`2 \cdot 1 \mod 41 = 2`
   0,:math:`2^2 \mod 41 = 4`,-
   1,:math:`4^2 \mod 41 = 16`,:math:`2 \cdot 16 \mod 41 = 32`
   0,:math:`32^2 \mod 41 = 40`,-
   0,:math:`40^2 \mod 41 = 1`,-
   0,:math:`1^2 \mod 41 = 1`,-

:math:`2^{40} \mod 41 = 1`, így 41 lehet prím.

Vizsgáljuk meg, hogy a 42 prímszám-e!

.. math::

   41_{10} = 101001_{2}

.. csv-table::
   :header-rows: 1

   :math:`b_i`,:math:`c^2 \mod 41`,:math:`2 \cdot c \mod 41`
   1,:math:`1^2 \mod 42 = 1`,:math:`2 \cdot 1 \mod 42 = 2`
   0,:math:`2^2 \mod 42 = 4`,- 
   1,:math:`4^2 \mod 42 = 16`,:math:`2 \cdot 16 \mod 42 = 32`
   0,:math:`32^2 \mod 42 = 16`,-
   0,:math:`16^2 \mod 42 = 4`,-
   1,:math:`4^2 \mod 42 = 1`,:math:`32 \mod 42 = 32`

:math:`2^{41} \mod 42 = 32 \neq 1`, így a 42 nem lehet prím.

RSA algoritmus
--------------

Készítsük el a publikus és a privát kulcsot a következő adatok segítségével!

.. math::

   p = 23, q = 31 \quad \Rightarrow \quad n = p \cdot q = 713

.. math::

   e = 13, \quad f = (p - 1) \cdot (q - 1) = 660

.. math::

   d = e^{-1} \mod f = 13^{-1} \mod 660 = 457

* publikus kulcs: :math:`P = (e; n) = (13; 713)`
* titkos kulcs: :math:`S = (d; n) = (457; 713)`

Kódoljuk az :math:`M = 150` üzenetet!

.. math::

   C = M^{e} \mod n = 150^{13} \mod 713 = 305

Dekódoljuk az előzőekben kódolt :math:`C = 305` értéket!

.. math::

   M = C^{d} \mod n = 305^{457} \mod 713 = 150

