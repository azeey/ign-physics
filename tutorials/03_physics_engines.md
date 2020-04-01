\page physicsengine Understanding the Physics Plugin

This is an introduction to different physics engines and how they are integrated into the Ignition Physics library.

## Ignition Physics

The [Ignition Physics](https://ignitionrobotics.org/api/physics/2.0/) library integrates external physics engines into the Ignition Simulation eco-system.
It allows users to select from multiple supported physics engines based on their simulation needs.
Its plugin interface loads physics engines with requested features at runtime.
It is also possible to integrate your own selected physics engine by writing a compatible plugin interface.

To get a more in-depth understanding of how the physics plugin works in Ignition, we will start with some high level concepts and definitions.

<!-- TODO: add tutorial on how to write your own physics plugin -->

### High Level Concept

Conceptually, the physics plugin can be viewed from two sides of its interface: user vs. implementation.

Each physics engine provides access to different features implemented by the Ignition Physics engine.
The interface is made possible through the [Ignition Plugin](https://ignitionrobotics.org/libs/plugin) library, which instantiates [Features](https://ignitionrobotics.org/api/physics/2.0/classignition_1_1physics_1_1Feature.html) in [FeatureLists](https://ignitionrobotics.org/api/physics/2.0/structignition_1_1physics_1_1FeatureList.html) and supplies pointers to the selected engine.
This "user side interface" makes the Ignition Physics library "callable" from other Ignition libraries.

The implementation side interface handles specific implementations of each `Feature`.
Depending on what external physics engine we are using (DART, TPE, Bullet etc.), the interface might be different.
This interface is more internal facing, i.e. used mostly inside the Ignition Physics library.

The implementation of the physics plugin revolves around four key elements.

1. [Entity](https://ignitionrobotics.org/api/physics/2.0/classignition_1_1physics_1_1Entity.html)

    This is the base class of all "proxy objects".
    The "proxy objects" are essentially interfaces into the actual objects which exist inside of the various physics engine implementations.
    The proxy objects contain the minimal amount of data (e.g. a unique identifier, a reference-counter for the implementation object, and a reference to the implementation interface that it needs) necessary to interface with the object inside of the implementation that it refers to.

2. [FeaturePolicy](https://ignitionrobotics.org/api/physics/2.0/structignition_1_1physics_1_1FeaturePolicy.html)

    FeaturePolicy is a "policy class" used to provide metadata to features about what kind of simulation engine they are going to be used in.
    Many physics simulations software libraries model 3-dimensional systems, though some (like Box2d) only consider 2-dimensional systems.
    A FeaturePolicy is used to customize Ignition Physics' APIs by the number of dimensions (2 or 3) and also the floating point scalar type (float or double).
    Dartsim and TPE reference implementations both use FeaturePolicy3d (3 dimensions, double).

3. [Feature](https://ignitionrobotics.org/api/physics/2.0/classignition_1_1physics_1_1Feature.html)

    This class defines the concept of a `Feature`, examples like `GetEngineFromWorld`, [GetEngineInfo](https://ignitionrobotics.org/api/physics/2.0/classignition_1_1physics_1_1GetEngineInfo.html) etc.
    There is a pre-defined list of features in Ignition Physics.
    They are implemented by using external physics engines' APIs to fulfill simulation needs requested by Ignition.

4. [FeatureList](https://ignitionrobotics.org/api/physics/2.0/structignition_1_1physics_1_1FeatureList.html)

    This is the class that aggregates a list of features.
    FeatureLists can be constructed in hierarchies, e.g. a `FeatureList` can be passed into another `FeatureList`, and the set of all features in the new list will be the sum.


### FeatureList Definitions

| Name  | Definition  |
|---|---|
| Base  | contains data structures and functions that define and use "proxy objects"   |
| CustomFeatures  | retrieves `World` entity from physics engine|
| EntityManagementFeatures  | provides features to get, remove and construct entities  |
| FreeGroupFeatures  | finds free group entities and sets world pose, linear and angular velocities  |
| JointFeatures  | defines types of joints used and sets joint properties  |
| KinematicsFeatures  | computes frame relative to world  |
| LinkFeatures  | applies external force and torque to link  |
| SDFFeatures  | constructs entities from SDF file  |
| ShapeFeatures  | retrieves `Shape` related properties like `BoundingBox`, `ShapeSize` etc. |
| SimulationFeatures  | updates `World` and everything within by defined stepsize |
|   |   |

### Dart vs. Trivial Physics Engine (TPE)

<!-- TODO: add Bullet once it's supported -->
<!-- ### Bullet -->

Dart ([Dynamic Animation and Robotics Toolkit](https://dartsim.github.io/)) is an open source library that provides data structures and algorithms for kinematic and dynamic applications in robotics and computer animation.
It is the default physics engine used in Ignition Simulation.
The plugin interface for DART is called [Dartsim](https://bitbucket.org/ignitionrobotics/ign-physics/src/default/dartsim/) in Ignition Physics.

TPE ([Trivial Physics Engine](<!-- TODO: add repo link -->)) is an open source library created by Open Robotics that enables fast, inexpensive kinematics simulation for entities at large scale.
It supports higher-order fleet dynamics without real physics (eg. gravity, force, constraint etc.) and multi-machine synchronization.
The plugin interface for TPE is called `TPE-Plugin` in Ignition Physics.

The following is a list of features supported by each physics engine to help users select one that fits their needs.

#### Entity Comparison

The following is a table of `Entity` names used in Ignition Physics plugin interface, Dart and TPE.
Entities are arranged in top-down hierarchical order.

| Physics Plugin | Dart  | TPE  |
|:-:|:-:|:-:|
| Engine  | Engine  | Engine  |
| World  | World  | World  |
| Frame  | Frame  | N/A  |
| Model  | Skeleton  | Model |
| Joint  | Joint  | N/A |
| Link  | Node  | Link  |
| Shape  | Shape  | Collision |
| Box/Sphere/Cylinder etc. | Box/Sphere/Cylinder etc.  | Shape |
|   |   |   |

#### Feature Comparison

The following is a table of implemented `FeatureLists` of Dartsim and TPE-Plugin.

| Dartsim  | TPE-Plugin  |
|:-:|:-:|
| Base  | Base  |
| CustomFeatures  | CustomFeatures  |
| EntityManagementFeatures  | EntityManagementFeatures  |
| FreeGroupFeatures  | FreeGroupFeatures  |
| JointFeatures  | N/A  |
| KinematicsFeatures  | KinematicsFeatures  |
| LinkFeatures  | N/A  |
| SDFFeatures  | SDFFeatures  |
| ShapeFeatures  | ShapeFeatures   |
| SimulationFeatures  | SimulationFeatures  |
|  |  |