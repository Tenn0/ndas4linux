#ifndef NDAS_NO_LANSCSI

//  IBM PC Implementation of the DES Cryptographic Algorithm by
//  Dr B. R. Gladman (gladman@seven77.demon.co.uk)
//
//  Some of the techniques in this DES source code are derived 
//  from ideas developed by Richard Outerbridge and Eric Young.  
//  I gratefully acknowledge their contribution.
//
//  DES Timings:
//  Key Setup:    1024 cycles
//  Encrypt:     456.4 cycles =   28.05 mbits/sec
//  Decrypt:     453.1 cycles =   28.25 mbits/sec
//  Mean:        454.8 cycles =   28.15 mbits/sec

#define BIG_TABLES

#include "des.h"

#ifdef  BIG_TABLES
#  define   TAB_SIZE    256
#else
#  define   TAB_SIZE     64
#endif

xuint32 sx_tab[8][TAB_SIZE] =
{
  { 0x00820200L, 0x00020000L, 0x80800000L, 0x80820200L,
    0x00800000L, 0x80020200L, 0x80020000L, 0x80800000L,
    0x80020200L, 0x00820200L, 0x00820000L, 0x80000200L,
    0x80800200L, 0x00800000L, 0x00000000L, 0x80020000L,
    0x00020000L, 0x80000000L, 0x00800200L, 0x00020200L,
    0x80820200L, 0x00820000L, 0x80000200L, 0x00800200L,
    0x80000000L, 0x00000200L, 0x00020200L, 0x80820000L,
    0x00000200L, 0x80800200L, 0x80820000L, 0x00000000L,
    0x00000000L, 0x80820200L, 0x00800200L, 0x80020000L,
    0x00820200L, 0x00020000L, 0x80000200L, 0x00800200L,
    0x80820000L, 0x00000200L, 0x00020200L, 0x80800000L,
    0x80020200L, 0x80000000L, 0x80800000L, 0x00820000L,
    0x80820200L, 0x00020200L, 0x00820000L, 0x80800200L,
    0x00800000L, 0x80000200L, 0x80020000L, 0x00000000L,
    0x00020000L, 0x00800000L, 0x80800200L, 0x00820200L,
    0x80000000L, 0x80820000L, 0x00000200L, 0x80020200L,
#ifdef BIG_TABLES
    0x00820200L, 0x00020000L, 0x80800000L, 0x80820200L,
    0x00800000L, 0x80020200L, 0x80020000L, 0x80800000L,
    0x80020200L, 0x00820200L, 0x00820000L, 0x80000200L,
    0x80800200L, 0x00800000L, 0x00000000L, 0x80020000L,
    0x00020000L, 0x80000000L, 0x00800200L, 0x00020200L,
    0x80820200L, 0x00820000L, 0x80000200L, 0x00800200L,
    0x80000000L, 0x00000200L, 0x00020200L, 0x80820000L,
    0x00000200L, 0x80800200L, 0x80820000L, 0x00000000L,
    0x00000000L, 0x80820200L, 0x00800200L, 0x80020000L,
    0x00820200L, 0x00020000L, 0x80000200L, 0x00800200L,
    0x80820000L, 0x00000200L, 0x00020200L, 0x80800000L,
    0x80020200L, 0x80000000L, 0x80800000L, 0x00820000L,
    0x80820200L, 0x00020200L, 0x00820000L, 0x80800200L,
    0x00800000L, 0x80000200L, 0x80020000L, 0x00000000L,
    0x00020000L, 0x00800000L, 0x80800200L, 0x00820200L,
    0x80000000L, 0x80820000L, 0x00000200L, 0x80020200L,

    0x00820200L, 0x00020000L, 0x80800000L, 0x80820200L,
    0x00800000L, 0x80020200L, 0x80020000L, 0x80800000L,
    0x80020200L, 0x00820200L, 0x00820000L, 0x80000200L,
    0x80800200L, 0x00800000L, 0x00000000L, 0x80020000L,
    0x00020000L, 0x80000000L, 0x00800200L, 0x00020200L,
    0x80820200L, 0x00820000L, 0x80000200L, 0x00800200L,
    0x80000000L, 0x00000200L, 0x00020200L, 0x80820000L,
    0x00000200L, 0x80800200L, 0x80820000L, 0x00000000L,
    0x00000000L, 0x80820200L, 0x00800200L, 0x80020000L,
    0x00820200L, 0x00020000L, 0x80000200L, 0x00800200L,
    0x80820000L, 0x00000200L, 0x00020200L, 0x80800000L,
    0x80020200L, 0x80000000L, 0x80800000L, 0x00820000L,
    0x80820200L, 0x00020200L, 0x00820000L, 0x80800200L,
    0x00800000L, 0x80000200L, 0x80020000L, 0x00000000L,
    0x00020000L, 0x00800000L, 0x80800200L, 0x00820200L,
    0x80000000L, 0x80820000L, 0x00000200L, 0x80020200L,

    0x00820200L, 0x00020000L, 0x80800000L, 0x80820200L,
    0x00800000L, 0x80020200L, 0x80020000L, 0x80800000L,
    0x80020200L, 0x00820200L, 0x00820000L, 0x80000200L,
    0x80800200L, 0x00800000L, 0x00000000L, 0x80020000L,
    0x00020000L, 0x80000000L, 0x00800200L, 0x00020200L,
    0x80820200L, 0x00820000L, 0x80000200L, 0x00800200L,
    0x80000000L, 0x00000200L, 0x00020200L, 0x80820000L,
    0x00000200L, 0x80800200L, 0x80820000L, 0x00000000L,
    0x00000000L, 0x80820200L, 0x00800200L, 0x80020000L,
    0x00820200L, 0x00020000L, 0x80000200L, 0x00800200L,
    0x80820000L, 0x00000200L, 0x00020200L, 0x80800000L,
    0x80020200L, 0x80000000L, 0x80800000L, 0x00820000L,
    0x80820200L, 0x00020200L, 0x00820000L, 0x80800200L,
    0x00800000L, 0x80000200L, 0x80020000L, 0x00000000L,
    0x00020000L, 0x00800000L, 0x80800200L, 0x00820200L,
    0x80000000L, 0x80820000L, 0x00000200L, 0x80020200L,
#endif
  },
  { 0x10042004L, 0x00000000L, 0x00042000L, 0x10040000L,
    0x10000004L, 0x00002004L, 0x10002000L, 0x00042000L,
    0x00002000L, 0x10040004L, 0x00000004L, 0x10002000L,
    0x00040004L, 0x10042000L, 0x10040000L, 0x00000004L,
    0x00040000L, 0x10002004L, 0x10040004L, 0x00002000L,
    0x00042004L, 0x10000000L, 0x00000000L, 0x00040004L,
    0x10002004L, 0x00042004L, 0x10042000L, 0x10000004L,
    0x10000000L, 0x00040000L, 0x00002004L, 0x10042004L,
    0x00040004L, 0x10042000L, 0x10002000L, 0x00042004L,
    0x10042004L, 0x00040004L, 0x10000004L, 0x00000000L,
    0x10000000L, 0x00002004L, 0x00040000L, 0x10040004L,
    0x00002000L, 0x10000000L, 0x00042004L, 0x10002004L,
    0x10042000L, 0x00002000L, 0x00000000L, 0x10000004L,
    0x00000004L, 0x10042004L, 0x00042000L, 0x10040000L,
    0x10040004L, 0x00040000L, 0x00002004L, 0x10002000L,
    0x10002004L, 0x00000004L, 0x10040000L, 0x00042000L,
#ifdef BIG_TABLES
    0x10042004L, 0x00000000L, 0x00042000L, 0x10040000L,
    0x10000004L, 0x00002004L, 0x10002000L, 0x00042000L,
    0x00002000L, 0x10040004L, 0x00000004L, 0x10002000L,
    0x00040004L, 0x10042000L, 0x10040000L, 0x00000004L,
    0x00040000L, 0x10002004L, 0x10040004L, 0x00002000L,
    0x00042004L, 0x10000000L, 0x00000000L, 0x00040004L,
    0x10002004L, 0x00042004L, 0x10042000L, 0x10000004L,
    0x10000000L, 0x00040000L, 0x00002004L, 0x10042004L,
    0x00040004L, 0x10042000L, 0x10002000L, 0x00042004L,
    0x10042004L, 0x00040004L, 0x10000004L, 0x00000000L,
    0x10000000L, 0x00002004L, 0x00040000L, 0x10040004L,
    0x00002000L, 0x10000000L, 0x00042004L, 0x10002004L,
    0x10042000L, 0x00002000L, 0x00000000L, 0x10000004L,
    0x00000004L, 0x10042004L, 0x00042000L, 0x10040000L,
    0x10040004L, 0x00040000L, 0x00002004L, 0x10002000L,
    0x10002004L, 0x00000004L, 0x10040000L, 0x00042000L,

    0x10042004L, 0x00000000L, 0x00042000L, 0x10040000L,
    0x10000004L, 0x00002004L, 0x10002000L, 0x00042000L,
    0x00002000L, 0x10040004L, 0x00000004L, 0x10002000L,
    0x00040004L, 0x10042000L, 0x10040000L, 0x00000004L,
    0x00040000L, 0x10002004L, 0x10040004L, 0x00002000L,
    0x00042004L, 0x10000000L, 0x00000000L, 0x00040004L,
    0x10002004L, 0x00042004L, 0x10042000L, 0x10000004L,
    0x10000000L, 0x00040000L, 0x00002004L, 0x10042004L,
    0x00040004L, 0x10042000L, 0x10002000L, 0x00042004L,
    0x10042004L, 0x00040004L, 0x10000004L, 0x00000000L,
    0x10000000L, 0x00002004L, 0x00040000L, 0x10040004L,
    0x00002000L, 0x10000000L, 0x00042004L, 0x10002004L,
    0x10042000L, 0x00002000L, 0x00000000L, 0x10000004L,
    0x00000004L, 0x10042004L, 0x00042000L, 0x10040000L,
    0x10040004L, 0x00040000L, 0x00002004L, 0x10002000L,
    0x10002004L, 0x00000004L, 0x10040000L, 0x00042000L,

    0x10042004L, 0x00000000L, 0x00042000L, 0x10040000L,
    0x10000004L, 0x00002004L, 0x10002000L, 0x00042000L,
    0x00002000L, 0x10040004L, 0x00000004L, 0x10002000L,
    0x00040004L, 0x10042000L, 0x10040000L, 0x00000004L,
    0x00040000L, 0x10002004L, 0x10040004L, 0x00002000L,
    0x00042004L, 0x10000000L, 0x00000000L, 0x00040004L,
    0x10002004L, 0x00042004L, 0x10042000L, 0x10000004L,
    0x10000000L, 0x00040000L, 0x00002004L, 0x10042004L,
    0x00040004L, 0x10042000L, 0x10002000L, 0x00042004L,
    0x10042004L, 0x00040004L, 0x10000004L, 0x00000000L,
    0x10000000L, 0x00002004L, 0x00040000L, 0x10040004L,
    0x00002000L, 0x10000000L, 0x00042004L, 0x10002004L,
    0x10042000L, 0x00002000L, 0x00000000L, 0x10000004L,
    0x00000004L, 0x10042004L, 0x00042000L, 0x10040000L,
    0x10040004L, 0x00040000L, 0x00002004L, 0x10002000L,
    0x10002004L, 0x00000004L, 0x10040000L, 0x00042000L,
#endif
  },
  { 0x41000000L, 0x01010040L, 0x00000040L, 0x41000040L,
    0x40010000L, 0x01000000L, 0x41000040L, 0x00010040L,
    0x01000040L, 0x00010000L, 0x01010000L, 0x40000000L,
    0x41010040L, 0x40000040L, 0x40000000L, 0x41010000L,
    0x00000000L, 0x40010000L, 0x01010040L, 0x00000040L,
    0x40000040L, 0x41010040L, 0x00010000L, 0x41000000L,
    0x41010000L, 0x01000040L, 0x40010040L, 0x01010000L,
    0x00010040L, 0x00000000L, 0x01000000L, 0x40010040L,
    0x01010040L, 0x00000040L, 0x40000000L, 0x00010000L,
    0x40000040L, 0x40010000L, 0x01010000L, 0x41000040L,
    0x00000000L, 0x01010040L, 0x00010040L, 0x41010000L,
    0x40010000L, 0x01000000L, 0x41010040L, 0x40000000L,
    0x40010040L, 0x41000000L, 0x01000000L, 0x41010040L,
    0x00010000L, 0x01000040L, 0x41000040L, 0x00010040L,
    0x01000040L, 0x00000000L, 0x41010000L, 0x40000040L,
    0x41000000L, 0x40010040L, 0x00000040L, 0x01010000L,
#ifdef BIG_TABLES
    0x41000000L, 0x01010040L, 0x00000040L, 0x41000040L,
    0x40010000L, 0x01000000L, 0x41000040L, 0x00010040L,
    0x01000040L, 0x00010000L, 0x01010000L, 0x40000000L,
    0x41010040L, 0x40000040L, 0x40000000L, 0x41010000L,
    0x00000000L, 0x40010000L, 0x01010040L, 0x00000040L,
    0x40000040L, 0x41010040L, 0x00010000L, 0x41000000L,
    0x41010000L, 0x01000040L, 0x40010040L, 0x01010000L,
    0x00010040L, 0x00000000L, 0x01000000L, 0x40010040L,
    0x01010040L, 0x00000040L, 0x40000000L, 0x00010000L,
    0x40000040L, 0x40010000L, 0x01010000L, 0x41000040L,
    0x00000000L, 0x01010040L, 0x00010040L, 0x41010000L,
    0x40010000L, 0x01000000L, 0x41010040L, 0x40000000L,
    0x40010040L, 0x41000000L, 0x01000000L, 0x41010040L,
    0x00010000L, 0x01000040L, 0x41000040L, 0x00010040L,
    0x01000040L, 0x00000000L, 0x41010000L, 0x40000040L,
    0x41000000L, 0x40010040L, 0x00000040L, 0x01010000L,

    0x41000000L, 0x01010040L, 0x00000040L, 0x41000040L,
    0x40010000L, 0x01000000L, 0x41000040L, 0x00010040L,
    0x01000040L, 0x00010000L, 0x01010000L, 0x40000000L,
    0x41010040L, 0x40000040L, 0x40000000L, 0x41010000L,
    0x00000000L, 0x40010000L, 0x01010040L, 0x00000040L,
    0x40000040L, 0x41010040L, 0x00010000L, 0x41000000L,
    0x41010000L, 0x01000040L, 0x40010040L, 0x01010000L,
    0x00010040L, 0x00000000L, 0x01000000L, 0x40010040L,
    0x01010040L, 0x00000040L, 0x40000000L, 0x00010000L,
    0x40000040L, 0x40010000L, 0x01010000L, 0x41000040L,
    0x00000000L, 0x01010040L, 0x00010040L, 0x41010000L,
    0x40010000L, 0x01000000L, 0x41010040L, 0x40000000L,
    0x40010040L, 0x41000000L, 0x01000000L, 0x41010040L,
    0x00010000L, 0x01000040L, 0x41000040L, 0x00010040L,
    0x01000040L, 0x00000000L, 0x41010000L, 0x40000040L,
    0x41000000L, 0x40010040L, 0x00000040L, 0x01010000L,

    0x41000000L, 0x01010040L, 0x00000040L, 0x41000040L,
    0x40010000L, 0x01000000L, 0x41000040L, 0x00010040L,
    0x01000040L, 0x00010000L, 0x01010000L, 0x40000000L,
    0x41010040L, 0x40000040L, 0x40000000L, 0x41010000L,
    0x00000000L, 0x40010000L, 0x01010040L, 0x00000040L,
    0x40000040L, 0x41010040L, 0x00010000L, 0x41000000L,
    0x41010000L, 0x01000040L, 0x40010040L, 0x01010000L,
    0x00010040L, 0x00000000L, 0x01000000L, 0x40010040L,
    0x01010040L, 0x00000040L, 0x40000000L, 0x00010000L,
    0x40000040L, 0x40010000L, 0x01010000L, 0x41000040L,
    0x00000000L, 0x01010040L, 0x00010040L, 0x41010000L,
    0x40010000L, 0x01000000L, 0x41010040L, 0x40000000L,
    0x40010040L, 0x41000000L, 0x01000000L, 0x41010040L,
    0x00010000L, 0x01000040L, 0x41000040L, 0x00010040L,
    0x01000040L, 0x00000000L, 0x41010000L, 0x40000040L,
    0x41000000L, 0x40010040L, 0x00000040L, 0x01010000L,
#endif
  },
  { 0x00100402L, 0x04000400L, 0x00000002L, 0x04100402L,
    0x00000000L, 0x04100000L, 0x04000402L, 0x00100002L,
    0x04100400L, 0x04000002L, 0x04000000L, 0x00000402L,
    0x04000002L, 0x00100402L, 0x00100000L, 0x04000000L,
    0x04100002L, 0x00100400L, 0x00000400L, 0x00000002L,
    0x00100400L, 0x04000402L, 0x04100000L, 0x00000400L,
    0x00000402L, 0x00000000L, 0x00100002L, 0x04100400L,
    0x04000400L, 0x04100002L, 0x04100402L, 0x00100000L,
    0x04100002L, 0x00000402L, 0x00100000L, 0x04000002L,
    0x00100400L, 0x04000400L, 0x00000002L, 0x04100000L,
    0x04000402L, 0x00000000L, 0x00000400L, 0x00100002L,
    0x00000000L, 0x04100002L, 0x04100400L, 0x00000400L,
    0x04000000L, 0x04100402L, 0x00100402L, 0x00100000L,
    0x04100402L, 0x00000002L, 0x04000400L, 0x00100402L,
    0x00100002L, 0x00100400L, 0x04100000L, 0x04000402L,
    0x00000402L, 0x04000000L, 0x04000002L, 0x04100400L,
#ifdef BIG_TABLES
    0x00100402L, 0x04000400L, 0x00000002L, 0x04100402L,
    0x00000000L, 0x04100000L, 0x04000402L, 0x00100002L,
    0x04100400L, 0x04000002L, 0x04000000L, 0x00000402L,
    0x04000002L, 0x00100402L, 0x00100000L, 0x04000000L,
    0x04100002L, 0x00100400L, 0x00000400L, 0x00000002L,
    0x00100400L, 0x04000402L, 0x04100000L, 0x00000400L,
    0x00000402L, 0x00000000L, 0x00100002L, 0x04100400L,
    0x04000400L, 0x04100002L, 0x04100402L, 0x00100000L,
    0x04100002L, 0x00000402L, 0x00100000L, 0x04000002L,
    0x00100400L, 0x04000400L, 0x00000002L, 0x04100000L,
    0x04000402L, 0x00000000L, 0x00000400L, 0x00100002L,
    0x00000000L, 0x04100002L, 0x04100400L, 0x00000400L,
    0x04000000L, 0x04100402L, 0x00100402L, 0x00100000L,
    0x04100402L, 0x00000002L, 0x04000400L, 0x00100402L,
    0x00100002L, 0x00100400L, 0x04100000L, 0x04000402L,
    0x00000402L, 0x04000000L, 0x04000002L, 0x04100400L,

    0x00100402L, 0x04000400L, 0x00000002L, 0x04100402L,
    0x00000000L, 0x04100000L, 0x04000402L, 0x00100002L,
    0x04100400L, 0x04000002L, 0x04000000L, 0x00000402L,
    0x04000002L, 0x00100402L, 0x00100000L, 0x04000000L,
    0x04100002L, 0x00100400L, 0x00000400L, 0x00000002L,
    0x00100400L, 0x04000402L, 0x04100000L, 0x00000400L,
    0x00000402L, 0x00000000L, 0x00100002L, 0x04100400L,
    0x04000400L, 0x04100002L, 0x04100402L, 0x00100000L,
    0x04100002L, 0x00000402L, 0x00100000L, 0x04000002L,
    0x00100400L, 0x04000400L, 0x00000002L, 0x04100000L,
    0x04000402L, 0x00000000L, 0x00000400L, 0x00100002L,
    0x00000000L, 0x04100002L, 0x04100400L, 0x00000400L,
    0x04000000L, 0x04100402L, 0x00100402L, 0x00100000L,
    0x04100402L, 0x00000002L, 0x04000400L, 0x00100402L,
    0x00100002L, 0x00100400L, 0x04100000L, 0x04000402L,
    0x00000402L, 0x04000000L, 0x04000002L, 0x04100400L,

    0x00100402L, 0x04000400L, 0x00000002L, 0x04100402L,
    0x00000000L, 0x04100000L, 0x04000402L, 0x00100002L,
    0x04100400L, 0x04000002L, 0x04000000L, 0x00000402L,
    0x04000002L, 0x00100402L, 0x00100000L, 0x04000000L,
    0x04100002L, 0x00100400L, 0x00000400L, 0x00000002L,
    0x00100400L, 0x04000402L, 0x04100000L, 0x00000400L,
    0x00000402L, 0x00000000L, 0x00100002L, 0x04100400L,
    0x04000400L, 0x04100002L, 0x04100402L, 0x00100000L,
    0x04100002L, 0x00000402L, 0x00100000L, 0x04000002L,
    0x00100400L, 0x04000400L, 0x00000002L, 0x04100000L,
    0x04000402L, 0x00000000L, 0x00000400L, 0x00100002L,
    0x00000000L, 0x04100002L, 0x04100400L, 0x00000400L,
    0x04000000L, 0x04100402L, 0x00100402L, 0x00100000L,
    0x04100402L, 0x00000002L, 0x04000400L, 0x00100402L,
    0x00100002L, 0x00100400L, 0x04100000L, 0x04000402L,
    0x00000402L, 0x04000000L, 0x04000002L, 0x04100400L,
#endif
  },
  { 0x02000000L, 0x00004000L, 0x00000100L, 0x02004108L,
    0x02004008L, 0x02000100L, 0x00004108L, 0x02004000L,
    0x00004000L, 0x00000008L, 0x02000008L, 0x00004100L,
    0x02000108L, 0x02004008L, 0x02004100L, 0x00000000L,
    0x00004100L, 0x02000000L, 0x00004008L, 0x00000108L,
    0x02000100L, 0x00004108L, 0x00000000L, 0x02000008L,
    0x00000008L, 0x02000108L, 0x02004108L, 0x00004008L,
    0x02004000L, 0x00000100L, 0x00000108L, 0x02004100L,
    0x02004100L, 0x02000108L, 0x00004008L, 0x02004000L,
    0x00004000L, 0x00000008L, 0x02000008L, 0x02000100L,
    0x02000000L, 0x00004100L, 0x02004108L, 0x00000000L,
    0x00004108L, 0x02000000L, 0x00000100L, 0x00004008L,
    0x02000108L, 0x00000100L, 0x00000000L, 0x02004108L,
    0x02004008L, 0x02004100L, 0x00000108L, 0x00004000L,
    0x00004100L, 0x02004008L, 0x02000100L, 0x00000108L,
    0x00000008L, 0x00004108L, 0x02004000L, 0x02000008L,
#ifdef BIG_TABLES
    0x02000000L, 0x00004000L, 0x00000100L, 0x02004108L,
    0x02004008L, 0x02000100L, 0x00004108L, 0x02004000L,
    0x00004000L, 0x00000008L, 0x02000008L, 0x00004100L,
    0x02000108L, 0x02004008L, 0x02004100L, 0x00000000L,
    0x00004100L, 0x02000000L, 0x00004008L, 0x00000108L,
    0x02000100L, 0x00004108L, 0x00000000L, 0x02000008L,
    0x00000008L, 0x02000108L, 0x02004108L, 0x00004008L,
    0x02004000L, 0x00000100L, 0x00000108L, 0x02004100L,
    0x02004100L, 0x02000108L, 0x00004008L, 0x02004000L,
    0x00004000L, 0x00000008L, 0x02000008L, 0x02000100L,
    0x02000000L, 0x00004100L, 0x02004108L, 0x00000000L,
    0x00004108L, 0x02000000L, 0x00000100L, 0x00004008L,
    0x02000108L, 0x00000100L, 0x00000000L, 0x02004108L,
    0x02004008L, 0x02004100L, 0x00000108L, 0x00004000L,
    0x00004100L, 0x02004008L, 0x02000100L, 0x00000108L,
    0x00000008L, 0x00004108L, 0x02004000L, 0x02000008L,

    0x02000000L, 0x00004000L, 0x00000100L, 0x02004108L,
    0x02004008L, 0x02000100L, 0x00004108L, 0x02004000L,
    0x00004000L, 0x00000008L, 0x02000008L, 0x00004100L,
    0x02000108L, 0x02004008L, 0x02004100L, 0x00000000L,
    0x00004100L, 0x02000000L, 0x00004008L, 0x00000108L,
    0x02000100L, 0x00004108L, 0x00000000L, 0x02000008L,
    0x00000008L, 0x02000108L, 0x02004108L, 0x00004008L,
    0x02004000L, 0x00000100L, 0x00000108L, 0x02004100L,
    0x02004100L, 0x02000108L, 0x00004008L, 0x02004000L,
    0x00004000L, 0x00000008L, 0x02000008L, 0x02000100L,
    0x02000000L, 0x00004100L, 0x02004108L, 0x00000000L,
    0x00004108L, 0x02000000L, 0x00000100L, 0x00004008L,
    0x02000108L, 0x00000100L, 0x00000000L, 0x02004108L,
    0x02004008L, 0x02004100L, 0x00000108L, 0x00004000L,
    0x00004100L, 0x02004008L, 0x02000100L, 0x00000108L,
    0x00000008L, 0x00004108L, 0x02004000L, 0x02000008L,

    0x02000000L, 0x00004000L, 0x00000100L, 0x02004108L,
    0x02004008L, 0x02000100L, 0x00004108L, 0x02004000L,
    0x00004000L, 0x00000008L, 0x02000008L, 0x00004100L,
    0x02000108L, 0x02004008L, 0x02004100L, 0x00000000L,
    0x00004100L, 0x02000000L, 0x00004008L, 0x00000108L,
    0x02000100L, 0x00004108L, 0x00000000L, 0x02000008L,
    0x00000008L, 0x02000108L, 0x02004108L, 0x00004008L,
    0x02004000L, 0x00000100L, 0x00000108L, 0x02004100L,
    0x02004100L, 0x02000108L, 0x00004008L, 0x02004000L,
    0x00004000L, 0x00000008L, 0x02000008L, 0x02000100L,
    0x02000000L, 0x00004100L, 0x02004108L, 0x00000000L,
    0x00004108L, 0x02000000L, 0x00000100L, 0x00004008L,
    0x02000108L, 0x00000100L, 0x00000000L, 0x02004108L,
    0x02004008L, 0x02004100L, 0x00000108L, 0x00004000L,
    0x00004100L, 0x02004008L, 0x02000100L, 0x00000108L,
    0x00000008L, 0x00004108L, 0x02004000L, 0x02000008L,
#endif
  },
  { 0x20000010L, 0x00080010L, 0x00000000L, 0x20080800L,
    0x00080010L, 0x00000800L, 0x20000810L, 0x00080000L,
    0x00000810L, 0x20080810L, 0x00080800L, 0x20000000L,
    0x20000800L, 0x20000010L, 0x20080000L, 0x00080810L,
    0x00080000L, 0x20000810L, 0x20080010L, 0x00000000L,
    0x00000800L, 0x00000010L, 0x20080800L, 0x20080010L,
    0x20080810L, 0x20080000L, 0x20000000L, 0x00000810L,
    0x00000010L, 0x00080800L, 0x00080810L, 0x20000800L,
    0x00000810L, 0x20000000L, 0x20000800L, 0x00080810L,
    0x20080800L, 0x00080010L, 0x00000000L, 0x20000800L,
    0x20000000L, 0x00000800L, 0x20080010L, 0x00080000L,
    0x00080010L, 0x20080810L, 0x00080800L, 0x00000010L,
    0x20080810L, 0x00080800L, 0x00080000L, 0x20000810L,
    0x20000010L, 0x20080000L, 0x00080810L, 0x00000000L,
    0x00000800L, 0x20000010L, 0x20000810L, 0x20080800L,
    0x20080000L, 0x00000810L, 0x00000010L, 0x20080010L,
#ifdef BIG_TABLES
    0x20000010L, 0x00080010L, 0x00000000L, 0x20080800L,
    0x00080010L, 0x00000800L, 0x20000810L, 0x00080000L,
    0x00000810L, 0x20080810L, 0x00080800L, 0x20000000L,
    0x20000800L, 0x20000010L, 0x20080000L, 0x00080810L,
    0x00080000L, 0x20000810L, 0x20080010L, 0x00000000L,
    0x00000800L, 0x00000010L, 0x20080800L, 0x20080010L,
    0x20080810L, 0x20080000L, 0x20000000L, 0x00000810L,
    0x00000010L, 0x00080800L, 0x00080810L, 0x20000800L,
    0x00000810L, 0x20000000L, 0x20000800L, 0x00080810L,
    0x20080800L, 0x00080010L, 0x00000000L, 0x20000800L,
    0x20000000L, 0x00000800L, 0x20080010L, 0x00080000L,
    0x00080010L, 0x20080810L, 0x00080800L, 0x00000010L,
    0x20080810L, 0x00080800L, 0x00080000L, 0x20000810L,
    0x20000010L, 0x20080000L, 0x00080810L, 0x00000000L,
    0x00000800L, 0x20000010L, 0x20000810L, 0x20080800L,
    0x20080000L, 0x00000810L, 0x00000010L, 0x20080010L,

    0x20000010L, 0x00080010L, 0x00000000L, 0x20080800L,
    0x00080010L, 0x00000800L, 0x20000810L, 0x00080000L,
    0x00000810L, 0x20080810L, 0x00080800L, 0x20000000L,
    0x20000800L, 0x20000010L, 0x20080000L, 0x00080810L,
    0x00080000L, 0x20000810L, 0x20080010L, 0x00000000L,
    0x00000800L, 0x00000010L, 0x20080800L, 0x20080010L,
    0x20080810L, 0x20080000L, 0x20000000L, 0x00000810L,
    0x00000010L, 0x00080800L, 0x00080810L, 0x20000800L,
    0x00000810L, 0x20000000L, 0x20000800L, 0x00080810L,
    0x20080800L, 0x00080010L, 0x00000000L, 0x20000800L,
    0x20000000L, 0x00000800L, 0x20080010L, 0x00080000L,
    0x00080010L, 0x20080810L, 0x00080800L, 0x00000010L,
    0x20080810L, 0x00080800L, 0x00080000L, 0x20000810L,
    0x20000010L, 0x20080000L, 0x00080810L, 0x00000000L,
    0x00000800L, 0x20000010L, 0x20000810L, 0x20080800L,
    0x20080000L, 0x00000810L, 0x00000010L, 0x20080010L,

    0x20000010L, 0x00080010L, 0x00000000L, 0x20080800L,
    0x00080010L, 0x00000800L, 0x20000810L, 0x00080000L,
    0x00000810L, 0x20080810L, 0x00080800L, 0x20000000L,
    0x20000800L, 0x20000010L, 0x20080000L, 0x00080810L,
    0x00080000L, 0x20000810L, 0x20080010L, 0x00000000L,
    0x00000800L, 0x00000010L, 0x20080800L, 0x20080010L,
    0x20080810L, 0x20080000L, 0x20000000L, 0x00000810L,
    0x00000010L, 0x00080800L, 0x00080810L, 0x20000800L,
    0x00000810L, 0x20000000L, 0x20000800L, 0x00080810L,
    0x20080800L, 0x00080010L, 0x00000000L, 0x20000800L,
    0x20000000L, 0x00000800L, 0x20080010L, 0x00080000L,
    0x00080010L, 0x20080810L, 0x00080800L, 0x00000010L,
    0x20080810L, 0x00080800L, 0x00080000L, 0x20000810L,
    0x20000010L, 0x20080000L, 0x00080810L, 0x00000000L,
    0x00000800L, 0x20000010L, 0x20000810L, 0x20080800L,
    0x20080000L, 0x00000810L, 0x00000010L, 0x20080010L,
#endif
  },
  { 0x00001000L, 0x00000080L, 0x00400080L, 0x00400001L,
    0x00401081L, 0x00001001L, 0x00001080L, 0x00000000L,
    0x00400000L, 0x00400081L, 0x00000081L, 0x00401000L,
    0x00000001L, 0x00401080L, 0x00401000L, 0x00000081L,
    0x00400081L, 0x00001000L, 0x00001001L, 0x00401081L,
    0x00000000L, 0x00400080L, 0x00400001L, 0x00001080L,
    0x00401001L, 0x00001081L, 0x00401080L, 0x00000001L,
    0x00001081L, 0x00401001L, 0x00000080L, 0x00400000L,
    0x00001081L, 0x00401000L, 0x00401001L, 0x00000081L,
    0x00001000L, 0x00000080L, 0x00400000L, 0x00401001L,
    0x00400081L, 0x00001081L, 0x00001080L, 0x00000000L,
    0x00000080L, 0x00400001L, 0x00000001L, 0x00400080L,
    0x00000000L, 0x00400081L, 0x00400080L, 0x00001080L,
    0x00000081L, 0x00001000L, 0x00401081L, 0x00400000L,
    0x00401080L, 0x00000001L, 0x00001001L, 0x00401081L,
    0x00400001L, 0x00401080L, 0x00401000L, 0x00001001L,
#ifdef BIG_TABLES
    0x00001000L, 0x00000080L, 0x00400080L, 0x00400001L,
    0x00401081L, 0x00001001L, 0x00001080L, 0x00000000L,
    0x00400000L, 0x00400081L, 0x00000081L, 0x00401000L,
    0x00000001L, 0x00401080L, 0x00401000L, 0x00000081L,
    0x00400081L, 0x00001000L, 0x00001001L, 0x00401081L,
    0x00000000L, 0x00400080L, 0x00400001L, 0x00001080L,
    0x00401001L, 0x00001081L, 0x00401080L, 0x00000001L,
    0x00001081L, 0x00401001L, 0x00000080L, 0x00400000L,
    0x00001081L, 0x00401000L, 0x00401001L, 0x00000081L,
    0x00001000L, 0x00000080L, 0x00400000L, 0x00401001L,
    0x00400081L, 0x00001081L, 0x00001080L, 0x00000000L,
    0x00000080L, 0x00400001L, 0x00000001L, 0x00400080L,
    0x00000000L, 0x00400081L, 0x00400080L, 0x00001080L,
    0x00000081L, 0x00001000L, 0x00401081L, 0x00400000L,
    0x00401080L, 0x00000001L, 0x00001001L, 0x00401081L,
    0x00400001L, 0x00401080L, 0x00401000L, 0x00001001L,

    0x00001000L, 0x00000080L, 0x00400080L, 0x00400001L,
    0x00401081L, 0x00001001L, 0x00001080L, 0x00000000L,
    0x00400000L, 0x00400081L, 0x00000081L, 0x00401000L,
    0x00000001L, 0x00401080L, 0x00401000L, 0x00000081L,
    0x00400081L, 0x00001000L, 0x00001001L, 0x00401081L,
    0x00000000L, 0x00400080L, 0x00400001L, 0x00001080L,
    0x00401001L, 0x00001081L, 0x00401080L, 0x00000001L,
    0x00001081L, 0x00401001L, 0x00000080L, 0x00400000L,
    0x00001081L, 0x00401000L, 0x00401001L, 0x00000081L,
    0x00001000L, 0x00000080L, 0x00400000L, 0x00401001L,
    0x00400081L, 0x00001081L, 0x00001080L, 0x00000000L,
    0x00000080L, 0x00400001L, 0x00000001L, 0x00400080L,
    0x00000000L, 0x00400081L, 0x00400080L, 0x00001080L,
    0x00000081L, 0x00001000L, 0x00401081L, 0x00400000L,
    0x00401080L, 0x00000001L, 0x00001001L, 0x00401081L,
    0x00400001L, 0x00401080L, 0x00401000L, 0x00001001L,

    0x00001000L, 0x00000080L, 0x00400080L, 0x00400001L,
    0x00401081L, 0x00001001L, 0x00001080L, 0x00000000L,
    0x00400000L, 0x00400081L, 0x00000081L, 0x00401000L,
    0x00000001L, 0x00401080L, 0x00401000L, 0x00000081L,
    0x00400081L, 0x00001000L, 0x00001001L, 0x00401081L,
    0x00000000L, 0x00400080L, 0x00400001L, 0x00001080L,
    0x00401001L, 0x00001081L, 0x00401080L, 0x00000001L,
    0x00001081L, 0x00401001L, 0x00000080L, 0x00400000L,
    0x00001081L, 0x00401000L, 0x00401001L, 0x00000081L,
    0x00001000L, 0x00000080L, 0x00400000L, 0x00401001L,
    0x00400081L, 0x00001081L, 0x00001080L, 0x00000000L,
    0x00000080L, 0x00400001L, 0x00000001L, 0x00400080L,
    0x00000000L, 0x00400081L, 0x00400080L, 0x00001080L,
    0x00000081L, 0x00001000L, 0x00401081L, 0x00400000L,
    0x00401080L, 0x00000001L, 0x00001001L, 0x00401081L,
    0x00400001L, 0x00401080L, 0x00401000L, 0x00001001L,
#endif
  },
  { 0x08200020L, 0x08208000L, 0x00008020L, 0x00000000L,
    0x08008000L, 0x00200020L, 0x08200000L, 0x08208020L,
    0x00000020L, 0x08000000L, 0x00208000L, 0x00008020L,
    0x00208020L, 0x08008020L, 0x08000020L, 0x08200000L,
    0x00008000L, 0x00208020L, 0x00200020L, 0x08008000L,
    0x08208020L, 0x08000020L, 0x00000000L, 0x00208000L,
    0x08000000L, 0x00200000L, 0x08008020L, 0x08200020L,
    0x00200000L, 0x00008000L, 0x08208000L, 0x00000020L,
    0x00200000L, 0x00008000L, 0x08000020L, 0x08208020L,
    0x00008020L, 0x08000000L, 0x00000000L, 0x00208000L,
    0x08200020L, 0x08008020L, 0x08008000L, 0x00200020L,
    0x08208000L, 0x00000020L, 0x00200020L, 0x08008000L,
    0x08208020L, 0x00200000L, 0x08200000L, 0x08000020L,
    0x00208000L, 0x00008020L, 0x08008020L, 0x08200000L,
    0x00000020L, 0x08208000L, 0x00208020L, 0x00000000L,
    0x08000000L, 0x08200020L, 0x00008000L, 0x00208020L,
#ifdef BIG_TABLES
    0x08200020L, 0x08208000L, 0x00008020L, 0x00000000L,
    0x08008000L, 0x00200020L, 0x08200000L, 0x08208020L,
    0x00000020L, 0x08000000L, 0x00208000L, 0x00008020L,
    0x00208020L, 0x08008020L, 0x08000020L, 0x08200000L,
    0x00008000L, 0x00208020L, 0x00200020L, 0x08008000L,
    0x08208020L, 0x08000020L, 0x00000000L, 0x00208000L,
    0x08000000L, 0x00200000L, 0x08008020L, 0x08200020L,
    0x00200000L, 0x00008000L, 0x08208000L, 0x00000020L,
    0x00200000L, 0x00008000L, 0x08000020L, 0x08208020L,
    0x00008020L, 0x08000000L, 0x00000000L, 0x00208000L,
    0x08200020L, 0x08008020L, 0x08008000L, 0x00200020L,
    0x08208000L, 0x00000020L, 0x00200020L, 0x08008000L,
    0x08208020L, 0x00200000L, 0x08200000L, 0x08000020L,
    0x00208000L, 0x00008020L, 0x08008020L, 0x08200000L,
    0x00000020L, 0x08208000L, 0x00208020L, 0x00000000L,
    0x08000000L, 0x08200020L, 0x00008000L, 0x00208020L,

    0x08200020L, 0x08208000L, 0x00008020L, 0x00000000L,
    0x08008000L, 0x00200020L, 0x08200000L, 0x08208020L,
    0x00000020L, 0x08000000L, 0x00208000L, 0x00008020L,
    0x00208020L, 0x08008020L, 0x08000020L, 0x08200000L,
    0x00008000L, 0x00208020L, 0x00200020L, 0x08008000L,
    0x08208020L, 0x08000020L, 0x00000000L, 0x00208000L,
    0x08000000L, 0x00200000L, 0x08008020L, 0x08200020L,
    0x00200000L, 0x00008000L, 0x08208000L, 0x00000020L,
    0x00200000L, 0x00008000L, 0x08000020L, 0x08208020L,
    0x00008020L, 0x08000000L, 0x00000000L, 0x00208000L,
    0x08200020L, 0x08008020L, 0x08008000L, 0x00200020L,
    0x08208000L, 0x00000020L, 0x00200020L, 0x08008000L,
    0x08208020L, 0x00200000L, 0x08200000L, 0x08000020L,
    0x00208000L, 0x00008020L, 0x08008020L, 0x08200000L,
    0x00000020L, 0x08208000L, 0x00208020L, 0x00000000L,
    0x08000000L, 0x08200020L, 0x00008000L, 0x00208020L,

    0x08200020L, 0x08208000L, 0x00008020L, 0x00000000L,
    0x08008000L, 0x00200020L, 0x08200000L, 0x08208020L,
    0x00000020L, 0x08000000L, 0x00208000L, 0x00008020L,
    0x00208020L, 0x08008020L, 0x08000020L, 0x08200000L,
    0x00008000L, 0x00208020L, 0x00200020L, 0x08008000L,
    0x08208020L, 0x08000020L, 0x00000000L, 0x00208000L,
    0x08000000L, 0x00200000L, 0x08008020L, 0x08200020L,
    0x00200000L, 0x00008000L, 0x08208000L, 0x00000020L,
    0x00200000L, 0x00008000L, 0x08000020L, 0x08208020L,
    0x00008020L, 0x08000000L, 0x00000000L, 0x00208000L,
    0x08200020L, 0x08008020L, 0x08008000L, 0x00200020L,
    0x08208000L, 0x00000020L, 0x00200020L, 0x08008000L,
    0x08208020L, 0x00200000L, 0x08200000L, 0x08000020L,
    0x00208000L, 0x00008020L, 0x08008020L, 0x08200000L,
    0x00000020L, 0x08208000L, 0x00208020L, 0x00000000L,
    0x08000000L, 0x08200020L, 0x00008000L, 0x00208020L,
#endif
  }
};

xuint32 bs_tab[] =
{   0x00000001L, 0x00000002L, 0x00000004L, 0x00000008L,
    0x00000010L, 0x00000020L, 0x00000040L, 0x00000080L,
    0x00000100L, 0x00000200L, 0x00000400L, 0x00000800L,
    0x00001000L, 0x00002000L, 0x00004000L, 0x00008000L,
    0x00010000L, 0x00020000L, 0x00040000L, 0x00080000L,
    0x00100000L, 0x00200000L, 0x00400000L, 0x00800000L,
    0x01000000L, 0x02000000L, 0x04000000L, 0x08000000L,
    0x10000000L, 0x20000000L, 0x40000000L, 0x80000000L
};

extern xuint32    key[32];

/* Conver 32 bit integer to little endian on any platform */
#define int_to_little_endian(v) \
        ((((char*)&(v))[0] & 0xff) |\
        (((xuint32) ((char*)&(v))[1] & 0xff) << 8 ) | \
        (((xuint32) ((char*)&(v))[2] & 0xff) << 16 ) |\
        (((xuint32) ((char*)&(v))[3] & 0xff) << 24))

#define int_to_system_endian(v) int_to_little_endian(v)

void des_ec(const void *i_blk, void *o_blk, void *key)
{   
    xuint32   q0, q1, l0, l1, tt;

    q0 = int_to_little_endian(*((char*)i_blk+4));
    q1 = int_to_little_endian(*((char*)i_blk));

    ip(q0, q1);

    round(q0, q1,  0); round(q1, q0,  2);
    round(q0, q1,  4); round(q1, q0,  6);
    round(q0, q1,  8); round(q1, q0, 10);
    round(q0, q1, 12); round(q1, q0, 14);
    round(q0, q1, 16); round(q1, q0, 18);
    round(q0, q1, 20); round(q1, q0, 22);
    round(q0, q1, 24); round(q1, q0, 26);
    round(q0, q1, 28); round(q1, q0, 30);

    fp(q1, q0);

    *(((xuint32*)o_blk)) = int_to_system_endian(q0); 
    *(((xuint32*)o_blk) + 1) = int_to_system_endian(q1);
};

void des_dc(const void *i_blk, void *o_blk, void *key)
{   
    xuint32   q0, q1, l0, l1, tt;

    q0 = int_to_little_endian(*(((char*)i_blk)+4));
    q1 = int_to_little_endian(*((char*)i_blk));    

    ip(q0, q1);
    
    round(q0, q1, 30); round(q1, q0, 28);
    round(q0, q1, 26); round(q1, q0, 24);
    round(q0, q1, 22); round(q1, q0, 20);
    round(q0, q1, 18); round(q1, q0, 16);
    round(q0, q1, 14); round(q1, q0, 12);
    round(q0, q1, 10); round(q1, q0,  8);
    round(q0, q1,  6); round(q1, q0,  4);
    round(q0, q1,  2); round(q1, q0,  0);

    fp(q1, q0);

    *(((xuint32*)o_blk)) = int_to_system_endian(q0); 
    *(((xuint32*)o_blk) + 1) = int_to_system_endian(q1);
};

/* modified encryption routine for DEAL */

void des_ecm(const void *i_blk, void *o_blk, void *key)
{   
    xuint32   q0, q1, l0, l1;

    q0 = int_to_little_endian(*((char*)i_blk+4));
    q1 = int_to_little_endian(*((char*)i_blk));    

    round(q0, q1,  0); round(q1, q0,  2);
    round(q0, q1,  4); round(q1, q0,  6);
    round(q0, q1,  8); round(q1, q0, 10);
    round(q0, q1, 12); round(q1, q0, 14);
    round(q0, q1, 16); round(q1, q0, 18);
    round(q0, q1, 20); round(q1, q0, 22);
    round(q0, q1, 24); round(q1, q0, 26);
    round(q0, q1, 28); round(q1, q0, 30);

    *(((xuint32*)o_blk)) = int_to_system_endian(q0); 
    *(((xuint32*)o_blk) + 1) = int_to_system_endian(q1);
};

#endif /* #ifndef NDAS_NO_LANSCSI */

