6. Gyakorló feladatok
=====================

Példa sor tömbös reprezentációjára
----------------------------------

Foglaljunk le egy sor számára egy 6 elemű tömböt.

* Tartsuk nyilván a fej[:math:`Q`] és a vége[:math:`Q`] értékeket! (Mindkettőt állítsuk kezdetben 1-re!)
* Végezzük el az alábbi beszúrásokat és törléseket!

50, 38, 26, T, 40, 82, T, T, 75, 41, T, 29

* Ezt követően mi lesz a fej[:math:`Q`] és a vége[:math:`Q`] értéke?
* Milyen értékek találhatók a tömbben a 2-es és 3-mas indexeken?
* Mennyi elemünk van összesen a sorban?
* Mennyi elemet tudunk még beszúrni a sorba?

Példa verem tömbös reprezentációjára
------------------------------------

Foglaljunk le egy veremnek egy 4 elemű tömböt, majd végezzük el az alábbi műveleteket!

12, 8, 3, T, T, 7, 9, 5, T

* Mennyi lesz a tömbben lévő értékek összege?

Láncolt lista tömbben
---------------------

Foglaljunk le egy 5 elemű tömböt egy duplán láncolt lista elemeinek tárolásához!

* Tegyük fel, hogy egy elem beszúrásakor az utoljára beszúrt elem után következő szabad helyet választjuk! Kezdetben az elsőt elemet tekintjük szabadnak. Amennyiben a tömb végére értünk, az elején folytatjuk a keresést.
* Végezzük el a következő  műveleteket!

63, 42, 15, 84, T42, 79, T15, 22, 18, T63, T18, 98

* Mennyi eleme van az így kapott listának?
* Mennyi a tömbben előforduló kulcsértékek minimuma?
* Mi a fej[:math:`L`] és a vége[:math:`L`] értéke?

Végezzük el az előbbi műveletsort úgy, hogy a szabad helyek nyilvántartásához egy külön láncolt listát használunk!

Lista elemeinek sorrendjének megfordítása
-----------------------------------------

Hogyan tudjuk megfordítani egy lista elemeinek a sorrendjét!

* Írjunk fel hozzá iteratív és rekurzív algoritmust is!

Hurok vizsgálata listában
-------------------------

Hogyan tudjuk ellenőrízni, hogy egy láncolt listában van-e hurok?

Feloszt eljárást
----------------

.. math::
   \begin{align*}
   &\text{FELOSZT}(@A, p, r, x, @q) \\
   &\quad i \leftarrow p - 1 \\
   &\quad j \leftarrow r + 1 \\
   &\quad \text{WHILE IGAZ DO} \\
   &\quad \quad \text{REPEAT } j \leftarrow j - 1 \\
   &\quad \quad \quad \text{UNTIL } A_j \leq x \\
   &\quad \quad \text{REPEAT } i \leftarrow i + 1 \\
   &\quad \quad \quad \text{UNTIL } A_i \geq x \\
   &\quad \quad \text{IF } i < j \\
   &\quad \quad \quad \text{THEN Csere } A_i \leftrightarrow A_j \\
   &\quad \quad \quad \text{ELSE } q \leftarrow j \\
   &\quad \quad \quad \quad \quad \quad \text{RETURN}(A, q) \\
   \end{align*}

Végezzük el a következő procedúrahívást!

.. math::

   \text{FELOSZT}(A, 1, 13, 28, q)

ahol

.. math::

   A = [17, 127, 20, 45, 81, 3, 10, 49, 50, 28, 12, 81, 9]

* Mennyi a kapott :math:`q` érték?
* Mennyi csere volt a művelet végrehajtása közben?

Lineáris keresés, rekurzív változat
-----------------------------------

* Írjuk meg a lineáris keresés rekurzív változatát tömbre és listára is!
* Vizsgáljuk meg ezek hatékonyságát!

Rekurzív maximum számítása
--------------------------

* Készítsünk rekurzív procedúrát egy tömb maximális értékének a meghatározásához!
* Vizsgáljunk meg több alternatívát is!

Bináris keresés
---------------

* Módosítsuk a bináris keresés algoritmusát balról zárt, jobbról nyitott intervallumra!
* Nézzük meg az iteratív és a rekurzív változatot!
* Készítsünk rá számítási példát!
* Vizsgáljuk meg az :math:`[i, j]` és az :math:`[i, j)` intervallumos változat hatékonyságát!

