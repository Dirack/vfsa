# vfsa
> Very Fast Simulated Anneeling global optimization of zero offset CRS parameters.

[This program is part of the Madagascar package! version 3.0.](https://github.com/ahay/src/tree/master/user/dirack)

This is a package with several C programs adapted to the Madagascar seismic processing package. The mains objective of
those programs is to extract the zero offset CRS parameters (RN, RNIP, BETA) 
a reflection data cube (seismic data organized in CMP x Offset X Time coordinates). 
These parameters can be used to fit the data with the non-hyperbolic CRS traveltime approximation.

[More information about the non-hyperbolic CRS](http://www.reproducibility.org/RSF/book/tccs/crs/paper_html/)

## Development setup

You need to have the actual Madagascar package stable release installed on your computer. Please follow the
[Installing Madagascar page](http://www.ahay.org/wiki/Installation) in the official documentation.

## Installation

After Madagascar installing process, you need to install the programs of this repository in your local Madagascar users
directory. You can compile and install as any Madagascar program. 
Run 'scons' on your Madagascar repository to compile:

```shell
~$ scons
```

If you need a SConstruct to compile, use 
[this example](https://github.com/Dirack/cre-gather-interpolation/blob/documentation/0.1/SConstruct).

And install it on your local Madagascar installation:

```shell
~$ sudo scons install
```

If you have any doubt about this process, please reffer to the oficial documentation in 
[Adding_new_programs_to_Madagascar](http://www.ahay.org/wiki/Adding_new_programs_to_Madagascar)

## Usage example

A few motivating and useful examples of how that product can be used can be found in the 
[usage_examples directory](https://github.com/ahay/src/tree/master/user/dirack/usage_examples).

_For more examples and usage, please refer to the [Wiki](https://github.com/Dirack/vfsa/wiki)._

We also have many SConstruct examples in this repository in the
[experiments directory](https://github.com/Dirack/cre-gather-interpolation/tree/documentation/0.1/experiments)

## Release History

* 1.0 - Stable release
    * The first proper release
    * Complete global optimization of the CRS parameters
    * Available in the [Madasgacar package](https://github.com/ahay/src/tree/master/user/dirack)

## Meta

Rodolfo Dirack – [@dirack](https://github.com/Dirack) – rodolfo_profissional@hotmail.com

Distributed under the GPL3 license. See ``LICENSE`` for more information.

[vfsa main page](https://github.com/Dirack/vfsa)

## Contributing

1. Fork it (<https://github.com/Dirack/vfsa/fork>)
2. Create your feature branch (`git checkout -b feature/fooBar`)
3. Commit your changes (`git commit -am 'Add some fooBar'`)
4. Push to the branch (`git push origin feature/fooBar`)
5. Create a new Pull Request

#### Important: The commit history should be clear, with commit mesages around one or two paraghraps describing your modifications. Pull Requests with unsatisfactory commit history will be rejected.
