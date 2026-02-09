2. POSIX szálak
===============

Szálak
------

* A segítségükkel ki lehet használni a számítógépben rendelkezésre álló több processzormagot.
* Az I/O-ra várakozás is hasznosan tölthető.
* Gazdaságosabb, mint új processzt indítani.
* A szálak egy közös névtéren osztoznak.
* A szálak nem tartanak nyilvántartást arról, hogy milyen szálakat indítottak, azt nekünk kell megoldani.

A szálak egy processzen belül a következőket osztják meg egymással.

* Memória címtér
* Megnyitott fájlok (fájlleírók)
* Szignálok kezelése
* Az aktuális munkajegyzéket (*cwd*, *pwd*)
* Felhasználó név és csoport (*jogosultságok*)

Minden szálban viszont egyediek az alábbiak:

* Szál azonosító (*Thread ID*)
* Regiszterek, verem mutató
* Lokális változók, visszatérési címek
* Prioritások
* Visszatérési hibakódok


Szál létrehozása és indítása
----------------------------

.. code:: cpp

  int pthread_create(
    pthread_t* thread,
    const pthread_attr_t* attr,
    void *(*start_routine)(void *),
    void *arg);

Paraméterek:

* ``thread``: A szál azonosítója (``unsigned long int`` típus)
* ``attr``: Szál beállításához szükséges attribútumok. (Alapértelmezéshez ``NULL`` érték.)
* ``start_routine``: A függvény, amelyet a szálban el kell indítani.
* ``arg``: Paraméterek, amelyek átadásra kerülnek a szálban indított függvénynek.

Visszatérési érték:

* Amennyiben a szál sikeresen elindult, úgy 0 értékkel tér vissza, egyébként pedig hibakóddal.


Várakozás a szál végrehajtására
-------------------------------

.. code:: cpp

  int pthread_join(
    pthread_t thread,
    void **retval);

Paraméterek:

* ``thread``: A szál azonosítója, amelyikre várni kell majd a főszálnak.
* ``retval``: A szál által visszaadott érték (``pthread_exit`` hívásban). Amennyiben nincs rá szükség, úgy ``NULL``-al jelölhető.

Visszatérési érték:

* Sikeres végrehajtás esetén 0, egyébként hibakód.


Mutexek
-------

Mutex: *Mutual Exclusion*

Inicializálás:

.. code:: cpp

  pthread_mutex_t value_mutex = PTHREAD_MUTEX_INITIALIZER;

Kritikus szakasz kijelölése:

.. code:: cpp

  pthread_mutex_lock(&value_mutex);
  // Critical section
  pthread_mutex_unlock(&value_mutex);


Szál végrehajtásának félbeszakítása
-----------------------------------

.. code:: cpp

  int pthread_cancel(pthread_t thread);

Visszatérési érték:

  * Sikeres végrehajtás esetén 0, egyébként hibakód.

*forrás*:

* https://www.cs.cmu.edu/afs/cs/academic/class/15492-f07/www/pthreads.html
* https://hpc-tutorials.llnl.gov/posix/
