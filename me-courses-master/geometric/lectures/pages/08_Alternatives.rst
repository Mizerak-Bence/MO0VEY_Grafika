****************************
Alternative modeling methods
****************************

Modelling methods
=================

Wireframe modeling
------------------

* We define the boundary edges, typical lines of the modeled shape by using line segments, arcs and curves.
* The representation is ambiguous. We can describe fairly different shapes by the same wireframe model.
* In this modeling method, we only know the edges, therefore it is not appropriate for collision detection and volume calculation.
* Nowadays, we consider it as an elementary, auxiliary phase of the modeling process.

Surface modeling
----------------

* We describe the boundary surfaces of the modeled object by joining surface patches to each others.
* This model is unable to handle topological information. It requires further analysis to determine the compoundness, continuity and the open/closed property of the surface.
* This representation is closer to the real objects. We can use shading, shadows and textures for more realistic visualization.

Boundary representation
-----------------------

* It is often abbreviated as *B-rep*.
* It represents the objects as a finite, closed shape, mostly by using polymesh approximation.
* It assumes that the physical models has finite and closed surface.
* It describes the model from topological aspect also.
* It is proper for physical simulations, finite element methods.

Solid geometry
--------------

* It is also called volumetric modeling or CSG modeling.
* It describes the model as a finite, closed set of points.
* It has a higher abstraction level than in the case of the previous models.

.. seealso::

  * http://old.bgk.uni-obuda.hu/ggyt/targyak/seged/bagca15nlc/

CSG modellezés
==============

*Constructive Solid Geometry*

Let assume that we know the shapes of the solids as implicit functions. These can tell us that an arbitrary point of the space whether belongs to a solid or not.

* The value of these functions are logical values. Therefore, we can apply logical operators on them.
* Considering the solids as set of points, we can use the set operations also.

The commonly used operators are the union (:math:`\cup`), the intersection (:math:`\cap`) and the subtraction (:math:`\setminus`).

We can combine multiple set operations to expressions. These expressions can be represented as binary trees. These show the process of the making of the model.

* We call this kind of tree as CSG tree.
* We (usually) consider binary operations which means that the tree is a binary tree.

For using this kind of model, we have to use a set of predefined primitive shapes. In most cases the followings are available in the CAD systems:

* rectangle,
* pyramid,
* cylinder,
* cone,
* sphere.

We can also use geometric transformations in the modeling process.

* This kind of modeling approach suits well with ray tracing/casting rendering algorithms.
* It is a common solution, to convert the resulted shapes to triangle mesh for visualization and/or model format export.
* This method is also benefitial when we design the model for manufacturing and assembly.

.. seealso::

  * https://en.wikipedia.org/wiki/Constructive_solid_geometry

Metaball modeling
=================

* https://en.wikipedia.org/wiki/Metaballs

Volumetric modeling
===================

We can use raster-based approach for planar and spatial object modeling also.

It is called volumetric modeling or voxel graphics when we assign properties to the cells/blocks in the three dimensional space.

.. seealso::

  * https://en.wikipedia.org/wiki/Voxel

Softwares for 3D modeling
=========================

* Blender: https://www.blender.org/
* FreeCAD: https://www.freecad.org/
* Wings 3D: https://www.wings3d.com/

Further exercises
=================

* Let implement an application, which is able to render CSG scenes by using simple ray tracing methods!
* Let try to approximate a surface by using metaball modeling technique!

