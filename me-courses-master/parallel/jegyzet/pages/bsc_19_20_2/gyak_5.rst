5. gyakorlat
============

Tűz szimuláció
--------------

* A Barrier-technika szemléltetéséhez készítsünk egy tűz szimulációs szoftvert!
* Tegyük fel, hogy tűznek a lángjait szeretnénk szimulálni. A teret diszkretizáljuk úgy, hogy az aktuális hőmérsékletet egy :math:`T \in \mathbb{R}^{n \times m}` méretű mátrixba tároljuk. Feltételezzük, hogy a hő felfelé (a nagyobb indexű soroktól az alacsonyabbak felé) terjed.
* A peremfeltételek a mátrix alsó és oldalsó részein adottak. A bal- és jobb oldali szélen konstans 0-nak tekintjük.
* A hőmérséklet értékeket a :math:`(k+1)`-edik iterációban a következő összefüggés szerint számolhatjuk:

.. math::

   T_{i, j}^{(k + 1)} = \dfrac{
   T_{i, j}^{(k)} + T_{i + 1, j - 1}^{(k)} + T_{i + 1, j}^{(k)} + T_{i + 1, j + 1}^{(k)}
   }{4.05}.

* Készítsünk olyan párhuzamosított programot MultiPascal-ban, amelyik a :math:`T` mátrix utolsó soraként megadott értékek alapján kiszámítja a teljes mátrixot!
* A bemeneteket egy fájlból olvassuk be!
* A mátrixban lévő adatokat alulról-felfelé kell kitölteni.
* A barrier-re azért van szükség, mert úgy tekintjük, hogy egy sort csak az alatta lévő sor adatai alapján tudunk kiszámítani.
* A barrier megvalósítható CHANNEL változó vagy SPINLOCK segítségével is.

.. note::

   Szekvenciális JavaScript változat:
   https://www.uni-miskolc.hu/~matip/_downloads/fire.html
