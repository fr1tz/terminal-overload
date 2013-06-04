<?php
// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// NOTE:  This all the source in the libvorbis library which
// according to the README includes libvorbis, libvorbisfile,
// and libvorbisenc.
//
// We really only need libvorbis and libvorbisfile for loading
// ogg vorbis files, but the source is distrubuted all in one
// folder and the project generator does not allow excluding 
// files.
// 
// In an effort to make upgrading this library simple the
// the inclusion of the encoder is acceptable.  It should
// be filtered out of the build by the linker.

addLibSrcDir( 'libvorbis/lib' );
addLibSrcDir( 'libvorbis/lib/books/coupled' );
addLibSrcDir( 'libvorbis/lib/books/floor' );
addLibSrcDir( 'libvorbis/lib/books/uncoupled' );
addLibSrcDir( 'libvorbis/lib/modes' );
addLibSrcDir( 'libvorbis/include/vorbis' );

addLibIncludePath( 'libvorbis/lib' );
addLibIncludePath( 'libvorbis/include' );
addLibIncludePath( 'libogg/include' );

?>