package Ithumb::XS;

use 5.024000;
use strict;
use warnings;

use base 'Exporter';
our @EXPORT_OK = qw(create_thumbnail);

our $VERSION = '0.5.5';

require XSLoader;
XSLoader::load('Ithumb::XS', $VERSION);

1;

__END__

=encoding UTF-8

=head1 NAME

Ithumb::XS - Image thumbnail creation routines

=head1 DESCRIPTION

Ithumb::XS - is a small (one function), simple and fast Perl-XS module
for creation a thumbnails (with resizing and cropping), using Imlib2 library.

=head1 AUTHOR

Peter P. Neuromantic <p.brovchenko@protonmail.com>

=head1 SYNOPSIS

  use Ithumb::XS ();

  Ithumb::XS::create_thumbnail({
      width  => 800,
      height => 600,
      src    => 'src_image.jpg',
      dst    => 'dst_image.jpg'
  });

=head1 FUNCTIONS

=head2 create_thumbnail($)

Creates a small copy (resizing and cropping) of the image.

=over 20

=item $_[0]->{width}  - destination width

=item $_[0]->{height} - destination height

=item $_[0]->{src}    - path to the source image

=item $_[0]->{dst}    - path to the destionation result image

=back

=head1 LICENSE AND COPYRIGHT

BSD 3-Clause License

Copyright (c) 2018-2021 Peter P. Neuromantic E<lt>p.brovchenko@protonmail.comE<gt>.
All rights reserved.

See LICENSE file for more information.

=cut
