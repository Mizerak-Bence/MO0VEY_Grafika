Bevezetés
=========

Kapcsolódó témakörök
--------------------

* Képfeldolgozás
* Gépi tanulás
* Statisztika
* Algebra, geometria


Fejlesztőkörnyezet telepítése
-----------------------------

A telepítendő eszközök
~~~~~~~~~~~~~~~~~~~~~~

A telepítendő Python csomagokat egy ``requirements.txt`` nevű állományba célszerű elhelyezni.

.. code::

   jupyter
   matplotlib
   numpy


Telepítés virtuális környezetbe
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code::

   $ python3 -m venv .venv
   $ source .venv/bin/activate
   (.venv) pip install --upgrade pip
   (.venv) pip install -r requirements.txt


Jupyter notebook
~~~~~~~~~~~~~~~~

.. code::

   (.venv) jupyter notebook

