# Ithumb::XS (project is closed)

[![Build Status](https://travis-ci.com/ChaoticEvil/p5-ithumb-xs.svg?branch=master)](https://travis-ci.com/ChaoticEvil/p5-ithumb-xs)
[![Coverage Status](https://coveralls.io/repos/github/ChaoticEvil/p5-ithumb-xs/badge.svg?branch=master)](https://coveralls.io/github/ChaoticEvil/p5-ithumb-xs?branch=master)
[![CPAN version](https://badge.fury.io/pl/Ithumb-XS.svg)](https://badge.fury.io/pl/Ithumb-XS)
[![Cpants Kwalitee](https://cpants.cpanauthors.org/release/BRDUCH/Ithumb-XS-0.5.5.svg)](https://cpants.cpanauthors.org/release/BRDUCH/Ithumb-XS-0.5.5)

**! ATTENTION !**

The project was started for educational purposes (for learning Perl C API).
At this moment I haven't reasons for continued development.
There are more suitable solutions for creation of image thumbnails.
I close a project. Thanks all.

---

Ithumb::XS - is a small (one function), simple and fast Perl-XS module
for creation a thumbnails (with resizing and cropping), using Imlib2 library.

## Dependences & requires

This module requires these other modules and libraries:

  Imlib2 (binary and headers)

Required Perl >= v5.24.0

## Installation

### MacOS prepare installation

```
$ brew cask install xquartz
$ brew install imlib2
```

### Manual installation

To manual install this module type the following:

```
$ perl Makefile.PL
$ make
$ make test
$ make install
```

To automatical install this module type the following:

```
$ cpan -i Ithumb::XS
```

## Usage

### From shell (as one-liner)

```
$ perl -MIthumb::XS=create_thumbnail -e \
    "create_thumbnail({width => 800, height => 600, src => '1.jpg', dst => '2.jpg'})"
```

### From perl code

```perl
use Ithumb::XS 'create_thumbnail';

create_thumbnail({
    width  => 800,
    height => 600,
    src    => 'src_image.jpg',
    dst    => 'dst_image.jpg',
});
```

## CopyRight and license

BSD 3-Clause License

Copyright (c) 2018-2021 Peter P. Neuromantic \<p.brovchenko@protonmail.com\>.\
All rights reserved.

See LICENSE file for more information.
