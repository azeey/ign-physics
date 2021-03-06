# Ignition Physics : Physics classes and functions for robot applications

**Maintainer:** scpeters AT openrobotics DOT org

[![Bitbucket open issues](https://img.shields.io/bitbucket/issues-raw/ignitionrobotics/ign-physics.svg)](https://bitbucket.org/ignitionrobotics/ign-physics/issues)
[![Bitbucket open pull requests](https://img.shields.io/bitbucket/pr-raw/ignitionrobotics/ign-physics.svg)](https://bitbucket.org/ignitionrobotics/ign-physics/pull-requests)
[![Discourse topics](https://img.shields.io/discourse/https/community.gazebosim.org/topics.svg)](https://community.gazebosim.org)
[![Hex.pm](https://img.shields.io/hexpm/l/plug.svg)](https://www.apache.org/licenses/LICENSE-2.0)

Build | Status
-- | --
Test coverage | [![codecov](https://codecov.io/bb/ignitionrobotics/ign-physics/branch/default/graph/badge.svg)](https://codecov.io/bb/ignitionrobotics/ign-physics)
Ubuntu Bionic | [![Build Status](https://build.osrfoundation.org/buildStatus/icon?job=ignition_physics-ci-default-bionic-amd64)](https://build.osrfoundation.org/job/ignition_physics-ci-default-bionic-amd64)
Homebrew      | [![Build Status](https://build.osrfoundation.org/buildStatus/icon?job=ignition_physics-ci-default-homebrew-amd64)](https://build.osrfoundation.org/job/ignition_physics-ci-default-homebrew-amd64)
Windows       | [![Build Status](https://build.osrfoundation.org/buildStatus/icon?job=ign_physics-ci-win)](https://build.osrfoundation.org/job/ign_physics-ci-win)

Ignition Physics, a component of [Ignition
Robotics](https://ignitionrobotics.org), provides an abstract physics interface
designed to support simulation and rapid development of robot applications.

# Table of Contents

[Motivation](#markdown-header-motivation)

[Features](#markdown-header-features)

[Install](#markdown-header-install)

* [Binary Install](#markdown-header-binary-install)

* [Source Install](#markdown-header-source-install)

    * [Prerequisites](#markdown-header-prerequisites)

    * [Building from Source](#markdown-header-building-from-source)

[Usage](#markdown-header-usage)

[Documentation](#markdown-header-documentation)

[Testing](#markdown-header-testing)

[Folder Structure](#markdown-header-folder-structure)

[Code of Conduct](#markdown-header-code-of-conduct)

[Contributing](#markdown-header-code-of-contributing)

[Versioning](#markdown-header-versioning)

[License](#markdown-header-license)

# Motivation

Many physics simulation software libraries have been designed for different
applications (gaming, robotics, science) and with different features
(rigid or deformable contact, 2d or 3d).
Ignition Physics is designed on the premise that there is not a single physics
engine that is universally best for all simulation contexts.
It should be possible to support a different set of features
for each physics engine according to its capabilities.
A physics engine can then be chosen for each application
based on its context.

# Features

Ignition Physics provides the following functionality:

* Granular definition of physics engine features as optional API's.
* Plugin interface for loading physics engines with requested features
  at runtime.
* Features for common aspects of rigid body dynamic simulation
    - Construct model from SDFormat file.
    - Collision shapes (such as box, sphere, cylinder, mesh, heightmap).
    - Joint types (such as revolute, prismatic, fixed, ball, screw, universal).
    - Step simulation, get/set state, apply inputs.
* Reference implementation of physics plugin using
  [dartsim](http://dartsim.github.io/).
* CompositeData structures for efficiently using native types in API.

# Install

We recommend following the [Binary Install](#markdown-header-binary-install) instructions to get up and running as quickly and painlessly as possible.

The [Source Install](#markdown-header-source-install) instructions should be used if you need the very latest software improvements, you need to modify the code, or you plan to make a contribution.

## Binary Install

On Ubuntu systems, `apt-get` can be used to install `ignition-physics3`:

```
sudo apt install libignition-physics3-dev
```

## Source Install

Source installation can be performed in UNIX systems by first installing the
necessary prerequisites followed by building from source.

### Prerequisites

Install required dependencies:

~~~
sudo apt update
sudo apt-get -y install lsb-release
sh -c 'echo "deb http://packages.osrfoundation.org/gazebo/ubuntu-stable `lsb_release -cs` main" > /etc/apt/sources.list.d/gazebo-stable.list'
apt-key adv --keyserver keyserver.ubuntu.com --recv-keys D2486D2DD83DB69272AFE98867170598AF249743
sudo apt-add-repository -s "deb http://packages.osrfoundation.org/gazebo/ubuntu-stable $(lsb_release -c -s) main"
sudo apt-get build-dep -y ignition-physics3

Use gcc-8:

~~~
sudo apt update
sudo apt-get -y install g++-8
sudo update-alternatives --install \
  /usr/bin/gcc gcc /usr/bin/gcc-8 800 \
  --slave /usr/bin/g++ g++ /usr/bin/g++-8 \
  --slave /usr/bin/gcov gcov /usr/bin/gcov-8
~~~

### Building from source

1. Clone the repository

    ```
    hg clone https://bitbucket.org/ignitionrobotics/ign-physics -b ign-physics3
    ```

2. Configure and build

    ```
    cd ign-physics; mkdir build; cd build; cmake ..; make
    ```

3. Optionally, install Ignition Physics

    ```
    sudo make install
    ```

# Usage

Please refer to the [examples directory](https://bitbucket.org/ignitionrobotics/ign-physics/raw/default/examples/?at=default).

# Documentation

API and tutorials can be found at [https://ignitionrobotics.org/libs/physics](https://ignitionrobotics.org/libs/physics).

You can also generate the documentation from a clone of this repository by following these steps.

1. You will need Doxygen. On Ubuntu Doxygen can be installed using

    ```
    sudo apt-get install doxygen
    ```

2. Clone the repository

    ```
    hg clone https://bitbucket.org/ignitionrobotics/ign-physics -b ign-physics3
    ```

3. Configure and build the documentation.

    ```
    cd ign-physics; mkdir build; cd build; cmake ../; make doc
    ```

4. View the documentation by running the following command from the build directory.

    ```
    firefox doxygen/html/index.html
    ```

# Testing

Follow these steps to run tests and static code analysis in your clone of this repository.

1. Follow the [source install instruction](#markdown-header-source-install).

2. Run tests.

    ```
    make test
    ```

3. Static code checker.

    ```
    make codecheck
    ```

# Folder Structure

Refer to the following table for information about important directories and files in this repository.

```
ign-physics
├── dartsim                   Files for dartsim plugin component.
├── include/ignition/physics  Header files.
├── mesh                      Files for mesh component.
├── resources                 Model and mesh resource files used by tests.
├── sdf                       Files for sdf component.
├── src                       Source files and unit tests.
├── test
│    ├── benchmark            Benchmark tests.
│    ├── integration          Integration tests.
│    ├── performance          Performance tests.
│    ├── plugins              Plugins used in tests.
│    ├── regression           Regression tests.
│    └── static_assert        Tests involving compilation failures.
├── tutorials                 Tutorials, written in markdown.
├── Changelog.md              Changelog.
└── CMakeLists.txt            CMake build script.
```
# Contributing

Please see
[CONTRIBUTING.md](https://bitbucket.org/ignitionrobotics/ign-gazebo/src/406665896aa40bb42f14cf61d48b3d94f2fc5dd8/CONTRIBUTING.md?at=default&fileviewer=file-view-default).

# Code of Conduct

Please see
[CODE\_OF\_CONDUCT.md](https://bitbucket.org/ignitionrobotics/ign-gazebo/src/406665896aa40bb42f14cf61d48b3d94f2fc5dd8/CODE_OF_CONDUCT.md?at=default&fileviewer=file-view-default).

# Versioning

This library uses [Semantic Versioning](https://semver.org/). Additionally, this library is part of the [Ignition Robotics project](https://ignitionrobotics.org) which periodically releases a versioned set of compatible and complimentary libraries. See the [Ignition Robotics website](https://ignitionrobotics.org) for version and release information.

# License

This library is licensed under [Apache 2.0](https://www.apache.org/licenses/LICENSE-2.0). See also the [LICENSE](https://bitbucket.org/ignitionrobotics/ign-physics/src/default/LICENSE) file.
