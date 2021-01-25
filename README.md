# Very Fast Simulated Anneeling global optimization of zero offset CRS parameters (VFSA).

[![Github release](https://img.shields.io/github/v/release/Dirack/vfsa)](https://github.com/Dirack/vfsa/releases/latest) [![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0) [![Madagascar](https://img.shields.io/badge/Madagascar-v3.0-blue)](https://github.com/ahay/src/tree/master) [![Build Status](https://travis-ci.com/Dirack/vfsa.svg?branch=master)](https://travis-ci.com/Dirack/vfsa)

![Result of the convergence test](https://github.com/Dirack/vfsa/blob/master/images/surfaces.png)

This package uses Very Fast Simulated Aneeling (VFSA) global optimization to extract the zero offset Common Reflection Surface (CRS) parameters, RN, RNIP, and BETA, from a reflection data cube (seismic data organized in CMP x Offset X Time coordinates). These parameters are obtained by fiting the non-hyperbolic CRS traveltime approximation in the data, the semblance between these surface and the data is the optimization criterion.

* For more details please check out ["What is VFSA?"](https://github.com/Dirack/vfsa/wiki/Very-Fast-Simulated-Anneling-(VFSA)) and ["What is non-hyperbolic CRS?"](https://github.com/Dirack/vfsa/wiki/Non-hyperbolic-CRS) in our Wiki.

In the first image above we show the expected result after VFSA global optimization algorithm application. It shows the convergence of the approximated surface, generated with the non-hyperbolic CRS traveltime approximation (midle), and the reflection surface extracted from the data (left).
The difference in the time between two surfaces is the approximation error (right, not in the same scale). The CRS paramters (RN, RNIP and BETA)
that produced the minimum error will be the optimized ones. We show the semblance between the two surfaces in function of the CRS parameters in the image above (maximum values in red).

In the image below we plot semblance values calculated for a set of RN, RNIP, BETA values, we can see a region of maximum semblance in red surounded by low values of semblance in green. In order to find the best semblance, someone have to calculate all the semblance values in the set for each RN, RNIP, and BETA, to find the CRS parameters related to the best semblance. VFSA algorithm allows faster convergence to this maximum semblance value, and consequently, optimizes the search of the RN, RNIP, and BETA parameters that produced it.

![Result of the convergence test](https://github.com/Dirack/vfsa/blob/master/images/parametersCube.png)

## Development setup

You need to have the current Madagascar package stable release installed on your computer. Please follow the [Installing Madagascar page](http://www.ahay.org/wiki/Installation) in the official documentation.

## Package installation

After Madagascar installing process, you need to install the programs of this repository in your local Madagascar user's directory. You can compile and install it as any other Madagascar program. Usually, Madagascar keeps the path of the source files of your Madagascar local version in the $RSFSRC environment variable. You can show that on a bash terminal using 'echo' command:

```sh
~$ echo "$RSFSRC"
```

And Madagascar will install executable files on your $RSFROOT directory. You can show that environment variable with 'echo' too:

```sh
~$ echo "$RSFROOT"
```

Madagascar stores user programs in $RSFSRC/user directory. So, you can create a new directory or put this repository inside that directory. In this repository, such as every user's repository in Madagascar, we have a compilation [SConstruct](https://github.com/Dirack/vfsa/blob/master/SConstruct) that compile the C programs of this package. Run 'scons' on your $RSFSRC/user/vfsa repository to compile it:

```shell
~$ scons
```

And run 'scons install' in the top directory of your local Madagascar installation (the directory path in your $RSFSRC variable):

```shell
~$ sudo scons install
```

If you have any doubt about this process, please reffer to the oficial documentation in [Adding_new_programs_to_Madagascar](http://www.ahay.org/wiki/Adding_new_programs_to_Madagascar), or follow [this tutorial on Youtube (Portuguese, English subtitles)](https://youtu.be/3Kkh0KF_4G8)

## Usage example

A few motivating and useful examples of how that product can be used can be found in the [usage_examples directory](https://github.com/Dirack/vfsa/tree/master/usage_examples). For more details, please refer to the [Wiki](https://github.com/Dirack/vfsa/wiki).

## Release History

* [v2.0.0](https://github.com/Dirack/vfsa/releases/tag/v2.0) - Beta release
   * Optimized algorithm using opemmp
   * New usage example: fullParametersOptimization
   * It does the experiment for a set of (t0,m0) pairs
   * Generate a new output: parameters cube for (t0,m0) pairs

* [v1.1.1](https://github.com/Dirack/vfsa/releases/tag/v1.1.1) - Stable release
   * New usage example os a multi layer model

* [v1.0.0](https://github.com/Dirack/vfsa/releases/tag/v1.0) - Stable release


[Please check out the full release history in our Wiki](https://github.com/Dirack/vfsa/wiki/Release-history).

## Meta

[vfsa main page](https://github.com/Dirack/vfsa)

Rodolfo Dirack – [@dirack](https://github.com/Dirack) – rodolfo_profissional@hotmail.com

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
