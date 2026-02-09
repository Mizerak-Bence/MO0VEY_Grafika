Message Passing Interface
=========================

.. libopenmpi-dev

Minimális MPI program
---------------------

A legegyszerűbb MPI programnak is tartalmaznia kell az ``MPI_Init`` és ``MPI_Finalize`` hívásokat, így például az alábbi formában képzelhető el:

.. literalinclude:: ../../../../algorithms/mpi_samples/hello.c
   :language: c

A program fordítása:

.. code:: bash

    gcc hello.c -o hello -l mpi

A program futtatása:

.. code:: bash

    mpirun hello


Master-slave
------------

Az MPI környezet a programból elérhető teszi, hogy az éppen hogy lett elindítva. A következő példában azt láthatjuk, hogy hogyan tudjuk megállapítani, hogy több folyamat közül melyik-melyik.

.. literalinclude:: ../../../algorithms/mpi_samples/master_slave.c
   :language: c

A programot fordítani a következő parancs kiadásával tudjuk:

.. code:: bash

    gcc master_slave.c -o master_slave -l mpi

Futtatáshoz adjuk meg, hogy a processzek száma 2 legyen:

.. code:: bash

    mpirun -np 2 master_slave

A program kimenetének az elvártak szerint a következő sorokat kell tartalmaznia:

.. code:: bash

    [0] I am the master!
    [1] I am just a slave.

Érdemes azt észrevenni/kipróbálni, hogy futtatástól függően a kiíratások sorrendje változhat.


Blokkoló üzenet küldése
-----------------------

Az üzenet küldésénél a blokkolás azt jelenti, hogy a program csak az üzenet elküldése után folytatja a futását.

.. literalinclude:: ../../../algorithms/mpi_samples/send_message.c
   :language: c

Néhány észrevétel:

* Az ``MPI_Send`` és ``MPI_Recv`` függvény visszatérési értéke ebben a rövid példában nincs ellenőrízve. A függvény egy hibakódot ad vissza, amellyel ellenőrízni lehet, hogy sikeres volt-e a küldés, vagy ha nem, akkor miért (http://web.mit.edu/22.00J/www/www3/MPI_Send.html).
* Futtatásonként a kiírt üzenetek sorrendje eltérhet.
* A program feltételezi, hogy legalább 2 process van.
* Szintén feltételezés, hogy a címzett rangja 1.
* A ``message`` változó kétféle módon kerül felhasználásra a küldő és fogadó oldalon.


Átlagolós példa
---------------

.. http://www.democritos.it/events/computational_physics/lecture_stefano4.pdf

Tegyük fel, hogy készíteni szeretnénk egy olyan programot, amelyben van egy megkülönböztetett (*master*) folyamat, amelyik a többi folyamattól vár egy-egy lebegőpontos értékeket, majd ezek átlagát számítja ki a többi által összességében becsült értékként.

Ahhoz, hogy a *master* folyamat tudja, hogy mikor érkezik be számára az utolsó érték, az egyszerűbb megoldás az, hogy ha kiszámítja a rajta kívül lévő folyamatok számát. Ez az ``MPI_Comm_Size`` függvénnyel lekérdezhető.

Az egyszerűség kedvéért most feltételezzük azt, hogy minden folyamat a saját rangját küldi át a *master*-nek (így az eredmény a rangok átlaga lesz majd).

Blokkoló hívás segítségével a következőképpen oldható meg a probléma:

.. literalinclude:: ../../../algorithms/mpi_samples/guess.c
   :language: c

A probléma megoldható az ``MPI_Reduce`` függvényének a segítségével is.
Ehhez itt található egy részletes leírás: https://mpitutorial.com/tutorials/mpi-reduce-and-allreduce/

Ezzel a következő formában képzelhető el:

.. literalinclude:: ../../../algorithms/mpi_samples/guess_reduced.c
   :language: c

.. warning::

    A ``MPI_Reduce`` függvény esetében figyelni kell a függvény paramétereinek az inicializálása!
    A függvény a szinkronizációt ugyan elvégzi, de a kezdeti értékek beállítása esetleges.

A program a következő tömörebb formába is átírható:

.. literalinclude:: ../../../algorithms/mpi_samples/guess_red.c
   :language: c
