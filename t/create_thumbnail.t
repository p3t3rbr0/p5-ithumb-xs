#!/usr/bin/env perl

use strict;
use warnings;

use Test::More 'no_plan';


BEGIN { use_ok('Ithumb::XS'); };

can_ok('Ithumb::XS', 'create_thumbnail');

# Source image have dimension 5x3 px.
use constant SRC => 't/src.png';
use constant DST => 't/src_thumb.png';

eval {
    Ithumb::XS::create_thumbnail({width => -2, height => 2, src => SRC, dst => DST});
} or do {
    like($@, qr/invalid value of width/i, 'check with invalid width');
};

eval {
    Ithumb::XS::create_thumbnail({width => 2, height => -2, src => SRC, dst => DST});
} or do {
    like($@, qr/invalid value of height/i, 'check with invalid height');
};

eval {
    Ithumb::XS::create_thumbnail({width => 2, height => 2, src => 'invalid_file.png', dst => DST});
} or do {
    like($@, qr/file does not exist/i, 'check not exists file');
};

eval {
    Ithumb::XS::create_thumbnail({width => 2, height => 2, src => 'invalid_file.png', dst => ''});
} or do {
    like($@, qr/invalid value of destination file path/i, 'dst is required');
};

ok(
    Ithumb::XS::create_thumbnail({width => 2, height => 2, src => SRC, dst => DST}),
    "create_thumbnail()"
);

unlink DST if -f DST;

done_testing();
