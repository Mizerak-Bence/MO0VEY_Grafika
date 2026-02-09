3. Előadás - Szálkezelés
========================

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

**Szálbiztonság**

* *Thread safety*
* Egy implementációt szálbiztosnak nevezünk, hogy ha garantált, hogy helyesen működik abban az esetben is, hogy ha több szál próbálja meg elérni.

**Fork**

* A nevét az elágazásról, mint villáról kapta.
* A végrehajtás ezen pontján a programból egy új futási szál jön létre.
* Ugyanazon kód fut tovább mindkét szálban.
* A szál ezt követően el tudja dönteni magáról, hogy az *eredeti* vagy az újonnan létrehozott szál-e.

**Join**

* Egy szinkronizációs primitív.
* A program végrehajtása ezen a ponton bevárja, hogy egy másik szál végrehajtásra kerüljön.

**Barrier**

* Egy szinkronizációs eszköz. A program ezen a ponton bevárja, hogy az összes szál elvégezze a számításait.
* Egymás után kiadott *join* műveletekkel megoldható abban az esetben is, hogy ha nincsen rá kész elem.

Alapvető műveletek
------------------

* Szál létrehozása
* Szál indítása
* Paraméterek átadása
* Várakozás a szál végrehajtására
* Szálak lekérdezése, státuszok
* Aktuális szál adatainak lekérdezése
* Mutex-ek, zárolás
* Szál futásának leállítása

:math:`\rhd` Hogyan tünne kézenfekvőnek ezeket egy programozási nyelv segítségével megoldani?

:math:`\rhd` Gondoljuk át, hogy milyen problémák jelentkezhetnek OOP nyelvek esetében! (Például scope-ok kezelése, kivételkezelés.)

POSIX szálak
------------

Portable Operating System Interface for UNIX

https://hu.wikipedia.org/wiki/POSIX

Szál létrehozása és indítása
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

A szál elindítása a létrehozáskor automatikusan megtörténik.

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


Paraméterek átadása
~~~~~~~~~~~~~~~~~~~

* A szálnak ``void*`` típusú paraméterként lehet átadni értékeket.
* Ez praktikusan jelentheti például egy struktúrának az átadását.


Várakozás a szál végrehajtására
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code:: cpp

  int pthread_join(
    pthread_t thread,
    void **retval);

Paraméterek:

* ``thread``: A szál azonosítója, amelyikre várni kell majd a főszálnak.
* ``retval``: A szál által visszaadott érték (``pthread_exit`` hívásban). Amennyiben nincs rá szükség, úgy ``NULL``-al jelölhető.

Visszatérési érték:

* Sikeres végrehajtás esetén 0, egyébként hibakód.


Szálak lekérdezése
~~~~~~~~~~~~~~~~~~

* Nincs rá egységes, platformfüggetlen megoldás.
* UNIX-szerű rendszerek esetében a ``/proc`` jegyzék tartalmaz erre vonatkozó információkat.


Aktuális szál adatainak lekérdezése
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Az aktuális szál azonosítóját a

.. code:: cpp

    #include <unistd.h>
    pid_t gettid(void);

    #include <pthread.h>
    pthread_t pthread_self(void);

függvényekkel lehet lekérdezni.

https://stackoverflow.com/questions/6372102/what-is-the-difference-between-pthread-self-and-gettid-which-one-should-i-u

Mutexek
~~~~~~~

Mutex: *Mutual Exclusion*

Inicializálás:

Amennyiben a mutex-et statikus változóként (globális névtérben) szeretnénk használni, akkor a következő makró formájában megadható:

.. code:: cpp

  pthread_mutex_t value_mutex = PTHREAD_MUTEX_INITIALIZER;

Amennyiben dinamikusan (például stack-en allokált) változóról van szó, akkor az előbbivel ekvivalens az alábbi hívás:

.. code:: cpp

  pthread_mutex_init(&value_mutex, NULL);

Kritikus szakasz kijelölése:

.. code:: cpp

  pthread_mutex_lock(&value_mutex);
  // Critical section
  pthread_mutex_unlock(&value_mutex);


Szál végrehajtásának félbeszakítása
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code:: cpp

  int pthread_cancel(pthread_t thread);

Visszatérési érték:

  * Sikeres végrehajtás esetén 0, egyébként hibakód.

*forrás*:

* https://www.cs.cmu.edu/afs/cs/academic/class/15492-f07/www/pthreads.html
* https://hpc-tutorials.llnl.gov/posix/

C++11/std::thread
-----------------

* A szálkezelést beemelték a szabványos függvénykönyvtárba.
* Platformfüggetlen megoldást igyekszik adni a szálkezelési problémára. (Ahogy anno a POSIX is próbálta.)

.. code:: cpp

  #include <thread>

https://thispointer.com/c-11-multithreading-part-1-three-different-ways-to-create-threads/

Szál létrehozása
~~~~~~~~~~~~~~~~

Egy ``std::thread`` konstruktora a következőkkel inicializálható:

* függvény mutató,
* függvény objektum,
* lambda függvény.

.. code:: cpp

  #include <thread>

  void worker() { ... }

  int main(int argc, char* argv[]) {
    std::thread myThread(worker);
    myThread.join();
    return 0;
  }

.. code:: cpp

    #include <thread>

    class MyThread {
    public:
        operator()() {
            // TODO: Calc here!
        }
    };

    int main(int argc, char* argv[]) {
      std::thread myThread(MyThread());
      myThread.join();
      return 0;
    }

.. code:: cpp

  #include <thread>

  int main(int argc, char* argv[]) {
    std::thread myThread([]{
        // TODO: Calc here!
    });
    myThread.join();
    return 0;
  }


Paraméterek átadása
~~~~~~~~~~~~~~~~~~~

Az ``std::thread`` konstruktorában átadhatók.

.. code:: cpp

  #include <thread>

  void worker(int x) {
    // TODO: Calc here!
  }

  int main(int argc, char* argv[]) {
    std::thread myThread(worker, 1234);
    myThread.join();
    return 0;
  }


Várakozás a szál végrehajtására
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code:: cpp

    void std::thread::join();


Szál adatainak lekérdezése
~~~~~~~~~~~~~~~~~~~~~~~~~~

Egyedi azonosító lekérdezése:

.. code:: cpp

    std::thread::get_id()

Az aktuális szál azonosítójának a lekérdezése:

.. code:: cpp

    std::this_thread::get_id()


Zárolás
~~~~~~~

.. code:: cpp

    #include <mutex>

    std::mutex myMutex;

    // ...

    myMutex.lock();

    // ...

    myMutex.unlock();


Future, Promise
~~~~~~~~~~~~~~~

* Tudunk kezelni olyan objektumokat, amelyek csak később tesznek elérhetővé bizonyos értékeket.

.. code:: cpp

    #include <future>
    #include <iostream>
    #include <thread>

    void worker(std::promise<int>* prom)
    {
        prom->set_value(1234);
    }

    int main(int argc, char* argv[])
    {
        std::promise<int> myPromise;
        std::future<int> myFuture = myPromise.get_future();
        std::thread myThread(worker, &myPromise);
        std::cout << myFuture.get() << std::endl;
        myThread.join();
        return 0;
    }


C++/Qt
------

Szál létrehozása és indítása
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

* A ``QThread`` osztályt lehet példányosítani vagy származtatni.
* A ``QThread::run`` metódust kell felüldefiniálni.
* A szálakat külön el kell indítani.

.. code::

    class MyThread : public QThread
    {
        Q_OBJECT
    private:
        void run();
    };

    int main(int argc, char* argv[])
    {
        MyThread thread;
        thread.run();
        // ...
        thread.wait();
        return 0;
    }

Paraméterek átadása
~~~~~~~~~~~~~~~~~~~

Mivel saját osztály definiálható, ezért kézenfekvő módon adódik.


Szálak adatainak lekérdezése
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

A ``QThread`` osztály metódusain keresztül lehet hozzáférni.

.. code::

    bool isFinished();
    bool isRunning();
    QThread* currentThread();
    Qt::HANDLE currentThreadId();


Zárolás
~~~~~~~

.. code:: cpp

    #include <QMutex>

    // ...

    QMutex mutex;
    mutex.lock()
    mutex.tryLock();
    mutex.unlock();

A mutex scope-hoz is köthető a ``QMutexLocker`` osztály segítségével.


Java, IRunnable, Thread
-----------------------

https://docs.oracle.com/javase/tutorial/essential/concurrency/runthread.html

Szál létrehozása és elindítása
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

A ``Runnable`` interfész implementálásával:

.. code:: java

    public class MyRunnable implements Runnable {
        public void run() {
            System.out.println("Run!");
        }
        public static void main(String args[]) {
            (new Thread(new MyRunnable())).start();
        }
    }

A ``Thread`` osztály származtatásával:

.. code:: java

    public class MyThread extends Thread {
        public void run() {
            System.out.println("Run!");
        }
        public static void main(String args[]) {
            (new MyThread()).start();
        }
    }


Paraméterek átadása
~~~~~~~~~~~~~~~~~~~

Mivel saját osztály definiálható, ezért kézenfekvő módon adódik.


Várakozás a szál végrehajtására
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code:: java

    Thread.join();
    Thread.join(long milliseconds)


Szálak lekérdezése, státusz
~~~~~~~~~~~~~~~~~~~~~~~~~~~

A ``Thread`` osztályon keresztül hozzáférhetők a következő metódusok.

.. code:: java

    static Thread currentThread();
    long getId();
    String getName();
    int getPriority();
    boolean isAlive();

A szálakat a Java csoportokban tartja nyilván. A ``ThreadGroup``-okon keresztül hozzá lehet férni az összes szálhoz.


Zárolás
~~~~~~~

.. code:: java

    Lock lock = new ReentrantLock();

    // ...
    lock.lock();
    lock.tryLock();
    lock.unlock();


C#, System.Threading
--------------------

Szál létrehozása és indítása
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code:: csharp

    using System;
    using System.Threading;

    namespace MyApplication {
        class Sample {
            public static void Worker() {
                // TODO: Calc here!
            }
            static void Main(string[] args) {
                ThreadStart threadStart = new ThreadStart(Worker);
                Thread thread = new Thread(threadStart);
                thread.start();
                thread.Name = "MainThread";
                Console.WriteLine("Name: {0}", thread.Name);
                Console.ReadKey();
            }
        }
    }


Várakozás a szál végrehajtására
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code:: csharp

    public void Join();


Szál futásának félbeszakítása
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code:: csharp

    Thread.Abort();


Python
------

https://docs.python.org/3/library/threading.html

https://realpython.com/intro-to-python-threading/


Szálak létrehozása és indítása
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code:: python

    import threading

    def worker():
        print('Work here!')

    if __name__ == '__main__':
        thread = threading.Thread(target=worker)
        thread.start()


Paraméterek átadása
~~~~~~~~~~~~~~~~~~~

.. code:: python

    import threading

    def worker(x, y):
        print(f'Work here on {x} and {y}!')

    if __name__ == '__main__':
        thread = threading.Thread(target=worker, args=(12, 34))
        thread.start()


Várakozás a szál végrehajtására
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code:: python

    Thread.join()


Szálak adatainak lekérdezése
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code:: python

    threading.get_ident()
    threading.get_native_id()


Zárolás
~~~~~~~

.. code:: python

    class Sample:

        def __init__(self):
            self._lock = threading.Lock()

        def work(self):
            with self._lock():
                pass

A ``Lock`` objektum műveletei:

* ``acquire``: zárás
* ``release``: feloldás
* ``locked``: lekérdezés


Kérdések
--------

* Mi az a POSIX?
* Milyen előnyei vannak a szálaknak a folyamatokhoz képest?
* Min osztoznak a szálak egy folyamaton belül?
* Mi az ami minden szál esetében egyedi?
* Mit jelent a szálbiztonság/szálbiztos implementáció?
* Milyen esetben van szükség reentrant lock-ra?

Feladatok
---------

POSIX szálak
~~~~~~~~~~~~

* Készítsünk olyan programot, amelynél a fő szál 8 másodpercnyi számítást végez el, míg az általa indított csak 4-et! Vizsgáljuk meg a fordított esetet is!
* Készítsünk egy programot, amelyik elindít 60 szálat. Mindegyik szál végezzen 1 másodpercnyi számítást! Vizsgáljuk meg a teljes program futási idejét!
* Készítsünk egy programot, amelyik 10 szál segítségével meghatározza, hogy mennyi prímszám van a [0, 99], [100, 199], ... intervallumokon! A szálaknak adja át az intervallumok indexét, majd az eredményt így írják közvetlenül egy globális tömbbe!
* Vizsgáljuk meg, hogy mi történik, hogy ha egy szálban futás idejű hiba keletkezik!


Algoritmusok párhuzamosítása
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

1. Készítsen egy programot, amely egy tömb elemeinek összegét számítja ki több szál felhasználásával!

    * Oldja meg, hogy a program működjön tetszőleges méretű tömbökre is!
    * Írjon egy programot, amely a tömböt közel egyenlő részekre oszt oldja meg az összegzést!
    * Írjon egy programot, amely rekurzív felosztásra épül!
    * A programban a szálak száma paraméterként szerepeljen!
    * Hasonlítsa össze a :math:`p = 1` esetet a szekvenciális változattal futási idő tekintetében!
    * Mérje le a futási időket különböző :math:`p` értékek és különböző bemenetméretek mellett!
    * Adjon becslést a :math:`T(n, p)` függvényre (ahol :math:`n` a bemeneti tömb mérete, :math:`p` pedig a szálak száma).
    * Adjon becslést a gyorsításra (mint :math:`S(p)` függvényre)!
    * A kapott eredményeket foglalja össze táblázatban, és ábrázolja grafikonon!

2. Készítsen olyan programokat, amelyek meghatározzák, hogy bizonyos tulajdonságú elemből mennyi található egy sorozatban. Ilyen tulajdonság lehet például, hogy

    * egész értékek esetén páros vagy páratlan számok-e,
    * 0 értékűek-e,
    * előjelesek-e,
    * lebegőpontos számok esetén 1-nél kisebb abszolút értékűek-e, vagy hogy
    * adott intervallumba esnek-e.

A feladat megoldásánál használjon

    * nagy méretű, véletlenszerűen generált adatokat,
    * dinamikusan allokált tömböket.

Hasonlítsa össze a szekvenciális és a többszálú megvalósítást!

    * Mérje le a futási időket a bemenet méretének és a szálak számának függvényében!
    * Összesítse a kapott eredményeket táblázatos formában!
    * Ábrázolja az eredményeket grafikonok!

3. Készítsen programot egy tömb prefixeinek a kiszámításához!

    * Adja meg a szekvenciális változatot!
    * Implementálja a ``CREW_PREFIX`` algoritmust!
    * Implementálja az ``EREW_PREFIX`` algoritmust!
    * Implementálja az ``OPTIMAL_PREFIX`` algoritmust!
    * Mérje le a futási időket különböző számú szál és különböző bemenetméretek mellett!
    * Adjon becslést a gyorsításra (mint :math:`S(p)` függvényre)!
    * A kapott eredményeket foglalja össze táblázatban, és ábrázolja grafikonon!
