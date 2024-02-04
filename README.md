# Very Fast Simulated Annealing global optimization of the zero offset CRS parameters (VFSA).

[![Github release](https://img.shields.io/github/v/release/Dirack/vfsa)](https://github.com/Dirack/vfsa/releases/latest) [![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0) [![Madagascar](https://img.shields.io/badge/Madagascar-v3.0-blue)](https://github.com/ahay/src/tree/master)

![Result of the convergence test](https://github.com/Dirack/vfsa/blob/master/res/surfaces.png)

This package uses Very Fast Simulated Aneeling (VFSA) global optimization inversion to obtain the zero offset Common Reflection Surface (CRS) parameters (RN, RNIP, and BETA) from a reflection data cube (seismic data organized in CMP x half-offset X Time coordinates). These parameters are obtained by fiting the non-hyperbolic CRS traveltime surface in the reflection data cube using the semblance between them as the optimization criterion.

In the image above we show the expected result after VFSA global optimization algorithm application. It shows the convergence of the approximated surface generated with the non-hyperbolic CRS traveltime approximation (midle) with the reflection surface extracted from the data (left).
The difference between these two surfaces is the approximation error (right, and not in the same scale). The CRS paramters (RN, RNIP and BETA)
that produced the minimum error will be the optimized ones. 

* For more details please check out ["What is VFSA?"](https://github.com/Dirack/vfsa/wiki/Very-Fast-Simulated-Anneling-(VFSA)) and ["What is non-hyperbolic CRS?"](https://github.com/Dirack/vfsa/wiki/Non-hyperbolic-CRS) in our Wiki.

## Development setup

The vfsa package is designed for the open-source software package Madagascar. You need to have the current Madagascar stable release installed on your computer. Please follow the [Installing Madagascar page](http://www.ahay.org/wiki/Installation) in the official documentation.

## Package installation

After Madagascar installing process, you need to install the programs of this repository in your local Madagascar user's directory.
It is a simple process described in details in [install dependencies](https://github.com/Dirack/vfsa/wiki#install-dependencies) section of our wiki.

## Usage example

A few motivating and useful examples of how that product can be used can be found in the [usage examples directory](https://github.com/Dirack/vfsa/tree/master/examples).
For more details, please refer to the [Wiki](https://github.com/Dirack/vfsa/wiki).

## Release History

[Please check out the full release history in our Wiki](https://github.com/Dirack/vfsa/wiki/Release-history).

## Meta

Rodolfo Dirack – [@dirack](https://github.com/Dirack) – rodolfo\_profissional@hotmail.com

Distributed under the GPL3 license. See ``LICENSE`` for more information.

## Contributing

In order to contribute with this project you should follow the list of steps bellow, please check out ["How to contribute with this project?"](https://github.com/Dirack/vfsa/wiki/Contribute) in our Wiki for more details. 

1. Create an issue to your request or choose an issue already defined
2. Fork this project in https://github.com/Dirack/vfsa/fork 
3. Create a branch for your contribution (name it using gitflow)
4. Do clear _commit_ messages (a title with 50 characters and two paragraphs of text)
5. _Push_ your contribution to this repository
6. Create a new Pull Request with a clear description of your contribution

###### Important: The commit history should be clear, with commit mesages around one or two paraghraps describing your modifications. Pull Requests with unsatisfactory commit history will be rejected.
